/**
 *******************************************************************************
 * @file  hc32f4a0_dma.c
 * @brief This file provides firmware functions to manage the Direct Memory
 *        Access (DMA).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-11       Zhangxl         First version
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
#include "hc32f4a0_dma.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DMA DMA
 * @brief Direct Memory Access Driver Library
 * @{
 */

#if (DDL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DMA_Local_Macros DMA Local Macros
 * @{
 */
#define DMA_CH_REG(reg_base, ch)    (*(uint32_t *)((uint32_t)(&reg_base) + ((ch) * 0x40UL)))

/**
 * @defgroup DMA_Check_Parameters_Validity DMA Check Parameters Validity
 * @{
 */
/* Parameter valid check for DMA unit. */
#define IS_DMA_UNIT(unit)                                                       \
(   ((unit) == M4_DMA1)                     ||                                  \
    ((unit) == M4_DMA2))

/* Parameter valid check for DMA channel. */
#define IS_DMA_CH(ch)                                                           \
(   ((ch) == DMA_CH0)                       ||                                  \
    ((ch) == DMA_CH1)                       ||                                  \
    ((ch) == DMA_CH2)                       ||                                  \
    ((ch) == DMA_CH3)                       ||                                  \
    ((ch) == DMA_CH4)                       ||                                  \
    ((ch) == DMA_CH5)                       ||                                  \
    ((ch) == DMA_CH6)                       ||                                  \
    ((ch) == DMA_CH7))

/* Parameter valid check for DMA multiplex channel. */
#define IS_DMA_MX_CH(ch)    (((ch) & DMA_MX_CH_ALL) != (uint32_t)(0x00UL))

/* Parameter valid check for DMA LLP pointer address. */
#define IS_DMA_LLP(llp)         (((llp) & 0x03UL) == (uint32_t)(0x00UL))

/* Parameter valid check for DMA LLP function. */
#define IS_DMA_LLP_EN(en)                                                       \
(   ((en) == DMA_LLP_ENABLE)                ||                                  \
    ((en) == DMA_LLP_DISABLE))

/* Parameter valid check for DMA linked-list-pointer mode. */
#define IS_DMA_LLP_MODE(mode)                                                   \
(   ((mode) == DMA_LLP_RUN)                 ||                                  \
    ((mode) == DMA_LLP_WAIT))

/* Parameter valid check for DMA error interrupt. */
#define IS_DMA_ERR_INT(int)     (((int) & DMA_ERR_INT_MASK) != ((uint32_t)0x00UL))

/* Parameter valid check for DMA transfer interrupt. */
#define IS_DMA_TRANS_INT(int)   (((int) & DMA_TRANS_INT_MASK) != ((uint32_t)0x00UL))

/* Parameter valid check for DMA request status. */
#define IS_DMA_REQ_STAT(stat)   (((stat) & DMA_REQ_STAT_MASK) != ((uint32_t)0x00UL))

/* Parameter valid check for DMA channel status. */
#define IS_DMA_TRANS_STAT(stat) (((stat) & DMA_TRANS_STAT_MASK) != ((uint32_t)0x00UL))

/* Parameter valid check for DMA transfer data width. */
#define IS_DMA_DATA_WIDTH(dw)                                                    \
(   ((dw) == DMA_DATAWIDTH_8BIT)            ||                                  \
    ((dw) == DMA_DATAWIDTH_16BIT)           ||                                  \
    ((dw) == DMA_DATAWIDTH_32BIT))

/* Parameter valid check for DMA source address mode. */
#define IS_DMA_SADDR_MODE(mode)                                                 \
(   ((mode) == DMA_SRC_ADDR_FIX)            ||                                  \
    ((mode) == DMA_SRC_ADDR_INC)            ||                                  \
    ((mode) == DMA_SRC_ADDR_DEC))

/* Parameter valid check for DMA destination address mode. */
#define IS_DMA_DADDR_MODE(mode)                                                 \
(   ((mode) == DMA_DEST_ADDR_FIX)           ||                                  \
    ((mode) == DMA_DEST_ADDR_INC)           ||                                  \
    ((mode) == DMA_DEST_ADDR_DEC))

/* Parameter valid check for DMA source address repeat selection. */
#define IS_DMA_SRC_RPT(rpt)                                                     \
(   ((rpt) == DMA_SRC_RPT_ENABLE)           ||                                  \
    ((rpt) == DMA_SRC_RPT_DISABLE))

/* Parameter valid check for DMA destination address repeat selection. */
#define IS_DMA_DEST_RPT(rpt)                                                    \
(   ((rpt) == DMA_DEST_RPT_ENABLE)          ||                                  \
    ((rpt) == DMA_DEST_RPT_DISABLE))

/* Parameter valid check for DMA source non-sequence selection. */
#define IS_DMA_SRC_NS(ns)                                                       \
(   ((ns) == DMA_SRC_NS_ENABLE)             ||                                  \
    ((ns) == DMA_SRC_NS_DISABLE))

/* Parameter valid check for DMA destination non-sequence selection. */
#define IS_DMA_DEST_NS(ns)                                                      \
(   ((ns) == DMA_DEST_NS_ENABLE)            ||                                  \
    ((ns) == DMA_DEST_NS_DISABLE))

/* Parameter valid check for DMA global interrupt function. */
#define IS_DMA_INT_FUNC(func)                                                   \
(   ((func) == DMA_INT_ENABLE)              ||                                  \
    ((func) == DMA_INT_DISABLE))

/* Parameter valid check for DMA reconfig count mode. */
#define IS_DMA_RC_CNT_MODE(mode)                                                \
(   ((mode) == DMA_RC_CNT_FIX)              ||                                  \
    ((mode) == DMA_RC_CNT_SRC)              ||                                  \
    ((mode) == DMA_RC_CNT_DEST))

/* Parameter valid check for DMA reconfig destination address mode. */
#define IS_DMA_RC_DA_MODE(mode)                                                 \
(   ((mode) == DMA_RC_DA_FIX)               ||                                  \
    ((mode) == DMA_RC_DA_NS )               ||                                  \
    ((mode) == DMA_RC_DA_RPT))

/* Parameter valid check for DMA reconfig source address mode. */
#define IS_DMA_RC_SA_MODE(mode)                                                 \
(   ((mode) == DMA_RC_SA_FIX)               ||                                  \
    ((mode) == DMA_RC_SA_NS )               ||                                  \
    ((mode) == DMA_RC_SA_RPT))

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
 * @defgroup DMA_Global_Functions DMA Global Functions
 * @{
 */

/**
 * @brief  DMA global function config.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_Cmd(M4_DMA_TypeDef *stcDmaReg, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    /* Global setting, Enable or Disable DMA */
    WRITE_REG32(stcDmaReg->EN, enNewState);
}

/**
 * @brief  DMA error IRQ function config.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32ErrInt DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR0.
 *   @arg  DMA_REQ_ERR1.
 *   @arg  DMA_REQ_ERR2.
 *   @arg  DMA_REQ_ERR3.
 *   @arg  DMA_REQ_ERR4.
 *   @arg  DMA_REQ_ERR5.
 *   @arg  DMA_REQ_ERR6.
 *   @arg  DMA_REQ_ERR7.
 *   @arg  DMA_TRANS_ERR0.
 *   @arg  DMA_TRANS_ERR1.
 *   @arg  DMA_TRANS_ERR2.
 *   @arg  DMA_TRANS_ERR3.
 *   @arg  DMA_TRANS_ERR4.
 *   @arg  DMA_TRANS_ERR5.
 *   @arg  DMA_TRANS_ERR6.
 *   @arg  DMA_TRANS_ERR7.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_ErrIntCmd(M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_ERR_INT(u32ErrInt));

    if (Disable == enNewState)
    {
        SET_REG32_BIT(stcDmaReg->INTMASK0, u32ErrInt);
    }
    else
    {
        CLEAR_REG32_BIT(stcDmaReg->INTMASK0, u32ErrInt);
    }
}

/**
 * @brief  Get DMA error IRQ status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32ErrInt DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR0.
 *   @arg  DMA_REQ_ERR1.
 *   @arg  DMA_REQ_ERR2.
 *   @arg  DMA_REQ_ERR3.
 *   @arg  DMA_REQ_ERR4.
 *   @arg  DMA_REQ_ERR5.
 *   @arg  DMA_REQ_ERR6.
 *   @arg  DMA_REQ_ERR7.
 *   @arg  DMA_TRANS_ERR0.
 *   @arg  DMA_TRANS_ERR1.
 *   @arg  DMA_TRANS_ERR2.
 *   @arg  DMA_TRANS_ERR3.
 *   @arg  DMA_TRANS_ERR4.
 *   @arg  DMA_TRANS_ERR5.
 *   @arg  DMA_TRANS_ERR6.
 *   @arg  DMA_TRANS_ERR7.
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetErrIntStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_ERR_INT(u32ErrInt));
    return (READ_REG32_BIT(stcDmaReg->INTSTAT0, u32ErrInt) ? Set : Reset);
}

/**
 * @brief  Clear DMA error IRQ status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32ErrInt DMA error IRQ flag.
 *   @arg  DMA_REQ_ERR0.
 *   @arg  DMA_REQ_ERR1.
 *   @arg  DMA_REQ_ERR2.
 *   @arg  DMA_REQ_ERR3.
 *   @arg  DMA_REQ_ERR4.
 *   @arg  DMA_REQ_ERR5.
 *   @arg  DMA_REQ_ERR6.
 *   @arg  DMA_REQ_ERR7.
 *   @arg  DMA_TRANS_ERR0.
 *   @arg  DMA_TRANS_ERR1.
 *   @arg  DMA_TRANS_ERR2.
 *   @arg  DMA_TRANS_ERR3.
 *   @arg  DMA_TRANS_ERR4.
 *   @arg  DMA_TRANS_ERR5.
 *   @arg  DMA_TRANS_ERR6.
 *   @arg  DMA_TRANS_ERR7.
 * @retval None
 */
void DMA_ClearErrIntStatus(M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_ERR_INT(u32ErrInt));

    SET_REG32_BIT(stcDmaReg->INTCLR0, u32ErrInt);
}


