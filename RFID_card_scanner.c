// This program uses an actual RFID card reader and outputs the scanned code from the RFID card via UART
// One of the three RFID codes are made to be valid and the rest invalid

#include <LPC17xx.H>
#include <string.H>

void uart_init()
{
	LPC_UART0 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART0 -> DLL = 0x75;
	LPC_UART0 -> DLM = 0x00;
	LPC_UART0 -> FDR = 0x10; 
	LPC_UART0 -> LCR = 0x03;
	
	LPC_UART3 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART3 -> DLL = 0x75;
	LPC_UART3 -> DLM = 0x00;
	LPC_UART3 -> FDR = 0x10; 
	LPC_UART3 -> LCR = 0x03;
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
	int count =0;
	char code[] = "09008206C944";
	char var[13];
	char msg1[] = " - Match\n";
	char msg2[] = " - Mismatch\n";

	
	SystemInit();
	uart_init();
	// Power and clock intialization
	LPC_SC -> PCONP |= 0x02000000; //enabling UART 3 at pin 25
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively for UART 0
	LPC_PINCON -> PINSEL9	|= 0x0F000050; // Pins 28 and 29 and made to be Tx and Rx respectively for UART 3
	/* For uni board these are the peripherals
	LPC_GPIO0 -> FIOMASK1 = 0xF0;
	LPC_GPIO0 -> FIODIR1 = 0x0F;
	*/
	
	//For NSK LPC1768 BRD R-5
/*	LPC_GPIO1 -> FIOMASK3 = 0xDF; //Pin 29 for test led , so 1101 1111
	LPC_GPIO1 -> FIODIR3 = 0x20; //Pin 29 is output*/
	
		while(1)
		{
		
		for(i=0;i<12;i++)
		{
		while((LPC_UART3 -> LSR & 0x01) != 0x01)
		{
		}
		var[i] = LPC_UART3 -> RBR;
		
		
		LPC_UART0 -> THR = var[i];
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
		{
		}
		}
		
		for(i=0;i<12;i++)
		{
			if(var[i] != code[i])
				count++;
		}
			
		if(!count)
		{
			/*LPC_GPIO1 -> FIOSET3 = 0x20; // For uni board GPIO0 and FIOSET1 = 0x0F
			delay(1000);
			LPC_GPIO1 -> FIOCLR3 = 0x20; // For uni board GPIO0 and FIOCLR1 = 0x0F*/
			
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
			//LPC_GPIO1 -> FIOCLR3 = 0x20; // For uni board GPIO0 and FIOCLR1 = 0x0F
			
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

