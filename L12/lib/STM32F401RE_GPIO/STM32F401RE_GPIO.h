// STM32F401RE_GPIO.h
// Header for GPIO functions

#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Values for GPIO pins ("val" arguments)
#define GPIO_LOW    0
#define GPIO_HIGH   1

// // Base addresses for GPIO ports
#define GPIOA_BASE  (0x40020000UL)
#define GPIOB_BASE  (0x40020400UL)
#define GPIOC_BASE  (0x40020800UL)

// Arbitrary GPIO functions for pinMode()
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define GPIO_ALT    2
#define GPIO_ANALOG 3

// Pin definitions for every GPIO pin
#define GPIO_PA0    0
#define GPIO_PA1    1
#define GPIO_PA2    2
#define GPIO_PA3    3
#define GPIO_PA4    4
#define GPIO_PA5    5
#define GPIO_PA6    6
#define GPIO_PA7    7
#define GPIO_PA8    8
#define GPIO_PA9    9
#define GPIO_PA10   10
#define GPIO_PA11   11
#define GPIO_PA12   12
#define GPIO_PA13   13
#define GPIO_PA14   14
#define GPIO_PA15   15

///////////////////////////////////////////////////////////////////////////////
// Bitfield structs
///////////////////////////////////////////////////////////////////////////////

// GPIO register structs here
typedef struct {
    volatile uint32_t MODER;   // GPIO Offset 0x00 GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO Offset 0x04
    volatile uint32_t OSPEEDR; // GPIO Offset 0x08
    volatile uint32_t PURPDR;  // GPIO Offset 0x0C
    volatile uint32_t IDR;     // GPIO Offset 0x10
    volatile uint32_t ODR;     // GPIO Offset 0x14
    volatile uint32_t BSRR;    // GPIO Offset 0x18
    volatile uint32_t LCKR;    // GPIO Offset 0x1C
    volatile uint32_t AFRL;    // GPIO Offset 0x20
    volatile uint32_t AFRH;    // GPIO Offset 0x24
} GPIO_TypeDef;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pinMode(GPIO_TypeDef *, int pin, int function);

int digitalRead(GPIO_TypeDef *, int pin);

void digitalWrite(GPIO_TypeDef *, int pin, int val);

void togglePin(GPIO_TypeDef *, int pin);

#endif