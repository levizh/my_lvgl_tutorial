/**
 *******************************************************************************
 * @file  hc32f4a0_i2s.c
 * @brief This file provides firmware functions to manage the Inter IC Sound Bus
 *        (I2S).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#include "hc32f4a0_i2s.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_I2S I2S
 * @brief Inter IC Sound Bus Driver Library
 * @{
 */

#if (DDL_I2S_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2S_Local_Macros I2S Local Macros
 * @{
 */

/* I2S CTRL register Mask */
#define I2S_CTRL_CLEAR_MASK             (I2S_CTRL_WMS      | I2S_CTRL_ODD      | I2S_CTRL_MCKOE     | \
                                         I2S_CTRL_TXBIRQWL | I2S_CTRL_RXBIRQWL | I2S_CTRL_I2SPLLSEL | \
                                         I2S_CTRL_SDOE     | I2S_CTRL_LRCKOE   | I2S_CTRL_CKOE      | \
                                         I2S_CTRL_DUPLEX   | I2S_CTRL_CLKSEL)

/**
 * @defgroup I2S_Check_Parameters_Validity I2S Check Parameters Validity
 * @{
 */
#define IS_I2S_UNIT(x)                          ||                             \
(   ((x) == M4_I2S1)                            ||                             \
    ((x) == M4_I2S2)                            ||                             \
    ((x) == M4_I2S3)                            ||                             \
    ((x) == M4_I2S4))

#define IS_I2S_CLK_SRC(x)                                                      \
(   ((x) == I2S_CLK_SRC_PLL)                    ||                             \
    ((x) == I2S_CLK_SRC_EXT))

#define IS_I2S_MD(x)                                                           \
(   ((x) == I2S_MD_MASTER)                      ||                             \
    ((x) == I2S_MD_SLAVE))

#define IS_I2S_COM_PROTOCOL(x)                                                 \
(   ((x) == I2S_COM_PROTOCOL_PHILLIPS)          ||                             \
    ((x) == I2S_COM_PROTOCOL_MSB)               ||                             \
    ((x) == I2S_COM_PROTOCOL_LSB)               ||                             \
    ((x) == I2S_COM_PROTOCOL_PCM_SHORT)         ||                             \
    ((x) == I2S_COM_PROTOCOL_PCM_LONG))

#define IS_I2S_TRANS_MD(x)                                                     \
(   ((x) == I2S_TRANS_MD_HALF_DUPLEX_RX)        ||                             \
    ((x) == I2S_TRANS_MD_HALF_DUPLEX_TX)        ||                             \
    ((x) == I2S_TRANS_MD_FULL_DUPLEX))

#define IS_I2S_AUDIO_FREQ(x)                                                   \
(   ((x) == I2S_AUDIO_FREQ_DEFAULT)             ||                             \
    (((x) >= I2S_AUDIO_FREQ_8K) && ((x) <= I2S_AUDIO_FREQ_192K)))

#define IS_I2S_CH_LEN(x)                                                       \
(   ((x) == I2S_CH_LEN_16BIT)                   ||                             \
    ((x) == I2S_CH_LEN_32BIT))

#define IS_I2S_DATA_LEN(x)                                                     \
(   ((x) == I2S_DATA_LEN_16BIT)                 ||                             \
    ((x) == I2S_DATA_LEN_24BIT)                 ||                             \
    ((x) == I2S_DATA_LEN_32BIT))

#define IS_I2S_MCK_OUTPUT(x)                                                   \
(   ((x) == I2S_MCK_OUTPUT_DISABLE)             ||                             \
    ((x) == I2S_MCK_OUTPUT_ENABLE))

#define IS_I2S_TRANS_LVL(x)                                                    \
(   ((x) == I2S_TRANS_LVL0)                     ||                             \
    ((x) == I2S_TRANS_LVL1)                     ||                             \
    ((x) == I2S_TRANS_LVL2)                     ||                             \
    ((x) == I2S_TRANS_LVL3)                     ||                             \
    ((x) == I2S_TRANS_LVL4))

