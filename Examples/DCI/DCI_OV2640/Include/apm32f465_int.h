/*!
 * @file        apm32f465_int.h
 *
 * @brief       This file contains the headers of the interrupt handlers
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
#ifndef __APM32A4XX_INT_H
#define __APM32A4XX_INT_H

/* Includes */
#include "apm32f465.h"
#include "bsp_delay.h"
#include "bsp_usart.h"
#include "main.h"

#ifdef __cplusplus
  extern "C" {
#endif

/** @addtogroup Examples
  @{
  */

/** @addtogroup DCI_OV2640
  @{
  */

/** @defgroup DCI_OV2640_INT_Functions INT_Functions
  @{
*/

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);
void DCI_IRQHandler(void);



#ifdef __cplusplus
}
#endif

#endif /*__APM32A4XX_INT_H */

/**@} end of group DCI_OV2640_INT_Functions */
/**@} end of group DCI_OV2640 */
/**@} end of group Examples */
