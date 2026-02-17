# SVC Immediate Extraction (Cortex-M)

Goal: trigger an SVC exception and extract the SVC immediate value from the calling instruction.

## What this experiment does
- Executes `SVC #8` in Thread mode
- Enters `SVC_Handler` (naked) and captures the active stack pointer
- Decodes the stacked PC to locate the SVC instruction in program memory
- Extracts the SVC immediate and prints it

## Key mechanism
On exception entry, Cortex-M automatically stacks:
R0, R1, R2, R3, R12, LR, PC, xPSR

The stacked PC points to the next instruction after `SVC`. Since SVC is a 16-bit Thumb instruction in this case, the handler subtracts 2 bytes to read the SVC opcode and extracts the immediate value.

## Notes / assumptions
- This version uses MSP for the stack frame passed into C (`MRS R0, MSP`).
  If Thread mode uses PSP, EXC_RETURN decoding is required to select MSP vs PSP.
- Output uses `printf`, requiring semihosting or a `_write()` implementation.
