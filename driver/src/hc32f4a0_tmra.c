/**
 *******************************************************************************
 * @file  hc32f4a0_timera.c
 * @brief This file provides firmware functions to manage the TimerA.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_tmra.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TIMERA TIMERA
 * @brief TimerA Driver Library
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Local_Macros TimerA Local Macros
 * @{
 */

/**
 * @defgroup TMRA_Configuration_Bit_Mask TIMERA Configuration Bit Mask
 * @{
 */
#define TMRA_BCSTR_INIT_MSK                     (0x01F6UL)
#define TMRA_INT_TYPE_MSK                       (0x000F3000UL)
#define TMRA_BCSTR_INT_MSK                      (0x00003000UL)
#define TMRA_FLAG_MSK                           (0x000FC000UL)
#define TMRA_BCSTR_FLAG_MSK                     (0x0000C000UL)
#define TMRA_EVENT_TYPE_MSK                     (0xFUL)
#define TMRA_FCONR_FILTER_CFG_MSK               (0x7UL)
#define TMRA_FCONR_FILTER_CLK_MSK               (0x3UL)
#define TMRA_CCONR_FILTER_CFG_MSK               (TMRA_CCONR_NOFIENCP | TMRA_CCONR_NOFICKCP)
#define TMRA_CCONR_FILTER_CLK_MSK               (TMRA_CCONR_NOFICKCP)
#define TMRA_CAPT_COND_MSK                      (0x0370UL)
#define TMRA_PWM_POLARITY_MSK                   (0x03FFUL)
#define TMRA_START_COND_MSK                     (0x0007UL)
#define TMRA_STOP_COND_MSK                      (0x0070UL)
#define TMRA_CLR_COND_MSK                       (0xF700UL)
#define TMRA_TRIG_COND_MSK                      (TMRA_START_COND_MSK | TMRA_STOP_COND_MSK | TMRA_CLR_COND_MSK)
#define TMRA_CACHE_COND_MSK                     (TMRA_BCONR_BSE0 | TMRA_BCONR_BSE1)
#define TMRA_HW_CLK_MSK                         (0x1FFFUL)
#define TMRA_COM_EVENT_EN_MSK                   (TMRA_COM1_TRIG_ENABLE | TMRA_COM2_TRIG_ENABLE)
#define TMRA_TRIG_EVENT_MSK                     (AOS_TMRA_HTSSR0_TRGSEL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Unit_Index TIMERA Unit Index
 * @{
 */
#define __TMRA_BASE                             (0x4003A000UL)
#define __TMRA_UNIT_SIZE                        (0x400UL)
#define TMRA_IDX(__TMRAx__)                     (((uint32_t)&(__TMRAx__)->CNTER - __TMRA_BASE) / __TMRA_UNIT_SIZE)
/**
 * @}
 */

/**
 * @defgroup TMRA_Register_Bit_Band TIMERA Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                         (0x42000000UL)
#define __PERIP_BASE                            (0x40000000UL)
#define __REG_OFS(__reg__)                      ((uint32_t)&(__reg__) - __PERIP_BASE)
#define __BIT_BAND_ADDR(__reg__, __pos__)       ((__REG_OFS(__reg__) << 5U) + ((uint32_t)(__pos__) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(__reg__, __pos__)              (*(__IO uint32_t *)__BIT_BAND_ADDR((__reg__), (__pos__)))
/**
 * @}
 */

/**
 * @defgroup TMRA_HTSSR_Address TMRA HTSSR Address
 * @{
 */
#define TMRA_HTSSR0_ADDR                        (0x40010880UL)
#define TMRA_HTSSR1_ADDR                        (0x40010884UL)
#define TMRA_HTSSR2_ADDR                        (0x40010888UL)
#define TMRA_HTSSR3_ADDR                        (0x4001088CUL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Check_Parameters_Validity TIMERA check parameters validity
 * @{
 */
#define IS_TMRA_UNIT(x)                                                        \
(   ((x) == M4_TMRA_1)                      ||                                 \
    ((x) == M4_TMRA_2)                      ||                                 \
    ((x) == M4_TMRA_3)                      ||                                 \
    ((x) == M4_TMRA_4)                      ||                                 \
    ((x) == M4_TMRA_5)                      ||                                 \
    ((x) == M4_TMRA_6)                      ||                                 \
    ((x) == M4_TMRA_7)                      ||                                 \
    ((x) == M4_TMRA_8)                      ||                                 \
    ((x) == M4_TMRA_9)                      ||                                 \
    ((x) == M4_TMRA_10)                     ||                                 \
    ((x) == M4_TMRA_11)                     ||                                 \
    ((x) == M4_TMRA_12))

#define IS_TMRA_CH(x)                                                          \
(   ((x) <= TMRA_CH_4))

#define IS_TMRA_FUNC_MODE(x)                                                   \
(   ((x) == TMRA_FUNC_COMPARE)              ||                                 \
    ((x) == TMRA_FUNC_CAPTURE))

#define IS_TMRA_1_BIT_MSK(x)                                                   \
(   ((x) != 0U)                             &&                                 \
    (((x) & ((x) - 1U)) == 0U))

#define IS_TMRA_BIT_MSK(x, msk)                                                \
(   ((x) != 0U)                             &&                                 \
    (((x) | (msk)) == (msk)))

#define IS_TMRA_PCLK_DIV(x)                                                    \
(   ((x) == TMRA_PCLK_DIV_1)                ||                                 \
    ((x) == TMRA_PCLK_DIV_2)                ||                                 \
    ((x) == TMRA_PCLK_DIV_4)                ||                                 \
    ((x) == TMRA_PCLK_DIV_8)                ||                                 \
    ((x) == TMRA_PCLK_DIV_16)               ||                                 \
    ((x) == TMRA_PCLK_DIV_32)               ||                                 \
    ((x) == TMRA_PCLK_DIV_64)               ||                                 \
    ((x) == TMRA_PCLK_DIV_128)              ||                                 \
    ((x) == TMRA_PCLK_DIV_256)              ||                                 \
    ((x) == TMRA_PCLK_DIV_512)              ||                                 \
    ((x) == TMRA_PCLK_DIV_1024))

#define IS_TMRA_CNT_DIR(x)                                                     \
(   ((x) == TMRA_DIR_DOWN)                  ||                                 \
    ((x) == TMRA_DIR_UP))

#define IS_TMRA_CNT_MODE(x)                                                    \
(   ((x) == TMRA_MODE_SAWTOOTH)             ||                                 \
    ((x) == TMRA_MODE_TRIANGLE))

#define IS_TMRA_OVF_OPERATION(x)                                               \
(   ((x) == TMRA_OVF_KEEP_CNT)              ||                                 \
    ((x) == TMRA_OVF_STOP))

#define IS_TMRA_FILTER_CLK_DIV(x)                                              \
(   ((x) <= TMRA_FILTER_CLK_DIV_64))

#define IS_TMRA_CACHE_COND(x)                                                  \
(   ((x) == TMRA_CACHE_COND_OVF_CLR)        ||                                 \
    ((x) == TMRA_CACHE_COND_TW_VALLEY)      ||                                 \
    ((x) == TMRA_CACHE_COND_TW_PEAK))

#define IS_TMRA_PWM_START_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_START_LOW)             ||                                 \
    ((x) == TMRA_PWM_START_HI)              ||                                 \
    ((x) == TMRA_PWM_START_KEEP))

#define IS_TMRA_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMRA_PWM_STOP_LOW)              ||                                 \
    ((x) == TMRA_PWM_STOP_HI)               ||                                 \
    ((x) == TMRA_PWM_STOP_KEEP))

