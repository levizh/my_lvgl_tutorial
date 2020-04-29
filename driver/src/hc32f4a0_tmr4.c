/**
 *******************************************************************************
 * @file  hc32f4a0_tmr4.c
 * @brief This file provides firmware functions to manage the TIMER4
 *        (TIMER4).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-17       Hongjh          First version
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
#include "hc32f4a0_tmr4.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TIMER4 TIMER4
 * @brief TIMER4 Driver Library
 * @{
 */

#if (DDL_TMR4_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TIMER4_Local_Macros TIMER4 Local Macros
 * @{
 */

/**
 * @defgroup TIMER4_Check_Parameters_Validity TIMER4 Check Parameters Validity
 * @{
 */

#define IS_VALID_TMR4_INSTANCE(x)                                              \
(   (M4_TMR4_1 == (x))                          ||                             \
    (M4_TMR4_2 == (x))                          ||                             \
    (M4_TMR4_3 == (x)))

#define IS_VALID_TMR4_CNT_CLK_DIV(x)                                           \
(   (TMR4_CNT_CLK_DIV1 == (x))                  ||                             \
    (TMR4_CNT_CLK_DIV2 == (x))                  ||                             \
    (TMR4_CNT_CLK_DIV4 == (x))                  ||                             \
    (TMR4_CNT_CLK_DIV8 == (x))                  ||                             \
    (TMR4_CNT_CLK_DIV16 == (x))                 ||                             \
    (TMR4_CNT_CLK_DIV32 == (x))                 ||                             \
    (TMR4_CNT_CLK_DIV64 == (x))                 ||                             \
    (TMR4_CNT_CLK_DIV128 == (x))                ||                             \
    (TMR4_CNT_CLK_DIV256 == (x))                ||                             \
    (TMR4_CNT_CLK_DIV512 == (x))                ||                             \
    (TMR4_CNT_CLK_DIV1024 == (x)))

#define IS_VALID_TMR4_CNT_MODE(x)                                              \
(   (TMR4_CNT_MODE_SAWTOOTH_WAVE == (x))        ||                             \
    (TMR4_CNT_MODE_TRIANGLE_WAVE == (x)))

#define IS_VALID_TMR4_CNT_BUF_STATE(x)                                         \
(   (TMR4_CNT_BUFFER_ENABLE == (x))             ||                             \
    (TMR4_CNT_BUFFER_DISABLE == (x)))

#define IS_VALID_TMR4_CNT_CLK_SRC(x)                                           \
(   (TMR4_CNT_PCLK == (x))                      ||                             \
    (TMR4_CNT_EXTCLK == (x)))

#define IS_VALID_TMR4_CNT_INT_MSK(x)                                           \
(   (TMR4_CNT_INT_MASK_0 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_1 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_2 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_3 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_4 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_5 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_6 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_7 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_8 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_9 == (x))                ||                             \
    (TMR4_CNT_INT_MASK_10 == (x))               ||                             \
    (TMR4_CNT_INT_MASK_11 == (x))               ||                             \
    (TMR4_CNT_INT_MASK_12 == (x))               ||                             \
    (TMR4_CNT_INT_MASK_13 == (x))               ||                             \
    (TMR4_CNT_INT_MASK_14 == (x))               ||                             \
    (TMR4_CNT_INT_MASK_15 == (x)))

#define IS_VALID_TMR4_CNT_INT(x)                                               \
(   (TMR4_CNT_INT_ZERO == (x))                  ||                             \
    (TMR4_CNT_INT_PEAK == (x)))

#define IS_VALID_TMR4_CNT_FLAG(x)                                              \
(   (TMR4_CNT_FLAG_ZERO == (x))                 ||                             \
    (TMR4_CNT_FLAG_PEAK == (x)))

#define IS_VALID_TMR4_OCO_CH(x)                                                \
(   (TMR4_OCO_UH == (x))                        ||                             \
    (TMR4_OCO_UL == (x))                        ||                             \
    (TMR4_OCO_VH == (x))                        ||                             \
    (TMR4_OCO_VL == (x))                        ||                             \
    (TMR4_OCO_WH == (x))                        ||                             \
    (TMR4_OCO_WL == (x)))

#define IS_VALID_TMR4_OCO_HIGH_CH(x)                                           \
(   (TMR4_OCO_UH == (x))                        ||                             \
    (TMR4_OCO_VH == (x))                        ||                             \
    (TMR4_OCO_WH == (x)))

#define IS_VALID_TMR4_OCO_LOW_CH(x)                                            \
(   (TMR4_OCO_UL == (x))                        ||                             \
    (TMR4_OCO_VL == (x))                        ||                             \
    (TMR4_OCO_WL == (x)))

#define IS_VALID_TMR4_OCO_STATE(x)                                             \
(   (TMR4_OCO_DISABLE == (x))                   ||                             \
    (TMR4_OCO_ENABLE == (x)))

#define IS_VALID_TMR4_OCO_EXTEND_MATCH(x)                                      \
(   (TMR4_OCO_EXTEND_MATCH_DISABLE == (x))      ||                         \
    (TMR4_OCO_EXTEND_MATCH_ENABLE == (x)))

#define IS_VALID_TMR4_OCO_OCCR_LINK_TRANSFER(x)                                \
(   (TMR4_OCO_OCCR_LINK_TRANSFER_DISABLE == (x))    ||                         \
    (TMR4_OCO_OCCR_LINK_TRANSFER_ENABLE == (x)))

#define IS_VALID_TMR4_OCO_OCCR_BUF_MODE(x)                                     \
(   (TMR4_OCO_OCCR_BUF_DISABLE == (x))          ||                             \
    (TMR4_OCO_OCCR_BUF_CNT_ZERO == (x))         ||                             \
    (TMR4_OCO_OCCR_BUF_CNT_PEAK == (x))         ||                             \
    (TMR4_OCO_OCCR_BUF_CNT_ZERO_OR_PEAK == (x)))

#define IS_VALID_TMR4_OCO_OCMR_LINK_TRANSFER(x)                                \
(   (TMR4_OCO_OCMR_LINK_TRANSFER_DISABLE == (x))    ||                         \
    (TMR4_OCO_OCMR_LINK_TRANSFER_ENABLE == (x)))

#define IS_VALID_TMR4_OCO_OCMR_BUF_MODE(x)                                     \
(   (TMR4_OCO_OCMR_BUF_DISABLE == (x))          ||                             \
    (TMR4_OCO_OCMR_BUF_CNT_ZERO == (x))         ||                             \
    (TMR4_OCO_OCMR_BUF_CNT_PEAK == (x))         ||                             \
    (TMR4_OCO_OCMR_BUF_CNT_ZERO_OR_PEAK == (x)))

#define IS_VALID_TMR4_OCO_PORT_INVALID_OP(x)                                   \
(   (TMR4_OCO_INVAILD_OP_LOW == (x))            ||                             \
    (TMR4_OCO_INVAILD_OP_HIGH == (x)))

#define IS_VALID_TMR4_OCO_OCF_STATE(x)                                         \
(   (TMR4_OCO_OCF_HOLD == (x))                  ||                             \
    (TMR4_OCO_OCF_SET == (x)))

#define IS_VALID_TMR4_OCO_OCF_STATE(x)                                         \
(   (TMR4_OCO_OCF_HOLD == (x))                  ||                             \
    (TMR4_OCO_OCF_SET == (x)))

#define IS_VALID_TMR4_OCO_OUTPUT_POLARITY(x)                                   \
(   (TMR4_OCO_OP_HOLD == (x))                   ||                             \
    (TMR4_OCO_OP_HIGH == (x))                   ||                             \
    (TMR4_OCO_OP_LOW == (x))                    ||                             \
    (TMR4_OCO_OP_INVERT == (x)))

#define IS_VALID_TMR4_OCO_INT(x)                (TMR4_OCO_INT_MATCH == (x))

#define IS_VALID_TMR4_OCO_FLAG(x)               (TMR4_OCO_FLAG_MATCH == (x))

#define IS_VALID_TMR4_PWM_CH(x)                                                \
(   (TMR4_PWM_U == (x))                         ||                             \
    (TMR4_PWM_V == (x))                         ||                             \
    (TMR4_PWM_W == (x)))

#define IS_VALID_TMR4_PWM_PORT(x)                                              \
(   (TMR4_PWM_PORT_OUH == (x))                  ||                             \
    (TMR4_PWM_PORT_OUL == (x))                  ||                             \
    (TMR4_PWM_PORT_OVH == (x))                  ||                             \
    (TMR4_PWM_PORT_OVL == (x))                  ||                             \
    (TMR4_PWM_PORT_OWH == (x))                  ||                             \
    (TMR4_PWM_PORT_OWL == (x)))

#define IS_VALID_TMR4_PWM_MODE(x)                                              \
(   (TMR4_PWM_THROUGH_MODE == (x))              ||                             \
    (TMR4_PWM_DEAD_TIMER_MODE == (x))           ||                             \
    (TMR4_PWM_DEAD_TIMER_FILTER_MODE == (x)))

#define IS_VALID_TMR4_PWM_TRANSFORM_OCO_POLARITY(x)                            \
(   (TMR4_PWM_OP_OXH_HOLD_OXL_HOLD == (x))      ||                             \
    (TMR4_PWM_OP_OXH_INVERT_OXL_HOLD == (x))    ||                             \
    (TMR4_PWM_OP_OXH_HOLD_OXL_INVERT == (x))    ||                             \
    (TMR4_PWM_OP_OXH_INVERT_OXL_INVERT == (x)))

#define IS_VALID_TMR4_PWM_CLK_DIV(x)                                           \
(   (TMR4_PWM_CLK_DIV1 == (x))                  ||                             \
    (TMR4_PWM_CLK_DIV2 == (x))                  ||                             \
    (TMR4_PWM_CLK_DIV4 == (x))                  ||                             \
    (TMR4_PWM_CLK_DIV8 == (x))                  ||                             \
    (TMR4_PWM_CLK_DIV16 == (x))                 ||                             \
    (TMR4_PWM_CLK_DIV32 == (x))                 ||                             \
    (TMR4_PWM_CLK_DIV64 == (x))                 ||                             \
    (TMR4_PWM_CLK_DIV128 == (x)))

#define IS_VALID_TMR4_PWM_EMB_PORT_OUTPUT_STATE(x)                             \
(   (TMR4_PWM_EMB_PORT_OUTPUT_NORMAL == (x))    ||                             \
    (TMR4_PWM_EMB_PORT_OUTPUT_HIZ == (x))       ||                             \
    (TMR4_PWM_EMB_PORT_OUTPUT_LOW == (x))       ||                             \
    (TMR4_PWM_EMB_PORT_OUTPUT_HIGH == (x)))

#define IS_VALID_TMR4_PWM_PORT_ENBIT_EFFECT(x)                                 \
(   (TMR4_PWM_PORT_ENBIT_EFFECT_IMMEDIATE == (x))   ||                         \
    (TMR4_PWM_PORT_ENBIT_EFFECT_CNTUVF == (x))      ||                         \
    (TMR4_PWM_PORT_ENBIT_EFFECT_CNTOVF == (x)))

#define IS_VALID_TMR4_PWM_PORT_MODE(x)                                         \
(   (TMR4_PWM_PORT_OUTPUT_OSxy == (x))          ||                             \
    (TMR4_PWM_PORT_OUTPUT_NORMAL == (x)))

#define IS_VALID_TMR4_SEVT_CH(x)                                               \
(   (TMR4_SEVT_UH == (x))                       ||                             \
    (TMR4_SEVT_UL == (x))                       ||                             \
    (TMR4_SEVT_VH == (x))                       ||                             \
    (TMR4_SEVT_VL == (x))                       ||                             \
    (TMR4_SEVT_WH == (x))                       ||                             \
    (TMR4_SEVT_WL == (x)))

#define IS_VALID_TMR4_SEVT_LINK_TRANSFER(x)                                    \
(   (TMR4_SEVT_LINK_TRANSFER_DISABLE == (x))    ||                             \
    (TMR4_SEVT_LINK_TRANSFER_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_DOWN_SEL(x)                                         \
(   (TMR4_SEVT_DOWN_DISABLE == (x))             ||                             \
    (TMR4_SEVT_DOWN_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_UP_SEL(x)                                           \
(   (TMR4_SEVT_UP_DISABLE == (x))               ||                             \
    (TMR4_SEVT_UP_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_PEAK_SEL(x)                                         \
(   (TMR4_SEVT_PEAK_DISABLE == (x))             ||                             \
    (TMR4_SEVT_PEAK_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_ZERO_SEL(x)                                         \
(   (TMR4_SEVT_ZERO_DISABLE == (x))             ||                             \
    (TMR4_SEVT_ZERO_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_ZERO_MATCH_MASK_SEL(x)                              \
(   (TMR4_SEVT_ZERO_MATCH_MASK_DISABLE == (x))  ||                             \
    (TMR4_SEVT_ZERO_MATCH_MASK_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_PEAK_MATCH_MASK_SEL(x)                              \
(   (TMR4_SEVT_PEAK_MATCH_MASK_DISABLE == (x))  ||                             \
    (TMR4_SEVT_PEAK_MATCH_MASK_ENABLE == (x)))

#define IS_VALID_TMR4_SEVT_OBJECT(x)                                           \
(   (TMR4_SEVT_DELAY_OCCRXH == (x))             ||                             \
    (TMR4_SEVT_DELAY_OCCRXL == (x)))

#define IS_VALID_TMR4_SEVT_MODE(x)                                             \
(   (TMR4_SEVT_MODE_DELAY_TRIGGER == (x))       ||                             \
    (TMR4_SEVT_MODE_COMPARE_TRIGGER == (x)))

#define IS_VALID_TMR4_SEVT_MASK(x)                                             \
(   (TMR4_SEVT_MASK_0 == (x))                   ||                             \
    (TMR4_SEVT_MASK_1 == (x))                   ||                             \
    (TMR4_SEVT_MASK_2 == (x))                   ||                             \
    (TMR4_SEVT_MASK_3 == (x))                   ||                             \
    (TMR4_SEVT_MASK_4 == (x))                   ||                             \
    (TMR4_SEVT_MASK_5 == (x))                   ||                             \
    (TMR4_SEVT_MASK_6 == (x))                   ||                             \
    (TMR4_SEVT_MASK_7 == (x))                   ||                             \
    (TMR4_SEVT_MASK_8 == (x))                   ||                             \
    (TMR4_SEVT_MASK_9 == (x))                   ||                             \
    (TMR4_SEVT_MASK_10 == (x))                  ||                             \
    (TMR4_SEVT_MASK_11 == (x))                  ||                             \
    (TMR4_SEVT_MASK_12 == (x))                  ||                             \
    (TMR4_SEVT_MASK_13 == (x))                  ||                             \
    (TMR4_SEVT_MASK_14 == (x))                  ||                             \
    (TMR4_SEVT_MASK_15 == (x)))

#define IS_VALID_TMR4_SEVT_OUTPUT_EVENT(x)                                     \
(   (TMR4_SEVT_OUTPUT_EVENT0 == (x))            ||                             \
    (TMR4_SEVT_OUTPUT_EVENT1 == (x))            ||                             \
    (TMR4_SEVT_OUTPUT_EVENT2 == (x))            ||                             \
    (TMR4_SEVT_OUTPUT_EVENT3 == (x))            ||                             \
    (TMR4_SEVT_OUTPUT_EVENT4 == (x))            ||                             \
    (TMR4_SEVT_OUTPUT_EVENT5 == (x)))

#define IS_VALID_TMR4_SEVT_BUF_MODE(x)                                         \
(   (TMR4_SEVT_BUF_DISABLE == (x))              ||                             \
    (TMR4_SEVT_BUF_CNT_ZERO == (x))             ||                             \
    (TMR4_SEVT_BUF_CNT_PEAK == (x))             ||                             \
    (TMR4_SEVT_BUF_CNT_ZERO_OR_PEAK == (x)))

#define IS_VALID_TMR4_SEVT_PORT_OUTPUT_SIGNAL(x)                               \
(   (TMR4_SEVT_PORT_OUTPUT_NONE == (x))             ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT0_SIGNAL == (x))    ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT1_SIGNAL == (x))    ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT2_SIGNAL == (x))    ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT3_SIGNAL == (x))    ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT4_SIGNAL == (x))    ||                         \
    (TMR4_SEVT_PORT_OUTPUT_EVENT5_SIGNAL == (x)))
/**
 * @}
 */

/**
 * @defgroup Get TIMER4 register address
 * @{
 */
#define REG_ADDR(__REG__)                   ((uint32_t)(&(__REG__)))
/**
 * @}
 */

/**
 * @defgroup Get register bit offset for TIMER4 OCO/PWM/SEVT channel
 * @{
 */
#define REG_xBIT_OFS(__CH__, __BITWIDTH__)  ((((__CH__) % 2UL) * (__BITWIDTH__)))
#define REG16_1BIT_OFS(__CH__)              ((uint16_t)REG_xBIT_OFS((__CH__), 1UL))
#define REG16_2BIT_OFS(__CH__)              ((uint16_t)REG_xBIT_OFS((__CH__), 2UL))
#define REG32_1BIT_OFS(__CH__)              ((uint32_t)REG_xBIT_OFS((__CH__), 1UL))
#define REG32_2BIT_OFS(__CH__)              ((uint32_t)REG_xBIT_OFS((__CH__), 2UL))
/**
 * @}
 */

/**
 * @defgroup TIMER4_OCO_Register TIMER4 OCO Register
 * @brief Get the specified OCO register address of the specified Timer4 unit
 * @note __CH__ value is TMR4_OCO_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCCRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->OCCRUH) + ((uint32_t)(__CH__))*4UL))
#define TMR4_OCMRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->OCMRHUH) + ((uint32_t)(__CH__))*4UL))
#define TMR4_OCERx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->OCERU) + (((uint32_t)(__CH__))/2UL)*4UL))
#define TMR4_OCSRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->OCSRU) + (((uint32_t)(__CH__))/2UL)*4UL))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCSR_Bit TMR4_OCSR Bit
 * @brief Get the specified TMR4_OCSR register bis value of the specified Timer4 Oco channel
 * @note __CH__ value is TMR4_OCO_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCSR_OCEx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_OCSR_OCEH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCSR_OCPx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_OCSR_OCPH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCSR_OCIEx_MASK(__CH__)        ((uint16_t)((uint16_t)TMR4_OCSR_OCIEH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCSR_OCFx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_OCSR_OCFH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCSR_MASK(__CH__)                                                 \
(   (uint16_t)((uint16_t)TMR4_OCSR_OCEH | (uint16_t)TMR4_OCSR_OCPH | (uint16_t)TMR4_OCSR_OCIEH | (uint16_t)TMR4_OCSR_OCFH) << REG16_1BIT_OFS(__CH__))
/**
 * @}
 */

/**
 * @defgroup TMR4_OCER_Bit TMR4_OCER Bit
 * @brief Get the specified TMR4_OCER register bis value of the specified Timer4 Oco channel
 * @note __CH__ value is TMR4_OCO_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_OCER_CxBUFEN_MASK(__CH__)      ((uint16_t)((uint16_t)TMR4_OCER_CHBUFEN << REG16_2BIT_OFS(__CH__)))
#define TMR4_OCER_MxBUFEN_MASK(__CH__)      ((uint16_t)((uint16_t)TMR4_OCER_MHBUFEN << REG16_2BIT_OFS(__CH__)))
#define TMR4_OCER_LMCx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_OCER_LMCH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCER_LMMx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_OCER_LMMH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCER_MCECx_MASK(__CH__)        ((uint16_t)((uint16_t)TMR4_OCER_MCECH << REG16_1BIT_OFS(__CH__)))
#define TMR4_OCER_MASK(__CH__)                                                 \
(   (uint16_t)(((uint16_t)TMR4_OCER_CHBUFEN | (uint16_t)TMR4_OCER_MHBUFEN) << REG16_2BIT_OFS(__CH__)) | \
    (uint16_t)(((uint16_t)TMR4_OCER_LMCH | (uint16_t)TMR4_OCER_LMMH | (uint16_t)TMR4_OCER_MCECH) << REG16_2BIT_OFS(__CH__)))
/**
 * @}
 */

/**
 * @defgroup TIMER4_PWM_Register TIMER4 PWM Register
 * @brief Get the specified PWM register address of the specified Timer4 unit
 * @note __CH__ value is TMR4_PWM_x (x=U/V/W)
 * @{
 */
#define TMR4_RCSRx(__TMR4x__)               ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->RCSR)))
#define TMR4_POCRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->POCRU) + ((uint32_t)(__CH__))*4UL))
#define TMR4_PDARx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->PDARU) + ((uint32_t)(__CH__))*8UL))
#define TMR4_PDBRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->PDBRU) + ((uint32_t)(__CH__))*8UL))
#define TMR4_PFSRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->PFSRU) + ((uint32_t)(__CH__))*8UL))
/**
 * @}
 */

/**
 * @defgroup TMR4_RCSR_Bit TMR4_RCSR Bit
 * @brief Get the specified TMR4_RCSR register bis value of the specified Timer4 PWM channel
 * @note __CH__ value is TMR4_PWM_x (x=U/V/W)
 * @{
 */
#define TMR4_RCSR_RTIDx_MASK(__CH__)        ((uint16_t)((uint16_t)TMR4_RCSR_RTIDU << (__CH__)))
#define TMR4_RCSR_RTIFx_MASK(__CH__)        ((uint16_t)((uint16_t)TMR4_RCSR_RTIFU << ((__CH__)*4U)))
#define TMR4_RCSR_RTICx_MASK(__CH__)        ((uint16_t)((uint16_t)TMR4_RCSR_RTICU << ((__CH__)*4U)))
#define TMR4_RCSR_RTEx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_RCSR_RTEU << ((__CH__)*4U)))
#define TMR4_RCSR_RTSx_MASK(__CH__)         ((uint16_t)((uint16_t)TMR4_RCSR_RTSU << ((__CH__)*4U)))
/**
 * @}
 */

/**
 * @defgroup TMR4_PSCR_Bit TMR4_PSCR Bit
 * @brief Get the specified TMR4_PSCR register bis value of the specified Timer4 PWM port channel
 * @note __CH__ value is TMR4_PWM_PORT_Oxy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_PSCR_OExy_MASK(__PORT__)       ((uint32_t)TMR4_PSCR_OEUH << (__PORT__))
#define TMR4_PSCR_OSxy_MASK(__PORT__)       ((uint32_t)TMR4_PSCR_OSUH << ((__PORT__) * 2UL))
/**
 * @}
 */

/**
 * @defgroup TIMER4_SEVT_Register TIMER4 SEVT Register
 * @brief Get the specified SEVT register address of the specified Timer4 unit
 * @note __CH__ value is TMR4_SEVT_xy (x=U/V/W, y=H/L)
 * @{
 */
#define TMR4_SCCRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->SCCRUH) + ((uint32_t)(__CH__))*4UL))
#define TMR4_SCSRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->SCSRUH) + ((uint32_t)(__CH__))*4UL))
#define TMR4_SCMRx(__TMR4x__, __CH__)       ((__IO uint16_t *)(REG_ADDR((__TMR4x__)->SCMRUH) + ((uint32_t)(__CH__))*4UL))
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
 * @defgroup TMR4_Global_Functions TIMER4 Global Functions
 * @{
 */

/**
 * @defgroup TMR4_CNT_Global_Functions TIMER4 Counter Global Functions
 * @{
 */

/**
 * @brief  Initialize Timer4 CNT.
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_tmr4_cnt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMR4_CNT_Init(M4_TMR4_TypeDef *TMR4x,
                                const stc_tmr4_cnt_init_t *pstcInit)
{
    uint16_t u16Val = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_CNT_BUF_STATE(pstcInit->u16BufState));
        DDL_ASSERT(IS_VALID_TMR4_CNT_MODE(pstcInit->u16CntMode));
        DDL_ASSERT(IS_VALID_TMR4_CNT_CLK_DIV(pstcInit->u16ClkDiv));
        DDL_ASSERT(IS_VALID_TMR4_CNT_CLK_SRC(pstcInit->u16ClkSrc));
        DDL_ASSERT(IS_VALID_TMR4_CNT_INT_MSK(pstcInit->u16ZeroIntMask));
        DDL_ASSERT(IS_VALID_TMR4_CNT_INT_MSK(pstcInit->u16PeakIntMask));

        /* Set default value */
        WRITE_REG16(TMR4x->CCSR, 0x0050U);
        WRITE_REG16(TMR4x->CVPR, 0x0000U);

        /* Set count clock div && cnt mode && buffer enable bit && 
           external clock enable bit && interrupt enable bit */
        u16Val = (pstcInit->u16ClkDiv  | \
                  pstcInit->u16ClkSrc  | \
                  pstcInit->u16CntMode | \
                  TMR4_CCSR_STOP       | \
                  pstcInit->u16BufState);
        WRITE_REG16(TMR4x->CCSR, u16Val);

        /* set interrupt mask times */
        u16Val = (((uint16_t)(pstcInit->u16ZeroIntMask << TMR4_CVPR_ZIM_POS)) | \
                  ((uint16_t)(pstcInit->u16PeakIntMask << TMR4_CVPR_PIM_POS)));
        WRITE_REG16(TMR4x->CVPR, u16Val);

        /* Set Timer4 cycle */
        WRITE_REG16(TMR4x->CPSR, pstcInit->u16CycleVal);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_cnt_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_tmr4_cnt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMR4_CNT_StructInit(stc_tmr4_cnt_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u16CycleVal = 0xFFFFU;
        pstcInit->u16CntMode = TMR4_CNT_MODE_SAWTOOTH_WAVE;
        pstcInit->u16ClkSrc = TMR4_CNT_PCLK;
        pstcInit->u16ClkDiv = TMR4_CNT_CLK_DIV1;
        pstcInit->u16ZeroIntMask = TMR4_CNT_INT_MASK_0;
        pstcInit->u16PeakIntMask = TMR4_CNT_INT_MASK_0;
        pstcInit->u16BufState = TMR4_CNT_BUFFER_DISABLE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize Timer4 count function
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @retval None
 */
void TMR4_CNT_DeInit(M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    /* Configures the registers to reset value. */
    WRITE_REG16(TMR4x->CCSR, 0x0050U);
    WRITE_REG16(TMR4x->CPSR, 0xFFFFU);
    WRITE_REG16(TMR4x->CVPR, 0x0000U);
}

/**
 * @brief Set Timer4 CNT clock source
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16ClkSrc               Timer4 CNT clock source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_PCLK:      Uses the internal clock (PCLK) as CNT's count clock
 *           @arg TMR4_CNT_EXTCLK:    Uses an external input clock (EXCK) as CNT's count clock
 * @retval None
 */
void TMR4_CNT_SetClock(M4_TMR4_TypeDef *TMR4x, uint16_t u16ClkSrc)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_CLK_SRC(u16ClkSrc));

    /* Set external clock enable bit */
    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_ECKEN, u16ClkSrc);
}

/**
 * @brief Get Timer4 CNT clock source
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_CNT_PCLK:      Uses the internal clock (PCLK) as CNT's count clock
 *           @arg TMR4_CNT_EXTCLK:    Uses an external input clock (EXCK) as CNT's count clock
 */
uint16_t TMR4_CNT_GetClock(const M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    /* Get external clock enable bit */
    return READ_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_ECKEN);
}

/**
 * @brief  Set Timer4 counter clock division
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16Div                  Timer4 clock division
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_CLK_DIV1:    HCLK
 *           @arg TMR4_CNT_CLK_DIV2:    HCLK/2
 *           @arg TMR4_CNT_CLK_DIV4:    HCLK/4
 *           @arg TMR4_CNT_CLK_DIV8:    HCLK/8
 *           @arg TMR4_CNT_CLK_DIV16:   HCLK/16
 *           @arg TMR4_CNT_CLK_DIV32:   HCLK/32
 *           @arg TMR4_CNT_CLK_DIV64:   HCLK/64
 *           @arg TMR4_CNT_CLK_DIV128:  HCLK/128
 *           @arg TMR4_CNT_CLK_DIV256:  HCLK/256
 *           @arg TMR4_CNT_CLK_DIV512:  HCLK/512
 *           @arg TMR4_CNT_CLK_DIV1024: HCLK/1024
 * @retval None
 */
void TMR4_CNT_SetClkDiv(M4_TMR4_TypeDef *TMR4x, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_CLK_DIV(u16Div));

    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_CKDIV, u16Div);
}

/**
 * @brief  Get Timer4 counter clock division
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_CNT_CLK_DIV1:    HCLK
 *           @arg TMR4_CNT_CLK_DIV2:    HCLK/2
 *           @arg TMR4_CNT_CLK_DIV4:    HCLK/4
 *           @arg TMR4_CNT_CLK_DIV8:    HCLK/8
 *           @arg TMR4_CNT_CLK_DIV16:   HCLK/16
 *           @arg TMR4_CNT_CLK_DIV32:   HCLK/32
 *           @arg TMR4_CNT_CLK_DIV64:   HCLK/64
 *           @arg TMR4_CNT_CLK_DIV128:  HCLK/128
 *           @arg TMR4_CNT_CLK_DIV256:  HCLK/256
 *           @arg TMR4_CNT_CLK_DIV512:  HCLK/512
 *           @arg TMR4_CNT_CLK_DIV1024: HCLK/1024
 */
uint16_t TMR4_CNT_GetClkDiv(const M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    return READ_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_CKDIV);
}

/**
 * @brief Set Timer4 CNT mode
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16Mode                 Timer4 CNT mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_MODE_SAWTOOTH_WAVE: Timer4 count mode:sawtooth wave
 *           @arg TMR4_CNT_MODE_TRIANGLE_WAVE: Timer4 count mode:triangular wave
 * @retval None
 */
void TMR4_CNT_SetMode(M4_TMR4_TypeDef *TMR4x, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_MODE(u16Mode));

    /* Set external clock enable bit */
    MODIFY_REG16(TMR4x->CCSR, TMR4_CCSR_MODE, u16Mode);
}

/**
 * @brief Get Timer4 CNT mode
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_CNT_MODE_SAWTOOTH_WAVE: Timer4 count mode:sawtooth wave
 *           @arg TMR4_CNT_MODE_TRIANGLE_WAVE: Timer4 count mode:triangular wave
 */
uint16_t TMR4_CNT_GetMode(const M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    /* Get external clock enable bit */
    return READ_REG16_BIT(TMR4x->CCSR, TMR4_CCSR_MODE);
}

/**
 * @brief  Get Timer4 CNT interrupt flag
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16Flag                 Timer4 flag
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_FLAG_PEAK: Overflow interrupt
 *           @arg TMR4_CNT_FLAG_ZERO: Underflow interrupt
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t TMR4_CNT_GetFlag(const M4_TMR4_TypeDef *TMR4x, uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    return READ_REG16_BIT(TMR4x->CCSR, u16Flag) ? Set : Reset;
}

/**
 * @brief  Clear Timer4 CNT interrupt flag
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16Flag                 Timer4 flag
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_FLAG_PEAK:   Overflow interrupt
 *           @arg TMR4_CNT_FLAG_ZERO:   Underflow interrupt
 * @retval None
 */
void TMR4_CNT_ClearFlag(M4_TMR4_TypeDef *TMR4x, uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    CLEAR_REG16_BIT(TMR4x->CCSR, u16Flag);
}

/**
 * @brief  Enable or disable specified Timer4 counter interrupt
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16IntSource            Timer4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:    Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:    Underflow interrupt
 * @param  [in] enNewState              The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_CNT_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint16_t u16IntSource,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_TMR4_CNT_INT(u16IntSource));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMR4x->CCSR, u16IntSource);
    }
    else
    {
        CLEAR_REG16_BIT(TMR4x->CCSR, u16IntSource);
    }
}

/**
 * @brief  Set Timer4 CNT interrupt mask times
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16IntSource            Timer4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:    Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:    Underflow interrupt
 * @param [in] u16MaskTimes             Timer4 CNT interrupt mask times
 *           @arg TMR4_CNT_INT_MASK_0:  CNT interrupt flag is always set(not masked) for every CNT count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK_1:  CNT interrupt flag is set once for 2 every CNT counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK_2:  CNT interrupt flag is set once for 3 every CNT counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK_3:  CNT interrupt flag is set once for 4 every CNT counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK_4:  CNT interrupt flag is set once for 5 every CNT counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK_5:  CNT interrupt flag is set once for 6 every CNT counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK_6:  CNT interrupt flag is set once for 7 every CNT counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK_7:  CNT interrupt flag is set once for 8 every CNT counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK_8:  CNT interrupt flag is set once for 9 every CNT counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK_9:  CNT interrupt flag is set once for 10 every CNT counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK_10: CNT interrupt flag is set once for 11 every CNT counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK_11: CNT interrupt flag is set once for 12 every CNT counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK_12: CNT interrupt flag is set once for 13 every CNT counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK_13: CNT interrupt flag is set once for 14 every CNT counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK_14: CNT interrupt flag is set once for 15 every CNT counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK_15: CNT interrupt flag is set once for 16 every CNT counts at "0x0000" or peak (skiping 15 count)
 * @retval None
 */
void TMR4_CNT_SetIntMaskTimes(M4_TMR4_TypeDef *TMR4x,
                                        uint16_t u16IntSource,
                                        uint16_t u16MaskTimes)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_INT(u16IntSource));
    DDL_ASSERT(IS_VALID_TMR4_CNT_INT_MSK(u16MaskTimes));

    switch (u16IntSource)
    {
        case TMR4_CNT_INT_ZERO:
            MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_ZIM, (uint16_t)(u16MaskTimes << TMR4_CVPR_ZIM_POS));
            break;
        case TMR4_CNT_INT_PEAK:
            MODIFY_REG16(TMR4x->CVPR, TMR4_CVPR_PIM, (uint16_t)(u16MaskTimes << TMR4_CVPR_PIM_POS));
            break;
        default:
            break;
    }
}

