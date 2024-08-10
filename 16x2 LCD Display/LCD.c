/* 
Program to send array elements one by one to p0.28 to p0.21 on an 16x2 LCD Display
These sent elements are commands that make the LCD perform a particular task
0x38 - Enables line 1 and 2 of the LCD
0x30 - Enables line 1 only
0x0E - Display
0x06 - Shift the cursor right
0x01 - clear LCD
0x80 to 0x8F are the address of the 16 elements of the first line
0xC0 to 0xCF are the address of the 16 elements of the second line


Pins P0.21 to P0.28 are outputs from board and inputs to the LCD
P2.11 - RS
P2.12 - R/W
P2.13 - Enable(EN)
*/


#include <LPC17xx.H>

void delay(int a)
{
	int i;
	for(i=0;i<a;i++)
	{
	}
}

int main ()
{
	int array[] = {0x38,0x0E,0x06,0x01,0x80,0xC0};
	unsigned char word[] = "wasssup";
	int k;
	SystemInit();
	LPC_SC -> PCONP = 0x00001000;
	
	
	LPC_GPIO0 -> FIOMASKH = 0xE01F; // top 16 bits of the GPIO pins , 1110 0000 0001 1111 ie pins 21 to 28 are enabled 
	LPC_GPIO0 -> FIODIRH = 0x1FE0; // pins 21 to 28 are outputs
	
	LPC_GPIO2 -> FIOMASK1 = 0xc7;
	LPC_GPIO2 -> FIODIR1 = 0x38;
	
	LPC_GPIO2 -> FIOCLR1 = 0x18; // p2.11 = rs   p2.12 = r/w  makes rs and rw as 0
	
	for(k=0;k<5;k++)
	{
		LPC_GPIO2 -> FIOSET1 = 0x20; //making enable at 13th pin high
	  LPC_GPIO0 -> FIOPIN = (array[k]<<21);	
		delay(1000000);
		LPC_GPIO2 -> FIOCLR1 = 0x20; //makes enable 0
		delay(1000000);
	}	
	
	LPC_GPIO2 -> FIOSET1 = 0x08;
	
	for(k=0;k<5;k++)
	{
		LPC_GPIO2 -> FIOSET1 = 0x20; //making enable at 13th pin high
	  LPC_GPIO0 -> FIOPIN = (word[k]<<21);	
		delay(1000000);
		LPC_GPIO2 -> FIOCLR1 = 0x20; //makes enable 0
		delay(1000000);
	}	
}