#define IS_TMRA_PWM_CM_POLARITY(x)                                             \
(   ((x) == TMRA_PWM_CM_LOW)                ||                                 \
    ((x) == TMRA_PWM_CM_HI)                 ||                                 \
    ((x) == TMRA_PWM_CM_KEEP)               ||                                 \
    ((x) == TMRA_PWM_CM_REVERSE))

#define IS_TMRA_PWM_PM_POLARITY(x)                                             \
(   ((x) == TMRA_PWM_PM_LOW)                ||                                 \
    ((x) == TMRA_PWM_PM_HI)                 ||                                 \
    ((x) == TMRA_PWM_PM_KEEP)               ||                                 \
    ((x) == TMRA_PWM_PM_REVERSE))

#define IS_TMRA_PWM_FORCE_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_FORCE_INVALID)         ||                                 \
    ((x) == TMRA_PWM_FORCE_LOW)             ||                                 \
    ((x) == TMRA_PWM_FORCE_HI))

#define IS_TMRA_CAPT_COND(x)                                                   \
(   ((x) == TMRA_CAPT_COND_INVALID)         ||                                 \
    ((x) == TMRA_CAPT_COND_PWMR)            ||                                 \
    ((x) == TMRA_CAPT_COND_PWMF)            ||                                 \
    ((x) == TMRA_CAPT_COND_EVENT)           ||                                 \
    ((x) == TMRA_CAPT_COND_TRIGR)           ||                                 \
    ((x) == TMRA_CAPT_COND_TRIGF))

/**
 * @}
 */

/**
 * @defgroup TMRA_Miscellaneous_Macros TIMERA Miscellaneous Macros
 * @{
 */
#define TMRA_CH_COUNT                       (4U)
#define TMRA_PIN_PWM_OFFSET                 (TMRA_PIN_PWM1)
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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Functions TimerA Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified TIMERA peripheral according to the specified parameters \
 *         in the structure stc_tmra_init_t
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  pstcInit               Pointer to a stc_tmra_init_t structure value that \
 *                                      contains the configuration information for the TIMERA.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMRAx == NULL.
 *                                     -pstcInit == NULL.
 */
en_result_t TMRA_Init(M4_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcInit)
{
    uint32_t u32Cfg = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMRAx != NULL) && (pstcInit != NULL))
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CNT_DIR(pstcInit->u32CntDir));
        DDL_ASSERT(IS_TMRA_CNT_MODE(pstcInit->u32CntMode));
        DDL_ASSERT(IS_TMRA_OVF_OPERATION(pstcInit->u32CntOvfOp));

        if (pstcInit->u32ClkSrc == TMRA_CLK_PCLK)
        {
            DDL_ASSERT(IS_TMRA_PCLK_DIV(pstcInit->u32PCLKDiv));
            u32Cfg = pstcInit->u32PCLKDiv | pstcInit->u32CntDir | pstcInit->u32CntMode;
        }
        else
        {
            WRITE_REG32(TMRAx->HCUPR, (pstcInit->u32ClkSrc & TMRA_CLK_HW_UP_ALL));
            WRITE_REG32(TMRAx->HCDOR, ((pstcInit->u32ClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U));
        }

        u32Cfg |= pstcInit->u32CntOvfOp;

        MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_INIT_MSK, u32Cfg);
        WRITE_REG32(TMRAx->PERAR, pstcInit->u32PeriodVal);
        WRITE_REG32(TMRAx->CNTER, pstcInit->u32CntVal);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the TIMERA initialization structure.
 * @param  [in]  pstcInit               Pointer to a stc_tmra_init_t structure value that \
 *                                      contains the configuration information for the TIMERA.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t TMRA_StructInit(stc_tmra_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u32ClkSrc    = TMRA_CLK_PCLK;
        pstcInit->u32PCLKDiv   = TMRA_PCLK_DIV_1;
        pstcInit->u32CntDir    = TMRA_DIR_UP;
        pstcInit->u32CntMode   = TMRA_MODE_SAWTOOTH;
        pstcInit->u32CntOvfOp  = TMRA_OVF_KEEP_CNT;
        pstcInit->u32PeriodVal = 0xFFFFU;
        pstcInit->u32CntVal    = 0U;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the TIMERA peripheral. Reset all registers of the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_DeInit(M4_TMRA_TypeDef *TMRAx)
{
    uint32_t i;
    uint32_t u32AddrOffset;
    uint32_t u32CMPARAddr;
    uint32_t u32CCONRAddr;
    uint32_t u32PCONRAddr;

    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32CMPARAddr = (uint32_t)TMRAx->CMPAR1;
        u32CCONRAddr = (uint32_t)TMRAx->CCONR1;
        u32PCONRAddr = (uint32_t)TMRAx->PCONR1;

        for (i=0U; i<TMRA_CH_COUNT; i++)
        {
            u32AddrOffset = i * 4U;
            RW_MEM32(u32CMPARAddr + u32AddrOffset) = (uint32_t)0xFFFFU;
            RW_MEM32(u32CCONRAddr + u32AddrOffset) = (uint32_t)0x0U;
            RW_MEM32(u32PCONRAddr + u32AddrOffset) = (uint32_t)0x0U;
        }

        WRITE_REG32(TMRAx->CNTER, 0x0U);
        WRITE_REG32(TMRAx->PERAR, 0xFFFFU);
        WRITE_REG32(TMRAx->BCSTR, 0x2U);
        WRITE_REG32(TMRAx->ICONR, 0x0U);
        WRITE_REG32(TMRAx->ECONR, 0x0U);
        WRITE_REG32(TMRAx->FCONR, 0x0U);
        WRITE_REG32(TMRAx->STFLR, 0x0U);
        WRITE_REG32(TMRAx->BCONR1, 0x0U);
        WRITE_REG32(TMRAx->BCONR2, 0x0U);
        WRITE_REG32(TMRAx->HCONR, 0x0U);
        WRITE_REG32(TMRAx->HCUPR, 0x0U);
        WRITE_REG32(TMRAx->HCDOR, 0x0U);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set general count value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Val                 The general count value to be set.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetCntVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        TMRAx->CNTER = u32Val;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get general count value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type type value of general count value.
 */
uint32_t TMRA_GetCntVal(const M4_TMRA_TypeDef *TMRAx)
{
    uint32_t u32Ret = 0U;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        u32Ret = TMRAx->CNTER;
    }

    return u32Ret;
}

/**
 * @brief  Set period reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Val                 The period reference value to be set.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetPeriodVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        TMRAx->PERAR = u32Val;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get period reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type type value of period reference value.
 */
uint32_t TMRA_GetPeriodVal(const M4_TMRA_TypeDef *TMRAx)
{
    uint32_t u32Ret = 0U;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        u32Ret = TMRAx->PERAR;
    }

    return u32Ret;
}

