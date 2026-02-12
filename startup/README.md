# Startup & Boot Sequence

This directory contains experiments related to the Cortex-M reset-to-main boot flow.

Focus areas:
- Vector table definition and placement
- Reset_Handler implementation
- Stack initialization
- .data and .bss section initialization
- Transition from reset to main()

All startup code is written without vendor templates to understand the exact sequence executed by the processor after reset.

## What’s implemented here

- Vector table placed in `.isr_vector`
- Weak-alias default handlers for core exceptions and IRQs
- `Reset_Handler` performs:
  - `.data` relocation from FLASH → SRAM (using linker symbols)
  - `.bss` zero initialization
  - `__libc_init_array()` call before `main()`
