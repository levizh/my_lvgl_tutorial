/**
 *******************************************************************************
 * @file  hc32f4a0_i2c.c
 * @brief This file provides firmware functions to manage the Inter-Integrated
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_i2c.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_I2C I2C
 * @brief I2C Driver Library
 * @{
 */

#if (DDL_I2C_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2C_Local_Macros I2C Local Macros
 * @{
 */

#define I2C_BAUDRATE_MAX                400000UL

#define I2C_CLR_MASK                   ((uint32_t)0x00F052DF)

/**
 * @defgroup I2C_Check_Parameters_Validity I2C Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_I2C1)                               ||                          \
    ((x) == M4_I2C2)                               ||                          \
    ((x) == M4_I2C3)                               ||                          \
    ((x) == M4_I2C4)                               ||                          \
    ((x) == M4_I2C5)                               ||                          \
    ((x) == M4_I2C6))

#define IS_VALID_CLEARBIT(x)            (0U == ((x) & (~I2C_CLR_MASK)))

#define IS_VALID_SPEED(speed)           ((speed) <= (I2C_BAUDRATE_MAX))

#define IS_VALID_DIGITAL_FILTER(x)             ((x) <= I2C_DIG_FILTMODE_4CYCLE)

#define IS_VALID_RD_STATUS_BIT(x)                                              \
(   ((x) == I2C_SR_STARTF)                         ||                          \
    ((x) == I2C_SR_SLADDR0F)                       ||                          \
    ((x) == I2C_SR_SLADDR1F)                       ||                          \
    ((x) == I2C_SR_TENDF)                          ||                          \
    ((x) == I2C_SR_STOPF)                          ||                          \
    ((x) == I2C_SR_RFULLF)                         ||                          \
    ((x) == I2C_SR_TEMPTYF)                        ||                          \
    ((x) == I2C_SR_ARLOF)                          ||                          \
    ((x) == I2C_SR_ACKRF)                          ||                          \
    ((x) == I2C_SR_NACKF)                          ||                          \
    ((x) == I2C_SR_TMOUTF)                         ||                         \
    ((x) == I2C_SR_MSL)                            ||                          \
    ((x) == I2C_SR_BUSY)                           ||                          \
    ((x) == I2C_SR_TRA)                            ||                          \
    ((x) == I2C_SR_GENCALLF)                       ||                          \
    ((x) == I2C_SR_SMBDEFAULTF)                    ||                          \
    ((x) == I2C_SR_SMBHOSTF)                       ||                          \
    ((x) == I2C_SR_SMBALRTF))

#define IS_VALID_WR_STATUS_BIT(x)                                              \
(   ((x) == I2C_SR_MSL)                            ||                          \
    ((x) == I2C_SR_TRA))

#define IS_VALID_SMBUS_CONFIG(x)     ( 0U == ((x) & (~(uint32_t)I2C_SMBUS_CONFIG_CLEARMASK)))

#define IS_VALID_ADRCONFIG(x)                                                  \
    (0U == ((x) & ~(uint32_t)(I2C_SLR0_ADDRMOD0 | I2C_SLR0_SLADDR0EN)))

#define IS_VALID_7BIT_ADR(x)            ((x) <= 0x7FU)
#define IS_VALIDE_10BIT_ADR(x)          ((x) <= 0x3FFU)

#define IS_VALID_ADR_NUM(x)                                                    \
(   ((x) == I2C_ADR_0)                             ||                          \
    ((x) == I2C_ADR_1))

#define IS_VALID_CLK_DIV(x)                                                    \
(   ((x) == I2C_CLK_DIV1)                          ||                          \
    ((x) == I2C_CLK_DIV2)                          ||                          \
    ((x) == I2C_CLK_DIV4)                          ||                          \
    ((x) == I2C_CLK_DIV8)                          ||                          \
    ((x) == I2C_CLK_DIV16)                         ||                          \
    ((x) == I2C_CLK_DIV32)                         ||                          \
    ((x) == I2C_CLK_DIV64)                         ||                          \
    ((x) == I2C_CLK_DIV128))

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
 * @defgroup I2C_Global_Functions I2C Global Functions
 * @{
 */

/**
 * @brief  Set the baudrate for I2C peripheral.
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] pstcI2C_InitStruct   Pointer to I2C configuration structure
 *                                   @ref stc_i2c_init_t
 *         @arg pstcI2C_InitStruct->u32I2cClkDiv: Division of Hclk, reference as:
 *              step1: calculate div = (Hclk/Baudrate/(68+2*dnfsum+SclTime)
 *                     Hclk -- system clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                according to i2c bus hardware parameter.
 *                     dnfsum -- 0 if digital filter off;
 *                               Filter capacity if digital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_division.
 *         @arg pstcI2C_InitStruct->u32Baudrate : Baudrate configuration
 *         @arg pstcI2C_InitStruct->u32SclTime : Indicate SCL pin rising and
 *              falling time, should be number of T(i2c clock period time)
 * @param  [in] pf32Err               Baudrate error
 * @retval en_result_t
 */
en_result_t I2C_BaudrateConfig(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2C_InitStruct, float32_t *pf32Err)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    en_result_t enRet = Ok;
    uint32_t Hclk, I2cDivClk, SclCnt, Baudrate;
    uint32_t dnfsum = 0UL, divsum = 0UL;
    float32_t WidthTotal, SumTotal;
    float32_t WidthHL;
    float32_t fErr = 0.0f;

    if ((NULL == pstcI2C_InitStruct)||(NULL == pf32Err))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_SPEED(pstcI2C_InitStruct->u32Baudrate));
        DDL_ASSERT(IS_VALID_CLK_DIV(pstcI2C_InitStruct->u32I2cClkDiv));

        /* Get configuration for i2c */
        Hclk = SystemCoreClock/(1UL<<((M4_CMU->SCFGR & CMU_SCFGR_PCLK3S)>>CMU_SCFGR_PCLK3S_POS));
        I2cDivClk = 1UL << pstcI2C_InitStruct->u32I2cClkDiv;
        SclCnt = pstcI2C_InitStruct->u32SclTime;
        Baudrate = pstcI2C_InitStruct->u32Baudrate;

        /* Judge digital filter status*/
        if(0U != READ_REG32_BIT(pstcI2Cx->FLTR, I2C_FLTR_DNFEN))
        {
            dnfsum = ((pstcI2Cx->FLTR & I2C_FLTR_DNF) >> I2C_FLTR_DNF_POS) + 1U;
        }
        else
        {
            dnfsum = 0UL;
        }

        /* Judge if clock divider on*/
        if(I2C_CLK_DIV1 == I2cDivClk)
        {
            divsum = 3UL;
        }
        else
        {
            divsum = 2UL;
        }

        WidthTotal = (float32_t)Hclk/(float32_t)Baudrate/(float32_t)I2cDivClk;
        SumTotal = 2.0f*(float32_t)divsum + 2.0f*(float32_t)dnfsum + (float32_t)SclCnt;
        WidthHL = WidthTotal - SumTotal;

        if(WidthTotal <= SumTotal)
        {
            /* Err, Should set a smaller division value for pstcI2C_InitStruct->u32I2cClkDiv */
            //DDL_ASSERT(NULL);
            enRet = ErrorInvalidParameter;
        }
        else if(WidthHL > ((float32_t)0x1F*(float32_t)2))
        {
            /* Err, Should set a bigger division value for pstcI2C_InitStruct->u32I2cClkDiv */
            //DDL_ASSERT(NULL);
            enRet = ErrorInvalidParameter;
        }
        else
        {
            fErr =(WidthHL - (float32_t)((uint32_t)WidthHL)) / WidthHL;

            pstcI2Cx->CCR = (pstcI2C_InitStruct->u32I2cClkDiv << I2C_CCR_FREQ_POS)     \
                           | (((uint32_t)WidthHL/2U) << I2C_CCR_SLOWW_POS)              \
                           | (((uint32_t)WidthHL - (uint32_t)WidthHL/2U) << I2C_CCR_SHIGHW_POS);
        }
    }
    if((NULL != pf32Err)&&(Ok == enRet))
    {
        *pf32Err = fErr;
    }
    return enRet;
}

