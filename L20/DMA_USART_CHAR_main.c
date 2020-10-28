// Standard library includes.
#include <stdint.h>
#include <stdlib.h>
// Vendor-provided device header file.
#include "stm32f4xx.h"

#define TIM TIM2
#define USART USART2
// 32-character array
const size_t CHAR_ARRAY_SIZE = 20;
const uint8_t CHAR_ARRAY[20] = "This is a DMA Test!\n";

/**
 * Main program.
 */
int main(void) {
    // Enable peripherals: GPIOA, DMA, TIM2.
    RCC->AHB1ENR  |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA1EN);
    RCC->APB1ENR  |= (RCC_APB1ENR_TIM2EN);

    // Configure USART2
    RCC->APB1ENR |= (RCC_APB1ENR_USART2EN); // Set USART2EN
    // Set PA2 to ALT function
    GPIOA->MODER &= ~(GPIO_MODER_MODER2);
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODER2_Pos);
    // Configure pin modes as ALT function
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2 | GPIO_AFRL_AFSEL3);
    // Configure correct alternate functions (AF07)
    GPIOA->AFR[0] |= (0b0111 << GPIO_AFRL_AFSEL2_Pos | 0b0111 << GPIO_AFRL_AFSEL3_Pos);

    USART->CR1 |= (USART_CR1_UE); // Enable USART
    USART->CR1 &= ~(USART_CR1_M); // M=0 corresponds to 8 data bits
    USART->CR2 &= ~(USART_CR2_STOP); // 0b00 corresponds to 1 stop bit
    USART->CR1 &= ~(USART_CR1_OVER8); // Set to 16 times sampling freq

    USART->BRR |= (8 << USART_BRR_DIV_Mantissa_Pos);
    USART->BRR |= (11 << USART_BRR_DIV_Fraction_Pos); // 11/16

    USART->CR1 |= (USART_CR1_TE); // Enable USART2

    // DMA1 configuration (channel 3 / stream 1).
    // SxCR register:
    // - Memory-to-peripheral
    // - Circular mode enabled.
    // - Increment memory ptr, don't increment periph ptr.
    // - 8-bit data size for both source and destination.
    // - High priority (2/3).

    // Reset DMA1 Stream 1
    DMA1_Stream1->CR &= ~( DMA_SxCR_CHSEL |
                            DMA_SxCR_PL |
                            DMA_SxCR_MSIZE |
                            DMA_SxCR_PSIZE |
                            DMA_SxCR_PINC |
                            DMA_SxCR_EN );
    // Set up DMA1 Stream 5
    DMA1_Stream1->CR |=  ( ( 0x2 << DMA_SxCR_PL_Pos ) |
                            ( 0x0 << DMA_SxCR_MSIZE_Pos ) |
                            ( 0x0 << DMA_SxCR_PSIZE_Pos ) |
                            ( 0x3 << DMA_SxCR_CHSEL_Pos ) |
                            DMA_SxCR_MINC |
                            DMA_SxCR_CIRC |
                            ( 0x1 << DMA_SxCR_DIR_Pos ) );
    
    // Set DMA source and destination addresses.
    // Source: Address of the character array buffer in memory.
    DMA1_Stream1->M0AR  = (uint32_t) &CHAR_ARRAY;
    // Dest.: USART data register
    DMA1_Stream1->PAR   = (uint32_t) &(USART->DR);
    // Set DMA data transfer length (# of samples).
    DMA1_Stream1->NDTR  = (uint16_t) CHAR_ARRAY_SIZE;

    // Enable DMA1 Stream 5.
    DMA1_Stream1->CR   |= ( DMA_SxCR_EN_Msk );

    // TIM2 configuration.
    // Set prescaler and autoreload to issue DMA request at 10 Hz
    TIM->PSC  =  0x0000;
    TIM->ARR  =  SystemCoreClock/10;
    
    // Enable trigger output on timer update events.
    TIM->CR2 &= ~(TIM_CR2_MMS);
    TIM->CR2 |=  ( 0x2 << TIM_CR2_MMS_Pos);
    TIM->CR2 |= (TIM_CR2_CCDS); // Set DMA request when update event occurs
    
    // Setup DMA request on update event for timer
    TIM->DIER |= (TIM_DIER_UDE);

    // Start the timer.
    TIM->CR1 |=  ( TIM_CR1_CEN );

    while (1) {
    }
}