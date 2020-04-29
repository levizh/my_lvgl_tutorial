/**
 *******************************************************************************
 * @file  hc32f4a0_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-09        Heqb         First version
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
#include "hc32f4a0_cmp.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CMP CMP
 * @brief CMP Driver Library
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CMP_Local_Macros CMP Local Macros
 * @{
 */


/**
 * @defgroup CMP_Check_Parameters_Validity CMP Check Parameters Validity
 * @{
 */

#define IS_CMP_INSTANCE(x)                                                     \
(   ((x) == M4_CMP1)                            ||                             \
    ((x) == M4_CMP2)                            ||                             \
    ((x) == M4_CMP3)                            ||                             \
    ((x) == M4_CMP4))

#define IS_CMP_MODE(x)                                                         \
(   ((x) == CMP_MODE_NORMAL)                    ||                             \
    ((x) == CMP_MODE_WINDOW))

#define IS_CMP_CVSL_CH(x)                                                     \
(   ((x) == CMP_CVSL_NONE)                      ||                             \
    ((x) == CMP_CVSL_INP1)                      ||                             \
    ((x) == CMP_CVSL_INP2)                      ||                             \
    ((x) == CMP_CVSL_INP3)                      ||                             \
    ((x) == CMP_CVSL_INP4))

#define IS_CMP1_CVSL_SOURCE(x)                                                 \
(   ((x) == CMP1_INP3_NONE)                     ||                             \
    ((x) == CMP1_INP3_CMP1_INP3)                ||                             \
    ((x) == CMP1_INP3_CMP2_INP3)                ||                             \
    ((x) == CMP1_INP2_NONE)                     ||                             \
    ((x) == CMP1_INP2_PGA1)                     ||                             \
    ((x) == CMP1_INP2_PGA2)                     ||                             \
    ((x) == CMP1_INP2_CMP1_INP2))

#define IS_CMP3_CVSL_SOURCE(x)                                                 \
(   ((x) == CMP3_INP3_NONE)                     ||                             \
    ((x) == CMP3_INP3_CMP3_INP3)                ||                             \
    ((x) == CMP3_INP3_CMP4_INP3)                ||                             \
    ((x) == CMP3_INP2_NONE)                     ||                             \
    ((x) == CMP3_INP2_PGA3)                     ||                             \
    ((x) == CMP3_INP2_PGA4)                     ||                             \
    ((x) == CMP3_INP2_CMP3_INP2))

#define IS_CMP_RVSL(x)                                                         \
(   ((x) == CMP_RVSL_NONE)                      ||                             \
    ((x) == CMP_RVSL_INM1)                      ||                             \
    ((x) == CMP_RVSL_INM2)                      ||                             \
    ((x) == CMP_RVSL_INM3)                      ||                             \
    ((x) == CMP_RVSL_INM4))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   ((x) == CMP_OUT_REVERSE_OFF)                ||                             \
    ((x) == CMP_OUT_REVERSE_ON))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   ((x) == CMP_DETECT_EDGS_NONE)               ||                             \
    ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   ((x) == CMP_OUT_FILTER_NONE)                ||                             \
    ((x) == CMP_OUT_FILTER_PCLK)                ||                             \
    ((x) == CMP_OUT_FILTER_PCLKDIV8)            ||                             \
    ((x) == CMP_OUT_FILTER_PCLKDIV32))

#define IS_CMP_TIMWIN_FUNC(x)                                                  \
(   ((x) == CMP_TIMERWIN_OFF)                   ||                             \
    ((x) == CMP_TIMERWIN_ON))

#define IS_CMP_TIMWIN_SELECT(x)                                               \
(   (x) <= CMP_TWSR_MASK)

#define IS_CMP_TIMWIN_INVALIDLEVEL(x)                                          \
(   ((x) == CMP_TIMERWIN_INVALID_LEVEL_LOW)     ||                             \
    ((x) == CMP_TIMERWIN_INVALID_LEVEL_HIGH))

