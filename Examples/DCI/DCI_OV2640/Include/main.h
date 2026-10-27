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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
#include "Board.h"
#include "stdio.h"

#include "apm32f465.h"
#include "apm32f465_can.h"
#include "apm32f465_misc.h"
#include "apm32f465_gpio.h"
#include "apm32f465_usart.h"
#include "apm32f465_misc.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup DCI_OV2640
  @{
  */

/** @defgroup DCI_OV2640_Enumerations Enumerations
  @{
  */

/*!
 * @brief     OV2640 work mode
 */
typedef enum
{
    RGB565_MODE,    /*!< OV2640 rgb565 work mode */
    JPEG_MODE,      /*!< OV2640 jpeg work mode */
} OV2640_MODE;

/**@} end of group DCI_OV2640_Enumerations*/

/** @defgroup DCI_OV2640_Variables Variables
  @{
  */

/* extern variables*/
extern OV2640_MODE g_ov2640Mode;

/**@} end of group DCI_OV2640_Variables */

/** @defgroup DCI_OV2640_Functions Functions
  @{
  */

void OV2640_JpegDataCallback(void);
void OV2640_Rgb565DataCallback(void);

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/**@} end of group DCI_OV2640_Functions */
/**@} end of group DCI_OV2640 */
/**@} end of group Examples */
