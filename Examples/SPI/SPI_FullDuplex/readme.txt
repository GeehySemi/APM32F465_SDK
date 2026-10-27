/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.0
 *
 * @date        2023-03-08
 *
 */

&par Example Description

This example shows how to use one board  SPI Peripheral  to  transfer data.
Press KEY1 to send data from SPI1 to SPI2, if communication success,
LED2 will turn on.  The data will be shown on serial assistant trough usart1.
Press KEY2 to use SPI1 to SPI2 to Realize full-duplex transmission.
if communication success, LED3 will turn on.
The data will be shown on serial assistant trough usart1.

The USART1 is configured as follows:
    - TX:PA9, RX:PA10
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

&par Hardware Description

Connect SPI1 and SPI2 pins as follows:
SPI1 NSS    (PA4)   to  SPI2 NSS    (PB12)
SPI1 SCK    (PA5)   to  SPI2 SCK    (PB13)
SPI1 MISO   (PA6)   to  SPI2 MISO   (PB14)
SPI1 MOSI   (PA7)   to  SPI2 MOSI   (PB15)

&par Directory contents

  - SPI/SPI_FullDuplex/Source/apm32f465_int.c       Interrupt handlers
  - SPI/SPI_FullDuplex/Source/main.c                Main program

&par IDE environment

  - MDK-ARM V5.29.0.0
  - EWARM V8.50.5.26295
  - Eclipse V2022-06（4.24.0）

&par Hardware and Software environment

  - This example runs on APM32F465 MINI Devices.