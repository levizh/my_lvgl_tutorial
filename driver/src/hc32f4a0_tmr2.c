/**
 *******************************************************************************
 * @file  hc32f4a0_timer2.c
 * @brief This file provides firmware functions to manage the TIMER2
 *        (TIMER2).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-06       Wuze            First version
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
#include "hc32f4a0_tmr2.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TIMER2 TIMER2
 * @brief TIMER2 Driver Library
 * @{
 */
#if (DDL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR2_Local_Macros TIMER2 Local Macros
 * @{
 */

/**
 * @defgroup TMR2_Configuration_Bit_Mask TIMER2 Configuration Bit Mask
 * @{
 */
#define TMR2_BCONR_INIT_MSK                 (TMR2_BCONR_CAPMDA | TMR2_BCONR_SYNSA | TMR2_BCONR_SYNCLKA | TMR2_BCONR_ASYNCLKA | \
                                             TMR2_BCONR_CKDIVA | TMR2_BCONR_SYNCLKAT_0 | TMR2_BCONR_SYNCLKAT_1)
#define TMR2_FUNC_MODE_MSK                  (TMR2_BCONR_CAPMDA)
#define TMR2_CLK_SRC_MSK                    (TMR2_BCONR_SYNSA |TMR2_BCONR_SYNCLKA |TMR2_BCONR_ASYNCLKA | TMR2_BCONR_SYNCLKAT_0 | \
                                             TMR2_BCONR_SYNCLKAT_1)
#define TMR2_CLK_DIV_MSK                    (TMR2_BCONR_CKDIVA)
#define TMR2_PWM_START_POLARITY_MSK         (TMR2_PCONR_STACA)
#define TMR2_PWM_STOP_POLARITY_MSK          (TMR2_PCONR_STPCA)
#define TMR2_PWM_CM_POLARITY_MSK            (TMR2_PCONR_CMPCA)
#define TMR2_PWM_POLARITY_MSK               (TMR2_PCONR_STACA | TMR2_PCONR_STPCA | TMR2_PCONR_CMPCA)
#define TMR2_FILTER_CLK_DIV_MSK             (TMR2_PCONR_NOFICKA)
#define TMR2_START_COND_MSK                 (TMR2_HCONR_HSTAA0 | TMR2_HCONR_HSTAA1 | TMR2_HCONR_HSTAA2)
#define TMR2_STOP_COND_MSK                  (TMR2_HCONR_HSTPA0 | TMR2_HCONR_HSTPA1 | TMR2_HCONR_HSTPA2)
#define TMR2_CLR_COND_MSK                   (TMR2_HCONR_HCLEA0 | TMR2_HCONR_HCLEA1 | TMR2_HCONR_HCLEA2)
#define TMR2_CAPT_COND_MSK                  (TMR2_HCONR_HICPA0 | TMR2_HCONR_HICPA1 | TMR2_HCONR_HICPA2)
#define TMR2_TRIG_COND_MSK                  (TMR2_START_COND_MSK | TMR2_STOP_COND_MSK | TMR2_CLR_COND_MSK | TMR2_CAPT_COND_MSK)
#define TMR2_INT_TYPE_MSK                   (TMR2_ICONR_CMENA | TMR2_ICONR_OVENA)
#define TMR2_FLAG_MSK                       (TMR2_FLAG_CNT_MATCH | TMR2_FLAG_CNT_OVF)
#define TMR2_COM_TRIG_EN_MSK                (TMR2_COM1_TRIG_ENABLE | TMR2_COM2_TRIG_ENABLE)
#define TMR2_TRIG_EVENT_MSK                 (AOS_TMR2_HTSSR_TRGSEL)
/**
 * @}
 */

/**
 * @defgroup TMR2_Channel_Cfg_Bit_Field_Offset TIMER2 Channel Configuration Bit Field Offset
 * @{
 */
#define TMR2_BCONR_OFFSET                   (TMR2_BCONR_CSTB_POS)
#define TMR2_ICONR_OFFSET                   (TMR2_ICONR_CMENB_POS)
#define TMR2_PCONR_OFFSET                   (TMR2_PCONR_STACB_POS)
#define TMR2_HCONR_OFFSET                   (TMR2_HCONR_HSTAB0_POS)
/**
 * @}
 */

/**
 * @defgroup TMR2_Register_Bit_Band TIMER2 Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(__reg__)                  ((uint32_t)&(__reg__) - __PERIP_BASE)
#define __BIT_BAND_ADDR(__reg__, __pos__)   ((__REG_OFS(__reg__) << 5U) + ((uint32_t)(__pos__) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(__reg__, __pos__)          (*(__IO uint32_t *)__BIT_BAND_ADDR((__reg__), (__pos__)))
/**
 * @}
 */

