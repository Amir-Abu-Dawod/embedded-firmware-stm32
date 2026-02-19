# SVC Operation Dispatch (System Call Style)

Goal: use SVC as a system-call mechanism to execute arithmetic operations inside the SVC handler.

## What this experiment does
- User code invokes `SVC #imm` to request an operation
- SVC handler decodes the SVC immediate from the calling instruction
- Handler extracts arguments from the stacked frame (R0, R1)
- Performs the requested operation
- Writes result back into stacked R0 for return to Thread mode

Operations implemented:
- Addition  (SVC #36)  
- Subtraction (SVC #37)  
- Multiplication (SVC #38)  
- Division (SVC #39)

## Key mechanism
On exception entry, Cortex-M automatically stacks:

R0, R1, R2, R3, R12, LR, PC, xPSR

The stacked PC points to the instruction *after* `SVC`.  
Since SVC is a 16-bit Thumb instruction, the handler subtracts 2 bytes to read the SVC opcode and extract the immediate value.

Arguments are read from stacked R0/R1.  
The return value is written back into stacked R0, following AAPCS.

## Build / Run (STM32CubeIDE)

- Target: STM32F407G-DISC1  
- Build: STM32CubeIDE (Debug configuration)  
- Output: SWV / ITM console

## Output / Debug

`printf` output is routed through **SWV/ITM** by overriding `_write()` to call `ITM_SendChar()` in `syscalls.c`.

Requires:
- Debug trace enabled (TRCENA)
- ITM stimulus port 0 enabled
- SWV configured and started in CubeIDE

Debugger setup:
- Enable **SWV ITM Data Console**
- Enable **Stimulus Port 0**
- Start trace (SWV) before running

## Notes / Assumptions
- Handler uses MSP (`MRS R0, MSP`).  
  If Thread mode uses PSP, EXC_RETURN must be decoded to select MSP vs PSP.
- Demo assumes valid inputs (division by zero is not handled).
- SVC decoding assumes a 16-bit Thumb SVC instruction.

## Debugger Checklist
- Inspect stacked frame: R0–R3, R12, LR, PC, xPSR
- Verify stacked PC points after SVC
- Confirm PC-2 contains the SVC opcode
- Confirm result written to stacked R0 before exception return
