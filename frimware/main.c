#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"
#include "rtc.h"

/***************************************************
                BUTTONS
****************************************************/
#define SET_BTN     PA0
#define INC_BTN     PA1
#define OK_BTN      PA2

/***************************************************
                ERROR LED
****************************************************/
#define ERROR_LED   PB0

RTC_Time rtc;

char lcdBuffer[17];

uint8_t editMode=0;
uint8_t editField=0;

/***************************************************
            BUTTON READ
****************************************************/
uint8_t ButtonPressed(uint8_t pin)
{
    if(!(PINA&(1<<pin)))
    {
        _delay_ms(20);

        if(!(PINA&(1<<pin)))
        {
            while(!(PINA&(1<<pin)));

            return 1;
        }
    }

    return 0;
}

/***************************************************
            SHOW CLOCK
****************************************************/
void DisplayClock(void)
{
    LCD_Clear();

    sprintf(lcdBuffer,"%02d:%02d:%02d",
            rtc.hour,
            rtc.minute,
            rtc.second);

    LCD_Goto(0,4);
    LCD_String(lcdBuffer);

    sprintf(lcdBuffer,"%02d/%02d/20%02d",
            rtc.date,
            rtc.month,
            rtc.year);

    LCD_Goto(1,2);
    LCD_String(lcdBuffer);
}

/***************************************************
            SHOW EDIT SCREEN
****************************************************/
void DisplayEdit(void)
{
    LCD_Clear();

    switch(editField)
    {
        case 0:
            LCD_String("SET HOURS");
            sprintf(lcdBuffer,"%02d",rtc.hour);
            break;

        case 1:
            LCD_String("SET MINUTES");
            sprintf(lcdBuffer,"%02d",rtc.minute);
            break;

        case 2:
            LCD_String("SET DATE");
            sprintf(lcdBuffer,"%02d",rtc.date);
            break;

        case 3:
            LCD_String("SET MONTH");
            sprintf(lcdBuffer,"%02d",rtc.month);
            break;

        case 4:
            LCD_String("SET YEAR");
            sprintf(lcdBuffer,"%02d",rtc.year);
            break;
    }

    LCD_Goto(1,7);
    LCD_String(lcdBuffer);
}

/***************************************************
                MAIN
****************************************************/
int main(void)
{

    DDRA &= ~((1<<SET_BTN)|
              (1<<INC_BTN)|
              (1<<OK_BTN));

    PORTA |= (1<<SET_BTN)|
             (1<<INC_BTN)|
             (1<<OK_BTN);

    DDRB |= (1<<ERROR_LED);

    PORTB &= ~(1<<ERROR_LED);

    LCD_Init();

    TWI_Init();

    LCD_Clear();
    LCD_String("RTC PROJECT");

    _delay_ms(1000);

    while(1)
    {

        if(RTC_Read(&rtc))
        {
            PORTB &= ~(1<<ERROR_LED);
        }
        else
        {
            PORTB |= (1<<ERROR_LED);

            LCD_Clear();
            LCD_String("RTC ERROR");

            _delay_ms(500);

            continue;
        }

        if(editMode==0)
        {
            DisplayClock();
        }
        else
        {
            DisplayEdit();
        }

//         /****************************************
//                 SET BUTTON
//         *****************************************/

//         if(ButtonPressed(SET_BTN))
//         {
//             editMode=1;

//             editField++;

//             if(editField>4)
//             {
//                 editField=0;
//             }
//         }

//         /****************************************
//                 INC BUTTON
//         *****************************************/

//         if(ButtonPressed(INC_BTN))
//         {

//             switch(editField)
//             {

//                 case 0:
//                     rtc.hour++;

//                     if(rtc.hour>=24)
//                         rtc.hour=0;
//                     break;

//                 case 1:
//                     rtc.minute++;

//                     if(rtc.minute>=60)
//                         rtc.minute=0;
//                     break;

//                 case 2:
//                     rtc.date++;

//                     if(rtc.date>31)
//                         rtc.date=1;
//                     break;

//                 case 3:
//                     rtc.month++;

//                     if(rtc.month>12)
//                         rtc.month=1;
//                     break;

//                 case 4:
//                     rtc.year++;

//                     if(rtc.year>99)
//                         rtc.year=0;
//                     break;
//             }

//         }

//         /****************************************
//                 CONFIRM BUTTON
//         *****************************************/

//         if(ButtonPressed(OK_BTN))
//         {

//             RTC_Write(&rtc);

//             editMode=0;

//             LCD_Clear();

//             LCD_String("TIME SAVED");

//             _delay_ms(700);

//         }

//         _delay_ms(200);

//     }

// }


        /****************************************
                SET BUTTON
        ****************************************/
        if(ButtonPressed(SET_BTN))
        {
            if(editMode == 0)
            {
                editMode = 1;
                editField = 0;
            }
            else
            {
                editField++;

                if(editField > 5)
                    editField = 0;
            }
        }

        /****************************************
                INCREMENT BUTTON
        ****************************************/
        if(ButtonPressed(INC_BTN))
        {
            if(editMode)
            {
                switch(editField)
                {
                    case 0:     // Hour
                        rtc.hour++;
                        if(rtc.hour >= 24)
                            rtc.hour = 0;
                        break;

                    case 1:     // Minute
                        rtc.minute++;
                        if(rtc.minute >= 60)
                            rtc.minute = 0;
                        break;

                    case 2:     // Second
                        rtc.second++;
                        if(rtc.second >= 60)
                            rtc.second = 0;
                        break;

                    case 3:     // Date
                        rtc.date++;
                        if(rtc.date > 31)
                            rtc.date = 1;
                        break;

                    case 4:     // Month
                        rtc.month++;
                        if(rtc.month > 12)
                            rtc.month = 1;
                        break;

                    case 5:     // Year
                        rtc.year++;
                        if(rtc.year > 99)
                            rtc.year = 0;
                        break;
                }

                DisplayEdit();
            }
        }

        /****************************************
                OK BUTTON
        ****************************************/
        if(ButtonPressed(OK_BTN))
        {
            if(editMode)
            {
                RTC_Write(&rtc);

                editMode = 0;

                LCD_Clear();
                LCD_String("TIME SAVED");

                _delay_ms(800);
            }
        }

        _delay_ms(150);
    }

    return 0;
}
