# Register-Level Peripheral Access

This directory contains experiments accessing STM32 peripherals directly via memory-mapped registers.

Focus areas:
- GPIO configuration
- Timer configuration
- Direct register manipulation
- Bitwise control and peripheral initialization

All interactions are performed without HAL abstractions to reinforce datasheet-driven development.

## What’s implemented here

- Direct RCC + GPIO register programming for GPIOD (STM32F4)
- LED control via MODER/ODR memory-mapped registers
- Used as observable output for scheduler tasks (blinking patterns)
