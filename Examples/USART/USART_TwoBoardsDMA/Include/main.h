/*!
 * @file        main.h
 *
 * @brief       Header for main.c module
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

/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "Board.h"
#include "stdio.h"

#include "apm32f465.h"
#include "apm32f465_can.h"
#include "apm32f465_misc.h"
#include "apm32f465_gpio.h"
#include "apm32f465_usart.h"
#include "apm32f465_dma.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup USART_TwoBoardsDMA
  @{
  */

/** @addtogroup USART_TwoBoardsDMA_Macros Macros
  @{
  */

#define DATA_BUF_SIZE       (32)

/**@} end of group USART_TwoBoardsDMA_Macros*/

/** @addtogroup USART_TwoBoardsDMA_Ex_Variables Ex_Variables
  @{
  */

extern uint32_t rxCountUSART1;
extern uint32_t txCountUSART1;
extern uint8_t txDataBufUSART1[DATA_BUF_SIZE];
extern uint8_t rxDataBufUSART1[DATA_BUF_SIZE];

/**@} end of group USART_TwoBoardsDMA_Ex_Variables*/

/** @defgroup USART_TwoBoardsDMA_Functions Functions
  @{
  */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/**@} end of group USART_TwoBoardsDMA_Functions */
/**@} end of group USART_TwoBoardsDMA */
/**@} end of group Examples */
