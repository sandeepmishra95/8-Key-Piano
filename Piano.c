// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port B bits 7-0 have 8 piano keys

#include "Piano.h"
#include "tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void)
{ 
	/*Using port B as Piano Input. PB0-PB7 as inputs*/
	unsigned long int delay;
	SYSCTL_RCGC2_R  |= 0x02;
	delay = SYSCTL_RCGC2_R ;
	GPIO_PORTB_DIR_R = 0x00;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_PDR_R = 0xFF;
	GPIO_PORTB_PCTL_R = 0;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_DATA_R = 0;
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed


/* KEY DETAILS
	Piano key 3: G (783.991 Hz)
	Piano key 2: E (659.255 Hz)
	Piano key 1: D (587.330 Hz)
	Piano key 0: C (523.251 Hz)

*/
unsigned long Piano_In(void)
{
	unsigned long int sw;
	sw = GPIO_PORTB_DATA_R & 0xFF;
	
	if(sw==0)
		return 0;
	else if(sw==1)
		return 1;
	else if(sw==2)
		return 2;
	else if(sw<=7)
		return 4;
	else if(sw<=15)
		return 8;
	else if(sw<=31)
		return 16;
	else if(sw<=63)
		return 32;
	else if(sw<=127)
		return 64;
	else
		return 128;
}
