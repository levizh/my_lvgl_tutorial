/**
 *******************************************************************************
 * @file  hc32f4a0_timera.h
 * @brief This file contains all the functions prototypes of the TimerA driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-10       Wuze            First version
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
#ifndef __HC32F4A0_TMRA_H__
#define __HC32F4A0_TMRA_H__

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
 * @addtogroup DDL_TIMERA
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Types TimerA Global Types
 * @{
 */
/**
 * @brief TIMERA initialization structure.
 * @note 'u32ClkDiv' and 'u32CntMode' are valid only when the clock source is PCLK1.
 */
typedef struct
{
    uint32_t u32ClkSrc;                     /*!< Specify the counting clock source of TIMERA.
                                                 This parameter can be a value of @ref TMRA_Clock_Source */
    uint32_t u32ClkDiv;                     /*!< Specify the division of the clock source.
                                                 This parameter can be a value of @ref TMRA_Clock_Source_Division */
    uint32_t u32CntDir;                     /*!< Specify the direction of counting.
                                                 This parameter can be a value of @ref TMRA_Count_Direction */
    uint32_t u32CntMode;                    /*!< Specify the mode of counting.
                                                 This parameter can be a value of @ref TMRA_Count_Mode */
    uint32_t u32CntOvfOp;                   /*!< Specify the operation when counting overflow/underflow.
                                                 This parameter can be a value of @ref TMRA_Count_Overflow_Operation */
    uint32_t u32PeriodRefVal;               /*!< Specify the period reference value. */
    uint32_t u32CntInitVal;                 /*!< Specify the initial value of the counter. */
} stc_tmra_init_t;

/**
 * @brief TIMERA PWM configuration structure.
 */
typedef struct
{
    uint32_t u32StartPolarity;              /*!< Specify the polarity when the specified TIMERA channel start counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Start_Polarity */
    uint32_t u32StopPolarity;               /*!< Specify the polarity when the specified TIMERA channel stop counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Stop_Polarity */
    uint32_t u32CMPolarity;                 /*!< Specify the polarity when the specified TIMERA channel counting matches the comparison reference register.
                                                 This parameter can be a value of @ref TMRA_PWM_Count_Match_Polarity */
    uint32_t u32PMPolarity;                 /*!< Specify the polarity when the specified TIMERA channel counting matches the period reference register.
                                                 This parameter can be a value of @ref TMRA_PWM_Period_Match_Polarity */
    uint32_t u32ForcePolarity;              /*!< Specify the polarity when the specified TIMERA channel at the beginning of the next cycle. 
                                                 This parameter can be a value of @ref TMRA_PWM_Force_Polarity */
} stc_tmra_pwm_cfg_t;

/**
 * @brief TIMERA hardware trigger condition configuration structure.
 */