/**
 * @brief  De-initialize I2C unit
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
void I2C_DeInit(M4_I2C_TypeDef* pstcI2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    /* Reset peripheral register and internal status*/
    CLEAR_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_PE);
    SET_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_SWRST);
}

/**
 * @brief  Initialize I2C peripheral according to the structure
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] pstcI2C_InitStruct   Pointer to I2C configuration structure
 *                                   @ref stc_i2c_init_t
 *         @arg pstcI2C_InitStruct->u32I2cClkDiv: Division of Hclk, reference as:
 *              step1: calculate div = (Hclk/Baudrate/(68+2*dnfsum+SclTime)
 *                     Hclk -- system clock
 *                     Baudrate -- baudrate of i2c
 *                     SclTime -- =(SCL rising time + SCL falling time)/period of i2c clock
 *                                according to i2c bus hardware parameter.
 *                     dnfsum -- 0 if ditital filter off;
 *                               Filter capacity if ditital filter on(1 ~ 4)
 *              step2: chose a division item which is similar and bigger than div
 *                     from @ref I2C_Clock_division.
 *         @arg pstcI2C_InitStruct->u32Baudrate : Baudrate configuration
 *         @arg pstcI2C_InitStruct->u32SclTime : Indicate SCL pin rising and
 *              falling time, should be number of T(i2c clock period time)
 * @param  [in] pf32Err               Baudrate error
 * @retval en_result_t
 */
