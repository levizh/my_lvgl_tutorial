/**
 *******************************************************************************
 * @file  hc32f4a0_dac.h
 * @brief This file contains all the functions prototypes of the DAC driver
 *        library.
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
#ifndef __HC32F4A0_DAC_H__
#define __HC32F4A0_DAC_H__

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
 * @addtogroup DDL_DAC
 * @{
 */

#if (DDL_DAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DAC_Global_Types DAC Global Types
 * @{
 */

/**
 * @brief DAC Channel
 */
typedef enum
{
    DAC_Channel_1 = 0U,
    DAC_Channel_2 = 1U,
} en_dac_ch_t;


/**
 * @brief DAC Data Align Type
 */
typedef enum
{
    DAC_Align_12b_R = 0U,
    DAC_Align_12b_L  = 1U,
} en_dac_align_t;

/**
 * @brief DAC Data Source
 */
typedef enum
{
    DAC_Data_From_DataReg = 0U,
    DAC_Data_From_DCU  = 1U,
} en_dac_src_t;

/**
 * @brief DAC Data State In ADC Priority Mode
 */
typedef enum
{
    DAC_Mode_Err  = -1,
    DAC_Convert_Completed = 0U,
    DAC_Convert_Ongoing  = 1U,
} en_dac_conv_sate_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup DAC_Global_Macros DAC Global Macros
 * @{
 */
#define DAC_PARAM_MAX           (4096)
#define DAC_ADPCR_CONFIG_ALL   (uint16_t)(DAC_DAADPCR_ADPSL1 | DAC_DAADPCR_ADPSL2 | DAC_DAADPCR_ADPSL3)

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
 * @addtogroup DAC_Global_Functions
 * @{
 */

/**
 * @brief  Set the specified data holding register value for DAC channel 1
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] data   Data to be loaded into data holding register of channel 1
 * @retval None
 */
__STATIC_INLINE void DAC_SetChannel1Data(M4_DAC_TypeDef* pstcDACx, uint16_t data)
{
  WRITE_REG16(pstcDACx->DADR1,data);
}

/**
 * @brief  Set the specified data holding register value for DAC channel 2
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  [in] data   Data to be loaded into data holding register of channel 2
 * @retval None
 */
__STATIC_INLINE void DAC_SetChannel2Data(M4_DAC_TypeDef* pstcDACx, uint16_t data)
{
    WRITE_REG16(pstcDACx->DADR2,data);
}

/**
 * @brief  Set the specified data holding register value for channel 1 and channel 2
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @param  data2:    Data to be loaded into data holding register of channel 2
 * @param  data1:    Data to be loaded into data holding register of channel 1
 * @retval None
 */
__STATIC_INLINE void DAC_SetChannelAllData(M4_DAC_TypeDef* pstcDACx, uint16_t data2, uint16_t data1)
{
    WRITE_REG16(pstcDACx->DADR1,data1);
    WRITE_REG16(pstcDACx->DADR2,data2);
}

/**
 * @brief  Get convert status of channel 1 in ADC priority mode
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @retval An en_dac_conv_sate_t enumeration value:
 *         - DAC_Mode_Err: Could not get convert status when adc priority is not enabled
 *         - DAC_Convert_Completed: Data convert completed
 *         - DAC_Convert_Ongoing: Data convert is ongoing
 */
__STATIC_INLINE en_dac_conv_sate_t  DAC_GetChannel1ConvState(M4_DAC_TypeDef* const pstcDACx)
{
    en_dac_conv_sate_t enStat = DAC_Mode_Err;
    if(pstcDACx->DAADPCR & DAC_DAADPCR_ADPEN)
    {
        enStat = DAC_Convert_Ongoing;
        if(((pstcDACx->DAADPCR >> DAC_DAADPCR_DA1SF_POS) & 1U) == 0U)
        {
            enStat = DAC_Convert_Completed;
        }
    }
    return enStat;
}

/**
 * @brief  Get convert status of channel 2 in ADC priority mode
 * @param  [in] pstcDACx   Pointer to the DAC peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_DAC1
 *         @arg M4_DAC2
 * @retval An en_dac_conv_sate_t enumeration value:
 *         - DAC_Mode_Err: Could not get convert status when adc priority is not enabled
 *         - DAC_Convert_Completed: Data convert completed
 *         - DAC_Convert_Ongoing: Data convert is ongoing
 */
__STATIC_INLINE en_dac_conv_sate_t DAC_GetChannel2ConvState(M4_DAC_TypeDef * const pstcDACx)
{
    en_dac_conv_sate_t enStat = DAC_Mode_Err;
    if(pstcDACx->DAADPCR & DAC_DAADPCR_ADPEN)
    {
        enStat = DAC_Convert_Ongoing;
        if(((pstcDACx->DAADPCR >> DAC_DAADPCR_DA2SF_POS) & 1U) == 0U)
        {
            enStat = DAC_Convert_Completed;
        }
    }
    return enStat;
}

__STATIC_INLINE void DAC_SetChannel1Data(M4_DAC_TypeDef* pstcDACx, uint16_t data);
__STATIC_INLINE void DAC_SetChannel2Data(M4_DAC_TypeDef* pstcDACx, uint16_t data);
__STATIC_INLINE void DAC_SetChannelAllData(M4_DAC_TypeDef* pstcDACx, uint16_t data2, uint16_t data1);
__STATIC_INLINE en_dac_conv_sate_t DAC_GetChannel1ConvState(M4_DAC_TypeDef* pstcDACx);
__STATIC_INLINE en_dac_conv_sate_t DAC_GetChannel2ConvState(M4_DAC_TypeDef* pstcDACx);
void DAC_ChannelAllCmd(M4_DAC_TypeDef* pstcDACx, en_functional_state_t enNewState);
en_result_t DAC_ChannelCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState);
void DAC_ADCPrioCmd(M4_DAC_TypeDef* pstcDACx, en_functional_state_t enNewState);
void DAC_ADCPrioConfig(M4_DAC_TypeDef* pstcDACx, uint16_t u16ADCxConfig);
void DAC_DataPatternConfig(M4_DAC_TypeDef* pstcDACx, en_dac_align_t enAlign);
void DAC_SetDataSource(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_dac_src_t src);
void DAC_OutputCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState);
en_result_t DAC_AMPCmd(M4_DAC_TypeDef* pstcDACx, en_dac_ch_t enCh, en_functional_state_t enNewState);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
