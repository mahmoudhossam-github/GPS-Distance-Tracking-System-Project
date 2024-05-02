
#include "TIVA_HEADERS.h"
#include "UART.h"
#include <string.h>


void UART_Init_pc(void) // funtion for init uart0
{

	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0; // activate uart 0
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // activate port A

	UART0_CTL_R &= ~UART_CTL_UARTEN; // disable uart0

	UART0_IBRD_R = 0X208;											// IBRD=INT(80000000/(9600*16)) =520
	UART0_FBRD_R = 0X35;											// FBRD=ROUND(0.833333*64) =53
	UART0_LCRH_R = (UART_LCRH_FEN | UART_LCRH_WLEN_8);				// 1110000   ENABLE FIFO + DATA IS 8 BITS
	UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN); // enable RXE, TXE UART
	GPIO_PORTA_AFSEL_R |= 0X03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0XFFFFFF00) | (GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
	GPIO_PORTA_DEN_R |= 0X03;	 // enable digital on PA0,PA1
	GPIO_PORTA_AMSEL_R &= ~0X03; // disable analog on PA0,PA1
}

char UART_InChar_pc() // read uart data
{
	while ((UART0_FR_R & UART_FR_RXFE) != 0); // while fifo is empty>>dont read
	return (char)(UART0_DR_R & 0xFF); // we just want the 8 bits
}

void UART_OutChar_pc(char data) // write uart data
{

	while ((UART0_FR_R & UART_FR_TXFF) != 0); // while fifo is full>>dont write
	UART0_DR_R = data; // we just want the 8 bits
}