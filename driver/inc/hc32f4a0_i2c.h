/**
 *******************************************************************************
 * @file  hc32f4a0_i2c.h
 * @brief This file contains all the functions prototypes of the Inter-Integrated
 *        Circuit(I2C).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-26       Hexiao          First version
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
#ifndef __HC32F4A0_I2C_H__
#define __HC32F4A0_I2C_H__

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
 * @addtogroup DDL_I2C
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup I2C_Global_Types I2C Global Types
 * @{
 */

/**
 * @brief I2c configuration structure
 */
typedef struct
{
    uint32_t u32I2cClkDiv;   /*!< I2C clock division for hclk*/
    uint32_t u32Baudrate;    /*!< I2C baudrate config*/
    uint32_t u32SclTime;     /*!< The SCL rising and falling time, count of T(hclk)*/
}stc_i2c_init_t;

/**
 * @brief I2C address index number
 */
typedef enum
{
    I2C_ADR_0 = 0U,
    I2C_ADR_1  = 1U,
} en_i2c_adr_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup I2C_Global_Macros I2C Global Macros
 * @{
 */

/** @defgroup I2C_Clock_division I2C clock division
  * @{
  */
#define I2C_CLK_DIV1            0U
#define I2C_CLK_DIV2            1U
#define I2C_CLK_DIV4            2U
#define I2C_CLK_DIV8            3U
#define I2C_CLK_DIV16           4U
#define I2C_CLK_DIV32           5U
#define I2C_CLK_DIV64           6U
#define I2C_CLK_DIV128          7U
/**
 * @}
 */


/** @defgroup I2C_Smbus_config I2C Smbus configuration
  * @{
  */
#define I2C_SMBUS_ALRTEN        (I2C_CR1_SMBALRTEN)
#define I2C_SMBUS_DEFAULTEN     (I2C_CR1_SMBDEFAULTEN)
#define I2C_SMBUS_HOSTEN        (I2C_CR1_SMBHOSTEN)
/**
 * @}
 */

/** @defgroup I2C_Smbus_clear_mask I2C Smbus clear mask
  * @{
  */
#define I2C_SMBUS_CONFIG_CLEARMASK      (I2C_CR1_SMBALRTEN|I2C_CR1_SMBDEFAULTEN|I2C_CR1_SMBHOSTEN)
/**
 * @}
 */


/** @defgroup I2C_peripheral_Enable I2C peripheral configuration
  * @{
  */
#define I2C_PE_EN               (I2C_CR1_PE)
#define I2C_PE_DISEN            0U

/**
 * @}
 */


/** @defgroup I2C_Digital_Filter_mode I2C digital filter mode
  * @{
  */
#define I2C_DIG_FILTMODE_1CYCLE     (0UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_2CYCLE     (1UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_3CYCLE     (2UL << I2C_FLTR_DNF_POS)
#define I2C_DIG_FILTMODE_4CYCLE     (3UL << I2C_FLTR_DNF_POS)
/**
 * @}
 */

/** @defgroup I2C_Adr_Config I2C Address configuration
  * @{
  */
#define     I2C_ADR_CONFIG_DISEN    0U
#define     I2C_ADR_CONFIG_7BIT     (I2C_SLR0_SLADDR0EN)
#define     I2C_ADR_CONFIG_10BIT    (I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0EN)
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
 * @addtogroup I2C_Global_Functions
 * @{
 */

/**
 * @brief  I2C generate start condition
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
__STATIC_INLINE void I2C_GenerateStart(M4_I2C_TypeDef* pstcI2Cx)
{
    SET_REG32_BIT(pstcI2Cx->CR1, I2C_CR1_START);
}

/**
 * @brief  I2C generate restart condition
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
__STATIC_INLINE void I2C_GenerateReStart(M4_I2C_TypeDef* pstcI2Cx)
{
    SET_REG32_BIT(pstcI2Cx->CR1, I2C_CR1_RESTART);
}

/**
 * @brief  I2C generate stop condition
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval None
 */
__STATIC_INLINE void I2C_GenerateStop(M4_I2C_TypeDef* pstcI2Cx)
{
    SET_REG32_BIT(pstcI2Cx->CR1, I2C_CR1_STOP);
}

/* Initialization and Configuration **********************************/
void I2C_DeInit(M4_I2C_TypeDef* pstcI2Cx);
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2C_InitStruct);
en_result_t I2C_Init(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2C_InitStruct, float32_t *pf32Err);
en_result_t I2C_BaudrateConfig(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2C_InitStruct, float32_t *pf32Err);
void I2C_Cmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_SmbusConfig(M4_I2C_TypeDef* pstcI2Cx, uint32_t SmbusConfig);
void I2C_SmBusCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_SoftwareResetCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* pstcI2Cx, uint32_t DigFilterMode);
void I2C_DigitalFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_AnalogFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_GeneralCallCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);
void I2C_IntCmd(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32IntEn, en_functional_state_t enNewState);
void I2C_SlaveAdrConfig(M4_I2C_TypeDef* pstcI2Cx, en_i2c_adr_t enAdrNum, uint32_t u32AdrConfig, uint32_t u32Adr);
void I2C_NackConfig(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState);

/* Status management **************************************************/ 
en_flag_status_t I2C_GetStatus(M4_I2C_TypeDef* const pstcI2Cx, uint32_t u32StatusBit);
void I2C_WriteStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit, en_flag_status_t enStatus);
void I2C_ClearStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit);

/* Data transfers ************************************  ***************/ 
void I2C_WriteDataReg(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Data);
uint8_t I2C_ReadDataReg(M4_I2C_TypeDef* const pstcI2Cx);

/* High level functions for reference *********************************/
en_result_t I2C_Start(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32TimeOut);
en_result_t I2C_Restart(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32TimeOut);
en_result_t I2C_SendAddr(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Adr, uint32_t u32TimeOut);
en_result_t I2C_SendData(M4_I2C_TypeDef* pstcI2Cx, uint8_t const pTxData[], uint32_t u32Size, uint32_t u32TimeOut);
en_result_t I2C_RcvData(M4_I2C_TypeDef* pstcI2Cx, uint8_t pRxData[], uint32_t u32Size, uint32_t u32TimeOut);
en_result_t I2C_Stop(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32TimeOut);

/**
 * @}
 */

#endif /* DDL_I2C_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
