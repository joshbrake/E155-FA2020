// 03_multiple_tasks_print.c
// This file presents a basic example of having multiple tasks and printing to
// the terminal over UART.
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
#define USART USART2
#define UART_DELAY_MS 2000

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

// Strings to print from tasks.
const uint8_t str1[64] = "Hello from Task 1.\n";
const uint8_t str2[64] = "Hello from Task 2.\n";

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

// Initialize and configure USART
void init_uart() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  // Configure PA2 and PA3 as alternate functions USART2
  GPIOA->MODER  &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
  GPIOA->MODER  |= (0b10 << GPIO_MODER_MODER2_Pos | 0b10 << GPIO_MODER_MODER3_Pos);
  GPIOA->AFR[0] |= (0b0111 << GPIO_AFRL_AFSEL2_Pos | 0b0111 << GPIO_AFRL_AFSEL3_Pos);

  USART->CR1 |= (USART_CR1_UE);
  USART->CR1 &= ~(USART_CR1_M | USART_CR1_OVER8);
  USART->CR2 &= ~(USART_CR2_STOP);

  // Set baud rate to 115200
  USART->BRR |= (22 << USART_BRR_DIV_Mantissa_Pos | 13 << USART_BRR_DIV_Fraction_Pos);
  USART->CR1 |= (USART_CR1_TE | USART_CR1_RE);
}

// Simple function to send characters over USART.
void sendChar(uint8_t data){
    USART->DR = (data & USART_DR_DR);
    while(!((USART->SR >> USART_SR_TC_Pos) & 1));
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

// Task to toggle LED
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

// Task to print string over USART
static void printStringTask(void *pvParameters) {
  uint8_t * str = (uint8_t *) pvParameters;
  const TickType_t xDelay = pdMS_TO_TICKS(UART_DELAY_MS);
  int i = 0;

  while(1) {
    do {
      sendChar(str[i]);
      i++;
    }
    while(str[i] != 0);
    
    i = 0;

    vTaskDelay(xDelay);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////

// Main function where initialization is performed and tasks are created.
int main()
{
    // Call initialization functions
    init_flash();   // Set up flash
    init_clock();   // Configure 84 MHz clock rate
    init_gpio();    // Initialize GPIO for LED
    init_uart();    // Initialize UART

    // Create tasks
    const size_t xRegTestStackSize = 250U; // Set value for stack for each task.
    xTaskCreate(toggleLedTask,      // Task function
                "Blink_1",          // Optional name for task
                xRegTestStackSize,  // Task stack size
                (void*)&led_1,      // void pointer to optional parameters
                1,                  // Task priority
                NULL);              // Handle to created task

    xTaskCreate(printStringTask, "Print_Test1", xRegTestStackSize, (void*)&str1, 3, NULL);
    xTaskCreate(printStringTask, "Print_Test2", xRegTestStackSize, (void*)&str2, 2, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Infinite while loop. Should never get here unless the scheduler fails to start.
    while (1);
}
