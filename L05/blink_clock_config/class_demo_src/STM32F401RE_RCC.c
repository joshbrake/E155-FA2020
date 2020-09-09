// STM32F401RE_RCC.c
// Source code for RCC functions

#include "STM32F401RE_RCC.h"

void configurePLL() {
    /* TODO: Set clock to 48 MHz
     Output freq = (src_clk) * (N/M) / P
     (8 MHz) * (N/M) / P = 42 MHz
     M:XX, N:XX, P:XX
     Use HSE as PLLSRC
    */

    RCC->CR.PLLON = 0; // Turn off PLL
    while (RCC->CR.PLLRDY != 0); // Wait till PLL is unlocked (e.g., off)

    /* TODO: Load configuration with the values shown above
        1. Set PLLSRC
        2. Set M
        3. Set N
        4. Set P
    */

    // TODO: Enable PLL and wait until it's locked (i.e., until PLLRDY goes high)

}

void configureClock(){
    // Turn on and bypass for HSE from ST-LINK
    RCC->CR.HSEBYP = 1;
    RCC->CR.HSEON = 1;
    while(!RCC->CR.HSERDY);
    
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR.SW = SW_PLL;
    while(!RCC->CFGR.SWS == 0b10);
}