# Access Levels: Privileged vs Unprivileged (Cortex-M)

Goal: demonstrate Cortex-M access levels by switching Thread mode to unprivileged using the CONTROL register.

## What this experiment does
- Prints in Thread mode
- Sets `CONTROL.nPRIV = 1` to drop Thread mode to **unprivileged**
- Triggers an interrupt via NVIC + STIR
- Prints inside the ISR (Handler mode), which runs **privileged**
- Returns to Thread mode

## Key concepts exercised
- `CONTROL` register:
  - `nPRIV` bit controls privileged/unprivileged Thread mode
- Thread mode can run privileged or unprivileged
- Handler mode always runs privileged (exceptions/interrupts)

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: SWV/ITM `printf` (via `_write()` → `ITM_SendChar()`)
