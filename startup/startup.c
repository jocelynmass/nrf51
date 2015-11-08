//
//  startup.c
//
//  Created by Jocelyn MASSEROT on 11/08/2015.
//  Copyright (c) 2015 Jocelyn MASSEROT. All rights reserved.
//


extern unsigned long _etext; // End of the code section
extern unsigned long _sdata; // Start address for the .data section
extern unsigned long _edata; // End address for the .data section
extern unsigned long _sbss; // Start address for the .bss section
extern unsigned long _ebss; // End address for the .bss section
extern void _end_of_stack; // Top of stack

extern int main(void);

void default_irq(void);
void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak, alias ("default_irq")));
void HardFault_Handler(void) __attribute__ ((weak, alias ("default_irq")));
void SVC_Handler(void) __attribute__ ((weak, alias ("default_irq")));
void PendSV_Handler(void) __attribute__ ((weak, alias ("default_irq")));
void SysTick_Handler(void) __attribute__ ((weak, alias ("default_irq")));
void POWER_CLOCK_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void RADIO_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void UART0_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SPI0_TWI0_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SPI1_TWI1_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void GPIOTE_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void ADC_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void TIMER0_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void TIMER1_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void TIMER2_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void RTC0_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void TEMP_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void RNG_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void ECB_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void CCM_AAR_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void WDT_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void RTC1_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void QDEC_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void LPCOMP_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI0_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI1_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI2_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI3_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI4_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));
void SWI5_IRQHandler(void) __attribute__ ((weak, alias ("default_irq")));

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	&_end_of_stack,        // The initial stack pointer
	Reset_Handler,         // Reset handler
	NMI_Handler,           // NMI handler
	HardFault_Handler,     // Hard fault handler
	0,0,0,0,0,0,0,         // 7 unused addresses   
	SVC_Handler,           // SVC handler
	0,0,                   // 2 unused addresses
	PendSV_Handler,        // Pend SV handler
	SysTick_Handler,       // Sys tick handler
	POWER_CLOCK_IRQHandler,// Power clock handler
	RADIO_IRQHandler,      // Radio handler
	UART0_IRQHandler,      // Uart 0 handler
	SPI0_TWI0_IRQHandler,  // SPI 0 handler
	SPI1_TWI1_IRQHandler,  // SPI 1 handler
	0,                     // 1 unused address
	GPIOTE_IRQHandler,     // GPIO handler
	ADC_IRQHandler,        // ADC handler
	TIMER0_IRQHandler,     // TIMER 0 handler
	TIMER1_IRQHandler,     // TIMER 1 handler
	TIMER2_IRQHandler,     // TIMER 2 handler
	RTC0_IRQHandler,       // RTC0 handler
	TEMP_IRQHandler,       // TEMP handler
	RNG_IRQHandler,        // RNG handler
	ECB_IRQHandler,        // ECB handler
	CCM_AAR_IRQHandler,    // CCM AAR handler
	WDT_IRQHandler,        // WDT handler
	RTC1_IRQHandler,       // RTC1 handler
	QDEC_IRQHandler,       // QDEC handler
	LPCOMP_IRQHandler,     // LDCOMP handler
	SWI0_IRQHandler,       // SWI0 handler
	SWI1_IRQHandler,       // SWI1 handler
	SWI2_IRQHandler,       // SWI2 handler
	SWI3_IRQHandler,       // SWI3 handler
	SWI4_IRQHandler,       // SWI4 handler
	SWI5_IRQHandler,       // SWI5 handler
	0,0,0,0,0,0,           // 6 unused addresses
};

void Reset_Handler(void)
{
	unsigned long *src, *dest;
	
	src = &_etext; // place pointer to the end of .text section, data value are stored after 
                       // code section
	
	//init RAM data with value contained in FLASH
	for(dest = &_sdata; dest < &_edata; )
	{
		*(dest++) = *(src++);
	}
	
	//init .bss section with 0 value
	for(dest = &_sbss; dest < &_ebss; )
	{
		*(dest++) = 0;
	}
	
	main(); // call main application entry point
}

void default_irq(void){
    // place warning debug here
}