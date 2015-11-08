# relative location of the toolchain binary
TOOLCHAIN = ../toolchain/arm_cm0/bin/arm-none-eabi-
# arm-none-eabi-gcc executable
CC   = $(TOOLCHAIN)gcc
# arm-none-eabi-objcopy executable          
CP   = $(TOOLCHAIN)objcopy    
# output format is raw binary and we strip the symbol information from source files                      
BIN  = $(CP) -O binary -S     


# Sources
# linker script directory
LDSCRIPT = ../linker_script/nrf51_ld_script.ld   
# startup folder directory     
STARTUP_DIR = ../startup

# main.c directory
SRC  = src/main.c          
# startup.c directory                         
SRC  += $(STARTUP_DIR)/startup.c                      

# include directory
INCLUDES = include/          

# add option "-I" before each included folders                    
INCLUDE_DIR  = $(patsubst %,-I%,$(INCLUDES))    

# Project name
PROJECT_NAME = led_blinking

# Options
OBJS  = $(SRC:.c=.o)

CPFLAGS = -mcpu=cortex-m0 -Os -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
LDFLAGS = -mcpu=cortex-m0 -lc -mthumb -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(PROJECT_NAME).map,--cref,--no-warn-mismatch $(LIBDIR)
 
# Generate dependency information
CPFLAGS += -MD -MP -MF .dep\$(@F).d
 


# Rules
 
all: $(OBJS) $(PROJECT_NAME).elf  $(PROJECT_NAME).bin $(PROJECT_NAME).map
 
 %o: %c
	$(CC) -c $(CPFLAGS) -I . $(INCLUDE_DIR) $< -o $@


%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	
%bin: %elf
	$(BIN)  $< $@

	
clean:
	find ./ -name '*~' | xargs rm -f
	rm -f $(OBJS)
	rm -f $(PROJECT_NAME).elf
	rm -f $(PROJECT_NAME).map
	rm -f $(PROJECT_NAME).hex
	rm -f $(PROJECT_NAME).bin
	rm $(SRC:.c=.lst)
	rm -r  .dep*
