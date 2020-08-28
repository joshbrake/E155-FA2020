// core.s
// Simple STM32F401RE startup: vector table plus reset_handler
// Josh Brake
// jbrake@hmc.edu
// 6/17/20

///////////////////////////////////////////////////////////////////////////////
// Assembly configuration
///////////////////////////////////////////////////////////////////////////////

// Define chip attributes and assembly language used

.syntax unified     // Unified syntax for ARM and THUMB instructions
.cpu cortex-m4      // STM32F401RE is a Cortex M4
.fpu softvfp        // Use software floating-point operations
.thumb              // Using thumb assembly

// Global memory locations. Declare as .global to make them available in
// other files.
.global vtable
.global reset_handler

///////////////////////////////////////////////////////////////////////////////
// Vector table setup
///////////////////////////////////////////////////////////////////////////////

// The actual vector table.
// Includes only the size of the RAM and 'reset' handler for simplicity

// .type directive tells us what the label points to. Usually either %function or %object
.type vtable, %object

// Label for section
vtable:          
// .word places value in 32-bit/4-byte location       
    .word _estack
    .word reset_handler
// .size directive tells assembler how much space that symbol points to
// is using. The "." in the expression ".-<label>" means the current value of
// the location counter
.size vtable, .-vtable 

///////////////////////////////////////////////////////////////////////////////
// reset_handler
///////////////////////////////////////////////////////////////////////////////

// Define reset_handler
.type reset_handler, %function
reset_handler:
    // Set the stack pointer to the end of the stack
    // '_estack' is defined in the linker script
    LDR r0, =_estack
    MOV sp, r0

    // Set some dummy values. When we see these values in our debugger, we'll
    // know that our program is loaded and working properly on the chip.
    LDR  r7, =0xDEADBEEF

    BL main
    BX lr
.size reset_handler, .-reset_handler