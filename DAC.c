// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port E bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none


void DAC_Init(void)
{
	/*Using port E as DAC Output. PE0-PE3 as bits DAC 0-3 bits*/
	unsigned long int delay;
	SYSCTL_RCGC2_R  |= 0x010;
	delay = SYSCTL_RCGC2_R ;
	GPIO_PORTE_DIR_R = 0x0F;
	GPIO_PORTE_DEN_R = 0x0F;
	GPIO_PORTE_PDR_R = 0x00;
	GPIO_PORTE_DR8R_R = 0x0F;  // For 8 mA drive current
	GPIO_PORTE_PCTL_R = 0;
	GPIO_PORTE_AMSEL_R = 0;
	GPIO_PORTE_AFSEL_R = 0;
	GPIO_PORTE_DATA_R = 0x0;
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data)
{
		data &= 0x0F;
		GPIO_PORTE_DATA_R = data;
}