/**
 * @brief  Specify the function mode of the specified TIMERA channle.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32FuncMode            Function mode of TIMERA.
 *                                      This parameter can be a value of @ref TMRA_Function_Mode
 *   @arg  TMRA_FUNC_COMPARE:           The function mode of TIMERA is comparison ouput.
 *   @arg  TMRA_FUNC_CAPTURE:           The function mode of TIMERA is capture the input.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetFuncMode(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32FuncMode)
{
    uint32_t u32CCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_FUNC_MODE(u32FuncMode));

        u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
        BIT_BAND(RW_MEM32(u32CCONRAddr), TMRA_CCONR_CAPMD_POS) = (uint32_t)u32FuncMode;
    }

    return enRet;
}

/**
 * @brief  Set compare reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Val                 The comparison reference value to be set.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetCmpVal(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Val)
{
    uint32_t u32CMPARAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + (uint32_t)u8TmrCh * 4U;
        RW_MEM32(u32CMPARAddr) = u32Val;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get compare reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @retval An uint32_t type type value of comparison reference value.
 */
uint32_t TMRA_GetCmpVal(const M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh)
{
    uint32_t u32CMPARAddr;
    uint32_t u32Ret = 0U;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));

        u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + (uint32_t)u8TmrCh * 4U;
        u32Ret = RW_MEM32(u32CMPARAddr);
    }

    return u32Ret;
}

/**
 * @brief  Configures the specified channel's PWM of TIMERA according to the specified parameters
 *         in the structure stc_tmra_pwm_cfg_t.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  pstcCfg                Pointer to a stc_tmra_pwm_cfg_t structure value that
 *                                      contains the configuration information for the PWM.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMRAx == NULL.
 *                                     -pstcCfg == NULL
 */
en_result_t TMRA_PWM_Config(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, const stc_tmra_pwm_cfg_t *pstcCfg)
{
    uint32_t u32Cfg;
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMRAx != NULL) && (pstcCfg != NULL))
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_START_POLARITY(pstcCfg->u32StartPolarity));
        DDL_ASSERT(IS_TMRA_PWM_STOP_POLARITY(pstcCfg->u32StopPolarity));
        DDL_ASSERT(IS_TMRA_PWM_CM_POLARITY(pstcCfg->u32CMPolarity));
        DDL_ASSERT(IS_TMRA_PWM_PM_POLARITY(pstcCfg->u32PMPolarity));
        DDL_ASSERT(IS_TMRA_PWM_FORCE_POLARITY(pstcCfg->u32ForcePolarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        u32Cfg = pstcCfg->u32StartPolarity | \
                 pstcCfg->u32StopPolarity  | \
                 pstcCfg->u32CMPolarity    | \
                 pstcCfg->u32PMPolarity    | \
                 pstcCfg->u32ForcePolarity;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PWM_POLARITY_MSK, u32Cfg);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the PWM configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_tmra_pwm_cfg_t structure value that
 *                                      contains the configuration information for the PWM.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u32StartPolarity = TMRA_PWM_START_HI;
        pstcCfg->u32StopPolarity  = TMRA_PWM_STOP_LOW;
        pstcCfg->u32CMPolarity    = TMRA_PWM_CM_REVERSE;
        pstcCfg->u32PMPolarity    = TMRA_PWM_PM_REVERSE;
        pstcCfg->u32ForcePolarity = TMRA_PWM_FORCE_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified channel's PWM output.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified channel's PWM output.
 *   @arg  Disable:                     Disable the specified channel's PWM output.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_Cmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        BIT_BAND(RW_MEM32(u32PCONRAddr), TMRA_PCONR_OUTEN_POS) = (uint32_t)enNewState;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the devision of filter's clock source for the specified TIMERA input pin.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32InputPin            The input pin of TIMERA.
 *                                      This parameter can be values of @ref TMRA_Input_Pin
 *   @arg  TMRA_PIN_TRIG:               Pin TIMA_<t>_TRIG.
 *   @arg  TMRA_PIN_CLKA:               Pin TIMA_<t>_PWM1/TIMA_<t>_CLKA.
 *   @arg  TMRA_PIN_CLKB:               Pin TIMA_<t>_PWM2/TIMA_<t>_CLKB.
 *   @arg  TMRA_PIN_PWM1:               Pin TIMA_<t>_PWM1.
 *   @arg  TMRA_PIN_PWM2:               Pin TIMA_<t>_PWM2.
 *   @arg  TMRA_PIN_PWM3:               Pin TIMA_<t>_PWM3.
 *   @arg  TMRA_PIN_PWM4:               Pin TIMA_<t>_PWM4.
 * @param  [in]  u32ClkDiv              The clock source division of the filter. Set it to zero while enNewState == Disable.
 *                                      This parameter can be a value of @ref TMRA_Filter_Clock_Divider
 *   @arg  TMRA_FILTER_CLK_DIV_1:       The filter clock is PCLK / 1.
 *   @arg  TMRA_FILTER_CLK_DIV_4:       The filter clock is PCLK / 4.
 *   @arg  TMRA_FILTER_CLK_DIV_16:      The filter clock is PCLK / 16.
 *   @arg  TMRA_FILTER_CLK_DIV_64:      The filter clock is PCLK / 64.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_FilterConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, uint32_t u32ClkDiv)
{
    uint8_t u8PinIdx = 0U;
    uint8_t u8TmrCh;
    uint32_t u32CfgMsk;
    uint32_t u32CCONRAddr;
    uint8_t au8Offset[] = {TMRA_FCONR_NOFICKTG_POS, TMRA_FCONR_NOFICKCA_POS, TMRA_FCONR_NOFICKCB_POS, \
                           TMRA_CCONR_NOFICKCP_POS, TMRA_CCONR_NOFICKCP_POS, TMRA_CCONR_NOFICKCP_POS, \
                           TMRA_CCONR_NOFICKCP_POS};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_FILTER_CLK_DIV(u32ClkDiv));

        u8InputPin &= TMRA_PIN_ALL;
        while (u8InputPin != 0U)
        {
            if ((u8InputPin & 0x1U) != 0U)
            {
                u32ClkDiv <<= au8Offset[u8PinIdx];
                if (u8PinIdx < TMRA_PIN_PWM_OFFSET)
                {
                    u32CfgMsk = (uint32_t)(TMRA_FCONR_FILTER_CLK_MSK << au8Offset[u8PinIdx]);
                    MODIFY_REG32(TMRAx->FCONR, u32CfgMsk, u32ClkDiv);
                }
                else
                {
                    u8TmrCh = u8PinIdx - TMRA_PIN_PWM_OFFSET;
                    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
                    MODIFY_REG32(RW_MEM32(u32CCONRAddr), TMRA_CCONR_FILTER_CLK_MSK, u32ClkDiv);
                }
            }
            u8InputPin >>= 1U;
            u8PinIdx++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the filter function of the specified TIMERA input pin.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32InputPin            The input pin of TIMERA.
 *                                      This parameter can be values of @ref TMRA_Input_Pin
 *   @arg  TMRA_PIN_TRIG:               Pin TIMA_<t>_TRIG.
 *   @arg  TMRA_PIN_CLKA:               Pin TIMA_<t>_PWM1/TIMA_<t>_CLKA.
 *   @arg  TMRA_PIN_CLKB:               Pin TIMA_<t>_PWM2/TIMA_<t>_CLKB.
 *   @arg  TMRA_PIN_PWM1:               Pin TIMA_<t>_PWM1.
 *   @arg  TMRA_PIN_PWM2:               Pin TIMA_<t>_PWM2.
 *   @arg  TMRA_PIN_PWM3:               Pin TIMA_<t>_PWM3.
 *   @arg  TMRA_PIN_PWM4:               Pin TIMA_<t>_PWM4.
 * @param  [in]  u32ClkDiv              The clock source division of the filter. Set it to zero while enNewState == Disable.
 *                                      This parameter can be a value of @ref TMRA_Filter_Clock_Divider
 *   @arg  TMRA_FILTER_CLK_DIV_1:       The filter clock is PCLK / 1.
 *   @arg  TMRA_FILTER_CLK_DIV_4:       The filter clock is PCLK / 4.
 *   @arg  TMRA_FILTER_CLK_DIV_16:      The filter clock is PCLK / 16.
 *   @arg  TMRA_FILTER_CLK_DIV_64:      The filter clock is PCLK / 64.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified pin's filter.
 *   @arg  Disable:                     Disable the specified pin's filter.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, en_functional_state_t enNewState)
{
    uint8_t u8PinIdx = 0U;
    uint8_t u8TmrCh;
    uint32_t u32CCONRAddr;
    uint8_t au8Offset[] = {TMRA_FCONR_NOFIENTG_POS, TMRA_FCONR_NOFIENCA_POS, TMRA_FCONR_NOFIENCB_POS, \
                           TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, \
                           TMRA_CCONR_NOFIENCP_POS};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u8InputPin &= TMRA_PIN_ALL;
        while (u8InputPin != 0U)
        {
            if ((u8InputPin & 0x1U) != 0U)
            {
                if (u8PinIdx < TMRA_PIN_PWM_OFFSET)
                {
                    u32CCONRAddr = (uint32_t)&TMRAx->FCONR;
                }
                else
                {
                    u8TmrCh = u8PinIdx - TMRA_PIN_PWM_OFFSET;
                    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
                }
                BIT_BAND(RW_MEM32(u32CCONRAddr), au8Offset[u8PinIdx]) = enNewState;
            }
            u8InputPin >>= 1U;
            u8PinIdx++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the capture condition for the specified channel.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Cond                The capture condition. Set this parameter to 0xFFFF to select all the conditions of capturing start.
 *                                      This parameter can be values of @ref TMRA_Channel_Capture_Condition
 *   @arg  TMRA_CAPT_COND_INVALID:      The condition of capture is INVALID.
 *   @arg  TMRA_CAPT_COND_PWMR:         The condition of capture is a rising edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_PWMF:         The condition of capture is a falling edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_EVENT:        The condition of capture is the specified event occurred.
 *   @arg  TMRA_CAPT_COND_TRIGR:        The condition of capture is a rising edge is sampled on TRIG.
 *   @arg  TMRA_CAPT_COND_TRIGF:        The condition of capture is a falling edge is sampled on TRIG.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetCaptCond(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Cond)
{
    uint32_t u32CCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));

        u32Cond &= TMRA_CAPT_COND_MSK;
        u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32CCONRAddr), TMRA_CAPT_COND_MSK, u32Cond);
    }

    return enRet;
}

