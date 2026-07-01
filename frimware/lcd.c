// #include "lcd.h"
// #include <stdio.h>

// static void LCD_Enable()
// {
//     PORTD |= (1<<LCD_EN);
//     _delay_us(2);
//     PORTD &= ~(1<<LCD_EN);
//     _delay_us(100);
// }

// static void LCD_SendNibble(uint8_t nibble)
// {
//     PORTD &= 0x0F;
//     PORTD |= (nibble & 0xF0);
//     LCD_Enable();
// }

// void LCD_Command(uint8_t cmd)
// {
//     PORTD &= ~(1<<LCD_RS);

//     LCD_SendNibble(cmd);
//     LCD_SendNibble(cmd<<4);

//     _delay_ms(2);
// }

// void LCD_Char(char data)
// {
//     PORTD |= (1<<LCD_RS);

//     LCD_SendNibble(data);
//     LCD_SendNibble(data<<4);

//     _delay_us(100);
// }

// void LCD_String(char *str)
// {
//     while(*str)
//     {
//         LCD_Char(*str++);
//     }
// }

// void LCD_Clear()
// {
//     LCD_Command(0x01);
//     _delay_ms(2);
// }

// void LCD_Goto(uint8_t row,uint8_t col)
// {
//     if(row==0)
//         LCD_Command(0x80+col);
//     else
//         LCD_Command(0xC0+col);
// }

// void LCD_Integer(int value)
// {
//     char buffer[10];
//     sprintf(buffer,"%d",value);
//     LCD_String(buffer);
// }

// void LCD_Init()
// {
//     DDRD |= (1<<PD0);
//     DDRD |= (1<<PD1);
//     DDRD |= (1<<PD4);
//     DDRD |= (1<<PD5);
//     DDRD |= (1<<PD6);
//     DDRD |= (1<<PD7);

//     _delay_ms(20);

//     LCD_Command(0x02);

//     LCD_Command(0x28);

//     LCD_Command(0x0C);

//     LCD_Command(0x06);

//     LCD_Command(0x01);

//     _delay_ms(2);
// }






#include "lcd.h"
#include <stdio.h>

/****************************************************
                PRIVATE FUNCTIONS
****************************************************/

static void LCD_EnablePulse(void)
{
    PORTD |= (1 << LCD_EN);
    _delay_us(2);

    PORTD &= ~(1 << LCD_EN);
    _delay_us(100);
}

static void LCD_SendNibble(uint8_t nibble)
{
    /* Clear D4-D7 */
    PORTD &= 0x0F;

    /* Put nibble on D4-D7 */
    PORTD |= (nibble & 0xF0);

    LCD_EnablePulse();
}

/****************************************************
                SEND COMMAND
****************************************************/

void LCD_Command(uint8_t cmd)
{
    PORTD &= ~(1 << LCD_RS);

    LCD_SendNibble(cmd);
    LCD_SendNibble(cmd << 4);

    _delay_ms(2);
}

/****************************************************
                SEND CHARACTER
****************************************************/

void LCD_Char(char data)
{
    PORTD |= (1 << LCD_RS);

    LCD_SendNibble(data);
    LCD_SendNibble(data << 4);

    _delay_us(100);
}

/****************************************************
                PRINT STRING
****************************************************/

void LCD_String(const char *str)
{
    while(*str)
    {
        LCD_Char(*str++);
    }
}

/****************************************************
                CLEAR LCD
****************************************************/

void LCD_Clear(void)
{
    LCD_Command(0x01);
    _delay_ms(2);
}

/****************************************************
                CURSOR POSITION
****************************************************/

void LCD_Goto(uint8_t row, uint8_t col)
{
    if(row == 0)
    {
        LCD_Command(0x80 + col);
    }
    else
    {
        LCD_Command(0xC0 + col);
    }
}

/****************************************************
                PRINT INTEGER
****************************************************/

void LCD_Integer(int value)
{
    char buffer[10];

    sprintf(buffer,"%d",value);

    LCD_String(buffer);
}

/****************************************************
                LCD INITIALIZATION
****************************************************/

void LCD_Init(void)
{
    /* PD0 RS */
    /* PD1 EN */
    /* PD4-D7 DATA */

    DDRD |= (1<<PD0);
    DDRD |= (1<<PD1);
    DDRD |= (1<<PD4);
    DDRD |= (1<<PD5);
    DDRD |= (1<<PD6);
    DDRD |= (1<<PD7);

    _delay_ms(20);

    /* Initialize LCD in 4-bit mode */

    LCD_Command(0x02);

    LCD_Command(0x28);

    LCD_Command(0x0C);

    LCD_Command(0x06);

    LCD_Clear();
}