/**
 * @brief  DMA transfer IRQ function config.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_BTC_INT0
 *   @arg  DMA_BTC_INT1
 *   @arg  DMA_BTC_INT2
 *   @arg  DMA_BTC_INT3
 *   @arg  DMA_BTC_INT4
 *   @arg  DMA_BTC_INT5
 *   @arg  DMA_BTC_INT6
 *   @arg  DMA_BTC_INT7
 *   @arg  DMA_TC_INT0
 *   @arg  DMA_TC_INT1
 *   @arg  DMA_TC_INT2
 *   @arg  DMA_TC_INT3
 *   @arg  DMA_TC_INT4
 *   @arg  DMA_TC_INT5
 *   @arg  DMA_TC_INT6
 *   @arg  DMA_TC_INT7
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_TransIntCmd(M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_TRANS_INT(u32TransInt));

    if (Disable == enNewState)
    {
        SET_REG32_BIT(stcDmaReg->INTMASK1, u32TransInt);
    }
    else
    {
        CLEAR_REG32_BIT(stcDmaReg->INTMASK1, u32TransInt);
    }
}

/**
 * @brief  Get DMA transfer IRQ status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_BTC_INT0
 *   @arg  DMA_BTC_INT1
 *   @arg  DMA_BTC_INT2
 *   @arg  DMA_BTC_INT3
 *   @arg  DMA_BTC_INT4
 *   @arg  DMA_BTC_INT5
 *   @arg  DMA_BTC_INT6
 *   @arg  DMA_BTC_INT7
 *   @arg  DMA_TC_INT0
 *   @arg  DMA_TC_INT1
 *   @arg  DMA_TC_INT2
 *   @arg  DMA_TC_INT3
 *   @arg  DMA_TC_INT4
 *   @arg  DMA_TC_INT5
 *   @arg  DMA_TC_INT6
 *   @arg  DMA_TC_INT7
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetTransIntStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt)
{
    DDL_ASSERT(IS_DMA_TRANS_INT(u32TransInt));
    return (READ_REG32_BIT(stcDmaReg->INTSTAT1, u32TransInt) ? Set : Reset);
}

/**
 * @brief  Clear DMA transfer IRQ status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32TransInt DMA transfer IRQ flag.
 *   @arg  DMA_BTC_INT0
 *   @arg  DMA_BTC_INT1
 *   @arg  DMA_BTC_INT2
 *   @arg  DMA_BTC_INT3
 *   @arg  DMA_BTC_INT4
 *   @arg  DMA_BTC_INT5
 *   @arg  DMA_BTC_INT6
 *   @arg  DMA_BTC_INT7
 *   @arg  DMA_TC_INT0
 *   @arg  DMA_TC_INT1
 *   @arg  DMA_TC_INT2
 *   @arg  DMA_TC_INT3
 *   @arg  DMA_TC_INT4
 *   @arg  DMA_TC_INT5
 *   @arg  DMA_TC_INT6
 *   @arg  DMA_TC_INT7
 * @retval None
 */