/**
 * @brief  Get Timer4 CNT interrupt mask times
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16IntSource            Timer4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:    Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:    Underflow interrupt
 * @retval Returned value can be one of thfollowing values:
 *           @arg TMR4_CNT_INT_MASK_0:  CNT interrupt flag is always set(not masked) for every CNT count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK_1:  CNT interrupt flag is set once for 2 every CNT counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK_2:  CNT interrupt flag is set once for 3 every CNT counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK_3:  CNT interrupt flag is set once for 4 every CNT counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK_4:  CNT interrupt flag is set once for 5 every CNT counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK_5:  CNT interrupt flag is set once for 6 every CNT counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK_6:  CNT interrupt flag is set once for 7 every CNT counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK_7:  CNT interrupt flag is set once for 8 every CNT counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK_8:  CNT interrupt flag is set once for 9 every CNT counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK_9:  CNT interrupt flag is set once for 10 every CNT counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK_10: CNT interrupt flag is set once for 11 every CNT counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK_11: CNT interrupt flag is set once for 12 every CNT counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK_12: CNT interrupt flag is set once for 13 every CNT counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK_13: CNT interrupt flag is set once for 14 every CNT counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK_14: CNT interrupt flag is set once for 15 every CNT counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK_15: CNT interrupt flag is set once for 16 every CNT counts at "0x0000" or peak (skiping 15 count)
 *           @arg TMR4_RESULT_ERROR:    Timer4 interrupt source is invalid
 */
