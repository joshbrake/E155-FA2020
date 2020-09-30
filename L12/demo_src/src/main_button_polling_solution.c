// main.c

#include "main.h"

#define LED_PIN 5
#define BUTTON_PIN 13 // PC13

int main(void) {
    configureFlash();
    configureClock();
    
    // Enable LED as output
    RCC->AHB1ENR.GPIOAEN = 1;
    pinMode(GPIOA, LED_PIN, GPIO_OUTPUT);

    // Enable button as input
    RCC->AHB1ENR.GPIOCEN = 1;
    pinMode(GPIOC, BUTTON_PIN, GPIO_INPUT);

    uint8_t volatile cur_button_state = digitalRead(GPIOC, BUTTON_PIN);
    uint8_t volatile led_state = 0;
    uint8_t volatile prev_button_state = cur_button_state;

    while(1){
        prev_button_state = cur_button_state;
        cur_button_state = digitalRead(GPIOC, BUTTON_PIN);
        if (prev_button_state == 1 && cur_button_state == 0){
            led_state = !led_state;
            digitalWrite(GPIOA, LED_PIN, led_state);
        }
    }
}