void DMA_ClearTransIntStatus(M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_TRANS_INT(u32TransInt));

    SET_REG32_BIT(stcDmaReg->INTCLR1, u32TransInt);
}

/**
 * @brief  DMA multiplex channel function config.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8MxCh DMA multiplex channel.
 *   @arg  DMA_MX_CH0.
 *   @arg  DMA_MX_CH1.
 *   @arg  DMA_MX_CH2.
 *   @arg  DMA_MX_CH3.
 *   @arg  DMA_MX_CH4.
 *   @arg  DMA_MX_CH5.
 *   @arg  DMA_MX_CH6.
 *   @arg  DMA_MX_CH7.
 *   @arg  DMA_MX_CH_ALL.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_MxChannelCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8MxCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_MX_CH(u8MxCh));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(stcDmaReg->CHEN, u8MxCh);
    }
    else
    {
        SET_REG32_BIT(stcDmaReg->CHENCLR, u8MxCh);
    }
}

/**
 * @brief  DMA channel function config.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] enNewState The function new state.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DMA_ChannelCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(stcDmaReg->CHEN, ((1UL << u8Ch) & 0xFFUL));
    }
    else
    {
        SET_REG32_BIT(stcDmaReg->CHENCLR, ((1UL << u8Ch) & 0xFFUL));
    }
}

/**
 * @brief  Get DMA request status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32Status DMA request status.
 *   @arg  DMA_REQ_CH0.
 *   @arg  DMA_REQ_CH1.
 *   @arg  DMA_REQ_CH2.
 *   @arg  DMA_REQ_CH3.
 *   @arg  DMA_REQ_CH4.
 *   @arg  DMA_REQ_CH5.
 *   @arg  DMA_REQ_CH6.
 *   @arg  DMA_REQ_CH7.
 *   @arg  DMA_REQ_RECONFIG.
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetReqStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32Status)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_REQ_STAT(u32Status));

    return (READ_REG32_BIT(stcDmaReg->REQSTAT, u32Status) ? Set : Reset);
}

/**
 * @brief  Get DMA transfer status.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u32Status DMA transfer status.
 *   @arg  DMA_TRANS_CH0.
 *   @arg  DMA_TRANS_CH1.
 *   @arg  DMA_TRANS_CH2.
 *   @arg  DMA_TRANS_CH3.
 *   @arg  DMA_TRANS_CH4.
 *   @arg  DMA_TRANS_CH5.
 *   @arg  DMA_TRANS_CH6.
 *   @arg  DMA_TRANS_CH7.
 *   @arg  DMA_TRANS_RECONFIG.
 *   @arg  DMA_TRANS_DMA.
 * @retval en_flag_status_t
 */
