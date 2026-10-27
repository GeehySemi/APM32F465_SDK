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
#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "Board.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup SDIO_SDCard
  @{
  */

/** @defgroup SDIO_SDCard_Variables Variables
  @{
  */

/** extern variables*/
extern uint32_t cntUs;
extern uint32_t cntMs;

/**@} end of group SDIO_SDCard_Variables */

/** @defgroup SDIO_SDCard_Functions Functions
  @{
  */

/** function declaration*/
void Delay_Init(void);
void Delay_ms(__IO u32 nms);
void Delay_us(__IO u32 nus);

#ifdef __cplusplus
}
#endif

#endif

/**@} end of group SDIO_SDCard_Functions */
/**@} end of group SDIO_SDCard */
/**@} end of group Examples */
