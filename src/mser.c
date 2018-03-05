#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
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
  uint32_t *ptr_level = pixel+IMG_OFFSET_ADDR;
  return *(ptr_level);
}

void setMaskBinPixel(uint32_t pixel){
  uint32_t *prt_mask = MASK_OFFSET_ADDR;
  uint16_t integerPart = pixel/8;
  uint8_t remain = (pixel%8)-1;
  uint8_t mask = (1 << (uint8_t)remain) & 0xff;
  prt_mask += integerPart;
  *(prt_mask) |= mask;
  printf("\n\rEscrevendo no endereco: %x %d o valor %d",prt_mask,prt_mask,mask);
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
    printf("\n\r\t Total pixel counter: %d",IMG_TOTAL_PIXELS);
    printf("\n\r Parameters:");
    printf("\n\r\t Min. area: %d pixels^2", MSER_MIN_AREA);
    printf("\n\r\t Max. area: %d pixels^2", MSER_MAX_AREA);
    printf("\n\r\t Delta: %d", MSER_DELTA);
    printf("\n\r\t Variation: %d", MSER_VARIATION);
    printf("\n\r\t Diversity: %d", MSER_DIVERSITY);
    printf("\n\r\t Writing \'ANDE\' to the memory image address: %x",IMG_OFFSET_ADDR);
  #endif
  init_mem(IMG_OFFSET_ADDR, 0x45444e41);
  #ifdef DEBUG_MSER
    printf(" done");
    printf("\n\r\t Creating a binary mask at the address: %x",MASK_OFFSET_ADDR);
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

  printf(" done");
  printf("\n\r\t End of MSER init!");
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

  setMaskBinPixel(2);
  setMaskBinPixel(450);
  setMaskBinPixel(307199);
  // while (!done) {
  //   gCounterIter++;
  //
  //   while (gCurrentEdge < 4) {
  //     edge_current++;
  //   }
  //   done = 1;
  // }
}
