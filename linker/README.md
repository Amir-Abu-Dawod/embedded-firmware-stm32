# Linker Scripts & Memory Layout

This directory explores custom linker scripts and memory ownership on STM32 (ARM Cortex-M).

Focus areas:
- Flash and RAM memory mapping
- Section placement (.text, .data, .bss, stack, heap)
- Linker symbols and relocation
- ELF analysis
- Resolving memory-related faults

The linker is treated as a core firmware component rather than a build afterthought.