typedef struct
{
    uint32_t u32StartCond;                  /*!< Specify the condition to start the specified TIMERA unit.
                                                 This parameter can be a value of @ref TMRA_Hardware_Start_Condition */
    uint32_t u32StopCond;                   /*!< Specify the condition to stop the specified TIMERA unit.
                                                 This parameter can be a value of @ref TMRA_Hardware_Stop_Condition */
    uint32_t u32ClrCond;                    /*!< Specify the condition to clear the specified TIMERA unit's count register.
                                                 This parameter can be a value of @ref TMRA_Hardware_Clear_Condition */
} stc_tmra_trig_cond_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Macros TimerA Global Macros
 * @{
 */

/**
 * @defgroup TMRA_Channel TIMERA Channel
 * @{
 */
#define TMRA_CH_1                           (0U)                        /*!< Channel 1 of TIMERA. */
#define TMRA_CH_2                           (1U)                        /*!< Channel 2 of TIMERA. */
#define TMRA_CH_3                           (2U)                        /*!< Channel 3 of TIMERA. */
#define TMRA_CH_4                           (3U)                        /*!< Channel 4 of TIMERA. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Input_Pin TIMERA Input Pin
 * @{
 */
#define TMRA_PIN_TRIG                       (0U)                        /*!< Pin TIMA_<t>_TRIG. */
#define TMRA_PIN_CLKA                       (1U)                        /*!< Pin TIMA_<t>_PWM1/TIMA_<t>_CLKA. */
#define TMRA_PIN_CLKB                       (2U)                        /*!< Pin TIMA_<t>_PWM2/TIMA_<t>_CLKB. */
#define TMRA_PIN_PWM1                       (3U)                        /*!< Pin TIMA_<t>_PWM1. */
#define TMRA_PIN_PWM2                       (4U)                        /*!< Pin TIMA_<t>_PWM2. */
#define TMRA_PIN_PWM3                       (5U)                        /*!< Pin TIMA_<t>_PWM3. */
#define TMRA_PIN_PWM4                       (6U)                        /*!< Pin TIMA_<t>_PWM4. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Direction TIMERA Counting Direction
 * @{
 */
#define TMRA_DIR_DOWN                       (0x0U)                      /*!< TIMERA count goes down. */
#define TMRA_DIR_UP                         (TMRA_BCSTR_DIR)            /*!< TIMERA count goes up. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Mode TIMERA Counting Mode
 * @{
 */
#define TMRA_MODE_SAWTOOTH                  (0x0U)                      /*!< Count mode is sawtooth wave. */
#define TMRA_MODE_TRIANGLE                  (TMRA_BCSTR_MODE)           /*!< Count mode is triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Clock_Source TIMERA Counting Clock Source
 * @note If another clock is selected, PCLK1 is automatically disabled.
 * @note Symmetric units: uint 1 and 2; uint 3 and 4; ... ; uint 11 and 12.
 * @{
 */
#define TMRA_CLK_PCLK1                      (0x0U)                      /*!< PCLK1. */
#define TMRA_CLK_CLKAL_CLKBR                (TMRA_HCUPR_HCUP0)          /*!< When CLKA is low, a rising edge is sampled on CLKB. */
#define TMRA_CLK_CLKAL_CLKBF                (TMRA_HCUPR_HCUP1)          /*!< When CLKA is low, a falling edge is sampled on CLKB. */
#define TMRA_CLK_CLKAH_CLKBR                (TMRA_HCUPR_HCUP2)          /*!< When CLKA is high, a rising edge is sampled on CLKB. */
#define TMRA_CLK_CLKAH_CLKBF                (TMRA_HCUPR_HCUP3)          /*!< When CLKA is high, a falling edge is sampled on CLKB. */
#define TMRA_CLK_CLKBL_CLKAR                (TMRA_HCUPR_HCUP4)          /*!< When CLKB is low, a rising edge is sampled on CLKA. */
#define TMRA_CLK_CLKBL_CLKAF                (TMRA_HCUPR_HCUP5)          /*!< When CLKB is low, a falling edge is sampled on CLKA. */
#define TMRA_CLK_CLKBH_CLKAR                (TMRA_HCUPR_HCUP6)          /*!< When CLKB is high, a rising edge is sampled on CLKA. */
#define TMRA_CLK_CLKBH_CLKAF                (TMRA_HCUPR_HCUP7)          /*!< When CLKB is high, a falling edge is sampled on CLKA. */
#define TMRA_CLK_TRIGR                      (TMRA_HCUPR_HCUP8)          /*!< Rising edge of TRIG. */
#define TMRA_CLK_TRIGF                      (TMRA_HCUPR_HCUP9)          /*!< Falling edge of TRIG. */
#define TMRA_CLK_EVENT                      (TMRA_HCUPR_HCUP10)         /*!< Event of other peripheral. */
#define TMRA_CLK_SYM_OVF                    (TMRA_HCUPR_HCUP11)         /*!< Overflow of the symmetric unit. */
#define TMRA_CLK_SYM_UNFL                   (TMRA_HCUPR_HCUP12)         /*!< Underflow of the symmetric unit. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Clock_Source_Division TIMERA Clock Source Division
 * @note Clock division is only valid for PCKL1.
 * @{
 */
#define TMRA_CLK_DIV_1                      (0x0U)                      /*!< The clock source of TIMERA is PCLK1. */
#define TMRA_CLK_DIV_2                      (TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TIMERA is PCLK1 / 2. */
#define TMRA_CLK_DIV_4                      (TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TIMERA is PCLK1 / 4. */
#define TMRA_CLK_DIV_8                      (TMRA_BCSTR_CKDIV_1 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TIMERA is PCLK1 / 8. */
#define TMRA_CLK_DIV_16                     (TMRA_BCSTR_CKDIV_2)        /*!< The clock source of TIMERA is PCLK1 / 16. */
#define TMRA_CLK_DIV_32                     (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TIMERA is PCLK1 / 32. */
#define TMRA_CLK_DIV_64                     (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TIMERA is PCLK1 / 64. */
#define TMRA_CLK_DIV_128                    (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_1 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TIMERA is PCLK1 / 128. */
#define TMRA_CLK_DIV_256                    (TMRA_BCSTR_CKDIV_3)        /*!< The clock source of TIMERA is PCLK1 / 256. */
#define TMRA_CLK_DIV_512                    (TMRA_BCSTR_CKDIV_3 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TIMERA is PCLK1 / 512. */
#define TMRA_CLK_DIV_1024                   (TMRA_BCSTR_CKDIV_3 | \
                                             TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TIMERA is PCLK1 / 1024. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Overflow_Operation TIMERA Count Overflow Operation
 * @{
 */
#define TMRA_OVF_KEEP_CNT                   (0x0U)                      /*!< When counting overflow(or underflow), counting keep going. */
#define TMRA_OVF_STOP                       (TMRA_BCSTR_OVSTP)          /*!< When counting overflow(or underflow), counting stop. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Interrupt_Type TIMERA Interrupt Type
 * @{
 */
#define TMRA_INT_OVF                        (1UL << 12U)                /*!< The interrupt of counting overflow. */
#define TMRA_INT_UNF                        (1UL << 13U)                /*!< The interrupt of counting underflow. */
#define TMRA_INT_MATCH_1                    (1UL << 16U)                /*!< The interrupt of counting match of channel 1. */
#define TMRA_INT_MATCH_2                    (1UL << 17U)                /*!< The interrupt of counting match of channel 2. */
#define TMRA_INT_MATCH_3                    (1UL << 18U)                /*!< The interrupt of counting match of channel 3. */
#define TMRA_INT_MATCH_4                    (1UL << 19U)                /*!< The interrupt of counting match of channel 4. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Type TIMERA Event Type
 * @{
 */
#define TMRA_EVENT_MATCH_1                  (TMRA_ECONR_ITEN1)          /*!< The event of counting match of channel 1. */
#define TMRA_EVENT_MATCH_2                  (TMRA_ECONR_ITEN2)          /*!< The event of counting match of channel 2. */
#define TMRA_EVENT_MATCH_3                  (TMRA_ECONR_ITEN3)          /*!< The event of counting match of channel 3. */
#define TMRA_EVENT_MATCH_4                  (TMRA_ECONR_ITEN4)          /*!< The event of counting match of channel 4. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Status_Flag TIMERA Status Flag
 * @{
 */
#define TMRA_FLAG_OVF                       (1UL << 14U)                /*!< The flag of counting overflow. */
#define TMRA_FLAG_UNF                       (1UL << 15U)                /*!< The flag of counting underflow. */
#define TMRA_FLAG_MATCH_1                   (1UL << 16U)                /*!< The flag of counting match of channel 1. */
#define TMRA_FLAG_MATCH_2                   (1UL << 17U)                /*!< The flag of counting match of channel 2. */
#define TMRA_FLAG_MATCH_3                   (1UL << 18U)                /*!< The flag of counting match of channel 3. */
#define TMRA_FLAG_MATCH_4                   (1UL << 19U)                /*!< The flag of counting match of channel 4. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Cmp_Ref_Value_Cache_Position TIMERA Comparison Reference Value Cache Position
 * @{
 */
#define TMRA_CACHE_POS_OVF_CLR              (0x0U)                      /*!< This configuration value applies to non-triangular wave counting mode. \
                                                                             When counting overflow or underflow or counting register was caleared, \
                                                                             transfer CMPARm(m=2,4) to CMPARn(n=1,3). */
#define TMRA_CACHE_POS_TW_PEAK              (TMRA_BCONR_BSE0)           /*!< In triangle wave count mode, when count reached peak position, \
                                                                             transfer CMPARm(m=2,4) to CMPARn(n=1,3). */
#define TMRA_CACHE_POS_TW_VALLEY            (TMRA_BCONR_BSE1)           /*!< In triangle wave count mode, when count reached valley position, \
                                                                             transfer CMPARm(m=2,4) to CMPARn(n=1,3). */
/**
 * @}
 */

/**
 * @defgroup TMRA_Function_Mode TIMERA Function Mode
 * @{
 */
#define TMRA_FUNC_COMPARE                   (0x0U)                      /*!< The function mode of TIMERA is comparison ouput. */
#define TMRA_FUNC_CAPTURE                   (TMRA_CCONR_CAPMD)          /*!< The function mode of TIMERA is capture the input. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Channel_Capture_Condition TIMERA Capturing Condition Of Channel
 * @{
 */
#define TMRA_CAPT_COND_INVALID              (0x0U)                     /*!< The condition of capture is INVALID. */
#define TMRA_CAPT_COND_PWMR                 (TMRA_CCONR_HICP0)         /*!< The condition of capture is a rising edge is sampled on PWM(pin). */
#define TMRA_CAPT_COND_PWMF                 (TMRA_CCONR_HICP1)         /*!< The condition of capture is a falling edge is sampled on PWM(pin). */
#define TMRA_CAPT_COND_EVENT                (TMRA_CCONR_HICP2)         /*!< The condition of capture is the specified event occurred. */
#define TMRA_CAPT_COND_TRIGR                (TMRA_CCONR_HICP3)         /*!< The condition of capture is a rising edge is sampled on TRIG. */
#define TMRA_CAPT_COND_TRIGF                (TMRA_CCONR_HICP4)         /*!< The condition of capture is a falling edge is sampled on TRIG. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Clock_Division TIMERA Filter Clock Division
 * @{
 */
#define TMRA_FILTER_CLK_DIV_1               (0x0U)                      /*!< The filter clock is PCLK / 1. */
#define TMRA_FILTER_CLK_DIV_4               (0x1U)                      /*!< The filter clock is PCLK / 4. */
#define TMRA_FILTER_CLK_DIV_16              (0x2U)                      /*!< The filter clock is PCLK / 16. */
#define TMRA_FILTER_CLK_DIV_64              (0x3U)                      /*!< The filter clock is PCLK / 64. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_State TIMERA PWM State
 * @{
 */
#define TMRA_PWM_START                      (0U)                        /*!< The state is counting start. */
#define TMRA_PWM_STOP                       (1U)                        /*!< The state is counting stop. */
#define TMRA_PWM_CM                         (2U)                        /*!< The state is counter is equal to the comparison reference value. */
#define TMRA_PWM_PM                         (3U)                        /*!< The state is counter is equal to the period reference value. */
#define TMRA_PWM_FORCE                      (4U)                        /*!< The state is counter is the beginning of the next cycle. \
                                                                           The beginning of the next cycle: overflow position or underflow position \
                                                                           of sawtooth wave; valley position of triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Output_Polarity TIMERA PWM Output Polarity
 * @{
 */
#define TMRA_PWM_OUT_LOW                    (0U)                        /*!< The polarity of PWM output is low. */
#define TMRA_PWM_OUT_HI                     (1U)                        /*!< The polarity of PWM output is high. */
#define TMRA_PWM_OUT_KEEP                   (2U)                        /*!< The polarity of PWM output keeps the current polarity. */
#define TMRA_PWM_OUT_REVERSE                (3U)                        /*!< The polarity of PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Out_Command TIMERA PWM Out Command
 * @{
 */
#define TMRA_PWM_DISABLE                    (0x0U)                      /*!< Disable PWM output. */
#define TMRA_PWM_ENABLE                     (TMRA_PCONR_OUTEN)          /*!< Enable PWM output. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Start_Polarity TIMERA PWM Start Polarity
 * @note The 'START' in the following macros is the state 'counting start'.
 * @{
 */
#define TMRA_PWM_START_LOW                  (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_START_HI                   (TMRA_PCONR_STAC_0)         /*!< PWM output high. */
#define TMRA_PWM_START_KEEP                 (TMRA_PCONR_STAC_1)         /*!< PWM output keeps the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Stop_Polarity TIMERA PWM Stop Polarity
 * @note The 'STOP' in the following macros is the state 'counting stop'.
 * @{
 */
#define TMRA_PWM_STOP_LOW                   (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_STOP_HI                    (TMRA_PCONR_STPC_0)         /*!< PWM output high. */
#define TMRA_PWM_STOP_KEEP                  (TMRA_PCONR_STPC_1)         /*!< PWM output keeps the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Count_Match_Polarity TIMERA PWM Count Match Polarity
 * @note The 'CM' in the following macros is the state 'the counter is equal to the comparison reference value'.
 * @{
 */
#define TMRA_PWM_CM_LOW                     (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_CM_HI                      (TMRA_PCONR_CMPC_0)         /*!< PWM output high. */
#define TMRA_PWM_CM_KEEP                    (TMRA_PCONR_CMPC_1)         /*!< PWM output keeps the current polarity. */
#define TMRA_PWM_CM_REVERSE                 (TMRA_PCONR_CMPC_1 | \
                                             TMRA_PCONR_CMPC_0)         /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Period_Match_Polarity TIMERA PWM Period Match Polarity
 * @note The 'PM' in the following macros is the state 'the counter is equal to the period reference value'.
 * @{
 */
#define TMRA_PWM_PM_LOW                     (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_PM_HI                      (TMRA_PCONR_PERC_0)         /*!< PWM output high. */
#define TMRA_PWM_PM_KEEP                    (TMRA_PCONR_PERC_1)         /*!< PWM output keeps the current polarity. */
#define TMRA_PWM_PM_REVERSE                 (TMRA_PCONR_PERC_1 | \
                                             TMRA_PCONR_PERC_0)         /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Force_Polarity TIMERA PWM Force Polarity
 * @{
 */
#define TMRA_PWM_FORCE_LOW                  (TMRA_PCONR_FORC_1)         /*!< Force the PWM output low at the beginning of the next cycle. \
                                                                             The beginning of the next cycle: overflow position or underflow position \
                                                                             of sawtooth wave; valley position of triangle wave. */
#define TMRA_PWM_FORCE_HI                   (TMRA_PCONR_FORC_1 | \
                                             TMRA_PCONR_FORC_0)         /*!< Force the PWM output high at the beginning of the next cycle. \
                                                                             The beginning of the next cycle: overflow position or underflow position \
                                                                             of sawtooth wave; valley position of triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Start_Condition TIMERA Hardware Start Condition
 * @{
 */
#define TMRA_START_COND_INVALID             (0x0U)                  /*!< The condition of start is INVALID. */
#define TMRA_START_COND_TRIGR               (TMRA_HCONR_HSTA0)      /*!< 1. Sync start is invalid: The condition is that a rising edge is sampled on TRIG of the current TIMERA unit. \
                                                                         2. Sync start is valid: The condition is that a rising edge is sampled on TRIG of the symmetric TIMERA unit. */
#define TMRA_START_COND_TRIGF               (TMRA_HCONR_HSTA1)      /*!< 1. Sync start is invalid: The condition is that a falling edge is sampled on TRIG of the current TIMERA unit. \
                                                                         2. Sync start is valid: The condition is that a falling edge is sampled on TRIG of the symmetric TIMERA unit. */
#define TMRA_START_COND_EVENT               (TMRA_HCONR_HSTA2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Stop_Condition TIMERA Hardware Stop Condition
 * @{
 */
#define TMRA_STOP_COND_INVALID              (0x0U)                  /*!< The condition of stop is INVALID. */
#define TMRA_STOP_COND_TRIGR                (TMRA_HCONR_HSTP0)      /*!< The condition is that a rising edge is sampled on pin TRIG of the current TIMERA unit. */
#define TMRA_STOP_COND_TRIGF                (TMRA_HCONR_HSTP1)      /*!< The condition is that a falling edge is sampled on pin TRIG of the current TIMERA unit. */
#define TMRA_STOP_COND_EVENT                (TMRA_HCONR_HSTP2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Clear_Condition TIMERA Hardware Clear Condition
 * @note Symmetric units: uint 1 and 2; uint 3 and 4; ... ; uint 11 and 12.
 * @{
 */
#define TMRA_CLR_COND_INVALID               (0x0U)                  /*!< The condition of clear is INVALID. */
#define TMRA_CLR_COND_TRIGR                 (TMRA_HCONR_HCLE0)      /*!< The condition is that a rising edge is sampled on TRIG of the current TIMERA unit. */
#define TMRA_CLR_COND_TRIGF                 (TMRA_HCONR_HCLE1)      /*!< The condition is that a falling edge is sampled on TRIG of the current TIMERA unit. */
#define TMRA_CLR_COND_EVENT                 (TMRA_HCONR_HCLE2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_CLR_COND_SYM_TRIGR             (TMRA_HCONR_HCLE3)      /*!< The condition is that a rising edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_SYM_TRIGF             (TMRA_HCONR_HCLE4)      /*!< The condition is that a falling edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_PWM3R                 (TMRA_HCONR_HCLE5)      /*!< The condition is that a rising edge is sampled on PWM3 of the current TIMERA unit. */
#define TMRA_CLR_COND_PWM3F                 (TMRA_HCONR_HCLE6)      /*!< The condition is that a falling edge is sampled on PWM3 of the current TIMERA unit. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Usage TIMERA Event Usage
 * @{
 */
#define TMRA_EVENT_USAGE_CNT                (0U)                    /*!< The specified event is used for counting. */
#define TMRA_EVENT_USAGE_CAPT               (1U)                    /*!< The specified event is used for capturing. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Common_Trigger_Event_Command TIMERA Common Trigger Event Command
 * @{
 */
#define TMRA_COM1_TRIG_DISABLE              ((uint32_t)0x00UL)
#define TMRA_COM2_TRIG_DISABLE              ((uint32_t)0x00UL)
#define TMRA_COM1_TRIG_ENABLE               ((uint32_t)(0x01UL << 30U))
#define TMRA_COM2_TRIG_ENABLE               ((uint32_t)(0x01UL << 31U))
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
 * @addtogroup TMRA_Global_Functions
 * @{
 */
     en_result_t TMRA_Init(M4_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcInit);
     en_result_t TMRA_StructInit(stc_tmra_init_t *pstcInit);
     en_result_t TMRA_DeInit(M4_TMRA_TypeDef *TMRAx);

     en_result_t TMRA_SetCntVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val);
        uint32_t TMRA_GetCntVal(const M4_TMRA_TypeDef *TMRAx);
     en_result_t TMRA_SetPeriodRefVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val);
        uint32_t TMRA_GetPeriodRefVal(const M4_TMRA_TypeDef *TMRAx);
     en_result_t TMRA_SetCmpRefVal(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Val);
        uint32_t TMRA_GetCmpRefVal(const M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh);

     en_result_t TMRA_PWM_Config(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, const stc_tmra_pwm_cfg_t *pstcCfg);
     en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_cfg_t *pstcCfg);
     en_result_t TMRA_PWM_Cmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState);

     en_result_t TMRA_FilterConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, uint32_t u32ClkDiv);
     en_result_t TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, en_functional_state_t enNewState);

     en_result_t TMRA_SetCaptCond(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Cond);
     en_result_t TMRA_SetTrigCond(M4_TMRA_TypeDef *TMRAx, const stc_tmra_trig_cond_t *pstcCfg);
     en_result_t TMRA_TrigCondStructInit(stc_tmra_trig_cond_t *pstcCfg);
     en_result_t TMRA_SetCntEvent(M4_TMRA_TypeDef *TMRAx, en_event_src_t enEvent);
     en_result_t TMRA_SetCaptEvent(M4_TMRA_TypeDef *TMRAx, en_event_src_t enEvent);

     en_result_t TMRA_SetTrigEvent(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, en_event_src_t enEvent);
     en_result_t TMRA_ComTrigCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, uint32_t u32ComTrigEn);

     en_result_t TMRA_CmpRefCacheConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CachePosition);
     en_result_t TMRA_CmpRefCacheCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState);

     en_result_t TMRA_SetOvfOperation(M4_TMRA_TypeDef *TMRAx, uint32_t u32OvfOp);
     en_result_t TMRA_SyncStartCmd(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);

     en_result_t TMRA_IntCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState);
     en_result_t TMRA_EventCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32EvtType, en_functional_state_t enNewState);

en_flag_status_t TMRA_GetStatus(const M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag);
     en_result_t TMRA_ClrStatus(M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag);

     en_result_t TMRA_Start(M4_TMRA_TypeDef *TMRAx);
     en_result_t TMRA_Stop(M4_TMRA_TypeDef *TMRAx);

     en_result_t TMRA_SetCntDir(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntDir);
     en_result_t TMRA_SetCntMode(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntMode);
     en_result_t TMRA_SetClkSrcDiv(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkDiv);

//TODO: TMRA_FilterCmd cmd function has a parameter 'u32ClkDiv'
/*
     en_result_t TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, \
                                uint32_t u32ClkDiv, en_functional_state_t enNewState);
*/
     en_result_t TMRA_SetFuncMode(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32FuncMode);

     en_result_t TMRA_PWM_SetOutPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, \
                                         uint8_t u8PWMState, uint32_t u32Polarity);

     en_result_t TMRA_CaptCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CaptCond, en_functional_state_t enNewState);
     en_result_t TMRA_TrigStartCondCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32StartCond, en_functional_state_t enNewState);
     en_result_t TMRA_TrigStopCondCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32StopCond, en_functional_state_t enNewState);
     en_result_t TMRA_TrigClrCondCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClrCond, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_TMRA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMRA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
