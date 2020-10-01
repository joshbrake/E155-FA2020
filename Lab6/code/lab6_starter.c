/**
    Main file
    @file lab6_starter.c
    @author Josh Brake
    @version 1.0 10/1/2020
*/

#include "STM32F401RE.h"
#include <string.h>

#define USART_ID USART2_ID

int main(void) {
    configureFlash();
    configureClock();

    RCC->AHB1ENR.GPIOAEN = 1;
    // Initialize timer
    RCC->APB1ENR |= (1 << 0); // TIM2EN

    initUSART(USART_ID);

    // TODO: Setup 1-Wire

    
    while(1){
        // TODO: Read data from MAX31820 and format temperature to be printed

        // Print out message to serial port
        uint8_t msg[64];
        sprintf(msg, "Temperature is: %d deg. C\n\r", temperature);
        uint8_t i = 0;

        do
        {
            sendChar(USART_ID, msg[i]);
            i += 1;
        } while (msg[i]);
        
        delay_millis(ONEWIRE_TIMx, 500);
    }
}