/**
 * @brief  Specify the hardware trigger condition of TIMERA according to the specified parameters
 *         in the structure stc_tmra_trig_cond_t.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  pstcCond               Pointer to a stc_tmra_trig_cond_t structure value that contains \
 *                                      the configuration information of hardware trigger condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:      -TMRAx == NULL.
 *                                     -pstcCond == NULL.
 */
en_result_t TMRA_SetTrigCond(M4_TMRA_TypeDef *TMRAx, const stc_tmra_trig_cond_t *pstcCond)
{
    uint32_t u32StartCond;
    en_result_t enRet = ErrorInvalidParameter;

    if ((TMRAx != NULL) && (pstcCond != NULL))
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32StartCond = (pstcCond->u32StartCond | pstcCond->u32StopCond | pstcCond->u32ClrCond) & TMRA_TRIG_COND_MSK;
        WRITE_REG32(TMRAx->HCONR, u32StartCond);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the hardware trigger condition configuration structure.
 * @param  [in]  pstcCond               Pointer to a stc_tmra_trig_cond_t structure value that contains \
 *                                      the configuration information of hardware trigger condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMRA_TrigCondStructInit(stc_tmra_trig_cond_t *pstcCond)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        pstcCond->u32StartCond = TMRA_START_COND_INVALID;
        pstcCond->u32StopCond  = TMRA_STOP_COND_INVALID;
        pstcCond->u32ClrCond   = TMRA_CLR_COND_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the event that is used to trigger counting.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  enEvent                An en_event_src_t enumeration type value.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 * @note Correspondence of TIMERA instances and the event setting registers is as follows:
 *      -TIMERA uint1  ---- TMRA_HTSSR0
 *      -TIMERA uint2  ---- TMRA_HTSSR1
 *      -TIMERA uint3  ---- TMRA_HTSSR2
 *      -TIMERA uint4  ---- TMRA_HTSSR3
 *      -TIMERA uint5  ---- TMRA_HTSSR0
 *      -TIMERA uint6  ---- TMRA_HTSSR1
 *      -TIMERA uint7  ---- TMRA_HTSSR2
 *      -TIMERA uint8  ---- TMRA_HTSSR3
 *      -TIMERA uint9  ---- TMRA_HTSSR0
 *      -TIMERA uint10 ---- TMRA_HTSSR1
 *      -TIMERA uint11 ---- TMRA_HTSSR2
 *      -TIMERA uint12 ---- TMRA_HTSSR3
 */
en_result_t TMRA_SetCntEvent(M4_TMRA_TypeDef *TMRAx, en_event_src_t enEvent)
{
    uint32_t u32Idx;
    uint32_t u32HTSSRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
        u32HTSSRAddr = (uint32_t)&M4_AOS->TMRA_HTSSR0 + u32Idx * 4U;
        MODIFY_REG32(RW_MEM32(u32HTSSRAddr), TMRA_TRIG_EVENT_MSK, enEvent);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the event that is used to trigger capturing.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  enEvent                An en_event_src_t enumeration type value.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 * @note Correspondence of TIMERA instances and the event setting registers is as follows:
 *      -TIMERA uint1  ---- TMRA_HTSSR1
 *      -TIMERA uint2  ---- TMRA_HTSSR0
 *      -TIMERA uint3  ---- TMRA_HTSSR3
 *      -TIMERA uint4  ---- TMRA_HTSSR2
 *      -TIMERA uint5  ---- TMRA_HTSSR1
 *      -TIMERA uint6  ---- TMRA_HTSSR0
 *      -TIMERA uint7  ---- TMRA_HTSSR3
 *      -TIMERA uint8  ---- TMRA_HTSSR2
 *      -TIMERA uint9  ---- TMRA_HTSSR1
 *      -TIMERA uint10 ---- TMRA_HTSSR0
 *      -TIMERA uint11 ---- TMRA_HTSSR3
 *      -TIMERA uint12 ---- TMRA_HTSSR2
 */
en_result_t TMRA_SetCaptEvent(M4_TMRA_TypeDef *TMRAx, en_event_src_t enEvent)
{
    uint32_t u32Idx;
    uint32_t au32HTSSRAddr[] = {TMRA_HTSSR1_ADDR, TMRA_HTSSR0_ADDR, \
                                TMRA_HTSSR3_ADDR, TMRA_HTSSR2_ADDR};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
        MODIFY_REG32(RW_MEM32(au32HTSSRAddr[u32Idx]), TMRA_TRIG_EVENT_MSK, enEvent);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the event for specified usage.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8EvtUsage             Usage of the event.
 *                                      This parameter can be a value of @ref TMRA_Event_Usage
 *   @arg  TMRA_EVENT_USAGE_CNT:        The specified event is used for counting.
 *   @arg  TMRA_EVENT_USAGE_CAPT:       The specified event is used for capturing.
 * @param  [in]  enEvent                An en_event_src_t enumeration type value.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 * @note Correspondence of TIMERA instances and the event setting registers is as follows:
 *      -TIMERA uint1  ---- TMRA_HTSSR1
 *      -TIMERA uint2  ---- TMRA_HTSSR0
 *      -TIMERA uint3  ---- TMRA_HTSSR3
 *      -TIMERA uint4  ---- TMRA_HTSSR2
 *      -TIMERA uint5  ---- TMRA_HTSSR1
 *      -TIMERA uint6  ---- TMRA_HTSSR0
 *      -TIMERA uint7  ---- TMRA_HTSSR3
 *      -TIMERA uint8  ---- TMRA_HTSSR2
 *      -TIMERA uint9  ---- TMRA_HTSSR1
 *      -TIMERA uint10 ---- TMRA_HTSSR0
 *      -TIMERA uint11 ---- TMRA_HTSSR3
 *      -TIMERA uint12 ---- TMRA_HTSSR2
 */
en_result_t TMRA_SetTrigEvent(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, en_event_src_t enEvent)
{
    uint32_t u32Idx;
    uint32_t u32HTSSRAddr;
    uint32_t au32CaptEventAddr[] = {TMRA_HTSSR1_ADDR, TMRA_HTSSR0_ADDR, \
                                    TMRA_HTSSR3_ADDR, TMRA_HTSSR2_ADDR};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT((u8EvtUsage == TMRA_EVENT_USAGE_CNT) || (u8EvtUsage == TMRA_EVENT_USAGE_CAPT));

        u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
        if (u8EvtUsage == TMRA_EVENT_USAGE_CNT)
        {
            u32HTSSRAddr = (uint32_t)&M4_AOS->TMRA_HTSSR0 + u32Idx * 4U;
        }
        else
        {
            u32HTSSRAddr = au32CaptEventAddr[u32Idx];
        }

        MODIFY_REG32(RW_MEM32(u32HTSSRAddr), TMRA_TRIG_EVENT_MSK, enEvent);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable common trigger event for the specified usage.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8EvtUsage             Usage of the event.
 *                                      This parameter can be a value of @ref TMRA_Event_Usage
 *   @arg  TMRA_EVENT_USAGE_CNT:        The specified event is used for counting.
 *   @arg  TMRA_EVENT_USAGE_CAPT:       The specified event is used for capturing.
 * @param  [in]  u32ComTrigEn           Common trigger event enable bit mask.
 *                                      This parameter can be values of @ref TMRA_Common_Trigger_Event_Command
 *   @arg  ADC_COM1_TRIG_DISABLE:       Enable common trigger event 1 for the specified usage.
 *   @arg  ADC_COM2_TRIG_DISABLE:       Enable common trigger event 2 for the specified usage.
 *   @arg  ADC_COM1_TRIG_ENABLE:        Disable common trigger event 1 for the specified usage.
 *   @arg  ADC_COM2_TRIG_ENABLE:        Disable common trigger event 2 for the specified usage.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_ComTrigCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, uint32_t u32ComTrigEn)
{
    uint32_t u32Idx;
    uint32_t u32HTSSRAddr;
    uint32_t au32CaptEventAddr[] = {TMRA_HTSSR1_ADDR, TMRA_HTSSR0_ADDR, \
                                    TMRA_HTSSR3_ADDR, TMRA_HTSSR2_ADDR};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT((u8EvtUsage == TMRA_EVENT_USAGE_CNT) || (u8EvtUsage == TMRA_EVENT_USAGE_CAPT));

        u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
        if (u8EvtUsage == TMRA_EVENT_USAGE_CNT)
        {
            u32HTSSRAddr = (uint32_t)&M4_AOS->TMRA_HTSSR0 + u32Idx * 4U;
        }
        else
        {
            u32HTSSRAddr = au32CaptEventAddr[u32Idx];
        }

        u32ComTrigEn &= TMRA_COM_EVENT_EN_MSK;
        MODIFY_REG32(RW_MEM32(u32HTSSRAddr), TMRA_COM_EVENT_EN_MSK, u32ComTrigEn);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures cache function. Specify the cache condition of compare value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be one of the following values of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 * @param  [in]  u32CacheCond           Cache condition of the specified TIMERA unit.
 *                                      This parameter can be a value of @ref TMRA_Cmp_Value_Cache_Condition
 *   @arg  TIEMRA_CACHE_POS_OVF_CLR:    This configuration value applies to non-triangular wave counting mode. \
 *                                      When counting overflow or underflow or counting register was cleared, \
 *                                      transfer CMPARm(m=2,4) to CMPARn(n=1,3).
 *   @arg  TMRA_CACHE_POS_TW_PEAK:      In triangle wave count mode, when count reached peak, \
 *                                      transfer CMMARm(m=2,4) to CMMARn(n=1,3).
 *   @arg  TMRA_CACHE_POS_TW_VALLEY:    In triangle wave count mode, when count reached valley, \
 *                                      transfer CMMARm(m=2,4) to CMMARn(n=1,3).
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_CmpValCacheConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CacheCond)
{
    uint32_t u32BCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT((u8TmrCh == TMRA_CH_1) || (u8TmrCh == TMRA_CH_3));
        DDL_ASSERT(IS_TMRA_CACHE_COND(u32CacheCond));

        u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32BCONRAddr), TMRA_CACHE_COND_MSK, u32CacheCond);
    }

    return enRet;
}

