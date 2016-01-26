SDK_DIRECTORY = ../sdk/nRF51_SDK_9.0.0_2e23562/components

# System
INCLUDES  += $(SDK_DIRECTORY)/toolchain
INCLUDES  += $(SDK_DIRECTORY)/toolchain/arm
INCLUDES  += $(SDK_DIRECTORY)/toolchain/gcc
INCLUDES  += $(SDK_DIRECTORY)/device

SRC       += $(SDK_DIRECTORY)/toolchain/system_nrf51.c

# Drivers
ifeq ($(USE_DRV_BLE_FLASH), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/ble_flash
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/ble_flash -name *.c)
CPFLAGS   += -DUSE_DRV_BLE_FLASH
endif
ifeq ($(USE_DRV_CLK), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/clock
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/clock -name *.c)
CPFLAGS   += -DUSE_DRV_CLK
endif
ifeq ($(USE_DRV_GPIOTE), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/gpiote
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/gpiote -name *.c)
CPFLAGS   += -DUSE_DRV_GPIOTE
endif
ifeq ($(USE_DRV_LPCOMP), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/lpcomp
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/lpcomp -name *.c)
CPFLAGS   += -DUSE_DRV_LPCOMP
endif
ifeq ($(USE_DRV_NOSD), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/nrf_soc_nosd
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/nrf_soc_nosd -name *.c)
CPFLAGS   += -DUSE_DRV_NOSD
endif
ifeq ($(USE_DRV_PPI), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/ppi
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/ppi -name *.c)
CPFLAGS   += -DUSE_DRV_PPI
endif
ifeq ($(USE_DRV_PSTORAGE), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/pstorage
SRC 	  += $(SDK_DIRECTORY)/drivers_nrf/pstorage/pstorage.c
CPFLAGS   += -DUSE_DRV_PSTORAGE
endif
ifeq ($(USE_DRV_QDEC), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/qdec
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/qdec -name *.c)
CPFLAGS   += -DUSE_DRV_QDEC
endif
ifeq ($(USE_DRV_RADIO_CFG), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/radio_config
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/radio_config -name *.c)
CPFLAGS   += -DUSE_DRV_RADIO_CFG
endif
ifeq ($(USE_DRV_RNG), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/rng
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/rng -name *.c)
CPFLAGS   += -DUSE_DRV_RNG
endif
ifeq ($(USE_DRV_RTC), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/rtc
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/rtc -name *.c)
CPFLAGS   += -DUSE_DRV_RTC
endif
ifeq ($(USE_DRV_SDIO), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/sdio
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/sdio -name *.c)
CPFLAGS   += -DUSE_DRV_SDIO
endif
ifeq ($(USE_DRV_SPI_SLV), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/spi_slave
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/spi_slave -name *.c)
CPFLAGS   += -DUSE_DRV_SPI_SLV
endif
ifeq ($(USE_DRV_SPI_MSTR), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/spi_master
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/spi_master -name *.c)
CPFLAGS   += -DUSE_DRV_SPI_MSTR
endif
ifeq ($(USE_DRV_SWI), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/swi
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/swi -name *.c)
CPFLAGS   += -DUSE_DRV_SWI
endif
ifeq ($(USE_DRV_TIMER), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/timer
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/timer -name *.c)
CPFLAGS   += -DUSE_DRV_TIMER
endif
ifeq ($(USE_DRV_TWI_MSTR), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/twi_master
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/twi_master -name *.c)
CPFLAGS   += -DUSE_DRV_TWI_MSTR
endif
ifeq ($(USE_DRV_UART), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/uart
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/uart -name *.c)
CPFLAGS   += -DUSE_DRV_UART
endif
ifeq ($(USE_DRV_WDT), y)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/wdt
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/wdt -name *.c)
CPFLAGS   += -DUSE_DRV_WDT
endif

INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/hal
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/hal -name *.c)
INCLUDES  += $(SDK_DIRECTORY)/drivers_nrf/common
SRC 	  += $(shell find $(SDK_DIRECTORY)/drivers_nrf/common -name *.c)


