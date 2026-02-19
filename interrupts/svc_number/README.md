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

The stacked PC points to the next instruction after `SVC`.  
Since SVC is a 16-bit Thumb instruction in this case, the handler subtracts 2 bytes to read the SVC opcode and extract the immediate value.

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
- SVC decoding assumes a 16-bit Thumb SVC instruction.

## Debugger Checklist
- Inspect stacked frame: R0–R3, R12, LR, PC, xPSR
- Verify stacked PC points after SVC
- Confirm PC-2 contains the SVC opcode
