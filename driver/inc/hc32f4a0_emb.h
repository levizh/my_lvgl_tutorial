/**
 *******************************************************************************
 * @file  hc32f4a0_emb.h
 * @brief Head file for EMB module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-04       Hongjh          First version
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
#ifndef __HC32F4A0_EMB_H__
#define __HC32F4A0_EMB_H__

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
 * @addtogroup DDL_EMB
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Types EMB Global Types
 * @{
 */

/**
 * @brief EMB monitor EMB port configuration
 */
typedef struct
{
    uint32_t    u32PortSel;         /*!< Enable or disable EMB detect port in control function
                                         This parameter can be a value of EMB_Port_EMBINx_Selection(x=1~4) */

    uint32_t    u32PortLevel;       /*!< EMB detect port level
                                         This parameter can be a value of EMB_Detect_Portx_Level(x=1~4) */

    uint32_t    u32PortFilterDiv;   /*!< EMB port filter division
                                         This parameter can be a value of EMB_Port_EMBINx_Filter_Clock_Division(x=1~4) */
} stc_emb_monitor_port_t;

/**
 * @brief EMB monitor Timer4 PWM configuration
 */
typedef struct
{
    uint32_t    u32Timer4PwmSel;    /*!< Enable or disable EMB detect Timer4 PWM x channel same phase function
                                         This parameter can be a value of EMB_Timer4_PWM_x_Selection(x=U/V/W) */

    uint32_t    u32Timer4PwmLvl;    /*!< Enable or disable EMB detect Timer4 PWM x channel polarity level
                                         This parameter can be a value of EMB_Detect_Timer4_PWM_x_Level(x=U/V/W) */
} stc_emb_monitor_tmr4_pwm_t;

/**
 * @brief EMB monitor Timer6 PWM configuration
 */
typedef struct
{
    uint32_t    u32Timer6PwmSel;    /*!< Enable or disable EMB detect Timer6_x PWM same phase function
                                         This parameter can be a value of EMB_Timer6_x_PWM_Selection(x=1~8) */

    uint32_t    u32Timer6PwmLvl;    /*!< Enable or disable EMB detect Timer6_x PWM polarity level
                                         This parameter can be a value of @ref EMB_Detect_Timer6_x_PWMW_Level(x=1~8) */
} stc_emb_monitor_tmr6_pwm_t;

/**
 * @brief EMB congtrol Timer4 initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1;                        /*!< Enable or disable EMB detect CMP1 result function
                                                     This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2;                        /*!< Enable or disable EMB detect CMP2 result function
                                                     This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3;                        /*!< Enable or disable EMB detect CMP3 result function
                                                     This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32Cmp4;                        /*!< Enable or disable EMB detect CMP4 result function
                                                     This parameter can be a value of @ref EMB_CMP4_Selection */

    uint32_t    u32Osc;                         /*!< EMB detect OSC failure function
                                                     This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_monitor_port_t      stcPort1;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort2;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort3;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort4;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_tmr4_pwm_t  stcTimer4PmwU;  /*!< EMB detect Timer4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr4_pwm_t structure */

    stc_emb_monitor_tmr4_pwm_t  stcTimer4PmwV;  /*!< EMB detect Timer4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr4_pwm_t structure */

    stc_emb_monitor_tmr4_pwm_t  stcTimer4PmwW;  /*!< EMB detect Timer4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr4_pwm_t structure */
} stc_emb_tmr4_init_t;

