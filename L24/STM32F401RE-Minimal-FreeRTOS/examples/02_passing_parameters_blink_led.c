// 02_passing_parameters_blink_led.c
// This file presents a basic example of passing parameters into a task.
//
// Josh Brake
// jbrake@hmc.edu
// 11/18/20

#include <FreeRTOS.h>
#include "task.h"

///////////////////////////////////////////////////////////////////////////////
// Defines and Macros
///////////////////////////////////////////////////////////////////////////////

#define LED_PIN 5

///////////////////////////////////////////////////////////////////////////////
// Custom Types
///////////////////////////////////////////////////////////////////////////////

// New type to hold information about LED
typedef struct param_led {
   uint32_t delay_ms;
   uint8_t led_pin;
} param_led;

///////////////////////////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////////////////////////

// Create param_led struct to hold delay and pin number for LED.
param_led led_1 = {200, 5}; // delay_ms = 200, led_pin = 5

///////////////////////////////////////////////////////////////////////////////
// Configuration Functions
///////////////////////////////////////////////////////////////////////////////

// Initialize GPIO for LED
void init_gpio()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable PortA clock
    GPIOA->MODER |= GPIO_MODER_MODER5_0; // Configure PA5 as output
}

// Initialize flash wait states to prepare for faster clock speed.
void init_flash()
{
    // Configure flash for 2 wait states and turn on prefetch
    FLASH->ACR |= (2 << FLASH_ACR_LATENCY_Pos | FLASH_ACR_PRFTEN);
}

// Initialize clock to 84 MHz using PLL and update SystemCoreClock variable.
void init_clock()
{
    // Configure APB prescalers
    // 1. Set APB2 (high-speed bus) prescaler to no division
    // 2. Set APB1 (low-speed bus) to divide by 2.
    RCC->CFGR |= (0b000 << RCC_CFGR_PPRE2_Pos | 0b100 << RCC_CFGR_PPRE1_Pos);

    // Turn on and bypass for HSE from ST-LINK
    RCC->CR |= (RCC_CR_HSEBYP | RCC_CR_HSEON);
    while (!((RCC->CR >> RCC_CR_HSERDY_Pos) & 1));

    // Configure PLL
    // Set clock to 84 MHz
    // Output freq = (src_clk) * (N/M) / P
    // (8 MHz) * (336/8) / 4 = 84 MHz
    // M:8, N:336, P:4, Q:4
    // Use HSE as PLLSRC

    RCC->CR &= ~(RCC_CR_PLLON); // Turn off PLL
    while (((RCC->CR >> RCC_CR_PLLRDY_Pos) & 1) != 0); // Wait till PLL is unlocked (e.g., off)

    // Load configuration
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLM);
    RCC->PLLCFGR |= (RCC_CFGR_SW_HSE << RCC_PLLCFGR_PLLSRC_Pos |
                     8 << RCC_PLLCFGR_PLLM_Pos |
                     336 << RCC_PLLCFGR_PLLN_Pos |
                     0b01 << RCC_PLLCFGR_PLLP_Pos |
                     4 << RCC_PLLCFGR_PLLQ_Pos);

    // Enable PLL and wait until it's locked
    RCC->CR |= (RCC_CR_PLLON);
    while (!((RCC->CR >> RCC_CR_PLLRDY_Pos) & 1));

    // Select PLL as clock source
    RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
    while (((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos) != 0b10);

    SystemCoreClock = 84000000;
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions to use in tasks
///////////////////////////////////////////////////////////////////////////////

// Function to toggle LED
void toggleLED(int pin)
{
    uint32_t pin_state = (GPIOA->IDR >> pin) & 1;

    if (pin_state)
        GPIOA->BSRR = (1 << (pin + 16));
    else
        GPIOA->BSRR = (1 << pin);
}

///////////////////////////////////////////////////////////////////////////////
// Tasks
///////////////////////////////////////////////////////////////////////////////

// Task to toggle LED at 1 Hz
static void toggleLedTask(void *pvParameters)
{
    const param_led * led_info = (param_led *) pvParameters;
    const TickType_t xDelay = pdMS_TO_TICKS(led_info->delay_ms);

    while (1)
    {
        /* Simply toggle the LED every xDelay ms, blocking between each toggle. */
        toggleLED(led_info->led_pin);
        vTaskDelay(xDelay);
    }
}

// Main function where initialization is performed and tasks are created.
int main()
{
    // Call initialization functions
    init_flash();   // Set up flash
    init_clock();   // Configure 84 MHz clock rate
    init_gpio();    // Initialize GPIO for LED

    // Create tasks
    const size_t xRegTestStackSize = 250U; // Set value for stack for each task.
    xTaskCreate(toggleLedTask,      // Task function
                "Blink_1",          // Optional name for task
                xRegTestStackSize,  // Task stack size
                (void*)&led_1,      // void pointer to optional parameters
                1,                  // Task priority
                NULL);              // Handle to created task

    // Start the scheduler
    vTaskStartScheduler();

    // Infinite while loop. Should never get here unless the scheduler fails to start.
    while (1);
}
