#ifndef _EEPROM_H_
#define _EEPROM_H_

#define MAXX 450

unsigned char EEPROM_Init(void);

char EEPROM_ReadChar(unsigned char shift); // Used inside another function (EEPROM_Read())

unsigned int EEPROM_Read(char *Data); // Reads whole EEPROM

void EEPROM_WriteCharInWord(char data, unsigned char shift);

void EEPROM_WriteChar(char data);

void EEPROM_WriteArray(char *data, unsigned int length); // MAINLY USED FUNCTION

void EEPROM_WriteArray2(char *data, unsigned int length);

void EEPROM_TO_PC(char *DATA, unsigned int idx);

#endif
