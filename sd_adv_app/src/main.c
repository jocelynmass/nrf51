//
//  main.c
//  sd_adv_app
//
//  Created by Jocelyn MASSEROT on 01/29/2016.
//

#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_delay.h"
#include "softdevice_handler.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

#define APP_ADV_NAME					"SD_ADV_APP"
#define APP_ADV_INTERVAL                320        // 320 * 0.625ms = 200ms

#define GREEN_LED_PIN					12

static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
	// Catch BLE events here
}

static void advertisement_evt_cb(ble_adv_evt_t ble_adv_evt)
{
	// Catch Advertisement events here
}

static void softdevice_init(void)
{
    uint32_t err_code;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, NULL);

    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));

    err_code = sd_ble_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);
    
    // Subscribe for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    APP_ERROR_CHECK(err_code);
}

static void gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)APP_ADV_NAME,
                                          strlen(APP_ADV_NAME));
    APP_ERROR_CHECK(err_code);
}


static void advertising_init(void)
{
    uint32_t      err_code;
    ble_advdata_t advdata;
    memset(&advdata, 0, sizeof(advdata));

    // advertise the the full device name
    advdata.name_type = BLE_ADVDATA_FULL_NAME;
    // 
    advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    ble_adv_modes_config_t options = {0};

    // enable fast advertisement
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    // set advertisement interval to 200 ms, 320 * 0.625ms
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    // set advertisement timeout to infinite
    options.ble_adv_fast_timeout  = BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED;

    err_code = ble_advertising_init(&advdata, NULL, &options, advertisement_evt_cb, NULL);
    APP_ERROR_CHECK(err_code);
}

int main(void){

	softdevice_init();
	gap_params_init();
	advertising_init();
	// start fast advertisement
	ble_advertising_start(BLE_ADV_MODE_FAST);

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