#define IS_I2S_RECEIVE_LVL(x)                                                  \
(   ((x) == I2S_RECEIVE_LVL0)                   ||                             \
    ((x) == I2S_RECEIVE_LVL1)                   ||                             \
    ((x) == I2S_RECEIVE_LVL2)                   ||                             \
    ((x) == I2S_RECEIVE_LVL3)                   ||                             \
    ((x) == I2S_RECEIVE_LVL4))

#define IS_I2S_FUNC(x)                                                         \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_FUNC_ALL) == I2S_FUNC_ALL))

#define IS_I2S_RST_TYPE(x)                                                     \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_RST_TYPE_ALL) == I2S_RST_TYPE_ALL))

#define IS_I2S_INT(x)                                                          \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_INT_ALL) == I2S_INT_ALL))

#define IS_I2S_FLAG(x)                                                         \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_FLAG_ALL) == I2S_FLAG_ALL))

#define IS_I2S_CLR_FLAG(x)                                                     \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_CLR_FLAG_ALL) == I2S_CLR_FLAG_ALL))

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
 * @defgroup I2S_Global_Functions I2S Global Functions
 * @{
 */

/**
 * @brief  De-Initialize I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @retval None
 */
void I2S_DeInit(M4_I2S_TypeDef *I2Sx)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));

    /* Reset all registers of I2S */
    SET_REG32_BIT(I2Sx->CTRL, I2S_RST_TYPE_ALL);
    CLEAR_REG32_BIT(I2Sx->CTRL, I2S_RST_TYPE_ALL);
}

