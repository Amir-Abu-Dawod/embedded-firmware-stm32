# Fault Generation + Stacked Frame Decode (Cortex-M)

Goal: deliberately trigger a configurable fault and inspect the exception context (stacked registers + fault status).

## What this experiment does
- Enables configurable faults in SHCSR:
  - MemManage, BusFault, UsageFault
- Deliberately branches to an invalid function pointer target to trigger a fault
- In `UsageFault_Handler`, captures the stack frame and prints:
  - fault status (UFSR)
  - stacked registers: R0–R3, R12, LR, PC, xPSR

## Fault mechanism used
The branch target is not a valid Thumb address (bit0 is not set), which triggers a UsageFault (invalid state) on Cortex-M.

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: SWV/ITM `printf` (via `_write()` → `ITM_SendChar()`)

## Debugger Checklist
- Confirm SHCSR enables the configurable faults (bits 16–18)
- Stop inside `UsageFault_Handler_c` and inspect:
  - stacked PC (where execution attempted to go)
  - stacked xPSR (Thumb state)
  - UFSR bits (expect INVSTATE for invalid Thumb state)