/**
 * @brief  Enable or disable the compare value function..
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be one of the following values of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the comparison reference value function.
 *   @arg  Disable:                     Disable the comparison reference value function.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_CmpValCacheCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState)
{
    uint32_t u32BCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT((u8TmrCh == TMRA_CH_1) || (u8TmrCh == TMRA_CH_3));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + (uint32_t)u8TmrCh * 4U;
        BIT_BAND(RW_MEM32(u32BCONRAddr), TMRA_BCONR_BEN_POS) = (uint32_t)enNewState;
    }

    return enRet;
}

/**
 * @brief  Specify the operation when counting overflow/underflow.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32OvfOp               The operation when count overflow/underflow.
 *   @arg  TMRA_OVF_KEEP_CNT:           When count overflow(or underflow), counting keep going.
 *   @arg  TMRA_OVF_STOP:               When count overflow(or underflow), counting stop.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetOvfOperation(M4_TMRA_TypeDef *TMRAx, uint32_t u32OvfOp)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_OVF_OPERATION(u32OvfOp));
        MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_OVSTP, u32OvfOp);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable synchronous start.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the synchronous start.
 *   @arg  Disable:                     Disable the synchronous start.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SyncStartCmd(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
        BIT_BAND(TMRAx->BCSTR, TMRA_BCSTR_SYNST_POS) = (uint32_t)enNewState;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable of disable the specified interrupts of the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32IntType             The interrupt type of TIMERA. Set this parameter to 0xFFFFFFFF to select all interrupts.
 *                                      This parameter can be values of @ref TMRA_Interrupt_Type
 *   @arg  TMRA_INT_OVF:                Count overflow interrupt.
 *   @arg  TMRA_INT_UNF:                Count underflow interrupt.
 *   @arg  TMRA_INT_CMP_CH1:            Compare-match interrupt of channel 1.
 *   @arg  TMRA_INT_CMP_CH2:            Compare-match interrupt of channel 2.
 *   @arg  TMRA_INT_CMP_CH3:            Compare-match interrupt of channel 3.
 *   @arg  TMRA_INT_CMP_CH4:            Compare-match interrupt of channel 4.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_IntCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32BCSTR;
    uint32_t u32ICONR;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32IntType &= TMRA_INT_TYPE_MSK;
        u32BCSTR    = u32IntType & TMRA_BCSTR_INT_MSK;
        u32ICONR    = u32IntType >> 16U;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMRAx->BCSTR, u32BCSTR);
            SET_REG32_BIT(TMRAx->ICONR, u32ICONR);
        }
        else
        {
            CLEAR_REG32_BIT(TMRAx->BCSTR, u32BCSTR);
            CLEAR_REG32_BIT(TMRAx->ICONR, u32ICONR);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable of disable the specified event of the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32EvtType             The event type of TIMERA. Set this parameter to 0xFFFF to select all events.
 *                                      This parameter can be values of @ref TMRA_Event_Type
 *   @arg  TMRA_EVENT_CMP_CH1:          Compare-match event of channel 1.
 *   @arg  TMRA_EVENT_CMP_CH2:          Compare-match event of channel 2.
 *   @arg  TMRA_EVENT_CMP_CH3:          Compare-match event of channel 3.
 *   @arg  TMRA_EVENT_CMP_CH4:          Compare-match event of channel 4.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified event.
 *   @arg  Disable:                     Disable the specified event.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_EventCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32EvtType, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32EvtType &= TMRA_EVENT_TYPE_MSK;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMRAx->ECONR, u32EvtType);
        }
        else
        {
            CLEAR_REG32_BIT(TMRAx->ECONR, u32EvtType);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the specified flag's status.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Flag                The status flags of TIMERA.
 *                                      This parameter can be a value of @ref TMRA_Status_Flag
 *   @arg  TMRA_FLAG_OVF:               Count overflow flag.
 *   @arg  TMRA_FLAG_UNF:               Count underflow flag.
 *   @arg  TMRA_FLAG_CMP_CH1:           Compare-match flag of channel 1.
 *   @arg  TMRA_FLAG_CMP_CH2:           Compare-match flag of channel 2.
 *   @arg  TMRA_FLAG_CMP_CH3:           Compare-match flag of channel 3.
 *   @arg  TMRA_FLAG_CMP_CH4:           Compare-match flag of channel 4.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg Set:                          The specified flag is set.
 *   @arg Reset:                        The specified flag is NOT set.
 */
