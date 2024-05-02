#ifndef LED.h
#define LED.h

#define LED_MASK 0xE
#define Red 0x02
#define Blue 0x04
#define Green 0x08

void LED_Init(void);	// LED Initialization

void turn_On_LED(unsigned char data); // Turns on Red, Blue or Green LED

#endif