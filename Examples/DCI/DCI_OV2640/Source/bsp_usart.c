/*!
 * @file        bsp_usart.c
 *
 * @brief       Usart board support package body
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
#include "bsp_usart.h"
#include <stdio.h>


/* public variables*/
USART_RX_STA_T rxStaUSART1;

/* USART1 receive buffer*/
u8 rxBufUSART1[USART1_REV_LEN];

/** @addtogroup Examples
  @{
  */

/** @addtogroup DCI_OV2640
  @{
  */

/** @defgroup DCI_OV2640_Functions Functions
  @{
  */

/*!
 * @brief     USART1 Initialization
 *
 * @param     None
 *
 * @retval    None
 *
 */
void USART1_Init(uint32_t baud)
{
    USART_Config_T usartConfigStruct;

    /* USART1 configuration */
    usartConfigStruct.baudRate = baud;
    usartConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfigStruct.mode = USART_MODE_TX_RX;
    usartConfigStruct.parity = USART_PARITY_NONE;
    usartConfigStruct.stopBits = USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_MINI_COMInit(COM1, &usartConfigStruct);

    Delay_ms(1);

    /* Enable USART1 RXBNE interrput */
    USART_EnableInterrupt(MINI_COM1, USART_INT_RXBNE);
    USART_ClearStatusFlag(MINI_COM1, USART_FLAG_RXBNE);
    NVIC_EnableIRQRequest(MINI_COM1_IRQn,1,0);
}

/*!
 * @brief     Serial port tramsimt data
 *
 * @param     pointer to date that need to be sent
 *
 * @retval    None
 *
 */
void USART_Write(USART_T* usart,uint8_t *dat, uint32_t count)
{
    while(count--)
    {
        while(USART_ReadStatusFlag(usart, USART_FLAG_TXBE) == RESET);
        USART_TxData(usart, *dat++);
    }
}

/*!
 * @brief     This function handles USARTx RX interrupt Handler
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      This function need to put into  void USARTx_IRQHandler(void)
 */
void USART_Receive_Isr(void)
{
    uint8_t res;

    /* USART1 Recieve Data */
    if(USART_ReadStatusFlag(MINI_COM1, USART_FLAG_RXBNE) != RESET)
    {
        /* Read the received data */
        res = (uint8_t)USART_RxData(MINI_COM1);

        if((rxStaUSART1.USART_RX_STA_B.FLAG_FRAME_END) == RESET)
        {
            /* Get the data frame break */
            if(rxStaUSART1.USART_RX_STA_B.FLAG_FRAME_BREAK)
            {
                if(res != 0x0A)
                {
                    /* Recieve data error */
                    rxStaUSART1.USART_RX_STA = RESET;
                }
                else
                {
                    rxBufUSART1[rxStaUSART1.USART_RX_STA_B.VALID_LENGHT] = res;
                    rxStaUSART1.USART_RX_STA_B.VALID_LENGHT++;
                    /* Recieve data ok */
                    rxStaUSART1.USART_RX_STA_B.FLAG_FRAME_END = SET;
                }
            }
            else
            {
                if(res == 0x0D)
                {
                    rxBufUSART1[rxStaUSART1.USART_RX_STA_B.VALID_LENGHT] = res;
                    rxStaUSART1.USART_RX_STA_B.VALID_LENGHT++;
                    rxStaUSART1.USART_RX_STA_B.FLAG_FRAME_BREAK = SET;
                }
                else
                {
                    rxBufUSART1[rxStaUSART1.USART_RX_STA_B.VALID_LENGHT] = res;
                    rxStaUSART1.USART_RX_STA_B.VALID_LENGHT++;
                    if(rxStaUSART1.USART_RX_STA_B.VALID_LENGHT > (USART1_REV_LEN - 1))
                    {
                        /* Recieve data error */
                        rxStaUSART1.USART_RX_STA = RESET;
                    }
                }
            }
        }
    }
}

/**@} end of group DCI_OV2640_Functions */
/**@} end of group DCI_OV2640 */
/**@} end of group Examples */
