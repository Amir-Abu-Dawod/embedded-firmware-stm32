# Operation Modes: Thread vs Handler (Cortex-M)

Goal: demonstrate the transition between Thread mode and Handler mode on a Cortex-M CPU.

## What this experiment does
- Runs in Thread mode and prints "before interrupt"
- Triggers an interrupt using NVIC enable + STIR software trigger
- Prints from the ISR (Handler mode)
- Returns to Thread mode and prints "after interrupt"

## Key concepts exercised
- Thread mode vs Handler mode execution context
- NVIC enable (ISER) and software pending via STIR
- Exception entry/exit flow and automatic return to Thread mode

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: SWV/ITM `printf` (via `_write()` → `ITM_SendChar()`)

## Notes / Assumptions
- The triggered IRQ number must match the ISR name used by the STM32F407 vector table.
- Recommended: verify the active exception number (IPSR) while stopped in the ISR.
