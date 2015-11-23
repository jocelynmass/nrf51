//
//  main.c
//  led_blinking
//
//  Created by Jocelyn MASSEROT on 11/08/2015.
//  Copyright (c) 2015 Jocelyn MASSEROT. All rights reserved.
//
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_delay.h"

#define GREEN_LED_PIN	12

int main(void){
	// setup led gpio in output mode
	NRF_GPIO->PIN_CNF[GREEN_LED_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                            | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);

	do{
		// set to 1 led gpio (bit 12 corresponding to pin 12)
		NRF_GPIO->OUTSET = (1UL << GREEN_LED_PIN);
		// wait 300ms
		nrf_delay_ms(300);
		// set to 0 led gpio (bit 12 corresponding to pin 12)
		NRF_GPIO->OUTCLR = (1UL << GREEN_LED_PIN);
		// wait 300ms
		nrf_delay_ms(300);
	}while(1); //infinite loop

    return 0;
}