en_flag_status_t DMA_GetTransStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32Status)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_TRANS_STAT(u32Status));

    return (READ_REG32_BIT(stcDmaReg->CHSTAT, u32Status) ? Set : Reset);
}


/**
 * @brief  DMA re-config mode trigger source.
 * @param  [in] enSrc DMA transfer trigger source.
 *   @arg  This parameter can be @ref en_event_src_t
 * @retval None
 * @note This register belongs to AOS module, please ensure enable it in advance.
 *       DMA1 and DMA2 share this register.
 */
void DMA_SetReConfigTrigSrc(en_event_src_t enSrc)
{
    WRITE_REG32(M4_AOS->DMA_TRGSELRC, enSrc);
}

/**
 * @brief  Config DMA transfer trigger source.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] enSrc DMA transfer trigger source.
 *   @arg  This parameter can be @ref en_event_src_t
 * @retval None
 * @note This register belongs to AOS module, please ensure enable it in advance.
 */
void DMA_SetTrigSrc(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_event_src_t enSrc)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    if (M4_DMA1 == stcDmaReg)
    {
        *(uint32_t*)((uint32_t)(&M4_AOS->DMA_1_TRGSEL0) + u8Ch*4UL) = enSrc;
    }
    else if (M4_DMA2 == stcDmaReg)
    {
        *(uint32_t*)((uint32_t)(&M4_AOS->DMA_2_TRGSEL0) + u8Ch*4UL) = enSrc;
    }
    else
    {
        __ASM("NOP");
    }
}

/**
 * @brief  Config DMA source address.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Addr DMA source address.
 * @retval None
 */
void DMA_SetSrcAddr(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    WRITE_REG32(DMA_CH_REG(stcDmaReg->SAR0, u8Ch), u32Addr);
}

/**
 * @brief  Config DMA destination address.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Addr DMA destination address.
 * @retval None
 */
void DMA_SetDestAddr(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    WRITE_REG32(DMA_CH_REG(stcDmaReg->DAR0, u8Ch), u32Addr);
}

/**
 * @brief  Config DMA transfer count.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u16Cnt DMA transfer count (0: infinite, 1 ~ 65535).
 * @retval None
 */
void DMA_SetTransCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Cnt)
{
    uint32_t *DTCTLx = 0UL;
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    /* avoid warning 12.2 */
    //MODIFY_REG32(DMA_CH_REG(stcDmaReg->DTCTL0, u8Ch), DMA_DTCTL_CNT,          \
        ((uint32_t)(u16Cnt) << DMA_DTCTL_CNT_POS));
    DTCTLx = &DMA_CH_REG(stcDmaReg->DTCTL0, u8Ch);
    MODIFY_REG32(*DTCTLx, DMA_DTCTL_CNT, ((uint32_t)(u16Cnt) << DMA_DTCTL_CNT_POS));
}

/**
 * @brief  Config DMA block size per transfer.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u16Size DMA block size (0: 1024, 1 ~ 1023).
 * @retval None
 */
void DMA_SetBlockSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size)
{
    uint32_t *DTCTLx = 0UL;
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    /* avoid warning 12.2 */
    //MODIFY_REG32(DMA_CH_REG(stcDmaReg->DTCTL0, u8Ch), DMA_DTCTL_BLKSIZE,      \
        ((uint32_t)(u16Size) << DMA_DTCTL_BLKSIZE_POS));
    DTCTLx = &DMA_CH_REG(stcDmaReg->DTCTL0, u8Ch);
    MODIFY_REG32(*DTCTLx, DMA_DTCTL_BLKSIZE, ((uint32_t)u16Size << DMA_DTCTL_BLKSIZE_POS));
}

/**
 * @brief  Config DMA source repeat size.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u16Size DMA source repeat size (0: 1024, 1 ~ 1023).
 * @retval None
 */
void DMA_SetSrcRptSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size)
{
    uint32_t *RPTx = 0UL;
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    /* avoid warning 12.2 */
    //MODIFY_REG32(DMA_CH_REG(stcDmaReg->RPT0, u8Ch), DMA_RPT_SRPT,              \
        ((uint32_t)(u16Size) << DMA_RPT_SRPT_POS));
    RPTx = &DMA_CH_REG(stcDmaReg->RPT0, u8Ch);
    MODIFY_REG32(*RPTx, DMA_RPT_SRPT, ((uint32_t)(u16Size) << DMA_RPT_SRPT_POS));
}

