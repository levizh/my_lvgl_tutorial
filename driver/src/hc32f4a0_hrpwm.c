/**
 *******************************************************************************
 * @file  hc32f4a0_hrpwm.c
 * @brief This file provides firmware functions to manage the High Resolution
 *        Pulse-Width Modulation(HRPWM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-04       Wangmin         First version
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
#include "hc32f4a0_hrpwm.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_HRPWM HRPWM
 * @brief HRPWM Driver Library
 * @{
 */

#if (DDL_HRPWM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HRPWM_Local_Macros HRPWM Local Macros
 * @{
 */
#define HRPWM_CAL_TIMEOUT       100000UL
/**
 * @defgroup HRPWM_Check_Parameters_Validity HRPWM Check Parameters Validity
 * @{
 */

/* Parameter valid check for HRPWM output channel */
#define IS_VALID_HRPWM_CH(x)                                                   \
(   ((x) >= HRPWM_CH_MIN)                       &&                             \
    ((x) <= HRPWM_CH_MAX))

/* Parameter valid check for HRPWM caliration unit */
#define IS_VALID_HRPWM_CAL_UNIT(x)                                             \
(   (HRPWM_CAL_UNIT0 == (x))                   ||                             \
    (HRPWM_CAL_UNIT1 == (x)))

/* Parameter valid check for HRPWM delay number */
#define IS_VALID_HRPWM_DELAY_NUM(x)                                            \
(   ((x) >= HRPWM_CH_DELAY_NUM_MIN)             &&                             \
    ((x) <= HRPWM_CH_DELAY_NUM_MAX))

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
 * @defgroup HRPWM_Local_Functions HRPWM Local Functions
 * @{
 */


/**
 * @}
 */

/**
 * @defgroup HRPWM_Global_Functions HRPWM Global Functions
 * @{
 */

/**
 * @brief  Process for getting HRPWM Calibrate function code
 * @param  [in] u32Unit     Calibrate unit, the parameter should be HRPWM_CAL_UNIT0 or HRPWM_CAL_UNIT1
 * @param  [in] pu8Code     The pointer to get calibrate code.
 *
 * @retval Ok:              Success
 * @retval ErrorTimeout:    Time out
 */
en_result_t HRPWM_CalibrateProcess(uint32_t u32Unit, uint8_t* pu8Code)
{
    uint32_t u32Timeout = HRPWM_CAL_TIMEOUT;
    en_result_t enRet = Ok;

    /* Enable calibrate */
    HRPWM_CalibrateCmd(u32Unit, Enable);
    /* Wait calibrate finish flag */
    while(Disable == HRPWM_CalibrateStdGet(u32Unit))
    {
        if(0UL == u32Timeout--)
        {
            break;
        }
    }

    if(0UL == u32Timeout)
    {
        enRet = ErrorTimeout;
    }
    else
    {
        /* Get calibrate code */
        *pu8Code = HRPWM_CalCodeGet(u32Unit);
    }
    return enRet;
}


/**
 * @brief  HRPWM Calibrate function enable or disable for specified unit
 * @param  [in] u32Unit     Calibrate unit, the parameter should be HRPWM_CAL_UNIT0 or HRPWM_CAL_UNIT1
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CalibrateCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CAL_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    switch (u32Unit)
    {
        case HRPWM_CAL_UNIT0:
            if(Enable == enNewState)
            {
                SET_REG32_BIT(M4_HRPWM->CALCR0, HRPWM_CALCR_CALEN);

            }
            else
            {
                CLEAR_REG32_BIT(M4_HRPWM->CALCR0, HRPWM_CALCR_CALEN);
            }
            break;
        case HRPWM_CAL_UNIT1:
            if(Enable == enNewState)
            {
                SET_REG32_BIT(M4_HRPWM->CALCR1, HRPWM_CALCR_CALEN);

            }
            else
            {
                CLEAR_REG32_BIT(M4_HRPWM->CALCR1, HRPWM_CALCR_CALEN);
            }
            break;
        default:
            break;
    }

    return Ok;
}


/**
 * @brief  HRPWM Calibrate function status get for specified unit
 * @param  [in] u32Unit     Calibrate unit, the parameter should be HRPWM_CAL_UNIT0 or HRPWM_CAL_UNIT1
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
en_functional_state_t HRPWM_CalibrateStdGet(uint32_t u32Unit)
{
    en_functional_state_t enRet = Disable;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CAL_UNIT(u32Unit));

    switch (u32Unit)
    {
        case HRPWM_CAL_UNIT0:
            if( 0UL != READ_REG32_BIT(M4_HRPWM->CALCR0, HRPWM_CALCR_ENDF))
            {
                enRet = Enable;
            }
            else
            {
                enRet = Disable;
            }

            break;

        case HRPWM_CAL_UNIT1:
            if( 0UL != READ_REG32_BIT(M4_HRPWM->CALCR1, HRPWM_CALCR_ENDF))
            {
                enRet = Enable;
            }
            else
            {
                enRet = Disable;
            }

            break;

        default:
            break;
    }

    return enRet;
}

/**
 * @brief  HRPWM Calibrate code get for specified unit
 * @param  [in] u32Unit     Calibrate unit, the parameter should be HRPWM_CAL_UNIT0 or HRPWM_CAL_UNIT1
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
uint8_t HRPWM_CalCodeGet(uint32_t u32Unit)
{
    uint8_t u8Ret = 0UL;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CAL_UNIT(u32Unit));

    switch (u32Unit)
    {
        case HRPWM_CAL_UNIT0:
            u8Ret = (uint8_t)(READ_REG32_BIT(M4_HRPWM->CALCR0, 0xFFUL));
            break;

        case HRPWM_CAL_UNIT1:
            u8Ret = (uint8_t)(READ_REG32_BIT(M4_HRPWM->CALCR1, 0xFFUL));
            break;

        default:
            break;
    }

    return u8Ret;
}

/**
 * @brief  HRPWM function enable or disable for specified channel
 * @param  [in] u32Ch       Channel, the parameter should range from HRPWM_CH_MIN to HRPWM_CH_MAX
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CHCmd(uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t *CRx;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CRx = (uint32_t*)(&M4_HRPWM->CR1 + (u32Ch - 1));
    if(Enable == enNewState)
    {
        SET_REG32_BIT(*CRx, HRPWM_CR_EN);

    }
    else
    {
        CLEAR_REG32_BIT(*CRx, HRPWM_CR_EN);
    }
    return Ok;
}


/**
 * @brief  HRPWM positive edge adjust enable or disable for specified channel
 * @param  [in] u32Ch       Channel, the parameter should range from HRPWM_CH_MIN to HRPWM_CH_MAX
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CHPositAdjCmd(uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t *CRx;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CRx = (uint32_t*)(&M4_HRPWM->CR1 + (u32Ch - 1));
    if(Enable == enNewState)
    {
        SET_REG32_BIT(*CRx, HRPWM_CR_PE);

    }
    else
    {
        CLEAR_REG32_BIT(*CRx, HRPWM_CR_PE);
    }
    return Ok;
}

/**
 * @brief  HRPWM negative edge adjust enable or disable for specified channel
 * @param  [in] u32Ch       Channel, the parameter should range from HRPWM_CH_MIN to HRPWM_CH_MAX
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CHNegatAdjCmd(uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t *CRx;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CRx = (uint32_t*)(&M4_HRPWM->CR1 + (u32Ch - 1));
    if(Enable == enNewState)
    {
        SET_REG32_BIT(*CRx, HRPWM_CR_NE);

    }
    else
    {
        CLEAR_REG32_BIT(*CRx, HRPWM_CR_NE);
    }
    return Ok;
}


/**
 * @brief  HRPWM positive edge adjust delay counts configration for specified channel
 * @param  [in] u32Ch       Channel, the parameter should range from HRPWM_CH_MIN to HRPWM_CH_MAX
 * @param  [in] u32DelayNum  Delay counts
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CHPositCfg(uint32_t u32Ch, uint32_t u32DelayNum)
{
    uint32_t *CRx;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CH(u32Ch));
    DDL_ASSERT(IS_VALID_HRPWM_DELAY_NUM(u32DelayNum));

    CRx = (uint32_t*)(&M4_HRPWM->CR1 + (u32Ch - 1UL));
    MODIFY_REG32(*CRx, HRPWM_CR_PSEL, (uint32_t)(u32DelayNum-1UL) << HRPWM_CR_PSEL_POS);

    return Ok;
}


/**
 * @brief  HRPWM negative edge adjust delay counts configration for specified channel
 * @param  [in] u32Ch       Channel, the parameter should range from HRPWM_CH_MIN to HRPWM_CH_MAX
 * @param  [in] u8DelayNum  Delay counts
 *
 * @retval Ok: Success
 */
en_result_t HRPWM_CHNegatCfg(uint32_t u32Ch, uint32_t u32DelayNum)
{
    uint32_t *CRx;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_HRPWM_CH(u32Ch));
    DDL_ASSERT(IS_VALID_HRPWM_DELAY_NUM(u32DelayNum));

    CRx = (uint32_t*)(&M4_HRPWM->CR1 + (u32Ch - 1UL));
    MODIFY_REG32(*CRx, HRPWM_CR_NSEL, (uint32_t)(u32DelayNum-1UL) << HRPWM_CR_NSEL_POS);

    return Ok;
}

/**
 * @}
 */

#endif /* DDL_HRPWM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
