# Makefile
# Simple makefile for Lab 1 demo
# Josh Brake
# jbrake@hmc.edu
# 6/22/20

# The @<command> structure allows you to suppress that line being passed to 
# the shell. This is useful when using the flag '-n' or '--just-print' as
# you can do a dry without actually doing anything.

all:
	@echo "Make targets"
	make clean
	make build

build: main_blink.c core.s STM32F401RE_simple.ld \
	   STM32F401RE_RCC.o STM32F401RE_GPIO.o STM32F401RE_FLASH.o
	@echo
	@echo "Build production image"
	arm-none-eabi-cpp main_blink.c -o main_blink.i
	arm-none-eabi-gcc -g -S -mcpu=cortex-m4 -mthumb -O0 -o main_blink.s main_blink.i
	arm-none-eabi-as -o core.o core.s
	arm-none-eabi-as -o main_blink.o main_blink.s
	arm-none-eabi-ld -T STM32F401RE_simple.ld core.o main_blink.o STM32F401RE_GPIO.o STM32F401RE_RCC.o STM32F401RE_FLASH.o -o blink.elf
	arm-none-eabi-objcopy -O binary blink.elf blink.bin

STM32F401RE_GPIO.o: STM32F401RE_GPIO.c
	@echo "Making STM32F401RE_GPIO.o"
	arm-none-eabi-cpp STM32F401RE_GPIO.c -o STM32F401RE_GPIO.i
	arm-none-eabi-gcc -g -S -mcpu=cortex-m4 -mthumb -O0 -o STM32F401RE_GPIO.s STM32F401RE_GPIO.i
	arm-none-eabi-as -o STM32F401RE_GPIO.o STM32F401RE_GPIO.s

STM32F401RE_RCC.o: STM32F401RE_RCC.c
	@echo "Making STM32F401RE_RCC.o"
	arm-none-eabi-cpp STM32F401RE_RCC.c -o STM32F401RE_RCC.i
	arm-none-eabi-gcc -g -S -mcpu=cortex-m4 -mthumb -O0 -o STM32F401RE_RCC.s STM32F401RE_RCC.i
	arm-none-eabi-as -o STM32F401RE_RCC.o STM32F401RE_RCC.s

STM32F401RE_FLASH.o: STM32F401RE_FLASH.c
	@echo "Making STM32F401RE_FLASH.o"
	arm-none-eabi-cpp STM32F401RE_FLASH.c -o STM32F401RE_FLASH.i
	arm-none-eabi-gcc -g -S -mcpu=cortex-m4 -mthumb -O0 -o STM32F401RE_FLASH.s STM32F401RE_FLASH.i
	arm-none-eabi-as -o STM32F401RE_FLASH.o STM32F401RE_FLASH.s	

clean:
	@echo
	@echo "Running target clean"
	rm -f *.o
	rm -f *.i
	rm -f *.elf
	rm -f *.bin
	rm -f STM32*.s
	rm -f main_blink.s