#define IS_CMP_TIMWIN_OUT_LEVEL(x)                                             \
(   ((x) == CMP_TIMERWIN_OUT_LEVEL_LOW)         ||                             \
    ((x) == CMP_TIMERWIN_OUT_LEVEL_HIGH))

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
static void CMP_Delay300ns(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Functions CMP Global Functions
 * @{
 */

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [in] pstcCMP_InitStruct     Pointer to a stc_cmp_init_t structure variable which will be initialized.
 *   @arg  See the struct @ref stc_cmp_init_t.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_StructInit(stc_cmp_init_t* pstcCMP_InitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;
    if (pstcCMP_InitStruct != NULL)
    {
        enRet = Ok;
        pstcCMP_InitStruct->u8CmpCh = CMP_CVSL_NONE;
        pstcCMP_InitStruct->u8RefVol = CMP_RVSL_NONE;
        pstcCMP_InitStruct->u8OutDetectEdges = CMP_DETECT_EDGS_NONE;
        pstcCMP_InitStruct->u8OutFilter = CMP_OUT_FILTER_NONE;
        pstcCMP_InitStruct->u8OutPolarity = CMP_OUT_REVERSE_OFF;
    }
    return enRet;
}

/**
 * @brief  De-initialize CMP unit
 * @param  [in] CMPx  Pointer to CMP instance register base,This
 * parameter can be one of the following values:
 *   @arg  M0P_CMP1:   CMP unit 1 instance register base
 *   @arg  M0P_CMP2:   CMP unit 2 instance register base
 *   @arg  M0P_CMP3:   CMP unit 3 instance register base
 *   @arg  M0P_CMP4:   CMP unit 4 instance register base
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_DeInit(M4_CMP_TypeDef *CMPx)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    CMPx->MDR = (uint8_t)0U;
    CMPx->FIR = (uint8_t)0U;
    CMPx->OCR = (uint8_t)0U;
    CMPx->PMSR = (uint8_t)0U;
    CMPx->VISR = (uint8_t)0U;
    CMPx->TWSR = (uint8_t)0U;
    CMPx->TWPR = (uint8_t)0U;
    enRet = Ok;
    return enRet;
}

/**
 * @brief  CMP normal mode initialize
 * @param  [in] CMPx   Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] pstcCmpInit     CMP function base parameter structure
 *   @arg  See the structure definition for @ref stc_cmp_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                                const stc_cmp_init_t* pstcCmpInit)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check CMPx instance and configuration structure*/
    if  (NULL != pstcCmpInit)
    {
        enRet = Ok;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_CVSL_CH(pstcCmpInit->u8CmpCh));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpInit->u8RefVol));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpInit->u8OutPolarity));

        /* Stop CMP compare */
        CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Set compare voltage */
        WRITE_REG8(CMPx->PMSR, pstcCmpInit->u8CmpCh);
        if((M4_CMP1 == CMPx) && ((pstcCmpInit->u8CmpCh == CMP_CVSL_INP2) ||
                                 (pstcCmpInit->u8CmpCh == CMP_CVSL_INP3)))
        {
            DDL_ASSERT(IS_CMP1_CVSL_SOURCE(pstcCmpInit->u16CmpVol));
            WRITE_REG8(CMPx->VISR, pstcCmpInit->u16CmpVol);
        }
        if((M4_CMP3 == CMPx) && ((pstcCmpInit->u8CmpCh == CMP_CVSL_INP2) ||
                                 (pstcCmpInit->u8CmpCh == CMP_CVSL_INP3)))
        {
            DDL_ASSERT(IS_CMP3_CVSL_SOURCE(pstcCmpInit->u16CmpVol));
            WRITE_REG8(CMPx->VISR, pstcCmpInit->u16CmpVol);
        }
        /* Set reference voltage */
        MODIFY_REG8(CMPx->PMSR, CMP_PMSR_RVSL, pstcCmpInit->u8RefVol);
        /* Delay 300ns*/
        CMP_Delay300ns();
        /* Start CMP compare */
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 300ns*/
        CMP_Delay300ns();

        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(CMPx->FIR, (pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges));
        WRITE_REG8(CMPx->OCR, pstcCmpInit->u8OutPolarity);
    }
    return enRet;
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] CMPx   Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   Select CMP1 CMP2 for window comparison
 *   @arg  M4_CMP2:   Select CMP1 CMP2 for window comparison
 *   @arg  M4_CMP3:   Select CMP3 CMP4 for window comparison
 *   @arg  M4_CMP4:   Select CMP3 CMP4 for window comparison
 * @param  [in] pstcCmpInit    Configuration structure for window mode initialize
 *   @arg  See the structure definition for @ref stc_cmp_init_t
 * @param  [in] pstcCmpWinRef  Configuration structure for window mode reference voltage
 *   @arg  See the structure definition for @ref stc_cmp_win_ref_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_WindowModeInit(M4_CMP_TypeDef *CMPx,
                                const stc_cmp_init_t* pstcCmpInit,
                                const stc_cmp_win_ref_t* pstcCmpWinRef)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check configuration structure */
    if (NULL != pstcCmpInit)
    {
        enRet = Ok;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpInit->u8OutPolarity));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpWinRef->u8WinVolLow));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpWinRef->u8WinVolHigh));
        if((CMPx == M4_CMP1) || (CMPx == M4_CMP2))
        {
            /* Stop CMP1 CMP2 compare */
            CLEAR_REG8_BIT(M4_CMP1->MDR, CMP_MDR_CENB);
            CLEAR_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CENB);
            /* Set compare voltage */
            WRITE_REG8(M4_CMP1->PMSR, pstcCmpInit->u8CmpCh);
            WRITE_REG8(M4_CMP1->VISR, pstcCmpInit->u16CmpVol);
            WRITE_REG8(M4_CMP2->PMSR, pstcCmpInit->u8CmpCh);
            /* Set reference Voltage */
            MODIFY_REG8(M4_CMP1->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolLow);
            MODIFY_REG8(M4_CMP2->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolHigh);
            /* Select window compare mode */
            SET_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CWDE);
            /* Start CMP compare function */
            SET_REG8_BIT(M4_CMP1->MDR, CMP_MDR_CENB);
            SET_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CENB);
            /* Delay 300ns*/
            CMP_Delay300ns();
            /* Set output filter and output detect edge and output polarity */
            WRITE_REG8(M4_CMP2->FIR, pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges);
            WRITE_REG8(M4_CMP2->OCR, pstcCmpInit->u8OutPolarity);
        }
        else
        {
            /* Stop CMP3 CMP4 compare */
            CLEAR_REG8_BIT(M4_CMP3->MDR, CMP_MDR_CENB);
            CLEAR_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CENB);
            /* Set compare voltage */
            WRITE_REG8(M4_CMP3->PMSR, pstcCmpInit->u8CmpCh);
            WRITE_REG8(M4_CMP3->VISR, pstcCmpInit->u16CmpVol);
            WRITE_REG8(M4_CMP4->PMSR, pstcCmpInit->u8CmpCh);
            /* Set reference Voltage */
            MODIFY_REG8(M4_CMP3->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolLow);
            MODIFY_REG8(M4_CMP4->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolHigh);
            /* Select window compare mode */
            SET_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CWDE);
            /* Start CMP compare function */
            SET_REG8_BIT(M4_CMP3->MDR, CMP_MDR_CENB);
            SET_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CENB);
            /* Delay 300ns*/
            CMP_Delay300ns();
            /* Set output filter and output detect edge and output polarity */
            WRITE_REG8(M4_CMP4->FIR, pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges);
            WRITE_REG8(M4_CMP4->OCR, pstcCmpInit->u8OutPolarity);
        }
    }
    return enRet;
}

