extern unsigned int _DATA_ROM_START;
extern unsigned int _DATA_RAM_START;
extern unsigned int _DATA_RAM_END;
extern unsigned int _BSS_START;
extern unsigned int _BSS_END;

#define STACK_TOP 0x20018000    // 96 KB of 
void startup();

/* Define minimal vector table. First entry is the address of the top of the 
 * stack and the second one is the address of the "reset handler" function
 */
unsigned int * myvectors[2] 
/* __attribute (section("section-name")) makes sure that this gets assembled
 * into a section with the name "vectors". This section label is used later
 * in our linker script to make sure these get put in the right spot.
 */
__attribute__ ((section("vectors")))= {
    (unsigned int *)    STACK_TOP,  // stack pointer
    (unsigned int *)    startup     // code entry point
};

void main(); // Function prototype declaration for sort function

void startup()
{
    /* Copy data belonging to the `.data` section from its
     * load time position on flash (ROM) to its run time position
     * in SRAM.
     */
    unsigned int * data_rom_start_p = &_DATA_ROM_START;
    unsigned int * data_ram_start_p = &_DATA_RAM_START;
    unsigned int * data_ram_end_p = &_DATA_RAM_END;

    while(data_ram_start_p != data_ram_end_p)
    {
        *data_ram_start_p = *data_rom_start_p;
        data_ram_start_p++;
        data_rom_start_p++;
    }

    /* Initialize data in the `.bss` section to zeros.
     */
    unsigned int * bss_start_p = &_BSS_START; 
    unsigned int * bss_end_p = &_BSS_END;

    while(bss_start_p != bss_end_p)
    {
        *bss_start_p = 0;
        bss_start_p++;
    }


    /* Call the `main()` function defined in `sort.s`.
     */
    main();
}