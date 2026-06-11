Interrupt-driven UART communication using STM32 HAL for USART handling and a custom C ring buffer for buffering.

Project: Interrupt-driven UART RX ring buffer on STM32F407G-DISC1

-Board: STM32F407G-DISC1
-Peripheral: USART2
-Pins:
-PA2 = USART2_TX
-PA3 = USART2_RX
-Baud rate: 115200
-Format: 8N1, no flow control

Hardware used:
CP210x USB-UART adapter
8-channel logic analyzer
PulseView / sigrok
PuTTY

Project Flow:
  PC/PuTTY sends bytes through USB-UART.
  STM32 receives each byte using USART2 RX interrupt.
  HAL_UART_RxCpltCallback pushes the byte into a fixed-size ring buffer.
  Main loop pops bytes from the ring buffer and transmits them back.
  Logic analyzer captures both RX and TX UART lines and PulseView decodes the echoed data.
