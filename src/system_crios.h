#ifndef _SYSTEM_CRIOS_H_
#define _SYSTEM_CRIOS_H_

#define DEBUG_ENABLE 1
#define HPS_LED_IDX        (ALT_GPIO_1BIT_53)                      // GPIO53
#define HPS_LED_PORT       (alt_gpio_bit_to_pid(HPS_LED_IDX))      // ALT_GPIO_PORTB
#define HPS_LED_PORT_BIT   (alt_gpio_bit_to_port_pin(HPS_LED_IDX)) // 24 (from GPIO1[24])
#define HPS_LED_MASK       (1 << HPS_LED_PORT_BIT)
#define ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))

extern int *fpga_leds; // Using PIO LEDS through FPGA Lightweight AXI
extern int *fpga_dip; // Using PIO LEDS through FPGA Lightweight AXI

extern ALT_STATUS_CODE setup_system(void);
extern void delay_us(uint32_t us);

#endif /* _SYSTEM_CRIOS_H_ */
