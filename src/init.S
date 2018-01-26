	.section .init_code, "ax"

	.extern image_main
	.extern stack_top

	.global start

#include "asic_types.h"

@--------------------------------------

@ The Cortex-M4 in the netX90 is a THUMB-only CPU.
@ All others start in 32 bit mode.
#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90_MPW_APP
	.syntax unified
	.thumb
#else
	.arm
#endif


    .func start, start
    .type start, STT_FUNC
start:
	@ Set own stack position.
	ldr     r2, =stack_top
	mov     sp, r2

	@ The netX90 APP CPU runs from the flash.
#if ASIC_TYP==ASIC_TYP_NETX90_MPW_APP
	@ copy the data section
	ldr     r2, =__SECTION_DATA_LOADADDR__
	ldr     r3, =__SECTION_DATA_START__
	ldr     r4, =__SECTION_DATA_END__

	cmp     r3, r4
	bcs     copy_data_end
copy_data:
	ldr     r5, [r2]
	str     r5, [r3], #4
	adds    r2, #4
	cmp     r3, r4
	blo     copy_data
copy_data_end:
#endif

	@ Clear the .bss section (zero init).
	mov     r2, #0
	ldr     r3, =__bss_start__
	ldr     r4, =__bss_end__
clear_bss:
	str     r2, [r3], #4
	cmp     r3, r4
	bmi     clear_bss

	b       image_main
    .endfunc

@--------------------------------------

  .end

