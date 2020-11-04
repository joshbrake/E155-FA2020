// main_blink_low_power.c
// Josh Brake
// jbrake@hmc.edu
// 11/4/20

#include "stm32f4xx.h"

#define LED_PIN 5
#define DELAY_TIM TIM2


int main(void) {
    // Configure GPIO pin
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);

    GPIOA->MODER &= ~(0b11 << LED_PIN*2);
    GPIOA->MODER |= (0x01 << LED_PIN*2);
    
    GPIOA->BSRR = (1 << (LED_PIN + 16));

    // Initialize timer
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIM2EN
    uint32_t psc_div = (uint32_t) ((SystemCoreClock/1e6)-1); // Set prescaler to give 1 µs time base
    DELAY_TIM->PSC = (psc_div - 1); // Set prescaler division factor
    DELAY_TIM->EGR |= TIM_EGR_UG; // Generate an update event to update prescaler value
    DELAY_TIM->CR1 |= TIM_CR1_CEN; // Set CEN = 1

    // Setup timer parameters
    DELAY_TIM->ARR = 1000e3; // Set ARR to 500 ms
    DELAY_TIM->EGR |= TIM_EGR_UG;     // Force update
    DELAY_TIM->SR &= ~TIM_SR_UIF; // Reset UIF
    DELAY_TIM->CNT = 0; // Reset CNT
    
    // Enable global interrupts
    __enable_irq();

    // Enable interrupts for TIMx
    DELAY_TIM->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn); // IRQn 28

    
    while(1){
        // __WFI();
        
        volatile int pin_val = (GPIOA->IDR >> LED_PIN) & 0x1;
        if(pin_val) GPIOA->BSRR = (1 << (LED_PIN + 16));
        else GPIOA->BSRR = (1 << LED_PIN);
    }
}

void TIM2_IRQHandler(){
    DELAY_TIM->SR &= ~TIM_SR_UIF;
}