/**
 * @brief  Initialize I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] pstcI2sInit             Pointer to a @ref stc_i2s_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t I2S_Init(M4_I2S_TypeDef *I2Sx, const stc_i2s_init_t *pstcI2sInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcI2sInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2S_UNIT(I2Sx));
        DDL_ASSERT(IS_I2S_CLK_SRC(pstcI2sInit->u32ClockSrc));
        DDL_ASSERT(IS_I2S_MD(pstcI2sInit->u32Mode));
        DDL_ASSERT(IS_I2S_COM_PROTOCOL(pstcI2sInit->u32ComProtocol));
        DDL_ASSERT(IS_I2S_TRANS_MD(pstcI2sInit->u32TransMode));
        DDL_ASSERT(IS_I2S_AUDIO_FREQ(pstcI2sInit->u32AudioFreq));
        DDL_ASSERT(IS_I2S_CH_LEN(pstcI2sInit->u32ChLen));
        DDL_ASSERT(IS_I2S_DATA_LEN(pstcI2sInit->u32DataLen));
        DDL_ASSERT(IS_I2S_MCK_OUTPUT(pstcI2sInit->u32MCKOutput));
        DDL_ASSERT(IS_I2S_TRANS_LVL(pstcI2sInit->u32TransFIFOLevel));
        DDL_ASSERT(IS_I2S_RECEIVE_LVL(pstcI2sInit->u32ReceiveFIFOLevel));

        uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
        uint32_t tmp = 0, i2sclk = 0;
        #ifndef I2S_EXTERNAL_CLOCK_VAL
        uint32_t pllm = 0, plln = 0, pllr = 0;
        #endif /* I2S_EXTERNAL_CLOCK_VAL */
        
        /* Check the I2S parameters */
        assert_param(IS_SPI_23_PERIPH(SPIx));
        assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
        assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
        assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
        assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
        assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
        assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

        /*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
        /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
        SPIx->I2SCFGR &= I2SCFGR_CLEAR_MASK; 
        SPIx->I2SPR = 0x0002;
        
        /* Get the I2SCFGR register value */
        tmpreg = SPIx->I2SCFGR;
        
        /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
        if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
        {
            i2sodd = (uint16_t)0;
            i2sdiv = (uint16_t)2;   
        }
        /* If the requested audio frequency is not the default, compute the prescaler */
        else
        {
            /* Check the frame length (For the Prescaler computing) *******************/
            if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
            {
            /* Packet length is 16 bits */
            packetlength = 1;
            }
            else
            {
            /* Packet length is 32 bits */
            packetlength = 2;
            }

            /* Get I2S source Clock frequency  ****************************************/
            
            /* If an external I2S clock has to be used, this define should be set  
            in the project configuration or in the stm32f4xx_conf.h file */
        #ifdef I2S_EXTERNAL_CLOCK_VAL     
            /* Set external clock as I2S clock source */
            if ((RCC->CFGR & RCC_CFGR_I2SSRC) == 0)
            {
            RCC->CFGR |= (uint32_t)RCC_CFGR_I2SSRC;
            }
            
            /* Set the I2S clock to the external clock  value */
            i2sclk = I2S_EXTERNAL_CLOCK_VAL;

        #else /* There is no define for External I2S clock source */
            /* Set PLLI2S as I2S clock source */
            if ((RCC->CFGR & RCC_CFGR_I2SSRC) != 0)
            {
            RCC->CFGR &= ~(uint32_t)RCC_CFGR_I2SSRC;
            }    
            
            /* Get the PLLI2SN value */
            plln = (uint32_t)(((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6) & \
                            (RCC_PLLI2SCFGR_PLLI2SN >> 6));
            
            /* Get the PLLI2SR value */
            pllr = (uint32_t)(((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28) & \
                            (RCC_PLLI2SCFGR_PLLI2SR >> 28));
            
            /* Get the PLLM value */
            pllm = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM);

            if((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE)
            {
            /* Get the I2S source clock value */
            i2sclk = (uint32_t)(((HSE_VALUE / pllm) * plln) / pllr);
            }
            else
            { /* Get the I2S source clock value */
            i2sclk = (uint32_t)(((HSI_VALUE / pllm) * plln) / pllr);
            }
        #endif /* I2S_EXTERNAL_CLOCK_VAL */
            
            /* Compute the Real divider depending on the MCLK output state, with a floating point */
            if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
            {
            /* MCLK output is enabled */
            tmp = (uint16_t)(((((i2sclk / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
            }
            else
            {
            /* MCLK output is disabled */
            tmp = (uint16_t)(((((i2sclk / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
            }
            
            /* Remove the flatting point */
            tmp = tmp / 10;  
            
            /* Check the parity of the divider */
            i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);
        
            /* Compute the i2sdiv prescaler */
            i2sdiv = (uint16_t)((tmp - i2sodd) / 2);
        
            /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
            i2sodd = (uint16_t) (i2sodd << 8);
        }

        /* Test if the divider is 1 or 0 or greater than 0xFF */
        if ((i2sdiv < 2) || (i2sdiv > 0xFF))
        {
            /* Set the default values */
            i2sdiv = 2;
            i2sodd = 0;
        }

        /* Write to SPIx I2SPR register the computed value */
        SPIx->I2SPR = (uint16_t)((uint16_t)i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));
        
        /* Configure the I2S with the SPI_InitStruct values */
        tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                        (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                        (uint16_t)I2S_InitStruct->I2S_CPOL))));
        
        #if defined(SPI_I2SCFGR_ASTRTEN)
        if((I2S_InitStruct->I2S_Standard  == I2S_Standard_PCMShort) || (I2S_InitStruct->I2S_Standard  == I2S_Standard_PCMLong))
        {
            /* Write to SPIx I2SCFGR */  
            SPIx->I2SCFGR = tmpreg | SPI_I2SCFGR_ASTRTEN;
        }
        #else
        /* Write to SPIx I2SCFGR */  
        SPIx->I2SCFGR = tmpreg ;
        #endif 






        uint32_t tmpreg = 0U, i2sdiv = 2U, i2sodd = 0U, packetlength = 16U;
        uint32_t tmp = 0U, i2sclk = 0U;

        /* Check the I2S handle allocation */
        if(hi2s == NULL)
        {
            return HAL_ERROR;
        }

        /* Check the I2S parameters */
        assert_param(IS_I2S_ALL_INSTANCE(hi2s->Instance));
        assert_param(IS_I2S_MODE(hi2s->Init.Mode));
        assert_param(IS_I2S_STANDARD(hi2s->Init.Standard));
        assert_param(IS_I2S_DATA_FORMAT(hi2s->Init.DataFormat));
        assert_param(IS_I2S_MCLK_OUTPUT(hi2s->Init.MCLKOutput));
        assert_param(IS_I2S_AUDIO_FREQ(hi2s->Init.AudioFreq));
        assert_param(IS_I2S_CPOL(hi2s->Init.CPOL));
        assert_param(IS_I2S_CLOCKSOURCE(hi2s->Init.ClockSource));

        hi2s->State = HAL_I2S_STATE_BUSY;

        /* Initialize Default I2S IrqHandler ISR */
        hi2s->IrqHandlerISR = I2S_IRQHandler;

        /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
        HAL_I2S_MspInit(hi2s);

        /*----------------------- SPIx I2SCFGR & I2SPR Configuration ---------------*/
        /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
        CLEAR_BIT(hi2s->Instance->I2SCFGR,(SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CKPOL | \
                                            SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
                                            SPI_I2SCFGR_I2SE | SPI_I2SCFGR_I2SMOD));
        hi2s->Instance->I2SPR = 0x0002U;

        /* Get the I2SCFGR register value */
        tmpreg = hi2s->Instance->I2SCFGR;

        /* If the default frequency value has to be written, reinitialize i2sdiv and i2sodd */
        /* If the requested audio frequency is not the default, compute the prescaler */
        if(hi2s->Init.AudioFreq != I2S_AUDIOFREQ_DEFAULT)
        {
            /* Check the frame length (For the Prescaler computing) *******************/
            /* Set I2S Packet Length value*/
            if(hi2s->Init.DataFormat != I2S_DATAFORMAT_16B)
            {
            /* Packet length is 32 bits */
            packetlength = 32U;
            }
            else
            {
            /* Packet length is 16 bits */
            packetlength = 16U;
            }

            /* I2S standard */
            if(hi2s->Init.Standard <= I2S_STANDARD_LSB)
            {
            /* In I2S standard packet lenght is multiplied by 2 */
            packetlength = packetlength * 2U;
            }

            /* Get I2S source Clock frequency from RCC ********************************/
        #if defined(I2S_APB1_APB2_FEATURE)
            if(IS_I2S_APB1_INSTANCE(hi2s->Instance))
            {
            i2sclk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2S_APB1);
            }
            else
            {
            i2sclk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2S_APB2);
            }
        #else
            i2sclk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I2S);
        #endif

            /* Compute the Real divider depending on the MCLK output state, with a floating point */
            if(hi2s->Init.MCLKOutput == I2S_MCLKOUTPUT_ENABLE)
            {
            /* MCLK output is enabled */
            if (hi2s->Init.DataFormat != I2S_DATAFORMAT_16B)
            {
                tmp = (uint32_t)(((((i2sclk / (packetlength*4)) * 10) / hi2s->Init.AudioFreq)) + 5);
            }
            else
            {
                tmp = (uint32_t)(((((i2sclk / (packetlength*8)) * 10) / hi2s->Init.AudioFreq)) + 5);
            }
            }
            else
            {
            /* MCLK output is disabled */
            tmp = (uint32_t)(((((i2sclk / packetlength) *10 ) / hi2s->Init.AudioFreq)) + 5);
            }

            /* Remove the flatting point */
            tmp = tmp / 10U;

            /* Check the parity of the divider */
            i2sodd = (uint16_t)(tmp & (uint16_t)1U);

            /* Compute the i2sdiv prescaler */
            i2sdiv = (uint16_t)((tmp - i2sodd) / 2U);

            /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
            i2sodd = (uint32_t) (i2sodd << 8U);
        }

        /* Test if the divider is 1 or 0 or greater than 0xFF */
        if((i2sdiv < 2U) || (i2sdiv > 0xFFU))
        {
            /* Set the default values */
            i2sdiv = 2U;
            i2sodd = 0U;

            /* Set the error code and execute error callback*/
            SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_PRESCALER);
            HAL_I2S_ErrorCallback(hi2s);
            return  HAL_ERROR;
        }

        /* Write to SPIx I2SPR register the computed value */
        hi2s->Instance->I2SPR = (uint32_t)((uint32_t)i2sdiv | (uint32_t)(i2sodd | (uint32_t)hi2s->Init.MCLKOutput));

        /* Configure the I2S with the I2S_InitStruct values */
        tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(hi2s->Init.Mode | \
                            (uint16_t)(hi2s->Init.Standard | (uint16_t)(hi2s->Init.DataFormat | \
                            (uint16_t)hi2s->Init.CPOL))));

        #if defined(SPI_I2SCFGR_ASTRTEN)
        if ((hi2s->Init.Standard == I2S_STANDARD_PCM_SHORT) ||(hi2s->Init.Standard == I2S_STANDARD_PCM_LONG))
        {
        /* Write to SPIx I2SCFGR */
            WRITE_REG(hi2s->Instance->I2SCFGR,(tmpreg | SPI_I2SCFGR_ASTRTEN));
        }
        else
        {
        /* Write to SPIx I2SCFGR */
            WRITE_REG(hi2s->Instance->I2SCFGR,tmpreg);
        }
        #else
        /* Write to SPIx I2SCFGR */
        WRITE_REG(hi2s->Instance->I2SCFGR, tmpreg);
        #endif

        #if defined (SPI_I2S_FULLDUPLEX_SUPPORT)

        /* Configure the I2S extended if the full duplex mode is enabled */
        assert_param(IS_I2S_FULLDUPLEX_MODE(hi2s->Init.FullDuplexMode));

        if(hi2s->Init.FullDuplexMode == I2S_FULLDUPLEXMODE_ENABLE)
        {
            /* Set FullDuplex I2S IrqHandler ISR if FULLDUPLEXMODE is enabled */
            hi2s->IrqHandlerISR = HAL_I2SEx_FullDuplex_IRQHandler;

            /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
            CLEAR_BIT(I2SxEXT(hi2s->Instance)->I2SCFGR,(SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CKPOL | \
                                                        SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
                                                        SPI_I2SCFGR_I2SE | SPI_I2SCFGR_I2SMOD));
            I2SxEXT(hi2s->Instance)->I2SPR = 2U;

            /* Get the I2SCFGR register value */
            tmpreg = I2SxEXT(hi2s->Instance)->I2SCFGR;

            /* Get the mode to be configured for the extended I2S */
            if((hi2s->Init.Mode == I2S_MODE_MASTER_TX) || (hi2s->Init.Mode == I2S_MODE_SLAVE_TX))
            {
            tmp = I2S_MODE_SLAVE_RX;
            }
            else /* I2S_MODE_MASTER_RX ||  I2S_MODE_SLAVE_RX */
            {
            tmp = I2S_MODE_SLAVE_TX;
            }

            /* Configure the I2S Slave with the I2S Master parameter values */
            tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(tmp | \
                                (uint16_t)(hi2s->Init.Standard | (uint16_t)(hi2s->Init.DataFormat | \
                                (uint16_t)hi2s->Init.CPOL))));

            /* Write to SPIx I2SCFGR */
            WRITE_REG(I2SxEXT(hi2s->Instance)->I2SCFGR,tmpreg);
        }
        #endif /* SPI_I2S_FULLDUPLEX_SUPPORT */

        hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
        hi2s->State     = HAL_I2S_STATE_READY;

        return HAL_OK;








    }

    return enRet;
}