uint16_t TMR4_CNT_GetIntMaskTimes(const M4_TMR4_TypeDef *TMR4x,
                                            uint16_t u16IntSource)
{
    uint16_t u16MaskTimes = TMR4_RESULT_ERROR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_INT(u16IntSource));

    switch (u16IntSource)
    {
        case TMR4_CNT_INT_ZERO:
            u16MaskTimes = (uint16_t)(READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIM) >> TMR4_CVPR_ZIM_POS);
            break;
        case TMR4_CNT_INT_PEAK:
            u16MaskTimes = (uint16_t)(READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIM) >> TMR4_CVPR_PIM_POS);
            break;
        default:
            break;
    }

    return u16MaskTimes;
}

/**
 * @brief  Get Timer4 CNT interrupt mask current times
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u16IntSource            Timer4 interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_CNT_INT_PEAK:    Overflow interrupt
 *           @arg TMR4_CNT_INT_ZERO:    Underflow interrupt
 * @retval Returned value can be one of thfollowing values:
 *           @arg TMR4_CNT_INT_MASK_0:  CNT interrupt flag is always set(not masked) for every CNT count at "0x0000" or peak
 *           @arg TMR4_CNT_INT_MASK_1:  CNT interrupt flag is set once for 2 every CNT counts at "0x0000" or peak (skiping 1 count)
 *           @arg TMR4_CNT_INT_MASK_2:  CNT interrupt flag is set once for 3 every CNT counts at "0x0000" or peak (skiping 2 count)
 *           @arg TMR4_CNT_INT_MASK_3:  CNT interrupt flag is set once for 4 every CNT counts at "0x0000" or peak (skiping 3 count)
 *           @arg TMR4_CNT_INT_MASK_4:  CNT interrupt flag is set once for 5 every CNT counts at "0x0000" or peak (skiping 4 count)
 *           @arg TMR4_CNT_INT_MASK_5:  CNT interrupt flag is set once for 6 every CNT counts at "0x0000" or peak (skiping 5 count)
 *           @arg TMR4_CNT_INT_MASK_6:  CNT interrupt flag is set once for 7 every CNT counts at "0x0000" or peak (skiping 6 count)
 *           @arg TMR4_CNT_INT_MASK_7:  CNT interrupt flag is set once for 8 every CNT counts at "0x0000" or peak (skiping 7 count)
 *           @arg TMR4_CNT_INT_MASK_8:  CNT interrupt flag is set once for 9 every CNT counts at "0x0000" or peak (skiping 8 count)
 *           @arg TMR4_CNT_INT_MASK_9:  CNT interrupt flag is set once for 10 every CNT counts at "0x0000" or peak (skiping 9 count)
 *           @arg TMR4_CNT_INT_MASK_10: CNT interrupt flag is set once for 11 every CNT counts at "0x0000" or peak (skiping 10 count)
 *           @arg TMR4_CNT_INT_MASK_11: CNT interrupt flag is set once for 12 every CNT counts at "0x0000" or peak (skiping 11 count)
 *           @arg TMR4_CNT_INT_MASK_12: CNT interrupt flag is set once for 13 every CNT counts at "0x0000" or peak (skiping 12 count)
 *           @arg TMR4_CNT_INT_MASK_13: CNT interrupt flag is set once for 14 every CNT counts at "0x0000" or peak (skiping 13 count)
 *           @arg TMR4_CNT_INT_MASK_14: CNT interrupt flag is set once for 15 every CNT counts at "0x0000" or peak (skiping 14 count)
 *           @arg TMR4_CNT_INT_MASK_15: CNT interrupt flag is set once for 16 every CNT counts at "0x0000" or peak (skiping 15 count)
 *           @arg TMR4_RESULT_ERROR:    Timer4 interrupt source is invalid
 */