en_flag_status_t TMRA_GetStatus(const M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    uint32_t u32BCSTR;
    uint32_t u32STFLR;
    en_flag_status_t enFlag = Reset;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_BIT_MSK(u32Flag, TMRA_FLAG_MSK));
        DDL_ASSERT(IS_TMRA_1_BIT_MSK(u32Flag));

        u32Flag &= TMRA_FLAG_MSK;
        u32BCSTR = TMRAx->BCSTR & (u32Flag & TMRA_BCSTR_FLAG_MSK);
        u32STFLR = TMRAx->STFLR & (u32Flag >> 16U);

        if ((u32BCSTR != 0U) || (u32STFLR != 0U))
        {
            enFlag = Set;
        }
    }

    return enFlag;
}

/**
 * @brief  Clear the specified flags' status.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Flag                The status flags of TIMERA. Set this parameter to 0xFFFFFFFF to select all status flags.
 *                                      This parameter can be values of @ref TMRA_Status_Flag
 *   @arg  TMRA_FLAG_OVF:               Count overflow flag.
 *   @arg  TMRA_FLAG_UNF:               Count underflow flag.
 *   @arg  TMRA_FLAG_MATCH_CH1:         Count match flag of channel 1.
 *   @arg  TMRA_FLAG_MATCH_CH2:         Count match flag of channel 2.
 *   @arg  TMRA_FLAG_MATCH_CH3:         Count match flag of channel 3.
 *   @arg  TMRA_FLAG_MATCH_CH4:         Count match flag of channel 4.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_ClrStatus(M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32Flag &= TMRA_FLAG_MSK;
        TMRAx->BCSTR &= (uint32_t)(~(u32Flag & TMRA_BCSTR_FLAG_MSK));
        TMRAx->STFLR &= (uint32_t)(~(u32Flag >> 16U));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Start the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_Start(M4_TMRA_TypeDef *TMRAx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        SET_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Stop the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_Stop(M4_TMRA_TypeDef *TMRAx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        CLEAR_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the counting direction for the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32CntDir              Count direction.
 *                                      This parameter can be a value of @ref TMRA_Count_Direction
 *   @arg  TMRA_DIR_DOWN:               TIMERA count goes down.
 *   @arg  TMRA_DIR_UP:                 TIMERA count goes up.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetCntDir(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntDir)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CNT_DIR(u32CntDir));

        MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_DIR, u32CntDir);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the counting mode for the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32CntDir              Count direction.
 *                                      This parameter can be a value of @ref TMRA_Count_Mode
 *   @arg  TMRA_MODE_SAWTOOTH:          Count mode is sawtooth wave.
 *   @arg  TMRA_MODE_TRIANGLE:          Count mode is triangle wave.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetCntMode(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntMode)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CNT_MODE(u32CntMode));

        BIT_BAND(TMRAx->BCSTR, TMRA_BCSTR_MODE_POS) = (uint32_t)u32CntMode;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the divider of PCLK when the clock source is PCLK.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32ClkDiv              The clock source division.
 *                                      This parameter can be a value of @ref TMRA_PCLK_Divider
 *   @arg  TMRA_PCLK_DIV_1:             The clock source of TIMERA is PCLK.
 *   @arg  TMRA_PCLK_DIV_2:             The clock source of TIMERA is PCLK / 2.
 *   @arg  TMRA_PCLK_DIV_4:             The clock source of TIMERA is PCLK / 4.
 *   @arg  TMRA_PCLK_DIV_8:             The clock source of TIMERA is PCLK / 8.
 *   @arg  TMRA_PCLK_DIV_16:            The clock source of TIMERA is PCLK / 16.
 *   @arg  TMRA_PCLK_DIV_32:            The clock source of TIMERA is PCLK / 32.
 *   @arg  TMRA_PCLK_DIV_64:            The clock source of TIMERA is PCLK / 64.
 *   @arg  TMRA_PCLK_DIV_128:           The clock source of TIMERA is PCLK / 128.
 *   @arg  TMRA_PCLK_DIV_256:           The clock source of TIMERA is PCLK / 256.
 *   @arg  TMRA_PCLK_DIV_512:           The clock source of TIMERA is PCLK / 512.
 *   @arg  TMRA_PCLK_DIV_1024:          The clock source of TIMERA is PCLK / 1024.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_SetPCLKDiv(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkDiv)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_PCLK_DIV(u32ClkDiv));

        MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_CKDIV, u32ClkDiv);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the counting direction of the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TIMERA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type value of counting direction.
 *   @arg  TMRA_DIR_DOWN:               TIMERA count goes down.
 *   @arg  TMRA_DIR_UP:                 TIMERA count goes up.
 *   @arg  0xFFFFFFFF:                  An invalid value when TMRAx is NULL.
 */