/**
 * @brief  Config DMA destination repeat size.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u16Size DMA destination repeat size (0: 1024, 1 ~ 1023).
 * @retval None
 */
void DMA_SetDestRptSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(DMA_CH_REG(stcDmaReg->RPT0, u8Ch), DMA_RPT_DRPT, ((uint32_t)(u16Size) << DMA_RPT_DRPT_POS));
}

/**
 * @brief  Config DMA source transfter count under non-sequence mode.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Cnt DMA source transfer count (0: 4096, 1 ~ 4095).
 * @retval None
 */
void DMA_SetNonSeqSrcCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Cnt)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(DMA_CH_REG(stcDmaReg->SNSEQCTL0, u8Ch), DMA_SNSEQCTLB_SNSCNTB, (u32Cnt << DMA_SNSEQCTLB_SNSCNTB_POS));
}

/**
 * @brief  Config DMA destination transfter count under non-sequence mode.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Cnt DMA destination transfer count (0: 4096, 1 ~ 4095).
 * @retval None
 */
void DMA_SetNonSeqDestCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Cnt)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(DMA_CH_REG(stcDmaReg->DNSEQCTL0, u8Ch), DMA_DNSEQCTL_DNSCNT, (u32Cnt << DMA_DNSEQCTL_DNSCNT_POS));
}

/**
 * @brief  Config DMA source offset number under non-sequence mode.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Ofs DMA source offset (0 ~ 2^20).
 * @retval None
 */
void DMA_SetNonSeqSrcOffset(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Ofs)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(DMA_CH_REG(stcDmaReg->SNSEQCTL0, u8Ch), DMA_SNSEQCTL_SOFFSET, u32Ofs);
}

/**
 * @brief  Config DMA destination offset number under non-sequence mode.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Ofs DMA destination offset (0 ~ 2^20).
 * @retval None
 */
void DMA_SetNonSeqDestOffset(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Ofs)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(DMA_CH_REG(stcDmaReg->DNSEQCTL0, u8Ch), DMA_DNSEQCTL_DOFFSET, u32Ofs);
}

/**
 * @brief  Initialize DMA config structure. Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaInit Pointer to a stc_dma_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_StructInit(stc_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaInit->u32IntEn       = DMA_INT_ENABLE;
        pstcDmaInit->u32SrcAddr     = 0x00UL;
        pstcDmaInit->u32DestAddr    = 0x00UL;
        pstcDmaInit->u32DataWidth   = DMA_DATAWIDTH_8BIT;
        pstcDmaInit->u32BlockSize   = 0x00UL;
        pstcDmaInit->u32TransCnt    = 0x01UL;
        pstcDmaInit->u32SrcInc      = DMA_SRC_ADDR_FIX;
        pstcDmaInit->u32DestInc     = DMA_DEST_ADDR_FIX;
    }
    return enRet;
}

/**
 * @brief  DMA basical function initialize.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] pstcDmaInit DMA config structure.
 *   @arg  u32IntEn         DMA interrupt enable or disable.
 *   @arg  u32SrcAddr       DMA source address.
 *   @arg  u32DestAddr      DMA destination address.
 *   @arg  u32DataWidth     DMA data width.
 *   @arg  u32BlockSize     DMA block size.
 *   @arg  u32TransferCnt   DMA transfer count.
 *   @arg  u32SrcInc        DMA source address direction.
 *   @arg  u32DestInc       DMA destination address direction.
 * @retval Ok: DMA basical function initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_Init(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_init_t *pstcDmaInit)
{
    en_result_t enRet = Ok;
    uint32_t *CHCTLx = 0UL;

    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_DMA_INT_FUNC(pstcDmaInit->u32IntEn));
        DDL_ASSERT(IS_DMA_DATA_WIDTH(pstcDmaInit->u32DataWidth));
        DDL_ASSERT(IS_DMA_SADDR_MODE(pstcDmaInit->u32SrcInc));
        DDL_ASSERT(IS_DMA_DADDR_MODE(pstcDmaInit->u32DestInc));

        WRITE_REG32(DMA_CH_REG(stcDmaReg->SAR0, u8Ch), pstcDmaInit->u32SrcAddr);
        WRITE_REG32(DMA_CH_REG(stcDmaReg->DAR0, u8Ch), pstcDmaInit->u32DestAddr);
        WRITE_REG32(DMA_CH_REG(stcDmaReg->DTCTL0, u8Ch), (pstcDmaInit->u32BlockSize|\
            (pstcDmaInit->u32TransCnt << DMA_DTCTL_CNT_POS)));

        /* avoid warning 12.2 */
        //MODIFY_REG32(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch),                     \
            (DMA_CHCTL_SINC | DMA_CHCTL_DINC | DMA_CHCTL_HSIZE | DMA_CHCTL_IE), \
            (pstcDmaInit->u32IntEn | pstcDmaInit->u32DataWidth |                \
            pstcDmaInit->u32SrcInc | pstcDmaInit->u32DestInc));
        CHCTLx = &DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx,                                                   \
            (DMA_CHCTL_SINC | DMA_CHCTL_DINC | DMA_CHCTL_HSIZE | DMA_CHCTL_IE), \
            (pstcDmaInit->u32IntEn | pstcDmaInit->u32DataWidth |                \
            pstcDmaInit->u32SrcInc | pstcDmaInit->u32DestInc));
    }
    return enRet;
}