uint16_t TMR4_CNT_GetIntMaskCurrentTimes(const M4_TMR4_TypeDef *TMR4x,
                                                        uint16_t u16IntSource)
{
    uint16_t u16MaskTimes = TMR4_RESULT_ERROR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_CNT_INT(u16IntSource));

    switch (u16IntSource)
    {
        case TMR4_CNT_INT_ZERO:
            u16MaskTimes = (uint16_t)(READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_ZIC) >> TMR4_CVPR_ZIC_POS);
            break;
        case TMR4_CNT_INT_PEAK:
            u16MaskTimes = (uint16_t)(READ_REG16_BIT(TMR4x->CVPR, TMR4_CVPR_PIC) >> TMR4_CVPR_PIC_POS);
            break;
        default:
            break;
    }

    return u16MaskTimes;
}

/**
 * @brief  Set Timer4 count direction signal output to port
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] enNewState          The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_CNT_PortOutputDirSigCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    }
    else
    {
        CLEAR_REG16_BIT(TMR4x->SCER, TMR4_SCER_PCTS);
    }
}

/**
 * @}
 */

/**
 * @defgroup TMR4_OCO_Global_Functions TIMER4 OCO Global Functions
 * @{
 */

/**
 * @brief  Initialize Timer4 OCO
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] pstcInit            Pointer to a @ref stc_tmr4_oco_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: u32Ch is invalid or pstcInit = NULL
 */
en_result_t TMR4_OCO_Init(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_tmr4_oco_init_t *pstcInit)
{
    uint16_t u16Val = 0U;
    __IO uint16_t *TMR4_OCER;
    __IO uint16_t *TMR4_OCSR;
    __IO uint16_t *TMR4_OCCR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
        DDL_ASSERT(IS_VALID_TMR4_OCO_STATE(pstcInit->u16OcoCmd));
        DDL_ASSERT(IS_VALID_TMR4_OCO_OCCR_LINK_TRANSFER(pstcInit->u16OccrLinkTransfer));
        DDL_ASSERT(IS_VALID_TMR4_OCO_OCMR_LINK_TRANSFER(pstcInit->u16OcmrLinkTransfer));
        DDL_ASSERT(IS_VALID_TMR4_OCO_OCCR_BUF_MODE(pstcInit->u16OccrBufMode));
        DDL_ASSERT(IS_VALID_TMR4_OCO_OCMR_BUF_MODE(pstcInit->u16OcmrBufMode));
        DDL_ASSERT(IS_VALID_TMR4_OCO_PORT_INVALID_OP(pstcInit->u16OcoInvalidOp));

        /* Get pointer of current channel OCO register address */
        TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);
        TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
        TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

        /* Set port output valid && OP level && interrupt */
        u16Val = ((uint16_t)(pstcInit->u16OcoCmd << REG16_1BIT_OFS(u32Ch))  | \
                  (uint16_t)(pstcInit->u16OcoInvalidOp << REG16_1BIT_OFS(u32Ch)));
        MODIFY_REG16(*TMR4_OCSR, TMR4_OCSR_MASK(u32Ch), u16Val);

        /* Set OCMR&&OCCR buffer */
        u16Val = ((uint16_t)(pstcInit->u16OccrBufMode << REG16_2BIT_OFS(u32Ch)) | \
                  (uint16_t)(pstcInit->u16OcmrBufMode << REG16_2BIT_OFS(u32Ch)) | \
                  (uint16_t)(pstcInit->u16OccrLinkTransfer << REG16_1BIT_OFS(u32Ch)) | \
                  (uint16_t)(pstcInit->u16OcmrLinkTransfer << REG16_1BIT_OFS(u32Ch)));
        MODIFY_REG16(*TMR4_OCER, TMR4_OCER_MASK(u32Ch), u16Val);

        /* Set OCO compare match value */
        WRITE_REG16(*TMR4_OCCR, pstcInit->u16CompareVal);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_oco_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_tmr4_oco_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMR4_OCO_StructInit(stc_tmr4_oco_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u16OcoCmd = TMR4_OCO_ENABLE;
        pstcInit->u16OccrLinkTransfer = TMR4_OCO_OCCR_LINK_TRANSFER_DISABLE;
        pstcInit->u16OcmrLinkTransfer = TMR4_OCO_OCMR_LINK_TRANSFER_DISABLE;
        pstcInit->u16OccrBufMode = TMR4_OCO_OCCR_BUF_DISABLE;
        pstcInit->u16OcmrBufMode = TMR4_OCO_OCMR_BUF_DISABLE;
        pstcInit->u16OcoInvalidOp = TMR4_OCO_INVAILD_OP_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize Timer4 OCO
 * @param  [in] TMR4x                   Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:            Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:            Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:            Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @retval None
 */
void TMR4_OCO_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_OCER;
    __IO uint16_t *TMR4_OCSR;
    __IO uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    /* Clear bits: port output valid && OP level && interrupt */
    CLEAR_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_MASK(u32Ch));

    /* Clear bits: OCMR&&OCCR buffer */
    CLEAR_REG16_BIT(*TMR4_OCER, TMR4_OCER_MASK(u32Ch));

    /* Set OCO compare match value */
    WRITE_REG16(*TMR4_OCCR, 0x0000U);
}