uint32_t TMRA_GetCntDir(M4_TMRA_TypeDef *TMRAx)
{
    uint32_t u32CntDir = 0xFFFFFFFFUL;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        u32CntDir = TMRAx->BCSTR & TMRA_BCSTR_DIR;
    }

    return u32CntDir;
}

/**
 * @brief  Specifies the clock source for the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32ClkSrc              The clock source of TIMERA.
 *                                      This parameter can be values of @ref TMRA_Clock_Source
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        TMRAx == NULL.
 */
en_result_t TMRA_SetClkSrc(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkSrc)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        WRITE_REG32(TMRAx->HCUPR, (u32ClkSrc & TMRA_CLK_HW_UP_ALL));
        WRITE_REG32(TMRAx->HCDOR, ((u32ClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified hardware clock source of the specified TIMERA unit.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32HwClkSrc            The hardware clock source of TIMERA.
 *                                      This parameter can be values of @ref TMRA_Clock_Source except TMRA_CLK_PCLK
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified hardware clock source.
 *   @arg Disable:                      Disable the specified hardware clock source.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        TMRAx == NULL.
 */
en_result_t TMRA_HwClkSrcCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32HwClkSrc, en_functional_state_t enNewState)
{
    uint32_t u32HwCntUpClk   = u32HwClkSrc & TMRA_CLK_HW_UP_ALL;
    uint32_t u32HwCntDownClk = (u32HwClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMRAx->HCUPR, u32HwCntUpClk);
            SET_REG32_BIT(TMRAx->HCDOR, u32HwCntDownClk);
        }
        else
        {
            SET_REG32_BIT(TMRAx->HCUPR, u32HwCntUpClk);
            SET_REG32_BIT(TMRAx->HCDOR, u32HwCntDownClk);
        }
        enRet = Ok;
    }

    return enRet;
}

