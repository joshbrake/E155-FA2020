// Standard library includes.
#include <stdint.h>
#include <stdlib.h>
// Vendor-provided device header file.
#include "stm32f4xx.h"

#define TIM TIM2
#define USART USART2
#define DMA_STREAM DMA1_Stream6

const size_t CHAR_ARRAY_SIZE = 231;
const uint8_t CHAR_ARRAY[231] = "\n  __  __  _                    ____        _  \n\ |  \\/  |(_)  ___  _ __  ___  |  _ \\  ___ | |\n\ | |\\/| || | / __|| '__|/ _ \\ | |_) |/ __|| |\n\ | |  | || || (__ | |  | (_) ||  __/ \\__ \\|_|\n\ |_|  |_||_| \\___||_|   \\___/ |_|    |___/(_)\n";

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
    GPIOA->MODER &= ~(GPIO_MODER_MODER2_Msk);
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODER2_Pos);
    // Configure pin modes as ALT function
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk);
    // Configure correct alternate functions (AF07)
    GPIOA->AFR[0] |= (0b0111 << GPIO_AFRL_AFSEL2_Pos | 0b0111 << GPIO_AFRL_AFSEL3_Pos);

    USART->CR1 |= (USART_CR1_UE_Msk); // Enable USART
    USART->CR1 &= ~(USART_CR1_M_Msk); // M=0 corresponds to 8 data bits
    USART->CR2 &= ~(USART_CR2_STOP_Msk); // 0b00 corresponds to 1 stop bit
    USART->CR1 &= ~(USART_CR1_OVER8_Msk); // Set to 16 times sampling freq

    USART->CR3 |= (USART_CR3_DMAT_Msk);
    USART->BRR |= (8 << USART_BRR_DIV_Mantissa_Pos);
    USART->BRR |= (11 << USART_BRR_DIV_Fraction_Pos); // 11/16

    USART->CR1 |= (USART_CR1_TE_Msk); // Enable USART2

    // DMA1 configuration (channel 3 / stream 5).
    // SxCR register:
    // - Memory-to-peripheral
    // - Increment memory ptr, don't increment periph ptr.
    // - 8-bit data size for both source and destination.
    // - High priority (2/3).

    // Reset DMA1 Stream 6
    DMA_STREAM->CR &= ~( DMA_SxCR_CHSEL |
                            DMA_SxCR_PL |
                            DMA_SxCR_MSIZE |
                            DMA_SxCR_PSIZE |
                            DMA_SxCR_PINC |
                            DMA_SxCR_EN );
    // TODO
    // Set up DMA1 Stream 6
    DMA_STREAM->CR |=  ;
    
    // TODO
    // Set DMA source and destination addresses.
    // Source: Address of the character array buffer in memory.

    // Dest.: USART data register
    
    // Set DMA data transfer length (# of samples).

    // Clear USART TC flag
    USART->SR &= ~(USART_SR_TC_Msk);

    // Enable DMA stream.
    DMA_STREAM->CR   |= DMA_SxCR_EN;

    // TIM6 configuration.
    // Set prescaler and autoreload to issue DMA request at 1 Hz
    TIM->PSC  =  0x0000;
    TIM->ARR  =  SystemCoreClock;
    
    // Enable trigger output on timer update events.
    TIM->CR2 &= ~(TIM_CR2_MMS);
    TIM->CR2 |=  (0x2 << TIM_CR2_MMS_Pos);
    TIM->CR2 |= (TIM_CR2_CCDS_Msk); // Set DMA request when update event occurs
    
    // Configure interrupt enable on update event
    TIM->DIER |= (TIM_DIER_UIE_Msk);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Start the timer.
    TIM->CR1 |=  ( TIM_CR1_CEN );

    while (1) {
    }
}

void TIM2_IRQHandler(void) {
    // Clear update interrupt flag
    TIM->SR &= ~(TIM_SR_UIF_Msk);

    // Clear Stream 6 DMA flags
    DMA1->HIFCR = (DMA_HIFCR_CTCIF6_Msk | DMA_HIFCR_CHTIF6_Msk | DMA_HIFCR_CTEIF6_Msk | DMA_HIFCR_CDMEIF6_Msk | DMA_HIFCR_CFEIF6_Msk);
    
    // Reset number of bytes to transmit
    DMA_STREAM->NDTR  = (uint16_t) CHAR_ARRAY_SIZE;
    
    // Re-enable DMA stream.
    DMA_STREAM->CR   |= DMA_SxCR_EN_Msk;
}