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
#include "apm32f465_wwdt.h"
#include "apm32f465_eint.h"
#include <stdio.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup WWDT_OverTime
  @{
  */

/** @addtogroup WWDT_OverTime_Macros Macros
  @{
  */

/** printf using USART1  */
#define DEBUG_USART  USART1

/**@} end of group WWDT_OverTime_Macros*/

/** @defgroup WWDT_OverTime_Variables Variables
  @{
  */

/** The OverTime is used to change the test way*/
uint8_t is_OverTime = 0;

static __IO u32 TimingDelay;

/**@} end of group WWDT_OverTime_Variables */

/** @defgroup WWDT_OverTime_Functions Functions
  @{
  */

void SysTick_Init(void);
void SysTick_Delay_ms(__IO u32 nTime);
void TimingDelay_Decrement(void);

/** WWDT_Init */
void WWDT_Init(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
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
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /** Clear WWDTRST flag */
    if (RCM_ReadStatusFlag(RCM_FLAG_WWDTRST)!=RESET)
    {
        APM_MINI_LEDOn(LED3);
        RCM_ClearStatusFlag();
    }

    printf("\r\n System reset \r\n");
    printf("\r\n The overtime is from 36.6ms to 49.9ms \r\n");

    SysTick_Init();
    WWDT_Init();

    while (1)
    {
        if (is_OverTime == RESET)
        {
            APM_MINI_LEDToggle(LED2);
            /* Delay 41ms , 36.6<41<49.9 ,Refresh allowed, system still running */
            SysTick_Delay_ms(41);
            WWDT_ConfigCounter(127);
            printf("running...\r\n");
        }

        if (is_OverTime == SET)
        {
            APM_MINI_LEDOn(LED3);
            /* Delay 59ms  ,49.9<59 ,Refresh not allowed, system reset */
            SysTick_Delay_ms(59);
            WWDT_ConfigCounter(127);
        }

        if (!APM_MINI_PBGetState(BUTTON_KEY1))
        {
            SysTick_Delay_ms(5);
            if (!APM_MINI_PBGetState(BUTTON_KEY1))
            {
                is_OverTime = SET;
            }
        }
    }
}

/*!
 * @brief       WWDT configuration
 *
 * @param       None
 *
 * @retval      None
 */
void WWDT_Init(void)
{
    /** Enable WWDT clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_WWDT);

    /** WWDT TimeBase =  PCLK1 (42MHz)/4096)/8 = 1282Hz (~0.78 ms)  */
    WWDT_ConfigTimebase(WWDT_TIME_BASE_8);

    /** Set Window value to 80; WWDT counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated  */
    WWDT_ConfigWindowData(80);

    /** Enable WWDG and set counter value to 127, WWDT timeout = ~780 us * 64 = 49.92 ms
     In this case the refresh window is: ~0.78 * (127-80)= 36.6ms < refresh window < ~0.78 * 64 = 49.92ms*/
    WWDT_Enable(127);
}

/*!
 * @brief       Start SysTick
 *
 * @param       None
 *
 * @retval      None
 */
void SysTick_Init(void)
{
    /** SystemFrequency / 1000 = 1ms */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /** Capture error */
        while (1);
    }
}

/*!
 * @brief       Precise Delay
 *
 * @param       nTime in milliseconds
 *
 * @retval      None
 */
void SysTick_Delay_ms(__IO u32 nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

/*!
 * @brief       Decrements the TimingDelay
 *
 * @param       None
 *
 * @retval      None
 */
void TimingDelay_Decrement(void)
{
    if(TimingDelay != 0)
    {
        TimingDelay--;
    }
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

/**@} end of group WWDT_OverTime_Functions */
/**@} end of group WWDT_OverTime */
/**@} end of group Examples */
