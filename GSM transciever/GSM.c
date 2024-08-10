// GSM transciever , GSM allows us to send messages to phone numbers via certain commands
// Commands sent and messages recieved by the GSM board are connected via UART0 port
// message "Hello" is sent once to the ph no by the GSM

#include <LPC17xx.H>
#include <string.h>

void uart_init()
{
	LPC_UART0 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART0 -> DLL = 0x75;
	LPC_UART0 -> DLM = 0x00;
	LPC_UART0 -> FDR = 0x10; 
	LPC_UART0 -> LCR = 0x03;
	
	LPC_UART1 -> LCR = 0x83; // divisor latch enabled , parity disabled , 8 bit char length , 1 stop bit
	LPC_UART1 -> DLL = 0x75;
	LPC_UART1 -> DLM = 0x00;
	LPC_UART1 -> FDR = 0x10; 
	LPC_UART1 -> LCR = 0x03;
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
	char cmd[7][30] = {"AT\r\n","AT+CREG?\r\n","AT+CMGF=1\r\n","AT+CMGS=\"7086039750\"\r\n","Hello",26}; /*AT - attention(cmd to start the GSM), AT+CREG? -asks the receiver can it transmit ,AT+MSGF=1 - Tells receiver send message
																																																				AT+CMGS=\"phonenumber\" - sends message to ph no, Hello - sent message , 26 - ascii for ctrl+z needed to exit the message */
	//char reply[4];
	int i,j,l;
	
	SystemInit();
	uart_init();
	// Power and clock intialization
	LPC_SC -> PCONP |= 0x00000000; //using UART port 0 & 1 at pins 3 and 4 so no need to enable (kinda dont need to initialize)
	LPC_PINCON -> PINSEL0 |= 0x00000050; // Pins 2 and 3 and made to be Tx and Rx respectively
	
		for(i=0;i<7;i++)
		{
			
			for(j=0;cmd[i][j]!='\0';j++)
				{
					
					LPC_UART0->THR = cmd[i][j];
					LPC_UART1->THR = cmd[i][j];
					while(((LPC_UART0 -> LSR & 0x20) != 0x20) && ((LPC_UART1 -> LSR & 0x20) != 0x20))
					{
					}
				}
					delay(400000);
					/*do
					{
						while((LPC_UART1 -> LSR & 0x01) != 0x01)
							{
							}
							reply[k] = LPC_UART1 -> RBR ;
						k+=1;
					}
					while(reply[k]!='\0');
					
					for(j=0;reply[j]!='\0';j++)
					{
						while(((LPC_UART0 -> LSR & 0x20) != 0x20) && ((LPC_UART1 -> LSR & 0x20) != 0x20))
							{
							}
						LPC_UART0 -> THR = reply[j];
					}*/
			}
		
			while(1)
			{
			}

	}
					
					
					
				
		
