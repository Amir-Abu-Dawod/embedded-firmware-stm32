# Inline Assembly Basics (GCC + ARM Cortex-M)

Goal: practice GCC inline assembly constraints and low-level ARM instructions in C.

## What this experiment does
- Moves a C value into a CPU register using an input operand constraint
- Reads the Cortex-M CONTROL register into a C variable using an output constraint
- Performs a raw memory load using register operands and an explicit `LDR`

## Key concepts exercised
- GCC inline assembly operands:
  - input operands (`"r"(val)`)
  - output operands (`"=r"(out)`)
- Reading system registers (`MRS CONTROL`)
- Using inline asm with pointers (address passed as register operand)
