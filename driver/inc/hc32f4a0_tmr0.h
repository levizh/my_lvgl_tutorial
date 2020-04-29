/**
 *******************************************************************************
 * @file  hc32f4a0_tmr0.h
 * @brief This file contains all the functions prototypes of the TMR0 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-15       Heqb          First version
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
#ifndef __HC32F4A0_TMR0_H__
#define __HC32F4A0_TMR0_H__

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
 * @addtogroup TMR0
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Types TMR0 Global Types
 * @{
 */

/**
 * @brief Tmr0 base counter function init structrue definition
 */
typedef struct
{
    uint32_t       u32ClockDivision;  /*!< specifies the TMR0 clock division,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Division_define */

    uint32_t       u32ClockSource;    /*!< specifies the TMR0 clock source,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Source_define*/

    uint32_t       u32Tmr0Func;        /*!< specifies the TMR0 function,
                                         compare output or capture input
                                         @ref TMR0_Function_define */

    uint32_t       u32HwTrigFunc;     /*!< specifies the TMR0 compare
                                         function hardware trigger function, and
                                         this parameter can be a value of @ref
                                         TMR0_HardwareTrigger_Func_define */

    uint16_t       u16CmpValue;       /*!< specifies the TMR0 compare value
                                         This value can be set 0-0xFFFF */
}stc_tmr0_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Macros TMR0 Global Macros
 * @{
 */

/** @defgroup TMR0_Clock_Division_define TMR0 clock division define
 * @{
 */
#define TMR0_CLK_DIV1           (uint32_t)(0UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV2           (uint32_t)(1UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV4           (uint32_t)(2UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV8           (uint32_t)(3UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV16          (uint32_t)(4UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV32          (uint32_t)(5UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV64          (uint32_t)(6UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV128         (uint32_t)(7UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV256         (uint32_t)(8UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV512         (uint32_t)(9UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV1024        (uint32_t)(10UL<<TMR0_BCONR_CKDIVA_POS)
/**
 * @}
 */

/**
 * @defgroup TMR0_Channel_Index TMR0 Channel Index
 * @{
 */
#define TMR0_ChannelA             ((uint8_t)0U)
#define TMR0_ChannelB             ((uint8_t)1U)
/**
 * @}
 */

/** @defgroup TMR0_Clock_Source_define TMR0 clock source define
 * @{
 */
#define TMR0_CLK_SRC_PCLK1        ((uint32_t)0x00000000U)
#define TMR0_CLK_SRC_INTHWTRIG    (TMR0_BCONR_SYNCLKA)
#define TMR0_CLK_SRC_LRC          (TMR0_BCONR_SYNSA)
#define TMR0_CLK_SRC_XTAL32       (TMR0_BCONR_ASYNCLKA | TMR0_BCONR_SYNSA)
/**
 * @}
 */

/** @defgroup TMR0_Function_define TMR0 Function define
 * @{
 */
#define TMR0_FUNC_CMP             ((uint32_t)0x00000000U)
#define TMR0_FUNC_CAPTURE         (TMR0_BCONR_CAPMDA | TMR0_BCONR_HICPA)
/**
 * @}
 */

/** @defgroup TMR0_HardwareTrigger_Func_define TMR0 hardware trigger function define
 * @{
 */
#define TMR0_BT_HWTRG_FUNC_START  (TMR0_BCONR_HSTAA)
#define TMR0_BT_HWTRG_FUNC_CLEAR  (TMR0_BCONR_HCLEA)
#define TMR0_BT_HWTRG_FUNC_STOP   (TMR0_BCONR_HSTPA)
#define TMR0_BT_HWTRG_FUNC_NONE   ((uint32_t)0x00000000U)
#define TMR0_BT_HETRG_FUNC_MASK   (TMR0_BT_HWTRG_FUNC_START | \
                                   TMR0_BT_HWTRG_FUNC_CLEAR | \
                                   TMR0_BT_HWTRG_FUNC_STOP)
/**
 * @}
 */

/**
 * @defgroup TMR0_CAMPAR_FLAG TMR0 Compare Status
 * @{
 */
#define TMR0_CMP_A                (TMR0_STFLR_CMFA)
#define TMR0_CMP_B                (TMR0_STFLR_CMFB)
/**
 * @}
 */

/**
 * @defgroup TMR0_Common_Trigger_Sel TMR0 common Trigger source select
 * @{
 */
#define TMR0_COM1_TRIG_DISABLE    ((uint32_t)0x00UL)
#define TMR0_COM2_TRIG_DISABLE    ((uint32_t)0x00UL)
#define TMR0_COM1_TRIG_ENABLE     ((uint32_t)(0x01UL << 31U))
#define TMR0_COM2_TRIG_ENABLE     ((uint32_t)(0x01Ul << 30U))
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
 * @addtogroup TMR0_Global_Functions
 * @{
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcInitStruct);
en_result_t TMR0_Init(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                      const stc_tmr0_init_t* pstcBaseInit);
en_result_t TMR0_DeInit(M4_TMR0_TypeDef* TMR0x);
en_result_t TMR0_Cmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                     en_functional_state_t enNewState);
en_result_t TMR0_IntCmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                        en_functional_state_t enNewState);
en_result_t TMR0_SetClkSrc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkSrc);
en_result_t TMR0_SetClkDiv(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkDiv);
en_result_t TMR0_HWTrigCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, \
                           uint32_t u32HWFunc, en_functional_state_t enNewState);
en_result_t TMR0_FuncCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32Func);
en_result_t TMR0_SetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value);
en_result_t TMR0_SetCmpVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value);
en_result_t TMR0_ClearStatus(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);

en_flag_status_t TMR0_GetStatus(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);

uint16_t TMR0_GetCntVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);
uint16_t TMR0_GetCmpVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);

void TMR0_SetTriggerSrc(en_event_src_t enEvent);
void TMR0_ComTrigCmd(uint32_t u32ComTrigEn);
/**
 * @}
 */

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
