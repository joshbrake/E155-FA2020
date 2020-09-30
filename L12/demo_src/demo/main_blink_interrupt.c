// main.c

#include "main.h"

#define DELAY_TIM TIM2
#define LED_PIN 5

// TODO fill in address for NVIC_ISER0
#define NVIC_ISER0 *((uint32_t *) 0xXXXXXXXX)

int main(void) {
    configureFlash();
    configureClock();

    // Configure GPIO pin
    RCC->AHB1ENR.GPIOAEN = 1;
    pinMode(GPIOA, LED_PIN, GPIO_OUTPUT);
    digitalWrite(GPIOA, LED_PIN, GPIO_LOW);

    // Initialize timer
    RCC->APB1ENR |= (1 << 0); // TIM2EN
    initTIM(DELAY_TIM);

    // Enable interrupts
    __enable_irq();

    // TODO Enable interrupts for TIMx
    // (Hint: what bit needs to be configured in the timer registers?)
    DELAY_TIM->XXXX |= (1 << 0);

    // Interrupts
    DELAY_TIM->ARR = 50e3; // Set ARR to 500 ms
    DELAY_TIM->EGR |= 1;     // Force update
    DELAY_TIM->SR &= ~(1 << 0); // Reset UIF
    DELAY_TIM ->CNT = 0; // Reset CNT

    // TODO Enable interrupt (set correct bit in ISER0)
    NVIC_ISER0 |= (1 << XX);

    while(1){
        // TIM2_IRQHandler();
        // delay_millis(TIM2, 1000);
    }

}

void TIM2_IRQHandler(void){
    // TODO handle interrupt
    // 1. Toggle LED_PIN
    // 2. Reset UIF in TIMx

}