/**
 * @defgroup TMR2_Check_Parameters_Validity TIMER2 check parameters validity
 * @{
 */
#define IS_TMR2_UNIT(x)                                                        \
(   ((x) == M4_TMR2_1)                       ||                                \
    ((x) == M4_TMR2_2)                       ||                                \
    ((x) == M4_TMR2_3)                       ||                                \
    ((x) == M4_TMR2_4))

#define IS_TMR2_CH(x)                                                          \
(   ((x) <= TMR2_CH_B))

#define IS_TMR2_FUNC_MODE(x)                                                   \
(   ((x) == TMR2_FUNC_COMPARE)              ||                                 \
    ((x) == TMR2_FUNC_CAPTURE))

#define IS_TMR2_CLK_SRC(x)                                                     \
(   ((x) == TMR2_CLK_SYNC_PCLK1)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TRIGR)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TRIGF)            ||                                 \
    ((x) == TMR2_CLK_SYNC_EVENT)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TIMER6_OVF)       ||                                 \
    ((x) == TMR2_CLK_SYNC_TIMER6_UDF)       ||                                 \
    ((x) == TMR2_CLK_ASYNC_LRC)             ||                                 \
    ((x) == TMR2_CLK_ASYNC_XTAL32)          ||                                 \
    ((x) == TMR2_CLK_ASYNC_PIN_CLK))

#define IS_TMR2_STATUS_FLAG(x)                                                 \
(   ((x) == TMR2_FLAG_CNT_MATCH)            ||                                 \
    ((x) == TMR2_FLAG_CNT_OVF))

#define IS_TMR2_CLK_DIV(x)                                                     \
(   ((x) == TMR2_CLK_DIV_1)                 ||                                 \
    ((x) == TMR2_CLK_DIV_2)                 ||                                 \
    ((x) == TMR2_CLK_DIV_4)                 ||                                 \
    ((x) == TMR2_CLK_DIV_8)                 ||                                 \
    ((x) == TMR2_CLK_DIV_16)                ||                                 \
    ((x) == TMR2_CLK_DIV_32)                ||                                 \
    ((x) == TMR2_CLK_DIV_64)                ||                                 \
    ((x) == TMR2_CLK_DIV_128)               ||                                 \
    ((x) == TMR2_CLK_DIV_256)               ||                                 \
    ((x) == TMR2_CLK_DIV_512)               ||                                 \
    ((x) == TMR2_CLK_DIV_1024))

#define IS_TMR2_FILTER_CLK_DIV(x)                                              \
(   ((x) == TMR2_FILTER_CLK_DIV_1)          ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV_4)          ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV_16)         ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV_64))

#define IS_TMR2_PWM_START_POLARITY(x)                                          \
(   ((x) == TMR2_PWM_START_LOW)             ||                                 \
    ((x) == TMR2_PWM_START_HIGH)            ||                                 \
    ((x) == TMR2_PWM_START_KEEP))

#define IS_TMR2_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMR2_PWM_STOP_LOW)              ||                                 \
    ((x) == TMR2_PWM_STOP_HIGH)             ||                                 \
    ((x) == TMR2_PWM_STOP_KEEP))

#define IS_TMR2_PWM_CM_POLARITY(x)                                             \
(   ((x) == TMR2_PWM_CM_LOW)                ||                                 \
    ((x) == TMR2_PWM_CM_HIGH)               ||                                 \
    ((x) == TMR2_PWM_CM_KEEP)               ||                                 \
    ((x) == TMR2_PWM_CM_REVERSE))

#define IS_TMR2_PWM_STATE(x)                                                   \
(   ((x) <= TMR2_PWM_CNT_MATCH))

#define IS_TMR2_PWM_POLARITY(x)                                                \
(   ((x) <= TMR2_PWM_OUT_REVERSE))

/**
 * @}
 */

/**
 * @defgroup TMR2_Miscellaneous_Macros TIMER2 Miscellaneous Macros
 * @{
 */
