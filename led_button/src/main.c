//
//  main.c
//  led_button
//
//  Created by AntoineM* on 02/21/2016.
//  Copyright (c) 2016 AntoineM*. All rights reserved.
//
//  contact infos : ameisso.fr


#include "nrf51.h"
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

#define GREEN_LED_PIN	12
#define BUTTON_PIN 11

//this function will be called when the BUTTON_PIN is toggled
void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(GREEN_LED_PIN);
}

static void gpio_init(void)
{
    ret_code_t err_code;
    
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);
    
    err_code = nrf_drv_gpiote_out_init(GREEN_LED_PIN, &out_config);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true); //could be replaced by GPIOTE_CONFIG_IN_SENSE_HITOLO or GPIOTE_CONFIG_IN_SENSE_LOTOHI
    in_config.pull = NRF_GPIO_PIN_PULLUP;                                       //Adding an internal pullup to that pin
    
    err_code = nrf_drv_gpiote_in_init(BUTTON_PIN, &in_config, in_pin_handler);  //define the function called on event
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_gpiote_in_event_enable(BUTTON_PIN, true);
}

int main(void)
{
    gpio_init();
    while (true)
    {
        // Do nothing.
    }
    
}