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
    uint8_t r; // Create variable for return value

    GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Clear mode
    GPIOx->MODER |= (0b01 << ONEWIRE_PIN  * 2); // Configure as output
    GPIOx->BSRR = (1 << (ONEWIRE_PIN + 16)); // Set to output low

    delay_micros(ONEWIRE_TIMx, 480); // Wait
    
    GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Configure as input
    delay_micros(ONEWIRE_TIMx, 120);
    r = !((GPIOx->IDR >> ONEWIRE_PIN) & 1);
    delay_micros(ONEWIRE_TIMx, 360);
    return r;
}

void write_bit(uint8_t val){
    if(val & 1) {
        GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Clear mode
        GPIOx->MODER |= (0b01 << ONEWIRE_PIN * 2); // Configure as output
        GPIOx->BSRR = (1 << (ONEWIRE_PIN + 16)); // Set to output low
        delay_micros(ONEWIRE_TIMx, 10);
        GPIOx->BSRR = (1 << ONEWIRE_PIN); // Set output high
        delay_micros(ONEWIRE_TIMx, 55);
    }
    else {
        GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Clear mode
        GPIOx->MODER |= (0b01 << ONEWIRE_PIN * 2); // Configure as output
        GPIOx->BSRR = (1 << (ONEWIRE_PIN + 16)); // Set to output low
        delay_micros(ONEWIRE_TIMx, 65);
        GPIOx->BSRR = (1 << ONEWIRE_PIN); // Set output high
        delay_micros(ONEWIRE_TIMx, 5);
    }
}

uint8_t read_bit(void){
    uint8_t r;
    GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Clear mode
    GPIOx->MODER |= (0b01 << ONEWIRE_PIN * 2); // Configure as output
    GPIOx->BSRR = (1 << (ONEWIRE_PIN + 16)); // Set to output low
    delay_micros(ONEWIRE_TIMx, 3);
    GPIOx->MODER &= ~(0b11 << ONEWIRE_PIN * 2); // Configure as input
    delay_micros(ONEWIRE_TIMx, 10);
    r = ((GPIOx->IDR >> ONEWIRE_PIN) & 1);
    delay_micros(ONEWIRE_TIMx, 53);
    return r;
}

void write_byte(uint8_t val){
    uint8_t bitMask;

    for(bitMask = 0x01; bitMask; bitMask <<= 1){
        write_bit((bitMask & val) ? 1 : 0);
    }
}

uint8_t read_byte(void){
    uint8_t bitMask;
    uint8_t r = 0;

    for(bitMask = 0x01; bitMask; bitMask <<= 1){
        if(read_bit()) r |= bitMask;
    }
    return r;
}

void read_rom(uint8_t rom_code[8]){
    init(); // Send initialization sequence

    write_byte(0x33); // Send Read ROM command code
    
    // Read out ROM code
    for(int i = 0; i < 8; i++){
        rom_code[i] = read_byte();
    }

    volatile uint8_t family_code = rom_code[0];
    volatile uint8_t serial_number[6];
    for(int i=0; i < 6; i++){
        serial_number[i] = rom_code[i+1];
    }
    volatile uint8_t crc_code = rom_code[7];

}

void read_scratchpad(uint8_t scratchpad[8]){
    // Send Read Scratchpad command
    write_byte(0xBE);

    for(int i=0; i< 8; i++){
        scratchpad[i] = read_byte();
    }
}