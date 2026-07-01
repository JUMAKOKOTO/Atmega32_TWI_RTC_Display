MCU=atmega32
F_CPU=8000000UL
TARGET=main

CC=D:/NOTES/THIRD YEAR/TICHA 2/CT 321/ATmega32_TWI_RTC_Display/RTC_project/avr8-gnu-toolchain-win32_x86_64/bin/avr-gcc.exe
OBJCOPY=D:/NOTES/THIRD YEAR/TICHA 2/CT 321/ATmega32_TWI_RTC_Display/RTC_project/avr8-gnu-toolchain-win32_x86_64/bin/avr-objcopy.exe

CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

all:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

clean:
	del *.elf *.hex