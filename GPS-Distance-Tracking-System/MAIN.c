#include "TIVA_HEADERS.h"
#include "LED.h"
#include "GPIO.h"
#include "UART.h"
#define M_PI 3.14159265358979323846
//------------------------//
//--- Global Variables ---//
//------------------------//

unsigned char button_in1;	// Variable to receive input from SW1
unsigned char button_in2; // Variable to receive input from SW2
unsigned char button_prev1 = 0; // Used for FALLING EDGE Condition of SW1
unsigned int distance = 50 ; // Distance variable
unsigned char LED_current; // Variable to get current LED data
char GPS_logName[] = "$GPGLL,"; 
char GPS_COUNTER;
char GPS[80];   


//------------------------//
//--- GPS_READ_FUNCTION---//
//------------------------//
char GPS_logName[] = "$GPGLL,"; 
char GPS_COUNTER;
char GPS[80];   


void GPS_READ(void)  //we will use GPGLL
{
	int k;
	int r;	
	char i;
    char RECIEVED_CHAR; 
    char flag = 1; 
    do 
    { 
        flag = 1; 
        
        for (i = 0; i < 7; i++) //"$GPGLL,"
        { 
 
            if (UART_InChar_gps() != GPS_logName[i]) 
            { 
                flag = 0; // break and exit from for loop 
                break; 
            } 
        } 
    } while (flag == 0);// i checked recieved output true or not  will continue checking untill the desired LOG arrives
 
   strcpy(GPS, ""); // INIT GPS ARRAY 
   GPS_COUNTER =0;
do{ 
     
    RECIEVED_CHAR=UART_InChar_gps(); 
     
    GPS[GPS_COUNTER++]=RECIEVED_CHAR;  //now we have a char array called GPS  29.9756000,N,31.2372000,E,182908.00,A,A*
	
} while(RECIEVED_CHAR!='*'); 

}

//----------------------------------------//
//--- CONVERT_T0_DEGREE_ANGLE_FUNTION  ---//
//---------------------------------------//

float convert_to_degree_angle(float angle) 
{ 
    int degree = (int)angle / 100; 
    float minutes = angle - (float)degree * 100; 
    return (degree + (minutes / 60)); 
} 

//------------------------------------//
//--- CONVERT_T0_RAD_ANGLE_FUNTION ---//
//------------------------------------//
float convert_to_rad_angle(float angle) 
{ 
 
    return angle * M_PI / 180; 
}



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
