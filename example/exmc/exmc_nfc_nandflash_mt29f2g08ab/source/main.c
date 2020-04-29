/**
 *******************************************************************************
 * @file  exmc/exmc_nfc_nandflash_mt29f2g08ab/source/main.c
 * @brief This example demonstrates NADN Flash function.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-17       Hongjh          First version
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
#include <string.h>

#include "hc32_ddl.h"
#include "1bit_per_512byte_ecc.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup EXMC_NFC_Nandflash
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define DATA_META_WITHOUT_SPARE_LEN         (MT29F2G08AB_PAGE_SIZE_WITHOUT_SPARE)
#define DATA_META_WITH_SPARE_LEN            (MT29F2G08AB_PAGE_SIZE_WITH_SPARE)
#define DATA_HWECC_WITH_SPARE_LEN           (MT29F2G08AB_PAGE_SIZE_WITH_SPARE)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static en_result_t MT29F2G08AB_ProgramMetaWithoutSpare(uint32_t u32Page);
static en_result_t MT29F2G08AB_ProgramMetaWithSpare(uint32_t u32Page);
static en_result_t MT29F2G08AB_ProgramHwEcc1Bit(uint32_t u32Page);
static en_result_t MT29F2G08AB_ProgramHwEcc4Bits(uint32_t u32Page);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  nandflash program test without ECC and spare
 * @param  [in] u32Page                 Program page
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       Errors occurred.
 */
