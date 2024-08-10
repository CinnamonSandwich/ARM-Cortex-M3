// this code blinks an led connected to the pin 8 of port 0

#include <LPC17xx.H>

void delay(unsigned int a) // some delay cant be sure exactly how long does it takes 
{
	int i;
	for( i = 0; i<a ; i++)
	{
	}
}

int main()
{
	SystemInit(); //initailizes clock and other system essentials
	LPC_SC -> PCONP = 0x00008000; //  PCONP = Power config peripherals , has given power to the 15th pin only out of 32 pins
	LPC_GPIO0 -> FIOMASK1 = 0xFE; //  has enabled the 8th pin out of 32 of port 0 (0 - enable , 1 - disable)
	LPC_GPIO0 -> FIODIR1 = 0x01; // Has initialized the 8th pin as output ( 0 - ip , 1- op)
	
	while(1) 
	{
		LPC_GPIO0 -> FIOSET1 = 0x01; // has set the 8th pin to 1
		delay(1000);
		LPC_GPIO0 -> FIOCLR1 = 0x01; // has cleared the 8th pin ie has set it to 0
		delay(1000);
	}
}