/**
 * @brief  Set Timer4 OCO OCCR buffer mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16OccrBufMode      Timer4 OCO OCCR buffer mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_OCCR_BUF_DISABLE:          Disable the register OCCR buffer function
 *           @arg TMR4_OCO_OCCR_BUF_CNT_ZERO:         Register OCCR buffer transfer when counter value is 0x0000
 *           @arg TMR4_OCO_OCCR_BUF_CNT_PEAK:         Register OCCR buffer transfer when counter value is CPSR
 *           @arg TMR4_OCO_OCCR_BUF_CNT_ZERO_OR_PEAK: Register OCCR buffer transfer when the value is both 0 and CPSR
 * @retval None
 */
void TMR4_OCO_SetOccrBufMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16OccrBufMode)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_OCCR_BUF_MODE(u16OccrBufMode));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: OCCR buffer mode */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_CxBUFEN_MASK(u32Ch), \
                 (u16OccrBufMode << REG16_2BIT_OFS(u32Ch)));
}

/**
 * @brief  Get Timer4 OCO OCCR buffer mode
 *         This parameter can be one of the following values:
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_OCO_OCCR_BUF_DISABLE:          Disable the register OCCR buffer function
 *           @arg TMR4_OCO_OCCR_BUF_CNT_ZERO:         Register OCCR buffer transfer when counter value is 0x0000
 *           @arg TMR4_OCO_OCCR_BUF_CNT_PEAK:         Register OCCR buffer transfer when counter value is CPSR
 *           @arg TMR4_OCO_OCCR_BUF_CNT_ZERO_OR_PEAK: Register OCCR buffer transfer when the value is both 0 and CPSR
 */
uint16_t TMR4_OCO_GetOccrBufMode(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch)
{
    uint16_t OccrBufMode;
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Get OCCR buffer mode */
    OccrBufMode = READ_REG16_BIT(*TMR4_OCER, TMR4_OCER_CxBUFEN_MASK(u32Ch));

    return (uint16_t)(OccrBufMode >> REG16_2BIT_OFS(u32Ch));
}

/**
 * @brief  Set Timer4 OCO OCCR buffer link transfer function
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16TransferState    The OCO OCCR buffer link transfer state
 *           @arg TMR4_OCO_OCCR_LINK_TRANSFER_DISABLE: Disable the register OCCR buffer link transfer function
 *           @arg TMR4_OCO_OCCR_LINK_TRANSFER_ENABLE: Register OCCR buffer transfer when the value is both 0 and CPSR and ZIC/PIC is 0
 * @retval None
 */
void TMR4_OCO_SetOccrLinkTransfer(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16TransferState)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_OCCR_LINK_TRANSFER(u16TransferState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: OCCR link transfer function */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_LMCx_MASK(u32Ch), \
                 (u16TransferState << REG16_1BIT_OFS(u32Ch)));
}

/**
 * @brief  Set Timer4 OCO OCMR buffer mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16OcmrBufMode      Timer4 OCO OCCR buffer mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_OCMR_BUF_DISABLE:          Disable the register OCMR buffer function
 *           @arg TMR4_OCO_OCMR_BUF_CNT_ZERO:         Register OCMR buffer transfer when counter value is 0x0000
 *           @arg TMR4_OCO_OCMR_BUF_CNT_PEAK:         Register OCMR buffer transfer when counter value is CPSR
 *           @arg TMR4_OCO_OCMR_BUF_CNT_ZERO_OR_PEAK: Register OCMR buffer transfer when the value is both 0 and CPSR
 * @retval None
 */
void TMR4_OCO_SetOcmrBufMode(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OcmrBufMode)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_OCMR_BUF_MODE(u16OcmrBufMode));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: OCMR buffer mode */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_MxBUFEN_MASK(u32Ch), \
                 (u16OcmrBufMode << REG16_2BIT_OFS(u32Ch)));
}

/**
 * @brief  Get Timer4 OCO OCMR buffer mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @retval Returned value can be one of the following values:
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_OCMR_BUF_DISABLE:          Disable the register OCMR buffer function
 *           @arg TMR4_OCO_OCMR_BUF_CNT_ZERO:         Register OCMR buffer transfer when counter value is 0x0000
 *           @arg TMR4_OCO_OCMR_BUF_CNT_PEAK:         Register OCMR buffer transfer when counter value is CPSR
 *           @arg TMR4_OCO_OCMR_BUF_CNT_ZERO_OR_PEAK: Register OCMR buffer transfer when the value is both 0 and CPSR
 */
uint16_t TMR4_OCO_GetOcmrBufMode(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch)
{
    uint16_t u16OcmrBufMode;
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Get OCCR buffer mode */
    u16OcmrBufMode = READ_REG16_BIT(*TMR4_OCER, TMR4_OCER_MxBUFEN_MASK(u32Ch));

    return (uint16_t)(u16OcmrBufMode >> REG16_2BIT_OFS(u32Ch));
}

/**
 * @brief  Set Timer4 OCO OCMR buffer link transfer function
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16TransferState    The OCO OCCR buffer link transfer state
 *           @arg TMR4_OCO_OCCR_LINK_TRANSFER_DISABLE: Disable the register OCCR buffer link transfer function
 *           @arg TMR4_OCO_OCCR_LINK_TRANSFER_ENABLE: Register OCCR buffer transfer when the value is both 0 and CPSR and ZIC/PIC is 0
 * @retval None
 */
void TMR4_OCO_SetOcmrLinkTransfer(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16TransferState)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_OCMR_LINK_TRANSFER(u16TransferState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: OCMR link transfer function */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_LMMx_MASK(u32Ch), \
                 (u16TransferState << REG16_1BIT_OFS(u32Ch)));
}

/**
 * @brief  Extend the matching conditions of Timer4 OCO channel
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] enNewState          The function new state
 *           @arg TMR4_OCO_EXTEND_MATCH_DISABLE: Disable TIMER4 OCO extend match function
 *           @arg TMR4_OCO_EXTEND_MATCH_ENABLE: Enable TIMER4 OCO extend match function
 * @retval None
 */
void TMR4_OCO_SetExtMatchCond(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16ExtMatch)
{
    __IO uint16_t *TMR4_OCER;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_EXTEND_MATCH(u16ExtMatch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);

    /* Set OCER register: Extend match function */
    MODIFY_REG16(*TMR4_OCER, \
                 TMR4_OCER_MCECx_MASK(u32Ch), \
                 (u16ExtMatch << REG16_1BIT_OFS(u32Ch)));
}

/**
 * @brief  Set the Timer4 OCO high channel mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 * @param  [in] pstcMode            Pointer to a @ref stc_oco_high_ch_compare_mode_t structure of the Timer4 OCO high channel mode
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: pstcMode = NULL
 */
en_result_t TMR4_OCO_SetHighChCompareMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_high_ch_compare_mode_t *pstcMode)
{
    __IO uint16_t *TMR4_OCER;
    __IO uint16_t *TMR4_OCMR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check pointer */
    if (NULL != pstcMode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_OCO_HIGH_CH(u32Ch));
        DDL_ASSERT(IS_VALID_TMR4_OCO_EXTEND_MATCH(pstcMode->u16ExtendMatch));

        /* Get pointer of current channel OCO register address */
        TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
        TMR4_OCMR = TMR4_OCMRx(TMR4x, u32Ch);

        WRITE_REG16(*TMR4_OCMR, pstcMode->OCMRx);
        MODIFY_REG16(*TMR4_OCER, TMR4_OCER_MCECx_MASK(u32Ch), pstcMode->u16ExtendMatch);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the Timer4 OCO low channel mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 * @param  [in] pstcMode            Pointer to a @ref stc_oco_low_ch_compare_mode_t structure of the Timer4 OCO low channel mode
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: pstcMode = NULL
 */
en_result_t TMR4_OCO_SetLowChCompareMode(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_oco_low_ch_compare_mode_t *pstcMode)
{
    __IO uint16_t *TMR4_OCER;
    __IO uint32_t *TMR4_OCMR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check pointer */
    if (NULL != pstcMode)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_OCO_LOW_CH(u32Ch));
        DDL_ASSERT(IS_VALID_TMR4_OCO_EXTEND_MATCH(pstcMode->u16ExtendMatch));

        /* Get pointer of current channel OCO register address */
        TMR4_OCER = TMR4_OCERx(TMR4x, u32Ch);
        TMR4_OCMR = (__IO uint32_t*)TMR4_OCMRx(TMR4x, u32Ch);

        WRITE_REG32(*TMR4_OCMR, pstcMode->OCMRx);
        MODIFY_REG16(*TMR4_OCER, \
                     TMR4_OCER_MCECx_MASK(u32Ch), \
                     (pstcMode->u16ExtendMatch << REG16_1BIT_OFS(u32Ch)));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the Timer4 OCO low channel mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16OcoCmd           The function new state
 *           @arg TMR4_OCO_DISABLE: Disable TIM4_<t>_OxH/TIM4_<t>_OxL output
 *           @arg TMR4_OCO_ENABLE: Enable TIM4_<t>_OxH/TIM4_<t>_OxL output
 * @retval None
 */
void TMR4_OCO_SetOutputCompare(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OcoCmd)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_STATE(u16OcoCmd));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Set OCSR port output compare */
    MODIFY_REG16(*TMR4_OCSR, \
                 TMR4_OCSR_OCEx_MASK(u32Ch), \
                 (u16OcoCmd << REG16_1BIT_OFS(u32Ch)));
}

/**
 * @brief  Set the Timer4 OCO interrupt function
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16IntSource        The OCO interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_INT_MATCH  TIMER4 OCO count match interrupt
 * @param  [in] enNewState          The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_OCO_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16IntSource,
                            en_functional_state_t enNewState)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_INT(u16IntSource));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*TMR4_OCSR, (u16IntSource << REG16_1BIT_OFS(u32Ch)));
    }
    else
    {
        CLEAR_REG16_BIT(*TMR4_OCSR, (u16IntSource << REG16_1BIT_OFS(u32Ch)));
    }
}

/**
 * @brief  Set the Timer4 OCO interrupt flag
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16Flag             The OCO flag
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_FLAG_MATCH  TIMER4 OCO count match flag
 * @retval An en_flag_status_t enumeration value:
 *           - Reset:               None interrupt request flag is set on Timer4 OCO
 *           - Set:                 Detection interrupt request on Timer4 OCO
 */
en_flag_status_t TMR4_OCO_GetFlag(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16Flag)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    return (READ_REG16_BIT(*TMR4_OCSR, (u16Flag << REG16_1BIT_OFS(u32Ch))) ? Set : Reset);
}

/**
 * @brief  Clear the Timer4 OCO interrupt function
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16Flag             The OCO flag
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_FLAG_MATCH  TIMER4 OCO count match flag
 * @retval None
 */
