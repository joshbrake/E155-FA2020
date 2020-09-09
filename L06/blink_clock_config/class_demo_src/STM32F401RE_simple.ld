/* STM32F401RE_simple.ld */
/* Simple linker script for STM32F401RE */
/* Josh Brake */
/* jbrake@hmc.edu */
/* 6/17/20 */

/* Define the end of RAM and limit of stack memory */
/* STM32F401xD/E devices feature 96 KB of SRAM (User Manual RM0368 p. 40)*/
/* STM32F401RE has 512 KB of flash (User Manual RM0368 p. 45) */
/* 96 KB = 0x00018000 */
/* 512 KB = 0x00080000
/* RAM starts at address 0x20000000 */
/* Flash starts at 0x08000000 */
_estack = 0x20018000;

MEMORY
{
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 512K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 96K
}