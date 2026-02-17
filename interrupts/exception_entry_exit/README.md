# Exception Entry/Exit (Thread vs Handler Mode)

Goal: observe Cortex-M exception entry/exit behavior and verify the Thread→Handler→Thread transition.

## What this experiment does
- Prints a message in Thread mode ("before interrupt")
- Triggers an interrupt via NVIC + STIR
- Prints from the ISR (Handler mode)
- Returns to Thread mode and prints ("after interrupt")

## Key concepts exercised
- NVIC interrupt enable (ISER)
- Software-triggered interrupts (STIR)
- Exception entry/exit flow on Cortex-M
- PSP vs MSP behavior by setting CONTROL.SPSEL and PSP

## Notes
This folder is intended to be inspected under a debugger to observe:
- LR/EXC_RETURN on exception entry
- automatic stacking of R0-R3, R12, LR, PC, xPSR
- the active stack pointer (MSP vs PSP) depending on configuration
