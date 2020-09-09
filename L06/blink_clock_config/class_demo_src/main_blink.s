	.cpu cortex-m4
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main_blink.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.global	ms_delay
	.arch armv7e-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ms_delay, %function
ms_delay:
.LFB0:
	.file 1 "main_blink.c"
	.loc 1 14 23
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #20
	.cfi_def_cfa_offset 24
	add	r7, sp, #0
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
	.loc 1 15 10
	b	.L2
.L5:
.LBB2:
	.loc 1 16 20
	mov	r3, #1000
	str	r3, [r7, #12]
	.loc 1 17 13
	b	.L3
.L4:
	.loc 1 18 10
	.syntax unified
@ 18 "main_blink.c" 1
	nop
@ 0 "" 2
	.thumb
	.syntax unified
.L3:
	.loc 1 17 15
	ldr	r3, [r7, #12]
	subs	r2, r3, #1
	str	r2, [r7, #12]
	.loc 1 17 13
	cmp	r3, #0
	bgt	.L4
.L2:
.LBE2:
	.loc 1 15 13
	ldr	r3, [r7, #4]
	subs	r2, r3, #1
	str	r2, [r7, #4]
	.loc 1 15 10
	cmp	r3, #0
	bgt	.L5
	.loc 1 20 1
	nop
	nop
	adds	r7, r7, #20
	.cfi_def_cfa_offset 4
	mov	sp, r7
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE0:
	.size	ms_delay, .-ms_delay
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
.LFB1:
	.loc 1 22 16
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	add	r7, sp, #0
	.cfi_def_cfa_register 7
	.loc 1 23 5
	bl	configureFlash
	.loc 1 29 37
	ldr	r2, .L8
	.loc 1 29 49
	ldr	r3, [r2, #8]
	orr	r3, r3, #6291456
	str	r3, [r2, #8]
	.loc 1 30 37
	ldr	r2, .L8
	.loc 1 30 52
	ldr	r3, [r2, #8]
	movs	r1, #6
	bfi	r3, r1, #24, #3
	str	r3, [r2, #8]
	.loc 1 36 37
	ldr	r2, .L8
	.loc 1 36 50
	ldr	r3, [r2, #8]
	bfc	r3, #13, #3
	str	r3, [r2, #8]
	.loc 1 37 37
	ldr	r2, .L8
	.loc 1 37 50
	ldr	r3, [r2, #8]
	movs	r1, #4
	bfi	r3, r1, #10, #3
	str	r3, [r2, #8]
	.loc 1 40 5
	bl	configureClock
	.loc 1 43 37
	ldr	r2, .L8
	.loc 1 43 55
	ldr	r3, [r2, #48]
	orr	r3, r3, #1
	str	r3, [r2, #48]
	.loc 1 46 5
	movs	r1, #2
	movs	r0, #8
	bl	pinMode
	.loc 1 49 5
	movs	r1, #1
	movs	r0, #5
	bl	pinMode
	.loc 1 52 38
	ldr	r3, .L8+4
	ldr	r3, [r3, #8]
	ldr	r2, .L8+4
	orr	r3, r3, #3072
	str	r3, [r2, #8]
.L7:
	.loc 1 56 9 discriminator 1
	mov	r0, #500
	bl	ms_delay
	.loc 1 57 9 discriminator 1
	movs	r0, #5
	bl	togglePin
	.loc 1 56 9 discriminator 1
	b	.L7
.L9:
	.align	2
.L8:
	.word	1073887232
	.word	1073872896
	.cfi_endproc
.LFE1:
	.size	main, .-main
.Letext0:
	.file 2 "/home/dev/gcc-arm-none-eabi-9-2020-q2-update/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/dev/gcc-arm-none-eabi-9-2020-q2-update/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "STM32F401RE_GPIO.h"
	.file 5 "STM32F401RE_RCC.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x600
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0xc
	.4byte	.LASF90
	.4byte	.LASF91
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x2
	.byte	0x4f
	.byte	0x1b
	.4byte	0x54
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x5
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x48
	.uleb128 0x5
	.4byte	0x7c
	.uleb128 0x6
	.byte	0x28
	.byte	0x4
	.byte	0x31
	.byte	0x9
	.4byte	0x119
	.uleb128 0x7
	.4byte	.LASF11
	.byte	0x4
	.byte	0x32
	.byte	0x17
	.4byte	0x88
	.byte	0
	.uleb128 0x7
	.4byte	.LASF12
	.byte	0x4
	.byte	0x33
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF13
	.byte	0x4
	.byte	0x34
	.byte	0x17
	.4byte	0x88
	.byte	0x8
	.uleb128 0x7
	.4byte	.LASF14
	.byte	0x4
	.byte	0x35
	.byte	0x17
	.4byte	0x88
	.byte	0xc
	.uleb128 0x8
	.ascii	"IDR\000"
	.byte	0x4
	.byte	0x36
	.byte	0x17
	.4byte	0x88
	.byte	0x10
	.uleb128 0x8
	.ascii	"ODR\000"
	.byte	0x4
	.byte	0x37
	.byte	0x17
	.4byte	0x88
	.byte	0x14
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x4
	.byte	0x38
	.byte	0x17
	.4byte	0x88
	.byte	0x18
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0x39
	.byte	0x17
	.4byte	0x88
	.byte	0x1c
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x4
	.byte	0x3a
	.byte	0x17
	.4byte	0x88
	.byte	0x20
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0x4
	.byte	0x3b
	.byte	0x17
	.4byte	0x88
	.byte	0x24
	.byte	0
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0x4
	.byte	0x3c
	.byte	0x3
	.4byte	0x8d
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0x1e
	.byte	0x9
	.4byte	0x1ef
	.uleb128 0x9
	.4byte	.LASF20
	.byte	0x5
	.byte	0x1f
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1f
	.byte	0
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x5
	.byte	0x20
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1e
	.byte	0
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x5
	.byte	0x22
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x5
	.byte	0x18
	.byte	0
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x5
	.byte	0x23
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x8
	.byte	0x10
	.byte	0
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x5
	.byte	0x24
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0xf
	.byte	0
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x5
	.byte	0x25
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0xe
	.byte	0
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x5
	.byte	0x26
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0xd
	.byte	0
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0x5
	.byte	0x27
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0xc
	.byte	0
	.uleb128 0x9
	.4byte	.LASF28
	.byte	0x5
	.byte	0x29
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.4byte	.LASF29
	.byte	0x5
	.byte	0x2a
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x6
	.byte	0
	.uleb128 0x9
	.4byte	.LASF30
	.byte	0x5
	.byte	0x2b
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x5
	.byte	0
	.uleb128 0x9
	.4byte	.LASF31
	.byte	0x5
	.byte	0x2c
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x4
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF32
	.byte	0x5
	.byte	0x2e
	.byte	0x3
	.4byte	0x125
	.uleb128 0x5
	.4byte	0x1ef
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0x30
	.byte	0x9
	.4byte	0x25a
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x5
	.byte	0x31
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x6
	.byte	0x1a
	.byte	0
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x5
	.byte	0x32
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x9
	.byte	0x11
	.byte	0
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x5
	.byte	0x34
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x2
	.byte	0xe
	.byte	0
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x5
	.byte	0x36
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x9
	.byte	0
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x5
	.byte	0x38
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x4
	.byte	0x4
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x5
	.byte	0x3a
	.byte	0x3
	.4byte	0x200
	.uleb128 0x5
	.4byte	0x25a
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0x3c
	.byte	0x9
	.4byte	0x324
	.uleb128 0xa
	.ascii	"SW\000"
	.byte	0x5
	.byte	0x3d
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x2
	.byte	0x1e
	.byte	0
	.uleb128 0xa
	.ascii	"SWS\000"
	.byte	0x5
	.byte	0x3e
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x2
	.byte	0x1c
	.byte	0
	.uleb128 0x9
	.4byte	.LASF39
	.byte	0x5
	.byte	0x3f
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x4
	.byte	0x18
	.byte	0
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x5
	.byte	0x41
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x3
	.byte	0x13
	.byte	0
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x5
	.byte	0x42
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x3
	.byte	0x10
	.byte	0
	.uleb128 0x9
	.4byte	.LASF42
	.byte	0x5
	.byte	0x43
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x5
	.byte	0xb
	.byte	0
	.uleb128 0x9
	.4byte	.LASF43
	.byte	0x5
	.byte	0x44
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x2
	.byte	0x9
	.byte	0
	.uleb128 0x9
	.4byte	.LASF44
	.byte	0x5
	.byte	0x45
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x8
	.byte	0
	.uleb128 0x9
	.4byte	.LASF45
	.byte	0x5
	.byte	0x46
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x3
	.byte	0x5
	.byte	0
	.uleb128 0x9
	.4byte	.LASF46
	.byte	0x5
	.byte	0x47
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x3
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.4byte	.LASF47
	.byte	0x5
	.byte	0x48
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x2
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x5
	.byte	0x49
	.byte	0x3
	.4byte	0x26b
	.uleb128 0x5
	.4byte	0x324
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0x4b
	.byte	0x9
	.4byte	0x3cf
	.uleb128 0x9
	.4byte	.LASF49
	.byte	0x5
	.byte	0x4c
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1f
	.byte	0
	.uleb128 0x9
	.4byte	.LASF50
	.byte	0x5
	.byte	0x4d
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1e
	.byte	0
	.uleb128 0x9
	.4byte	.LASF51
	.byte	0x5
	.byte	0x4e
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1d
	.byte	0
	.uleb128 0x9
	.4byte	.LASF52
	.byte	0x5
	.byte	0x4f
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1c
	.byte	0
	.uleb128 0x9
	.4byte	.LASF53
	.byte	0x5
	.byte	0x50
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x1b
	.byte	0
	.uleb128 0x9
	.4byte	.LASF54
	.byte	0x5
	.byte	0x52
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x18
	.byte	0
	.uleb128 0x9
	.4byte	.LASF55
	.byte	0x5
	.byte	0x54
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x13
	.byte	0
	.uleb128 0x9
	.4byte	.LASF56
	.byte	0x5
	.byte	0x57
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0xa
	.byte	0
	.uleb128 0x9
	.4byte	.LASF57
	.byte	0x5
	.byte	0x58
	.byte	0x17
	.4byte	0x88
	.byte	0x4
	.byte	0x1
	.byte	0x9
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF58
	.byte	0x5
	.byte	0x5a
	.byte	0x3
	.4byte	0x335
	.uleb128 0x5
	.4byte	0x3cf
	.uleb128 0x6
	.byte	0x90
	.byte	0x5
	.byte	0x5c
	.byte	0x9
	.4byte	0x589
	.uleb128 0x8
	.ascii	"CR\000"
	.byte	0x5
	.byte	0x5d
	.byte	0x14
	.4byte	0x1fb
	.byte	0
	.uleb128 0x7
	.4byte	.LASF59
	.byte	0x5
	.byte	0x5e
	.byte	0x19
	.4byte	0x266
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF60
	.byte	0x5
	.byte	0x5f
	.byte	0x16
	.4byte	0x330
	.byte	0x8
	.uleb128 0x8
	.ascii	"CIR\000"
	.byte	0x5
	.byte	0x60
	.byte	0x15
	.4byte	0x88
	.byte	0xc
	.uleb128 0x7
	.4byte	.LASF61
	.byte	0x5
	.byte	0x61
	.byte	0x15
	.4byte	0x88
	.byte	0x10
	.uleb128 0x7
	.4byte	.LASF62
	.byte	0x5
	.byte	0x62
	.byte	0x15
	.4byte	0x88
	.byte	0x14
	.uleb128 0x7
	.4byte	.LASF63
	.byte	0x5
	.byte	0x63
	.byte	0x15
	.4byte	0x88
	.byte	0x18
	.uleb128 0x7
	.4byte	.LASF64
	.byte	0x5
	.byte	0x64
	.byte	0xc
	.4byte	0x7c
	.byte	0x1c
	.uleb128 0x7
	.4byte	.LASF65
	.byte	0x5
	.byte	0x65
	.byte	0x15
	.4byte	0x88
	.byte	0x20
	.uleb128 0x7
	.4byte	.LASF66
	.byte	0x5
	.byte	0x66
	.byte	0x15
	.4byte	0x88
	.byte	0x24
	.uleb128 0x7
	.4byte	.LASF67
	.byte	0x5
	.byte	0x67
	.byte	0xc
	.4byte	0x589
	.byte	0x28
	.uleb128 0x7
	.4byte	.LASF68
	.byte	0x5
	.byte	0x68
	.byte	0x19
	.4byte	0x3db
	.byte	0x30
	.uleb128 0x7
	.4byte	.LASF69
	.byte	0x5
	.byte	0x69
	.byte	0x15
	.4byte	0x88
	.byte	0x34
	.uleb128 0x7
	.4byte	.LASF70
	.byte	0x5
	.byte	0x6a
	.byte	0x15
	.4byte	0x88
	.byte	0x38
	.uleb128 0x7
	.4byte	.LASF71
	.byte	0x5
	.byte	0x6b
	.byte	0xc
	.4byte	0x7c
	.byte	0x3c
	.uleb128 0x7
	.4byte	.LASF72
	.byte	0x5
	.byte	0x6c
	.byte	0x15
	.4byte	0x88
	.byte	0x40
	.uleb128 0x7
	.4byte	.LASF73
	.byte	0x5
	.byte	0x6d
	.byte	0x15
	.4byte	0x88
	.byte	0x44
	.uleb128 0x7
	.4byte	.LASF74
	.byte	0x5
	.byte	0x6e
	.byte	0xc
	.4byte	0x589
	.byte	0x48
	.uleb128 0x7
	.4byte	.LASF75
	.byte	0x5
	.byte	0x6f
	.byte	0x15
	.4byte	0x88
	.byte	0x50
	.uleb128 0x7
	.4byte	.LASF76
	.byte	0x5
	.byte	0x70
	.byte	0x15
	.4byte	0x88
	.byte	0x54
	.uleb128 0x7
	.4byte	.LASF77
	.byte	0x5
	.byte	0x71
	.byte	0x15
	.4byte	0x88
	.byte	0x58
	.uleb128 0x7
	.4byte	.LASF78
	.byte	0x5
	.byte	0x72
	.byte	0xc
	.4byte	0x7c
	.byte	0x5c
	.uleb128 0x7
	.4byte	.LASF79
	.byte	0x5
	.byte	0x73
	.byte	0x15
	.4byte	0x88
	.byte	0x60
	.uleb128 0x7
	.4byte	.LASF80
	.byte	0x5
	.byte	0x74
	.byte	0x15
	.4byte	0x88
	.byte	0x64
	.uleb128 0x7
	.4byte	.LASF81
	.byte	0x5
	.byte	0x75
	.byte	0xc
	.4byte	0x589
	.byte	0x68
	.uleb128 0x7
	.4byte	.LASF82
	.byte	0x5
	.byte	0x76
	.byte	0x15
	.4byte	0x88
	.byte	0x70
	.uleb128 0x8
	.ascii	"CSR\000"
	.byte	0x5
	.byte	0x77
	.byte	0x15
	.4byte	0x88
	.byte	0x74
	.uleb128 0x7
	.4byte	.LASF83
	.byte	0x5
	.byte	0x78
	.byte	0xc
	.4byte	0x589
	.byte	0x78
	.uleb128 0x7
	.4byte	.LASF84
	.byte	0x5
	.byte	0x79
	.byte	0x15
	.4byte	0x88
	.byte	0x80
	.uleb128 0x7
	.4byte	.LASF85
	.byte	0x5
	.byte	0x7a
	.byte	0x15
	.4byte	0x88
	.byte	0x84
	.uleb128 0x7
	.4byte	.LASF86
	.byte	0x5
	.byte	0x7b
	.byte	0xc
	.4byte	0x599
	.byte	0x88
	.uleb128 0x7
	.4byte	.LASF87
	.byte	0x5
	.byte	0x7c
	.byte	0x15
	.4byte	0x88
	.byte	0x8c
	.byte	0
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x599
	.uleb128 0xc
	.4byte	0x75
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x5a9
	.uleb128 0xc
	.4byte	0x75
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF88
	.byte	0x5
	.byte	0x7d
	.byte	0x3
	.4byte	0x3e0
	.uleb128 0xd
	.4byte	.LASF92
	.byte	0x1
	.byte	0x16
	.byte	0x5
	.4byte	0x69
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.4byte	.LASF93
	.byte	0x1
	.byte	0xe
	.byte	0x6
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xf
	.ascii	"ms\000"
	.byte	0x1
	.byte	0xe
	.byte	0x13
	.4byte	0x69
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x10
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x11
	.ascii	"x\000"
	.byte	0x1
	.byte	0x10
	.byte	0x14
	.4byte	0x70
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF58:
	.ascii	"AHB1ENR_bits\000"
.LASF48:
	.ascii	"CFGR_bits\000"
.LASF65:
	.ascii	"APB1RSTR\000"
.LASF14:
	.ascii	"PURPDR\000"
.LASF69:
	.ascii	"AHB2ENR\000"
.LASF72:
	.ascii	"APB1ENR\000"
.LASF45:
	.ascii	"MCO1PRE\000"
.LASF2:
	.ascii	"short int\000"
.LASF82:
	.ascii	"BDCR\000"
.LASF85:
	.ascii	"PLLI2SCFGR\000"
.LASF29:
	.ascii	"PLLRDY\000"
.LASF92:
	.ascii	"main\000"
.LASF43:
	.ascii	"MCO1\000"
.LASF47:
	.ascii	"MCO2\000"
.LASF9:
	.ascii	"__uint32_t\000"
.LASF80:
	.ascii	"APB2LPENR\000"
.LASF84:
	.ascii	"SSCGR\000"
.LASF33:
	.ascii	"PLLM\000"
.LASF34:
	.ascii	"PLLN\000"
.LASF35:
	.ascii	"PLLP\000"
.LASF24:
	.ascii	"HSEON\000"
.LASF77:
	.ascii	"AHB3LPENR\000"
.LASF71:
	.ascii	"RESERVED2\000"
.LASF89:
	.ascii	"GNU C17 9.3.1 20200408 (release) -mcpu=cortex-m4 -m"
	.ascii	"thumb -mfloat-abi=soft -march=armv7e-m -g -O0\000"
.LASF74:
	.ascii	"RESERVED3\000"
.LASF39:
	.ascii	"HPRE\000"
.LASF81:
	.ascii	"RESERVED5\000"
.LASF23:
	.ascii	"HSICAL\000"
.LASF83:
	.ascii	"RESERVED6\000"
.LASF86:
	.ascii	"RESERVED7\000"
.LASF12:
	.ascii	"OTYPER\000"
.LASF87:
	.ascii	"DCKCFGR\000"
.LASF53:
	.ascii	"GPIOEEN\000"
.LASF70:
	.ascii	"AHB3ENR\000"
.LASF6:
	.ascii	"long long int\000"
.LASF91:
	.ascii	"/usr/project/src\000"
.LASF76:
	.ascii	"AHB2LPENR\000"
.LASF4:
	.ascii	"long int\000"
.LASF88:
	.ascii	"RCC_TypeDef\000"
.LASF15:
	.ascii	"BSRR\000"
.LASF11:
	.ascii	"MODER\000"
.LASF28:
	.ascii	"PLLON\000"
.LASF20:
	.ascii	"HSION\000"
.LASF46:
	.ascii	"MCO2PRE\000"
.LASF52:
	.ascii	"GPIODEN\000"
.LASF55:
	.ascii	"CRCEN\000"
.LASF21:
	.ascii	"HSIRDY\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF73:
	.ascii	"APB2ENR\000"
.LASF0:
	.ascii	"signed char\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF51:
	.ascii	"GPIOCEN\000"
.LASF10:
	.ascii	"uint32_t\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF62:
	.ascii	"AHB2RSTR\000"
.LASF37:
	.ascii	"PLLQ\000"
.LASF18:
	.ascii	"AFRH\000"
.LASF59:
	.ascii	"PLLCFGR\000"
.LASF17:
	.ascii	"AFRL\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF19:
	.ascii	"GPIO\000"
.LASF38:
	.ascii	"PLLCFGR_bits\000"
.LASF57:
	.ascii	"DMA2EN\000"
.LASF50:
	.ascii	"GPIOBEN\000"
.LASF36:
	.ascii	"PLLSRC\000"
.LASF22:
	.ascii	"HSITRIM\000"
.LASF44:
	.ascii	"I2SSCR\000"
.LASF54:
	.ascii	"GPIOHEN\000"
.LASF66:
	.ascii	"APB2RSTR\000"
.LASF75:
	.ascii	"AHB1LPENR\000"
.LASF64:
	.ascii	"RESERVED0\000"
.LASF67:
	.ascii	"RESERVED1\000"
.LASF30:
	.ascii	"PLLI2SON\000"
.LASF13:
	.ascii	"OSPEEDR\000"
.LASF78:
	.ascii	"RESERVED4\000"
.LASF26:
	.ascii	"HSEBYP\000"
.LASF5:
	.ascii	"long unsigned int\000"
.LASF56:
	.ascii	"DMA1EN\000"
.LASF49:
	.ascii	"GPIOAEN\000"
.LASF32:
	.ascii	"CR_bits\000"
.LASF68:
	.ascii	"AHB1ENR\000"
.LASF27:
	.ascii	"CSSON\000"
.LASF61:
	.ascii	"AHB1RSTR\000"
.LASF42:
	.ascii	"RTCPRE\000"
.LASF25:
	.ascii	"HSERDY\000"
.LASF63:
	.ascii	"AHB3RSTR\000"
.LASF31:
	.ascii	"PLLI2SRDY\000"
.LASF60:
	.ascii	"CFGR\000"
.LASF16:
	.ascii	"LCKR\000"
.LASF90:
	.ascii	"main_blink.c\000"
.LASF79:
	.ascii	"APB1LPENR\000"
.LASF40:
	.ascii	"PPRE1\000"
.LASF41:
	.ascii	"PPRE2\000"
.LASF93:
	.ascii	"ms_delay\000"
	.ident	"GCC: (GNU Arm Embedded Toolchain 9-2020-q2-update) 9.3.1 20200408 (release)"
