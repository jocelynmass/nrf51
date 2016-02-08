//
//  ble_led.h
// 	BLE service to exchange generic data with a Central
//
//  Created by Jocelyn MASSEROT on 01/31/2016.
//

#ifndef __BLE_LED_H__
#define __BLE_LED_H__

#include <stdint.h>
#include <ble.h>
#include "ble_gatts.h"

#define BLE_LED_SERVICE_UUID                 0x3560     /**< The UUID of the LED Service. */
#define BLE_LED_STA_CHAR_UUID                0x3561     /**< The UUID of the LED status Characteristic. */
 

typedef struct 
{
    uint16_t     conn_handle;        /**< Handle of the current connection (as provided by the S110 SoftDevice). This will be BLE_CONN_HANDLE_INVALID when not in a connection. */
    uint16_t     revision;           /**< Handle of LED Service (as provided by the S110 SoftDevice). */
    uint16_t     service_handle;     /**< Handle of LED Service (as provided by the S110 SoftDevice). */
    uint8_t      uuid_type;          /**< UUID type assigned for LED Service by the S110 SoftDevice. */
    ble_gatts_char_handles_t     led_status_handles;  /**< Handles related to the LED Packet characteristic. */
    void (*set_led_value) (uint8_t led_value);
}ble_led_t;

void ble_led_on_ble_evt(ble_led_t * p_led, ble_evt_t * p_ble_evt);

#endif //__BLE_LED_H__