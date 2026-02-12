# Linker Scripts & Memory Layout

This directory explores custom linker scripts and memory ownership on STM32 (ARM Cortex-M).

Focus areas:
- Flash and RAM memory mapping
- Section placement (.text, .data, .bss, stack, heap)
- Linker symbols and relocation
- ELF analysis
- Resolving memory-related faults

The linker is treated as a core firmware component rather than a build afterthought.

## What’s implemented here

- FLASH/SRAM memory regions for STM32F4
- `.isr_vector`, `.text`, `.rodata` in FLASH
- `.data` in SRAM with LMA in FLASH (`AT> FLASH`) and `LOADADDR(.data)` exposed
- `.bss` in SRAM with `_sbss/_ebss` bounds
- Map-file driven iteration during bring-up (see `final.map`)
