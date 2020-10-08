// STM32F401RE_USART.c
// Source code for USART functions

#include "STM32F401RE_USART.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"
#include "UARTRingBuffer.h"

USART_TypeDef * id2Port(uint32_t USART_ID){
    USART_TypeDef * USART;
    switch(USART_ID){
        case(USART1_ID) :
            USART = USART1;
            break;
        case(USART2_ID) :
            USART = USART2;
            break;
        default :
            USART = 0;
    }
    return USART;
}

USART_TypeDef * initUSART(uint8_t USART_ID, uint32_t baud_rate){
    RCC->AHB1ENR.GPIOAEN = 1; // Enable GPIO port A

    USART_TypeDef * USART = id2Port(USART_ID);

    switch(USART_ID){
        case USART1_ID :
            RCC->APB2ENR |= (1 << 4); // Set USART1EN

            // Configure pin modes as ALT function
            pinMode(GPIOA, GPIO_PA9, GPIO_ALT); // TX
            pinMode(GPIOA, GPIO_PA10, GPIO_ALT); // RX

            GPIOA->AFRH |= (0b111 << 4*2) | (0b111 << 4*1);
            break;
        case USART2_ID :
            RCC->APB1ENR |= (1 << 17); // Set USART1EN

            // Configure pin modes as ALT function
            pinMode(GPIOA, GPIO_PA2, GPIO_ALT); // TX
            pinMode(GPIOA, GPIO_PA3, GPIO_ALT); // RX

            // Configure correct alternate functions (AF07)
            GPIOA->AFRL |= (0b111 << 4*3) | (0b111 << 4*2);
            break;
    }

    USART->CR1.UE = 1; // Enable USART
    USART->CR1.M = 0; // M=0 corresponds to 8 data bits
    USART->CR2.STOP = 0b00; // 0b00 corresponds to 1 stop bit
    USART->CR1.OVER8 = 0; // Set to 16 times sampling freq

    // Set baud rate to 9.6 kbps
    // Tx/Rx baud = (f_CK)/(8*(2-OVER8)*USARTDIV) = Tx/Rx baud = (f_CK)/(16*USARTDIV)
    // f_CK = 84e6 Hz on APB2 (USART1) or 42e6 on APB1 (USART2)
    // USARTDIV = 546.875 should be in BRR
    // 546 = 0x0222
    // 0.875 = 7/8 = 0b1110
    // DIV_Mantissa = 0x222
    // DIV_Fraction = 0b111

    if(USART_ID == USART1_ID){
        if (baud_rate == 9600){
            USART->BRR.DIV_Mantissa = 546;
            USART->BRR.DIV_Fraction = 0b1110;
        } else {
            // Default to 115200
            USART->BRR.DIV_Mantissa = 45;
            USART->BRR.DIV_Fraction = 0b1001;
        }

    }
    else if (USART_ID == USART2_ID){
        if (baud_rate == 9600){
            USART->BRR.DIV_Mantissa = 273;
            USART->BRR.DIV_Fraction = 0b0111;
        } else {
            // Default to 115200
            USART->BRR.DIV_Mantissa = 22;
            USART->BRR.DIV_Fraction = 0b1101;
        }
    }

    USART->CR1.TE = 1; // Enable transmission
    USART->CR1.RE = 1; // Enable reception

    return USART;
}

void sendChar(USART_TypeDef * USART, uint8_t data){
    while(!USART->SR.TXE);
    USART->DR.DR = data;
    while(!USART->SR.TC);
}

void sendString(USART_TypeDef * USART, uint8_t * charArray){

    uint32_t i = 0;
    do{
        sendChar(USART, charArray[i]);
        i++;
    }
    while(charArray[i] != 0);
}

uint8_t readChar(USART_TypeDef * USART){
    if(is_data_available()){
        uint8_t data = read_char_buffer();
        return data;
    } else {
        return 0;
    }

}

void readString(USART_TypeDef * USART, uint8_t * charArray){
    uint32_t i = 0;
    do{
        charArray[i] = readChar(USART);
        i++;
    }
    while(is_data_available());
}