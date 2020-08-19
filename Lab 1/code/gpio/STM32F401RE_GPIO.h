// STM32F401RE_GPIO.h
// Header for GPIO functions

#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include <stdint.h> // Include stdint header

// TODO: Fill in "<XXXXXXXX>" with correct base address
#define GPIOA_BASE  (0x<XXXXXXXX>)

// TODO: Put bitfield structs here
typedef struct {
    volatile uint32_t GPIO_MODER; // GPIO Offset 0x00 GPIO port mode register
    // TODO: Fill in the rest of the registers here
} GPIO;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define GPIOA ((GPIO*) GPIOA_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pinMode();

int digitalRead(int pin);

void digitalWrite(int pin, int val);

void togglePin(int pin);

#endif