/**
 * @brief  Fills each stc_i2s_init_t member with default value.
 * @param  [out] pstcI2sInit            Pointer to a @ref stc_i2s_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: stc_i2s_init_t member initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t I2S_StructInit(stc_i2s_init_t *pstcI2sInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcI2sInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcI2sInit->u32ClockSrc         = I2S_CLK_SRC_PLL;
        pstcI2sInit->u32Mode             = I2S_MD_MASTER;
        pstcI2sInit->u32ComProtocol      = I2S_COM_PROTOCOL_PHILLIPS;
        pstcI2sInit->u32TransMode        = I2S_TRANS_MD_HALF_DUPLEX_RX;
        pstcI2sInit->u32AudioFreq        = I2S_AUDIO_FREQ_DEFAULT;
        pstcI2sInit->u32ChLen            = I2S_CH_LEN_16BIT;
        pstcI2sInit->u32DataLen          = I2S_DATA_LEN_16BIT;
        pstcI2sInit->u32MCKOutput        = I2S_MCK_OUTPUT_DISABLE;
        pstcI2sInit->u32TransFIFOLevel   = I2S_TRANS_LVL2;
        pstcI2sInit->u32ReceiveFIFOLevel = I2S_RECEIVE_LVL2;
    }

    return enRet;
}

/**
 * @brief  Set the software reset of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32ResetType            Software reset type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_RST_TYPE_SW:      I2S software reset
 *           @arg I2S_RST_TYPE_CODEC:   Reset codec of I2S
 *           @arg I2S_RST_TYPE_FIFO:    Reset FIFO of I2S
 *           @arg I2S_RST_TYPE_ALL:     All of the above
 * @retval None
 */
