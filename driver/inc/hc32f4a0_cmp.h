/**
 *******************************************************************************
 * @file  hc32f4a0_cmp.h
 * @brief Head file for CMP module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-06       Heqb         First version
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
#ifndef __HC32F4A0_CMP_H__
#define __HC32F4A0_CMP_H__

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
 * @addtogroup DDL_CMP
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CMP_Global_Types CMP Global Types
 * @{
 */

/**
 * @brief CMP configuration structure
 */
typedef struct
{
    uint8_t u8CmpCh;                /*!< Select the compare voltage channel for normal mode
                                        @ref CMP_CVSL_Channal */
    uint16_t u16CmpVol;             /*!< Select the compare voltage source for normal mode
                                        (Config the parameter when use CMP1 or CMP3)@ref CMP1_3_CVSL_Source */
    uint8_t u8RefVol;               /*!< Reference voltage for normal mode, @ref CMP_RVSL_Source*/

    uint8_t u8OutPolarity;          /*!< Output polarity select, @ref CMP_Out_Polarity_Select */

    uint8_t u8OutDetectEdges;       /*!< Output detecte edge, @ref CMP_Out_Detect_Edge */

    uint8_t u8OutFilter;            /*!< Output Filter, @ref CMP_Out_Filter */
}stc_cmp_init_t;

/**
 * @brief CMP reference voltage for window mode configuration structure
 */
typedef struct
{
    uint8_t u8CmpCh1;               /*!< Select the compare voltage channel for window mode
                                        @ref CMP_CVSL_Channal */
    uint16_t u16CmpVol;             /*!< Select the compare voltage source for window mode
                                        (Config the parameter when use CMP1 or CMP3)@ref CMP1_3_CVSL_Source */
    uint8_t u8CmpCh2;               /*!< Select the compare voltage channel for window mode
                                        @ref CMP_CVSL_Channal */
    uint8_t u8WinVolLow;            /*!< CMP reference low voltage for window mode
                                        @ref CMP_RVSL_Source */
    uint8_t u8WinVolHigh;           /*!< CMP reference high voltage for window mode
                                        @ref CMP_RVSL_Source */
}stc_cmp_win_ref_t;

/**
 * @brief CMP timer windows function configuration structure
 */
