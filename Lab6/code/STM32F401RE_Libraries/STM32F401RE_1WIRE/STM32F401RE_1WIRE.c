/**
    1WIRE Library: Initializes and controls data acquisition over a 1-Wire interface
    @file STM32F401RE_1WIRE.c
    @author Josh Brake
    @version 1.0 10/1/2020
*/

#include "STM32F401RE_1WIRE.h"


void setupOneWire(void){
    initTIM(ONEWIRE_TIMx);
    GPIOx->OTYPER |= (1 << ONEWIRE_PIN);
    GPIOx->OSPEEDR |= (0b11 << ONEWIRE_PIN * 2);
}

uint8_t init(void){

}

void write_bit(uint8_t val){

}

uint8_t read_bit(void){

}

void write_byte(uint8_t val){

}

uint8_t read_byte(void){

}

void read_rom(uint8_t rom_code[8]){
    // Send initialization sequence

    // Send Read ROM command code
    
    // Read out ROM code
}

void read_scratchpad(uint8_t scratchpad[8]){
    // Send Read Scratchpad command

    // Read out scratchpad
}