void TMR4_OCO_ClearFlag(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                uint16_t u16Flag)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Clear OCSR count compare flag */
    CLEAR_REG16_BIT(*TMR4_OCSR, (u16Flag << REG16_1BIT_OFS(u32Ch)));
}

/**
 * @brief  Set Timer4 OCO invalid output polarity
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16OutputPolarity   Timer4 OCO invalid output polarity.
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_INVAILD_OP_LOW:    TIM4_<t>_OxH/TIM4_<t>_OxL output low level when OCO is invalid
 *           @arg TMR4_OCO_INVAILD_OP_HIGH:   TIM4_<t>_OxH/TIM4_<t>_OxL output high level when OCO is invalid
 * @retval None
 */
void TMR4_OCO_SetOcoInvalidOp(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16OutputPolarity)
{
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_OCO_PORT_INVALID_OP(u16OutputPolarity));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Set OCSR register: OCO invalid output polarity */
    MODIFY_REG16(*TMR4_OCSR, \
                 TMR4_OCSR_OCPx_MASK(u32Ch), \
                 (u16OutputPolarity << REG16_1BIT_OFS(u32Ch)));

}

/**
 * @brief  Get Timer4 OCO output polarity
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_OCO_INVAILD_OP_LOW:    TIM4_<t>_OxH/TIM4_<t>_OxL output low level when OCO is invalid
 *           @arg TMR4_OCO_INVAILD_OP_HIGH:   TIM4_<t>_OxH/TIM4_<t>_OxL output high level when OCO is invalid
 *           @arg TMR4_RESULT_ERROR:          Timer4 OCO channel is invalid
 */
uint16_t TMR4_OCO_GetOutputPolarity(const M4_TMR4_TypeDef *TMR4x,
                                                uint32_t u32Ch)
{
    uint16_t u16OutputPolarity;
    __IO uint16_t *TMR4_OCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCSR = TMR4_OCSRx(TMR4x, u32Ch);

    /* Get OCSR register: OCO output polarity */
    u16OutputPolarity = READ_REG16_BIT(*TMR4_OCSR, TMR4_OCSR_OCPx_MASK(u32Ch));

    return (u16OutputPolarity >> REG16_1BIT_OFS(u32Ch));
}

/**
 * @brief  Set Timer4 OCO compare value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @param  [in] u16CompareVal          The Timer4 OCO OCCR register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_OCO_SetCompareVal(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16CompareVal)
{
    __IO uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    WRITE_REG16(*TMR4_OCCR, u16CompareVal);
}

/**
 * @brief  Get Timer4 OCO OCCR compare value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 OCO channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_OCO_UH:      Timer4 OCO channel - UH
 *           @arg TMR4_OCO_UL:      Timer4 OCO channel - UL
 *           @arg TMR4_OCO_VH:      Timer4 OCO channel - VH
 *           @arg TMR4_OCO_VL:      Timer4 OCO channel - VL
 *           @arg TMR4_OCO_WH:      Timer4 OCO channel - WH
 *           @arg TMR4_OCO_WL:      Timer4 OCO channel - WL
 * @retval The OCCR register value of the Timer4 OCO
 */
uint16_t TMR4_OCO_GetCompareVal(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __IO uint16_t *TMR4_OCCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_OCO_CH(u32Ch));

    /* Get pointer of current channel OCO register address */
    TMR4_OCCR = TMR4_OCCRx(TMR4x, u32Ch);

    return READ_REG16(*TMR4_OCCR);
}

/**
 * @}
 */

/**
 * @defgroup TMR4_PWM_Global_Functions TIMER4 PWM Global Functions
 * @{
 */

/**
 * @brief  Initialize Timer4 PWM
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [in] pstcInit            Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: u32Ch is invalid or pstcInit = NULL
 */
en_result_t TMR4_PWM_Init(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch,
                                const stc_tmr4_pwm_init_t *pstcInit)
{
    __IO uint16_t *TMR4_POCR;
    __IO uint16_t *TMR4_RCSR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check channel && structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));
        DDL_ASSERT(IS_VALID_TMR4_PWM_MODE(pstcInit->u16Mode));
        DDL_ASSERT(IS_VALID_TMR4_PWM_CLK_DIV(pstcInit->u16ClkDiv));
        DDL_ASSERT(IS_VALID_TMR4_PWM_TRANSFORM_OCO_POLARITY(pstcInit->u16TransformOcoPol));
        DDL_ASSERT(IS_VALID_TMR4_PWM_EMB_PORT_OUTPUT_STATE(pstcInit->u32EmbOxHPortState));
        DDL_ASSERT(IS_VALID_TMR4_PWM_EMB_PORT_OUTPUT_STATE(pstcInit->u32EmbOxLPortState));

        /* Get pointer of current channel PWM register address */
        TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);
        TMR4_RCSR = TMR4_RCSRx(TMR4x);

        /* Set POCR register */
        WRITE_REG16(*TMR4_POCR, (pstcInit->u16ClkDiv | pstcInit->u16Mode | pstcInit->u16TransformOcoPol));

        /* Set RCSR register */
        MODIFY_REG16(*TMR4_RCSR,
                      TMR4_RCSR_RTEx_MASK(u32Ch), \
                      (TMR4_RCSR_RTIDx_MASK(u32Ch) | TMR4_RCSR_RTSx_MASK(u32Ch) | TMR4_RCSR_RTICx_MASK(u32Ch)));

        /* Set PSCR register: PWM port state */
        MODIFY_REG32(TMR4x->PSCR, \
                     (((uint32_t)TMR4_PSCR_OEUH | (uint32_t)TMR4_PSCR_OEUL) << (u32Ch * 2UL) | \
                      ((uint32_t)TMR4_PSCR_OSUH | (uint32_t)TMR4_PSCR_OSUL) << (u32Ch * 4UL)), \
                     ((pstcInit->u32OxHPortOutMode << (u32Ch * 2UL)) | \
                      (pstcInit->u32OxLPortOutMode << (u32Ch * 2UL + 1UL)) | \
                      (pstcInit->u32EmbOxHPortState << (u32Ch * 4UL)) | \
                      (pstcInit->u32EmbOxLPortState << (u32Ch * 4UL + 2UL))));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_pwm_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMR4_PWM_StructInit(stc_tmr4_pwm_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u16Mode = TMR4_PWM_THROUGH_MODE;
        pstcInit->u16ClkDiv = TMR4_PWM_CLK_DIV1;
        pstcInit->u16TransformOcoPol = TMR4_PWM_OP_OXH_HOLD_OXL_HOLD;
        pstcInit->u32OxHPortOutMode = TMR4_PWM_PORT_OUTPUT_OSxy;
        pstcInit->u32EmbOxHPortState = TMR4_PWM_EMB_PORT_OUTPUT_NORMAL;
        pstcInit->u32OxLPortOutMode = TMR4_PWM_PORT_OUTPUT_OSxy;
        pstcInit->u32EmbOxLPortState = TMR4_PWM_EMB_PORT_OUTPUT_NORMAL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize Timer4 PWM
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_POCR;
    __IO uint16_t *TMR4_RCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);
    TMR4_RCSR = TMR4_RCSRx(TMR4x);

    /* Set POCR register */
    WRITE_REG16(*TMR4_POCR, (TMR4_PWM_CLK_DIV1 | \
                             TMR4_PWM_THROUGH_MODE | \
                             TMR4_PWM_OP_OXH_HOLD_OXL_HOLD));

    /* Set RCSR register */
    MODIFY_REG16(*TMR4_RCSR,
                  TMR4_RCSR_RTEx_MASK(u32Ch), \
                  (TMR4_RCSR_RTIDx_MASK(u32Ch) | \
                   TMR4_RCSR_RTSx_MASK(u32Ch) | \
                   TMR4_RCSR_RTICx_MASK(u32Ch)));
}

/**
 * @brief  Set Timer4 PWM output polarity transform
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [in] u16OcoPolTransform  Timer4 PWM transform OCO polarity
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_OP_OXH_HOLD_OXL_HOLD:      Output PWML and PWMH signals without changing the level
 *           @arg TMR4_PWM_OP_OXH_INVERT_OXL_INVERT:  Output both PWML and PWMH signals reversed
 *           @arg TMR4_PWM_OP_OXH_INVERT_OXL_HOLD:    Output the PWMH signal reversed, outputs the PWML signal without changing the level
 *           @arg TMR4_PWM_OP_OXH_HOLD_OXL_INVERT:    Output the PWMH signal without changing the level, Outputs the PWML signal reversed
 * @retval None
 */
void TMR4_PWM_SetOcoPolarityTransform(M4_TMR4_TypeDef *TMR4x,
                                                uint32_t u32Ch,
                                                uint16_t u16OcoPolTransform)
{
    __IO uint16_t *TMR4_POCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_PWM_TRANSFORM_OCO_POLARITY(u16OcoPolTransform));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);

    MODIFY_REG16(*TMR4_POCR, TMR4_POCR_LVLS, u16OcoPolTransform);
}

/**
 * @brief  Get Timer4 PWM output polarity transform
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_PWM_OP_OXH_HOLD_OXL_HOLD:      Output PWML and PWMH signals without changing the level
 *           @arg TMR4_PWM_OP_OXH_INVERT_OXL_INVERT:  Output both PWML and PWMH signals reversed
 *           @arg TMR4_PWM_OP_OXH_INVERT_OXL_HOLD:    Output the PWMH signal reversed, outputs the PWML signal without changing the level
 *           @arg TMR4_PWM_OP_OXH_HOLD_OXL_INVERT:    Output the PWMH signal without changing the level, Outputs the PWML signal reversed
 */
uint16_t TMR4_PWM_GetOcoPolarityTransform(const M4_TMR4_TypeDef *TMR4x,
                                                    uint32_t u32Ch)
{
    __IO uint16_t *TMR4_POCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_POCR = TMR4_POCRx(TMR4x, u32Ch);

    return READ_REG16_BIT(*TMR4_POCR, TMR4_POCR_LVLS);
}

/**
 * @brief  Start Timer4 PWM reload-timer
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_StartReloadTimer(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTEx_MASK(u32Ch));
}

/**
 * @brief  Stop Timer4 PWM reload-timer
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_StopReloadTimer(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTSx_MASK(u32Ch));
}

/**
 * @brief  Set the Timer4 PWM interrupt function
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [in] enNewState          The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_PWM_IntCmd(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        CLEAR_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTIDx_MASK(u32Ch));
    }
    else
    {
        SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTIDx_MASK(u32Ch));
    }
}

/**
 * @brief  Get PWM reload-timer interrupt flag
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval An en_flag_status_t enumeration value:
 *           - Reset                None interrupt request on PWM reload-timer
 *           - Set                  Detection interrupt request on PWM reload-timer
 */
en_flag_status_t TMR4_PWM_GetFlag(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __IO uint16_t *TMR4_RCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    /* Get pointer of current channel PWM register address */
    TMR4_RCSR = TMR4_RCSRx(TMR4x);

    return (READ_REG16_BIT(*TMR4_RCSR, TMR4_RCSR_RTIFx_MASK(u32Ch)) ? Set : Reset);
}