#define TMR2_CH_COUNT                       (2U)
#define IO_REG32(reg)                       ((__IO uint32_t *)((uint32_t)&(reg)))
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
static en_result_t TMR2_AsyncCheck(uint32_t u32RegAddr, uint32_t u32BitMsk, uint32_t u32BitVal);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__IO uint32_t m_u32AsyncDelay = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Functions TIMER2 Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified TIMER2 channel according to the specified parameters \
 *         in the structure stc_tmr2_init_t
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  pstcInit               Pointer to a stc_tmr2_init_t structure value that \
 *                                      contains the configuration information for the TIMER2 channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -pstcInit == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_Init(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_init_t *pstcInit)
{
    uint32_t u32Temp;
    uint32_t u32AsyncClkFreq = 0U;
    uint32_t u32CMPRAddr;
    uint32_t u32CNTRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (pstcInit != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_FUNC_MODE(pstcInit->u32FuncMode));
        DDL_ASSERT(IS_TMR2_CLK_SRC(pstcInit->u32ClkSrc));
        DDL_ASSERT(IS_TMR2_CLK_DIV(pstcInit->u32ClkDiv));

        u32Temp     = (uint32_t)u8Tmr2Ch * 4U;
        u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + u32Temp;
        u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + u32Temp;
        RW_MEM32(u32CMPRAddr) = pstcInit->u32CmpVal;
        RW_MEM32(u32CNTRAddr) = pstcInit->u32CntInitVal;

        u32Temp = pstcInit->u32FuncMode | \
                  pstcInit->u32ClkSrc   | \
                  pstcInit->u32ClkDiv;

        /* Channel bit filed offset. */
        u8Tmr2Ch *= TMR2_BCONR_OFFSET;
        MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_INIT_MSK << u8Tmr2Ch), (u32Temp << u8Tmr2Ch));

        enRet = Ok;
        switch (pstcInit->u32ClkSrc)
        {
        case TMR2_CLK_ASYNC_LRC:
        case TMR2_CLK_ASYNC_XTAL32:
            u32AsyncClkFreq = XTAL32_VALUE;
            break;
        case TMR2_CLK_ASYNC_PIN_CLK:
            u32AsyncClkFreq = pstcInit->u32AsyncClkFreq;
            break;
        default:
            break;
        }
        if (u32AsyncClkFreq != 0U)
        {
            enRet = TMR2_SetAsyncDelay(u32AsyncClkFreq, pstcInit->u32ClkDiv);
        }
    }

    return enRet;
}

/**
 * @brief  Set a default value for TIMER2 initialization structure.
 * @param  [in]  pstcInit           Pointer to a stc_tmr2_init_t structure that
 *                                  contains configuration information.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pstcInit == NULL.
 */
en_result_t TMR2_StructInit(stc_tmr2_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u32FuncMode     = TMR2_FUNC_COMPARE;
        pstcInit->u32ClkSrc       = TMR2_CLK_SYNC_PCLK1;
        pstcInit->u32ClkDiv       = TMR2_CLK_DIV_1;
        pstcInit->u32CmpVal       = 0xFFFFUL;
        pstcInit->u32CntInitVal   = 0U;
        pstcInit->u32AsyncClkFreq = 0U;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the specified TIMER2 unit.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   TMR2x == NULL.
 */
en_result_t TMR2_DeInit(M4_TMR2_TypeDef *TMR2x)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMR2x != NULL)
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));

        TMR2_Stop(TMR2x, TMR2_CH_A);
        TMR2_Stop(TMR2x, TMR2_CH_B);

        CLEAR_REG32(TMR2x->CNTAR);
        CLEAR_REG32(TMR2x->CNTBR);
        CLEAR_REG32(TMR2x->BCONR);
        CLEAR_REG32(TMR2x->ICONR);
        CLEAR_REG32(TMR2x->PCONR);
        CLEAR_REG32(TMR2x->HCONR);
        CLEAR_REG32(TMR2x->STFLR);

        WRITE_REG32(TMR2x->CMPAR, 0xFFFFU);
        WRITE_REG32(TMR2x->CMPBR, 0xFFFFU);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures the specified channel's PWM output polarity according to the specified \
 *         parameters in the structure stc_tmr2_pwm_cfg_t
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  pstcCfg                Pointer to a stc_tmr2_pwm_cfg_t structure value that contains \
 *                                      the configuration information for the PWM output polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -pstcCfg == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_PWM_Config(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_pwm_cfg_t *pstcCfg)
{
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (pstcCfg != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_PWM_START_POLARITY(pstcCfg->u32StartPolarity));
        DDL_ASSERT(IS_TMR2_PWM_STOP_POLARITY(pstcCfg->u32StopPolarity));
        DDL_ASSERT(IS_TMR2_PWM_CM_POLARITY(pstcCfg->u32CMPolarity));

        u32Cfg = pstcCfg->u32StartPolarity | \
                 pstcCfg->u32StopPolarity  | \
                 pstcCfg->u32CMPolarity;
        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, (TMR2_PWM_POLARITY_MSK << u8Tmr2Ch), (u32Cfg << u8Tmr2Ch));

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for TIMER2 PWM configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_tmr2_pwm_cfg_t structure value that contains \
 *                                      the configuration information for the PWM output polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMR2_PWM_StructInit(stc_tmr2_pwm_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u32StartPolarity = TMR2_PWM_START_HIGH;
        pstcCfg->u32StopPolarity  = TMR2_PWM_STOP_LOW;
        pstcCfg->u32CMPolarity    = TMR2_PWM_CM_REVERSE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable PWM output of the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable PWM output of the specified TIMER2's channel.
 *   @arg  Disable:                     Disable PWM output of the specified TIMER2's channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_PWM_Cmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState)
{
    uint8_t au8EnPos[] = {TMR2_PCONR_OUTENA_POS, TMR2_PCONR_OUTENB_POS};
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        BIT_BAND(TMR2x->PCONR, au8EnPos[u8Tmr2Ch]) = (uint32_t)enNewState;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the channel's hardware trigger condition according to the specified \
 *         parameters in the structure stc_tmr2_trig_cond_t
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  pstcCond               Pointer to a stc_tmr2_trig_cond_t structure value that contains \
 *                                      the configuration information for the hardware condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -pstcCond == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetTrigCond(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_trig_cond_t *pstcCond)
{
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (pstcCond != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));

        u32Cfg  = pstcCond->u32StartCond | \
                  pstcCond->u32StopCond  | \
                  pstcCond->u32ClrCond   | \
                  pstcCond->u32CaptCond;
        u32Cfg &= TMR2_TRIG_COND_MSK;
        u8Tmr2Ch *= TMR2_HCONR_OFFSET;
        MODIFY_REG32(TMR2x->HCONR, (TMR2_TRIG_COND_MSK << u8Tmr2Ch), (u32Cfg << u8Tmr2Ch));
    }

    return enRet;
}

