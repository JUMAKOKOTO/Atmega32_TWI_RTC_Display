#include "rtc.h"

uint8_t BCD_To_Dec(uint8_t val)
{
    return ((val>>4)*10)+(val&0x0F);
}

uint8_t Dec_To_BCD(uint8_t val)
{
    return ((val/10)<<4)|(val%10);
}

/****************************************************
                TWI
****************************************************/

void TWI_Init(void)
{
    TWSR=0x00;
    TWBR=32;
    TWCR=(1<<TWEN);
}

uint8_t TWI_Start(uint8_t address)
{
    TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    while(!(TWCR&(1<<TWINT)));

    if((TWSR&0xF8)!=0x08 &&
       (TWSR&0xF8)!=0x10)
        return 0;

    TWDR=address;

    TWCR=(1<<TWINT)|(1<<TWEN);

    while(!(TWCR&(1<<TWINT)));

    uint8_t status=TWSR&0xF8;

    if(status!=0x18 &&
       status!=0x40)
        return 0;

    return 1;
}

void TWI_Stop(void)
{
    TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);

    while(TWCR&(1<<TWSTO));
}

void TWI_Write(uint8_t data)
{
    TWDR=data;

    TWCR=(1<<TWINT)|(1<<TWEN);

    while(!(TWCR&(1<<TWINT)));
}

uint8_t TWI_Read_ACK(void)
{
    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

    while(!(TWCR&(1<<TWINT)));

    return TWDR;
}

uint8_t TWI_Read_NACK(void)
{
    TWCR=(1<<TWINT)|(1<<TWEN);

    while(!(TWCR&(1<<TWINT)));

    return TWDR;
}

/****************************************************
                RTC READ
****************************************************/

uint8_t RTC_Read(RTC_Time *rtc)
{
    if(!TWI_Start(0xD0))
        return 0;

    TWI_Write(0x00);

    if(!TWI_Start(0xD1))
        return 0;

    rtc->second=BCD_To_Dec(TWI_Read_ACK()&0x7F);
    rtc->minute=BCD_To_Dec(TWI_Read_ACK());
    rtc->hour=BCD_To_Dec(TWI_Read_ACK());
    rtc->day=TWI_Read_ACK();
    rtc->date=BCD_To_Dec(TWI_Read_ACK());
    rtc->month=BCD_To_Dec(TWI_Read_ACK());
    rtc->year=BCD_To_Dec(TWI_Read_NACK());

    TWI_Stop();

    return 1;
}

/****************************************************
                RTC WRITE
****************************************************/

uint8_t RTC_Write(RTC_Time *rtc)
{
    if(!TWI_Start(0xD0))
        return 0;

    TWI_Write(0x00);

    TWI_Write(Dec_To_BCD(rtc->second));
    TWI_Write(Dec_To_BCD(rtc->minute));
    TWI_Write(Dec_To_BCD(rtc->hour));
    TWI_Write(rtc->day);
    TWI_Write(Dec_To_BCD(rtc->date));
    TWI_Write(Dec_To_BCD(rtc->month));
    TWI_Write(Dec_To_BCD(rtc->year));

    TWI_Stop();

    return 1;
}