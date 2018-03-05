/*
	 .d8888b.  8888888b.  8888888 .d88888b.   .d8888b.
	d88P  Y88b 888   Y88b   888  d88P   Y88b d88P  Y88b
	888    888 888    888   888  888     888 Y88b.
	888        888   d88P   888  888     888   Y888b.
	888        8888888P     888  888     888      Y88b.
	888    888 888 T88b     888  888     888        888
	Y88b  d88P 888  T88b    888  Y88b. .d88P Y88b  d88P
		Y8888P   888   T88b 8888888  Y88888P     Y8888P

 ============================================================================
	 Name        : CRIOS_ARM.c
	 Author      : Anderson Ignacio da Silva
	 Version     :
	 Copyright   : Your copyright notice
	 Description : Hello World in C, Ansi-style
 ============================================================================
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alt_clock_manager.h"
#include "alt_generalpurpose_io.h"
#include "alt_globaltmr.h"
#include "hwlib.h"
#include "socal/alt_gpio.h"
#include "socal/hps.h"
#include "socal/socal.h"
#include "hps_0.h"
#include "system_crios.h"
#include "mser.h"

int main(void) {
  setup_system();
  mser_init();

  while (1) {
    mser_find();
    printf("\n\rRUNNING...%d",gRegions[0]->level);

    delay_us(ALT_MICROSECS_IN_A_SEC/10);
	}
	return 0;
}