en_result_t I2C_Init(M4_I2C_TypeDef* pstcI2Cx, const stc_i2c_init_t* pstcI2C_InitStruct, float32_t *pf32Err)
{
    en_result_t enRet = Ok;
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    if (NULL == pstcI2C_InitStruct )
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_VALID_SPEED(pstcI2C_InitStruct->u32Baudrate));
        DDL_ASSERT(IS_VALID_CLK_DIV(pstcI2C_InitStruct->u32I2cClkDiv));

        /* Register and internal status reset */
        CLEAR_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_PE);
        SET_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_SWRST);
        SET_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_PE);

        /* I2C baudrate config */
        I2C_BaudrateConfig(pstcI2Cx, pstcI2C_InitStruct, pf32Err);

        /* Disable global broadcast address function */
        CLEAR_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_ENGC);

        /* Release software reset */
        CLEAR_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_SWRST);
        /* Disable I2C peripheral */
        CLEAR_REG32_BIT(pstcI2Cx->CR1,I2C_CR1_PE);
    }
    return enRet;
}

/**
 * @brief  I2C function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_Cmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_CR1_PE, (uint32_t)enNewState << I2C_CR1_PE_POS);
}

/**
 * @brief  I2C SMBUS function configuration
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] SmbusConfig       Indicate the SMBUS function configuration
 *         This parameter can be one or any combination of the following values:
 *         @ref  I2C_Smbus_config
 *         @arg  I2C_SMBUS_ALRTEN    : Smbus alarm address enable
 *         @arg  I2C_SMBUS_DEFAULTEN : Smbus default address enable
 *         @arg  I2C_SMBUS_HOSTEN    : Smbus host address address enable
 * @retval None
 */
void I2C_SmbusConfig(M4_I2C_TypeDef* pstcI2Cx, uint32_t SmbusConfig)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_SMBUS_CONFIG(SmbusConfig));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_SMBUS_CONFIG_CLEARMASK, SmbusConfig);
}

/**
 * @brief  I2C SMBUS function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx SMBUS function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_SmBusCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_CR1_SMBUS, (uint32_t)enNewState << I2C_CR1_SMBUS_POS);
}

/**
 * @brief  I2C software reset function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_SoftwareResetCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_CR1_SWRST, (uint32_t)enNewState << I2C_CR1_SWRST_POS);
}

/**
 * @brief  I2C digital filter function configuration
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] DigFilterMode        Chose the digital filter mode,
 *                                   @ref I2C_Digital_Filter_mode
 * @retval None
 */
void I2C_DigitalFilterConfig(M4_I2C_TypeDef* pstcI2Cx, uint32_t DigFilterMode)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_DIGITAL_FILTER(DigFilterMode));

    MODIFY_REG32(pstcI2Cx->FLTR, I2C_FLTR_DNF, DigFilterMode);
}

/**
 * @brief  I2C digital filter function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_DigitalFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->FLTR, I2C_FLTR_DNFEN, (uint32_t)enNewState << I2C_FLTR_DNFEN_POS);
}

/**
 * @brief  I2C analog filter function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_AnalogFilterCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->FLTR, I2C_FLTR_ANFEN, (uint32_t)enNewState << I2C_FLTR_ANFEN_POS);
}

/**
 * @brief  I2C general call function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_GeneralCallCmd(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_CR1_ENGC, (uint32_t)enNewState << I2C_CR1_ENGC_POS);
}

/**
 * @brief  I2C slave address config
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enAdrNum            I2C_ADR_0 or I2C_ADR_1 @ref en_i2c_adr_t
 * @param  [in] u32AdrConfig         Address mode configuration,
 *                                   @ref I2C_Adr_Config
 * @param  [in] u32Adr               The slave address
 * @retval None
 */
