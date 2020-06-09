/**
 *******************************************************************************
 * @file  crc/crc_base/source/main.c
 * @brief Main program of CRC base for the Device Driver Library.
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
 * @addtogroup CRC_Base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CRC16_InitVal                 (0xFFFFU)
#define CRC32_InitVal                 (0xFFFFFFFFUL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of template project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t  u8SrcData[1U]  = {0x12};
    uint16_t u16SrcData[2U] = {0x2020,0x0527};
    uint32_t u32SrcData[3U] = {0x20200527UL,0x12345678UL,0x1111FFFFUL};
    uint8_t  u8CheckData[1U];
    uint16_t u16CheckData[1U];
    uint32_t u32CheckData[1U];
    uint16_t u16Checksum;
    uint32_t u32Checksum;

    /* Configures CRC. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_CRC, Enable); /* Enable CRC */

    /***************** Configuration end, application start **************/
    while (1)
    {
        /* Calculates byte data's CRC16 checksum and CRC32 checksum. */
        CRC_Calculate(CRC_CRC16, (uint8_t *)&u8SrcData[0U], CRC16_InitVal, 1U, CRC_BW_8);
        CRC_Calculate(CRC_CRC32, (uint8_t *)&u8SrcData[0U], CRC32_InitVal, 1U, CRC_BW_8);

        /* Calculates half word data's CRC16 checksum and CRC32 checksum. */
        CRC_Calculate(CRC_CRC16, (uint16_t *)&u16SrcData[0U], CRC16_InitVal, 2U, CRC_BW_16);
        CRC_Calculate(CRC_CRC32, (uint16_t *)&u16SrcData[0U], CRC32_InitVal, 2U, CRC_BW_16);

        /* Calculates word data's CRC16 checksum and CRC32 checksum. */
        CRC_Calculate(CRC_CRC16, (uint32_t *)&u32SrcData[0U], CRC16_InitVal, 3U, CRC_BW_32);
        CRC_Calculate(CRC_CRC32, (uint32_t *)&u32SrcData[0U], CRC32_InitVal, 3U, CRC_BW_32);

        /* Checks byte data's CRC16 checksum and CRC32 checksum. */
        u8CheckData[0U] = 0xC8U;
        u16Checksum   = 0xBA3CU;
        CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, (uint8_t *)&u8CheckData[0U], CRC16_InitVal, 1U, CRC_BW_8);
        u32Checksum   = 0x47BDA50FUL;
        CRC_Check(CRC_CRC32, u32Checksum, (uint8_t *)&u8CheckData[0U], CRC32_InitVal, 1U, CRC_BW_8);

        /* Checks half word data's CRC16 checksum and CRC32 checksum. */
        u16CheckData[0U] = 0x1234U;
        u16Checksum    = 0xED16U;
        CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, (uint16_t *)&u16CheckData[0U], CRC16_InitVal, 1U, CRC_BW_16);
        u32Checksum    = 0x094A9040UL;
        CRC_Check(CRC_CRC32, u32Checksum, (uint16_t *)&u16CheckData[0U], CRC32_InitVal, 1U, CRC_BW_16);

        /* Checks word data's CRC16 checksum and CRC32 checksum. */
        u32CheckData[0u] = 0x12345678UL;
        u16Checksum    = 0xF428U;
        CRC_Check(CRC_CRC16, (uint32_t)u16Checksum, (uint32_t *)&u32CheckData[0U], CRC16_InitVal, 1U, CRC_BW_32);
        u32Checksum    = 0xAF6D87D2UL;
        CRC_Check(CRC_CRC32, u32Checksum, (uint32_t *)&u32CheckData[0U], CRC32_InitVal, 1U, CRC_BW_32);

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