/**
 * @brief  Clear PWM reload-timer interrupt flag
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @retval None
 */
void TMR4_PWM_ClearFlag(M4_TMR4_TypeDef *TMR4x,
                                uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    SET_REG16_BIT(TMR4x->RCSR, TMR4_RCSR_RTICx_MASK(u32Ch));
}

/**
 * @brief  Set Timer4 PWM dead region count
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [in] u16PDAR             PDAR value
 *           @arg number of 16bit
 * @param  [in] u16PDBR             PDBR value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetDeadRegionValue(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16PDAR,
                                            uint16_t u16PDBR)
{
    __IO uint16_t *TMR4_PDAR;
    __IO uint16_t *TMR4_PDBR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_PDAR = TMR4_PDARx(TMR4x, u32Ch);
    TMR4_PDBR = TMR4_PDBRx(TMR4x, u32Ch);

    WRITE_REG16(*TMR4_PDAR, u16PDAR);
    WRITE_REG16(*TMR4_PDBR, u16PDBR);
}

/**
 * @brief  Get Timer4 PWM dead region count
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [out] pu16PDAR           Pointer of 16bit data
 *           @arg pointer of 16bit
 * @param  [out] pu16PDBR           Pointer of 16bit data
 *           @arg pointer of 16bit
 * @retval None
 */
void TMR4_PWM_GetDeadRegionValue(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t *pu16PDAR,
                                            uint16_t *pu16PDBR)
{
    __IO uint16_t *TMR4_PDAR;
    __IO uint16_t *TMR4_PDBR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_PDAR = TMR4_PDARx(TMR4x, u32Ch);
    TMR4_PDBR = TMR4_PDBRx(TMR4x, u32Ch);

    *pu16PDAR = READ_REG16(*TMR4_PDAR);
    *pu16PDBR = READ_REG16(*TMR4_PDBR);
}

/**
 * @brief  Set Timer4 PWM filter count value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_U:       Timer4 PWM couple channel - U
 *           @arg TMR4_PWM_V:       Timer4 PWM couple channel - V
 *           @arg TMR4_PWM_W:       Timer4 PWM couple channel - W
 * @param  [in] u16Count            Timer4 PWM filter count value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_PWM_SetFilterCountValue(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch,
                                            uint16_t u16Count)
{
    __IO uint16_t *TMR4_PFSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_CH(u32Ch));

    /* Get pointer of current channel PWM register address */
    TMR4_PFSR = TMR4_PFSRx(TMR4x, u32Ch);

    WRITE_REG16(*TMR4_PFSR, u16Count);
}

/**
 * @brief Enable Timer4 PWM master output
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] enNewSta            The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_PWM_AutoOutputCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_AOE);
    }
    else
    {
        CLEAR_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_AOE);
    }
}

/**
 * @brief Enable Timer4 PWM master output
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] enNewState          The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR4_PWM_MasterOutputCmd(M4_TMR4_TypeDef *TMR4x,
                                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    }
    else
    {
        CLEAR_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_MOE);
    }
}

/**
 * @brief Set Timer4 PWM port output mode
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUH:  Timer4 PWM port - TIM4_<t>_OUH
 *           @arg TMR4_PWM_PORT_OUL:  Timer4 PWM port - TIM4_<t>_OUL
 *           @arg TMR4_PWM_PORT_OVH:  Timer4 PWM port - TIM4_<t>_OVH
 *           @arg TMR4_PWM_PORT_OVL:  Timer4 PWM port - TIM4_<t>_OVL
 *           @arg TMR4_PWM_PORT_OWH:  Timer4 PWM port - TIM4_<t>_OWH
 *           @arg TMR4_PWM_PORT_OWL:  Timer4 PWM port - TIM4_<t>_OWL
 * @param  [in] u32Mode             The PWM port output mode
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUTPUT_OSxy: TIM4_<t>_Oxy output polarity by specified OSxy
 *           @arg TMR4_PWM_PORT_OUTPUT_NORMAL: TIM4_<t>_Oxy output normal PWM
 * @retval None
 */
void TMR4_PWM_PortOutputMode(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32PwmPort,
                                    uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_PORT(u32PwmPort));
    DDL_ASSERT(IS_VALID_TMR4_PWM_PORT_MODE(u32Mode));

    MODIFY_REG32(TMR4x->PSCR, \
                 TMR4_PSCR_OExy_MASK(u32PwmPort), \
                 (u32Mode << u32PwmPort));
}

/**
 * @brief Set Timer4 PWM port state
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32PwmPort          Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_IMMEDIATE:TIMER4 PWM port enable bit effective Time - Immediate
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_CNTUVF: TIMER4 PWM port enable bit effective Time - Timer4 counter underflow
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_CNTOVF: TIMER4 PWM port enable bit effective Time - Timer4 counter overflow
 * @retval None
 */
void TMR4_PWM_SetPortEnBitEffectTime(M4_TMR4_TypeDef *TMR4x,
                                                    uint32_t u32EffectTime)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_PORT_ENBIT_EFFECT(u32EffectTime));

    MODIFY_REG32(TMR4x->PSCR, TMR4_PSCR_ODT, u32EffectTime);
}

/**
 * @brief Get Timer4 PWM port state
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_IMMEDIATE:TIMER4 PWM port enable bit effective Time - Immediate
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_CNTUVF: TIMER4 PWM port enable bit effective Time - Timer4 counter underflow
 *           @arg TMR4_PWM_PORT_ENBIT_EFFECT_CNTOVF: TIMER4 PWM port enable bit effective Time - Timer4 counter overflow
 */
uint32_t TMR4_PWM_GetPortEnBitEffectTime(const M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    return READ_REG32_BIT(TMR4x->PSCR, TMR4_PSCR_ODT);
}

/**
 * @brief Timer4 PWM port output when emb event occur
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32PwmPort          Timer4 PWM channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_PORT_OUH:  Timer4 PWM port - TIM4_<t>_OUH
 *           @arg TMR4_PWM_PORT_OUL:  Timer4 PWM port - TIM4_<t>_OUL
 *           @arg TMR4_PWM_PORT_OVH:  Timer4 PWM port - TIM4_<t>_OVH
 *           @arg TMR4_PWM_PORT_OVL:  Timer4 PWM port - TIM4_<t>_OVL
 *           @arg TMR4_PWM_PORT_OWH:  Timer4 PWM port - TIM4_<t>_OWH
 *           @arg TMR4_PWM_PORT_OWL:  Timer4 PWM port - TIM4_<t>_OWL
 * @param  [in] u32State            The port new state
 *         This parameter can be one of the following values:
 *           @arg TMR4_PWM_EMB_PORT_OUTPUT_NORMAL:TIM4_<t>_Oxy output normal
 *           @arg TMR4_PWM_EMB_PORT_OUTPUT_HIZ:   TIM4_<t>_Oxy output Hi-z
 *           @arg TMR4_PWM_EMB_PORT_OUTPUT_LOW:   TIM4_<t>_Oxy output low level
 *           @arg TMR4_PWM_EMB_PORT_OUTPUT_HIGH:  TIM4_<t>_Oxy output high level
 * @retval None
 */
void TMR4_PWM_EmbPwmPortOutputState(M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32PwmPort,
                                            uint32_t u32State)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_PWM_PORT(u32PwmPort));
    DDL_ASSERT(IS_VALID_TMR4_PWM_EMB_PORT_OUTPUT_STATE(u32State));

    MODIFY_REG32(TMR4x->PSCR, \
                 TMR4_PSCR_OSxy_MASK(u32PwmPort), \
                 (u32State << (u32PwmPort * 2UL)));
}

/**
 * @}
 */

/**
 * @defgroup TMR4_SEVT_Global_Functions TIMER4 SEVT Global Functions
 * @{
 */

/**
 * @brief  Initialize Timer4 SEVT
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @param  [in] pstcInit            Pointer to a @ref stc_tmr4_sevt_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: u32Ch is invalid or pstcInit = NULL
 */
en_result_t TMR4_SEVT_Init(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    const stc_tmr4_sevt_init_t *pstcInit)
{
    __IO uint16_t *TMR4_SCCR;
    __IO uint16_t *TMR4_SCSR;
    __IO uint16_t *TMR4_SCMR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_MODE(pstcInit->u16Mode));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_LINK_TRANSFER(pstcInit->u16LinkTransfer));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_OUTPUT_EVENT(pstcInit->u16OutpuEvent));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_BUF_MODE(pstcInit->u16BufMode));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_UP_SEL(pstcInit->u16UpMatchCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_DOWN_SEL(pstcInit->u16DownMatchCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_PEAK_SEL(pstcInit->u16PeakMatchCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_ZERO_SEL(pstcInit->u16ZeroMatchCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_ZERO_MATCH_MASK_SEL(pstcInit->u16ZeroMatchMaskCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_PEAK_MATCH_MASK_SEL(pstcInit->u16PeakMatchMaskCmd));
        DDL_ASSERT(IS_VALID_TMR4_SEVT_MASK(pstcInit->u16MaskTimes));

        /* Get actual address of register list of current channel */
        TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);
        TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);
        TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

        /* Configure default parameter */
        WRITE_REG16(*TMR4_SCSR, 0x0000U);
        WRITE_REG16(*TMR4_SCMR, 0xFF00U);

        /* Set SCSR register */
        WRITE_REG16(*TMR4_SCSR,             \
                    (pstcInit->u16Mode    | \
                     pstcInit->u16OutpuEvent | \
                     pstcInit->u16BufMode | \
                     pstcInit->u16LinkTransfer | \
                     pstcInit->u16DownMatchCmd | \
                     pstcInit->u16PeakMatchCmd | \
                     pstcInit->u16UpMatchCmd | \
                     pstcInit->u16ZeroMatchCmd));

        /* Set SCMR register */
        WRITE_REG16(*TMR4_SCMR, \
                    (pstcInit->u16MaskTimes | \
                     pstcInit->u16ZeroMatchMaskCmd | \
                     pstcInit->u16PeakMatchMaskCmd));

        WRITE_REG16(*TMR4_SCCR, pstcInit->u16CompareVal);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr4_pwm_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_tmr4_pwm_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMR4_SEVT_StructInit(stc_tmr4_sevt_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u16CompareVal = 0U;
        pstcInit->u16Mode = TMR4_SEVT_MODE_COMPARE_TRIGGER;
        pstcInit->u16OutpuEvent = TMR4_SEVT_OUTPUT_EVENT0;
        pstcInit->u16BufMode = TMR4_SEVT_BUF_DISABLE;
        pstcInit->u16LinkTransfer = TMR4_SEVT_LINK_TRANSFER_DISABLE;
        pstcInit->u16DownMatchCmd = TMR4_SEVT_DOWN_DISABLE;
        pstcInit->u16PeakMatchCmd = TMR4_SEVT_PEAK_DISABLE;
        pstcInit->u16UpMatchCmd = TMR4_SEVT_UP_DISABLE;
        pstcInit->u16ZeroMatchCmd = TMR4_SEVT_ZERO_DISABLE;
        pstcInit->u16ZeroMatchMaskCmd = TMR4_SEVT_ZERO_MATCH_MASK_DISABLE;
        pstcInit->u16PeakMatchMaskCmd = TMR4_SEVT_PEAK_MATCH_MASK_DISABLE;
        pstcInit->u16MaskTimes = TMR4_SEVT_MASK_0;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initialize Timer4 PWM
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @retval None
 */
void TMR4_SEVT_DeInit(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCCR;
    __IO uint16_t *TMR4_SCSR;
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    /* Configure default parameter */
    WRITE_REG16(*TMR4_SCCR, 0x0U);
    WRITE_REG16(*TMR4_SCSR, 0x0000U);
    WRITE_REG16(*TMR4_SCMR, 0xFF00U);
}

/**
 * @brief  Set Timer4 SEVT trigger event
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @param  [in] u16Event            Timer4 SEVT trigger event
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_OUTPUT_EVENT0: TIMER4 SEVT output special event 0
 *           @arg TMR4_SEVT_OUTPUT_EVENT1: TIMER4 SEVT output special event 1
 *           @arg TMR4_SEVT_OUTPUT_EVENT2: TIMER4 SEVT output special event 2
 *           @arg TMR4_SEVT_OUTPUT_EVENT3: TIMER4 SEVT output special event 3
 *           @arg TMR4_SEVT_OUTPUT_EVENT4: TIMER4 SEVT output special event 4
 *           @arg TMR4_SEVT_OUTPUT_EVENT5: TIMER4 SEVT output special event 5
 * @retval None
 */
void TMR4_SEVT_SetOutpuEvent(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16Event)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_OUTPUT_EVENT(u16Event));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*TMR4_SCSR, TMR4_SCSR_EVTOS, u16Event);
}

