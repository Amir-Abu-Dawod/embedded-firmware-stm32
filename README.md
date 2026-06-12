## Embedded Firmware Experiments on ARM Cortex-M (STM32)
This repository documents hands-on exploration of bare-metal firmware development on ARM Cortex-M3/M4 microcontrollers (STM32), with a strong focus on startup, interrupts, scheduling, and fault analysis.

The core startup, scheduling, interrupt, and fault-handling experiments are intentionally low-level, with no RTOS and minimal vendor abstraction. Peripheral validation demos may use STM32 HAL for bring-up while focusing on custom buffering, interrupt flow, and hardware verification.
The goal is to understand how the processor boots, handles exceptions, schedules work, and fails — and to debug those failures at the register and stack level.

- [Target Platform](#target-platform)
- [What This Repository Explores](#what-this-repository-explores)
- [Core Technical Areas](#core-technical-areas)
- [Project Structure](#project-structure)
- [Engineering Focus](#engineering-focus)
- [Current Implementation (Bare-Metal Scheduler Demo)](#current-implementation-bare-metal-scheduler-demo)
- [Hardware-Verified UART Demo](#hardware-verified-uart-demo)
- [Build & Flash Workflow](#build--flash-workflow)

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
- Hardware-verified UART communication using RX interrupts, a custom ring buffer, USB-UART adapter, and PulseView logic analyzer decoding

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

├── peripherals/ # Peripheral demos, UART ring buffer, and hardware validation

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

## Hardware-Verified UART Demo

The repository also includes a hardware-verified UART communication demo:

* [`peripherals/uart_interrupt_ring_buffer`](peripherals/uart_interrupt_ring_buffer) — USART2 echo demo using interrupt-driven RX, a custom C ring buffer, USB-UART communication, and PulseView logic analyzer validation.
* RX path: PC/PuTTY → USB-UART → STM32 USART2 RX interrupt → ring buffer.
* TX path: main loop pops bytes from the ring buffer and echoes them back through USART2 TX.
* Hardware verification includes a CP210x USB-UART adapter, 8-channel logic analyzer, PulseView UART decoding, and captured RX/TX waveforms.


## Build & Flash Workflow


### Option 1 — OpenOCD + Telnet (Semihosting)

```
make semi          # Build with semihosting support
make load          # Start OpenOCD server
```
  
In a new terminal (Telnet to OpenOCD port 4444):
```
reset init
flash write_image erase final_sh.elf
reset halt
resume
```

### Option 2 — OpenOCD + GDB

Terminal 1:
```
make               # Build firmware
make load          # Start OpenOCD server
```

Terminal 2:
```
arm-none-eabi-gdb final.elf
target remote localhost:3333
monitor reset init
monitor flash write_image erase final.elf
monitor reset halt
monitor resume
```