/**
 * @brief  Initialize DMA repeat mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaRptInit Pointer to a stc_dma_rpt_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA repeat mode config structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_RepeatStructInit(stc_dma_rpt_init_t *pstcDmaRptInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaRptInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaRptInit->u32SrcRptEn     = DMA_SRC_RPT_DISABLE;
        pstcDmaRptInit->u32SrcRptSize   = 0x00UL;
        pstcDmaRptInit->u32DestRptEn    = DMA_DEST_RPT_DISABLE;
        pstcDmaRptInit->u32DestRptSize  = 0x00UL;
    }
    return enRet;
}

/**
 * @brief  DMA repeat mode initialize.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] pstcDmaRptInit DMA repeat mode config structure.
 *   @arg  u32SrcRptEn      DMA source repeat enable or disable.
 *   @arg  u32SrcRptSize    DMA source repeat size.
 *   @arg  u32DestRptEn     DMA destination repeat enable or disable.
 *   @arg  u32DestRptSize   DMA destination repeat size.
 * @retval Ok: DMA repeat function initilize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_RepeatInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_rpt_init_t *pstcDmaRptInit)
{
    en_result_t enRet = Ok;
    uint32_t *CHCTLx = 0UL;

    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaRptInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_DMA_SRC_RPT(pstcDmaRptInit->u32SrcRptEn));
        DDL_ASSERT(IS_DMA_DEST_RPT(pstcDmaRptInit->u32DestRptEn));

        /* avoid warning 12.2 */
        //MODIFY_REG32(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch),                     \
            (DMA_CHCTL_SRTPEN | DMA_CHCTL_DRPTEN),                              \
            (pstcDmaRptInit->u32SrcRptEn | pstcDmaRptInit->u32DestRptEn));
        CHCTLx = &DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx,                                                    \
            (DMA_CHCTL_SRTPEN | DMA_CHCTL_DRPTEN),                              \
            (pstcDmaRptInit->u32SrcRptEn | pstcDmaRptInit->u32DestRptEn));

        WRITE_REG32(DMA_CH_REG(stcDmaReg->RPT0, u8Ch),                          \
            ((pstcDmaRptInit->u32DestRptSize << DMA_RPT_DRPT_POS) |             \
            pstcDmaRptInit->u32SrcRptSize));
    }
    return enRet;
}

/**
 * @brief  Initialize DMA non-sequence mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaNonSeqInit Pointer to a stc_dma_nonseq_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA non-sequence mode structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaNonSeqInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaNonSeqInit->u32SrcNonSeqEn   = DMA_SRC_NS_DISABLE;
        pstcDmaNonSeqInit->u32SrcNonSeqCnt  = 0x00UL;
        pstcDmaNonSeqInit->u32SrcNonSeqOfs  = 0x00UL;
        pstcDmaNonSeqInit->u32DestNonSeqEn  = DMA_DEST_NS_DISABLE;
        pstcDmaNonSeqInit->u32DestNonSeqCnt = 0x00UL;
        pstcDmaNonSeqInit->u32DestNonSeqOfs = 0x00UL;
    }
    return enRet;
}

/**
 * @brief  DMA non-sequece mode initialize.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] pstcDmaRptInit DMA non-sequence mode config structure.
 *   @arg  u32SrcNonSeqEn   DMA source non-sequence enable or disable.
 *   @arg  u32SrcNonSeqCnt  DMA source non-sequence count.
 *   @arg  u32SrcNonSeqOfs  DMA source non-sequence offset.
 *   @arg  u32DestNonSeqEn  DMA destination non-sequence enable or disable.
 *   @arg  u32DestNonSeqCnt DMA destination non-sequence count.
 *   @arg  u32DestNonSeqOfs DMA destination non-sequence offset.
 * @retval Ok: DMA non-sequence function initilize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_NonSeqInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    en_result_t enRet = Ok;
    uint32_t *CHCTLx = 0UL;

    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaNonSeqInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_DMA_SRC_NS(pstcDmaNonSeqInit->u32SrcNonSeqEn));
        DDL_ASSERT(IS_DMA_DEST_NS(pstcDmaNonSeqInit->u32DestNonSeqEn));

        /* avoid warning 12.2 */
        //MODIFY_REG32(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch),                     \
            (DMA_CHCTL_SNSEQEN | DMA_CHCTL_DNSEQEN),                            \
            (pstcDmaNonSeqInit->u32SrcNonSeqEn | pstcDmaNonSeqInit->u32DestNonSeqEn));
        CHCTLx = &DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx,                                                    \
            (DMA_CHCTL_SNSEQEN | DMA_CHCTL_DNSEQEN),                            \
            (pstcDmaNonSeqInit->u32SrcNonSeqEn | pstcDmaNonSeqInit->u32DestNonSeqEn));

        WRITE_REG32(DMA_CH_REG(stcDmaReg->SNSEQCTL0, u8Ch),                     \
            ((pstcDmaNonSeqInit->u32SrcNonSeqCnt << DMA_SNSEQCTL_SNSCNT_POS) |  \
            pstcDmaNonSeqInit->u32SrcNonSeqOfs));
    }
    return enRet;
}

