/**
 *******************************************************************************
 * @file  hc32f4a0_dac.c
 * @brief This file provides firmware functions to manage the Digital-to-Analog
 *        Converter(DAC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-09       Hexiao          First version
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
#include "hc32f4a0_dac.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DAC DAC
 * @brief DAC Driver Library
 * @{
 */

#if (DDL_DAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DAC_Local_Macros DAC Local Macros
 * @{
 */

/**
 * @defgroup DAC_Check_Parameters_Validity DAC Check Parameters Validity
 * @{
 */

#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_DAC1)                               ||                          \
    ((x) == M4_DAC2))

#define IS_VALID_ADCPRIO_CONFIG(x)   (0U == ((x) & (uint16_t)(~DAC_ADPCR_CONFIG_ALL)))


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
 * @defgroup DAC_Global_Functions DAC Global Functions
 * @{
 */

/**
 * @brief  ADC priority function command
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enNewState           New state of the ADC priority function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void DAC_ADCPrioCmd(M4_DAC_TypeDef* pstcDACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG16(pstcDACx->DAADPCR, DAC_DAADPCR_ADPEN, (uint32_t)enNewState << DAC_DAADPCR_ADPEN_POS);
}

/**
 * @brief  ADC priority function configuration
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] u32ADCxConfig        The ADCx priority to be configured
 *         This parameter can be one or any combination of the following values:
 *         - DAC_DAADPCR_ADPSL1
 *         - DAC_DAADPCR_ADPSL2
 *         - DAC_DAADPCR_ADPSL3
 * @retval None
 */
void DAC_ADCPrioConfig(M4_DAC_TypeDef* pstcDACx, uint16_t u16ADCxConfig)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_VALID_ADCPRIO_CONFIG(u16ADCxConfig));

    MODIFY_REG16(pstcDACx->DAADPCR, DAC_ADPCR_CONFIG_ALL, u16ADCxConfig);
}

/**
 * @brief  DAC channel 1 and channel 2 function command
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enNewState    New state of DAC channel 1 and channel 2 function,
 *                            @ref en_functional_state_t
 * @retval None
 */
void DAC_ChannelAllCmd(M4_DAC_TypeDef* pstcDACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG16(pstcDACx->DACR, DAC_DACR_DAE, (uint32_t)enNewState << DAC_DACR_DAE_POS);
}

/**
 * @brief  DAC channel 1 or channel 2 function command
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enCh          The selected DAC channel
 *                            @ref en_dac_ch_t 
 * @param  [in] enNewState    New state of DAC channel 1 or channel 2 function,
 *                            @ref en_functional_state_t
 * @retval An en_result_t enumeration value:
 *         - Ok: No errors occurred
 *         - ErrorInvalidMode: cannot enable or disable single channel when \n
 *                           these two channels have been enabled by \n
 *                           DAC_ChannelAllCmd @ref DAC_ChannelAllCmd
 */
en_result_t DAC_ChannelCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    en_result_t ret = Ok;
    if(pstcDACx->DACR & DAC_DACR_DAE)
    {
      ret = ErrorInvalidMode;
    }
    else
    {
      MODIFY_REG16(pstcDACx->DACR, (uint16_t)1U << (DAC_DACR_DA1E_POS + enCh)\
                 , (uint32_t)enNewState << (DAC_DACR_DA1E_POS + enCh));
    }

    return ret;
}

/**
 * @brief  DAC output function command
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enNewState           New state of the DAC output function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void DAC_OutputCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    uint16_t u16State = enNewState;
    MODIFY_REG16(pstcDACx->DAOCR, (uint16_t)1U << (DAC_DAOCR_DAODIS1_POS + enCh)\
                 , (uint16_t)(~u16State) << (DAC_DAOCR_DAODIS1_POS + enCh));
}

/**
 * @brief  DAC AMP function command
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enCh                The selected DAC channel
 *                                   @ref en_dac_ch_t 
 * @param  [in] enNewState           New state of the AMP function,
 *                                   @ref en_functional_state_t
 * @retval An en_result_t enumeration value:
 *         - Ok: No errors occurred
 *         - ErrorInvalidMode: cannot enable AMP when data source is from DCU
 */
en_result_t DAC_AMPCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    en_result_t ret = Ok;
    uint16_t u16CmdPos = (uint16_t)DAC_DACR_EXTDSL1_POS + enCh;
    if(1U & (pstcDACx->DACR >> u16CmdPos))
    {
      ret = ErrorInvalidMode;
    }
    else
    {
      u16CmdPos = (uint16_t)DAC_DACR_DAAMP1_POS + enCh;
      MODIFY_REG16(pstcDACx->DACR, (uint16_t)1U << u16CmdPos, (uint32_t)enNewState << u16CmdPos);
    }

    return ret;
}

/**
 * @brief  DAC data pattern configuration
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enAlign            Specify the data alignment
 *                                 @ref en_dac_align_t
 * @retval None
 */
void DAC_DataPatternConfig(M4_DAC_TypeDef* pstcDACx, en_dac_align_t enAlign)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    MODIFY_REG16(pstcDACx->DACR, DAC_DACR_DPSEL , (uint32_t)enAlign << DAC_DACR_DPSEL_POS);
}

/**
 * @brief  Set DAC data source 
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] enCh               The selected DAC channel
 *                                 @ref en_dac_ch_t 
 * @param  [in] src                Data source of DAC
 *                                 @arg DAC_Data_From_DataReg
 *                                 @arg DAC_Data_From_DCU
 * @retval None
 */
void DAC_SetDataSource(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_dac_src_t src)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcDACx));
    uint16_t u16CmdPos = (uint16_t)DAC_DACR_EXTDSL1_POS + enCh;
    MODIFY_REG16(pstcDACx->DACR, (uint16_t)1U << u16CmdPos, (uint32_t)src << u16CmdPos);
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* DDL_DAC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
