# NVIC Interrupt Priority & Preemption (STM32F4 / Cortex-M4)

Goal: demonstrate NVIC priority behavior and interrupt preemption by forcing a higher-priority IRQ to preempt a lower-priority IRQ.

## What this experiment does
- Programs NVIC IPR registers directly to set priorities for:
  - TIM2 IRQ (lower priority)
  - I2C1 event IRQ (higher priority)
- Pends TIM2 in NVIC (ISPR) and enables both interrupts (ISER)
- Inside `TIM2_IRQHandler`, pends I2C1 to create a nested interrupt scenario

Expected behavior:
- TIM2 handler starts
- I2C1 is pended from within TIM2
- Since I2C1 has higher priority, it should preempt TIM2 and run immediately

## Implementation details
- NVIC registers used:
  - ISER (enable)
  - ISPR (pending)
  - IPR (priority)
- Priority values are written as 8-bit fields, but only the upper implemented bits are used on STM32F4.

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: SWV/ITM `printf` (via `_write()` → `ITM_SendChar()`)

## Debugger Checklist
- Confirm IPR byte lanes for IRQ 28 and 31
- Observe handler entry order:
  - TIM2 prints first
  - I2C1 prints while TIM2 is still active (preemption)
- Inspect IPSR / active exception number during nesting
