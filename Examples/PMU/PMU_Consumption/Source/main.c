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
#include "low_power_modes.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup PMU_Consumption
  @{
  */

/** @defgroup PMU_Consumption_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART                     USART1

#define SYS_SLEEP_MODE                  1
#define SYS_STOP_MODE                   0
#define SYS_STANDBY_MODE                0
#define SYS_STANDBY_RTC_MODE            0
#define SYS_STANDBY_RTC_BKPSRAM_MODE    0

/**@} end of group PMU_BOR_Macros*/

/** @defgroup PMU_BOR_Functions Functions
  @{
  */

/* Delay */
void Delay(uint32_t count);

/* BOR*/
void BOR_Config(FMC_OPT_BOR_T level);

/*!
 * @brief     Main program
 *
 * @param     None
 *
 * @retval    None
 */
int main(void)
{
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

    printf("System reset\r\n");
    
    /* Enable PMU clock*/
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    
    /* Allow access to Backup domain*/
    PMU_EnableBackupAccess();
    
    /* Reset RTC*/
    RCM_EnableBackupReset();
    RCM_DisableBackupReset();
    
    /* If system was resumed from Standby mode*/
    if(PMU_ReadStatusFlag(PMU_FLAG_SB) != RESET)
    {
        PMU_ClearStatusFlag(PMU_FLAG_SB);
        printf("System was resumed from Standby mode\r\n");
        
        while(1)
        {
            APM_MINI_LEDToggle(LED2);
            Delay(0x3FFFFF);
        }
    }
    
    printf("Please press KEY1 to run specific mode\r\n");
    while(APM_MINI_PBGetState(BUTTON_KEY1) != RESET)
    {
    }
    printf("Waitting KEY1 release\r\n");
    while(APM_MINI_PBGetState(BUTTON_KEY1) == RESET)
    {
    }
    
#if (SYS_STANDBY_RTC_BKPSRAM_MODE)
    printf("Run SYS_STANDBY_RTC_BKPSRAM_MODE\r\n");
    ConsumptionMeasure_StandbyRTCBKPSRAMMode();
#elif (SYS_STANDBY_RTC_MODE)
    printf("Run SYS_STANDBY_RTC_MODE\r\n");
    ConsumptionMeasure_StandbyRTCMode();
#elif (SYS_STANDBY_MODE)
    printf("Run SYS_STANDBY_MODE\r\n");
    ConsumptionMeasure_StandbyMode();
#elif (SYS_STOP_MODE)
    printf("Run SYS_STOP_MODE\r\n");
    ConsumptionMeasure_StopMode();
#elif (SYS_SLEEP_MODE)
    printf("Run SYS_SLEEP_MODE\r\n");
    ConsumptionMeasure_SleepMode();
#else
    printf("Run normal mode\r\n");
    while (1)
    {
        Delay(0x3FFFFF);
        APM_MINI_LEDToggle(LED3);
    }
#endif
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

/**@} end of group PMU_Consumption_Functions */
/**@} end of group PMU_Consumption */
/**@} end of group Examples */
