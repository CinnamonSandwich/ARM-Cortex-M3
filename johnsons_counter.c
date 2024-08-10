// johnsons counter

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
	int val = 0x01;
	int en = 0;
	
	SystemInit(); //initailizes clock and other system essentials
	LPC_SC -> PCONP = 0x00008000; //  PCONP = Power config peripherals , has given power to the 15th pin only out of 32 pins since 15th pin is the gpio pin
	LPC_GPIO0 -> FIOMASK1 = 0xF0;
	LPC_GPIO0 -> FIODIR1 = 0x0F;
	
	
	while(1)
	{
		LPC_GPIO0 -> FIOPIN1 = val;
		delay(1000000);
		
		if(val == 0x0F)
			en = 1;
		
		if(en == 1)
		val = val << 1;
		else 
		{
		val = val << 1;
		val = val | 0x01;
		}
	}
}
