MEMORY
{
	RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 16k
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256k
}

_end_of_stack = (0x20000000 + 16k);
_stack_size = 2k;
_heap_size = 2k;

SECTIONS
{
	.isr_vector : {
		KEEP(*(.isr_vector)) /* vector table */
		. = ALIGN(4);
	} > FLASH

	.text : { /* code and constants */
		. = ALIGN(4);
		*(.text) /* .text sections (code) */
		*(.text*) /* .text* sections (code) */
		*(.rodata) /* .rodata sections (constants, strings, etc.) */
		*(.rodata*) /* .rodata* sections (constants, strings, etc.) */
		. = ALIGN(4);
		_etext = .; /* Used by .data section, to place initialized variable RAM values*/
	} >FLASH
	
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;        /* Used by the startup code in order to initialize the .bss section */
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = . ;      /* Used by the startup in order to initialize the .bss section */

	} >RAM
	
	.data  : AT ( _etext )
	{
		. = ALIGN(4);
		_sdata = . ;  /* Used by the startup in order to initialize the .data section */
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = . ; /* Used by the startup in order to initialize the .data section */
	} >RAM
	
	/DISCARD/ : {
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )

	}
}