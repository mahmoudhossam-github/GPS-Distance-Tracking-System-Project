#include "TIVA_HEADERS.h"
#include GPIO.h

void SW_Init(void){
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |= SW_ALL_MASK; //allow changes for port 1,2,3 for portf
	GPIO_PORTF_AMSEL_R &= ~SW_ALL_MASK ;
	GPIO_PORTF_AFSEL_R &= ~SW_ALL_MASK ;
	GPIO_PORTF_PCTL_R  &= ~GPIO_PCTL_PF0_M; //clear bits in PCTL
	GPIO_PORTF_PCTL_R  &= ~GPIO_PCTL_PF4_M;
	GPIO_PORTF_DIR_R &= ~SW_ALL_MASK;
	GPIO_PORTF_DEN_R |=SW_ALL_MASK;
	GPIO_PORTF_PUR_R  =SW_ALL_MASK;
}

unsigned char SW2_Input(void){
	return GPIO_PORTF_DATA_R & SW2_MASK;
}
unsigned char SW1_Input(void){
	return GPIO_PORTF_DATA_R & SW1_MASK;
}
unsigned char switch1On(void){		// return true if switch1 is pressed on
	return ((~GPIO_PORTF_DATA_R & 0x10) == 0x10);
}
unsigned char switch2On(void){
	return ((~GPIO_PORTF_DATA_R & 0x01) == 0x01);
}
