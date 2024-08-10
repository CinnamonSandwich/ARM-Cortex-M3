// program to blink all 4 leds 10 times 

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
	int j;
	SystemInit(); //initailizes clock and other system essentials
	LPC_SC -> PCONP = 0x00008000; //  PCONP = Power config peripherals , has given power to the 15th pin only out of 32 pins since 15th pin is the gpio pin
	LPC_GPIO0 -> FIOMASK1 = 0xF0;
	LPC_GPIO0 -> FIODIR1 = 0x0F;
	
	
	for(j=0;j<10;j++)
	{
		LPC_GPIO0 -> FIOSET1 = 0x0F;
		delay(1000000);
		LPC_GPIO0 -> FIOCLR1 = 0x0F;
		delay(1000000);
	}
}
