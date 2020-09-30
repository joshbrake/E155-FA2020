// main.c

#include "main.h"

#define LED_PIN 5
#define BUTTON_PIN 13 // PC13

#define NVIC_ISER1 ((uint32_t *) 0xE000E104UL)
#define SYSCFG_EXTICR4 ((uint32_t *) (0x40013800UL + 0x14UL))

typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_TypeDef;

#define EXTI ((EXTI_TypeDef *) 0x40013C00UL)

int main(void) {
    configureFlash();
    configureClock();
    
    // Enable LED as output
    RCC->AHB1ENR.GPIOAEN = 1;
    pinMode(GPIOA, LED_PIN, GPIO_OUTPUT);

    // Enable button as input
    RCC->AHB1ENR.GPIOCEN = 1;
    pinMode(GPIOC, BUTTON_PIN, GPIO_INPUT);

    // Enable SYSCFG and set EXTICR4 for PC13
    RCC->APB2ENR |= (1 << 14); //SYSCFGEN
    *SYSCFG_EXTICR4 |= (0b0010 << 4*1);

    // Enable interrupts globally
    __enable_irq();

    // Configure interrupt for falling edge of GPIO PC13
    EXTI->IMR |= (1 << BUTTON_PIN); // Configure the mask bit
    EXTI->RTSR &= ~(1 << BUTTON_PIN);// Enable rising edge trigger
    EXTI->FTSR |= (1 << BUTTON_PIN);// Disable rising edge trigger
    *NVIC_ISER1 |= (1 << 8);

    while(1){
        
        // TIM2_IRQHandler();
        // delay_millis(TIM2, 1000);
    }

}

void EXTI15_10_IRQHandler(void){
    // Check that the button EXTI_13 was what triggered our interrupt
    if (EXTI->PR & (1 << BUTTON_PIN)){
        // If so, clear the interrupt
        EXTI->PR |= (1 << BUTTON_PIN);

        // Then toggle the LED
        togglePin(GPIOA, LED_PIN);

    }
}