void I2S_SetSWReset(M4_I2S_TypeDef *I2Sx, uint32_t u32ResetType)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_RST_TYPE(u32ResetType));

    SET_REG32_BIT(I2Sx->CTRL, u32ResetType);
    CLEAR_REG32_BIT(I2Sx->CTRL, u32ResetType);
}

/**
 * @brief  Set the transfer mode for the I2S communication.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Mode                 Transfer mode
 *         This parameter can be one of the following values:
 *           @arg I2S_TRANS_MD_HALF_DUPLEX_RX:  Receive only and half duplex mode
 *           @arg I2S_TRANS_MD_HALF_DUPLEX_TX:  Send only and half duplex mode
 *           @arg I2S_TRANS_MD_FULL_DUPLEX:     Full duplex mode
 * @retval None
 */
void I2S_SetTransMode(M4_I2S_TypeDef *I2Sx, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_TRANS_MD(u32Mode));

    MODIFY_REG32(I2Sx->CTRL, (I2S_CTRL_DUPLEX | I2S_CTRL_SDOE), u32Mode);
}

/**
 * @brief  Set the transfer FIFO level of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Level                Transfer FIFO level
 *         This parameter can be one of the following values:
 *           @arg I2S_TRANS_LVL0:       Transfer FIFO level is 0
 *           @arg I2S_TRANS_LVL1:       Transfer FIFO level is 1
 *           @arg I2S_TRANS_LVL2:       Transfer FIFO level is 2
 *           @arg I2S_TRANS_LVL3:       Transfer FIFO level is 3
 *           @arg I2S_TRANS_LVL4:       Transfer FIFO level is 4
 * @retval None
 */
