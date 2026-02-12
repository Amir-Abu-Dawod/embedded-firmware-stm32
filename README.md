## Embedded Firmware Experiments on ARM Cortex-M (STM32)
This repository documents hands-on exploration of bare-metal firmware development on ARM Cortex-M3/M4 microcontrollers (STM32), with a strong focus on startup, interrupts, scheduling, and fault analysis.

The work here is intentionally low-level: no HAL abstractions and no RTOS.
The goal is to understand how the processor boots, handles exceptions, schedules work, and fails — and to debug those failures at the register and stack level.

- [Target Platform](#target-platform)
- [What This Repository Explores](#what-this-repository-explores)
- [Core Technical Areas](#core-technical-areas)
- [Project Structure](#project-structure)
- [Engineering Focus](#engineering-focus)
- [Current Implementation (Bare-Metal Scheduler Demo)](#current-implementation-bare-metal-scheduler-demo)

## Target Platform

- Board: STM32F407G-DISC1 (STM32F4 Discovery)
- MCU: STM32F407VG (ARM Cortex-M4)
- Clock Source: HSI (16 MHz)
- Debug Interface: JTAG / SWD

This project targets the STM32F4 Discovery board for all bring-up and experiments.

## What This Repository Explores

- MCU reset-to-main boot flow, including vector tables and startup code
- Exception and interrupt handling, NVIC configuration, and priority/preemption behavior
- Exception entry/exit and stack frame analysis during interrupts and faults
- Preemptive scheduling using SysTick and PendSV, including manual context switching
- Processor fault handling (HardFault, MemManage, BusFault, UsageFault) and crash diagnosis
- Linker-driven memory layout, stack/heap placement, and ELF analysis
- Register-level debugging via JTAG/SWD using OpenOCD and GDB

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
embedded-firmware-stm32/

├── startup/ # Reset handler, vector table, boot sequence

├── linker/ # Custom linker scripts and memory layout

├── interrupts/ # NVIC configuration, IRQs, fault handlers

├── scheduler/ # SysTick, PendSV, context switching

├── debugging/ # Fault analysis and crash investigation

├── peripherals/ # Register-level peripheral access

└── notes/ # Architecture, ABI, and design reasoning

## Engineering Focus
No vendor templates, HAL, or RTOS abstractions

Emphasis on deterministic behavior and correctness

Learn by building, breaking, and analyzing failures

Treat firmware as a system, not isolated functions

Prioritize understanding over convenience

## Current Implementation (Bare-Metal Scheduler Demo)

This repository currently includes a working bare-metal demo featuring:

- Custom startup code and vector table (`startup/`)
- Custom linker script with SRAM/FLASH layout and `.data` relocation (`linker/`)
- Preemptive scheduler using SysTick + PendSV with manual context switching (`scheduler/`)
- Register-level GPIO control for task-visible output (LED toggling) (`peripherals/`)
- Minimal newlib syscall stubs / semihosting hooks for bring-up printing (`syscalls.c`)
- GCC-based build pipeline and OpenOCD workflow (`Makefile`)
