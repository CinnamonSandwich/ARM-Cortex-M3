/*Program to trigger a buzzer when value goes above a threshold and leds are off*/

#include <LPC17xx.H>

int main()
{
	int aout;
	//initialization
	SystemInit();
	LPC_SC -> PCONP = LPC_SC -> PCONP | 0x00001000;
	LPC_GPIO0 -> FIOMASK2 = 0xDF; // 21st pin is buzzer which is enabled (11011111)
	LPC_GPIO0 -> FIODIR2 = 0x20; // 21st pin is initialized as output
	LPC_GPIO0 -> FIOMASK1 = 0xF0; // led at pins 8 9 10 11 enabled 
	LPC_GPIO0 -> FIODIR1 = 0x0F; // leds initialized as output
	
	LPC_PINCON -> PINSEL3 = 0xC0000000; // 1100 ..... since the 31st pin needs to be at state 3 ie (11 -> potentiometer)
	LPC_ADC -> ADCR = 0x00210320;
	
	while(1)
	{
		while(( LPC_ADC -> ADSTAT & 0x00000020 )!= 0x00000020) // as long as the bit in 5th pos (done bit) doesnt become high keep waiting
		{
		}
		aout = ((LPC_ADC -> ADDR5) & 0x0000FFF0)>>4; // since output stored in bits 4 to 15 we mask the rest and then shift the val to obtain proper output
		if(aout > 0xE00)// if greater than val then trigger buzzer 
		{
			LPC_GPIO0 -> FIOPIN2 = 0x20;
			LPC_GPIO0 -> FIOPIN1 = 0x0F;
		}
		else if(aout > 0xC00)
		{
			LPC_GPIO0 ->FIOPIN1 = 0x07;
			LPC_GPIO0 -> FIOPIN2 = 0x00;
		}
		else if(aout > 0x800)
		{
			LPC_GPIO0 ->FIOPIN1 = 0x03;
			LPC_GPIO0 -> FIOPIN2 = 0x00;
		}
		else if(aout > 0x400)
		{
			LPC_GPIO0 ->FIOPIN1 = 0x01;
			LPC_GPIO0 -> FIOPIN2 = 0x00;
		}
		
		
	}
}
