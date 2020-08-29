// main_blink.c

#include "STM32F401RE_GPIO.h"

#define LED_PIN     <XX> // TODO: the correct LED pin here
#define DELAY_MS    500

void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=1000;
      while (x-- > 0)
         __asm("nop");
   }
}

int main(void)
{
    // Put setup functions here

    // Test function to blink LED

}