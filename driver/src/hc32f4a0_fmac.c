/**
 *******************************************************************************
 * @file  hc32f4a0_fmac.c
 * @brief This file provides firmware functions to manage the Filter Math 
 *        Accelerote (FMAC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-19       Heqb          First version
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
#include "hc32f4a0_fmac.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_FMAC FMAC
 * @brief FMAC Driver Library
 * @{
 */

#if (DDL_FMAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FMAC_Local_Macros FMAC Local Macros
 * @{
 */

/**
 * @defgroup FMAC_Check_Parameters_Validity FMAC Check Parameters Validity
 * @{
 */
#define IS_FMAC_FILTER_SHIFT(x)                                              \
(   ((x) == FMAC_FILTER_SHIFT_0BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_1BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_2BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_3BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_4BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_5BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_6BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_7BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_8BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_9BIT)               ||                         \
    ((x) == FMAC_FILTER_SHIFT_10BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_11BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_12BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_13BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_14BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_15BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_16BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_17BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_18BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_19BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_20BIT)              ||                         \
    ((x) == FMAC_FILTER_SHIFT_21BIT))

#define IS_FMAC_FILTER_STAGE(x)                                              \
(   ((x) == FMAC_FILTER_STAGE_0)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_1)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_2)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_3)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_4)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_5)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_6)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_7)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_8)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_9)                  ||                         \
    ((x) == FMAC_FILTER_STAGE_10)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_11)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_12)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_13)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_14)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_15)                 ||                         \
    ((x) == FMAC_FILTER_STAGE_16))

#define IS_VALID_UNIT(x)                                                     \
(   ((x) == M4_FMAC1)                             ||                         \
    ((x) == M4_FMAC2)                             ||                         \
    ((x) == M4_FMAC3)                             ||                         \
    ((x) == M4_FMAC4))
/**
 * @}
 */


/**
 * @}
 */

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
 * @defgroup FMAC_Global_Functions FMAC Global Functions
 * @{
 */

/**
 * @brief  FMAC peripheral initialization stucture clear
 * @param  [in] pstcInitStruct    FMAC function structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_StructInit(stc_fmac_init_t* pstcInitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInitStruct != NULL)
    {
        pstcInitStruct->u8FiltStage  = FMAC_FILTER_STAGE_0;
        pstcInitStruct->u8FiltShift  = FMAC_FILTER_SHIFT_0BIT;
        pstcInitStruct->FiltFactor   = 0;
        pstcInitStruct->enFmacIntCmd = Disable;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  De-Initialize FMAC function
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_DeInit(M4_FMAC_TypeDef* FMACx)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));

    WRITE_REG32(FMACx->CTR, 0UL);
    WRITE_REG32(FMACx->IER, 0UL);
    WRITE_REG32(FMACx->DTR, 0UL);
    WRITE_REG32(FMACx->RTR0, 0UL);
    WRITE_REG32(FMACx->RTR1, 0UL);
    WRITE_REG32(FMACx->STR, 0UL);
    enRet = Ok;
    return enRet;
}

/**
 * @brief  FMAC peripheral function initialize
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1              FMAC unit 1 instance register base
 *   @arg  M4_FMAC2              FMAC unit 2 instance register base
 *   @arg  M4_FMAC3              FMAC unit 3 instance register base
 *   @arg  M4_FMAC4              FMAC unit 4 instance register base
 * @param  [in] pstcFmacInit     FMAC function base parameter structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_Init(M4_FMAC_TypeDef* FMACx, const stc_fmac_init_t *pstcFmacInit)
{
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t *FMAC_CORx;
    uint8_t u8temp = 0U; 
    if(pstcFmacInit != NULL)
    {
        enRet = Ok;
        DDL_ASSERT(IS_VALID_UNIT(FMACx));
        DDL_ASSERT(IS_FMAC_FILTER_SHIFT(pstcFmacInit->u8FiltShift));
        DDL_ASSERT(IS_FMAC_FILTER_STAGE(pstcFmacInit->u8FiltStage));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcFmacInit->enFmacIntCmd));
        u8temp = pstcFmacInit->u8FiltStage;
        /* Configure filter stage and results right shift bits */
        FMACx->CTR = (pstcFmacInit->u8FiltStage | \
                     ((uint32_t)pstcFmacInit->u8FiltShift << FMAC_CTR_SHIFT_POS));
        /* Configure interrupt command */
        FMACx->IER = pstcFmacInit->enFmacIntCmd;
        do{
            FMAC_CORx = (uint32_t *)((uint32_t)(&FMACx->COR0) + ((uint32_t)u8temp << 2U));
            *FMAC_CORx = (uint32_t)pstcFmacInit->FiltFactor;
        }while(u8temp--);
    }
    return enRet;
}

/**
 * @brief  Enable or Disable FMAC
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @param  [in] enNewState      Disable or Enable the function
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_Cmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    FMACx->ENR = (uint32_t)enNewState;
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set Filter result shift bits.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @param  [in] u8ShiftNum      Result shift times.
 * This parameter can be set 0-21
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_SetResultShift(M4_FMAC_TypeDef* FMACx, uint8_t u8ShiftNum)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FILTER_SHIFT(u8ShiftNum));
    /* Set Filter result shift bits */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_SHIFT, (uint32_t)u8ShiftNum << FMAC_CTR_SHIFT_POS);
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set filter stage number and filter factor.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @param  [in] u8filterStage   FMAC filter stage number.
 * This parameter can be set 0 ~ 16
 * @param  [in] factor          FMAC filter factor.
 * This parameter can be set -32768 ~ 32767
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_SetStageFactor(M4_FMAC_TypeDef* FMACx, uint8_t u8filterStage, int16_t factor)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint16_t *FMAC_CORx;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FILTER_STAGE(u8filterStage));
    /* FMAC Software reset */
    FMACx->ENR = FMAC_FUNC_DISABLE;
    FMACx->ENR = FMAC_FUNC_ENABLE;
    /* Set filter stage number */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_STAGE_NUM, u8filterStage);
    do
    {
        FMAC_CORx = (uint16_t*)((uint32_t)(&FMACx->COR0) + ((uint32_t)u8filterStage << 2U));
        *FMAC_CORx = (uint16_t)factor;
    }while(u8filterStage--);
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Configure interrupt command.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @param  [in] enNewState      Disable or Enable the function.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_IntCmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    FMACx->IER = (uint32_t)enNewState;
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Data input.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @param  [in] FIRData         Data that needs to be processed.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_FIRInput(M4_FMAC_TypeDef* FMACx, int16_t FIRData)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    FMACx->DTR = (uint32_t)FIRData;
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Get FMAC status.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @retval Set                  Calculate complete
 *         Reset                Calculation in progress
 */
en_flag_status_t FMAC_GetStatus(const M4_FMAC_TypeDef* FMACx)
{
    uint32_t enRet = 0U;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    enRet = FMACx->STR & FMAC_STR_READY;

    return (enRet ? Set : Reset);
}

/**
 * @brief  Get calculation results.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4             FMAC unit 4 instance register base
 * @retval An stc_fmac_result_t structure value:
 *         u32ResultHigh        The high value of the result
 *         u32ResultLow         The low value of the result
 */
 stc_fmac_result_t FMAC_GetResult(const M4_FMAC_TypeDef* FMACx)
{
    stc_fmac_result_t stcResult;
    stcResult.u32ResultHigh = FMACx->RTR0;
    stcResult.u32ResultLow  = FMACx->RTR1;

    return stcResult;
}

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
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

