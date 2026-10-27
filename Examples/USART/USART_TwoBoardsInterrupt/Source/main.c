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
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

/** @addtogroup USART_TwoBoardsInterrupt
  @{
  */

/** @addtogroup USART_TwoBoardsInterrupt_Macros Macros
  @{
  */

/* Uncomment the line below if you want to use the USART in Transmitter Mode */
/* #define USART_TX_BOARD */
/* Uncomment the line below if you want to use the USART in Receiver Mode */
#define USART_RX_BOARD

/**@} end of group USART_TwoBoardsInterrupt_Macros*/

/** @defgroup USART_TwoBoardsInterrupt_Enumerations Enumerations
  @{
  */

typedef enum {FALSE, TRUE} BOOL;

/**@} end of group USART_TwoBoardsInterrupt_Enumerations*/

/** @defgroup USART_TwoBoardsInterrupt_Variables Variables
  @{
  */

/** USART1 receive buffer*/
uint8_t rxDataBufUSART1[DATA_BUF_SIZE] = {0};
/** USART1 transmit buffer*/
uint8_t txDataBufUSART1[DATA_BUF_SIZE] = {0};

uint32_t rxCountUSART1 = 0;
uint32_t txCountUSART1 = 0;

/**@} end of group USART_TwoBoardsInterrupt_Variables */

/** @defgroup USART_TwoBoardsInterrupt_Functions Functions
  @{
  */

/** USART Initialization */
void USART_Init(void);
/** USART Write data */
void USART_Write(USART_T* usart,uint8_t *dat, uint32_t count);

/** Delay */
void Delay(uint32_t count);
/** Buffer compare*/
BOOL BufferCompare(uint8_t *buf1, uint8_t *buf2, uint8_t size);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 */
int main(void)
{
#ifdef USART_RX_BOARD
    
    BOOL state = TRUE;
#endif
    
    /* Init txDataBufUSART2 */
    for(int i = 0; i < DATA_BUF_SIZE; i++)
    {
        txDataBufUSART1[i] = i;
    }

    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);

    /* USART Initialization */
    USART_Init();
    
#ifdef USART_TX_BOARD
    /* Wait KEY1 button is pressed */
    while(APM_MINI_PBGetState(BUTTON_KEY1) != RESET)
    {
    }
    
    /* Wait KEY1 button is released */
    while(APM_MINI_PBGetState(BUTTON_KEY1) == RESET)
    {
    }
    
    USART_EnableInterrupt(MINI_COM1, USART_INT_TXBE);
    
#endif

#ifdef USART_RX_BOARD
    
    USART_EnableInterrupt(MINI_COM1, USART_INT_RXBNE);
    
    /* Waiting the end of data transfer */
    while ((txCountUSART1 < DATA_BUF_SIZE) && (rxCountUSART1 < DATA_BUF_SIZE))
    {
    } 
    
    /* Verify data */
    state = BufferCompare(rxDataBufUSART1, txDataBufUSART1, DATA_BUF_SIZE);

    /* Data is ok then turn off LED2 */
    if(state == TRUE)
    {
        APM_MINI_LEDOn(LED2);
    }
    else
    {
        APM_MINI_LEDOn(LED3);
    }

#endif

    while(1)
    {
    }
}

/*!
 * @brief       USARTS Initialization
 *
 * @param       None
 *
 * @retval      None
 */
void USART_Init(void)
{
    USART_Config_T usartConfigStruct;

    usartConfigStruct.baudRate = 115200;
    usartConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfigStruct.mode = USART_MODE_TX_RX;
    usartConfigStruct.parity = USART_PARITY_NONE;
    usartConfigStruct.stopBits = USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_MINI_COMInit(COM1, &usartConfigStruct);

    Delay(0x7FFF);

    NVIC_EnableIRQRequest(MINI_COM1_IRQn,1,0);
}

/*!
 * @brief       This function handles USART1 interrupt Handler
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into  void USART1_IRQHandler(void)
 */
void  USART_Isr(void)
{
    /* USART1 Send Data */
    if(USART_ReadIntFlag(MINI_COM1, USART_INT_TXBE) == SET)
    {
        if(txCountUSART1 < DATA_BUF_SIZE)
        {
            USART_TxData(MINI_COM1,txDataBufUSART1[txCountUSART1++]);
        }
        else
        {
            USART_DisableInterrupt(MINI_COM1, USART_INT_TXBE);
        }
    }

    /* USART1 Recieve Data */
    if(USART_ReadStatusFlag(MINI_COM1, USART_FLAG_RXBNE) == SET)
    {
        if(rxCountUSART1 < DATA_BUF_SIZE)
        {
            rxDataBufUSART1[rxCountUSART1++] = (uint8_t)USART_RxData(MINI_COM1);
        }
        else
        {
            USART_DisableInterrupt(MINI_COM1, USART_INT_RXBNE);
        }
    }
}

/*!
 * @brief       Compares two buffers
 *
 * @param       buf1:    First buffer to be compared
 *
 * @param       buf1:    Second buffer to be compared
 *
 * @param       size:    Buffer size
 *
 * @retval      Return SET if buf1 = buf2. If not then return RESET
 */
BOOL BufferCompare(uint8_t *buf1, uint8_t *buf2, uint8_t size)
{
    uint8_t i;

    for(i = 0; i < size; i++)
    {
        if(buf1[i] != buf2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*!
 * @brief       Serial port tramsimt data
 *
 * @param       pointer to date that need to be sent
 *
 * @retval      None
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

/**@} end of group USART_TwoBoardsInterrupt_Functions */
/**@} end of group USART_TwoBoardsInterrupt */
/**@} end of group Examples */