void I2C_SlaveAdrConfig(M4_I2C_TypeDef* pstcI2Cx, en_i2c_adr_t enAdrNum, uint32_t u32AdrConfig, uint32_t u32Adr)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_ADRCONFIG(u32AdrConfig));

    uint32_t u32AdrReg = (uint32_t)&pstcI2Cx->SLR0 + enAdrNum * 4;
    if(I2C_ADR_CONFIG_10BIT == u32AdrConfig)
    {
        /* if 10 bit address mode */
        DDL_ASSERT(IS_VALIDE_10BIT_ADR(u32Adr));
        WRITE_REG16(*(__IO uint32_t*)(u32AdrReg), u32AdrConfig + u32Adr);
    }
    //else if(I2C_ADR_CONFIG_7BIT == u32AdrConfig)
    else
    {
        /* if 7 bit address mode */
        DDL_ASSERT(IS_VALID_7BIT_ADR(u32Adr));
        WRITE_REG16(*(__IO uint32_t*)(u32AdrReg), u32AdrConfig + (u32Adr << 1));
    }
}

/**
 * @brief  I2C interrupt function command
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32IntEn   Specifies the I2C interrupts sources to be configuration
 *         This parameter can be any combination of the following values:
 *         @arg    I2C_CR2_STARTIE      : Start flag interrupt
 *         @arg    I2C_CR2_SLADDR0IE    : Address 0 detected interrupt
 *         @arg    I2C_CR2_SLADDR1IE    : Address 1 detected interrupt
 *         @arg    I2C_CR2_TENDIE       : Transfer end interrupt
 *         @arg    I2C_CR2_STOPIE       : Stop flag interrupt
 *         @arg    I2C_CR2_RFULLIE      : Receive buffer full interrupt
 *         @arg    I2C_CR2_TEMPTYIE     : Transfer buffer empty interrupt
 *         @arg    I2C_CR2_ARLOIE       : Arbitration fails interrupt
 *         @arg    I2C_CR2_NACKIE       : NACK flag detected interrupt
 *         @arg    I2C_CR2_TMOUTIE      : Time out detected interrupt
 *         @arg    I2C_CR2_GENCALLIE    : General call address detected interrupt
 *         @arg    I2C_CR2_SMBDEFAULTIE : Smbus default address detected interrupt
 *         @arg    I2C_CR2_SMBHOSTIE    : Smbus host address detected interrupt
 *         @arg    I2C_CR2_SMBALRTIE    : Smbus alarm address detected interrupt
 * @param  [in] enNewState           New state of the I2Cx function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void I2C_IntCmd(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32IntEn, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        pstcI2Cx->CR2 |= u32IntEn;
    }
    else
    {
        pstcI2Cx->CR2 &= (uint32_t)~u32IntEn;
    }
}

/**
 * @brief  I2C send data or address
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u8Data               The data to be send
 * @retval None
 */
void I2C_SendData(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Data)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    pstcI2Cx->DTR = u8Data;
}

/**
 * @brief  I2C read data from register
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @retval The value of the received data
 */
uint8_t I2C_ReadData(M4_I2C_TypeDef* const pstcI2Cx)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    return (uint8_t)pstcI2Cx->DRR;
}

/**
 * @brief  I2C ACK status configuration
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] enNewState           New state of the I2Cx function, can be
 *                                   Disable or Enable the function
 * @retval None
 */
void I2C_NackConfig(M4_I2C_TypeDef* pstcI2Cx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(pstcI2Cx->CR1, I2C_CR1_ACK, (uint32_t)enNewState << I2C_CR1_ACK_POS);
}

/**
 * @brief  I2C status bit get
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32StatusBit         specifies the flag to check,
 *         This parameter can be one of the following values:
 *         @arg   I2C_SR_STARTF     : Start condition detected flag
 *         @arg   I2C_SR_SLADDR0F   : Address 0 detected flag
 *         @arg   I2C_SR_SLADDR1F   : Address 1 detected flag
 *         @arg   I2C_SR_TENDF      : Transfer end flag
 *         @arg   I2C_SR_STOPF      : Stop condition detected flag
 *         @arg   I2C_SR_RFULLF     : Receive buffer full flag
 *         @arg   I2C_SR_TEMPTYF    : Transfer buffer empty flag
 *         @arg   I2C_SR_ARLOF      : Arbitration fails flag
 *         @arg   I2C_SR_ACKRF      : ACK detected flag
 *         @arg   I2C_SR_NACKF      : NACK detected flag
 *         @arg   I2C_SR_TMOUTF     : Time out detected flag
 *         @arg   I2C_SR_MSL        : Master mode flag
 *         @arg   I2C_SR_BUSY       : Bus busy status flag
 *         @arg   I2C_SR_TRA        : Transfer mode flag
 *         @arg   I2C_SR_GENCALLF   : General call detected flag
 *         @arg   I2C_SR_SMBDEFAULTF: Smbus default address detected flag
 *         @arg   I2C_SR_SMBHOSTF   : Smbus host address detected flag
 *         @arg   I2C_SR_SMBALRTF   : Smbus alarm address detected flag
 * @retval The status of the I2C status flag, may be Set or Reset.
 */
