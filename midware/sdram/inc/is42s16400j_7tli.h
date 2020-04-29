/**
 *******************************************************************************
 * @file  is42s16400j_7tli.h
 * @brief This file contains all the functions prototypes of the SDRAM midware
 *        library for is42s16400j_7tli.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-09       Hongjh          First version
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
#ifndef __IS42S16400J_7TLI_H__
#define __IS42S16400J_7TLI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_dmc.h"

/**
 * @addtogroup HC32F4A0_DDL_Midware
 * @{
 */

/**
 * @addtogroup MW_SDRAM
 * @{
 */

#if (MW_SDRAM_IS42S16400J7TLI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SDRAM_IS42S16400J_Global_Macros SDRAM IS42S16400J Global Macros
 * @{
 */

/**
 * @defgroup IS42S16400J_Map_DMC_Chip IS42S16400J Map DMC Chip
 * @{
 */
#define IS42S16400J_MAP_DMC_CHIP                (EXMC_DMC_CHIP_1)
/**
 * @}
 */

/**
 * @defgroup SDRAM_Address_Space SDRAM Address Space
 * @note SRAM address:[0x80000000, 0x807FFFFF] / size: 8M bytes
 * @{
 */
#define SDRAM_IS42S_START_ADDR                  (EXMC_DMC_ChipStartAddress(IS42S16400J_MAP_DMC_CHIP))
#define SDRAM_IS42S_SIZE                        (8UL * 1024UL * 1024UL)     /* 8MBytes*/
#define SDRAM_IS42S_END_ADDR                    (SDRAM_IS42S_START_ADDR + SDRAM_IS42S_SIZE - 1UL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup IS42S16400J7TLI_Global_Functions IS42S16400J7TLI Global Functions
 * @{
 */
void IS42S_Init(void);

en_result_t IS42S_WriteMem8(const uint8_t au8Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);
en_result_t IS42S_ReadMem8(uint8_t au8Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);
en_result_t IS42S_WriteMem16(const uint16_t au16Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);
en_result_t IS42S_ReadMem16(uint16_t au16Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);
en_result_t IS42S_WriteMem32(const uint32_t au32Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);
en_result_t IS42S_ReadMem32(uint32_t au32Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size);

/**
 * @}
 */

#endif /* MW_SDRAM_IS42S16400J7TLI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __IS42S16400J_7TLI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
