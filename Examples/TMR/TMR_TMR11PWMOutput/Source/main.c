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

/** @addtogroup Examples
  @{
  */

/** @addtogroup TMR_TMR11PWMOutput
  @{
  */

/** @defgroup TMR_TMR11PWMOutput_Functions Functions
  @{
  */

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 */
int main(void)
{
    GPIO_Config_T GPIO_ConfigStruct;
    TMR_BaseConfig_T TMR_TimeBaseStruct;
    TMR_OCConfig_T OCcongigStruct;

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR11);
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);

    /** TMR11_CH1 */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_9, GPIO_AF_TMR11);

    /** Config TMR11 GPIO for output PWM */
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_100MHz;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);

    /** config TMR11 */
    TMR_TimeBaseStruct.clockDivision = TMR_CLOCK_DIV_1;
    TMR_TimeBaseStruct.countMode = TMR_COUNTER_MODE_UP;
    TMR_TimeBaseStruct.division = 167;
    TMR_TimeBaseStruct.period = 999;
    TMR_ConfigTimeBase(TMR11, &TMR_TimeBaseStruct);

    /** Configure channel1 */
    TMR_ConfigOCStructInit(&OCcongigStruct);

    OCcongigStruct.mode = TMR_OC_MODE_PWM1;
    OCcongigStruct.outputState = TMR_OC_STATE_ENABLE;
    OCcongigStruct.polarity = TMR_OC_POLARITY_HIGH;

    /** Configure Channel 1 duty cycle = 80% */
    OCcongigStruct.pulse = 800;
    TMR_ConfigOC1(TMR11, &OCcongigStruct);
    TMR_ConfigOC1Preload(TMR11, TMR_OC_PRELOAD_ENABLE);

    TMR_EnableAutoReload(TMR11);
    TMR_Enable(TMR11);

    while(1)
    {
    }
}

/**@} end of group TMR_TMR11PWMOutput_Functions */
/**@} end of group TMR_TMR11PWMOutput */
/**@} end of group Examples */
