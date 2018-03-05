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
#include "alt_clock_manager.h"
#include "alt_generalpurpose_io.h"
#include "alt_globaltmr.h"
#include "hwlib.h"
#include "socal/alt_gpio.h"
#include "system_crios.h"
#include "mser.h"
#include "hps_0.h"

*fpga_leds = ALT_LWFPGASLVS_ADDR + LED_PIO_BASE; // Using PIO LEDS through FPGA Lightweight AXI
*fpga_dip = ALT_LWFPGASLVS_ADDR + DIPSW_PIO_BASE; // Using PIO LEDS through FPGA Lightweight AXI

void setup_fpga_leds() {
    alt_write_word(fpga_leds, 0x1);
}

void setup_hps_gpio() {
  uint32_t hps_gpio_config_len = 1;
  ALT_GPIO_CONFIG_RECORD_t hps_gpio_config[] = {
    {HPS_LED_IDX, ALT_GPIO_PIN_OUTPUT, 0, 0, ALT_GPIO_PIN_DEBOUNCE, ALT_GPIO_PIN_DATAZERO}
  };
  assert(ALT_E_SUCCESS == alt_gpio_init());
  assert(ALT_E_SUCCESS == alt_gpio_group_config(hps_gpio_config, hps_gpio_config_len));
}

void setup_hps_timer() {
    assert(ALT_E_SUCCESS == alt_globaltmr_init());
}

void delay_us(uint32_t us) {
    uint64_t start_time = alt_globaltmr_get64();
    uint32_t timer_prescaler = alt_globaltmr_prescaler_get() + 1;
    uint64_t end_time;
    alt_freq_t timer_clock;

    assert(ALT_E_SUCCESS == alt_clk_freq_get(ALT_CLK_MPU_PERIPH, &timer_clock));
    end_time = start_time + us * ((timer_clock / timer_prescaler) / ALT_MICROSECS_IN_A_SEC);

    // polling wait
    while(alt_globaltmr_get64() < end_time);
}

ALT_STATUS_CODE setup_system(void){
  printf("\n\r ####### CRIOS Project #######");
  setup_hps_timer();
  setup_hps_gpio();
  setup_fpga_leds();

  return ALT_E_SUCCESS;
}