en_flag_status_t I2C_GetStatus(M4_I2C_TypeDef * const pstcI2Cx, uint32_t u32StatusBit)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_RD_STATUS_BIT(u32StatusBit));

    return ((pstcI2Cx->SR & u32StatusBit) ? Set : Reset);
}

/**
 * @brief  I2C status bit get
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32StatusBit         Specifies the flag to be write,
 *         This parameter can be one of the following values:
 *         @arg  I2C_SR_MSL
 *         @arg  I2C_SR_TRA
 * @param  [in] enStatus             New state of the I2Cx function, can be
 *                                   Disable or Enable the function
 * @retval None
 */
void  I2C_WriteStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit, en_flag_status_t enStatus)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_WR_STATUS_BIT(u32StatusBit));

    if(Set == enStatus)
    {
        pstcI2Cx->SR |= u32StatusBit;
    }
    else
    {
        pstcI2Cx->SR &= (~u32StatusBit);
    }
}

/**
 * @brief  Clear I2C status flag
 * @param  [in] pstcI2Cx   Pointer to the I2C peripheral register
 *         This parameter can be one of the following values:
 *         @arg M4_I2C1
 *         @arg M4_I2C2
 *         @arg M4_I2C3
 *         @arg M4_I2C4
 *         @arg M4_I2C5
 *         @arg M4_I2C6
 * @param  [in] u32StatusBit         Specifies the flag to clear,
 *         This parameter can be any combination of the following values:
 *         @arg  I2C_CLR_STARTFCLR     : Start flag clear
 *         @arg  I2C_CLR_SLADDR0FCLR   : Address 0 detected flag clear
 *         @arg  I2C_CLR_SLADDR1FCLR   : Address 1 detected flag clear
 *         @arg  I2C_CLR_TENDFCLR      : Transfer end flag clear
 *         @arg  I2C_CLR_STOPFCLR      : Stop flag clear
 *         @arg  I2C_CLR_RFULLFCLR     : Receive buffer full flag clear
 *         @arg  I2C_CLR_TEMPTYFCLR    : Transfer buffer empty flag clear
 *         @arg  I2C_CLR_ARLOFCLR      : Arbitration fails flag clear
 *         @arg  I2C_CLR_NACKFCLR      : Nack detected flag clear
 *         @arg  I2C_CLR_TMOUTFCLR     : Time out detected flag clear
 *         @arg  I2C_CLR_GENCALLFCLR   : General call address detected flag clear
 *         @arg  I2C_CLR_SMBDEFAULTFCLR: Smbus default address detected flag clear
 *         @arg  I2C_CLR_SMBHOSTFCLR   : Smbus host address detected flag clear
 *         @arg  I2C_CLR_SMBALRTFCLR   : Smbus alarm address detected flag clear
 * @retval None
 */
void I2C_ClearStatus(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32StatusBit)
{
    DDL_ASSERT(IS_VALID_UNIT(pstcI2Cx));
    DDL_ASSERT(IS_VALID_CLEARBIT(u32StatusBit));

    pstcI2Cx->CLR |= u32StatusBit;
}

/**
 * @brief  Initialize structure stc_i2c_init_t variable with default value.
 * @param  [out] pstcI2C_InitStruct     Pointer to a stc_i2c_init_t structure variable
 *                                      which will be initialized.
 *   @arg  See the struct @ref stc_i2c_init_t.
 * @retval en_result_t
 */
en_result_t I2C_StructInit(stc_i2c_init_t* pstcI2C_InitStruct)
{
    en_result_t enRet = Ok;
    if (pstcI2C_InitStruct == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcI2C_InitStruct->u32Baudrate = 50000UL;
        pstcI2C_InitStruct->u32SclTime = 0UL;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
