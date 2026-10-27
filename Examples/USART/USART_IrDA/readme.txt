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

The program shows how to  using USART IrDA mode, in this case,
USART1 sends data to upper computer. You can check the data in a Serial Port Utility.

USART2 and USART3 configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

To use this example, the user needs to prepare two IrDA modules.
   VCC             ---> 1# IrDA module VCC
   GND             ---> 1# IrDA module GND
   PA2(USART2_TX)  ---> 1# IrDA module TX
   PA3(USART2_RX)  ---> 1# IrDA module RX
   
   VCC             ---> 2# IrDA module VCC
   GND             ---> 2# IrDA module GND
   PB10(USART3_TX) ---> 2# IrDA module TX
   PB11(USART3_RX) ---> 2# IrDA module RX

&par Hardware Description

USART1_TX(PA9) ----> USART2_RX(PA3)
USART1_RX(PA10)----> USART2_TX(PA2)

  - USART1 configured as follow:
  - BaudRate = 115200
  - Word Length = USART_WordLength_8b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

&par Directory contents

  - USART/USART_IrDA/Source/apm32f465_int.c     Interrupt handlers
  - USART/USART_IrDA/Source/main.c              Main program

&par IDE environment

  - MDK-ARM V5.36
  - EWARM V8.50.5.26295
  - Eclipse V2022-06（4.24.0）

&par Hardware and Software environment

  - This example runs on APM32F465 MINI Devices.