void I2S_SetTransFIFOLevel(M4_I2S_TypeDef *I2Sx, uint32_t u32Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_TRANS_LVL(u32Level));

    MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_TXBIRQWL, u32Level);
}

/**
 * @brief  Set the receive FIFO level of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Level                Receive FIFO level
 *         This parameter can be one of the following values:
 *           @arg I2S_RECEIVE_LVL0:     Receive FIFO level is 0
 *           @arg I2S_RECEIVE_LVL1:     Receive FIFO level is 1
 *           @arg I2S_RECEIVE_LVL2:     Receive FIFO level is 2
 *           @arg I2S_RECEIVE_LVL3:     Receive FIFO level is 3
 *           @arg I2S_RECEIVE_LVL4:     Receive FIFO level is 4
 * @retval None
 */
void I2S_SetReceiveFIFOLevel(M4_I2S_TypeDef *I2Sx, uint32_t u32Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_RECEIVE_LVL(u32Level));

    MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_RXBIRQWL, u32Level);
}

/**
 * @brief  Set the communication protocol of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Protocol             Communication protocol
 *         This parameter can be one of the following values:
 *           @arg I2S_COM_PROTOCOL_PHILLIPS:    Phillips protocol
 *           @arg I2S_COM_PROTOCOL_MSB:         MSB justified protocol
 *           @arg I2S_COM_PROTOCOL_LSB:         LSB justified protocol
 *           @arg I2S_COM_PROTOCOL_PCM_SHORT:   PCM short-frame protocol
 *           @arg I2S_COM_PROTOCOL_PCM_LONG:    PCM long-frame protocol
 * @retval None
 */
void I2S_SetComProtocol(M4_I2S_TypeDef *I2Sx, uint32_t u32Protocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_COM_PROTOCOL(u32Protocol));

    MODIFY_REG32(I2Sx->CFGR, (I2S_CFGR_I2SSTD | I2S_CFGR_PCMSYNC), u32Protocol);
}



