// RFID Card Reader 
// Program to read a string and compare it to a user defined string

#include <LPC17xx.H>
#include <string.h>

void uart_init()
{
	LPC_UART0 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART0 -> DLL = 0x75;
	LPC_UART0 -> DLM = 0x00;
	LPC_UART0 -> FDR = 0x10; 
	LPC_UART0 -> LCR = 0x03;
}
	
void delay(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
	}
}

int main()
{
	int i;
	char code[] = "Hello";
	char var[5];
	char msg1[] = " - Match\n";
	char msg2[] = " - Mismatch\n";

	
	SystemInit();
	uart_init();
	// Power and clock intialization
	LPC_SC -> PCONP |= 0x00000000; //using UART port 0 & 1 at pins 3 and 4 so no need to enable (kinda dont need to initialize)
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively
	
	/* For uni board these are the peripherals
	LPC_GPIO0 -> FIOMASK1 = 0xF0;
	LPC_GPIO0 -> FIODIR1 = 0x0F;
	*/
	
	//For NSK LPC1768 BRD R-5
	LPC_GPIO1 -> FIOMASK3 = 0xDF; //Pin 29 for test led , so 1101 1111
	LPC_GPIO1 -> FIODIR3 = 0x20; //Pin 29 is output
	
		while(1)
		{
		
		for(i=0;code[i]!='\0';i++)
		{
		while((LPC_UART0 -> LSR & 0x01) != 0x01)
		{
		}
		var[i] = LPC_UART0 -> RBR;
		
	
		LPC_UART0 -> THR = var[i];
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
		{
		}
		}
		
		if(!strcmp(var,code))
		{
			LPC_GPIO1 -> FIOSET3 = 0x20; // For uni board GPIO0 and FIOSET1 = 0x0F
			delay(1000000);
			LPC_GPIO1 -> FIOCLR3 = 0x20; // For uni board GPIO0 and FIOCLR1 = 0x0F
			
			for(i=0;i<strlen(msg1);i++)
			{
				LPC_UART0 -> THR = msg1[i];
				while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
				{
				}
			}
		}
			
		else 
		{
			LPC_GPIO1 -> FIOCLR3 = 0x20; // For uni board GPIO0 and FIOCLR1 = 0x0F
			
			for(i=0;i<strlen(msg2);i++)
			{
				LPC_UART0 -> THR = msg2[i];
				while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
				{
				}
			}
		}
	}
	
}

