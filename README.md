## Embedded Firmware Experiments on ARM Cortex-M (STM32)
This repository documents hands-on exploration of bare-metal firmware development on ARM Cortex-M3/M4 microcontrollers (STM32), with a strong focus on startup, interrupts, scheduling, and fault analysis.

The work here is intentionally low-level: no HAL abstractions and no RTOS.
The goal is to understand how the processor boots, handles exceptions, schedules work, and fails — and to debug those failures at the register and stack level.

## What This Repository Explores
This project investigates core firmware mechanisms that sit below typical application frameworks:

MCU reset-to-main boot flow, including vector tables and startup code

Exception and interrupt handling, NVIC configuration, and priority/preemption behavior

Exception entry/exit and stack frame analysis during interrupts and faults

Preemptive scheduling using SysTick and PendSV, including manual context switching

Processor fault handling (HardFault, MemManage, BusFault, UsageFault) and crash diagnosis

Linker-driven memory layout, stack/heap placement, and ELF analysis

Register-level debugging via JTAG/SWD using OpenOCD and GDB

## Core Technical Areas
Bare-metal firmware in C and inline assembly

ARM Cortex-M exception model and NVIC

SysTick + PendSV-based task scheduling

MSP/PSP stack management and AAPCS-compliant context switching

Custom startup code and linker scripts written from scratch

Memory-mapped peripheral access

Fault analysis using stacked registers and stack frames

Low-level debugging without HAL or RTOS abstractions

## Project Structure


## Engineering Focus
No vendor templates, HAL, or RTOS abstractions

Emphasis on deterministic behavior and correctness

Learn by building, breaking, and analyzing failures

Treat firmware as a system, not isolated functions

Prioritize understanding over convenience

