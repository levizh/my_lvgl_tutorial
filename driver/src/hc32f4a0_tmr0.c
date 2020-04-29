/**
 *******************************************************************************
 * @file  hc32f4a0_tmr0.c
 * @brief This file provides firmware functions to manage the TMR0
 *        (TMR0).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_tmr0.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR0 TMR0
 * @brief TMR0 Driver Library
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Local_Macros TMR0 Local Macros
 * @{
 */

#define TMR0_CHA_CLKSRC_MSK             (TMR0_BCONR_SYNSA   |                  \
                                        TMR0_BCONR_SYNCLKA  |                  \
                                        TMR0_BCONR_ASYNCLKA)
#define TMR0_CHB_CLKSRC_MSK             (TMR0_BCONR_SYNSB   |                  \
                                        TMR0_BCONR_SYNCLKB  |                  \
                                        TMR0_BCONR_ASYNCLKB)
#define TMR0_COM_TRIG_EN_MSK          (TMR0_COM1_TRIG_ENABLE | TMR0_COM2_TRIG_ENABLE)
#define TMR0_CHB_POS                  (16U)
/**
 * @defgroup TMR0_Check_Parameters_Validity TMR0 Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_TMR0_1)                             ||                          \
    ((x) == M4_TMR0_2))

#define IS_VALID_CHANNEL(x)                                                    \
(   ((x) == TMR0_ChannelA)                         ||                          \
    ((x) == TMR0_ChannelB))

#define IS_VALID_CLK_DIVISION(x)                                               \
(   ((x) == TMR0_CLK_DIV1)                         ||                          \
    ((x) == TMR0_CLK_DIV2)                         ||                          \
    ((x) == TMR0_CLK_DIV4)                         ||                          \
    ((x) == TMR0_CLK_DIV8)                         ||                          \
    ((x) == TMR0_CLK_DIV16)                        ||                          \
    ((x) == TMR0_CLK_DIV32)                        ||                          \
    ((x) == TMR0_CLK_DIV64)                        ||                          \
    ((x) == TMR0_CLK_DIV128)                       ||                          \
    ((x) == TMR0_CLK_DIV256)                       ||                          \
    ((x) == TMR0_CLK_DIV512)                       ||                          \
    ((x) == TMR0_CLK_DIV1024))

#define IS_VALID_CLK_SRC(x)                                                    \
(   ((x) == TMR0_CLK_SRC_PCLK1)                    ||                          \
    ((x) == TMR0_CLK_SRC_INTHWTRIG)                ||                          \
    ((x) == TMR0_CLK_SRC_XTAL32)                   ||                          \
    ((x) == TMR0_CLK_SRC_LRC))

#define IS_VALID_HWTRG_FUNC(x)                                                 \
(   ((x) == TMR0_BT_HWTRG_FUNC_NONE)               ||                          \
    (((x) & TMR0_BT_HETRG_FUNC_MASK) != (uint32_t)0x0UL))


#  define IS_VALID_TMR0_FUNC(x)                                                \
(   ((x) == TMR0_FUNC_CMP)                         ||                          \
    ((x) == TMR0_FUNC_CAPTURE))
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
static void AsyncDelay(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup TMR0_Global_Functions TMR0 Global Functions
 * @{
 */

/**
 * @brief  Set a default value for TMR0 configuration structure.
 * @param  [in] pstcInitStruct    Tmr0 function structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcInitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInitStruct != NULL)
    {
        pstcInitStruct->u32ClockDivision = TMR0_CLK_DIV1;
        pstcInitStruct->u32ClockSource   = TMR0_CLK_SRC_PCLK1;
        pstcInitStruct->u32Tmr0Func      = TMR0_FUNC_CMP;
        pstcInitStruct->u16CmpValue      = 0xFFFFU;
        pstcInitStruct->u32HwTrigFunc    = TMR0_BT_HWTRG_FUNC_NONE;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Tmr0 peripheral function initialize
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] pstcTmr0Init       TMR0 function base parameter structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 * @note   In capture mode, don't need configure member u32HwTrigFunc and u16CmpValue
 */