#if 0
/**
 * @brief  Enable or disable the filter of the specified input pin of TIMERA.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32InputPin            The input pin of TIMERA.
 *                                      This parameter can be values of @ref TMRA_Input_Pin
 *   @arg  TMRA_PIN_TRIG:               Pin TIMA_<t>_TRIG.
 *   @arg  TMRA_PIN_CLKA:               Pin TIMA_<t>_PWM1/TIMA_<t>_CLKA.
 *   @arg  TMRA_PIN_CLKB:               Pin TIMA_<t>_PWM2/TIMA_<t>_CLKB.
 *   @arg  TMRA_PIN_PWM1:               Pin TIMA_<t>_PWM1.
 *   @arg  TMRA_PIN_PWM2:               Pin TIMA_<t>_PWM2.
 *   @arg  TMRA_PIN_PWM3:               Pin TIMA_<t>_PWM3.
 *   @arg  TMRA_PIN_PWM4:               Pin TIMA_<t>_PWM4.
 * @param  [in]  u32ClkDiv              The clock source division of the filter. Set it to zero while enNewState == Disable.
 *                                      This parameter can be a value of @ref TMRA_Filter_Clock_Divider
 *   @arg  TMRA_FILTER_CLK_DIV_1:       The filter clock is PCLK / 1.
 *   @arg  TMRA_FILTER_CLK_DIV_4:       The filter clock is PCLK / 4.
 *   @arg  TMRA_FILTER_CLK_DIV_16:      The filter clock is PCLK / 16.
 *   @arg  TMRA_FILTER_CLK_DIV_64:      The filter clock is PCLK / 64.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified pin's filter.
 *   @arg  Disable:                     Disable the specified pin's filter.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u8InputPin, \
                           uint32_t u32ClkDiv, en_functional_state_t enNewState)
{
    uint8_t u8PinIdx = 0U;
    uint8_t u8TmrCh;
    uint32_t u32CfgMsk;
    __IO uint32_t *ioCCONR;
    uint8_t au8Offset[] = {TMRA_FCONR_NOFIENTG_POS, TMRA_FCONR_NOFIENCA_POS, TMRA_FCONR_NOFIENCB_POS, \
                           TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, \
                           TMRA_CCONR_NOFIENCP_POS};
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_FILTER_CLK_DIV(u32ClkDiv));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u8InputPin &= TMRA_PIN_ALL;
        while (u8InputPin != 0U)
        {
            if ((u8InputPin & 0x1U) != 0U)
            {
                u32ClkDiv   = ((u32ClkDiv << 1U) | ((uint32_t)enNewState));
                u32ClkDiv <<= au8Offset[u8PinIdx];
                if (u8PinIdx < TMRA_PIN_PWM_OFFSET)
                {
                    u32CfgMsk = (uint32_t)(TMRA_FCONR_FILTER_CFG_MSK << au8Offset[u8PinIdx]);
                    MODIFY_REG32(TMRAx->FCONR, u32CfgMsk, u32ClkDiv);
                }
                else
                {
                    u8TmrCh = u8PinIdx - TMRA_PIN_PWM_OFFSET;
                    ioCCONR = IO_REG32(TMRAx->CCONR);
                    MODIFY_REG32(ioCCONR[u8TmrCh], TMRA_CCONR_FILTER_CFG_MSK, u32ClkDiv);
                }
            }
            u8InputPin >>= 1U;
            u8PinIdx++;
        }

        enRet = Ok;
    }

    return enRet;
}
#endif

/**
 * @brief  Specify the PWM polarity when counting start.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Start_Polarity
 *   @arg  TMRA_PWM_START_LOW:          The polarity of PWM output is low.
 *   @arg  TMRA_PWM_START_HI:           The polarity of PWM output is high.
 *   @arg  TMRA_PWM_START_KEEP:         The polarity of PWM output keeps the current polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_SetStartPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_START_POLARITY(u32Polarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_STAC, u32Polarity);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the PWM polarity when counting stop.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Stop_Polarity
 *   @arg  TMRA_PWM_STOP_LOW:           The polarity of PWM output is low.
 *   @arg  TMRA_PWM_STOP_HI:            The polarity of PWM output is high.
 *   @arg  TMRA_PWM_STOP_KEEP:          The polarity of PWM output keeps the current polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_SetStopPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_STOP_POLARITY(u32Polarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_STPC, u32Polarity);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the PWM polarity when counting matchs the compare reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Count_Match_Polarity
 *   @arg  TMRA_PWM_CM_LOW:             The polarity of PWM output is low.
 *   @arg  TMRA_PWM_CM_HI:              The polarity of PWM output is high.
 *   @arg  TMRA_PWM_CM_KEEP:            The polarity of PWM output keeps the current polarity.
 *   @arg  TMRA_PWM_CM_REVERSE:         PWM output reverses the current polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_SetCntMatchPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_CM_POLARITY(u32Polarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_CMPC, u32Polarity);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the PWM polarity when counting matchs the period reference value.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Period_Match_Polarity
 *   @arg  TMRA_PWM_PM_LOW:             The polarity of PWM output is low.
 *   @arg  TMRA_PWM_PM_HI:              The polarity of PWM output is high.
 *   @arg  TMRA_PWM_PM_KEEP:            The polarity of PWM output keeps the current polarity.
 *   @arg  TMRA_PWM_PM_REVERSE:         PWM output reverses the current polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_SetPeriodMatchPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_PM_POLARITY(u32Polarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_PERC, u32Polarity);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the PWM polarity when next cycle start.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Count_Match_Polarity
 *   @arg  TMRA_PWM_FORCE_INVALID:      Force polarity is invalid.
 *   @arg  TMRA_PWM_FORCE_LOW:          Force the PWM output low at the beginning of the next cycle. \
 *                                      The beginning of the next cycle: overflow position or underflow position \
 *                                      of sawtooth wave; valley position of triangle wave.
 *   @arg  TMRA_PWM_FORCE_HI:           Force the PWM output high at the beginning of the next cycle. \
 *                                      The beginning of the next cycle: overflow position or underflow position \
 *                                      of sawtooth wave; valley position of triangle wave.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_PWM_SetForcePolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_FORCE_POLARITY(u32Polarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_FORC, u32Polarity);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the capture condition for the specified channel.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TIMERA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TIMERA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TIMERA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TIMERA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TIMERA.
 * @param  [in]  u32CaptCond            The capture condition. Set this parameter to 0xFFFF to select all the conditions of capturing start.
 *                                      This parameter can be values of @ref TMRA_Channel_Capture_Condition
 *   @arg  TMRA_CAPT_COND_PWMR:         The condition of capture is a rising edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_PWMF:         The condition of capture is a falling edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_EVENT:        The condition of capture is the specified event occurred.
 *   @arg  TMRA_CAPT_COND_TRIGR:        The condition of capture is a rising edge is sampled on TRIG.
 *   @arg  TMRA_CAPT_COND_TRIGF:        The condition of capture is a falling edge is sampled on TRIG.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_CaptCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CaptCond, en_functional_state_t enNewState)
{
    uint32_t u32CCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));

        u32CaptCond &= TMRA_CAPT_COND_MSK;
        u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(RW_MEM32(u32CCONRAddr), u32CaptCond);
        }
        else
        {
            CLEAR_REG32_BIT(RW_MEM32(u32CCONRAddr), u32CaptCond);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified hardware start condition.
 * @param  [in]  TMRAx                  Pointer to TIMERA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TIMERA unit 1 ~ 12 instance register base.
 * @param  [in]  u32TrigCond            The trigger condition.
 *                                      This parameter can be a value of:
 *                                      @ref TMRA_Hardware_Start_Condition
 *                                      @ref TMRA_Hardware_Start_Condition
 *                                      @ref TMRA_Hardware_Start_Condition
 *   @arg  TMRA_START_COND_TRIGR:       1. Sync start is invalid: The condition is that a rising edge is sampled on TRIG of the current TIMERA unit. \
 *                                      2. Sync start is valid: The condition is that a rising edge is sampled on TRIG of the symmetric TIMERA unit.
 *   @arg  TMRA_START_COND_TRIGF:       1. Sync start is invalid: The condition is that a falling edge is sampled on TRIG of the current TIMERA unit. \
 *                                      2. Sync start is valid: The condition is that a falling edge is sampled on TRIG of the symmetric TIMERA unit.
 *   @arg  TMRA_START_COND_EVENT:       The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_STOP_COND_TRIGR:        The condition is that a rising edge is sampled on pin TRIG of the current TIMERA unit.
 *   @arg  TMRA_STOP_COND_TRIGF:        The condition is that a falling edge is sampled on pin TRIG of the current TIMERA unit.
 *   @arg  TMRA_STOP_COND_EVENT:        The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_CLR_COND_TRIGR:         The condition is that a rising edge is sampled on TRIG of the current TIMERA unit.
 *   @arg  TMRA_CLR_COND_TRIGF:         The condition is that a falling edge is sampled on TRIG of the current TIMERA unit.
 *   @arg  TMRA_CLR_COND_EVENT:         The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_CLR_COND_SYM_TRIGR:     The condition is that a rising edge is sampled on TRIG of the symmetric unit.
 *   @arg  TMRA_CLR_COND_SYM_TRIGF:     The condition is that a falling edge is sampled on TRIG of the symmetric unit.
 *   @arg  TMRA_CLR_COND_PWM3R:         The condition is that a rising edge is sampled on PWM3 of the current TIMERA unit.
 *   @arg  TMRA_CLR_COND_PWM3F:         The condition is that a falling edge is sampled on PWM3 of the current TIMERA unit.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified hardware start condition.
 *   @arg  Disable:                     Disable the specified hardware start condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       TMRAx == NULL.
 */
en_result_t TMRA_TrigCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32TrigCond, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (TMRAx != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u32TrigCond &= TMRA_TRIG_COND_MSK;
        if (enNewState == Enable)
        {
            SET_REG32_BIT(TMRAx->HCONR, u32TrigCond);
        }
        else
        {
            CLEAR_REG32_BIT(TMRAx->HCONR, u32TrigCond);
        }

        enRet = Ok;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
