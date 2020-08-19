// main.c
// Simple main loop demo
// Josh Brake
// jbrake@hmc.edu
// 6/19/20

#include <stdint.h> // Include stdint header

int main(void)
{
    uint32_t i;     // Initialize i variable as 32-bit unsigned integer

    while(1)
    {
        i = i + 1;  // Run an infinite loop incrementing i by 1 each execution.
    }
}