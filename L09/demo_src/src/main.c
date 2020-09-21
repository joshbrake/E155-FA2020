// main.c

#include "STM32F401RE_FLASH.h"
#include "STM32F401RE_RCC.h"
#include "STM32F401RE_USART.h"

#define USART_ID USART2_ID

void delay_ms(int ms) {
   while (ms-- > 0) {
      volatile int x=1000;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void) {
    // Configure flash and clock
    configureFlash();
    configureClock(); // Set system clock to 84 MHz

    // Initialize USART
    // TODO: Write this function in USART.c
    initUSART(USART_ID);
    
    uint8_t msg[64] = "Replace with your message!\n\r";

    while(1){
        // TODO: Loop through the array of characters and send each one until
        // until you get to the end of the array (null character).

        
        delay_ms(2000);
    }
}