/**
 * @brief  Set the audio frequency for the I2S communication.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Freq                 Audio frequency
 *         This parameter can be 'I2S_AUDIO_FREQ_DEFAULT' or between
 *         'I2S_AUDIO_FREQ_8K' and 'I2S_AUDIO_FREQ_192K':
 *           @arg I2S_AUDIO_FREQ_192K:          FS = 192000Hz
 *           @arg I2S_AUDIO_FREQ_8K:            FS = 8000Hz
 *           @arg I2S_AUDIO_FREQ_DEFAULT
 * @retval None
 */
en_result_t I2S_SetAudioFreq(M4_I2S_TypeDef *I2Sx, uint32_t u32Freq)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_AUDIO_FREQ(u32Freq));
}



/**
 * @brief  Enable or disable MCK clock output.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_MCKOutputCmd(M4_I2S_TypeDef *I2Sx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, I2S_CTRL_MCKOE);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, I2S_CTRL_MCKOE);
    }
}

/**
 * @brief  Enable or disable the function of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Func                 I2S function
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FUNC_TXE:         Transfer function
 *           @arg I2S_FUNC_RXE:         Receive function
 *           @arg I2S_FUNC_ALL:         All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_FuncCmd(M4_I2S_TypeDef* I2Sx, uint32_t u32Func, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_FUNC(u32Func));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, u32Func);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, u32Func);
    }
}





void I2S_WriteData(M4_I2S_TypeDef *I2Sx, uint32_t u32Data);
uint32_t I2S_ReadData(const M4_I2S_TypeDef *I2Sx);
en_result_t I2S_Trans(M4_I2S_TypeDef *I2Sx, const void *pvBuf, uint32_t u32Len, uint32_t u32Timeout);
en_result_t I2S_Receive(M4_I2S_TypeDef *I2Sx, void *pvBuf, uint32_t u32Len, uint32_t u32Timeout);




/**
 * @brief  Enable or disable specified I2S interrupt.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32IntType              Interrupt type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_INT_TX:           Transfer interrupt
 *           @arg I2S_INT_RX:           Receive interrupt
 *           @arg I2S_INT_ERR:          Communication error interrupt
 *           @arg I2S_INT_ALL:          All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_IntCmd(M4_I2S_TypeDef *I2Sx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, u32IntType);
    }
}

/**
 * @brief  Get I2S flag status.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Flag                 I2S flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FLAG_TX_ALARM:    Transfer buffer alarm flag
 *           @arg I2S_FLAG_RX_ALARM:    Receive buffer alarm flag
 *           @arg I2S_FLAG_TX_EMPTY:    Transfer buffer empty flag
 *           @arg I2S_FLAG_TX_FULL:     Transfer buffer full flag
 *           @arg I2S_FLAG_RX_EMPTY:    Receive buffer empty flag
 *           @arg I2S_FLAG_RX_FULL:     Receive buffer full flag
 *           @arg I2S_FLAG_TX_ERR:      Transfer overflow or underflow flag
 *           @arg I2S_FLAG_RX_ERR:      Receive overflow flag
 *           @arg I2S_FLAG_ALL:         All of the above
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t I2S_GetStatus(M4_I2S_TypeDef *I2Sx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;
    uint32_t u32NormalFlag;
    uint32_t u32ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_FLAG(u32Flag));

    u32NormalFlag = u32Flag & 0xFFFFUL;
    u32ErrorFlag  = u32Flag >> 16U;
    if (0UL != u32NormalFlag)
    {
        if (0UL != (READ_REG32_BIT(I2Sx->SR, u32NormalFlag)))
        {
            enFlagSta = Set;
        }
    }
    if ((Reset == enFlagSta) && (0UL != u32ErrorFlag))
    {
        if (0UL != (READ_REG32_BIT(I2Sx->ER, u32ErrorFlag)))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear I2S flag.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Flag                 I2S flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FLAG_TX_ERR:      Transfer overflow or underflow flag
 *           @arg I2S_FLAG_RX_ERR:      Receive overflow flag
 *           @arg I2S_CLR_FLAG_ALL:     All of the above
 * @retval None
 */
void I2S_ClearStatus(M4_I2S_TypeDef *I2Sx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_CLR_FLAG(u32Flag));

    CLEAR_REG32_BIT(I2Sx->ER, u32Flag);
}

/**
 * @}
 */

#endif /* DDL_I2S_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