/**
 * @brief  Voltage compare function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus     The function new status.
 * This parameter can be: Enable or Disable.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));

    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 300ns*/
        CMP_Delay300ns();
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Voltage compare interrupt function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));

    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Voltage compare output command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));

    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Voltage compare output port VCOUT function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   This parameter can be: Enable or Disable.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));

    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Voltage compare result flag read
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @retval In normal mode:
 *         Reset:     compare voltage < reference voltage
 *         Set:       compare voltage > reference voltage
 *         In Window mode:
 *         Reset:     compare voltage < reference low voltage or
 *                    compare voltage > reference high voltage
 *         Set:       compare voltage > reference low voltage and
 *                    compare voltage < reference high voltage
 */
en_flag_status_t CMP_GetResult(M4_CMP_TypeDef *CMPx)
{
    uint8_t enRet = 0U;
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    enRet = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CMON) ? Reset : Set;

    return (en_flag_status_t)enRet;
}

/**
 * @brief  Voltage compare timer window function configuration
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @retval Ok: Successfully
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_TimerWindowConfig(M4_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindows_t* pstcCMP_TimerWinStruct)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check CMPx instance and configuration structure*/
    if (NULL != pstcCMP_TimerWinStruct)
    {
        enRet = Ok;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_TIMWIN_INVALIDLEVEL(pstcCMP_TimerWinStruct->u8TWInvalidLevel));
        DDL_ASSERT(IS_CMP_TIMWIN_OUT_LEVEL(pstcCMP_TimerWinStruct->u8TWOutLevel));
        //DDL_ASSERT(IS_CMP_TIMWIN_SELECT(pstcCMP_TimerWinStruct->u16TWSelect));
        /* Select timer window mode */
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
        /* Select output level when timer window invalid */
        MODIFY_REG8(CMPx->OCR, CMP_OCR_TWOL, pstcCMP_TimerWinStruct->u8TWInvalidLevel);
        /* Selecet Timer window source  */
        WRITE_REG16(CMPx->TWSR, pstcCMP_TimerWinStruct->u16TWSelect);
        /* Select timer window mode output level */
        if(pstcCMP_TimerWinStruct->u8TWOutLevel)
        {
            SET_REG16_BIT(CMPx->TWPR, pstcCMP_TimerWinStruct->u16TWSelect);
        }
        else
        {
            CLEAR_REG16_BIT(CMPx->TWPR, pstcCMP_TimerWinStruct->u16TWSelect);
        }
    }
    return enRet;
}

