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
uint16_t stackRegions[MSER_MAX_REG];
uint16_t gIndexRegions = 0;
uint16_t gIndexStack = 0;
uint32_t gCounterIter = 0;

/******************** START REGION FUNCTIONS ********************/
void processStack(uint8_t newPixelGreyLevel){
  uint16_t indexTop,
           indexNewTop;
  uint8_t newTopLevel;

  while (newPixelGreyLevel > gRegions[stackRegions[gIndexStack]]->level) {
    indexTop = stackRegions[gIndexStack];
    gIndexStack--;
    indexNewTop = stackRegions[gIndexStack];
    newTopLevel = gRegions[indexNewTop]->level;
    if (newPixelGreyLevel < newTopLevel) {
      gIndexRegions++;
      gIndexStack++;
      gRegions[gIndexRegions]->level = newPixelGreyLevel;
      gRegions[gIndexRegions]->area = gRegions[indexTop]->area;
      for (size_t i = 0; i < 5; i++) {
        gRegions[gIndexRegions]->mom[i] = gRegions[indexTop]->mom[i];
      }
      gRegions[gIndexRegions]->stable = 0;
      gRegions[gIndexRegions]->parent = NULL;
      gRegions[indexTop]->next = gRegions[gIndexRegions]->child;
      gRegions[indexTop]->parent = gRegions[gIndexRegions];
      gRegions[gIndexRegions]->child = gRegions[indexTop];
      gRegions[gIndexRegions]->next = NULL;

      gRegions[gIndexRegions]->rect.top = (gRegions[indexTop]->rect.top < gRegions[gIndexRegions]->rect.top ? gRegions[indexTop]->rect.top : gRegions[gIndexRegions]->rect.top);
      gRegions[gIndexRegions]->rect.bottom = (gRegions[indexTop]->rect.bottom > gRegions[gIndexRegions]->rect.bottom ? gRegions[indexTop]->rect.bottom : gRegions[gIndexRegions]->rect.bottom);
      gRegions[gIndexRegions]->rect.left = (gRegions[indexTop]->rect.left < gRegions[gIndexRegions]->rect.left ? gRegions[indexTop]->rect.left : gRegions[gIndexRegions]->rect.left);
      gRegions[gIndexRegions]->rect.right = (gRegions[indexTop]->rect.right > gRegions[gIndexRegions]->rect.right ? gRegions[indexTop]->rect.right : gRegions[gIndexRegions]->rect.right);

      stackRegions[gIndexStack] = gIndexRegions;
      break;
    }

    gRegions[indexNewTop]->area += gRegions[indexTop]->area;
    for (size_t i = 0; i < 5; i++) {
      gRegions[indexNewTop]->mom[i] += gRegions[indexTop]->mom[i];
    }
    gRegions[indexTop]->parent = gRegions[indexNewTop];
    gRegions[indexTop]->next = gRegions[indexNewTop]->child;
    gRegions[indexNewTop]->child = gRegions[indexTop];

    gRegions[indexNewTop]->rect.top = (gRegions[indexTop]->rect.top < gRegions[indexNewTop]->rect.top ? gRegions[indexTop]->rect.top : gRegions[indexNewTop]->rect.top);
    gRegions[indexNewTop]->rect.bottom = (gRegions[indexTop]->rect.bottom > gRegions[indexNewTop]->rect.bottom ? gRegions[indexTop]->rect.bottom : gRegions[indexNewTop]->rect.bottom);
    gRegions[indexNewTop]->rect.left = (gRegions[indexTop]->rect.left < gRegions[indexNewTop]->rect.left ? gRegions[indexTop]->rect.left : gRegions[indexNewTop]->rect.left);
    gRegions[indexNewTop]->rect.right = (gRegions[indexTop]->rect.right > gRegions[indexNewTop]->rect.right ? gRegions[indexTop]->rect.right : gRegions[indexNewTop]->rect.right);

    stackRegions[gIndexStack] = indexNewTop;
  }
}

void accumulateRegion(uint16_t x, uint16_t y){
    uint16_t topRegion = stackRegions[gIndexStack];
    gRegions[topRegion]->area += 1;
    gRegions[topRegion]->mom[0] += x;
    gRegions[topRegion]->mom[1] += y;
    gRegions[topRegion]->mom[2] += (x*x);
    gRegions[topRegion]->mom[3] += (x*y);
    gRegions[topRegion]->mom[4] += (y*y);
    gRegions[topRegion]->rect.top = (gRegions[topRegion]->rect.top < y ? gRegions[topRegion]->rect.top : y);
    gRegions[topRegion]->rect.bottom = (gRegions[topRegion]->rect.bottom > (y+1) ? gRegions[topRegion]->rect.bottom : y+1);
    gRegions[topRegion]->rect.left = (gRegions[topRegion]->rect.left < x ? gRegions[topRegion]->rect.left : x);
    gRegions[topRegion]->rect.right = (gRegions[topRegion]->rect.right > (x+1) ? gRegions[topRegion]->rect.right : x+1);
}

/******************** END REGION FUNCTIONS ********************/

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
void setPixelLevel(uint16_t x, uint16_t y, uint8_t value){
  uint32_t pixel_linear = x*y;
  uint32_t *ptr_level = TEST_OFFSET_ADDR;
  uint32_t addrOffset = pixel_linear/4;
  ptr_level += addrOffset;
  uint8_t remain = pixel_linear%4;
  uint32_t mask = ((0xff & value) << remain*8);
  *(ptr_level) |= mask;
}

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
  uint8_t nLevel;
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

  nLevel = getPixelLevel(neighborPixel);
  return nLevel;
}

