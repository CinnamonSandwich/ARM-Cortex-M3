//buzzer 

#include <LPC17xx.H>

void delay( unsigned int a )
{
	int i;
	for( i=0;i<a;i++)
	{
	}
}

int main()
{
	int sw;
	
	
	SystemInit(); //initailizes clock and other system essentials
	LPC_SC -> PCONP = 0x00008000; //  PCONP = Power config peripherals , has given power to the 15th pin only out of 32 pins since 15th pin is the gpio pin
	LPC_GPIO0 -> FIOMASK2 = 0x20;
	LPC_GPIO0 -> FIODIR3 = 0x00;
	LPC_GPIO0 -> FIODIR2 = 0x20;
	
	
	
	while(1)
	{
		sw = LPC_GPIO0 -> FIOPIN3;
		if(sw == 0x40)
			LPC_GPIO0 -> FIOSET2 = 0x20;
		
	}
	
}

