CUSTOM_BLE_SRV_DIRECTORY = ../custom/ble_service


# BLE services
ifeq ($(USE_BLE_LED), y)
INCLUDES  += $(CUSTOM_BLE_SRV_DIRECTORY)/ble_led
SRC 	  += $(CUSTOM_BLE_SRV_DIRECTORY)/ble_led/ble_led.c
CPFLAGS   += -DUSE_BLE_LED
endif