uint32_t getPixelneighbor(uint32_t pixel, uint8_t edge){
  uint32_t neighborPixel;
  uint16_t x = pixel%IMG_RESOLUTION_WIDTH;
  uint16_t y = pixel/IMG_RESOLUTION_WIDTH;
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

  return neighborPixel;
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
void testMem(void){
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

void initMemMask(int offset_addr, int content){
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

void initMemImage(int offset_addr, int content){
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

void resetMser(void){
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

  int *ptr_memory = MASK_OFFSET_ADDR;
  uint32_t i;
  for (i = 0; i < IMG_TOTAL_PIXELS/32; i++) {
    *(ptr_memory) = 0x00000000;
    ptr_memory++;
  }
}

void mserInit(void){
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
  initMemImage(IMG_OFFSET_ADDR, 0x45444e41);
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Writing 0x00 for the binary mask at the address: %x",MASK_OFFSET_ADDR);
  #endif
  initMemMask(MASK_OFFSET_ADDR, 0x0);
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Creating MSER regions stack...");
  #endif

  for (size_t i = 0; i < BD_MAX_LEVELS; i++)
    gBoundary[i] = CreateStack(BD_MAX_STACK_PLEVEL);

  for (size_t i = 0; i < MSER_MAX_REG; i++)
    gRegions[i] = malloc(sizeof(regions_t));

  // resetMser();

  #ifdef DEBUG_MSER
    printf(" done");
  #endif

  testMem();

  #ifdef DEBUG_MSER
    printf("\n\r\t Writing 0x00 again for the binary mask at the address: %x",MASK_OFFSET_ADDR);
    initMemMask(MASK_OFFSET_ADDR, 0x0);
  #endif
  #ifdef DEBUG_MSER
    printf("\n\r\t End of MSER init!");
  #endif
}

void drawTestImage(void){
  for (uint16_t l = 0; l < IMG_RESOLUTION_HEIGHT; l++) {
    for (uint16_t c = 0; c < IMG_RESOLUTION_WIDTH; c++) {
      if (c > IMG_RESOLUTION_WIDTH*0.40 && \
          c < IMG_RESOLUTION_WIDTH*0.80 && \
          l > IMG_RESOLUTION_HEIGHT*0.40 && \
          l < IMG_RESOLUTION_HEIGHT*0.80){
        setPixelLevel(l,c,15);
      }
      else{
        setPixelLevel(l,c,255);
      }
    }
  }
}

void mserFindRegions(void){
  bool done;
  uint32_t currentPixel,
           dataToStore,
           dataToRetrieve;
  uint16_t priority;
  uint8_t currentLevel,
          currentEdge,
          neighborPixel,
          neighborLevel,
          newPixelGreyLevel;

  resetMser();

  priority = 256;
  currentPixel = 0;
  currentEdge = 0;
  currentLevel = getPixelLevel(currentPixel);
  setMaskBinPixel(currentPixel);
  gIndexRegions = 0;
  gIndexStack = 0;

  // Insert into the tree the most 'bright' pixel that equivalent to 256
  gRegions[gIndexRegions]->level = 256; // This level do not exist
  stackRegions[gIndexStack] = gIndexRegions;

  // Define the first pixel
  gIndexRegions++;
  gIndexStack++;
  gRegions[gIndexRegions]->level = currentLevel;
  stackRegions[gIndexStack] = gIndexRegions;

  gCounterIter = 0;
  done = false;
  while (!done) {
    gCounterIter++;
    //+- 2000 instrucoes / ms
    while (currentEdge < 4) {
      neighborPixel = getPixelneighbor(currentPixel, currentEdge);
      if (getMaskBinPixel(neighborPixel) == false) {
        neighborLevel = getPixelLevel(neighborPixel);
        setMaskBinPixel(neighborPixel);
        if (neighborLevel < currentLevel) {
          dataToStore = (currentPixel << 4) | (currentEdge+1);
          push(gBoundary[currentLevel],dataToStore);
          if (currentLevel < priority) {
            priority = currentLevel;
          }
          currentPixel = neighborPixel;
          currentEdge = 0;
          currentLevel = neighborLevel;

          gIndexRegions++;
          gIndexStack++;
          gRegions[gIndexRegions]->level = currentLevel;
          stackRegions[gIndexStack] = gIndexRegions;
          continue;
        }

        dataToStore = (neighborPixel << 4) | 0;
        push(gBoundary[neighborLevel],dataToStore);
        if (neighborLevel < priority){
          priority = neighborLevel;
        }
      }
      currentEdge = currentEdge + 1;
    }
    uint16_t x = currentPixel%IMG_RESOLUTION_WIDTH;
    uint16_t y = currentPixel/IMG_RESOLUTION_WIDTH;
    accumulateRegion(x,y);
    if (priority == 256) {
      for (uint8_t i = 0; i < 256; i++){
        printf("\n\rLEVEL ->%d",i);
        printStack(gBoundary[i]);
      }
      newPixelGreyLevel = (uint8_t)256;
      processStack(newPixelGreyLevel);
      done = 1;
      break;
    }
    dataToRetrieve = pop(gBoundary[priority]);
    currentPixel = (dataToRetrieve >> 4) & 0xffffffff;
    currentEdge = (dataToRetrieve) & 0x0f;
    while (isEmpty(gBoundary[priority]) && (priority < 256)) {
      priority += 1;
    }
    newPixelGreyLevel =  getPixelLevel(currentPixel);
    if (newPixelGreyLevel != currentLevel) {
      processStack(newPixelGreyLevel);
      currentLevel = newPixelGreyLevel;
    }
  }
}