/**
 * @brief  Initialize DMA LLP mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaLlpInit Pointer to a stc_dma_llp_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA LLP mode config structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaLlpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaLlpInit->u32LlpEn    = DMA_LLP_DISABLE;
        pstcDmaLlpInit->u32LlpRun   = DMA_LLP_WAIT;
        pstcDmaLlpInit->u32Llp      = 0x00UL;
    }
    return enRet;
}

/**
 * @brief  DMA LLP mode initialize.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] pstcDmaLlpInit DMA LLP config structure.
 *   @arg  u32LlpEn         DMA LLP enable or disable.
 *   @arg  u32LlpRun        DMA LLP auto-run or wait request.
 *   @arg  u32Llp           DMA LLP next list pointer.
 * @retval Ok: DMA LLP function initilize successful
 *         ErrorInvalidParameter: NULL pointer
 * @note Call this function after DMA_Init();
 */
en_result_t DMA_LlpInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_llp_init_t *pstcDmaLlpInit)
{
    en_result_t enRet = Ok;
    uint32_t *CHCTLx = 0UL;

    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaLlpInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_DMA_LLP_EN(pstcDmaLlpInit->u32LlpEn));
        DDL_ASSERT(IS_DMA_LLP(pstcDmaLlpInit->u32Llp));
        DDL_ASSERT(IS_DMA_LLP_MODE(pstcDmaLlpInit->u32LlpRun));

        /* avoid warning 12.2 */
        //MODIFY_REG32(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch),                     \
            (DMA_CHCTL_LLPEN | DMA_CHCTL_LLPRUN),                               \
            (pstcDmaLlpInit->u32LlpEn | pstcDmaLlpInit->u32LlpRun));
        CHCTLx = &DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx,                                                   \
            (DMA_CHCTL_LLPEN | DMA_CHCTL_LLPRUN),                               \
            (pstcDmaLlpInit->u32LlpEn | pstcDmaLlpInit->u32LlpRun));

        WRITE_REG32(DMA_CH_REG(stcDmaReg->LLP0, u8Ch), pstcDmaLlpInit->u32Llp);
    }

    return enRet;
}

/**
 * @brief  Config DMA LLP value.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] u32Llp Next link pointer address for DMA LLP mode.
 * @retval None
 */
void DMA_SetLLP(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Llp)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_LLP(u32Llp));

    WRITE_REG32(DMA_CH_REG(stcDmaReg->LLP0, u8Ch), (u32Llp & 0xFFFFFFFCUL));
}

/**
 * @brief  DMA LLP enable or disable.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] enNewState New state of LLP function.
 * @retval None
 */
void DMA_LlpCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch), DMA_CHCTL_LLPEN);
    }
    else
    {
        CLEAR_REG32_BIT(DMA_CH_REG(stcDmaReg->CHCTL0, u8Ch), DMA_CHCTL_LLPEN);
    }
}

/**
 * @brief  DMA reconfig function enable or disable.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] enNewState New state of reconfig function.
 * @retval None
 */
void DMA_ReConfigCmd(M4_DMA_TypeDef *stcDmaReg, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(stcDmaReg->RCFGCTL, 1UL);
    }
    else
    {
        CLEAR_REG32_BIT(stcDmaReg->RCFGCTL, 1UL);
    }
}

/**
 * @brief  DMA LLP enable or disable  for reconfig function.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] enNewState New state of LLP function in reconfig case.
 * @retval None
 */
void DMA_ReConfigLlpCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    MODIFY_REG32(stcDmaReg->RCFGCTL, DMA_RCFGCTL_RCFGCHS, ((uint32_t)(u8Ch) << DMA_RCFGCTL_RCFGCHS_POS));
    WRITE_REG32(stcDmaReg->RCFGCTL, enNewState);
}