/**
 * @brief  Get Timer4 SEVT trigger event
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_SEVT_OUTPUT_EVENT0: TIMER4 SEVT output special event 0
 *           @arg TMR4_SEVT_OUTPUT_EVENT1: TIMER4 SEVT output special event 1
 *           @arg TMR4_SEVT_OUTPUT_EVENT2: TIMER4 SEVT output special event 2
 *           @arg TMR4_SEVT_OUTPUT_EVENT3: TIMER4 SEVT output special event 3
 *           @arg TMR4_SEVT_OUTPUT_EVENT4: TIMER4 SEVT output special event 4
 *           @arg TMR4_SEVT_OUTPUT_EVENT5: TIMER4 SEVT output special event 5
 */
uint16_t TMR4_SEVT_GetOutpuEvent(M4_TMR4_TypeDef *TMR4x, uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);
    return READ_REG16_BIT(*TMR4_SCSR, TMR4_SCSR_EVTOS);
}

/**
 * @brief  Set Timer4 SEVT delay object
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @param  [in] u16DelayObject      Timer4 SEVT delay object
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_DELAY_OCCRXH: TIMER4 SEVT delay object - OCCRxh
 *           @arg TMR4_SEVT_DELAY_OCCRXL: TIMER4 SEVT delay object - OCCRxl
 * @retval None
 */
void TMR4_SEVT_SetDelayObject(M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch,
                                        uint16_t u16DelayObject)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_OBJECT(u16DelayObject));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    /* Set SCSR register */
    MODIFY_REG16(*TMR4_SCSR, TMR4_SCSR_EVTDS, u16DelayObject);
}

/**
 * @brief  Get Timer4 SEVT SCCR register value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_SEVT_DELAY_OCCRXH: TIMER4 SEVT delay object - OCCRxh
 *           @arg TMR4_SEVT_DELAY_OCCRXL: TIMER4 SEVT delay object - OCCRxl
 */
uint16_t TMR4_SEVT_GetDelayObject(const M4_TMR4_TypeDef *TMR4x,
                                            uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCSR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCSR = TMR4_SCSRx(TMR4x, u32Ch);

    return READ_REG16_BIT(*TMR4_SCSR, TMR4_SCSR_EVTDS);
}

/**
 * @brief  Set Timer4 SEVT compare value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @param  [in] u16CompareVal       SCCR register value
 *           @arg number of 16bit
 * @retval None
 */
void TMR4_SEVT_SetCompareVal(M4_TMR4_TypeDef *TMR4x,
                            uint32_t u32Ch,
                            uint16_t u16CompareVal)
{
    __IO uint16_t *TMR4_SCCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);

    /* Set SCCR register */
    WRITE_REG16(*TMR4_SCCR, u16CompareVal);
}

/**
 * @brief  Get Timer4 SEVT compare value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @retval SCCR register value
 */
uint16_t TMR4_SEVT_GetCompareVal(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCCR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCCR = TMR4_SCCRx(TMR4x, u32Ch);

    return READ_REG16(*TMR4_SCCR);
}

/**
 * @brief  Set Timer4 SEVT trigger event.
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @param  [in] u16MaskTimes        Mask times
 *           @arg TMR4_SEVT_MASK_0:   Mask 0 times
 *           @arg TMR4_SEVT_MASK_1:   Mask 1 times
 *           @arg TMR4_SEVT_MASK_2:   Mask 2 times
 *           @arg TMR4_SEVT_MASK_3:   Mask 3 times
 *           @arg TMR4_SEVT_MASK_4:   Mask 4 times
 *           @arg TMR4_SEVT_MASK_5:   Mask 5 times
 *           @arg TMR4_SEVT_MASK_6:   Mask 6 times
 *           @arg TMR4_SEVT_MASK_7:   Mask 7 times
 *           @arg TMR4_SEVT_MASK_8:   Mask 8 times
 *           @arg TMR4_SEVT_MASK_9:   Mask 9 times
 *           @arg TMR4_SEVT_MASK_10:  Mask 10 times
 *           @arg TMR4_SEVT_MASK_11:  Mask 11 times
 *           @arg TMR4_SEVT_MASK_12:  Mask 12 times
 *           @arg TMR4_SEVT_MASK_13:  Mask 13 times
 *           @arg TMR4_SEVT_MASK_14:  Mask 14 times
 *           @arg TMR4_SEVT_MASK_15:  Mask 15 times
 * @retval None
 */
void TMR4_SEVT_SetMaskTimes(M4_TMR4_TypeDef *TMR4x,
                                    uint32_t u32Ch,
                                    uint16_t u16MaskTimes)
{
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_MASK(u16MaskTimes));

    /* Get actual address of register list of current channel */
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    /* Set SCMR register */
    MODIFY_REG16(*TMR4_SCMR, TMR4_SCMR_AMC, u16MaskTimes);
}

/**
 * @brief  Get Timer4 SEVT SCCR register value
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u32Ch               Timer4 SEVT channel
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_UH:     Timer4 SEVT channel - UH
 *           @arg TMR4_SEVT_UL:     Timer4 SEVT channel - UL
 *           @arg TMR4_SEVT_VH:     Timer4 SEVT channel - VH
 *           @arg TMR4_SEVT_VL:     Timer4 SEVT channel - VL
 *           @arg TMR4_SEVT_WH:     Timer4 SEVT channel - WH
 *           @arg TMR4_SEVT_WL:     Timer4 SEVT channel - WL
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_SEVT_MASK_0:   Mask 0 times
 *           @arg TMR4_SEVT_MASK_1:   Mask 1 times
 *           @arg TMR4_SEVT_MASK_2:   Mask 2 times
 *           @arg TMR4_SEVT_MASK_3:   Mask 3 times
 *           @arg TMR4_SEVT_MASK_4:   Mask 4 times
 *           @arg TMR4_SEVT_MASK_5:   Mask 5 times
 *           @arg TMR4_SEVT_MASK_6:   Mask 6 times
 *           @arg TMR4_SEVT_MASK_7:   Mask 7 times
 *           @arg TMR4_SEVT_MASK_8:   Mask 8 times
 *           @arg TMR4_SEVT_MASK_9:   Mask 9 times
 *           @arg TMR4_SEVT_MASK_10:  Mask 10 times
 *           @arg TMR4_SEVT_MASK_11:  Mask 11 times
 *           @arg TMR4_SEVT_MASK_12:  Mask 12 times
 *           @arg TMR4_SEVT_MASK_13:  Mask 13 times
 *           @arg TMR4_SEVT_MASK_14:  Mask 14 times
 *           @arg TMR4_SEVT_MASK_15:  Mask 15 times
 */
uint16_t TMR4_SEVT_GetMaskTimes(const M4_TMR4_TypeDef *TMR4x,
                                        uint32_t u32Ch)
{
    __IO uint16_t *TMR4_SCMR;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_CH(u32Ch));

    /* Get actual address of register list of current channel */
    TMR4_SCMR = TMR4_SCMRx(TMR4x, u32Ch);

    return READ_REG16_BIT(*TMR4_SCMR, TMR4_SCMR_AMC);
}

/**
 * @brief  Set Timer4 SEVT event signal output to port
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @param  [in] u16EvtSignal        Timer4 SEVT event signal selection
 *         This parameter can be one of the following values:
 *           @arg TMR4_SEVT_PORT_OUTPUT_NONE: Disable output event signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT0_SIGNAL: Output the specified event 0 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT1_SIGNAL: Output the specified event 1 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT2_SIGNAL: Output the specified event 2 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT3_SIGNAL: Output the specified event 3 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT4_SIGNAL: Output the specified event 4 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT5_SIGNAL: Output the specified event 5 signal of Timer4 Special-EVT
 * @retval None
 */
void TMR4_SEVT_SetPortOutputEventSig(M4_TMR4_TypeDef *TMR4x,
                                            uint16_t u16EvtSignal)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));
    DDL_ASSERT(IS_VALID_TMR4_SEVT_PORT_OUTPUT_SIGNAL(u16EvtSignal));

    MODIFY_REG16(TMR4x->SCER, TMR4_SCER_EVTRS, u16EvtSignal);
}

/**
 * @brief  Get Timer4 SEVT event signal output to port
 * @param  [in] TMR4x               Pointer to Timer4 instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMR4_1:        Timer4 unit 1 instance register base
 *           @arg M4_TMR4_2:        Timer4 unit 2 instance register base
 *           @arg M4_TMR4_3:        Timer4 unit 3 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMR4_SEVT_PORT_OUTPUT_NONE: Disable output event signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT0_SIGNAL: Output the specified event 0 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT1_SIGNAL: Output the specified event 1 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT2_SIGNAL: Output the specified event 2 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT3_SIGNAL: Output the specified event 3 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT4_SIGNAL: Output the specified event 4 signal of Timer4 Special-EVT
 *           @arg TMR4_SEVT_PORT_OUTPUT_EVENT5_SIGNAL: Output the specified event 5 signal of Timer4 Special-EVT
 */
uint16_t TMR4_SEVT_GetPortOutputEventSig(const M4_TMR4_TypeDef *TMR4x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR4_INSTANCE(TMR4x));

    return READ_REG16_BIT(TMR4x->SCER, TMR4_SCER_EVTRS);
}

/**
 * @}
 */

/**
 * @}
 */

#endif /* DDL_TMR4_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/