/**
 * @brief  Set output detecte edge
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpEdges    CMP output detect edge selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_DETECT_EDGS_NONE:      Do not detect edge
 *   @arg  CMP_DETECT_EDGS_RISING:    Detect rising edge
 *   @arg  CMP_DETECT_EDGS_FALLING:   Detect falling edge
 *   @arg  CMP_DETECT_EDGS_BOTH:      Detect rising and falling edges
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_SetOutDetectEdges(M4_CMP_TypeDef *CMPx, uint8_t u8CmpEdges)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint8_t u8temp = 0U;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(u8CmpEdges));
    /* Read CMP status */
    u8temp = (CMPx->MDR & CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output detect edge selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_EDGS, u8CmpEdges);
    /* Recover CMP status */
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
    if(u8temp)
    {
        /* Delay 300ns */
        CMP_Delay300ns();
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set output filter
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpFilter    CMP output filter selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_OUT_FILTER_NONE:      Do not filter
 *   @arg  CMP_OUT_FILTER_PCLK:      Use pclk
 *   @arg  CMP_OUT_FILTER_PCLKDIV8:  Use pclk/8
 *   @arg  CMP_OUT_FILTER_PCLKDIV32: Use pclk/32
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_SetOutputFilter(M4_CMP_TypeDef *CMPx, uint8_t u8CmpFilter)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint8_t u8temp = 0U;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_FILTER(u8CmpFilter));
    /* Read CMP status */
    u8temp = (CMPx->MDR & CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output filter selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_FCKS, u8CmpFilter);
    /* Recover CMP status */
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
    if(u8temp)
    {
        /* Delay 300ns */
        CMP_Delay300ns();
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set output polarity
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpPolarity    CMP output polarity selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_OUT_REVERSE_OFF:      CMP output don't reverse
 *   @arg  CMP_OUT_REVERSE_ON:       CMP output level reverse
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_SetOutputPolarity(M4_CMP_TypeDef *CMPx, uint8_t u8CmpPolarity)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint8_t u8temp = 0U;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_POLARITY(u8CmpPolarity));
    /* Read CMP status */
    u8temp = (CMPx->MDR & CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output polarity selection */
    MODIFY_REG8(CMPx->OCR, CMP_OCR_COPS, u8CmpPolarity);
    /* Recover CMP status */
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
    if(u8temp)
    {
        /* Delay 300ns */
        CMP_Delay300ns();
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set compare voltage
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpCh    Select the compare voltage.
 *   This parameter can be one of the following values:
 *   @arg  CMP_CVSL_NONE:      Don't input compare voltage
 *   @arg  CMP_CVSL_INP1:      Select INP1 as compare voltage
 *   @arg  CMP_CVSL_INP2:      Select INP2 as compare voltage
 *   @arg  CMP_CVSL_INP3:      Select INP3 as compare voltage
 *   @arg  CMP_CVSL_INP4:      Select INP4 as compare voltage
 * @param  [in] u8CmpVol   Select the compare voltage source (Config the parameter when use CMP1 or CMP3)
 *   This parameter can be one of the following values:
 *   When use CMP1:
 *   @arg  CMP1_INP3_NONE       Don't input voltage to CMP1 INP3
 *   @arg  CMP1_INP3_CMP1_INP3  Select CMP1_INP3 as CMP1 INP3 input
 *   @arg  CMP1_INP3_CMP2_INP3  Select CMP2_INP3 as CMP1 INP3 input
 *   @arg  CMP1_INP2_NONE       Don't input voltage to CMP1 INP2
 *   @arg  CMP1_INP2_PGA1       Select PGA1 as CMP1 INP2 input
 *   @arg  CMP1_INP2_PGA2       Select PGA2 as CMP1 INP2 input
 *   @arg  CMP1_INP2_CMP1_INP2  Select CMP1_INP2 as CMP1 INP2 input
 *   When use CMP3:
 *   @arg  CMP3_INP3_NONE       Don't input voltage to CMP3 INP3
 *   @arg  CMP3_INP3_CMP3_INP3  Select CMP3_INP3 as CMP3 INP3 input
 *   @arg  CMP3_INP3_CMP4_INP3  Select CMP4_INP3 as CMP3 INP3 input
 *   @arg  CMP3_INP2_NONE       Don't input voltage to CMP3 INP2
 *   @arg  CMP3_INP2_PGA3       Select PGA3 as CMP3 INP2 input
 *   @arg  CMP3_INP2_PGA4       Select PGA4 as CMP3 INP2 input
 *   @arg  CMP3_INP2_CMP3_INP2  Select CMP3_INP2 as CMp3 INP2 input
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_SetCompaerVol(M4_CMP_TypeDef *CMPx, uint8_t u8CmpCh, uint8_t u8CmpVol)
{
    en_result_t  enRet = ErrorInvalidParameter;
    uint8_t u8temp = 0U;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_CVSL_CH(u8CmpCh));
    /* Read CMP status */
    u8temp = (CMPx->MDR & CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Set compare voltage */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_CVSL, u8CmpCh);
    if((M4_CMP1 == CMPx) && ((u8CmpCh == CMP_CVSL_INP2) || (u8CmpCh == CMP_CVSL_INP3)))
    {
        DDL_ASSERT(IS_CMP1_CVSL_SOURCE(u8CmpVol));
        WRITE_REG8(CMPx->VISR, u8CmpVol);
    }
    if((M4_CMP3 == CMPx) && ((u8CmpCh == CMP_CVSL_INP2) || (u8CmpCh == CMP_CVSL_INP3)))
    {
        DDL_ASSERT(IS_CMP3_CVSL_SOURCE(u8CmpVol));
        WRITE_REG8(CMPx->VISR, u8CmpVol);
    }
    /* Recover CMP status */
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
    if(u8temp)
    {
        /* Delay 300ns */
        CMP_Delay300ns();
    }
    enRet = Ok;

    return enRet;
}

/**
 * @brief  Set reference voltage
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8RefVol    Select the reference voltage.
 *   This parameter can be one of the following values:
 *   @arg  CMP_RVSL_NONE:      Don't input reference voltage
 *   @arg  CMP_RVSL_INM1:      Select INM1 as reference voltage
 *   @arg  CMP_RVSL_INM2:      Select INM2 as reference voltage
 *   @arg  CMP_RVSL_INM3:      Select INM3 as reference voltage
 *   @arg  CMP_RVSL_INM4:      Select INM4 as reference voltage
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_SetRefVol(M4_CMP_TypeDef *CMPx, uint8_t u8RefVol)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint8_t u8temp = 0U;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_RVSL(u8RefVol));
    /* Read CMP status */
    u8temp = (CMPx->MDR & CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Set reference voltage */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_RVSL, u8RefVol);
    /* Recover CMP status */
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
    if(u8temp)
    {
        /* Delay 300ns */
        CMP_Delay300ns();
    }
    enRet = Ok;

    return enRet;
}

/**
 * @}
 */

/**
 * @brief  Software delay 300ns.
 * @param  None
 * @retval None
 */
static void CMP_Delay300ns(void)
{
    for(uint32_t i=0U; i<(SystemCoreClock/3333333U + 1U); i++)
    {
        __NOP();
    }
}

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/