static en_result_t MT29F2G08AB_ProgramMetaWithoutSpare(uint32_t u32Page)
{
    en_result_t enRet = Ok;

    __ALIGN_BEGIN static uint8_t m_au8ReadDataMeta[DATA_META_WITHOUT_SPARE_LEN];
    __ALIGN_BEGIN static uint8_t m_au8WriteDataMeta[DATA_META_WITHOUT_SPARE_LEN];

    /* Initialize data. */
    for (uint16_t i = 0U; i < DATA_META_WITHOUT_SPARE_LEN; i++)
    {
        m_au8WriteDataMeta[i] = (uint8_t)i;
    }

    if (Ok == MT29F2G08AB_WritePageMeta(u32Page, m_au8WriteDataMeta, DATA_META_WITHOUT_SPARE_LEN))
    {
        if (Ok == MT29F2G08AB_ReadPageMeta(u32Page, m_au8ReadDataMeta, DATA_META_WITHOUT_SPARE_LEN))
        {
            /* Verify write/read data. */
            for (uint32_t i = 0UL; i < DATA_META_WITHOUT_SPARE_LEN; i++)
            {
                if (m_au8WriteDataMeta[i] != m_au8ReadDataMeta[i])
                {
                    enRet = Error;
                }
            }
        }
    }
    else
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief  nandflash program test without ECC
 * @param  [in] u32Page                 Program page
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       Errors occurred.
 */
static en_result_t MT29F2G08AB_ProgramMetaWithSpare(uint32_t u32Page)
{
    en_result_t enRet = Ok;

    __ALIGN_BEGIN static uint8_t m_au8ReadDataMetaWithSpare[DATA_META_WITH_SPARE_LEN];
    __ALIGN_BEGIN static uint8_t m_au8WriteDataMetaWithSpare[DATA_META_WITH_SPARE_LEN];

    /* Initialize data. */
    for (uint16_t i = 0U; i < DATA_META_WITH_SPARE_LEN; i++)
    {
        m_au8WriteDataMetaWithSpare[i] = (uint8_t)i;
    }

    if (Ok == MT29F2G08AB_WritePageMeta(u32Page, m_au8WriteDataMetaWithSpare, DATA_META_WITH_SPARE_LEN))
    {
        if (Ok == MT29F2G08AB_ReadPageMeta(u32Page, m_au8ReadDataMetaWithSpare, DATA_META_WITH_SPARE_LEN))
        {
            /* Verify write/read data. */
            for (uint32_t i = 0UL; i < DATA_META_WITH_SPARE_LEN; i++)
            {
                if (m_au8WriteDataMetaWithSpare[i] != m_au8ReadDataMetaWithSpare[i])
                {
                    enRet = Error;
                }
            }
        }
    }
    else
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief  nandflash program test with hardware ECC 1 bit
 * @param  [in] u32Page                 Program page
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       Errors occurred.
 */
static en_result_t MT29F2G08AB_ProgramHwEcc1Bit(uint32_t u32Page)
{
    uint32_t i = 0UL;
    uint32_t u32EccTestResult = 0UL;
    uint32_t u32EccExpectedResult = 0UL;
    en_result_t enRet = Error;

    __ALIGN_BEGIN static uint8_t m_au8ReadDataHwEcc[DATA_HWECC_WITH_SPARE_LEN];
    __ALIGN_BEGIN static uint8_t m_au8WriteDataHwEcc[DATA_HWECC_WITH_SPARE_LEN];
    __ALIGN_BEGIN static uint8_t m_au8SwEcc1Bit[MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE];

    /* Initialize data. */
    for (i = 0U; i < DATA_HWECC_WITH_SPARE_LEN; i++)
    {
        m_au8WriteDataHwEcc[i] = (uint8_t)(i);
    }

    EXMC_NFC_SetEccMode(EXMC_NFC_ECC_1BIT);

    if (Ok == MT29F2G08AB_WritePageHwEcc(u32Page, \
                                        m_au8WriteDataHwEcc, \
                                        (DATA_HWECC_WITH_SPARE_LEN - MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE), \
                                        MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE))
    {
        MT29F2G08AB_ReadPageMeta(u32Page, m_au8ReadDataHwEcc, DATA_META_WITH_SPARE_LEN);
        sw_calculate_nand_ecc(&m_au8WriteDataHwEcc[0], &m_au8SwEcc1Bit[0], 512U);
        sw_calculate_nand_ecc(&m_au8WriteDataHwEcc[512], &m_au8SwEcc1Bit[3], 512U);
        sw_calculate_nand_ecc(&m_au8WriteDataHwEcc[1024], &m_au8SwEcc1Bit[6], 512U);
        sw_calculate_nand_ecc(&m_au8WriteDataHwEcc[1536], &m_au8SwEcc1Bit[9], 512U);

        if (0 == memcmp (m_au8SwEcc1Bit, \
                    &m_au8ReadDataHwEcc[DATA_HWECC_WITH_SPARE_LEN - MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE], \
                    MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE))
        {
            m_au8ReadDataHwEcc[1] = 0x00U;  /* Modify the second byte value from 0x01 to 0x00 */
            u32EccExpectedResult = (EXMC_NFC_1BIT_ECC_SINGLE_BIT_ERR | (1UL << 3UL)); /* Single bit error & the second byte: bit 0 */

            MT29F2G08AB_WritePageMeta(u32Page, m_au8ReadDataHwEcc, DATA_META_WITH_SPARE_LEN);
            MT29F2G08AB_ReadPageHwEcc(u32Page, \
                                      m_au8ReadDataHwEcc, \
                                      (DATA_HWECC_WITH_SPARE_LEN - MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE), \
                                      MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE);

            u32EccTestResult = EXMC_NFC_GetEccReg(EXMC_NFC_ECCR0);
            if (u32EccExpectedResult == u32EccTestResult)
            {
                enRet = Ok; /* The result meets the expected */
            }
        }
    }

    return enRet;
}

/**
 * @brief  nandflash program test with hardware ECC 4bits
 * @param  [in] u32Page                 Program page
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       Errors occurred.
 */
static en_result_t MT29F2G08AB_ProgramHwEcc4Bits(uint32_t u32Page)
{
    uint32_t i = 0UL;
    en_result_t enRet = Ok;
#if 0
    /* Initialize data. */
    for (i = 0U; i < DATA_HWECC_WITH_SPARE_LEN; i++)
    {
        m_au8WriteDataHwEcc[i] = (uint8_t)i;
    }

    EXMC_NFC_SetEccMode(EXMC_NFC_ECC_4BITS);

    if (Ok == MT29F2G08AB_WritePageHwEcc(u32Page, \
                                        m_au8WriteDataHwEcc, \
                                        (DATA_HWECC_WITH_SPARE_LEN - MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE), \
                                        MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE))
    {
        MT29F2G08AB_ReadPageHwEcc(u32Page, \
                                  m_au8ReadDataHwEcc, \
                                  (DATA_HWECC_WITH_SPARE_LEN - MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE), \
                                  MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE);

        MT29F2G08AB_ReadPageMeta(u32Page, m_au8ReadDataMetaWithSpare, DATA_META_WITH_SPARE_LEN);

        /* Verify write/read data. */
        for (i = 0UL; i < MT29F2G08AB_PAGE_SIZE_WITHOUT_SPARE; i++)
        {
            if ((m_au8WriteDataHwEcc[i] != m_au8ReadDataHwEcc[i]) || \
                (m_au8ReadDataMetaWithSpare[i] != m_au8ReadDataHwEcc[i]))
            {
                enRet = Error;
            }
        }
    }
    else
    {
        enRet = Error;
    }
#endif
    return enRet;
}

__IO uint8_t protect = 0UL;
/**
 * @brief  Main function of EXMC NFC project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t au8DevId[4];
    uint8_t u8TestErrCnt = 0U;

    /* Initialize system clock: */
    BSP_CLK_Init();

    /* PCLK0, HCLK  Max 240MHz */
    /* PCLK1, PCLK4 Max 120MHz */
    /* PCLK2, PCLK3 Max 60MHz  */
    /* EXCLK 60MHz */
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | \
                              CLK_PCLK2_DIV4 | CLK_PCLK3_DIV4 | \
                              CLK_PCLK4_DIV2 | CLK_EXCLK_DIV4 | CLK_HCLK_DIV1));

    /* Initialize LED */
    BSP_IO_Init();
    BSP_LED_Init();

    while (!protect)
    {}

    /* Configure nandflash */
    MT29F2G08AB_Init();

    /* Read id */
    MT29F2G08AB_ReadId(0UL, au8DevId, 4U);
    if ((au8DevId[0] == MT29F2G08ABAEA_MANUFACTURER_ID) || \
        (au8DevId[1] == MT29F2G08ABAEA_DEVICE_ID1) || \
        (au8DevId[2] == MT29F2G08ABAEA_DEVICE_ID2) || \
        (au8DevId[3] == MT29F2G08ABAEA_DEVICE_ID3))
    {
        /* Erase nandflash. */
        if (Ok == MT29F2G08AB_EraseBlock(0UL))
        {
            if (Ok != MT29F2G08AB_ProgramMetaWithoutSpare(0UL))
            {
                u8TestErrCnt++;
            }

            if (Ok != MT29F2G08AB_ProgramMetaWithSpare(1UL))
            {
                u8TestErrCnt++;
            }

            if (Ok != MT29F2G08AB_ProgramHwEcc1Bit(2UL))
            {
                u8TestErrCnt++;
            }
        }
        else
        {
            u8TestErrCnt++;
        }
    }
    else
    {
        u8TestErrCnt++;
    }

    if (u8TestErrCnt)
    {
        BSP_LED_On(LED_RED);
    }
    else
    {
        BSP_LED_On(LED_BLUE);
    }

    while (1)
    {
    }
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