typedef struct
{
    uint16_t u16TWSelect;           /*!< Timer window source select
                                         @ref CMP_TimerWin_Select */
    uint8_t u8TWOutLevel;           /*!< Timer window mode output level
                                        @ref CMP_TimerWin_output_Level*/
    uint8_t u8TWInvalidLevel;       /*!< Output level when timer window invalid
                                        @ref CMP_TimerWin_Invalid_Level */
}stc_cmp_timerwindow_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Macros CMP Global Macros
 * @{
 */

#define CMP_TWSR_MASK           ((0xFFFFU)

/** @defgroup CMP_Mode CMP compare mode
  * @{
  */
#define CMP_MODE_NORMAL         (0x00U)                  /*!< Normal mode */
#define CMP_MODE_WINDOW         (CMP_MDR_CWDE)           /*!< Window mode */
/**
 * @}
 */

/** @defgroup CMP_CVSL_Channal CMP compare voltage channal selection
  * @{
  */
#define CMP_CVSL_NONE           (0x0U)                    /*!< Don't input compare voltage */
#define CMP_CVSL_INP1           (CMP_PMSR_CVSL_0)         /*!< Select INP1 as compare voltage */
#define CMP_CVSL_INP2           (CMP_PMSR_CVSL_1)         /*!< Select INP2 as compare voltage */
#define CMP_CVSL_INP3           (CMP_PMSR_CVSL_2)         /*!< Select INP3 as compare voltage */
#define CMP_CVSL_INP4           (CMP_PMSR_CVSL_3)         /*!< Select INP4 as compare voltage */
/**
 * @}
 */

/** @defgroup CMP_RVSL_Source CMP reference voltage selection
  * @{
  */
#define CMP_RVSL_NONE           (0x0U)                    /*!< Don't input reference voltage */
#define CMP_RVSL_INM1           (CMP_PMSR_RVSL_0)         /*!< Select INM1 as reference voltage */
#define CMP_RVSL_INM2           (CMP_PMSR_RVSL_1)         /*!< Select INM2 as reference voltage */
#define CMP_RVSL_INM3           (CMP_PMSR_RVSL_2)         /*!< Select INM3 as reference voltage */
#define CMP_RVSL_INM4           (CMP_PMSR_RVSL_3)         /*!< Select INM4 as reference voltage */
/**
 * @}
 */

/** @defgroup CMP1_3_CVSL_Source CMP1 CMP3 compare voltage selection
  * @{
  */
#define CMP1_INP3_NONE          (0x0U)                    /*!< Don't input voltage to CMP1 INP3 */
#define CMP1_INP3_CMP1_INP3     (CMP_VISR_P3SL_0)         /*!< Select CMP1_INP3 as CMP1 INP3 input */
#define CMP1_INP3_CMP2_INP3     (CMP_VISR_P3SL_1)         /*!< Select CMP2_INP3 as CMP1 INP3 input */
#define CMP1_INP2_NONE          (0x0U)                    /*!< Don't input voltage to CMP1 INP2 */
#define CMP1_INP2_PGA1          (CMP_VISR_P2SL_0)         /*!< Select PGA1 as CMP1 INP2 input */
#define CMP1_INP2_PGA2          (CMP_VISR_P2SL_1)         /*!< Select PGA2 as CMP1 INP2 input */
#define CMP1_INP2_CMP1_INP2     (CMP_VISR_P2SL_2)         /*!< Select CMP1_INP2 as CMP1 INP2 input */
#define CMP3_INP3_NONE          (0x0U)                    /*!< Don't input voltage to CMP3 INP3 */
#define CMP3_INP3_CMP3_INP3     (CMP_VISR_P3SL_0)         /*!< Select CMP3_INP3 as CMP3 INP3 input */
#define CMP3_INP3_CMP4_INP3     (CMP_VISR_P3SL_1)         /*!< Select CMP4_INP3 as CMP3 INP3 input */
#define CMP3_INP2_NONE          (0x0U)                    /*!< Don't input voltage to CMP3 INP2 */
#define CMP3_INP2_PGA3          (CMP_VISR_P2SL_0)         /*!< Select PGA3 as CMP3 INP2 input */
#define CMP3_INP2_PGA4          (CMP_VISR_P2SL_1)         /*!< Select PGA4 as CMP3 INP2 input */
#define CMP3_INP2_CMP3_INP2     (CMP_VISR_P2SL_2)         /*!< Select CMP3_INP2 as CMp3 INP2 input */
/**
 * @}
 */

/** @defgroup CMP_Out_Polarity_Select CMP output polarity selection
  * @{
  */
#define CMP_OUT_REVERSE_OFF     (0x0U)                    /*!< CMP output don't reverse */
#define CMP_OUT_REVERSE_ON      (CMP_OCR_COPS)            /*!< CMP output level reverse */
/**
 * @}
 */

/** @defgroup CMP_Out_Detect_Edge CMP output detect edge selection
  * @{
  */
#define CMP_DETECT_EDGS_NONE      (0U)                       /*!< Do not detect edge */
#define CMP_DETECT_EDGS_RISING    (1U << CMP_FIR_EDGS_POS)   /*!< Detect rising edge */
#define CMP_DETECT_EDGS_FALLING   (2U << CMP_FIR_EDGS_POS)   /*!< Detect falling edge */
#define CMP_DETECT_EDGS_BOTH      (3U << CMP_FIR_EDGS_POS)   /*!< Detect rising and falling edges */
/**
 * @}
 */

/** @defgroup CMP_Out_Filter CMP output filter configuration
  * @{
  */
#define CMP_OUT_FILTER_NONE         (0U)                  /*!< Do not filter */
#define CMP_OUT_FILTER_PCLK3        (1U)                  /*!< Use pclk3 */
#define CMP_OUT_FILTER_PCLK3_DIV8   (2U)                  /*!< Use pclk3/8 */
#define CMP_OUT_FILTER_PCLK3_DIV32  (3U)                  /*!< Use pclk3/32 */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_func CMP timer window function configuration
  * @{
  */
#define CMP_TIMERWIN_OFF            (0x0U)                /*!< Disable Timer Window function */
#define CMP_TIMERWIN_ON             (CMP_OCR_TWOE)        /*!< Enable Timer Window function */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Select CMP output timer windows function control signal definition for CMP1
  * @{
  */
#define CMP_TIMERWIN_TIMA_x_PWM1    (CMP_TWSR_CTWS0)       /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIMA_x_PWM2    (CMP_TWSR_CTWS1)       /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIMA_x_PWM3    (CMP_TWSR_CTWS2)       /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIMA_y_PWM1    (CMP_TWSR_CTWS3)       /*!< y = 2,3,4 */
#define CMP_TIMERWIN_TIMA_y_PWM2    (CMP_TWSR_CTWS4)       /*!< y = 2,3,4 */
#define CMP_TIMERWIN_TIMA_y_PWM3    (CMP_TWSR_CTWS5)       /*!< y = 2,3,4 */
#define CMP_TIMERWIN_TIM6_a_PWMb    (CMP_TWSR_CTWS6)       /*!< a = 1,5  b = A,B */
#define CMP_TIMERWIN_TIM6_c_PWMd    (CMP_TWSR_CTWS7)       /*!< c = 2,6  d = A,B */
#define CMP_TIMERWIN_TIM6_e_PWMf    (CMP_TWSR_CTWS8)       /*!< e = 3,7  f = A,B */
#define CMP_TIMERWIN_TIM6_g_PWMh    (CMP_TWSR_CTWS9)       /*!< g = 4,8  h = A,B */
#define CMP_TIMERWIN_TIM4_x_OUH     (CMP_TWSR_CTWS10)      /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIM4_x_OUL     (CMP_TWSR_CTWS11)      /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIM4_x_OVH     (CMP_TWSR_CTWS12)      /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIM4_x_OVL     (CMP_TWSR_CTWS13)      /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIM4_x_OWH     (CMP_TWSR_CTWS14)      /*!< x = 1,2,3 */
#define CMP_TIMERWIN_TIM4_x_OWL     (CMP_TWSR_CTWS15)      /*!< x = 1,2,3 */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Invalid_Level CMP output level when timer window invalid
  * @{
  */
#define CMP_TIMERWIN_INVALID_LEVEL_LOW   (0x0U)            /*!< Output Low when timer window invalid */
#define CMP_TIMERWIN_INVALID_LEVEL_HIGH  (CMP_OCR_TWOL)    /*!< Output High when timer window invalid */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_output_Level CMP output level in timer windows mode
  * @{
  */
#define CMP_TIMERWIN_OUT_LEVEL_LOW       (0U)              /*!< Output Low in timer windows mode */
#define CMP_TIMERWIN_OUT_LEVEL_HIGH      (1U)              /*!< Output High in timer windows mode */
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
 * @addtogroup CMP_Global_Functions
 * @{
 */
en_result_t CMP_StructInit(stc_cmp_init_t *pstcCMP_InitStruct);
en_result_t CMP_DeInit(M4_CMP_TypeDef *CMPx);
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                               const stc_cmp_init_t *pstcCmpInit);
en_result_t CMP_WindowModeInit(const M4_CMP_TypeDef *CMPx,
                               const stc_cmp_init_t *pstcCmpInit,
                               const stc_cmp_win_ref_t *pstcCmpWinRef);
en_result_t CMP_TimerWindowConfig(M4_CMP_TypeDef *CMPx,
                                  const stc_cmp_timerwindow_t *pstcCMP_TimerWinStruct);

void CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSttusa);
void CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_SetOutDetectEdges(M4_CMP_TypeDef *CMPx, uint8_t u8CmpEdges);
void CMP_SetOutputFilter(M4_CMP_TypeDef *CMPx, uint8_t u8CmpFilter);
void CMP_SetOutputPolarity(M4_CMP_TypeDef *CMPx, uint8_t u8CmpPolarity);
void CMP_SetCompareVol(M4_CMP_TypeDef *CMPx, uint8_t u8CmpCh, uint8_t u8CmpVol);
void CMP_SetRefVol(M4_CMP_TypeDef *CMPx, uint8_t u8RefVol);

en_flag_status_t CMP_GetResult(const M4_CMP_TypeDef *CMPx);
/**
 * @}
 */

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CMP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
