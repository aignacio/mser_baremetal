#ifndef _MSER_H_
#define _MSER_H_

#define DEBUG_MSER
#define IMG_RESOLUTION_WIDTH  1280
#define IMG_RESOLUTION_HEIGHT 720
#define IMG_TOTAL_PIXELS      (IMG_RESOLUTION_WIDTH*IMG_RESOLUTION_HEIGHT)
#define IMG_OFFSET_ADDR       0xC00000
#define MASK_OFFSET_ADDR      0xE00000
#define TEST_OFFSET_ADDR      0xB00000

// MSER Parameters
#define MSER_MIN_AREA         0.00001*IMG_TOTAL_PIXELS
#define MSER_MAX_AREA         0.25*IMG_TOTAL_PIXELS
#define MSER_DELTA            2
#define MSER_VARIATION        0.5
#define MSER_DIVERSITY        0.33
#define MSER_MAX_REG          200000 // Max. regions to store
#define MSER_INIT_VARIA       999999 // Initial variation for MSER

// Boundary pixels
#define BD_MAX_STACK_PLEVEL   1000000 // Max. items per gray level in the stack struct
#define BD_MAX_LEVELS         256 // Max levels that's capable to store in stack

// Main Structure of rectangle regions
typedef struct rect {
  uint16_t top;
  uint16_t bottom;
  uint16_t left;
  uint16_t right;
  bool draw;
} rect_t;

// Main Structure of regions
typedef struct regions {
  uint16_t level; // We need to use 256, that's why int16 not int8
  uint32_t area;
  uint64_t mom[5];
  float variation;
  bool stable;
  rect_t rect;
  struct regions *parent;
  struct regions *child;
  struct regions *next;
} regions_t;

// Main Structure of boundary pixels that'll store the
// neighbors grey levels 0-256;
struct bp_stack {
  int top; // We need to assume -1, that's why used int type
  uint32_t capacity;
  uint32_t *pixels;
};

// Globals
extern struct bp_stack* gBoundary[BD_MAX_LEVELS];
extern regions_t* gRegions[MSER_MAX_REG];
extern uint32_t gCounterIter;

// Prototypes
extern struct bp_stack* CreateStack(uint32_t size);
extern bool isFull(struct bp_stack *stack);
extern bool isEmpty(struct bp_stack *stack);
extern void push(struct bp_stack* stack, uint32_t item);
extern uint32_t pop(struct bp_stack* stack);
extern uint32_t pop(struct bp_stack* stack);
extern void resetMser(void);
extern void mserFindRegions(void);
extern void mserInit(void);
extern uint8_t getPixelLevel(uint32_t pixel);
extern void drawTestImage(void);
extern uint8_t getPixelneighborLevel(uint32_t pixel, uint8_t edge);
extern void setMaskBinPixel(uint32_t pixel);
extern bool getMaskBinPixel(uint32_t pixel);
extern void testMem(void);
extern void initMemMask(int offset_addr, int content);
extern void initMemImage(int offset_addr, int content);
extern void drawTestImage(void);
extern void setPixelLevel(uint16_t x, uint16_t y, uint8_t value);

#endif /* _MSER_H_ */
