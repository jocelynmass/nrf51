//
//  main.c
//  sd_led_app
//
//  Created by Jocelyn MASSEROT on 01/29/2016.
//

#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_delay.h"
#include "softdevice_handler.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_led.h"

#define APP_ADV_NAME					"SD_LED_APP"
#define APP_ADV_CUSTOM_DATA			    "hello world!"
#define APP_ADV_INTERVAL                320        // 320 * 0.625ms = 200ms

#define RED_LED_PIN                     16
#define BLUE_LED_PIN					15
#define GREEN_LED_PIN                   12

static ble_led_t _led;

static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
	// Catch BLE events here
    switch (p_ble_evt->header.evt_id)
    {            
        case BLE_GAP_EVT_DISCONNECTED:
            // Manually restart advertisement when a disconnection occured
            ble_advertising_start(BLE_ADV_MODE_FAST);
            break;
        default:
            break;
    }

    ble_led_on_ble_evt(&_led, p_ble_evt);
}

static void advertisement_evt_cb(ble_adv_evt_t ble_adv_evt)
{
	// Catch Advertisement events here
}

#define LED_OFF          0
#define LED_SET_RED      1
#define LED_SET_GREEN    2
#define LED_SET_BLUE     3


static void led_set_cb(uint8_t value)
{
    NRF_GPIO->OUTSET = (1UL << RED_LED_PIN);
    NRF_GPIO->OUTSET = (1UL << BLUE_LED_PIN);
    NRF_GPIO->OUTSET = (1UL << 12);

        
    switch(value)
    {
        case LED_OFF: 
            NRF_GPIO->OUTSET = (1UL << RED_LED_PIN);
            NRF_GPIO->OUTSET = (1UL << BLUE_LED_PIN);
            NRF_GPIO->OUTSET = (1UL << GREEN_LED_PIN);
            break;
        
        case LED_SET_RED: 
            NRF_GPIO->OUTCLR = (1UL << RED_LED_PIN);
            break;
        
        case LED_SET_GREEN: 
            NRF_GPIO->OUTCLR = (1UL << GREEN_LED_PIN);
            break;
        
        case LED_SET_BLUE: 
            NRF_GPIO->OUTCLR = (1UL << BLUE_LED_PIN);
            break;
    }
}

static void softdevice_init(void)
{
    uint32_t err_code;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_SYNTH_250_PPM, NULL);

    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));

    // Tell the Central that Services on Peripheral changed. Without this line, 
    // the Central won't update the services list of our device.
    ble_enable_params.gatts_enable_params.service_changed = 1;
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
    ble_gap_conn_params_t   gap_conn_params;

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
    ble_advdata_t scanrsp;
    ble_advdata_manuf_data_t manfdata;
    ble_uuid_t adv_uuids[] = {{BLE_LED_SERVICE_UUID, _led.uuid_type}};

    memset(&advdata, 0, sizeof(advdata));

    // advertise the the full device name
    advdata.name_type = BLE_ADVDATA_FULL_NAME;
    // LE General Discoverable Mode, BR/EDR not supported.
    advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    // Set the manufacturer specific data below
    memset(&manfdata, 0, sizeof(manfdata));

    manfdata.company_identifier = 0x1234;
    manfdata.data.size = strlen(APP_ADV_CUSTOM_DATA);
    manfdata.data.p_data = (uint8_t *)APP_ADV_CUSTOM_DATA;

    advdata.p_manuf_specific_data = &manfdata;

    ble_adv_modes_config_t options = {0};

    // enable fast advertisement
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    // set advertisement interval to 200 ms, 320 * 0.625ms
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    // set advertisement timeout to infinite
    options.ble_adv_fast_timeout  = BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED;

    memset(&scanrsp, 0, sizeof(scanrsp));

    // number of UUIDs
    scanrsp.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
    // UUID
    scanrsp.uuids_complete.p_uuids  = adv_uuids;

    err_code = ble_advertising_init(&advdata, &scanrsp, &options, advertisement_evt_cb, NULL);
    APP_ERROR_CHECK(err_code);
}

static void led_init(void)
{
    // setup green led gpio in output mode
    NRF_GPIO->PIN_CNF[RED_LED_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                            | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
    NRF_GPIO->PIN_CNF[BLUE_LED_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                            | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
    NRF_GPIO->PIN_CNF[GREEN_LED_PIN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                            | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);

    NRF_GPIO->OUTSET |= (1UL << RED_LED_PIN);
    NRF_GPIO->OUTSET |= (1UL << BLUE_LED_PIN);
    NRF_GPIO->OUTSET |= (1UL << GREEN_LED_PIN);
}

int main(void){

	softdevice_init();
	gap_params_init();

    _led.set_led_value = led_set_cb;
    ble_led_init(&_led);
    led_init();
    
	advertising_init();
	// start fast advertisement
	ble_advertising_start(BLE_ADV_MODE_FAST);


	
	do{
		// set to 1 led gpio (bit 12 corresponding to pin 12)
	//	NRF_GPIO->OUTSET = (1UL << GREEN_LED_PIN);
		// wait 300ms
		nrf_delay_ms(300);
		// set to 0 led gpio (bit 12 corresponding to pin 12)
	//	NRF_GPIO->OUTCLR = (1UL << GREEN_LED_PIN);
		// wait 300ms
		nrf_delay_ms(300);
	}while(1); //infinite loop

    return 0;
}