/**
 * @brief  Set a default value for TIMER2 hardware trigger condition structure.
 * @param  [in]  pstcCond               Pointer to a stc_tmr2_trig_cond_t structure value that contains \
 *                                      the configuration information for the hardware condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCond == NULL.
 */
en_result_t TMR2_TrigCondStructInit(stc_tmr2_trig_cond_t *pstcCond)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        pstcCond->u32StartCond = TMR2_START_COND_INVALID;
        pstcCond->u32StopCond  = TMR2_STOP_COND_INVALID;
        pstcCond->u32ClrCond   = TMR2_CLR_COND_INVALID;
        pstcCond->u32CaptCond  = TMR2_CAPT_COND_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set trigger event for TIMER2.
 * @param  [in]  enEvent            An en_event_src_t enumeration type value.
 * @retval None
 */
void TMR2_SetTrigEvent(en_event_src_t enEvent)
{
    MODIFY_REG32(M4_AOS->TMR2_HTSSR, TMR2_TRIG_EVENT_MSK, enEvent);
}

/**
 * @brief  Enable or disable common trigger event for the specified usage.
 * @param  [in]  u32ComTrigEn           Common trigger event enable bit mask.
 *                                      This parameter can be a value of @ref TMR2_Common_Trigger_Event_Command
 *   @arg  TMR2_COM1_TRIG_DISABLE:      Enable common trigger event 1 for the specified usage.
 *   @arg  TMR2_COM2_TRIG_DISABLE:      Enable common trigger event 2 for the specified usage.
 *   @arg  TMR2_COM1_TRIG_ENABLE:       Disable common trigger event 1 for the specified usage.
 *   @arg  TMR2_COM2_TRIG_ENABLE:       Disable common trigger event 2 for the specified usage.
 * @retval None
 */
void TMR2_ComTrigCmd(uint32_t u32ComTrigEn)
{
    u32ComTrigEn &= TMR2_COM_TRIG_EN_MSK;
    MODIFY_REG32(M4_AOS->TMR2_HTSSR, TMR2_COM_TRIG_EN_MSK, u32ComTrigEn);
}

