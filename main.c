// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "DAC.h"



// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delayms(unsigned long msec);
void PLL_Init(void);


void PLL_Init(void)
{
	// 0) Use RCC2
  SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~0x00002000;
  // 4) set the desired system divider
  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~0x00000800;
}


void delayms(unsigned long msec)
{
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;  // each loop takes 5 cycles in simulation
    } 
    msec--;
  }
}

int main(void)
{
	
	unsigned long select,prev=0;
	PLL_Init();
	// PortB used for piano keys, PortE used for DAC    
	Sound_Init(); // initialize SysTick timer and DAC
	DAC_Init();
  //Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done

  while(1)
	{           
			select = Piano_In();
			if(select != prev)
			{
				if(select==1)
						Sound_Tone(5209); //Piano key 0: sa (240 Hz)
				
				else if (select==2)
						Sound_Tone(4628);		//Piano key 1: re (270 Hz)
				
				else if (select==4)
						Sound_Tone(4165); 	//Piano key 2: ga (300 Hz)
				
				else if (select==8)
						Sound_Tone(3905);		//Piano key 3: ma (320 Hz)
				
				else if (select==16)
						Sound_Tone(3471);		//Piano key 4: pa (360 Hz)
				
				else if (select==32)
						Sound_Tone(3124); 	//Piano key 5: dha (400 Hz)
				
				else if (select==64)
						Sound_Tone(2776);		//Piano key 6: ni (450 Hz)
				
				else if (select==128)
						Sound_Tone(2603); 	//Piano key 7: Sa (480 Hz)
				
				else
						Sound_Off();
			}
			prev = select;
			delayms(10);
	} 
	
}



