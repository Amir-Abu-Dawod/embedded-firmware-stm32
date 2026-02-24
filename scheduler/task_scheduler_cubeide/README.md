# Preemptive Task Scheduler (SysTick + PendSV) — STM32CubeIDE

Goal: implement a minimal preemptive scheduler on Cortex-M using SysTick as the timebase and PendSV for context switching (no RTOS, no HAL).

## What this experiment does
- Creates 4 user tasks + an idle task (each with its own PSP stack)
- Builds an initial synthetic exception frame per task (xPSR/PC/LR + registers)
- Switches Thread mode to use PSP; keeps MSP for exceptions/scheduler
- Uses SysTick to drive periodic scheduling and tick-based delays
- Uses PendSV to perform manual context switching (save/restore R4–R11)
- Validates scheduling via LED toggling patterns on STM32F407G-DISC1

## Key concepts exercised
- MSP vs PSP stack model (Thread mode uses PSP, Handler mode uses MSP)
- AAPCS expectations for register usage and return values
- EXC_RETURN (`0xFFFFFFFD`) for returning to Thread mode using PSP
- SysTick configuration and periodic tick handling
- PendSV as a deferred context switch mechanism
- Task state machine: READY / BLOCKED, tick-based unblock

## Build / Run (STM32CubeIDE)
- Target: STM32F407G-DISC1
- Output: LED toggling on GPIOD (PD12–PD15)
- Optional debug prints via SWV/ITM if enabled in the project

## Debugger Checklist
- Verify CONTROL.SPSEL is set after switching to PSP
- Inspect PSP values per task and confirm stacks are independent
- Stop in PendSV and confirm:
  - R4–R11 saved to outgoing task stack
  - PSP updated to incoming task stack
- Stop in SysTick and confirm tick increments + task unblock transitions