# Libraries
ifeq ($(USE_LIB_DFU), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/bootloader_dfu
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/bootloader_dfu -name *.c)
CPFLAGS   += -DUSE_LIB_DFU
endif
ifeq ($(USE_LIB_BUTTON), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/button
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/button -name *.c)
CPFLAGS   += -DUSE_LIB_BUTTON
endif
ifeq ($(USE_LIB_CONSOLE), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/console
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/console -name *.c)
CPFLAGS   += -DUSE_LIB_CONSOLE
endif
ifeq ($(USE_LIB_CRC16), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/crc16
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/crc16 -name *.c)
CPFLAGS   += -DUSE_LIB_CRC16
endif
ifeq ($(USE_LIB_FIFO), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/fifo
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/fifo -name *.c)
CPFLAGS   += -DUSE_LIB_FIFO
endif
ifeq ($(USE_LIB_GPIOTE), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/gpiote
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/gpiote -name *.c)
CPFLAGS   += -DUSE_LIB_GPIOTE
endif
ifeq ($(USE_LIB_HCI), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/hci
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/hci -name *.c)
CPFLAGS   += -DUSE_LIB_HCI
endif
ifeq ($(USE_LIB_IC_INFO), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/ic_info
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/ic_info -name *.c)
CPFLAGS   += -DUSE_LIB_IC_INFO
endif
ifeq ($(USE_LIB_MEM_MNG), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/mem_manager
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/mem_manager -name *.c)
CPFLAGS   += -DUSE_LIB_MEM_MNG
endif
ifeq ($(USE_LIB_PWM), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/pwm
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/pwm -name *.c)
CPFLAGS   += -DUSE_LIB_PWM
endif
ifeq ($(USE_LIB_SCHEDULER), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/scheduler
SRC 	  += $(SDK_DIRECTORY)/libraries/scheduler/app_scheduler.c
CPFLAGS   += -DUSE_LIB_SCHEDULER
endif
ifeq ($(USE_LIB_SENSORSIM), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/sensorsim
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/sensorsim -name *.c)
CPFLAGS   += -DUSE_LIB_SENSORSIM
endif
ifeq ($(USE_LIB_SH256), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/sha256
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/sha256 -name *.c)
CPFLAGS   += -DUSE_LIB_SH256
endif
ifeq ($(USE_LIB_SIMPLE_TIMER), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/simple_timer
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/simple_timer -name *.c)
CPFLAGS   += -DUSE_LIB_SIMPLE_TIMER
endif
ifeq ($(USE_LIB_TIMER), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/timer
SRC 	  += $(SDK_DIRECTORY)/libraries/timer/app_timer.c
CPFLAGS   += -DUSE_LIB_TIMER
endif
ifeq ($(USE_LIB_TRACE), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/trace
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/trace -name *.c)
CPFLAGS   += -DUSE_LIB_TRACE
endif
ifeq ($(USE_LIB_UART), y)
INCLUDES  += $(SDK_DIRECTORY)/libraries/uart
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/uart -name *.c)
CPFLAGS   += -DUSE_LIB_UART
endif

ifeq ($(USE_BLE_ADV), y)
INCLUDES  += $(SDK_DIRECTORY)/ble/ble_advertising
SRC 	  += $(shell find $(SDK_DIRECTORY)/ble/ble_advertising -name *.c)
CPFLAGS   += -DUSE_BLE_ADV
endif

ifeq ($(USE_BLE_COMMON), y)
INCLUDES  += $(SDK_DIRECTORY)/ble/common
SRC 	  += $(shell find $(SDK_DIRECTORY)/ble/common -name *.c)
CPFLAGS   += -DUSE_BLE_COMMON
endif

INCLUDES  += $(SDK_DIRECTORY)/libraries/util
SRC 	  += $(shell find $(SDK_DIRECTORY)/libraries/util -name *.c)

ifeq ($(USE_SD110), y)
# SD110, BLE stack
INCLUDES  += $(SDK_DIRECTORY)/softdevice/common/softdevice_handler
SRC 	  += $(shell find $(SDK_DIRECTORY)/softdevice/common/softdevice_handler -name *.c)
INCLUDES  += $(SDK_DIRECTORY)/softdevice/s110/headers
endif
