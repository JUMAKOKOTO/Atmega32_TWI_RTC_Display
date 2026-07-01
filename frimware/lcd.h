// #ifndef LCD_H
// #define LCD_H

// #include <avr/io.h>
// #include <util/delay.h>

// #define LCD_RS PD0
// #define LCD_EN PD1

// void LCD_Init(void);
// void LCD_Command(uint8_t cmd);
// void LCD_Char(char data);
// void LCD_String(char *str);
// void LCD_Clear(void);
// void LCD_Goto(uint8_t row,uint8_t col);
// void LCD_Integer(int value);

// #endif




#ifndef LCD_H
#define LCD_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/****************************************************
                LCD CONNECTION
*****************************************************

ATmega32          LCD

PD0 ------------> RS
PD1 ------------> EN
PD4 ------------> D4
PD5 ------------> D5
PD6 ------------> D6
PD7 ------------> D7

RW -------------- GND

****************************************************/

#define LCD_RS     PD0
#define LCD_EN     PD1

/****************************************************
                LCD FUNCTIONS
****************************************************/

void LCD_Init(void);

void LCD_Command(uint8_t cmd);

void LCD_Char(char data);

void LCD_String(const char *str);

void LCD_Clear(void);

void LCD_Goto(uint8_t row, uint8_t col);

void LCD_Integer(int value);

#endif