/**
 * @brief  Initialize DMA re-config mode config structure.
 *          Fill each pstcDmaRCInit with default value
 * @param  [in] pstcDmaRCInit Pointer to a stc_dma_reconfig_init_t structure that
 *                            contains configuration information.
 * @retval Ok: DMA reconfig mode config structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_ReConfigStructInit(stc_dma_reconfig_init_t *pstcDmaRCInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcDmaRCInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcDmaRCInit->u32CntMode       = DMA_RC_CNT_FIX;
        pstcDmaRCInit->u32DestAddrMode  = DMA_RC_DA_FIX;
        pstcDmaRCInit->u32SrcAddrMode   = DMA_RC_SA_FIX;
    }
    return enRet;
}

/**
 * @brief  DMA reconfig mode initialize.
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @param  [in] pstcDmaRCInit New state of LLP function.
 *   @arg  u32CntMode       DMA reconfig count mode.
 *   @arg  u32DestAddrMode  DMA reconfig destination address mode.
 *   @arg  u32SrcAddrMode   DMA reconfig source address mode.
 * @retval Ok: DMA reconfig function initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t DMA_ReConfigInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_reconfig_init_t *pstcDmaRCInit)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaRCInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_DMA_RC_CNT_MODE(pstcDmaRCInit->u32CntMode));
        DDL_ASSERT(IS_DMA_RC_DA_MODE(pstcDmaRCInit->u32DestAddrMode));
        DDL_ASSERT(IS_DMA_RC_SA_MODE(pstcDmaRCInit->u32SrcAddrMode));

        MODIFY_REG32(stcDmaReg->RCFGCTL,                                        \
            (DMA_RCFGCTL_RCFGCHS | DMA_RCFGCTL_SARMD | DMA_RCFGCTL_DARMD |      \
            DMA_RCFGCTL_CNTMD),                                                 \
            (pstcDmaRCInit->u32SrcAddrMode | pstcDmaRCInit->u32DestAddrMode |   \
            pstcDmaRCInit->u32DestAddrMode | ((uint32_t)(u8Ch) << DMA_RCFGCTL_RCFGCHS_POS)));
    }
    return enRet;
}

/**
 * @brief  DMA get current source address
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current source address.
 */
uint32_t DMA_GetSrcAddr(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return READ_REG32(DMA_CH_REG(stcDmaReg->MONSAR0, u8Ch));
}

/**
 * @brief  DMA get current destination address
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current destination address.
 */
uint32_t DMA_GetDestAddr(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return READ_REG32(DMA_CH_REG(stcDmaReg->MONDAR0, u8Ch));
}

/**
 * @brief  DMA get current transfer count
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current transfer count.
 */
uint32_t DMA_GetTransCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(stcDmaReg->MONDTCTL0, u8Ch)) >> DMA_DTCTL_CNT_POS) & 0xFFFFUL);
}

/**
 * @brief  DMA get current block size
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current block size.
 */
uint32_t DMA_GetBlockSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32(DMA_CH_REG(stcDmaReg->MONDTCTL0, u8Ch)) & DMA_DTCTL_BLKSIZE);
}

/**
 * @brief  DMA get current source repeat size
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current source repeat size.
 */
uint32_t DMA_GetSrcRptSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32(DMA_CH_REG(stcDmaReg->MONRPT0, u8Ch)) & DMA_RPT_SRPT);
}

/**
 * @brief  DMA get current destination repeat size
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current destination repeat size.
 */
uint32_t DMA_GetDestRptSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(stcDmaReg->MONRPT0, u8Ch)) >> DMA_RPT_DRPT_POS) & 0x3FFUL);
}

/**
 * @brief  DMA get current source count in non-sequence mode
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current source count in non-sequence mode.
 */
uint32_t DMA_GetNonSeqSrcCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(stcDmaReg->MONSNSEQCTL0, u8Ch)) >> DMA_SNSEQCTLB_SNSCNTB_POS) & 0xFFFUL);
}

/**
 * @brief  DMA get current destination count in non-sequence mode
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current destination count in non-sequence mode.
 */
uint32_t DMA_GetNonSeqDestCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(stcDmaReg->MONDNSEQCTL0, u8Ch)) >> DMA_DNSEQCTL_DNSCNT_POS) & 0xFFFUL);
}

/**
 * @brief  DMA get current source offset in non-sequence mode
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current source offset in non-sequence mode.
 */
uint32_t DMA_GetNonSeqSrcOffset(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32(DMA_CH_REG(stcDmaReg->MONSNSEQCTL0, u8Ch)) & DMA_SNSEQCTL_SOFFSET);
}

/**
 * @brief  DMA get current destination offset in non-sequence mode
 * @param  [in] stcDmaReg DMA unit instance.
 *   @arg  M4_DMA1 Unit1.
 *   @arg  M4_DMA2 Unit2.
 * @param  [in] u8Ch DMA channel.
 *   @arg  DMA_CH0.
 *   @arg  DMA_CH1.
 *   @arg  DMA_CH2.
 *   @arg  DMA_CH3.
 *   @arg  DMA_CH4.
 *   @arg  DMA_CH5.
 *   @arg  DMA_CH6.
 *   @arg  DMA_CH7.
 * @retval Current destination offset in non-sequence mode.
 */
uint32_t DMA_GetNonSeqDestOffset(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(stcDmaReg));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32(DMA_CH_REG(stcDmaReg->MONDNSEQCTL0, u8Ch)) & DMA_DNSEQCTL_DOFFSET);
}

/**
 * @}
 */

#endif  /* DDL_DMA_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
