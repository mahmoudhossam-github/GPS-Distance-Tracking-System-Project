#include "TIVA_HEADERS.h"
#include "LED.h"
#include "GPIO.h"
#include "UART.h"

//------------------------//
//--- Global Variables ---//
//------------------------//

unsigned char button_in1;	// Variable to receive input from SW1
unsigned char button_in2; // Variable to receive input from SW2
unsigned char button_prev1 = 0; // Used for FALLING EDGE Condition of SW1
unsigned int distance = 50 ; // Distance variable
unsigned char LED_current; // Variable to get current LED data


//----------------------------------------------------------------------//
//----------------------------- Main Code ------------------------------//
//----------------------------------------------------------------------//
int main(){
	
	LED_Init();
	SW_Init();
	SysTick_Init();
	UART_Init_pc();
	
	while(1){
		
		LED_current = getData_LED();
		button_in1 = SW1_Input();

		if(button_in1==0 && button_prev1 != 0){ // If button is pressed (Falling Edge)
			
			if ((LED_current & Green) == 0) turn_On_LED(Green); 
			else turn_Off_LED(Green);
		}
		
		else {	// Button is not pressed
			if (distance > 100) turn_On_LED(Blue);
			else turn_Off_LED(Blue);
		} 		 
		
		button_prev1 = button_in1; // For falling edge condition on	SW1
		
		SysTick_Delay10ms(); // Delay to avoid runtime problems.
	}
	
}
