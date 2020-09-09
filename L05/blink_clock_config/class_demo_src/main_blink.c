// main_blink.c
// GPIO blink LED with clock configuration
// Josh Brake
// jbrake@hmc.edu
// 9/9/20

#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"
#include "STM32F401RE_FLASH.h"

#define LED_PIN     5
#define DELAY_MS    500

void ms_delay(int ms) {
   while (ms-- > 0) {
      volatile int x=1000;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void) {
    configureFlash();

    /* TODO: Configure MCO1 to:
        1. output PLL clock
        2. Set prescaler to divide by 4
    */


    /* TODO: Configure APB prescalers
        1. Set APB2 (high-speed bus) prescaler to no division
        2. Set APB1 (low-speed bus) to divide by 2.
    */

    // TODO: Call configureClock() (declared in STM32F401RE_RCC.h)
    configureClock();

    // TODO: Turn on clock to GPIOA using GPIOA bitfield structure

    // TODO: Set pinMode for PA8 to be alternate function
    pinMode(GPIO_PA8, GPIO_ALT);

    // Set LED_PIN as output
    pinMode(LED_PIN, GPIO_OUTPUT);

    // Configure LED_PIN for high speed output
    GPIOA->OSPEEDR |= (0b11 << 2*LED_PIN);

    // Blink LED
    while(1) {
        ms_delay(DELAY_MS);
        togglePin(LED_PIN);
    }
    return 0;
}