#/bin/bash

arm-none-eabi-gdb -tui --eval-command="target extended-remote host.docker.internal:3333" -ex "load" -ex "layout asm" -ex "layout reg"  blink.elf