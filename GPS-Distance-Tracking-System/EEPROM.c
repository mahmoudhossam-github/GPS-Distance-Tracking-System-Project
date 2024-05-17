#include "TIVA_HEADERS.h"
#include "EEPROM.h"
#include "LED.h"
#include "UART.h"
#include <string.h>
#include <stdint.h>

unsigned int shiftCounter = 4; // GLOBAL VARIABLE FOR EEPROM_WriteChar() function!

unsigned char EEPROM_Init(void)
{
	SysTick_Delay10ms();
	
	SYSCTL_RCGCEEPROM_R = 1;
	
	SysTick_Delay10ms();
	while((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING));
	
	
	if(EEPROM_EESUPP_R & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY)){
		return 0;
	}
	
	if((SYSCTL_PREEPROM_R & 1) ==0) {turn_On_LED(Red); return 0;}
	
	return 1;
}

char EEPROM_ReadChar(unsigned char shift)
{
	uint32_t data = EEPROM_EERDWR_R & (0xFF<<(8*shift));;
	data = (data >> (8*shift));
	return (char)data;
}

unsigned int EEPROM_Read(char *Data)
{
	unsigned int idx = 0;
	unsigned int i;
	unsigned char flag = 0;
	
	EEPROM_EEBLOCK_R = 0;
	EEPROM_EEOFFSET_R = 0;
	
	while(1)
	{
		for(i = 0; i<4; i++)
		{
			Data[idx] = EEPROM_ReadChar(3-i);
			while((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING));
		
			if(Data[idx] == '-')
			{
				flag = 1;
				break;
			}
			idx++;
		}
		
		if(flag == 1) break;
		
		else if(EEPROM_EEBLOCK_R == 31) break;
		
		else if(EEPROM_EEOFFSET_R == 15)
		{
			EEPROM_EEOFFSET_R = 0;
			EEPROM_EEBLOCK_R += 1;
		}
		
		else
		{
			EEPROM_EEOFFSET_R += 1;
		}
		SysTick_Delay10ms();
	}
	return idx;
	
}

void EEPROM_WriteCharInWord(char data, unsigned char shift)
{
	uint32_t mask = 0;
	mask |= data;
	mask = (mask<<(8*shift));
	EEPROM_EERDWR_R &= ~(0xFF<< (8*shift));
	EEPROM_EERDWR_R |= mask;
}

void EEPROM_WriteChar(char data)
{
		shiftCounter--;
	
		EEPROM_WriteCharInWord(data,shiftCounter);
	
		while((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING));
	
		SysTick_Delay10ms();
		if(data == '-') return;
		while(1){
			if(shiftCounter != 0)	return;
			
			else if(shiftCounter == 0) shiftCounter = 4;
			
			if(EEPROM_EEOFFSET_R < 0x0F)
				
			EEPROM_EEOFFSET_R++;		// increment the Offset if it will remain less thatn 16 ( max Offset )
			else
			{
				if(EEPROM_EEBLOCK_R <= 30) EEPROM_EEBLOCK_R++;		// increment the block number
				else
				{
					break;
				}
				EEPROM_EEOFFSET_R = 0x00;	// reset the Offset to 0
			}
	}
}

void EEPROM_WriteArray(char *data, unsigned int length)
{
    unsigned int i; 
    for (i = 0; i < length; i++) 
	{
        EEPROM_WriteChar(data[i]); // Write the character
        // Add a delay to ensure proper EEPROM write operation
        SysTick_Delay10ms(); // Adjust delay as needed 
		if(data[i] == '-') break;
	}
}

void EEPROM_WriteArray2(char *data, unsigned int length)
{
    unsigned int i;
	  
    for (i = 0; i < length; i++) 
	{
        EEPROM_WriteChar(data[i]); // Write the character
        // Add a delay to ensure proper EEPROM write operation
        SysTick_Delay10ms(); // Adjust delay as needed 
		if(data[i] == ' ') break;
	}
}

void EEPROM_TO_PC(char *DATA, unsigned int idx) /* FUNCTION TO SEND DATA FROM EEPROM TO PC after
	receiving command 'U'*/
{
	unsigned int i;
	unsigned char flagg = 0;
	
	//UART_Init_pc();
			LED_Reset();
			SysTick_Delay10ms();
			turn_On_LED(Red);
			turn_On_LED(Green);
			
			if(UART_InChar_pc() == 'U')
			{
				SysTick_Delay10ms();
				LED_Reset();
				turn_On_LED(Blue); // Indicates in progress!
				i = 0;
				// We need to setup block of code to send data from EEPROM to PC!
				for(i = 0; i<idx+1 ; i++)
				{
					if(DATA[i]=='-') break;
					UART_OutChar_pc(DATA[i]);
					//while(UART_InChar_pc() != 'R');
					SysTick_Delay10ms();
					SysTick_Delay10ms();
				}
				LED_Reset();
				SysTick_Delay10ms();
				turn_On_LED(Green);
				SysTick_Delay10ms();
			}	
}


