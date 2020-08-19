SECTIONS
{
    .  = 0x08000000;         /* From 0x08000000, the start of flash memory   */
                             /* This address is mapped to 0x00000000 because */
                             /* BOOT0 = 0 (p. 41 RM0368) */

    .text : 
    {
        *(vectors)          /* Vector table */
        *(.text)            /* Program code */
    }
    .rodata : 
    {
        *(.rodata)          /* Read only data */
    }
    _DATA_ROM_START = .;    /* Store the current location as _DATA_ROM_START */

    .  = 0x20000000;        /* From 0x20000000 */      

    _DATA_RAM_START = .;    /* Store the current location as _DATA_RAM_START */
    .data : AT(_DATA_ROM_START) 
    {
        *(.data)            /* Data memory */
    }
    _DATA_RAM_END = .;

    _BSS_START = .;         /* Indicates where BSS section starts in RAM */
    .bss :
    {
        *(.bss)             /* Zero-filled run time allocate data memory */
    }
    _BSS_END = .;           /* Indicates where BSS section ends in RAM */
}