en_result_t TMR0_Init(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,       \
                        const stc_tmr0_init_t* pstcTmr0Init)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32temp = 0U;
    if (pstcTmr0Init != NULL)
    {
        enRet = Ok;
        DDL_ASSERT(IS_VALID_UNIT(TMR0x));
        DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
        DDL_ASSERT(IS_VALID_CLK_DIVISION(pstcTmr0Init->u32ClockDivision));
        DDL_ASSERT(IS_VALID_CLK_SRC(pstcTmr0Init->u32ClockSource));
        DDL_ASSERT(IS_VALID_TMR0_FUNC(pstcTmr0Init->u32Tmr0Func));
        DDL_ASSERT(IS_VALID_HWTRG_FUNC(pstcTmr0Init->u32HwTrigFunc));

        u32temp = pstcTmr0Init->u32ClockDivision \
                  | pstcTmr0Init->u32HwTrigFunc  \
                  | pstcTmr0Init->u32Tmr0Func;

        if(u8Channel == TMR0_ChannelA)
        {
            /* Set TMR0_CHA compare value */
            TMR0x->CMPAR = pstcTmr0Init->u16CmpValue;
            /* Configure clock division, function mode, Hardware trigger function */
            TMR0x->BCONR = u32temp;
            /* Configure clock srouce */
            MODIFY_REG32(TMR0x->BCONR, TMR0_CHA_CLKSRC_MSK,            \
                        pstcTmr0Init->u32ClockSource);
        }
        else
        {
            /* Set TMR0_CHB compare value */
            TMR0x->CMPBR = pstcTmr0Init->u16CmpValue;
            /* Configure clock division, function mode, Hardware trigger function */
            TMR0x->BCONR = u32temp << TMR0_CHB_POS;
            /* Configure clock srouce */
            MODIFY_REG32(TMR0x->BCONR, TMR0_CHB_CLKSRC_MSK,            \
                        (pstcTmr0Init->u32ClockSource)<<TMR0_CHB_POS);
        }
    }
    return enRet;
}

/**
 * @brief  Set clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u32ClkSrc          Specifies the clock source
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_SRC_PCLK1:     Synchronous clock source: PCLK1.
 *   @arg  TMR0_CLK_SRC_INTHWTRIG: Synchronous clock source: Hardware Trigger Event.
 *   @arg  TMR0_CLK_SRC_XTAL32:    Asynchronous clock source: XTAl32
 *   @arg  TMR0_CLK_SRC_LRC:       Asynchronous clock source: LRC
 * @retval Ok: Success.
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_SetClkSrc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkSrc)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_SRC(u32ClkSrc));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        MODIFY_REG32(TMR0x->BCONR, TMR0_CHA_CLKSRC_MSK, u32ClkSrc);
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        MODIFY_REG32(TMR0x->BCONR, TMR0_CHB_CLKSRC_MSK, u32ClkSrc << TMR0_CHB_POS);
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Set the division of the clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u32ClkDiv          Specifies the clock source division
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_DIV1:         Clock source.
 *   @arg  TMR0_CLK_DIV2:         Clock source / 2.
 *   @arg  TMR0_CLK_DIV4:         Clock source / 4.
 *   @arg  TMR0_CLK_DIV8:         Clock source / 8.
 *   @arg  TMR0_CLK_DIV16:        Clock source / 16.
 *   @arg  TMR0_CLK_DIV32:        Clock source / 32.
 *   @arg  TMR0_CLK_DIV64:        Clock source / 64.
 *   @arg  TMR0_CLK_DIV128:       Clock source / 128.
 *   @arg  TMR0_CLK_DIV256:       Clock source / 256.
 *   @arg  TMR0_CLK_DIV512:       Clock source / 512.
 *   @arg  TMR0_CLK_DIV1024:      Clock source / 1024.
 * @retval Ok: Success.
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_SetClkDiv(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkDiv)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_DIVISION(u32ClkDiv));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_CKDIVA, u32ClkDiv);
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_CKDIVB, u32ClkDiv << TMR0_CHB_POS);
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Set Tmr0 HardWare TRigger Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u32HWFunc          Select TMR0 hardware trigger function
 *                                 This parameter can be a value of @ref TMR0_HardwareTrigger_Func_define
 * @param  [in] enNewState         Disable or Enable the function
 * @retval Ok: Success.
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_HWTrigCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, \
                           uint32_t u32HWFunc, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_HWTRG_FUNC(u32HWFunc));
    if(enNewState == Enable)
    {
        switch (u8Channel)
        {
        case TMR0_ChannelA:
            MODIFY_REG32(TMR0x->BCONR, TMR0_BT_HETRG_FUNC_MASK, u32HWFunc);
            AsyncDelay(TMR0x, u8Channel);
            break;
        case TMR0_ChannelB:
            MODIFY_REG32(TMR0x->BCONR, TMR0_BT_HETRG_FUNC_MASK << TMR0_CHB_POS, \
                         u32HWFunc << TMR0_CHB_POS);
            AsyncDelay(TMR0x, u8Channel);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (u8Channel)
        {
        case TMR0_ChannelA:
            CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BT_HETRG_FUNC_MASK);
            AsyncDelay(TMR0x, u8Channel);
            break;
        case TMR0_ChannelB:
            CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BT_HETRG_FUNC_MASK << TMR0_CHB_POS);
            AsyncDelay(TMR0x, u8Channel);
            break;
        default:
            break;
        }
    }
    enRet = Ok;
    return enRet;

}

/**
 * @brief  Set Tmr0  Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u32Func            Select TMR0 function
 *   @arg  TMR0_FUNC_CMP           Select the Compare function for TMR0
 *   @arg  TMR0_FUNC_CAPTURE       Select the Capture function for TMR0
 * @param  [in] enNewState         Disable or Enable the function
 * @retval Ok: Success.
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_FuncCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32Func)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_TMR0_FUNC(u32Func));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        if(u32Func == TMR0_FUNC_CMP)
        {
            CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_CAPMDA);
            AsyncDelay(TMR0x, u8Channel);
        }
        else
        {
            SET_REG32_BIT(TMR0x->BCONR, TMR0_FUNC_CAPTURE);
            AsyncDelay(TMR0x, u8Channel);
        }
        break;
    case TMR0_ChannelB:
        if(u32Func == TMR0_FUNC_CMP)
        {
            CLEAR_REG32_BIT(TMR0x->BCONR, TMR0_BCONR_CAPMDA << TMR0_CHB_POS);
            AsyncDelay(TMR0x, u8Channel);
        }
        else
        {
            SET_REG32_BIT(TMR0x->BCONR, TMR0_FUNC_CAPTURE << TMR0_CHB_POS);
            AsyncDelay(TMR0x, u8Channel);
        }
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;

}

/**
 * @brief  Get Tmr0 status flag
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @retval Set: Flag is set
 *         Reset: Flag is reset
 */
