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
#include "Board.h"
#include "apm32f465_pmu.h"
#include "apm32f465_usart.h"
#include "apm32f465_rcm.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup PMU_PVD
  @{
  */

/** @defgroup PMU_PVD_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART  USART1

/**@} end of group PMU_PVD_Macros*/

/** @defgroup PMU_PVD_Functions Functions
  @{
  */

/* Delay */
void Delay(uint32_t count);

/* PVD*/
void PVD_Config(void);

/*!
 * @brief     Main program
 *
 * @param     None
 *
 * @retval    None
 */
int main(void)
{
    NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_1);
    
    USART_Config_T usartConfigStruct;

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);

    usartConfigStruct.baudRate = 115200;
    usartConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfigStruct.mode = USART_MODE_TX;
    usartConfigStruct.parity = USART_PARITY_NONE;
    usartConfigStruct.stopBits = USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_MINI_COMInit(COM1, &usartConfigStruct);

    PMU_Reset();

    PVD_Config();

    while (1)
    {
        Delay(0x3FFFFF);
        APM_MINI_LEDToggle(LED3);
    }
}

/*!
 * @brief     Configure power valtage detector
 *
 * @param     None
 *
 * @retval    None
 */
void PVD_Config(void)
{
    EINT_Config_T eintConfigStruct;
    
    /* Enable PMU clock*/
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    
    EINT_ClearIntFlag(EINT_LINE_16);
    eintConfigStruct.line = EINT_LINE_16;
    eintConfigStruct.mode = EINT_MODE_INTERRUPT;
    eintConfigStruct.trigger = EINT_TRIGGER_RISING;
    eintConfigStruct.lineCmd = ENABLE;
    EINT_Config(&eintConfigStruct);
    
    /* PVD detection level set to 2.6V*/
    PMU_ConfigPVDLevel(PMU_PVD_LEVEL_2V6);
    
    NVIC_EnableIRQRequest(PVD_IRQn,0,0);
    
    PMU_EnablePVD();
}

/*!
 * @brief     PVD interrupt callback
 *
 * @param     None
 *
 * @retval    None
 */
void PMU_PVD_Isr(void)
{
    uint8_t temp = 3;
    
    while(temp--)
    {
        printf("PVD detected that VDD rose above the threshold\r\n");
        Delay(0x3FFFFF);
        APM_MINI_LEDToggle(LED2);
    }
}

/*!
 * @brief     Delay
 *
 * @param     count:  delay count
 *
 * @retval    None
 */
void Delay(uint32_t count)
{
    volatile uint32_t delay = count;
    
    while(delay--);
}

 /*!
 * @brief     Redirect C Library function printf to serial port.
 *            After Redirection, you can use printf function.
 *
 * @param     ch:  The characters that need to be send.
 *
 * @param     *f:  pointer to a FILE that can recording all information
 *            needed to control a stream
 *
 * @retval    The characters that need to be send.
 */
int fputc(int ch, FILE *f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART,(uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

/**@} end of group PMU_PVD_Functions */
/**@} end of group PMU_PVD */
/**@} end of group Examples */
