/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.0
 *
 * @date        2023-03-08
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

&par Example Description

The program aims to show how to use KEY1 button to trigger USART communication using interrupts, in this case,
you need to load program on two APM32F465_MINI boards. Then connect these two boards through USART lines and GND.
If USART RX Board receives the correct data from USART TX Board, USART RX Board LED2 will turn on.

notes:
Uncomment the line below in main.c if you want to use the USART in Transmitter Mode
 - #define USART_TX_BOARD
Uncomment the line below in main.c if you want to use the USART in Receiver Mode
 - #define USART_RX_BOARD

&par Hardware Description

*---------------------------------------*
|  USART TX Board       USART RX Board  |
|                                       |
| USART1_TX(PA9)  ----> USART1_RX(PA10) |
| USART1_RX(PA10) ----> USART1_TX(PA9)  |
| GND                   GND             |
|                                       |
*---------------------------------------*

  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - USART/USART_TwoBoardsInterrupt/Source/apm32f465_int.c     Interrupt handlers
  - USART/USART_TwoBoardsInterrupt/Source/main.c              Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - Eclipse V2022-06（4.24.0）

&par Hardware and Software environment

  - This example runs on APM32F465_MINI Devices.
