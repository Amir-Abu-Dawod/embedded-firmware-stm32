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
