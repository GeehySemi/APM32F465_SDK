/*!
 * @file        main.c
 *
 * @brief       Main program body
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

/* Includes */
#include "main.h"
#include "bsp_usart.h"
#include "bsp_flash.h"
#include "Board.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup IAP_BootLoader
  @{
  */

/** @defgroup IAP_BootLoader_Functions Functions
  @{
  */

uint32_t JumpAddress;
pFunction Jump_To_Application;


/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 */
int main(void)
{
    /** Initialize LED on APM32F465 MINI Board */
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    /** Initialize UART mounted on APM32F465 MINI Board */
    USART_Init(DEBUG_USART_BAUDRATE);

    APM_MINI_LEDOn(LED2);
    APM_MINI_LEDOn(LED3);
    
    /** Configure the Flash to re-program the Flash */
    FLASH_IAP_Init();
    
    /** Display Select menu */
    Select_Menu();

    /** Jump to user application 1 */
    SendString(">> Jump to user application 1\r\n");
    Jump_to_App(APP1);
    
    while (1)
    {
    }
}

/*!
 * @brief       Delay
 *
 * @param       count:  delay count
 *
 * @retval      None
 */
void Delay(uint32_t count)
{
    volatile uint32_t delay = count;
    while(delay--);
}

/*!
 * @brief       Jump to user application
 *
 * @param       Application : APP1 or APP2
 *
 * @retval      None
 *
 * @note
 */
void Jump_to_App(uint8_t Application)
{
    uint32_t address;

    /** Lock the Program memory */
    FMC_Lock();
    
    if(Application == APP1)
    {
        address = USER_APP1_ADDRESS;
    }
    else
    {
        address = USER_APP2_ADDRESS;
    }

    /** Jump to user application */
    JumpAddress = *(__IO uint32_t *) (address + 4);
    Jump_To_Application = (pFunction) JumpAddress;

    /** Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t *) address);

    /** Jump to application */
    Jump_To_Application();
}

/**@} end of group IAP_BootLoader_Functions */
/**@} end of group IAP_BootLoader */
/**@} end of group Examples */
