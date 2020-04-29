/**
 *******************************************************************************
 * @file  hc32f4a0_keyscan.h
 * @brief This file contains all the functions prototypes of the KEYSCAN driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-23       Zhangxl         First version
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
#ifndef __HC32F4A0_KEYSCAN_H__
#define __HC32F4A0_KEYSCAN_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_KEYSCAN
 * @{
 */

#if (DDL_KEYSCAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup KEYSCAN_Global_Types KEYSCAN Global Types
 * @{
 */

/**
 * @brief  KEYSCAN configuration
 */
typedef struct stc_keyscan_init
{
    uint32_t u32HizCycle;           /*!< Specifies the KEYSCAN Hiz cycles.
                                        This parameter can be a value of @ref KEYSCAN_Hiz_Cycle_Sel */

    uint32_t u32LowCycle;           /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Low_Cycle_Sel */

    uint32_t u32KeyClk;             /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Clock_Sel */

    uint32_t u32Keyout;             /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Keyout_Sel */

    uint32_t u32Keyin;              /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Keyin_Sel */
} stc_keyscan_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup KEYSCAN_Global_Macros KEYSCAN Global Macros
 * @{
 */

/**
 * @defgroup KEYSCAN_Hiz_Cycle_Sel KEYSCAN Hiz cycles during low ouput selection
 * @{
 */
#define KEYSCAN_HIZ_CLC_4       ((uint32_t)(0x00UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 4 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_8       ((uint32_t)(0x01UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 8 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_16      ((uint32_t)(0x02UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 16 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_32      ((uint32_t)(0x03UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 32 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_64      ((uint32_t)(0x04UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 64 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_256     ((uint32_t)(0x05UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 256 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_512     ((uint32_t)(0x06UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 512 cycles during low ouput */
#define KEYSCAN_HIZ_CLC_1024    ((uint32_t)(0x07UL << KEYSCAN_SCR_T_HIZ_POS))       /*!< KEYSCAN HiZ keep 1024 cycles during low ouput */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Low_Cycle_Sel KEYSCAN low level output cycles selection
 * @{
 */
#define KEYSCAN_LOW_CLC_4       ((uint32_t)(0x02UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^2=4 cycles */
#define KEYSCAN_LOW_CLC_8       ((uint32_t)(0x03UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^3=8 cycles */
#define KEYSCAN_LOW_CLC_16      ((uint32_t)(0x04UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^4=16 cycles */
#define KEYSCAN_LOW_CLC_32      ((uint32_t)(0x05UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^5=32 cycles */
#define KEYSCAN_LOW_CLC_64      ((uint32_t)(0x06UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^6=64 cycles */
#define KEYSCAN_LOW_CLC_128     ((uint32_t)(0x07UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^7=128 cycles */
#define KEYSCAN_LOW_CLC_256     ((uint32_t)(0x08UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^8=256 cycles */
#define KEYSCAN_LOW_CLC_512     ((uint32_t)(0x09UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^9=512 cycles */
#define KEYSCAN_LOW_CLC_1K      ((uint32_t)(0x0AUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^10=1K cycles */
#define KEYSCAN_LOW_CLC_2K      ((uint32_t)(0x0BUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^11=2K cycles */
#define KEYSCAN_LOW_CLC_4K      ((uint32_t)(0x0CUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^12=4K cycles */
#define KEYSCAN_LOW_CLC_8K      ((uint32_t)(0x0DUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^13=8K cycles */
#define KEYSCAN_LOW_CLC_16K     ((uint32_t)(0x0EUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^14=16K cycles */
#define KEYSCAN_LOW_CLC_32K     ((uint32_t)(0x0FUL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^15=32K cycles */
#define KEYSCAN_LOW_CLC_64K     ((uint32_t)(0x10UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^16=64K cycles */
#define KEYSCAN_LOW_CLC_128K    ((uint32_t)(0x11UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^17=128K cycles */
#define KEYSCAN_LOW_CLC_256K    ((uint32_t)(0x12UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^18=256K cycles */
#define KEYSCAN_LOW_CLC_512K    ((uint32_t)(0x13UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^19=512K cycles */
#define KEYSCAN_LOW_CLC_1M      ((uint32_t)(0x14UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^20=1M cycles */
#define KEYSCAN_LOW_CLC_2M      ((uint32_t)(0x15UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^21=2M cycles */
#define KEYSCAN_LOW_CLC_4M      ((uint32_t)(0x16UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^22=4M cycles */
#define KEYSCAN_LOW_CLC_8M      ((uint32_t)(0x17UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^23=8M cycles */
#define KEYSCAN_LOW_CLC_16M     ((uint32_t)(0x18UL << KEYSCAN_SCR_T_LLEVEL_POS))    /*!< KEYSCAN low level output is 2^24=16M cycles */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Clock_Sel KEYSCAN scan clock selection
 * @{
 */
#define KEYSCAN_CLK_HCLK        ((uint32_t)(0x00UL << KEYSCAN_SCR_CKSEL_POS))       /*!< KEYSCAN low level output is 2^2=4 cycles */
#define KEYSCAN_CLK_LRC         ((uint32_t)(0x01UL << KEYSCAN_SCR_CKSEL_POS))       /*!< KEYSCAN low level output is 2^3=8 cycles */
#define KEYSCAN_CLK_XTAL32      ((uint32_t)(0x02UL << KEYSCAN_SCR_CKSEL_POS))       /*!< KEYSCAN low level output is 2^4=16 cycles */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Keyout_Sel KEYSCAN keyout pins selection
 * @{
 */
#define KEYSCAN_OUT_0T1         ((uint32_t)(0x01UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 1 are selected */
#define KEYSCAN_OUT_0T2         ((uint32_t)(0x02UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 2 are selected */
#define KEYSCAN_OUT_0T3         ((uint32_t)(0x03UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 3 are selected */
#define KEYSCAN_OUT_0T4         ((uint32_t)(0x04UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 4 are selected */
#define KEYSCAN_OUT_0T5         ((uint32_t)(0x05UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 5 are selected */
#define KEYSCAN_OUT_0T6         ((uint32_t)(0x06UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 6 are selected */
#define KEYSCAN_OUT_0T7         ((uint32_t)(0x07UL << KEYSCAN_SCR_KEYOUTSEL_POS))   /*!< KEYOUT 0 ~ 7 are selected */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Keyin_Sel KEYSCAN keyin pins selection
 * @{
 */
#define KEYSCAN_IN_0            ((uint32_t)(0x0001UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 0 is selected */
#define KEYSCAN_IN_1            ((uint32_t)(0x0002UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 1 is selected */
#define KEYSCAN_IN_2            ((uint32_t)(0x0004UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 2 is selected */
#define KEYSCAN_IN_3            ((uint32_t)(0x0008UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 3 is selected */
#define KEYSCAN_IN_4            ((uint32_t)(0x0010UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 4 is selected */
#define KEYSCAN_IN_5            ((uint32_t)(0x0020UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 5 is selected */
#define KEYSCAN_IN_6            ((uint32_t)(0x0040UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 6 is selected */
#define KEYSCAN_IN_7            ((uint32_t)(0x0080UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 7 is selected */
#define KEYSCAN_IN_8            ((uint32_t)(0x0100UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 8  is selected */
#define KEYSCAN_IN_9            ((uint32_t)(0x0200UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 9  is selected */
#define KEYSCAN_IN_10           ((uint32_t)(0x0400UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 10 is selected */
#define KEYSCAN_IN_11           ((uint32_t)(0x0800UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 11 is selected */
#define KEYSCAN_IN_12           ((uint32_t)(0x1000UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 12 is selected */
#define KEYSCAN_IN_13           ((uint32_t)(0x2000UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 13 is selected */
#define KEYSCAN_IN_14           ((uint32_t)(0x4000UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 14 is selected */
#define KEYSCAN_IN_15           ((uint32_t)(0x8000UL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) 15 is selected */
#define KEYSCAN_IN_MASK         ((uint32_t)(0xFFFFUL << KEYSCAN_SCR_KEYINSEL_POS))    /*!< KEYIN(EIRQ) mask */

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
 * @addtogroup KEYSCAN_Global_Functions
 * @{
 */
en_result_t KEYSCAN_StructInit(stc_keyscan_init_t *pstcKeyscanInit);
en_result_t KEYSCAN_Init(const stc_keyscan_init_t *pstcKeyscanInit);
void KEYSCAN_Cmd(en_functional_state_t enNewState);
uint32_t KEYSCAN_GetKeyoutIdx(void);

/**
 * @}
 */

#endif /* DDL_KEYSCAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_KEYSCAN_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/