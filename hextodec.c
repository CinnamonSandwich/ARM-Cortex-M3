// Program to convert hexadecimal value to decimal and display in LCD
// The program takes a hex value from the ADC and converts that value to decimal 
// Input to ADC is an analog value ranging from 0 to 3.3 V coming from a potentiometer

#include <LPC17xx.H>
#include <stdio.h>

void hextodec(int a,int arr[]) //converts a 16bit hex val to dec
{
	arr[3] = a%0x0A ;
	a /= 0x0A;
	arr[2] = a%0x0A;
	a /= 0x0A;
	arr[1] = a%0x0A; 
	a /= 0x0A;
	arr[0] = a%0x0A ;
}


void convert_to_char(int arr[])
{
	int i;
	for(i=0;i<4;i++)
	{
		arr[i] += 0x30;
	}
}
	


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
	int hexa;
	int arr[4];
	int k;
	SystemInit();
	uart_init();
	
	LPC_SC -> PCONP = LPC_SC -> PCONP | 0x00001000;
	LPC_PINCON -> PINSEL3 = 0xC0000000; // 1100 ..... since the 31st pin needs to be at state 3 ie (11 -> potentiometer)
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively
	LPC_ADC -> ADCR = 0x00210320;
	
	while(1)
	{
		
	while(( LPC_ADC -> ADSTAT & 0x00000020 )!= 0x00000020) // as long as the bit in 5th pos (done bit) doesnt become high keep waiting
		{
		}
		hexa = ((LPC_ADC -> ADDR5) & 0x0000FFF0)>>4; // since output stored in bits 4 to 15 we mask the rest and then shift the val to obtain proper output
	
	
	hextodec(hexa,arr);
		
		
	convert_to_char(arr);
		
		
	for(k=0;arr[k]!='\0';k++)
	{
		LPC_UART0 -> THR = arr[k];
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020) //waits until a char has been transmitted ie THR becomes empty
		{
		}
		
	}
	LPC_UART0 -> THR = '\n';
		while((LPC_UART0 -> LSR & 0x00000020) != 0x00000020) //waits until a char has been transmitted ie THR becomes empty
		{
		}
	delay(1000000);
	}
		
}
	