en_flag_status_t TMR0_GetStatus(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint32_t enRet = 0U;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        enRet = TMR0x->STFLR & TMR0_STFLR_CMFA;
        break;
    case TMR0_ChannelB:
        enRet = TMR0x->STFLR & TMR0_STFLR_CMFB;
        break;
    default:
        break;
    }
    return (enRet ? Set : Reset);
}

/**
 * @brief  Clear Tmr0 status flag
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_ClearStatus(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    /*Clear the Flag*/
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        CLEAR_REG32_BIT(TMR0x->STFLR, TMR0_STFLR_CMFA);
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        CLEAR_REG32_BIT(TMR0x->STFLR, TMR0_STFLR_CMFB);
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Command the tmr0 function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] enNewState         Disable or Enable the function
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_Cmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                        en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_CSTA, enNewState);
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_CSTB, (uint32_t)enNewState<<TMR0_CHB_POS);
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Tmr0 interrupt function command
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1             TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] enNewState       Disable or Enable the function
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_IntCmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                        en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    switch (u8Channel)
    {
    case TMR0_ChannelA:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_INTENA, \
                     (uint32_t)enNewState << TMR0_BCONR_INTENA_POS);
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        MODIFY_REG32(TMR0x->BCONR, TMR0_BCONR_INTENB, \
                     (uint32_t)enNewState << TMR0_BCONR_INTENB_POS);
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Get Tmr0 counter value
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1             TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_ChannelA or TMR0_ChannelB
 * @retval The counter register data
 * @note   Macksure tmr0 function is disable in asynchronous mode
 */
uint16_t TMR0_GetCntVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CntVal = 0U;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        u16CntVal = (uint16_t)(TMR0x->CNTAR & 0xFFFFU);
        break;
    case TMR0_ChannelB:
        u16CntVal = (uint16_t)(TMR0x->CNTBR & 0xFFFFU);
        break;
    default:
        break;
    }
    return u16CntVal;
}

