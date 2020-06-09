/**
 *******************************************************************************
 * @file  crc/crc_software/source/main.c
 * @brief Main program of CRC software for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-27       Heqb            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co., Ltd. ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACCOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup CRC_Software
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define ByteCnt1                      (1U)
#define ByteCnt2                      (2U)
#define ByteCnt4                      (4U)

#define CRC16_InitVal                 (0xFFFFU)
#define CRC32_InitVal                 (0xFFFFFFFFUL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static uint16_t CalaCRC16(const uint8_t *pu8Data, uint32_t u32InitVal, uint8_t ByteWidth, uint32_t Length);
static uint32_t CalaCRC32(const uint8_t *pu8Data, uint32_t u32InitVal, uint8_t ByteWidth, uint32_t Length);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of CRC project
 * @param  None
 * @retval None
 */
int32_t main(void)
{
    uint8_t  u8SrcData [3u] = {0x12U,0x21U,0U};
    uint16_t u16SrcData[3u] = {0x1234U,0x4321U,0U};
    uint32_t u32SrcData[3u] = {0x12345678UL,0x87654321UL,0UL};
    uint32_t u16Checksum;
    uint32_t u32Checksum;
    uint32_t u32CRC16Data;
    uint32_t u32CRC32Data;

    /* Enable CRC. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_CRC, Enable); /* Enable CRC */
    /* LED Init */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Turn on LED_B */
    BSP_LED_On(LED_BLUE);

    /***************** Configuration end, application start **************/
    while (1)
    {
        /* Calculates byte data's CRC16 checksum and CRC32 checksum. */
        u32CRC16Data = CalaCRC16((uint8_t *)&u8SrcData, CRC16_InitVal, ByteCnt1, sizeof(u8SrcData));
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, (uint8_t *)&u8SrcData, CRC16_InitVal, sizeof(u8SrcData), CRC_BW_8);
        if(u32CRC16Data != u16Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }
        u32CRC32Data = CalaCRC32((uint8_t *)&u8SrcData, CRC32_InitVal, ByteCnt1, sizeof(u8SrcData));
        u32Checksum  = CRC_Calculate(CRC_CRC32, (uint8_t *)&u8SrcData, CRC32_InitVal, sizeof(u8SrcData), CRC_BW_8);
        if(u32CRC32Data != u32Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }

        /* Calculates half word data's CRC16 checksum and CRC32 checksum. */
        u32CRC16Data = CalaCRC16((uint8_t *)&u16SrcData, CRC16_InitVal, ByteCnt2, sizeof(u16SrcData)/2U);
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, (uint16_t *)&u16SrcData, CRC16_InitVal, sizeof(u16SrcData)/2U, CRC_BW_16);
        if(u32CRC16Data != u16Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }
        u32CRC32Data = CalaCRC32((uint8_t *)&u16SrcData, CRC32_InitVal, ByteCnt2, sizeof(u16SrcData)/2U);
        u32Checksum  = CRC_Calculate(CRC_CRC32, (uint16_t *)&u16SrcData, CRC32_InitVal, sizeof(u16SrcData)/2U, CRC_BW_16);
        if(u32CRC32Data != u32Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }

        /* Calculates word data's CRC16 checksum and CRC32 checksum. */
        u32CRC16Data = CalaCRC16((uint8_t *)&u32SrcData, CRC16_InitVal, ByteCnt4, sizeof(u32SrcData)/4U);
        u16Checksum  = (uint16_t)CRC_Calculate(CRC_CRC16, (uint32_t *)&u32SrcData, CRC16_InitVal, sizeof(u32SrcData)/4U, CRC_BW_32);
        if(u32CRC16Data != u16Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }
        u32CRC32Data = CalaCRC32((uint8_t *)&u32SrcData, CRC32_InitVal,ByteCnt4, sizeof(u32SrcData)/4U);
        u32Checksum  = CRC_Calculate(CRC_CRC32, (uint32_t *)&u32SrcData, CRC32_InitVal, sizeof(u32SrcData)/4U, CRC_BW_32);
        if(u32CRC32Data != u32Checksum)
        {
            BSP_LED_On(LED_RED);
            BSP_LED_Off(LED_BLUE);
        }
    }
}


/**
 * @brief CRC-16 calculation.
 * @param  [in]   pu8Data               Pointer to the buffer containing the data to be computed.
 * @param  [in]   u32InitVal            Initialize the CRC calculation.
 * @param  [in]   u8ByteWidth           Byte width of the data.
 * @param  [in]   u32Length             The length of the data to be computed.
 * @retval crc
 */

uint16_t CalaCRC16(const uint8_t *pu8Data, uint32_t u32InitVal, uint8_t u8ByteWidth, uint32_t u32Length)
{
    uint32_t i = 0U,j = 0U;
    uint32_t Temp = (uint32_t)pu8Data;
    uint16_t crc = (uint16_t)u32InitVal; /*  Initial value */

    while(u32Length--)
    {
        i = u8ByteWidth;
        while(i--)
        {
            crc ^= *(uint8_t *)Temp;
            Temp ++;
            for (j = 0U; j < 8U; j++)
            {     
                if (crc & 0x1U)
                {
                    crc >>= 1U;
                    crc ^= 0x8408U;  /* 0x8408 = reverse 0x1021 */
                }
                else
                {
                    crc >>= 1U;
                }
            }
       }

    }

    crc =~crc;

    return crc;
}


/**
 * @brief CRC-32 calculation.
 * @param  [in]   pu8Data               Pointer to the buffer containing the data to be computed.
 * @param  [in]   u32InitVal            Initialize the CRC calculation.
 * @param  [in]   u8ByteWidth           Byte width of the data.
 * @param  [in]   u32Length             The length of the data to be computed.
 * @retval crc
 */
uint32_t CalaCRC32(const uint8_t *pu8Data, uint32_t u32InitVal, uint8_t u8ByteWidth, uint32_t u32Length)  
{
    uint32_t i = 0U, j = 0U;
    uint32_t Temp = (uint32_t)pu8Data;
    uint32_t crc = u32InitVal; /*  Initial value */ 

    while(u32Length--)
    {
        i = u8ByteWidth;
        while(i--)
        {
            crc ^= *(uint8_t *)Temp;
            Temp ++;
            for (j = 0U; j < 8U; j++)
            {
                if (crc & 0x1U)
                {
                    crc = (crc >> 1U) ^ 0xEDB88320UL; /*0xEDB88320= reverse 0x04C11DB7*/
                }
                else
                {
                crc = (crc >> 1U);
                }
            }
        }
    }
    crc =~crc;

    return crc;
}  
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
