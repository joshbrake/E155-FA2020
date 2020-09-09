// STM32F401RE_GPIO.c
// Source code for GPIO functions

#include "STM32F401RE_GPIO.h"

void pinMode(int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIOA->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIOA->MODER |= (0b1 << 2*pin);
            GPIOA->MODER &= ~(0b1 << 2*pin+1);
            break;
        case GPIO_ALT:
            GPIOA->MODER &= ~(0b1 << 2*pin);
            GPIOA->MODER |= (0b1 << 2*pin+1);
            break;
        case GPIO_ANALOG:
            GPIOA->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalRead(int pin) {
    return ((GPIOA->IDR) >> pin) & 1;
}

void digitalWrite(int pin, int val) {
    GPIOA->ODR |= (1 << pin);
}

void togglePin(int pin) {
    // Use XOR to toggle
    GPIOA->ODR ^= (1 << pin);
}