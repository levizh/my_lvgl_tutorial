/**
 *******************************************************************************
 * @file  hc32f4a0_timer2.h
 * @brief This file contains all the functions prototypes of the TIMER2 driver
 *        library.
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
#ifndef __HC32F4A0_TMR2_H__
#define __HC32F4A0_TMR2_H__

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
 * @addtogroup DDL_TIMER2
 * @{
 */
#if (DDL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Types TIMER2 Global Types
 * @{
 */

/**
 * @brief TIMER2 initialization structure.
 */
typedef struct
{
    uint32_t u32FuncMode;                   /*!< Specify the function mode for TIMER2's channel.
                                                 This parameter can be a value of @ref TMR2_Function_Mode */
    uint32_t u32ClkSrc;                     /*!< Specify the clock source for TIMER2's channel.
                                                 This parameter can be a value of @ref TMR2_Clock_Source */
    uint32_t u32ClkDiv;                     /*!< Specify the division of the clock source.
                                                 This parameter can be a value of @ref TMR2_Clock_Division */
    uint32_t u32CmpVal;                     /*!< Specify the compare value depends on your application. */
    uint32_t u32CntVal;                     /*!< Initial value of the count register. */
    uint32_t u32AsyncClkFreq;               /*!< This parameter is the frequency(Hz) of the asynchronous clock input from pin TIM2_x_CLKA/B. */
} stc_tmr2_init_t;

/**
 * @brief TIMER2 PWM output polarity configuration structure.
 */
typedef struct
{
    uint32_t u32StartPolarity;              /*!< Specify the polarity of PWM output when TIMER2 counting start.
                                                 This parameter can be a value of @ref TMR2_PWM_Start_Polarity */
    uint32_t u32StopPolarity;               /*!< Specify the polarity of PWM output when TIMER2 counting stop.
                                                 This parameter can be a value of @ref TMR2_PWM_Stop_Polarity */
    uint32_t u32CMPolarity;                 /*!< Specify the polarity of PWM output when TIMER2 counting match.
                                                 This parameter can be a value of @ref TMR2_PWM_CM_Polarity */
} stc_tmr2_pwm_cfg_t;

/**
 * @brief TIMER2 hardware trigger condition configuration structure.
 */
typedef struct
{
    uint32_t u32StartCond;                  /*!< Specify the trigger condition of start counting.
                                                 This parameter can be a value of @ref TMR2_Hardware_Start_Condition */
    uint32_t u32StopCond;                   /*!< Specify the trigger condition of stop counting.
                                                 This parameter can be a value of @ref TMR2_Hardware_Stop_Condition */
    uint32_t u32ClrCond;                    /*!< Specify the trigger condition of clearing counter register.
                                                 This parameter can be a value of @ref TMR2_Hardware_Clear_Condition */
    uint32_t u32CaptCond;                   /*!< Specify the trigger condition of start capturing.
                                                 This parameter can be a value of @ref TMR2_Hardware_Capture_Condition */
} stc_tmr2_trig_cond_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Macros TIMER2 Global Macros
 * @{
 */

/**
 * @defgroup TMR2_Channel_Number TIMER2 Channel Number
 * @{
 */
#define TMR2_CH_A                       (0U)                            /*!< Channel A of TIMER2. */
#define TMR2_CH_B                       (1U)                            /*!< Channel B of TIMER2. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Function_Mode TIMER2 Function Mode
 * @{
 */
#define TMR2_FUNC_COMPARE               (0x0U)                          /*!< The function mode of TIMER2 is comparison ouput. */
#define TMR2_FUNC_CAPTURE               (TMR2_BCONR_CAPMDA)             /*!< The function mode of TIMER2 is capture the input. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Division TIMER2 Clock Division
 * @{
 */
#define TMR2_CLK_DIV_1                  (0x0U)                          /*!< Clock source. */
#define TMR2_CLK_DIV_2                  (TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 2. */
#define TMR2_CLK_DIV_4                  (TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 4. */
#define TMR2_CLK_DIV_8                  (TMR2_BCONR_CKDIVA_1 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 8. */
#define TMR2_CLK_DIV_16                 (TMR2_BCONR_CKDIVA_2)           /*!< Clock source / 16. */
#define TMR2_CLK_DIV_32                 (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 32. */
#define TMR2_CLK_DIV_64                 (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 64. */
#define TMR2_CLK_DIV_128                (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_1 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 128. */
#define TMR2_CLK_DIV_256                (TMR2_BCONR_CKDIVA_3)           /*!< Clock source / 256. */
#define TMR2_CLK_DIV_512                (TMR2_BCONR_CKDIVA_3 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 512. */
#define TMR2_CLK_DIV_1024               (TMR2_BCONR_CKDIVA_3 | \
                                         TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 1024. */

/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Source TIMER2 Clock Source
 * @{
 */
#define TMR2_CLK_SYNC_PCLK1             (0x0U)                          /*!< Synchronous clock source, PCLK1. */
#define TMR2_CLK_SYNC_TRIGR             (TMR2_BCONR_SYNCLKA_0)          /*!< Synchronous clock source, rising edge of TIM2_x_TRIGA/B. \
                                                                             One rising edge causes one count. */
#define TMR2_CLK_SYNC_TRIGF             (TMR2_BCONR_SYNCLKA_1)          /*!< Synchronous clock source, falling edge of TIM2_x_TRIGA/B. \
                                                                             One falling edge causes one count. */
#define TMR2_CLK_SYNC_EVENT             (TMR2_BCONR_SYNCLKA)            /*!< Synchronous clock source, peripheral event. The event is specified by register TMR2_HTSSR. \
                                                                             The event causes one count. */
#define TMR2_CLK_SYNC_TIMER6_OVF        (TMR2_BCONR_SYNCLKAT_0)         /*!< Synchronous clock source, the event of counting overflow of TIMER6. \
                                                                             It is NO need to set register TMR2_HTSSR. */
#define TMR2_CLK_SYNC_TIMER6_UDF        (TMR2_BCONR_SYNCLKAT_1)         /*!< Synchronous clock source, the event of counting underflow of TIMER6. \
                                                                             It is NO need to set register TMR2_HTSSR. */
#define TMR2_CLK_ASYNC_LRC              (TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, LRC(32.768KHz). */
#define TMR2_CLK_ASYNC_XTAL32           (TMR2_BCONR_ASYNCLKA_0 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, XTAL32(32.768KHz). */
#define TMR2_CLK_ASYNC_PIN_CLK          (TMR2_BCONR_ASYNCLKA_1 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, input from pin TIM2_x_CLKA/B. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Interrupt_Type TIMER2 Interrupt Type
 * @{
 */
#define TMR2_INT_CMP                    (TMR2_ICONR_CMENA)              /*!< TIMER2 count match interrupt. */
#define TMR2_INT_OVF                    (TMR2_ICONR_OVENA)              /*!< TIMER2 count overflow interrupt. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Start_Polarity TIMER2 PWM Start Polarity
 * @{
 */
#define TMR2_PWM_START_LOW              (0x0U)                          /*!< PWM output low when counting start. */
#define TMR2_PWM_START_HIGH             (TMR2_PCONR_STACA_0)            /*!< PWM output high when counting start. */
#define TMR2_PWM_START_KEEP             (TMR2_PCONR_STACA_1)            /*!< PWM output keeps the current polarity when counting start. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Stop_Polarity TIMER2 PWM Stop Polarity
 * @{
 */
#define TMR2_PWM_STOP_LOW               (0x0U)                          /*!< PWM output low when counting stop. */
#define TMR2_PWM_STOP_HIGH              (TMR2_PCONR_STPCA_0)            /*!< PWM output high when counting stop. */
#define TMR2_PWM_STOP_KEEP              (TMR2_PCONR_STPCA_1)            /*!< PWM output keeps the current polarity when counting stop. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Count_Match_Polarity TIMER2 PWM Count Match Polarity
 * @{
 */
#define TMR2_PWM_CM_LOW                 (0x0U)                          /*!< PWM output low when counting match. */
#define TMR2_PWM_CM_HIGH                (TMR2_PCONR_CMPCA_0)            /*!< PWM output high when counting match. */
#define TMR2_PWM_CM_KEEP                (TMR2_PCONR_CMPCA_1)            /*!< PWM output keeps the current polarity when counting match. */
#define TMR2_PWM_CM_REVERSE             (TMR2_PCONR_CMPCA_1 | \
                                         TMR2_PCONR_CMPCA_0)            /*!< PWM output reverses the current polarity when counting match. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Output_Polarity TIMER2 PWM Output Polarity
 * @{
 */
#define TMR2_PWM_OUT_LOW                (0U)                            /*!< The polarity of PWM output is low. */
#define TMR2_PWM_OUT_HI                 (1U)                            /*!< The polarity of PWM output is high. */
#define TMR2_PWM_OUT_KEEP               (2U)                            /*!< The polarity of PWM output keeps the current polarity. */
#define TMR2_PWM_OUT_REVERSE            (3U)                            /*!< The polarity of PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Filter_Clock_Division TIMER2 Filter Clock Prescaler
 * @{
 */
#define TMR2_FILTER_CLK_DIV_1           (0x0U)                          /*!< Clock source. */
#define TMR2_FILTER_CLK_DIV_4           (TMR2_PCONR_NOFICKA_0)          /*!< Clock source / 4. */
#define TMR2_FILTER_CLK_DIV_16          (TMR2_PCONR_NOFICKA_1)          /*!< Clock source / 16. */
#define TMR2_FILTER_CLK_DIV_64          (TMR2_PCONR_NOFICKA)            /*!< Clock source / 64. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Start_Condition TIMER2 Hardware Start Condition
 * @{
 */
#define TMR2_START_COND_INVALID         (0x0U)                          /*!< The start condition of TIMER2 is INVALID. */
#define TMR2_START_COND_TRIGR           (1UL << TMR2_HCONR_HSTAA0_POS)  /*!< The start condition of TIMER2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_TRIGF           (1UL << TMR2_HCONR_HSTAA1_POS)  /*!< The start condition of TIMER2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_EVENT           (1UL << TMR2_HCONR_HSTAA2_POS)  /*!< The start condition of TIMER2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Stop_Condition TIMER2 Hardware Stop Condition
 * @{
 */
#define TMR2_STOP_COND_INVALID          (0x0U)                          /*!< The stop condition of TIMER2 is INVALID. */
#define TMR2_STOP_COND_TRIGR            (TMR2_HCONR_HSTPA0)             /*!< The stop condition of TIMER2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_TRIGF            (TMR2_HCONR_HSTPA1)             /*!< The stop condition of TIMER2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_EVENT            (TMR2_HCONR_HSTPA2)             /*!< The stop condition of TIMER2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Clear_Condition TIMER2 Hardware Clear Condition
 * @{
 */
#define TMR2_CLR_COND_INVALID           (0x0U)                          /*!< The clear condition of TIMER2 is INVALID. */
#define TMR2_CLR_COND_TRIGR             (TMR2_HCONR_HCLEA0)             /*!< The clear(clear CNTAR/CNTBR) condition of TIMER2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_TRIGF             (TMR2_HCONR_HCLEA1)             /*!< The clear(clear CNTAR/CNTBR) condition of TIMER2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_EVENT             (TMR2_HCONR_HCLEA2)             /*!< The clear(clear CNTAR/CNTBR) condition of TIMER2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Capture_Condition TIMER2 Hardware Capture Condition
 * @{
 */
#define TMR2_CAPT_COND_INVALID          (0x0U)                          /*!< The capture condition of TIMER2 is INVALID. */
#define TMR2_CAPT_COND_TRIGR            (TMR2_HCONR_HICPA0)             /*!< The capture condition of TIMER2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_TRIGF            (TMR2_HCONR_HICPA1)             /*!< The capture condition of TIMER2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_EVENT            (TMR2_HCONR_HICPA2)             /*!< The capture condition of TIMER2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_State_Flag TIMER2 State Flag
 * @{
 */
#define TMR2_FLAG_CMP                   (TMR2_STFLR_CMFA)               /*!< Counter match flag. */
#define TMR2_FLAG_OVF                   (TMR2_STFLR_OVFA)               /*!< Counter overflow flag. */
#define TMR2_FLAG_ALL                   (TMR2_FLAG_CMP | TMR2_FLAG_OVF)
/**
 * @}
 */

/**
 * @defgroup TMR2_Common_Trigger_Event_Command TIMER2 Common Trigger Event Command
 * @{
 */
#define TMR2_COM1_TRIG_DISABLE          (0x00UL)
#define TMR2_COM2_TRIG_DISABLE          (0x00UL)
#define TMR2_COM1_TRIG_ENABLE           (0x01UL << 30U)
#define TMR2_COM2_TRIG_ENABLE           (0x01UL << 31U)
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
 * @addtogroup TMR2_Global_Functions
 * @{
 */
     en_result_t TMR2_Init(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_init_t *pstcInit);
     en_result_t TMR2_StructInit(stc_tmr2_init_t *pstcInit);
            void TMR2_DeInit(M4_TMR2_TypeDef *TMR2x);

     en_result_t TMR2_PWM_Config(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_pwm_cfg_t *pstcCfg);
     en_result_t TMR2_PWM_StructInit(stc_tmr2_pwm_cfg_t *pstcCfg);
            void TMR2_PWM_Cmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState);

     en_result_t TMR2_SetTrigCond(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_trig_cond_t *pstcCond);
     en_result_t TMR2_TrigCondStructInit(stc_tmr2_trig_cond_t *pstcCond);
            void TMR2_SetTrigEvent(en_event_src_t enEvent);
            void TMR2_ComTrigCmd(uint32_t u32ComTrigEn);

            void TMR2_FilterConfig(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv);
            void TMR2_FilterCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState);

            void TMR2_IntCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, \
                             uint32_t u32IntType, en_functional_state_t enNewState);

     en_result_t TMR2_Start(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);
     en_result_t TMR2_Stop(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

en_flag_status_t TMR2_GetStatus(const M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag);
     en_result_t TMR2_ClrStatus(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag);

     en_result_t TMR2_SetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val);
        uint32_t TMR2_GetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

     en_result_t TMR2_SetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val);
        uint32_t TMR2_GetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

     en_result_t TMR2_SetFuncMode(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32FuncMode);

     en_result_t TMR2_SetClkSrc(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkSrc);
     en_result_t TMR2_SetClkDiv(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv);
     en_result_t TMR2_SetAsyncDelay(uint32_t u32AsyncClkFreq, uint32_t u32ClkDiv);

            void TMR2_TrigCondCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Cond, en_functional_state_t enNewState);

            void TMR2_PWM_SetStartPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);
            void TMR2_PWM_SetStopPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);
            void TMR2_PWM_SetCntMatchPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR2_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