/**
 * @brief EMB congtrol Timer6 initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1;                        /*!< Enable or disable EMB detect CMP1 result function
                                                     This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2;                        /*!< Enable or disable EMB detect CMP2 result function
                                                     This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3;                        /*!< Enable or disable EMB detect CMP3 result function
                                                     This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32Cmp4;                        /*!< Enable or disable EMB detect CMP4 result function
                                                     This parameter can be a value of @ref EMB_CMP4_Selection */

    uint32_t    u32Osc;                         /*!< EMB detect OSC failure function
                                                     This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_monitor_port_t      stcPort1;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort2;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort3;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort4;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_1;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_2;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_3;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_4;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_5;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_6;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_7;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */

    stc_emb_monitor_tmr6_pwm_t  stcTimer6_8;    /*!< EMB detect Timer6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr6_pwm_t structure */
} stc_emb_tmr6_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Macros EMB Global Macros
 * @{
 */

/**
 * @defgroup EMB_CMP1_Selection EMB CMP1 Selection
 * @{
 */
#define EMB_CMP1_ENABLE                     (EMB_CTL1_CMPEN_0)
#define EMB_CMP1_DISABLE                    ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP2_Selection EMB CMP2 Selection
 * @{
 */
#define EMB_CMP2_ENABLE                     (EMB_CTL1_CMPEN_1)
#define EMB_CMP2_DISABLE                    ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP3_Selection EMB CMP3 Selection
 * @{
 */
#define EMB_CMP3_ENABLE                     (EMB_CTL1_CMPEN_2)
#define EMB_CMP3_DISABLE                    ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP4_Selection EMB CMP4 Selection
 * @{
 */
#define EMB_CMP4_ENABLE                     (EMB_CTL1_CMPEN_3)
#define EMB_CMP4_DISABLE                    ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_OSC_Stop_Selection EMB OSC Stop Selection
 * @{
 */
#define EMB_OSC_ENABLE                      (EMB_CTL1_OSCSTPEN)
#define EMB_OSC_DISABLE                     ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_W_Selection EMB Timer4 PWM W Selection
 * @{
 */
#define EMB_TMR4_PWM_W_ENABLE               (EMB_CTL1_PWMSEN_0)
#define EMB_TMR4_PWM_W_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_V_Selection EMB Timer4 PWM V Selection
 * @{
 */
#define EMB_TMR4_PWM_V_ENABLE               (EMB_CTL1_PWMSEN_1)
#define EMB_TMR4_PWM_V_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_U_Selection EMB Timer4 PWM U Selection
 * @{
 */
#define EMB_TMR4_PWM_U_ENABLE               (EMB_CTL1_PWMSEN_2)
#define EMB_TMR4_PWM_U_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_1_PWM_Selection EMB_Timer6_1_PWM Selection
 * @{
 */
#define EMB_TMR6_1_PWM_ENABLE               (EMB_CTL1_PWMSEN_0)
#define EMB_TMR6_1_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_2_PWM_Selection EMB_Timer6_2_PWM Selection
 * @{
 */
#define EMB_TMR6_2_PWM_ENABLE               (EMB_CTL1_PWMSEN_1)
#define EMB_TMR6_2_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_3_PWM_Selection EMB_Timer6_3_PWM Selection
 * @{
 */
#define EMB_TMR6_3_PWM_ENABLE               (EMB_CTL1_PWMSEN_2)
#define EMB_TMR6_3_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_4_PWM_Selection EMB_Timer6_4_PWM Selection
 * @{
 */
#define EMB_TMR6_4_PWM_ENABLE               (EMB_CTL1_PWMSEN_3)
#define EMB_TMR6_4_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_5_PWM_Selection EMB_Timer6_5_PWM Selection
 * @{
 */
#define EMB_TMR6_5_PWM_ENABLE               (EMB_CTL1_PWMSEN_4)
#define EMB_TMR6_5_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_6_PWM_Selection EMB_Timer6_6_PWM Selection
 * @{
 */
#define EMB_TMR6_6_PWM_ENABLE               (EMB_CTL1_PWMSEN_5)
#define EMB_TMR6_6_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_7_PWM_Selection EMB_Timer6_7_PWM Selection
 * @{
 */
#define EMB_TMR6_7_PWM_ENABLE               (EMB_CTL1_PWMSEN_6)
#define EMB_TMR6_7_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer6_8_PWM_Selection EMB_Timer6_8_PWM Selection
 * @{
 */
#define EMB_TMR6_8_PWM_ENABLE               (EMB_CTL1_PWMSEN_7)
#define EMB_TMR6_8_PWM_DISABLE              ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port1_Selection EMB Port1 Selection
 * @{
 */
#define EMB_PORT1_ENABLE                    (EMB_CTL1_PORTINEN1)
#define EMB_PORT1_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port2_Selection EMB Port2 Selection
 * @{
 */
#define EMB_PORT2_ENABLE                    (EMB_CTL1_PORTINEN2)
#define EMB_PORT2_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port3_Selection EMB Port3 Selection
 * @{
 */
#define EMB_PORT3_ENABLE                    (EMB_CTL1_PORTINEN3)
#define EMB_PORT3_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port4_Selection EMB Port4 Selection
 * @{
 */
#define EMB_PORT4_ENABLE                    (EMB_CTL1_PORTINEN2)
#define EMB_PORT4_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port1_Level EMB Detect Port1 Level
 * @{
 */
#define EMB_DETECT_PORT1_LEVEL_HIGH         ((uint32_t)0UL)
#define EMB_DETECT_PORT1_LEVEL_LOW          (EMB_CTL1_INVSEL1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port2_Level EMB Detect Port2 Level
 * @{
 */
#define EMB_DETECT_PORT2_LEVEL_HIGH         ((uint32_t)0UL)
#define EMB_DETECT_PORT2_LEVEL_LOW          (EMB_CTL1_INVSEL2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port3_Level EMB Detect Port3 Level
 * @{
 */
#define EMB_DETECT_PORT3_LEVEL_HIGH         ((uint32_t)0UL)
#define EMB_DETECT_PORT3_LEVEL_LOW          (EMB_CTL1_INVSEL3)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port4_Level EMB Detect Port4 Level
 * @{
 */
#define EMB_DETECT_PORT4_LEVEL_HIGH         ((uint32_t)0UL)
#define EMB_DETECT_PORT4_LEVEL_LOW          (EMB_CTL1_INVSEL4)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer4_PWM_W_Level EMB Detect Timer4 PWM W Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_W_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR4_PWM_W_BOTH_HIGH     (EMB_CTL2_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer4_PWM_V_Level EMB Detect Timer4 PWM V Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_V_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR4_PWM_V_BOTH_HIGH     (EMB_CTL2_PWMLV_1)
/**
 * @}
 */
/**
 * @defgroup EMB_Detect_Timer4_PWM_U_Level EMB Detect Timer4 PWM U Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_U_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR4_PWM_U_BOTH_HIGH     (EMB_CTL2_PWMLV_2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_1_PWM_Level EMB Detect Timer6_1 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_1_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_1_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_2_PWM_Level EMB Detect Timer6_2 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_2_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_2_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_3_PWM_Level EMB Detect Timer6_3 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_3_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_3_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_4_PWM_Level EMB Detect Timer6_4 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_4_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_4_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_3)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_5_PWM_Level EMB Detect Timer6_5 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_5_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_5_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_4)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_6_PWM_Level EMB Detect Timer6_6 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_6_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_6_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_5)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_7_PWM_Level EMB Detect Timer6_7 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_7_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_7_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_6)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Timer6_8_PWM_Level EMB Detect Timer6_8 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_8_PWM_BOTH_LOW      ((uint32_t)0UL)
#define EMB_DETECT_TMR6_8_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_7)
/**
 * @}
 */

/** @defgroup EMB_Port1_Filter_Clock_Division EMB Port1 Filter Clock Division
 * @{
 */
#define EMB_PORT1_FILTER_NONE               ((uint32_t)0UL)
#define EMB_PORT1_FILTER_CLK_DIV1           (EMB_CTL2_NFEN1)
#define EMB_PORT1_FILTER_CLK_DIV8           (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1_0)
#define EMB_PORT1_FILTER_CLK_DIV32          (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1_1)
#define EMB_PORT1_FILTER_CLK_DIV128         (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1)
/**
 * @}
 */

/** @defgroup EMB_Port2_Filter_Clock_Division EMB Port2 Filter Clock Division
 * @{
 */
#define EMB_PORT2_FILTER_NONE               ((uint32_t)0UL)
#define EMB_PORT2_FILTER_CLK_DIV1           (EMB_CTL2_NFEN2)
#define EMB_PORT2_FILTER_CLK_DIV8           (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2_0)
#define EMB_PORT2_FILTER_CLK_DIV32          (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2_1)
#define EMB_PORT2_FILTER_CLK_DIV128         (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2)
/**
 * @}
 */

/** @defgroup EMB_Port3_Filter_Clock_Division EMB Port3 Filter Clock Division
 * @{
 */
#define EMB_PORT3_FILTER_NONE               ((uint32_t)0UL)
#define EMB_PORT3_FILTER_CLK_DIV1           (EMB_CTL2_NFEN3)
#define EMB_PORT3_FILTER_CLK_DIV8           (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3_0)
#define EMB_PORT3_FILTER_CLK_DIV32          (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3_1)
#define EMB_PORT3_FILTER_CLK_DIV128         (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3)
/**
 * @}
 */

/** @defgroup EMB_Port4_Filter_Clock_Division EMB Port4 Filter Clock Division
 * @{
 */
#define EMB_PORT4_FILTER_NONE               ((uint32_t)0UL)
#define EMB_PORT4_FILTER_CLK_DIV1           (EMB_CTL2_NFEN4)
#define EMB_PORT4_FILTER_CLK_DIV8           (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4_0)
#define EMB_PORT4_FILTER_CLK_DIV32          (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4_1)
#define EMB_PORT4_FILTER_CLK_DIV128         (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4)
/**
 * @}
 */

/**
 * @defgroup EMB_Flag EMB Flag
 * @{
 */
#define EMB_FLAG_PWMS                       (EMB_STAT_PWMSF)
#define EMB_FLAG_CMP                        (EMB_STAT_CMPF)
#define EMB_FLAG_OSC                        (EMB_STAT_OSF)
#define EMB_FLAG_PORT1                      (EMB_STAT_PORTINF1)
#define EMB_FLAG_PORT2                      (EMB_STAT_PORTINF2)
#define EMB_FLAG_PORT3                      (EMB_STAT_PORTINF3)
#define EMB_FLAG_PORT4                      (EMB_STAT_PORTINF4)
/**
 * @}
 */

/**
 * @defgroup EMB_State EMB State
 * @{
 */
#define EMB_STATE_PWMS                      (EMB_STAT_PWMST)
#define EMB_STATE_CMP                       (EMB_STAT_CMPST)
#define EMB_STATE_OSC                       (EMB_STAT_OSST)
#define EMB_STATE_PORT1                     (EMB_STAT_PORTINST1)
#define EMB_STATE_PORT2                     (EMB_STAT_PORTINST2)
#define EMB_STATE_PORT3                     (EMB_STAT_PORTINST3)
#define EMB_STATE_PORT4                     (EMB_STAT_PORTINST4)
/**
 * @}
 */

/**
 * @defgroup EMB_Interrupt EMB Interrupt
 * @{
 */
#define EMB_INT_PWMS                        (EMB_INTEN_PWMSINTEN)
#define EMB_INT_CMP                         (EMB_INTEN_CMPINTEN)
#define EMB_INT_OSC                         (EMB_INTEN_OSINTEN)
#define EMB_INT_PORT1                       (EMB_INTEN_PORTINTEN1)
#define EMB_INT_PORT2                       (EMB_INTEN_PORTINTEN2)
#define EMB_INT_PORT3                       (EMB_INTEN_PORTINTEN3)
#define EMB_INT_PORT4                       (EMB_INTEN_PORTINTEN4)
/**
 * @}
 */

/**
 * @defgroup EMB_Release_Timer_PWM_Selection EMB Release Timer PWM Selection
 * @{
 */
#define EMB_RELEALSE_PWM_SEL_FLAG_ZERO      ((uint32_t)0UL)
#define EMB_RELEALSE_PWM_SEL_STATE_ZERO     ((uint32_t)1UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Monitor_Event EMB Monitor Event
 * @{
 */
#define EMB_EVENT_PWMS                      (EMB_RLSSEL_PWMRSEL)
#define EMB_EVENT_CMP                       (EMB_RLSSEL_CMPRSEL)
#define EMB_EVENT_OSC                       (EMB_RLSSEL_OSRSEL)
#define EMB_EVENT_PORT1                     (EMB_RLSSEL_PORTINRSEL1)
#define EMB_EVENT_PORT2                     (EMB_RLSSEL_PORTINRSEL2)
#define EMB_EVENT_PORT3                     (EMB_RLSSEL_PORTINRSEL3)
#define EMB_EVENT_PORT4                     (EMB_RLSSEL_PORTINRSEL4)
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
 * @addtogroup EMB_Global_Functions EMB Global Functions
 * @{
 */

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 4 instance register base
 *           @arg M4_EMB1:              EMB group 5 instance register base
 *           @arg M4_EMB2:              EMB group 6 instance register base
 *           @arg M4_EMB3:              EMB group 4 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWMS: PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT1: EMB Port1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT2: EMB Port2 input trigger stop PWM
 *           @arg EMB_FLAG_PORT3: EMB Port3 input trigger stop PWM
 *           @arg EMB_FLAG_PORT4: EMB Port4 input trigger stop PWM
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
__STATIC_INLINE en_flag_status_t EMB_GetFlag(const M4_EMB_TypeDef *EMBx,
                                                uint32_t u32Flag)
{
    return READ_REG32_BIT(EMBx->STAT, u32Flag) ? Set : Reset;
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 4 instance register base
 *           @arg M4_EMB1:              EMB group 5 instance register base
 *           @arg M4_EMB2:              EMB group 6 instance register base
 *           @arg M4_EMB3:              EMB group 4 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWMS: PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT1: EMB Port1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT2: EMB Port2 input trigger stop PWM
 *           @arg EMB_FLAG_PORT3: EMB Port3 input trigger stop PWM
 *           @arg EMB_FLAG_PORT4: EMB Port4 input trigger stop PWM
 * @retval None
 */
__STATIC_INLINE void EMB_ClearFlag(M4_EMB_TypeDef *EMBx,
                                        uint32_t u32Flag)
{
    SET_REG32_BIT(EMBx->STATCLR, u32Flag);
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 4 instance register base
 *           @arg M4_EMB1:              EMB group 5 instance register base
 *           @arg M4_EMB2:              EMB group 6 instance register base
 *           @arg M4_EMB3:              EMB group 4 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Status               EMB state
 *         This parameter can be one of the following values:
 *           @arg EMB_STATE_PWMS: PWM same phase occur
 *           @arg EMB_STATE_CMP: CMP comapre event occur
 *           @arg EMB_STATE_OSC: OSC stop event occur
 *           @arg EMB_STATE_PORT1: EMB Port1 input control state
 *           @arg EMB_STATE_PORT2: EMB Port2 input control state
 *           @arg EMB_STATE_PORT3: EMB Port3 input control state
 *           @arg EMB_STATE_PORT4: EMB Port4 input control state
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
__STATIC_INLINE en_flag_status_t EMB_GetStatus(const M4_EMB_TypeDef *EMBx,
                                                uint32_t u32Status)
{
    return READ_REG32_BIT(EMBx->STAT, u32Status) ? Set : Reset;
}

/**
 * @brief  Start/stop EMB software brake
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 4 instance register base
 *           @arg M4_EMB1:              EMB group 5 instance register base
 *           @arg M4_EMB2:              EMB group 6 instance register base
 *           @arg M4_EMB3:              EMB group 4 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] enNewSta                The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
__STATIC_INLINE void EMB_SwBrake(M4_EMB_TypeDef *EMBx,
                                    en_functional_state_t enNewSta)
{
    WRITE_REG32(EMBx->SOE, (uint32_t)enNewSta);
}

en_result_t EMB_Timer4Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr4_init_t *pstcInit);
en_result_t EMB_Timer4StructInit(stc_emb_tmr4_init_t *pstcInit);
en_result_t EMB_Timer6Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr6_init_t *pstcInit);
en_result_t EMB_Timer6StructInit(stc_emb_tmr6_init_t *pstcInit);
void EMB_DeInit(M4_EMB_TypeDef *EMBx);
void EMB_IntCmd(M4_EMB_TypeDef *EMBx,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewSta);
void EMB_SetReleasePwmMode(M4_EMB_TypeDef *EMBx,
                                uint32_t u32MonitorEvent,
                                uint32_t u32Mode);
/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