/**
 * @brief  Set Tmr0 counter value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u16Value           The data to write to the counter register
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 * @note   Setting the count requires stop timer0
 */
en_result_t TMR0_SetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                                uint16_t u16Value)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        TMR0x->CNTAR = (uint32_t)u16Value;
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        TMR0x->CNTBR = (uint32_t)u16Value;
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  Get Tmr0 base compare value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @retval The compare register data
 * @note   Macksure timer0 function is disable in asynchronous mode
 */
uint16_t TMR0_GetCmpVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CmpVal = 0U;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        u16CmpVal = (uint16_t)(TMR0x->CMPAR & 0xFFFFU);
        break;
    case TMR0_ChannelB:
        u16CmpVal = (uint16_t)(TMR0x->CMPBR & 0xFFFFU);
        break;
    default:
        break;
    }
    return u16CmpVal;
}

/**
 * @brief  Set Tmr0 compare value
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @param  [in] u16Value           The data to write to the compare register
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_SetCmpVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel,
                                uint16_t u16Value)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    switch (u8Channel)
    {
    case TMR0_ChannelA:
        TMR0x->CMPAR = (uint32_t)u16Value;
        AsyncDelay(TMR0x, u8Channel);
        break;
    case TMR0_ChannelB:
        TMR0x->CMPBR = (uint32_t)u16Value;
        AsyncDelay(TMR0x, u8Channel);
        break;
    default:
        break;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  De-Initialize TMR0 function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @retval Ok: Success
 */
en_result_t TMR0_DeInit(M4_TMR0_TypeDef* TMR0x)
{
    en_result_t enRet = Ok;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));

    TMR0x->CMPAR = (uint32_t)0x0000FFFFUL;
    TMR0x->CNTAR = (uint32_t)0x00000000UL;
    TMR0x->STFLR = (uint32_t)0x00000000UL;
    TMR0x->BCONR = (uint32_t)0x00000000UL;
    return enRet;
}

/**
 * @brief  Set common trigger source for Tmr0
 * @param  [in] u32ComTrigEn        Common trigger event enable bit mask.
 *                                  This parameter can be a value of @ref TMR0_Common_Trigger_Sel
 *   @arg  TMR0_COM1_TRIG_DISABLE:  Enable common trigger event 1 for the specified usage.
 *   @arg  TMR0_COM2_TRIG_DISABLE:  Enable common trigger event 2 for the specified usage.
 *   @arg  TMR0_COM1_TRIG_ENABLE:   Disable common trigger event 1 for the specified usage.
 *   @arg  TMR0_COM2_TRIG_ENABLE:   Disable common trigger event 2 for the specified usage.
 * @retval None
 */
void TMR0_ComTrigCmd(uint32_t u32ComTrigEn)
{
    u32ComTrigEn &= TMR0_COM_TRIG_EN_MSK;
    MODIFY_REG32(M4_AOS->TMR0_HTSSR, TMR0_COM_TRIG_EN_MSK, u32ComTrigEn);
}

/**
 * @brief  Set external trigger source for Tmr0
 * @param  [in] enEvent        External event source, @ref en_event_src_t
 *
 * @retval None
 */
void TMR0_SetTriggerSrc(en_event_src_t enEvent)
{
    MODIFY_REG32(M4_AOS->TMR0_HTSSR, AOS_TMR0_HTSSR_TRGSEL, (uint32_t)enEvent);
}

/**
 * @brief  Time delay for register write in asynchronous mode
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR0_1               TMR0 unit 1 instance register base
 *   @arg  M4_TMR0_2               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 * @retval None
 */
static void AsyncDelay(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint32_t u32ModeA = 0U;
    uint32_t u32ModeB = 0U;
    if(u8Channel == TMR0_ChannelA)
    {
        u32ModeA = TMR0x->BCONR & TMR0_BCONR_SYNSA;
        if(u32ModeA != 0U)
        {
            for(uint32_t i=0UL; i < (SystemCoreClock/10000UL); i++)
            {
                __NOP();
            }
        }
    }
    if(u8Channel == TMR0_ChannelB)
    {
        u32ModeB = TMR0x->BCONR & TMR0_BCONR_SYNSB;
        if(u32ModeB != 0U)
        {
            for(uint32_t i=0UL; i < (SystemCoreClock/10000UL); i++)
            {
                __NOP();
            }
        }
    }

}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
