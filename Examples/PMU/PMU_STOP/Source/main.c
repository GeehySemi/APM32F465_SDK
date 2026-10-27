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

/** @addtogroup PMU_STOP
  @{
  */

/** @defgroup PMU_STOP_Macros Macros
  @{
*/

/* printf using USART1  */
#define DEBUG_USART  USART1

/**@} end of group PMU_STOP_Macros*/

/** @defgroup PMU_STOP_Functions Functions
  @{
  */

int8_t g_enterStopFlag = BIT_RESET;

/* Delay */
void Delay(uint32_t count);

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

    usartConfigStruct.baudRate = 115200;
    usartConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfigStruct.mode = USART_MODE_TX;
    usartConfigStruct.parity = USART_PARITY_NONE;
    usartConfigStruct.stopBits = USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_MINI_COMInit(COM1, &usartConfigStruct);

    APM_MINI_LEDInit(LED2);
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_EINT);
    APM_MINI_PBInit(BUTTON_KEY2,BUTTON_MODE_EINT);

    /* Enable PMU Periph Clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU);
    PMU_Reset();

    printf("\r\nSystem is Init\r\n");
    printf("Press KEY1 to Enter STOP Mode\r\n");

    while (1)
    {
        Delay(0xFFFFFF);

        APM_MINI_LEDToggle(LED2);
        printf("\r\nSystem is running\r\n");

        if(g_enterStopFlag == BIT_SET)
        {
            g_enterStopFlag = BIT_RESET;

            printf("\r\nSystem have entered STOP mode\r\n");
            printf("now, LED2 remains in the previous state\r\n");
            printf("please press KEY2 or reset System to exit STOP mode\r\n");
            Delay(0xFFFFFF);

            /* Enter STOP Mode in WFI*/
            PMU_EnterSTOPMode(PMU_REGULATOR_ON,PMU_STOP_ENTRY_WFI);
        }
    }
}

/*!
 * @brief     Enter STOP mode Interrupt
 *
 * @param     None
 *
 * @retval    None
 */
void APM_MINI_PB_PMU_Isr(void)
{
    g_enterStopFlag = BIT_SET;
}

/*!
 * @brief     WakeUp from STOP mode Interrupt
 *
 * @param     None
 *
 * @retval    None
 */
void EINT_WakeUp_From_STOP_Isr()
{
    SystemInit();
    printf("\r\nSystem have exit Stop mode\r\n");
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

#if defined (__CC_ARM) || defined (__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*
* @note
*/
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*
* @note
*/
int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, ch);

    /* wait for the data to be send */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*
* @note
*/
int _write(int file, char* ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#else
#warning Not supported compiler type
#endif

/**@} end of group PMU_STOP_Functions */
/**@} end of group PMU_STOP */
/**@} end of group Examples */
