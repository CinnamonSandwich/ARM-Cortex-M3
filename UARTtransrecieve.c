// Program to recieve character typed into the pc and check is the key pressed 1 or 0 , if 1 turn on led if 0 turn off led any other key no action

// The UART ports are initialized in pin 3, 4, 24 & 25 
// pins 3 and 4 are on by default and the rest off

#include <LPC17xx.H>

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
	unsigned char var;
	SystemInit();
	uart_init();
	// Power and clock intialization
	LPC_SC -> PCONP |= 0x00000000; //using UART port 0 & 1 at pins 3 and 4 so no need to enable (kinda dont need to initialize)
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively
	LPC_GPIO0 -> FIOMASK1 = 0xFE;
	LPC_GPIO0 -> FIODIR1 = 0x01;
	
	
		while(1)
		{
		
		
		while((LPC_UART0 -> LSR & 0x01) != 0x01)
		{
		}
		var = LPC_UART0 -> RBR;
	
		
		LPC_UART0 -> THR = var;
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
		{
		}
		if(var == '1')
			LPC_GPIO0 -> FIOSET1 = 0x01;
		else if(var == '0')
			LPC_GPIO0 -> FIOCLR1 = 0x01;
		
	  }
	}
	


