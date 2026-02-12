# Preemptive Scheduling & Context Switching

This directory implements a simple preemptive task scheduler using the Cortex-M exception model.

Core components:
- SysTick as a system time base
- PendSV for deferred context switching
- Per-task stack initialization
- MSP/PSP management
- Manual context save/restore
- AAPCS-compliant register preservation
- Task blocking and tick-based scheduling

The implementation mirrors core RTOS mechanisms but is built directly on bare-metal principles without external frameworks.

## What’s implemented here

- SysTick configured as 1ms timebase (16MHz HSI assumed)
- PendSV used for deferred context switching
- PSP used for tasks, MSP reserved for scheduler/handlers
- Manual context switch saves/restores R4–R11 on task stacks
- Per-task stack initialization with synthetic exception frame:
  - xPSR Thumb bit set (0x01000000)
  - PC set to task entry
  - LR set to EXC_RETURN (0xFFFFFFFD)
- Basic task states (READY/BLOCKED) with tick-based delay (`task_delay`)
- Idle task when no runnable task exists
- LED toggling tasks to validate scheduling behavior on hardware
