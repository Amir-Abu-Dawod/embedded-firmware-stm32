# NVIC Pending Interrupt Demo: USART3 IRQ (IRQ39)

Goal: demonstrate NVIC pending behavior by software-pending an IRQ and observing ISR entry without peripheral stimulus.

## What this experiment does
- Sets the pending bit for IRQ39 (USART3) using NVIC ISPR1
- Enables IRQ39 using NVIC ISER1
- NVIC vectors into `USART3_IRQHandler` and prints a message

## Key concepts exercised
- NVIC interrupt banks:
  - IRQ 0–31 use ISER0/ISPR0
  - IRQ 32–63 use ISER1/ISPR1
- Software pending of interrupts via ISPR
- ISR entry is controlled by NVIC pending+enable state (independent of peripheral state)

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: SWV/ITM `printf` (via `_write()` → `ITM_SendChar()`)

## Debugger Checklist
- Verify bit `(39 % 32)` is set in ISPR1
- Verify the same bit is set in ISER1
- Observe ISR entry into `USART3_IRQHandler`
