// #ifndef RTC_H
// #define RTC_H

// #include <avr/io.h>

// typedef struct
// {
//     uint8_t second;
//     uint8_t minute;
//     uint8_t hour;

//     uint8_t day;

//     uint8_t date;
//     uint8_t month;
//     uint8_t year;

// }RTC_Time;

// void TWI_Init(void);

// uint8_t RTC_Read(RTC_Time *rtc);

// uint8_t RTC_Write(RTC_Time *rtc);

// #endif





#ifndef RTC_H
#define RTC_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <stdint.h>

/****************************************************
                DS1307 I2C ADDRESS
****************************************************/

#define DS1307_WRITE   0xD0
#define DS1307_READ    0xD1

/****************************************************
                RTC STRUCTURE
****************************************************/

typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

    uint8_t day;

    uint8_t date;
    uint8_t month;
    uint8_t year;

}RTC_Time;

/****************************************************
            BCD CONVERSION FUNCTIONS
****************************************************/

uint8_t BCD_To_Dec(uint8_t value);
uint8_t Dec_To_BCD(uint8_t value);

/****************************************************
                TWI FUNCTIONS
****************************************************/

void TWI_Init(void);

uint8_t TWI_Start(uint8_t address);

void TWI_Stop(void);

void TWI_Write(uint8_t data);

uint8_t TWI_Read_ACK(void);

uint8_t TWI_Read_NACK(void);

/****************************************************
                RTC FUNCTIONS
****************************************************/

uint8_t RTC_Read(RTC_Time *rtc);

uint8_t RTC_Write(RTC_Time *rtc);

#endif