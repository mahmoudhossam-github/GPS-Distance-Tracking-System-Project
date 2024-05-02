#ifndef UART.h
#define UART.h
#define CR 0x0D 
void UART_Init_pc(void); // init_uart_pc

void UART_OutChar_pc(char data); // write uart data

char UART_InChar_pc(); // read uart data

#endif
