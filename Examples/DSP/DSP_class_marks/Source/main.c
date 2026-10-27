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
#include "stdio.h"

#include "apm32f465_gpio.h"
#include "apm32f465_misc.h"
#include "apm32f465_usart.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup DSP_class_marks
  @{
  */

/** @defgroup DSP_class_marks_Macros Macros
  @{
*/

#define DSP_TEST_DEMO_N "class_marks test"

/**@} end of group DSP_class_marks_Macros*/

/** @defgroup DSP_class_marks_Functions Functions
  @{
  */

/** DSP Demo Test */
extern void DSPTestDemo(void);

/*!
 * @brief     Main program
 *
 * @param     None
 *
 * @retval    None
 */
int main(void)
{
    uint8_t keyType;
    
    /* Set system interrupt priority grouping */
    NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_2);
    
    /* Init delay function */
    Delay_Init();

    /* Init LED */
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    /* Init USART1 */
    USART1_Init(115200);

    /* Init KEY */
    APM_MINI_PBInit(BUTTON_KEY2, BUTTON_MODE_GPIO);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* Wait board and module power on */
    Delay_ms(200);
    
    printf("This is a DSP %s demo!\n",DSP_TEST_DEMO_N);
    printf("press KEY1 start test!\n");
    APM_MINI_LEDOn(LED3);
    
    while(1)
    {
        keyType = Key_Scan(KEY_MODE_SINGLE);

        /* Select single block test function  */
        if(keyType == KEY1_PRESSED)
        {
            APM_MINI_LEDOn(LED2);
            printf( "%s\r\n",DSP_TEST_DEMO_N );
            DSPTestDemo();
            APM_MINI_LEDOff(LED2);
            
            while(KEY1 == 0);
        }

        Delay_ms(10);
    }
}

/**@} end of group DSP_class_marks_Functions */
/**@} end of group DSP_class_marks */
/**@} end of group Examples */
