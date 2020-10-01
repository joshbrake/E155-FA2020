/**
    1WIRE Library: Initializes and controls data acquisition over a 1-Wire interface
    @file STM32F401RE_1WIRE.h
    @author Josh Brake
    @version 1.0 10/1/2020
*/


#ifndef STM32F4_1WIRE_H
#define STM32F4_1WIRE_H

#include <stdint.h>
#include "STM32F401RE_TIM.h"
#include "STM32F401RE_GPIO.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define GPIOx GPIOA
#define ONEWIRE_PIN 6
#define ONEWIRE_TIMx TIM2

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

/**
    Setups up a 1-Wire interface on ONEWIRE_PIN.
    @return The area of the circle.
*/
void setupOneWire(void);

/**
    Sets up up a 1-Wire interface on ONEWIRE_PIN.
    @return 1 if a device is detected on the line and a 0 otherwise
*/
uint8_t init(void);

/**
    Writes a bit to the 1-Wire data line on ONEWIRE_PIN
    @param Value to be written (1 or 0)
*/
void write_bit(uint8_t val);

/**
    Reads a bit to the 1-Wire data line on ONEWIRE_PIN
    @return Value read (1 or 0)
*/
uint8_t read_bit(void);

/**
    Writes a byte (8 bits) to the 1-Wire data line on ONEWIRE_PIN
    @param Byte to be written
*/
void write_byte(uint8_t val);

/**
    Reads a byte from the 1-Wire data line on ONEWIRE_PIN
    @return Byte read
*/
uint8_t read_byte(void);

/**
    Reads the ROM code of the MAXIM 31820 device on the bus.
    @param Array where rom_code should be written
*/
void read_rom(uint8_t rom_code[8]);

/**
    Reads the scratchpad code of the MAXIM 31820 device on the bus.
    @param Array where rom_code should be written
*/
void read_scratchpad(uint8_t scratchpad[8]);

#endif