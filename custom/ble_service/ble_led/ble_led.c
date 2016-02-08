//
//  ble_led.c
// 	BLE service to exchange generic data with a Central
//
//  Created by Jocelyn MASSEROT on 01/31/2016.
//
#include <stddef.h>
#include <string.h>
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "ble_led.h"
#include "nrf_error.h"
#include "ble_types.h"
#include "ble_gatts.h"
#include "ble_srv_common.h"
#include <ble.h>


void ble_led_on_ble_evt(ble_led_t * p_led, ble_evt_t * p_ble_evt)
{
    if ((p_led == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    if (p_led->set_led_value != NULL)
    {
        switch (p_ble_evt->header.evt_id)
        {
            case BLE_GATTS_EVT_WRITE:

                if (p_ble_evt->evt.gatts_evt.params.write.handle == p_led->led_status_handles.value_handle)
                {            
                    p_led->set_led_value(p_ble_evt->evt.gatts_evt.params.write.data[0]);  
                }
                break;

            default:
                // No implementation needed.
                break;
        }
    }
}

// This function allows to add a Characteristic in our Service
static uint32_t ble_led_sta_char_add(ble_led_t * const p_led)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t initial_led_status = 0;

    memset(&char_md, 0, sizeof(char_md));

    // set the Characteristic type to Write Without Response
    // it means Central won't except any acknowledgment from the Peripheral
    char_md.char_props.write_wo_resp = 1;

    // Here we set the Characteristic UUID
    char_uuid.type = p_led->uuid_type;
    char_uuid.uuid = BLE_LED_STA_CHAR_UUID;

    memset(&attr_md, 0, sizeof(attr_md));

    // add write permission
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    // Attribute configuration, the data is stored in stack memory space
    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    // setup Attribute default value
    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);
    attr_char_value.p_value   = &initial_led_status;

    return sd_ble_gatts_characteristic_add(p_led->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_led->led_status_handles);
}

uint32_t ble_led_init(ble_led_t * p_led)
{
	ble_uuid_t service_uuid;
    uint32_t   ret;

	// check if parameters are correctly set up
    if (p_led == NULL)
    {
        return NRF_ERROR_NULL;
    }

    p_led->conn_handle = BLE_CONN_HANDLE_INVALID;

    // create a custom base BLE uuid for our service (ble_led_service in ascii)
    const ble_uuid128_t base_uuid128 =
    {
        {
            0x62, 0x6c, 0x65, 0x5f, 0x6c, 0x65, 0x64, 0x5f,
            0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x00
        }
    };

    // setup LED service uuid
    service_uuid.uuid = BLE_LED_SERVICE_UUID;

    // add our custom services in BLE stack's table 
    ret = sd_ble_uuid_vs_add(&base_uuid128, &(service_uuid.type));
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    // sd led service declaration to the local server ATT table
    ret = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &(p_led->service_handle));
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    p_led->uuid_type = service_uuid.type;

    // add LED status Characteristics
    ret = ble_led_sta_char_add(p_led);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    return NRF_SUCCESS;
}


