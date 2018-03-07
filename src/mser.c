#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include "alt_dma.h"
#include "alt_globaltmr.h"
#include "socal/hps.h"
#include "socal/socal.h"
#include "mser.h"

struct bp_stack* gBoundary[BD_MAX_LEVELS];
regions_t* gRegions[MSER_MAX_REG];
uint32_t gCurrentPixel = 0;
uint16_t gIndexRegions = 0;
uint32_t gCounterIter = 0;
uint8_t gCurrentEdge = 0;

/******************** START STACK METHODS ********************/
struct bp_stack* CreateStack(uint16_t size){
  // Allocate space for ONE struct of type bp_stack, returning to the pointer stack
  struct bp_stack* stack = (struct bp_stack*) malloc(sizeof(struct bp_stack));
  stack->capacity = size;
  stack->top = -1;
  // Allocate space for SIZE elements in the stack
  stack->pixels = (uint32_t *) malloc(stack->capacity*sizeof(uint32_t));
  return stack;
}

bool isFull(struct bp_stack *stack){
  return (stack->top == stack->capacity-1);
}

bool isEmpty(struct bp_stack *stack){
  return (stack->top == -1);
}

// Function to add an item to stack.  It increases top by 1
void push(struct bp_stack* stack, uint32_t item) {
    if (isFull(stack)){
      printf("\r\n[MSER] Stack is full!");
      return;
    }

    stack->pixels[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
uint32_t pop(struct bp_stack* stack) {
    if (isEmpty(stack)){
      printf("\r\n[MSER] Stack is empty!");
      return -1;
    }
    return stack->pixels[stack->top--];
}

// Function to print stack
void printStack(struct bp_stack* stack) {
  if (isEmpty(stack) == 0) {
    printf("\n\r Printing Stack size, top points to %d",stack->top);
    for (size_t i = 0; i <= stack->top; i++) {
      printf("\n\r[n=%d] %d",i ,stack->pixels[i]);
    }
  }
}
/******************** END STACK METHODS ********************/

/******************** MEMORY FUNCTIONS ********************/
uint8_t getPixelLevel(uint32_t pixel){
  uint32_t *ptr_level = IMG_OFFSET_ADDR;
  uint32_t addrOffset = pixel/4;
  ptr_level += addrOffset;
  uint8_t remain = pixel%4;
  uint32_t mask = (0xff << remain*8);
  uint32_t content = *ptr_level;
  uint8_t data = (content & mask) >> remain*8;
  // printf("\n\r[MSER] Pixel [%d] Reading the byte [%d] of address [%x] = %x",pixel, remain, ptr_level, data);
  return data;
}

uint8_t getPixelneighborLevel(uint32_t pixel, uint8_t edge){
  uint32_t neighborPixel;
  uint16_t x = pixel%IMG_RESOLUTION_WIDTH;
  uint16_t y = pixel/IMG_RESOLUTION_WIDTH;
  uint8_t neighborLevel;
  //
  //                   edge=3
  //           edge=2  PIXEL  edge=0
  //                   edge=1
  //
  switch (edge) {
    case 0: // >>
      if (x < (IMG_RESOLUTION_WIDTH-1)) {
        neighborPixel = pixel+1;
      }
    break;
    case 1: // VV
      if (y < (IMG_RESOLUTION_HEIGHT-1)) {
        neighborPixel = pixel+IMG_RESOLUTION_WIDTH;
      }
    break;
    case 2: // <<
      if (x > 0) {
        neighborPixel = pixel-1;
      }
    break;
    case 3: // ^^
      if (y > 0) {
        neighborPixel = pixel-IMG_RESOLUTION_WIDTH;
      }
    break;
    default:
      neighborPixel = pixel;
    break;
  }

  neighborLevel = getPixelLevel(neighborPixel);
  return neighborLevel;
}

void setMaskBinPixel(uint32_t pixel){
  uint32_t *prt_mask = MASK_OFFSET_ADDR;
  uint32_t addrOffset = pixel/32;
  uint8_t remain = pixel%32;
  uint32_t mask = (1 << remain) & 0xffffffff;
  prt_mask += addrOffset;
  *(prt_mask) |= mask;
  // printf("\n\r[MSER] Pixel [%d] Setting the bit [%d] of address [%x]",pixel, remain, prt_mask);
}

bool getMaskBinPixel(uint32_t pixel){
  uint32_t *prt_mask = MASK_OFFSET_ADDR;
  uint32_t addrOffset = pixel/32;
  uint8_t remain = pixel%32;
  uint32_t mask = (1 << remain) & 0xffffffff;
  prt_mask += addrOffset;
  uint32_t rr = *(prt_mask) & mask;
  // printf("\n\r[MSER] Pixel [%d] Reading the bit [%d] of address [%x] = %d",pixel, remain, prt_mask, rr > 0 ? 1 : 0);
  return rr > 0 ? true : false;
}

// This function implements a simple test to write and read each pixel variables
// such as LEVEL and BINARY mask in the SDRAM memory before start the algorithm
void test_memory(void){
  uint8_t level_default[] = {0x41,0x4e,0x44,0x45}; // 'ANDE'
  uint8_t neighbor_level_default[] = {0x44,0x4e,0x41,0x4e};
  #ifdef DEBUG_MSER
    printf("\n\r\t Testing memory: binary mask...");
  #endif
  // Testing binary Mask for each pixel
  for (uint32_t i = 0; i < IMG_TOTAL_PIXELS; i++) i%2 ? setMaskBinPixel(i):0;
  for (uint32_t i = 0; i < IMG_TOTAL_PIXELS; i++) assert(i%2 == getMaskBinPixel(i));
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Testing memory: pixel level \'ANDE\'...");
  #endif
  for (uint32_t i = 0; i < IMG_TOTAL_PIXELS; i++) assert(level_default[i%4] == getPixelLevel(i));
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Testing neighbor level: ");
    // printf("\n\r\t [ONLY WORK FOR 640x480 IMAGES]: ");
  #endif
  //
  //                      edge 3=1
  //           edge=640  PIXEL=641  edge 0=642
  //                    edge 1=1281
  //
  for (size_t i = 0; i < 4; i++) {
    uint8_t nl = getPixelneighborLevel(IMG_RESOLUTION_WIDTH+1, i);
    assert(neighbor_level_default[i] == nl);
    #ifdef DEBUG_MSER
      printf("\n\r\t ->Edge %d expected: %x level: %x = OK",i,neighbor_level_default[i], nl);
    #endif
  }
  #ifdef DEBUG_MSER
    printf("\n\r\t ...done");
  #endif
  // Testing level for each pixel
}
/******************** END MEMORY FUNCTIONS ********************/

void init_mem_mask(int offset_addr, int content){
  int *ptr_memory = offset_addr;
  uint32_t i;
  for (i = 0; i < IMG_TOTAL_PIXELS/32; i++) {
    *(ptr_memory) = content;
    ptr_memory++;
  }
  #ifdef DEBUG_MSER
    printf("...%x", ptr_memory);
  #endif
}

void init_mem(int offset_addr, int content){
  int *ptr_memory = offset_addr;
  uint32_t i;
  for (i = 0; i < IMG_TOTAL_PIXELS/4; i++) {
    *(ptr_memory) = content; // ANDE
    ptr_memory++;
  }
  #ifdef DEBUG_MSER
    printf("...%x", ptr_memory);
  #endif
}

void reset_mser(void){
  for (size_t i = 0; i < BD_MAX_LEVELS; i++)
    while (!isEmpty(gBoundary[i])) pop(gBoundary[i]);

  for (size_t i = 0; i < MSER_MAX_REG; i++){
    gRegions[i]->level = 255;
    gRegions[i]->area = 0;
    for (size_t j = 0; j < 5; j++) {
      gRegions[i]->mom[j] = 0;
    }
    gRegions[i]->variation = MSER_INIT_VARIA;
    gRegions[i]->parent = NULL;
    gRegions[i]->child = NULL;
    gRegions[i]->next = NULL;
    gRegions[i]->rect.top = 65535;
    gRegions[i]->rect.bottom = 0;
    gRegions[i]->rect.left = 65535;
    gRegions[i]->rect.right = 0;
    gRegions[i]->rect.draw = false;
  }
}

void mser_init(void){
  #ifdef DEBUG_MSER
    printf("\n\n\r MSER configuration started:");
    printf("\n\r\t Image resolution: %d x %d",IMG_RESOLUTION_WIDTH,IMG_RESOLUTION_HEIGHT);
    printf("\n\r\t Max. area: %d",IMG_RESOLUTION_WIDTH*IMG_RESOLUTION_HEIGHT);
    printf("\n\r\t Number of pixels: %d pixels",IMG_TOTAL_PIXELS);
    printf("\n\r Parameters:");
    printf("\n\r\t Min. area: %d pixels^2", MSER_MIN_AREA);
    printf("\n\r\t Max. area: %d pixels^2", MSER_MAX_AREA);
    printf("\n\r\t Delta: %d", MSER_DELTA);
    printf("\n\r\t Variation: %d", MSER_VARIATION);
    printf("\n\r\t Diversity: %d", MSER_DIVERSITY);
    printf("\n\r Memory:");
    printf("\n\r\t Writing \'ANDE\' to the memory image address: %x",IMG_OFFSET_ADDR);
  #endif
  init_mem(IMG_OFFSET_ADDR, 0x45444e41);
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Writing 0x00 for the binary mask at the address: %x",MASK_OFFSET_ADDR);
  #endif
  init_mem_mask(MASK_OFFSET_ADDR, 0x0);
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Creating MSER regions stack...");
  #endif

  for (size_t i = 0; i < BD_MAX_LEVELS; i++)
    gBoundary[i] = CreateStack(BD_MAX_STACK_PLEVEL);

  for (size_t i = 0; i < MSER_MAX_REG; i++)
    gRegions[i] = malloc(sizeof(regions_t));

  reset_mser();

  #ifdef DEBUG_MSER
    printf(" done");
  #endif

  test_memory();

  #ifdef DEBUG_MSER
      printf("\n\r\t End of MSER init!");
  #endif
}

void mser_find(void){
  bool done = false;
  uint8_t currentLevel;

  gCurrentPixel = 0;
  gIndexRegions = 0;
  gCounterIter = 0;
  gCurrentEdge = 0;

  // Define the first pixel
  currentLevel = getPixelLevel(gCurrentPixel);
  setMaskBinPixel(gCurrentPixel);
  gRegions[gIndexRegions++]->level = getPixelLevel(gCurrentPixel);

  uint8_t teste2 = getPixelLevel(641);
  uint8_t teste3 = getPixelLevel(642);
  uint8_t teste4 = getPixelLevel(643);
  uint8_t teste5 = getPixelLevel(644);
  // 0    1     2    3 4 5 .. 639
  // 640 641
  //uint8_t teste = getPixelneighborLevel(641, 0);
  //for (size_t i = 0; i < 4; i++) {
  //  printf("\n\rEDGE=%d PIXEL_VALUE=%d",i,getPixelneighborLevel(641, i));
  //}
  while (!done) {
    gCounterIter++;
    //+- 2000 instrucoes / ms

    // while (gCurrentEdge < 4) {
    //   edge_current++;
    // }
    done = gCounterIter > IMG_TOTAL_PIXELS ? 1 : 0;
  }
}
