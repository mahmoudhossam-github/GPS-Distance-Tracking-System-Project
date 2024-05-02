#ifndef GPIO.h
#define GPIO.h

#define SW_ALL_MASK 0x11
#define SW2_MASK  0x01
#define SW1_MASK  0x10


unsigned char SW2_Input(void); // Read input from switch 2 (PF0)

unsigned char SW1_Input(void); // Read input from switch 1 (PF4)

unsigned char switch1On(void);    // return true if switch1 is pressed on

unsigned char switch2On(void);    // return true if switch2 is pressed on

void SW_Init(void);    // Switches Initialization

#endif