/**
 * @brief  Set clock division for the filter of the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32ClkDiv              Clock division for the specified TIMER2 unit channel filter.
 *   @arg  TMR2_FILTER_CLK_DIV_1:       Clock source.
 *   @arg  TMR2_FILTER_CLK_DIV_4:       Clock source / 4.
 *   @arg  TMR2_FILTER_CLK_DIV_16:      Clock source / 16.
 *   @arg  TMR2_FILTER_CLK_DIV_64:      Clock source / 64.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_FilterConfig(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_FILTER_CLK_DIV(u32ClkDiv));

        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, \
                     (TMR2_FILTER_CLK_DIV_MSK << u8Tmr2Ch), \
                     (u32ClkDiv << u8Tmr2Ch));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the filter of the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the filter of the specified channel.
 *   @arg  Disable:                     Disable the filter of the specified channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_FilterCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState)
{
    uint8_t au8EnPos[] = {TMR2_PCONR_NOFIENA_POS, TMR2_PCONR_NOFIENB_POS};
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        BIT_BAND(TMR2x->PCONR, au8EnPos[u8Tmr2Ch]) = (uint32_t)enNewState;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the interrupt of the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32IntType             The interrupt type.
 *                                      This parameter can be a value(s) of @ref TMR2_Interrupt_Type
 *   @arg  TMR2_INT_CNT_MATCH:          TIMER2 count match interrupt.
 *   @arg  TMR2_INT_CNT_OVF:            TIMER2 count overflow interrupt.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified interrupt.
 *   @arg  Disable:                     Disable the specified interrupt.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_IntCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, \
                          uint32_t u32IntType, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u8Tmr2Ch    *= TMR2_ICONR_OFFSET;
        u32IntType  &= TMR2_INT_TYPE_MSK;
        u32IntType <<= u8Tmr2Ch;

        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMR2x->ICONR, u32IntType);
        }
        else
        {
            CLEAR_REG32_BIT(TMR2x->ICONR, u32IntType);
        }
    }

    return enRet;
}

/**
 * @brief  Start the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:  -TMR2x == NULL.
 *                                 -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_Start(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t u32Cfg   = TMR2_BCONR_CSTA;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        if (u8Tmr2Ch == TMR2_CH_B)
        {
            u32Cfg = TMR2_BCONR_CSTB;
        }
        SET_REG32_BIT(TMR2x->BCONR, u32Cfg);

        if (m_u32AsyncDelay != 0U)
        {
            /*!< Check if stop successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->BCONR, u32Cfg, u32Cfg);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Stop the specified channel of the specified TIMER2 unit.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:  -TMR2x == NULL.
 *                                 -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_Stop(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t au32Cfg[] = {TMR2_BCONR_CSTA, TMR2_BCONR_CSTB};
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        CLEAR_REG32_BIT(TMR2x->BCONR, au32Cfg[u8Tmr2Ch]);

        if (m_u32AsyncDelay != 0U)
        {
            /*!< Check if stop successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->BCONR, au32Cfg[u8Tmr2Ch], 0UL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Get the specified flag's status of the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @param  [in]  u32Flag            TIMER2 state flag.
 *                                  This parameter can be a value of @ref TMR2_State_Flag
 *   @arg  TMR2_FLAG_CNT_MATCH:     Counting match flag.
 *   @arg  TMR2_FLAG_CNT_OVF:       Counting overflow flag.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                     The specified flag is set.
 *   @arg  Reset:                   The specified flag is not set.
 */
en_flag_status_t TMR2_GetStatus(const M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag)
{
    en_flag_status_t enFlag = Reset;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_STATUS_FLAG(u32Flag));
        u32Flag <<= ((uint32_t)u8Tmr2Ch * TMR2_ICONR_OFFSET);
        if ((TMR2x->STFLR & u32Flag) != 0U)
        {
            enFlag = Set;
        }
    }

    return enFlag;
}

/**
 * @brief  Clear the specified flag state of the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @param  [in]  u32Flag            TIMER2 state flag.
 *                                  This parameter can be a value of @ref TMR2_State_Flag
 *   @arg  TMR2_FLAG_CNT_MATCH:     Counter match flag of channel A/B.
 *   @arg  TMR2_FLAG_CNT_OVF:       Counter overflow flag of channel A/B.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   TMR2x == NULL
 */
en_result_t TMR2_ClrStatus(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        /* Bit filed offset. */
        u8Tmr2Ch *= TMR2_ICONR_OFFSET;
        u32Flag  &= TMR2_FLAG_MSK;
        u32Flag <<= u8Tmr2Ch;
        CLEAR_REG32_BIT(TMR2x->STFLR, u32Flag);

        if (m_u32AsyncDelay != 0U)
        {
            /*!< Check if stop successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->STFLR, u32Flag, 0UL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set comparison value for the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @param  [in]  u32Val             The comparison for the specified TIMER2's channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:  -TMR2x == NULL.
 *                                 -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val)
{
    uint32_t u32CMPRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + (uint32_t)u8Tmr2Ch * 4U;
        RW_MEM32(u32CMPRAddr) = u32Val;

        if (m_u32AsyncDelay != 0U)
        {
            enRet = TMR2_AsyncCheck(u32CMPRAddr, 0xFFFFUL, u32Val);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Get comparison value of the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @retval The comparison value of the specified TIMER2's channel.
 */
uint32_t TMR2_GetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t u32CMPRAddr;
    uint32_t u32Ret = 0U;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + (uint32_t)u8Tmr2Ch * 4U;
        u32Ret = RW_MEM32(u32CMPRAddr);
    }

    return u32Ret;
}

