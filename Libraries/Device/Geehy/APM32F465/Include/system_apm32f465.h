/*!
 * @file        system_apm32f465.h
 *
 * @brief       CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
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
#ifndef __SYSTEM_APM32F465_H
#define __SYSTEM_APM32F465_H

#ifdef __cplusplus
  extern "C" {
#endif

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F465_System
  @{
*/

/** @defgroup System_Variables
  @{
*/

/* System Clock Frequency (Core Clock) */
extern unsigned int SystemCoreClock;

/**
  * @}
  */

/** @defgroup System_Functions
  @{
*/

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_APM32F465_H */

/**@} end of group System_Functions */
/**@} end of group APM32F465_System */
/**@} end of group CMSIS */
