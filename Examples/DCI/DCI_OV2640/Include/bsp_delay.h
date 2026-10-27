/*!
 * @file        bsp_delay.h
 *
 * @brief       Header for bsp_delay.c module
 *
 * @version     V1.0.0
 *
 * @date        2023-03-08
 *
 * @attention
 *
 *  Copyright (C) 2023 Geehy Semiconductor
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
#ifndef _BSP_DELAY_H
#define _BSP_DELAY_H

/* Includes */
#include "Board.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup DCI_OV2640
  @{
  */

/** @defgroup DCI_OV2640_Variables Variables
  @{
  */

/* extern variables*/
extern uint32_t cntUs;
extern uint32_t cntMs;

/**@} end of group DCI_OV2640_Variables */

/** @defgroup DCI_OV2640_Functions Functions
  @{
  */

/* function declaration*/
void Delay_Init(void);
void Delay_ms(__IO u32 nms);
void Delay_us(__IO u32 nus);

#endif

/**@} end of group DCI_OV2640_Functions */
/**@} end of group DCI_OV2640 */
/**@} end of group Examples */
