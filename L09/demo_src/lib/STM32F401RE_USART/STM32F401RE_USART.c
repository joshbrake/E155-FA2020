// STM32F401RE_USART.c
// Source code for USART functions

#include "STM32F401RE_USART.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"

/*
    id2Port takes a USART_ID (index of USART peripheral) and returns a pointer
    to a USART-sized chunk of memory at the correct base address for that
    peripheral.
*/
USART_TypeDef * id2Port(USART_ID){
    USART_TypeDef * USART;
    switch(USART_ID){
        case(USART1_ID) :
            USART = USART1;
            break;
        case(USART2_ID) :
            USART = USART2;
            break;
    }
    return USART;
}

void initUSART(uint8_t USART_ID){
    RCC->AHB1ENR.GPIOAEN = 1; // Enable GPIO port A

    USART_TypeDef * USART = id2Port(USART_ID); // Get pointer to USART peripheral

    switch(USART_ID){
        case USART1_ID :
            RCC->APB2ENR |= (1 << 4); // Set USART1EN

            // Configure pin modes as ALT function
            // USART1_TX on PA9
            // USART1_RX on PA10
            pinMode(GPIOA, GPIO_PA9, GPIO_ALT);
            pinMode(GPIOA, GPIO_PA10, GPIO_ALT);

            GPIOA->AFRH |= (0b111 << 4*2) | (0b111 << 4*1);
            break;
        case USART2_ID :
            RCC->APB1ENR |= (1 << 17); // Set USART1EN

            // Configure pin modes as ALT function
            // USART2_TX on PA2
            // USART2_RX on PA3
            pinMode(GPIOA, GPIO_PA2, GPIO_ALT);
            pinMode(GPIOA, GPIO_PA3, GPIO_ALT);

            // Configure correct alternate functions (AF07)
            GPIOA->AFRL |= (0b111 << 4*3) | (0b111 << 4*2);
            break;
    }

    /* TODO: Configure USART
       Read the datasheet and figure out the procedures. Configure for the following settings:
       * 8 data bits
       * 1 Stop bit
       * 16x oversampling frequency
       * Baud rate of 9.6 Kbps (9600 baud)
    */

}

/*
    sendChar takes USART_ID (index of USART peripheral) and an 8-bit data packet
    and outputs the data packet over the serial interface.
    It should wait for the transmission to be complete to exit the function.
*/
void sendChar(uint8_t USART_ID, uint8_t data){
    USART_TypeDef * USART = id2Port(USART_ID);

    // TODO: Add code to send packet and wait for transmission to complete

}