/**
 * @brief  Set counter value for the specified channel of the specified TIMER2 unit.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel of the specified TIMER2 unit.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @param  [in]  u32Val             The counter value for the specified TIMER2's channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:  -TMR2x == NULL.
 *                                 -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val)
{
    uint32_t u32CNTRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + (uint32_t)u8Tmr2Ch * 4U;
        RW_MEM32(u32CNTRAddr) = u32Val;

        if (m_u32AsyncDelay != 0U)
        {
            enRet = TMR2_AsyncCheck(u32CNTRAddr, 0xFFFFUL, u32Val);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Get counter value of the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @retval The counter value of the specified TIMER2's channel.
 */
uint32_t TMR2_GetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t u32CNTRAddr;
    uint32_t u32Ret = 0U;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + (uint32_t)u8Tmr2Ch * 4U;
        u32Ret = RW_MEM32(u32CNTRAddr);
    }

    return u32Ret;
}

/**
 * @brief  Set function mode for the specified TIMER2's channel.
 * @param  [in]  TMR2x              Pointer to TIMER2 instance register base.
 *                                  This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:               TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:               TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:               TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:               TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch           The channel number of TIMER2.
 *                                  This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:               Channel A of TIMER2.
 *   @arg  TMR2_CH_B:               Channel B of TIMER2.
 * @param  [in]  u32FuncMode        Specifies the function for the specified TIMER2's channel.
 *                                  This parameter can be a value of @ref TMR2_Function_Mode
 *   @arg  TMR2_FUNC_COMPARE:       Set the function of the specified channel of TIMER2 unit as comparison output.
 *   @arg  TMR2_FUNC_CAPTURE:       Set the function of the specified channel of TIMER2 unit as capturing input.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:  -TMR2x == NULL.
 *                                 -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetFuncMode(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32FuncMode)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_FUNC_MODE(u32FuncMode));

        /* Bit filed offset. */
        u8Tmr2Ch *= TMR2_BCONR_OFFSET;
        u32Msk    = TMR2_FUNC_MODE_MSK << u8Tmr2Ch;
        u32Cfg    = u32FuncMode << u8Tmr2Ch;
        MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);

        if (m_u32AsyncDelay != 0U)
        {
            /*!< Check if write successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->BCONR, u32Msk, u32Cfg);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Specify the clock source for the specified TIMER2 channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32ClkSrc              Specifies the clock source for the specified TIMER2's channel.
 *                                      This parameter can be a value of @ref TMR2_Clock_Source
 *   @arg  TMR2_SYNC_CLK_PCLK1:         Synchronous clock source, PCLK1.
 *   @arg  TMR2_SYNC_CLK_TRIG_RISE:     Synchronous clock source, rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_SYNC_CLK_TRIG_FALL:     Synchronous clock source, falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_SYNC_CLK_EVENT:         Synchronous clock source, peripheral event.
 *   @arg  TMR2_CLK_SYNC_TIMER6_OVF:    Synchronous clock source, the event of counting overflow of TIMER6. \
 *                                      It is NO need to set register TMR2_HTSSR.
 *   @arg  TMR2_CLK_SYNC_TIMER6_UDF:    Synchronous clock source, the event of counting underflow of TIMER6. \
 *                                      It is NO need to set register TMR2_HTSSR.
 *   @arg  TMR2_ASYNC_CLK_LRC:          Asynchronous clock source, LRC.
 *   @arg  TMR2_ASYNC_CLK_XTAL32:       Asynchronous clock source, XTAL32.
 *   @arg  TMR2_ASYNC_CLK_PIN_CLK:      Asynchronous clock source, from pin TIM2_x_CLKA/B.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetClkSrc(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkSrc)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_CLK_SRC(u32ClkSrc));

        /* Bit filed offset. */
        u8Tmr2Ch *= TMR2_BCONR_OFFSET;
        u32Msk    = TMR2_CLK_SRC_MSK << u8Tmr2Ch;
        u32Cfg    = u32ClkSrc << u8Tmr2Ch;
        MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);

        if (m_u32AsyncDelay > 0U)
        {
            /*!< Check if write successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->BCONR, u32Msk, u32Cfg);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Specify the division of the clock source for the specified TIMER2 channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32ClkDiv              Specifies the clock source division for the specified TIMER2's channel.
 *                                      This parameter can be a value of @ref TMR2_Clock_Division
 *   @arg  TMR2_CLK_DIV_1:              Clock source.
 *   @arg  TMR2_CLK_DIV_2:              Clock source / 2.
 *   @arg  TMR2_CLK_DIV_4:              Clock source / 4.
 *   @arg  TMR2_CLK_DIV_8:              Clock source / 8.
 *   @arg  TMR2_CLK_DIV_16:             Clock source / 16.
 *   @arg  TMR2_CLK_DIV_32:             Clock source / 32.
 *   @arg  TMR2_CLK_DIV_64:             Clock source / 64.
 *   @arg  TMR2_CLK_DIV_128:            Clock source / 128.
 *   @arg  TMR2_CLK_DIV_256:            Clock source / 256.
 *   @arg  TMR2_CLK_DIV_512:            Clock source / 512.
 *   @arg  TMR2_CLK_DIV_1024:           Clock source / 1024.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_SetClkDiv(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_CLK_DIV(u32ClkDiv));

        /* Bit filed offset. */
        u8Tmr2Ch *= TMR2_BCONR_OFFSET;
        u32Msk    = TMR2_CLK_DIV_MSK << u8Tmr2Ch;
        u32Cfg    = u32ClkDiv << u8Tmr2Ch;
        MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);

        if (m_u32AsyncDelay > 0U)
        {
            /*!< Check if write successfully when using asynchronous clock. */
            enRet = TMR2_AsyncCheck((uint32_t)&TMR2x->BCONR, u32Msk, u32Cfg);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Calculate asynchronous delay via asynchronous clock frequency and it's division.
 * @param  [in]  u32AsyncClkFreq        Asynchronous clock frequency(Hz).
 * @param  [in]  u32ClkDiv              The clock division.
 *                                      This parameter can be a value of @ref TMR2_Clock_Division
 *   @arg  TMR2_CLK_DIV_1:              Clock source.
 *   @arg  TMR2_CLK_DIV_2:              Clock source / 2.
 *   @arg  TMR2_CLK_DIV_4:              Clock source / 4.
 *   @arg  TMR2_CLK_DIV_8:              Clock source / 8.
 *   @arg  TMR2_CLK_DIV_16:             Clock source / 16.
 *   @arg  TMR2_CLK_DIV_32:             Clock source / 32.
 *   @arg  TMR2_CLK_DIV_64:             Clock source / 64.
 *   @arg  TMR2_CLK_DIV_128:            Clock source / 128.
 *   @arg  TMR2_CLK_DIV_256:            Clock source / 256.
 *   @arg  TMR2_CLK_DIV_512:            Clock source / 512.
 *   @arg  TMR2_CLK_DIV_1024:           Clock source / 1024.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       u32AsyncClkFreq == 0.
 */
en_result_t TMR2_SetAsyncDelay(uint32_t u32AsyncClkFreq, uint32_t u32ClkDiv)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (u32AsyncClkFreq != 0U)
    {
        DDL_ASSERT(IS_TMR2_CLK_DIV(u32ClkDiv));

        u32ClkDiv = 1UL << (u32ClkDiv >> TMR2_BCONR_CKDIVA_POS);
        m_u32AsyncDelay = ((SystemCoreClock * u32ClkDiv) / u32AsyncClkFreq) * 3UL;
        if (m_u32AsyncDelay == 0U)
        {
            m_u32AsyncDelay = 3U;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified trigger condition of the specified TIMER2 channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32Cond                The specified condition(s).
 *                                      This parameter can be a value of
 *                                      @ref TMR2_Hardware_Start_Condition \
 *                                      @ref TMR2_Hardware_Stop_Condition  \
 *                                      @ref TMR2_Hardware_Clear_Condition \
 *                                      @ref TMR2_Hardware_Capture_Condition
 *   @arg  TMR2_START_COND_TRIG_RISE:   The condition of start is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_START_COND_TRIG_FALL:   The condition of start is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_START_COND_EVENT:       The condition of start is the specified event occurred.
 *   @arg  TMR2_STOP_COND_TRIG_RISE:    The condition of stop is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_STOP_COND_TRIG_FALL:    The condition of stop is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_STOP_COND_EVENT:        The condition of stop is the specified event occurred.
 *   @arg  TMR2_CLR_COND_TRIG_RISE:     The condition of clear(clear CNTAR/CNTBR) is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CLR_COND_TRIG_FALL:     The condition of clear(clear CNTAR/CNTBR) is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CLR_COND_EVENT:         The condition of clear(clear CNTAR/CNTBR) is the specified event occurred.
 *   @arg  TMR2_CAPT_COND_TRIG_RISE:    The condition for capturing is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CAPT_COND_TRIG_FALL:    The condition for capturing is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CAPT_COND_EVENT:        The condition for capturing is the specified event occurred.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_TrigCondCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32Cond &= TMR2_TRIG_COND_MSK;
        u8Tmr2Ch *= TMR2_HCONR_OFFSET;
        u32Cond <<= u8Tmr2Ch;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMR2x->HCONR, u32Cond);
        }
        else
        {
            CLEAR_REG32_BIT(TMR2x->HCONR, u32Cond);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set PWM start polarity for the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32Polarity            Specifies the PWM start polarity for the specified TIMER2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Start_Polarity
 *   @arg  TMR2_PWM_START_LOW:          PWM output low when counting start.
 *   @arg  TMR2_PWM_START_HIGH:         PWM output high when counting start.
 *   @arg  TMR2_PWM_START_KEEP:         PWM output keeps the current polarity when counting start.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_PWM_SetStartPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_PWM_START_POLARITY(u32Polarity));

        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, \
                     (TMR2_PWM_START_POLARITY_MSK << u8Tmr2Ch), \
                     (u32Polarity << u8Tmr2Ch));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set PWM stop polarity for the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32Polarity            Specifies the PWM stop polarity for the specified TIMER2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Stop_Polarity
 *   @arg  TMR2_PWM_STOP_LOW:           PWM output low when counting stop.
 *   @arg  TMR2_PWM_STOP_HIGH:          PWM output high when counting stop.
 *   @arg  TMR2_PWM_STOP_KEEP:          PWM output keeps the current polarity when counting stop.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_PWM_SetStopPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_PWM_STOP_POLARITY(u32Polarity));

        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, \
                     (TMR2_PWM_STOP_POLARITY_MSK << u8Tmr2Ch), \
                     (u32Polarity << u8Tmr2Ch));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set PWM count match polarity for the specified TIMER2's channel.
 * @param  [in]  TMR2x                  Pointer to TIMER2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TIMER2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TIMER2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TIMER2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TIMER2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TIMER2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TIMER2.
 *   @arg  TMR2_CH_B:                   Channel B of TIMER2.
 * @param  [in]  u32Polarity            Specifies the PWM count match polarity for the specified TIMER2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Count_Match_Polarity
 *   @arg  TMR2_PWM_CM_LOW:             PWM output low when counting match.
 *   @arg  TMR2_PWM_CM_HIGH:            PWM output high when counting match.
 *   @arg  TMR2_PWM_CM_KEEP:            PWM output keeps the current polarity when counting match.
 *   @arg  TMR2_PWM_CM_REVERSE:         PWM output reverses the current polarity when counting match.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:      -TMR2x == NULL.
 *                                     -u8Tmr2Ch >= TMR2_CH_COUNT.
 */
