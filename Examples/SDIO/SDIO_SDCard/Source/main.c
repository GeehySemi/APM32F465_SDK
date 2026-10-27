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
#include "bsp_delay.h"
#include "bsp_usart.h"
#include "bsp_key.h"
#include "bsp_sdio.h"
#include <stdio.h>
#include <string.h>

/** @addtogroup Examples
  @{
  */

/** @addtogroup SDIO_SDCard
  @{
  */

/** @defgroup SDIO_SDCard_Variables Variables
  @{
  */

/** public variables*/
/** Record SD card command and data status */
SD_ERROR_T g_status = SD_OK;

/**@} end of group SDIO_SDCard_Variables */

/** private function prototypes */
/** SD write and read single block test function */
void SD_SingleBlockTest(void);
/** SD write and read multi block test function */
void SD_MultiBlockTest(void);

/** @defgroup SDIO_SDCard_Functions Functions
  @{
  */

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    uint8_t keyType;

    /** Set system interrupt priority grouping */
    NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_2);

    /** Init delay function */
    Delay_Init();

    /** Init LED */
    APM_MINI_LEDInit(LED2);
    APM_MINI_LEDInit(LED3);

    /** Init USART1 */
    USART1_Init(115200);

    /** Init KEY */
    APM_MINI_PBInit(BUTTON_KEY2, BUTTON_MODE_GPIO);
    APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /** Wait board and module power on */
    Delay_ms(200);

    /** Init SD Card */
    if((g_status = SD_Init()) != SD_OK)
    {
        APM_MINI_LEDOn(LED3);

        printf("SD Init Fail\n");

    }
    else
    {
        APM_MINI_LEDOff(LED3);

        printf("SD Init Success\n");
    }
    /** Show SD card informations */
    SD_ShowCardInfo();

    while(1)
    {
        keyType = Key_Scan(KEY_MODE_SINGLE);

        /** Select single block test function  */
        if(keyType == KEY1_PRESSED)
        {
            printf("Single Block Test\r\n");

            if(g_status == SD_OK)
            {
                SD_SingleBlockTest();
            }
            while(KEY1 == 0);
        }
        /** Select multi block test function  */
        else if(keyType == KEY2_PRESSED)
        {
            printf("Multi Block Test\r\n");
            
            if(g_status == SD_OK) 
            {
                SD_MultiBlockTest();
            }
            while(KEY2 == 0);
        }

        Delay_ms(10);
    }
}

/*!
 * @brief       Write and read SD card single block
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SD_SingleBlockTest(void)
{
    uint32_t sdSize;
    uint8_t sta = SD_OK;
    long long sectorAddress = 0;
    uint8_t buffer[512];

    /** Fill the data to be written  */
    for(sdSize = 0; sdSize < 512; sdSize++)
    {
        buffer[sdSize] = sdSize + 1 ;
    }
    /** Write one sector data to sector 0 address  */
    if((sta = SD_WriteBlock(buffer,sectorAddress,512)) == SD_OK)
    {
        printf("write success\r\n");
        Delay_ms(50);
    }
    else
    {
        printf("Write Error Status:%d\r\n",sta);
    }

    memset(buffer,0,512);

    if((sta = SD_ReadBlock(buffer,sectorAddress,512)) == SD_OK)
    {
        /** Print sector 0 data  */
        printf("Sector 0 Data:\r\n");

        for(sdSize = 1; sdSize <= 512; sdSize++)
        {
            printf("%X ",buffer[sdSize - 1]);

            if((sdSize != 0) && ((sdSize % 16) == 0))
            {
                printf("\r\n");
            }
        }
        printf("Sector 0 Data Ended\r\n");
    }
    else
    {
        printf("Read Error Status %d\r\n",sta);
    }

    printf("Single Block Test OK\r\n");
}

/*!
 * @brief       Write and read SD card multi block
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SD_MultiBlockTest(void)
{
    uint32_t sdSize;
    uint8_t sta = SD_OK;
    uint32_t sectorAddress = 0;
    uint8_t sectorCnt = 2;
    uint8_t buffer[1024];
    uint8_t i;


    /** Fill the data to be written  */
    for(sdSize = 0; sdSize < 512; sdSize++)
    {
        buffer[sdSize] = sdSize ;
    }

    /** Fill the data to be written  */
    for(sdSize = 512; sdSize < 1024; sdSize++)
    {
        buffer[sdSize] = 0xAA ;
    }

    /** Write one sector data to sector 0 address  */
    if((sta = SD_WriteMultiBlocks(buffer,sectorAddress,1024,sectorCnt)) == SD_OK)
    {
        printf("write success\r\n");
        Delay_ms(50);
    }
    else
    {
        printf("Write Error Status:%d\r\n",sta);
    }

    memset(buffer,0,1024);

    if((sta = SD_ReadMultiBlocks(buffer,sectorAddress,1024,sectorCnt)) == SD_OK)
    {
        /** Print sector 0 data  */
        for(i = sectorAddress; i < sectorCnt; i++)
        {
            printf("Sector %d Data:\r\n",i);
            
            for(sdSize = 1 + (i * 512); sdSize <= 512 + (i * 512); sdSize++)
            {
                printf("%X ",buffer[sdSize - 1]);
                 
                if((sdSize != 0) && ((sdSize % 16) == 0))
                {
                    printf("\r\n");
                }
            }
            printf("Sector %d Data Ended\r\n",i);
        }
    }
    else
    {
        printf("Read Error Status %d\r\n",sta);
    }

    printf("Multi Block Test OK\r\n");
}

/**@} end of group SDIO_SDCard_Functions */
/**@} end of group SDIO_SDCard */
/**@} end of group Examples */
