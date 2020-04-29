/**
 *******************************************************************************
 * @file  hc32f4a0_fmac.h
 * @brief This file contains all the functions prototypes of the FMAC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-19       Heqb         First version
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
#ifndef __HC32F4A0_FMAC_H__
#define __HC32F4A0_FMAC_H__

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
 * @addtogroup DDL_FMAC
 * @{
 */

#if (DDL_FMAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FMAC_Global_Types FMAC Global Types
 * @{
 */

/**
 * @brief FMAC configuration structure
 */
typedef struct
{
    uint8_t u8FiltStage;                /*!< FMAC filter stage number config.
                                             This parameter can be a value of @ref FMAC_Filter_stage.*/
    uint8_t u8FiltShift;                /*!< FMAC filter result right shift bits.
                                             This parameter can be a value of @ref FMAC_Filter_shift.*/
    int16_t  FiltFactor;                /*!< FMAC filter factor config.
                                             This parameter can be set -32768~32767 */
    en_functional_state_t enFmacIntCmd; /*!< Enable or disable FMAC interrupt.
                                             This parameter can be a value of @ref en_functional_state_t.*/
}stc_fmac_init_t;

/**
 * @brief FMAC result definition
 */
typedef struct
{
    uint32_t            u32ResultHigh;      /*!< The high value of the result.    */
    uint32_t            u32ResultLow;       /*!< The low value of the result.     */

} stc_fmac_result_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup FMAC_Global_Macros FMAC Global Macros
 * @{
 */

/**
 * @defgroup FMAC_ENABLE FMAC Enable or Disable
 * @{
 */
#define FMAC_FUNC_ENABLE              (FMAC_ENR_FMACEN)
#define FMAC_FUNC_DISABLE             ((uint32_t)0x00000000U)
/**
 * @}
 */

/** @defgroup FMAC_Filter_shift FMAC filter shift times
  * @{
  */
#define FMAC_FILTER_SHIFT_0BIT        ((uint8_t)0U)
#define FMAC_FILTER_SHIFT_1BIT        ((uint8_t)1U)
#define FMAC_FILTER_SHIFT_2BIT        ((uint8_t)2U)
#define FMAC_FILTER_SHIFT_3BIT        ((uint8_t)3U)
#define FMAC_FILTER_SHIFT_4BIT        ((uint8_t)4U)
#define FMAC_FILTER_SHIFT_5BIT        ((uint8_t)5U)
#define FMAC_FILTER_SHIFT_6BIT        ((uint8_t)6U)
#define FMAC_FILTER_SHIFT_7BIT        ((uint8_t)7U)
#define FMAC_FILTER_SHIFT_8BIT        ((uint8_t)8U)
#define FMAC_FILTER_SHIFT_9BIT        ((uint8_t)9U)
#define FMAC_FILTER_SHIFT_10BIT       ((uint8_t)10U)
#define FMAC_FILTER_SHIFT_11BIT       ((uint8_t)11U)
#define FMAC_FILTER_SHIFT_12BIT       ((uint8_t)12U)
#define FMAC_FILTER_SHIFT_13BIT       ((uint8_t)13U)
#define FMAC_FILTER_SHIFT_14BIT       ((uint8_t)14U)
#define FMAC_FILTER_SHIFT_15BIT       ((uint8_t)15U)
#define FMAC_FILTER_SHIFT_16BIT       ((uint8_t)16U)
#define FMAC_FILTER_SHIFT_17BIT       ((uint8_t)17U)
#define FMAC_FILTER_SHIFT_18BIT       ((uint8_t)18U)
#define FMAC_FILTER_SHIFT_19BIT       ((uint8_t)19U)
#define FMAC_FILTER_SHIFT_20BIT       ((uint8_t)20U)
#define FMAC_FILTER_SHIFT_21BIT       ((uint8_t)21U)
/**
 * @}
 */

/** @defgroup FMAC_Filter_stage FMAC filter stage number
  * @{
  */
#define FMAC_FILTER_STAGE_0          ((uint8_t)0U)
#define FMAC_FILTER_STAGE_1          ((uint8_t)1U)
#define FMAC_FILTER_STAGE_2          ((uint8_t)2U)
#define FMAC_FILTER_STAGE_3          ((uint8_t)3U)
#define FMAC_FILTER_STAGE_4          ((uint8_t)4U)
#define FMAC_FILTER_STAGE_5          ((uint8_t)5U)
#define FMAC_FILTER_STAGE_6          ((uint8_t)6U)
#define FMAC_FILTER_STAGE_7          ((uint8_t)7U)
#define FMAC_FILTER_STAGE_8          ((uint8_t)8U)
#define FMAC_FILTER_STAGE_9          ((uint8_t)9U)
#define FMAC_FILTER_STAGE_10         ((uint8_t)10U)
#define FMAC_FILTER_STAGE_11         ((uint8_t)11U)
#define FMAC_FILTER_STAGE_12         ((uint8_t)12U)
#define FMAC_FILTER_STAGE_13         ((uint8_t)13U)
#define FMAC_FILTER_STAGE_14         ((uint8_t)14U)
#define FMAC_FILTER_STAGE_15         ((uint8_t)15U)
#define FMAC_FILTER_STAGE_16         ((uint8_t)16U)
/**
 * @}
 */



/** @defgroup 
  * @{
  */

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
 * @addtogroup FMAC_Global_Functions
 * @{
 */
en_result_t FMAC_StructInit(stc_fmac_init_t* pstcInitStruct);
en_result_t FMAC_DeInit(M4_FMAC_TypeDef* FMACx);
en_result_t FMAC_Init(M4_FMAC_TypeDef* FMACx, const stc_fmac_init_t *pstcFmacInit);
en_result_t FMAC_Cmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState);
en_result_t FMAC_SetResultShift(M4_FMAC_TypeDef* FMACx, uint8_t u8ShiftNum);
en_result_t FMAC_FilterStageNum(M4_FMAC_TypeDef* FMACx, uint8_t u8filterStage);
en_result_t FMAC_SetStageFactor(M4_FMAC_TypeDef* FMACx, uint8_t u8filterStage, int16_t factor);
en_result_t FMAC_IntCmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState);
en_result_t FMAC_FIRInput(M4_FMAC_TypeDef* FMACx, int16_t FIRData);
en_flag_status_t FMAC_GetStatus(const M4_FMAC_TypeDef* FMACx);
stc_fmac_result_t FMAC_GetResult(const M4_FMAC_TypeDef* FMACx);
/**
 * @}
 */

#endif /* DDL_FMAC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_FMAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