en_result_t TMR2_PWM_SetCntMatchPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMR2x != NULL) && (u8Tmr2Ch < TMR2_CH_COUNT))
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_PWM_CM_POLARITY(u32Polarity));

        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, \
                     (TMR2_PWM_CM_POLARITY_MSK << u8Tmr2Ch), \
                     (u32Polarity << u8Tmr2Ch));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup TMR2_Local_Functions TIMER2 Local Functions
 * @{
 */

/**
 * @brief  When using asynchronous clock, some registers require a delay between successive writes.
 * @param  [in]  ioREG                  Pointer to a TIMER2 register.
 * @param  [in]  u32BitMsk              The bit mask is to be compared.
 * @param  [in]  u32BitVal              The target value.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Time out.
 */
static en_result_t TMR2_AsyncCheck(uint32_t u32RegAddr, uint32_t u32BitMsk, uint32_t u32BitVal)
{
    uint32_t u32DlyCnt;
    en_result_t enRet = ErrorTimeout;

    if (m_u32AsyncDelay > 0U)
    {
        u32DlyCnt = m_u32AsyncDelay;
        /* Check if write successfully. */
        do
        {
            if ((RW_MEM32(u32RegAddr) & u32BitMsk) == u32BitVal)
            {
                enRet = Ok;
                break;
            }
        } while (u32DlyCnt-- != 0U);
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_TMR2_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
