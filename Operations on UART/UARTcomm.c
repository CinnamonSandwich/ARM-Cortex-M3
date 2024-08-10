/* UART Communication */

// The UART ports are initialized in pin 3, 4, 24 & 25 
// pins 3 and 4 are on by default and the rest off

#include <LPC17xx.H>

void uart_init()
{
	LPC_UART0 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART0 -> DLL = 0x01;
	LPC_UART0 -> DLM = 0x00;
	LPC_UART0 -> FDR = 0x00000010; 
	LPC_UART0 -> LCR = 0x03;
}
	
	

int main()
{
	unsigned char a[] ="Welcome";
	unsigned char k;
	SystemInit();
	uart_init();
	// Power and clock intialization
	LPC_SC -> PCONP |= 0x00000000; //using UART port 0 & 1 at pins 3 and 4 so no need to enable (kinda dont need to initialize)
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively
	
	for(k=0;a[k]!='\0';k++)
	{
		LPC_UART0 -> THR = a[k];
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020)
		{
		}
	}
	while(1)
	{
	}
	
}
