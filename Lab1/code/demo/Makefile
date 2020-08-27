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

build: main.c core.s STM32F401RE_simple.ld
	@echo
	@echo "Build production image"
	arm-none-eabi-cpp main.c -o main.i
	arm-none-eabi-gcc -g -S -mcpu=cortex-m4 -mthumb -O0 -o main.s main.i
	arm-none-eabi-as -o core.o core.s
	arm-none-eabi-as -o main.o main.s
	arm-none-eabi-ld -T STM32F401RE_simple.ld core.o main.o -o test.elf
	arm-none-eabi-objcopy -O binary test.elf test.bin

clean:
	@echo
	@echo "Running target clean"
	rm -f *.o
	rm -f *.i
	rm -f *.elf
	rm -f *.bin
