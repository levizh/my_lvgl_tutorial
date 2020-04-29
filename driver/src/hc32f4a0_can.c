/**
 *******************************************************************************
 * @file  hc32f4a0_can.c
 * @brief This file provides firmware functions to manage the CAN.
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
#include "hc32f4a0_can.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CAN CAN
 * @brief CAN Driver Library
 * @{
 */

#if (DDL_CAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CAN_Local_Macros CAN Local Macros
 * @{
 */

/**
 * @defgroup CAN_Configuration_Bit_Mask CAN Configuration Bit Mask
 * @{
 */
#define CAN_LB_MODE_MSK                     (CAN_CFG_STAT_LBMI | CAN_CFG_STAT_LBME)
#define CAN_TRANS_MODE_MSK                  (CAN_CFG_STAT_TPSS | CAN_CFG_STAT_TSSS)
#define CAN_ERRINT_FLAS_MSK                 ((uint8_t)0xD5U)
#define CAN_BUS_STAT_MSK                    (0x7UL)
#define CAN_BUS_STAT_MSK_NOT                ((uint32_t)(~CAN_BUS_STAT_MSK))
#define CAN_ABORT_TB_MSK                    (CAN_TCMD_TPA | CAN_TCMD_TSA)
#define CAN_ACF_AIDE_MSK                    (CAN_ACF_AIDE | CAN_ACF_AIDEE)
#define CAN_TTC_TB_STATE_MSK                (CAN_TBSLOT_TBE | CAN_TBSLOT_TBF)
#define CAN_STATUS_FLAG_MSK                 (0xD5FF0127UL)
#define CAN_INT_TYPE_MSK                    (0x2AFEUL)
#define CAN_TTC_INT_TYPE_MSK                (CAN_TTC_INT_TTI | CAN_TTC_INT_WTI)
#define CAN_TTC_CLR_FLAG_MSK                (CAN_TTC_FLAG_TTI | CAN_TTC_FLAG_WTI)
#define CAN_TTC_GET_FLAG_MSK                (CAN_TTC_FLAG_TTI | CAN_TTC_FLAG_TEI | CAN_TTC_FLAG_WTI)
/**
 * @}
 */

/**
 * @defgroup CAN_Register_Bit_Band CAN Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(__reg__)                  ((uint32_t)&(__reg__) - __PERIP_BASE)
#define __BIT_BAND_ADDR(__reg__, __pos__)   ((__REG_OFS(__reg__) << 5U) + ((uint32_t)(__pos__) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(__reg__, __pos__)          (*(__IO uint32_t *)__BIT_BAND_ADDR((__reg__), (__pos__)))
/**
 * @}
 */

/**
 * @defgroup CAN_Check_Parameters_Validity CAN check parameters validity
 * @{
 */
#define IS_CAN_UNIT(x)                                                         \
(   ((x) == M4_CAN1)                            ||                             \
    ((x) == M4_CAN2))

#define IS_CAN_IDE(x)                                                          \
(   ((x) == 0U)                                 ||                             \
    ((x) == 1U))

#define IS_CAN_SELF_ACK_CMD(x)                                                 \
(   ((x) == CAN_SELF_ACK_DISABLE)               ||                             \
    ((x) == CAN_SELF_ACK_ENABLE))

#define IS_CAN_TB_TYPE(x)                                                      \
(   ((x) == CAN_PTB)                            ||                             \
    ((x) == CAN_STB))

#define IS_CAN_STB_TX_CTRL(x)                                                  \
(   ((x) == CAN_STB_TRANS_ALL)                  ||                             \
    ((x) == CAN_STB_TRANS_ONE))

#define IS_CAN_SET_STATE(x)                                                    \
(   ((x) == CAN_SET_NORMAL_COMM)                ||                             \
    ((x) == CAN_SET_SW_RESET))

#define IS_CAN_WORK_MODE(x)                                                    \
(   ((x) <= CAN_MODE_ELB_SILENT))

#define IS_CAN_TRANS_MODE(x)                                                   \
(   ((x) == CAN_TRANS_NORMAL)                   ||                             \
    ((x) == CAN_TRANS_PTB_SSHOT)                ||                             \
    ((x) == CAN_TRANS_STB_SSHOT)                ||                             \
    ((x) == CAN_TRANS_PTB_STB_SSHOT))

#define IS_CAN_SBT_PRIO_MODE(x)                                                \
(   ((x) == CAN_STB_PRIO_FIFO)                  ||                             \
    ((x) == CAN_STB_PRIO_ID))

#define IS_CAN_RB_STORE_SEL(x)                                                 \
(   ((x) == CAN_RB_STORE_CORRECT_DATA)          ||                             \
    ((x) == CAN_RB_STORE_ALL_DATA))

#define IS_CAN_RB_OVF_OP(x)                                                    \
(   ((x) == CAN_RB_OVF_SAVE_NEW)                ||                             \
    ((x) == CAN_RB_OVF_DISCARD_NEW))

#define IS_CAN_RBS_FULL_WARN_LIMIT(x)                                          \
(   ((x) >= CAN_RBS_WARN_LIMIT_MIN)             &&                             \
    ((x) <= CAN_RBS_WARN_LIMIT_MAX))

#define IS_CAN_ERR_WARN_LIMIT(x)                                               \
(   ((x) <= 15U))

#define IS_CAN_AF_MSK_TYPE(x)                                                  \
(   ((x) == CAN_AF_MSK_STD_EXT)                 ||                             \
    ((x) == CAN_AF_MSK_STD)                     ||                             \
    ((x) == CAN_AF_MSK_EXT))

#define IS_CAN_ABORT_TB(x)                                                     \
(   ((x) == CAN_ABORT_PTB)                      ||                             \
    ((x) == CAN_ABORT_STB)                      ||                             \
    ((x) == CAN_ABORT_PTB_STB))

#define IS_CAN_1_BIT_MSK(x)                                                    \
(   ((x) != 0U)                                 &&                             \
    (((x) & ((x) - 1U)) == 0U))

#define IS_CAN_BIT_MSK(x, msk)                                                 \
(   ((x) != 0U)                                 &&                             \
    (((x) | (msk)) == (msk)))

#define IS_CAN_FD_ISO_MODE(x)                                                  \
(   ((x) == CAN_FD_ISO_BOSCH)                   ||                             \
    ((x) == CAN_FD_ISO_11898))

#define IS_CAN_TDC_CMD(x)                                                      \
(   ((x) == CAN_TDC_DISABLE)                    ||                             \
    ((x) == CAN_TDC_ENABLE))

#define IS_TTC_TBS(x)                                                          \
(   ((x) <= CAN_TTC_TBS_STB_S3))

#define IS_TTC_TRIG_TYPE(x)                                                    \
(   ((x) == CAN_TTC_TRIG_IMMED)                 ||                             \
    ((x) == CAN_TTC_TRIG_TIME)                  ||                             \
    ((x) == CAN_TTC_TRIG_SSHOT_TRANS)           ||                             \
    ((x) == CAN_TTC_TRIG_TRANS_STRT)            ||                             \
    ((x) == CAN_TTC_TRIG_TRANS_STOP))

#define IS_TTC_TB_STATE(x)                                                     \
(   ((x) == CAN_TTC_SET_TB_FILLED)              ||                             \
    ((x) == CAN_TTC_SET_TB_EMPTY))

#define IS_TTC_TMR_PRESC(x)                                                    \
(   ((x) == CAN_TTC_TMR_PRESC_1)                ||                             \
    ((x) == CAN_TTC_TMR_PRESC_2)                ||                             \
    ((x) == CAN_TTC_TMR_PRESC_4)                ||                             \
    ((x) == CAN_TTC_TMR_PRESC_8))

#define IS_TTC_SST_TW(x)                                                       \
(   (x) < 16U)

/**
 * @}
 */

/**
 * @defgroup CAN_Miscellaneous_Macros CAN Miscellaneous Macros
 * @{
 */
#define CAN_BASE_ADDR                       (0x40009000UL)
#define CAN_RBS_CNT                         (8U)                /*!< Each CAN unit has 8 receive buffer slots. */
#define CAN_RBS_WARN_LIMIT_MIN              (1U)
#define CAN_RBS_WARN_LIMIT_MAX              (CAN_RBS_CNT)
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
 * @defgroup CAN_Global_Functions CAN Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified CAN peripheral according to the specified parameters
 *         in the stc_can_init_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcInit               Pointer to a stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL
 *                                     -pstcInit == NULL.
 */
en_result_t CAN_Init(M4_CAN_TypeDef *CANx, const stc_can_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcInit != NULL))
    {
        CAN_SWReset(CANx);
        CAN_SBTConfig(CANx, &pstcInit->stcSBT);

        CAN_SetSTBPrioMode(CANx, pstcInit->u8STBPrioMode);
        CAN_AFConfig(CANx, pstcInit->u16AFSel, pstcInit->pstcID);

        /* CAN bus enters normal communication mode. */
        CAN_EnterNormalComm(CANx);
        CAN_SetWorkMode(CANx, pstcInit->u8WorkMode);
        CAN_SetTransMode(CANx, pstcInit->u8TransMode);
        CAN_SetRBStoreSel(CANx, pstcInit->u8RBStoreSel);

        CAN_SetRBSWarnLimit(CANx, pstcInit->u8RBSWarnLimit);
        CAN_SetErrWarnLimit(CANx, pstcInit->u8ErrWarnLimit);
        CAN_SetRBOvfOp(CANx, pstcInit->u8RBOvfOp);
        CAN_AFCmd(CANx, pstcInit->u16AFSel, Enable);

        /* Enable or disable self-ACK. */
        DDL_ASSERT(IS_CAN_SELF_ACK_CMD(pstcInit->u8SelfACKCmd));
        MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_SACK, pstcInit->u8SelfACKCmd);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the CAN initialization structure. \
 *         Based on 40MHz CAN clock, TQ clock is CAN clock divided by 4. \
 *         Bit rate 500Kbps, 1 bit time is 20TQs, sample point is 75%.
 * @param  [in]  pstcInit               Pointer to a stc_can_init_t structure value that
 *                                      contains the configuration information for the CAN unit.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        pstcInit == NULL.
 */
en_result_t CAN_StructInit(stc_can_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u8WorkMode     = CAN_MODE_NORMAL;
        pstcInit->u8TransMode    = CAN_TRANS_NORMAL;
        pstcInit->u8STBPrioMode  = CAN_STB_PRIO_FIFO;
        pstcInit->u8RBSWarnLimit = 2U;
    	pstcInit->u8ErrWarnLimit = 7U;
        pstcInit->u16AFSel       = CAN_AF1;
        pstcInit->u8RBStoreSel   = CAN_RB_STORE_CORRECT_DATA;
        pstcInit->u8RBOvfOp      = CAN_RB_OVF_DISCARD_NEW;
        pstcInit->u8SelfACKCmd   = CAN_SELF_ACK_DISABLE;

        pstcInit->stcSBT.u32SEG1 = 16U;
        pstcInit->stcSBT.u32SEG2 = 4U;
        pstcInit->stcSBT.u32SJW  = 1U;
        pstcInit->stcSBT.u32Prescaler = 4U;

        pstcInit->pstcID = NULL;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the CAN peripheral. Reset the registers of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_DeInit(M4_CAN_TypeDef *CANx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        CAN_EnterNormalComm(CANx);

        WRITE_REG8(CANx->CFG_STAT, 0x80U);
        WRITE_REG8(CANx->TCMD, 0x00U);
        WRITE_REG8(CANx->TCTRL, 0x90U);
        WRITE_REG8(CANx->RCTRL, 0x00U);
        WRITE_REG8(CANx->RTIE, 0xFEU);
        WRITE_REG8(CANx->RTIF, 0x00U);
        WRITE_REG8(CANx->ERRINT, 0x00U);
        WRITE_REG8(CANx->LIMIT, 0x1BU);
        WRITE_REG32(CANx->SBT, 0x01020203U);
        WRITE_REG32(CANx->FBT, 0x01020203U);
        WRITE_REG8(CANx->EALCAP, 0x00U);
        WRITE_REG8(CANx->TDC, 0x00U);
        WRITE_REG8(CANx->RECNT, 0x00U);
        WRITE_REG8(CANx->TECNT, 0x00U);
        WRITE_REG8(CANx->ACFCTRL, 0x00U);
        WRITE_REG8(CANx->ACFEN, 0x01U);
        WRITE_REG8(CANx->TBSLOT, 0x00U);
        WRITE_REG8(CANx->TTCFG, 0x90U);
        WRITE_REG16(CANx->TRG_CFG, 0x00U);
        WRITE_REG16(CANx->TT_TRIG, 0x00U);
        WRITE_REG16(CANx->TT_WTRIG, 0x00U);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Software reset the specified CAN unit. \
           Software reset is a partial reset and CANNOT reset all registers. \
           Some registers need software reset before written.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_SWReset(M4_CAN_TypeDef *CANx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the CAN node to enter the normal communication mode.
 *         When this state is set, it takes 11 CAN bit time for this node to participate in communication.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_EnterNormalComm(M4_CAN_TypeDef *CANx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        CLEAR_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_RESET);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the CAN node state. Software reset or normal communication mode.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8NodeState            The state to be set.
 *                                      This parameter can be a value of @ref CAN_Node_Set_State
 *   @arg  CAN_SET_NORMAL_COMM:         Set the CAN node to enter the normal communication mode. \
 *                                      When this state is set, it takes 11 CAN bit time for this node \
 *                                      to participate in communication.
 *   @arg  CAN_SET_SW_RESET:            Set the CAN node software reset. Software reset is a partial reset \
 *                                      and CANNOT reset all registers.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_SetNodeState(M4_CAN_TypeDef *CANx, uint8_t u8NodeState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_SET_STATE(u8NodeState));
        BIT_BAND(CANx->CFG_STAT, CAN_CFG_STAT_RESET_POS) = (uint32_t)u8NodeState;
        enRet = Ok;
    }

    return enRet;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Set work mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8WorkMode             Work mode of CAN.
 *                                      This parameter can be a value of @ref CAN_Work_Mode
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 0.
 */
en_result_t CAN_SetWorkMode(M4_CAN_TypeDef *CANx, uint8_t u8WorkMode)
{
    uint8_t u8CFGSTAT = 0U;
    uint8_t u8TCMD    = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_WORK_MODE(u8WorkMode));

        switch (u8WorkMode)
        {
            case CAN_MODE_NORMAL:
                break;
            case CAN_MODE_SILENT:
                u8TCMD    = CAN_TCMD_LOM;
                break;
            case CAN_MODE_ILB:
                u8CFGSTAT = CAN_CFG_STAT_LBMI;
                break;
            case CAN_MODE_ELB:
                u8CFGSTAT = CAN_CFG_STAT_LBME;
                break;
            case CAN_MODE_ELB_SILENT:
                u8TCMD    = CAN_TCMD_LOM;
                u8CFGSTAT = CAN_CFG_STAT_LBME;
                break;
            default:
                break;
        }

        MODIFY_REG8(CANx->CFG_STAT, CAN_LB_MODE_MSK, u8CFGSTAT);
        MODIFY_REG8(CANx->TCMD, CAN_TCMD_LOM, u8TCMD);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify transmission mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TransMode            PTB/STB transmission mode.
 *                                      This parameter can be a value of @ref CAN_Trans_Mode
 *   @arg  CAN_TRANS_NORMAL:            Normal transmission mode. Both PTB and STB automatically retransmit.
 *   @arg  CAN_TRANS_PTB_SSHOT:         PTB single shot transmit.
 *   @arg  CAN_TRANS_STB_SSHOT:         STB single shot transmit.
 *   @arg  CAN_TRANS_PTB_STB_SSHOT:     STB and PTB both single shot transmit.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 0.
 */
en_result_t CAN_SetTransMode(M4_CAN_TypeDef *CANx, uint8_t u8TransMode)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_TRANS_MODE(u8TransMode));

        MODIFY_REG8(CANx->CFG_STAT, CAN_TRANS_MODE_MSK, u8TransMode);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify STB transmission priority mode for the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8STBPrioMode          STB transmission priority mode.
 *                                      This parameter can be a value of @ref CAN_STB_Priority_Mode
 *   @arg  CAN_STB_PRIO_FIFO:           Data first in first be transmitted.
 *   @arg  CAN_STB_PRIO_ID :            Data with smallest ID first be transmitted.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Whatever the priority mode of STB is, PTB always has the highest priority.
 */
en_result_t CAN_SetSTBPrioMode(M4_CAN_TypeDef *CANx, uint8_t u8STBPrioMode)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_SBT_PRIO_MODE(u8STBPrioMode));
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_TSMODE, u8STBPrioMode);
        //TRY: Try BIT_BAND
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the receive buffer store selection for specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8RBStoreSel           Receive buffer store selection.
 *                                      This parameter can be a value of @ref CAN_RB_Store_Selection
 *   @arg  CAN_RB_STORE_CORRECT_DATA:   Receive buffer stores correct data frames only.
 *   @arg  CAN_RB_STORE_ALL_DATA:       Receive buffer stores all data frames, includes error data.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 0.
 */
en_result_t CAN_SetRBStoreSel(M4_CAN_TypeDef *CANx, uint8_t u8RBStoreSel)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_RB_STORE_SEL(u8RBStoreSel));
        MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_RBALL, u8RBStoreSel);
        //TRY: Try BIT_BAND
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specify the operation when receive buffer overflow.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8RBOvfOp              Operation when receive buffer overflow.
 *                                      This parameter can be a value of @ref CAN_RB_Overflow_Operation
 *   @arg  CAN_RB_OVF_SAVE_NEW:         Saves the newly received data and the first received data will be overwritten.
 *   @arg  CAN_RB_OVF_DISCARD_NEW:      Discard the newly received data.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_SetRBOvfOp(M4_CAN_TypeDef *CANx, uint8_t u8RBOvfOp)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_RB_OVF_OP(u8RBOvfOp));
        MODIFY_REG8(CANx->RCTRL, CAN_RCTRL_ROM, u8RBOvfOp);
        //TODO: try BIT_BAND
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified interrupts of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32IntType             Interrupt type of CAN. Set this parameter to 0xFFFFFFFF to select all the interrupts of CAN.
 *                                      This parameter can be values of @ref CAN_Interrupt_Type
 *   @arg  CAN_INT_ERR_INT:             Register bit RTIE.EIE. Error interrupt.
 *   @arg  CAN_INT_STB_TRANS_OK:        Register bit RTIE.TSIE. Secondary transmit buffer was transmitted successfully.
 *   @arg  CAN_INT_PTB_TRANS_OK:        Register bit RTIE.TPIE. Primary transmit buffer was transmitted successfully.
 *   @arg  CAN_INT_RB_ALMOST_FULL:      Register bit RTIE.RAFIE. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_INT_RB_FIFO_FULL:        Register bit RTIE.RFIE. The FIFO of receive buffer is full.
 *   @arg  CAN_INT_RX_OVERRUN:          Register bit RTIE.ROIE. Receive buffers are full and there is a further message to be stored.
 *   @arg  CAN_INT_RX:                  Register bit RTIE.RIE. Received a valid data frame or remote frame.
 *   @arg  CAN_INT_BUS_ERR:             Register bit ERRINT.BEIE. Arbitration lost caused bus error
 *   @arg  CAN_INT_ARB_LOST:            Register bit ERRINT.ALIE. Arbitration lost.
 *   @arg  CAN_INT_ERR_PASSIVE:         Register bit ERRINT.EPIE. A change from error-passive to error-active or error-active to error-passive has occurred.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_IntCmd(M4_CAN_TypeDef *CANx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint8_t u8RTIE;
    uint8_t u8ERRINT;
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        u32IntType &= CAN_INT_TYPE_MSK;
        u8RTIE      = (uint8_t)u32IntType;
        u8ERRINT    = (uint8_t)(u32IntType >> 8U);

        if (enNewState == Enable)
        {
            SET_REG8_BIT(CANx->RTIE, u8RTIE);
            SET_REG8_BIT(CANx->ERRINT, u8ERRINT);
        }
        else
        {
            CLEAR_REG8_BIT(CANx->RTIE, u8RTIE);
            CLEAR_REG8_BIT(CANx->ERRINT, u8ERRINT);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures slow bit timing(SBT).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_bt_cfg_t structure value that
 *                                      contains the configuration information for SBT.
 *   @arg  u32SEG1:                     Range [2, 65]. For CAN2.0 whole and CAN FD arbitration segment.
 *   @arg  u32SEG2:                     Range [1, 8] for CAN2.0. Range [1, 32] for CAN FD arbitration segment.
 *   @arg  u32SJW:                      Range [1, 16]. For CAN2.0 whole and CAN FD arbitration segment.
 *   @arg  u32Prescaler:                Range [1, 256].
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -pstcCfg == NULL.
 * @note 1. Restrictions: u32SEG1 >= u32SEG2 + 1, u32SEG2 >= u32SJW.
 * @note 2. TQ = u32Prescaler / CANClock.
 * @note 3. Slow bit time = (u32SEG1 + u32SEG2) × TQ.
 * @note 4. Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_SBTConfig(M4_CAN_TypeDef *CANx, const stc_can_bt_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcCfg != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        CANx->SBT = (pstcCfg->u32SEG1 - 2U) | \
                    ((pstcCfg->u32SEG2 - 1U) << CAN_SBT_S_SEG_2_POS) | \
                    ((pstcCfg->u32SJW - 1U) << CAN_SBT_S_SJW_POS)    | \
                    ((pstcCfg->u32Prescaler - 1U) << CAN_SBT_S_PRESC_POS);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get arbitration lost position of a frame.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval A uint8_t type value of arbitration lost position.
 */
uint8_t CAN_GetArbLostPos(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0U;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->EALCAP & CAN_EALCAP_ALC;
    }

    return u8Ret;
}

/**
 * @brief  Get error type.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t value of error type.
 *   @arg  CAN_ERR_NO:                  No error.
 *   @arg  CAN_ERR_BIT:                 Error is bit error.
 *   @arg  CAN_ERR_FORM:                Error is form error.
 *   @arg  CAN_ERR_STUFF:               Error is stuff error.
 *   @arg  CAN_ERR_ACK:                 Error is ACK error.
 *   @arg  CAN_ERR_CRC:                 Error is CRC error.
 *   @arg  CAN_ERR_OTHER:               Error is other error.
 *   @arg  0xFF:                        An invalid return value if CANx == NULL.
 */
uint8_t CAN_GetErrType(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0xFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->EALCAP & CAN_EALCAP_KOER;
    }

    return u8Ret;
}

/**
 * @brief  Set receive buffer slots full warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in] u8RBSWarnLimit:         Receive buffer slots full warning limit. Rang is [1, 8].
 *                                      Each CAN unit has 8 receive buffer slots. When the number of received frames \
 *                                      reaches the set value of u8RBSWarnLimit, register bit RTIF.RAFIF is set and \
 *                                      the interrupt occurred if it was enabled.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_SetRBSWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8RBSWarnLimit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_RBS_FULL_WARN_LIMIT(u8RBSWarnLimit));

        u8RBSWarnLimit <<= CAN_LIMIT_AFWL_POS;
        MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_AFWL, u8RBSWarnLimit);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set error warning limit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8ErrWarnLimit         Programmable error warning limit. Range is [0, 15].
 *                                      Error warning limit = (u8ErrWarnLimit + 1) * 8.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -u8ErrWarnLimit >= 16U
 * @note //TODO: Restrictions
 */
en_result_t CAN_SetErrWarnLimit(M4_CAN_TypeDef *CANx, uint8_t u8ErrWarnLimit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (u8ErrWarnLimit < 16U))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_ERR_WARN_LIMIT(u8ErrWarnLimit));
        MODIFY_REG8(CANx->LIMIT, CAN_LIMIT_EWL, u8ErrWarnLimit);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get receive error count(REC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of REC.
 */
uint8_t CAN_GetREC(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 255U;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->RECNT;
    }

    return u8Ret;
}

/**
 * @brief  Clear receive error count(REC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Set CFG_STAT.BUSOFF to 1 to clear REC, ONLY for TEST mode!
 */
en_result_t CAN_ClrREC(M4_CAN_TypeDef *CANx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_BUSOFF);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get transmission error count(TEC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of TEC.
 */
uint8_t CAN_GetTEC(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 255U;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->TECNT;
    }

    return u8Ret;
}

/**
 * @brief  Clear transmission error count(TEC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Set CFG_STAT.BUSOFF to 1 to clear TEC, ONLY for TEST mode!
 */
en_result_t CAN_ClrTEC(M4_CAN_TypeDef *CANx)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        SET_REG8_BIT(CANx->CFG_STAT, CAN_CFG_STAT_BUSOFF);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures acceptance filter. Set ID and ID mask for the specified acceptance filters.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16AFSel               Acceptance filter enable bit.
 *                                      This parameter can be values of @ref CAN_AF
 *   @arg CAN_AF1 ~ CAN_AF16
 * @param  [in]  pstcID                 Points to a stc_can_af_id_t structure type array which contains ID and ID mask
 *                                      values for the acceptance filters specified by parameter u16AFSel.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -u16AFSel == 0U.
 *                                     -pstcID == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_AFConfig(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, const stc_can_af_id_t pstcID[])
{
    uint8_t u8AFAddr = 0U;
    uint8_t i = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (u16AFSel != 0U) && (pstcID != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        while (u16AFSel != 0U)
        {
            if ((u16AFSel & (uint16_t)0x1U) != 0U)
            {
                DDL_ASSERT(IS_CAN_AF_MSK_TYPE(pstcID[i].u32MskType));

                WRITE_REG8(CANx->ACFCTRL, u8AFAddr);
                WRITE_REG32(CANx->ACF, pstcID[i].u32ID);
                SET_REG8_BIT(CANx->ACFCTRL, CAN_ACFCTRL_SELMASK);
                WRITE_REG32(CANx->ACF, pstcID[i].u32IDMsk | pstcID[i].u32MskType);
                i++;
            }

            u16AFSel >>= 1U;
            u8AFAddr++;
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable acceptance filter.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16AFSel               Acceptance filter enable bit.
 *                                      This parameter can be values of @ref CAN_AF
 *   @arg CAN_AF1 ~ CAN_AF16
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the acceptance filters that specified by parameter u16AFSel.
 *   @arg Disable:                      Disable the acceptance filters that specified by parameter u16AFSel.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_AFCmd(M4_CAN_TypeDef *CANx, uint16_t u16AFSel, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (enNewState == Enable)
        {
            SET_REG16_BIT(CANx->ACFEN, u16AFSel);
        }
        else
        {
            CLEAR_REG16_BIT(CANx->ACFEN, u16AFSel);
        }

        enRet = Ok;
    }

    return enRet;
}

#if 0
/**
 * @brief  Sepcifies acceptance type for acceptance filter(AF).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8AFType               AF type.
 *                                      This parameter can be a value of @ref CAN_AF_Type
 *   @arg  CAN_AF_STD_ID:               Acceptance filter accept standard ID.
 *   @arg  CAN_AF_EXT_ID:               Acceptance filter accept extended ID.
 *   @arg  CAN_AF_STD_ID_MSK:           Acceptance filter accept standard ID, but ingore the mask bits.
 *   @arg  CAN_AF_EXT_ID_MSK:           Acceptance filter accept extended ID, but ingore the mask bits.
 *   @arg  CAN_AF_STD_EXT_ID_MSK:       Acceptance filter accept both standard ID and extended ID, but ingore the mask bits of both.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_AFSetType(M4_CAN_TypeDef *CANx, uint8_t u8AFType)
{
    uint32_t u32SELMASK = 0U;
    uint32_t u32AIDEE   = 0U;
    uint32_t u32AIDE    = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_AF_TYPE(u8AFType));

        switch (u8AFType)
        {
            case CAN_AF_STD_ID:
                break;
            case CAN_AF_EXT_ID:
                u32AIDE    = CAN_ACF_AIDE;
                break;
            case CAN_AF_STD_ID_MSK:
                u32SELMASK = 1U;
                u32AIDEE   = CAN_ACF_AIDEE;
                break;
            case CAN_AF_EXT_ID_MSK:
                u32SELMASK = 1U;
                u32AIDEE   = CAN_ACF_AIDEE;
                u32AIDE    = CAN_ACF_AIDE;
                break;
            case CAN_AF_STD_EXT_ID_MSK:
                u32SELMASK = 1U;
                break;
            default:
                break;
        }

        BIT_BAND(CANx->ACFCTRL, CAN_ACFCTRL_SELMASK_POS) = u32SELMASK;
        MODIFY_REG32(CANx->ACF, CAN_ACF_AIDE_MSK, (u32AIDE | u32AIDEE));

        enRet = Ok;
    }

    return enRet;
}
#endif

/**
 * @brief  Cancel the transmission of the specified transmit buffer that ready but not started.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8CancelTB             The transmit buffer to be cancelled.
 *                                      This parameter can be a value of @ref CAN_Abort_Transmit_Buffer
 *   @arg  CAN_ABORT_PTB:               Cancel PTB transmission that ready but not started.
 *   @arg  CAN_ABORT_STB:               Cancel STB transmission that ready but not started.
 *   @arg  CAN_ABORT_PTB_STB:           Cancel both STB transmission and PTB transmission that ready but not started.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 0.
 */
en_result_t CAN_AbortTrans(M4_CAN_TypeDef *CANx, uint8_t u8AbortTB)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_ABORT_TB(u8AbortTB));
        CLEAR_REG8_BIT(CANx->TCMD, u8AbortTB);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the common flag's status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32Flag                Status flag.
 *                                      This parameter can be a value of @ref CAN_Common_Status_Flag
 *   @arg  CAN_FLAG_BUS_OFF:            Register bit CFG_STAT.BUSOFF. CAN bus off.
 *   @arg  CAN_FLAG_BUS_TX:             Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *   @arg  CAN_FLAG_BUS_RX:             Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *   @arg  CAN_FLAG_RB_OVF:             Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TB_FULL:            Register bit RTIE.TSFF. Transmit buffers are all full: \
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled. \
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *   @arg  CAN_FLAG_TRANS_ABORTED:      Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter and the \
 *                                      set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TRANS_O:        Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TRANS_OK:       Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RB_ALMOST_FULL:     Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RB_FIFO_FULL:       Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX:                 Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. Arbitration lost caused bus error.
 *   @arg  CAN_FLAG_ARB_LOST:           Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_REACH_WARN_LIMIT:   Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg Set:                          The specified status flag is set.
 *   @arg Reset:                       -The specified status flag is not set.
 *                                     -CANx == NULL.
 */
en_flag_status_t CAN_GetStatus(const M4_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8CFGSTAT;
    uint8_t u8RCTRL;
    uint8_t u8RTIE;
    uint8_t u8RTIF;
    uint8_t u8ERRINT;

    en_flag_status_t enFlag = Reset;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_BIT_MSK(u32Flag, CAN_STATUS_FLAG_MSK));
        DDL_ASSERT(IS_CAN_1_BIT_MSK(u32Flag));

        u8CFGSTAT = (uint8_t)(u32Flag & CAN_BUS_STAT_MSK);
        u8RCTRL   = (uint8_t)(u32Flag & CAN_BUS_STAT_MSK_NOT);
        u8RTIE    = (uint8_t)(u32Flag >> 8U);
        u8RTIF    = (uint8_t)(u32Flag >> 16U);
        u8ERRINT  = (uint8_t)(u32Flag >> 24U);

        u8CFGSTAT = CANx->CFG_STAT & u8CFGSTAT;
        u8RCTRL   = CANx->RCTRL & u8RCTRL;
        u8RTIE    = CANx->RTIE & u8RTIE;
        u8RTIF    = CANx->RTIF & u8RTIF;
        u8ERRINT  = CANx->ERRINT & u8ERRINT;

        if ((u8CFGSTAT != 0U) || (u8RCTRL != 0U) || \
            (u8RTIE != 0U) || (u8RTIF != 0U) || (u8ERRINT != 0U))
        {
            enFlag = Set;
        }
    }

    return enFlag;
}

/**
 * @brief  Clear the common flag's status.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32Flag                Status flag. Set this parameter to 0xFFFFFFFF to select all sataus flags of CAN.
 *                                      This parameter can be a value of @ref CAN_Common_Status_Flag
 *   @arg  CAN_FLAG_BUS_OFF:            Register bit CFG_STAT.BUSOFF. CAN bus off.
 *   @arg  CAN_FLAG_BUS_TX:             Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
 *   @arg  CAN_FLAG_BUS_RX:             Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
 *   @arg  CAN_FLAG_RB_OVF:             Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least one data is lost.
 *   @arg  CAN_FLAG_TB_FULL:            Register bit RTIE.TSFF. Transmit buffers are all full: \
 *                                      TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled. \
 *                                      TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
 *   @arg  CAN_FLAG_TRANS_ABORTED:      Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully canceled.
 *   @arg  CAN_FLAG_ERR_INT:            Register bit RTIF.EIF. The CFG_STAT.BUSOFF bit changes, or the relative relationship between the value of the error counter \
 *                                      and the set value of the ERROR warning limit changes. For example, the value of the error counter changes from less than \
 *                                      the set value to greater than the set value, or from greater than the set value to less than the set value.
 *   @arg  CAN_FLAG_STB_TRANS_O:        Register bit RTIF.TSIF. STB was transmitted successfully.
 *   @arg  CAN_FLAG_PTB_TRANS_OK:       Register bit RTIF.TPIF. PTB was transmitted successfully.
 *   @arg  CAN_FLAG_RB_ALMOST_FULL:     Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL setting value.
 *   @arg  CAN_FLAG_RB_FIFO_FULL:       Register bit RTIF.RFIF. The FIFO of receive buffer is full.
 *   @arg  CAN_FLAG_RX_OVERRUN:         Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be stored.
 *   @arg  CAN_FLAG_RX:                 Register bit RTIF.RIF. Received a valid data frame or remote frame.
 *   @arg  CAN_FLAG_BUS_ERR:            Register bit ERRINT.BEIF. Arbitration lost caused bus error.
 *   @arg  CAN_FLAG_ARB_LOST:           Register bit ERRINT.ALIF. Arbitration lost.
 *   @arg  CAN_FLAG_ERR_PASSIVE:        Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to error-passive has occurred.
 *   @arg  CAN_FLAG_ERR_PASSIVE_NODE:   Register bit ERRINT.EPASS. The node is an error-passive node.
 *   @arg  CAN_FLAG_REACH_WARN_LIMIT:   Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_ClrStatus(M4_CAN_TypeDef *CANx, uint32_t u32Flag)
{
    uint8_t u8RCTRL;
    uint8_t u8RTIF;
    uint8_t u8ERRINT;

    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        u32Flag &= CAN_STATUS_FLAG_MSK;
        u8RCTRL  = (uint8_t)(u32Flag & CAN_BUS_STAT_MSK_NOT);
        u8RTIF   = (uint8_t)(u32Flag >> 16U);
        u8ERRINT = (uint8_t)(u32Flag >> 24U);

        if (u8RCTRL & (uint8_t)CAN_FLAG_RB_OVF)
        {
            CANx->RCTRL |= CAN_RCTRL_RREL;
        }
        CANx->RTIF   |= u8RTIF;
        CANx->ERRINT |= (u8ERRINT & CAN_ERRINT_FLAS_MSK);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get status(full or empty) of transmit buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of status of transmit buffer. It's can be a value of @ref CAN_TB_Status
 *   @arg  CAN_TB_STAT_EMPTY:           TTCAN is disabled(TTEN == 0): STB is empty.
 *                                      TTCAN is disabled(TTEN == 1) and transmit buffer is specified by TBPTR and TTPTR(TTTBM == 1):
 *                                      PTB and STB are both empty.
 *   @arg  CAN_TB_STAT_LESS_HALF:       TTEN == 0: STB is not less than half full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are neither empty.
 *   @arg  CAN_TB_STAT_MORE_HALF:       TTEN == 0: STB is more than half full;
 *                                      TTEN == 1 && TTTBM == 1: reserved value.
 *   @arg  CAN_TB_STAT_FULL             TTEN == 0: STB is full;
 *                                      TTEN == 1 && TTTBM == 1: PTB and STB are both full.
 *   @arg  0xFFU:                       An invalid value when CANx == NULL.
 */
uint8_t CAN_GetTBFullStatus(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0xFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->TCTRL & CAN_TCTRL_TSSTAT;
    }

    return u8Ret;
}

/**
 * @brief  Get status(full or empty) of receive buffer.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of status of receive buffer. It's can be a value of @ref CAN_RB_Status
 *   @arg  CAN_RB_STAT_EMPTY:           Receive buffer(RB) is empty.
 *   @arg  CAN_RB_STAT_LESS_WARN_LIMIT: RB is not empty, but is less than almost full warning limit.
 *   @arg  CAN_RB_STAT_MORE_WARN_LIMIT: RB is not full, but is more than or equal to almost full warning limit.
 *   @arg  CAN_RB_STAT_FULL:            RB is full.
 *   @arg  0xFFU:                       An invalid value when CANx == NULL.
 */
uint8_t CAN_GetRBFullStatus(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0xFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = CANx->RCTRL & CAN_RCTRL_RSTAT;
    }

    return u8Ret;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Configures the specified CAN FD according to the specified parameters
 *         in the stc_can_fd_cfg_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_fd_cfg_t structure value that
 *                                      contains the configuration information for the CAN FD.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL
 *                                     -pstcCfg == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_FD_Config(M4_CAN_TypeDef *CANx, const stc_can_fd_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcCfg != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_FD_ISO_MODE(pstcCfg->u8CANFDISO));
        DDL_ASSERT(IS_CAN_TDC_CMD(pstcCfg->u8TDCCmd));

        /* Specify CAN FD ISO mode. */
        MODIFY_REG8(CANx->TCTRL, CAN_TCTRL_FD_ISO, pstcCfg->u8CANFDISO);

        CAN_FD_FBTConfig(CANx, &pstcCfg->stcFBT);

        CAN_FD_TDCSetSSP(CANx, pstcCfg->u8TDCSSP);
        /* Enable or disable TDC. */
        MODIFY_REG8(CANx->TDC, CAN_TDC_TDCEN, pstcCfg->u8TDCCmd);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the CAN FD configuration structure.
 * @param  [in]  pstcInit               Pointer to a stc_can_fd_cfg_t structure value that
 *                                      contains the configuration information for the CAN FD.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        pstcCfg == NULL.
 * @note //TODO:
 */
en_result_t CAN_FD_StructInit(stc_can_fd_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u8CANFDISO     = CAN_FD_ISO_BOSCH;
        pstcCfg->u8TDCCmd       = CAN_TDC_ENABLE;
        pstcCfg->u8TDCSSP       = 80U;
        pstcCfg->stcFBT.u32SEG1 = 32U;
        pstcCfg->stcFBT.u32SEG2 = 8U;
        pstcCfg->stcFBT.u32SJW  = 8U;
        pstcCfg->stcFBT.u32Prescaler = 2U;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures fast bit timing(FBT).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_bt_cfg_t structure value that
 *                                      contains the configuration information for FBT.
 *   @arg  u32SEG1:                     Range [2, 17] for CAN FD data segment.
 *   @arg  u32SEG2:                     Range [1, 8] for CAN FD data segment.
 *   @arg  u32SJW:                      Range [1, 8] for CAN FD data segment.
 *   @arg  u32Prescaler:                Range [1, 256].
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -pstcCfg == NULL.
 * @note 1. Restrictions: u32SEG1 >= u32SEG2 + 1, u32SEG2 >= u32SJW.
 * @note 2. TQ = u32Prescaler / CANClock.
 * @note 3. Fast bit time = (u32SEG1 + u32SEG2) × TQ.
 * @note 4. Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_FD_FBTConfig(M4_CAN_TypeDef *CANx, const stc_can_bt_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcCfg != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        CANx->FBT = (pstcCfg->u32SEG1 - 2U) | \
                    ((pstcCfg->u32SEG2 - 1U) << CAN_FBT_F_SEG_2_POS) | \
                    ((pstcCfg->u32SJW - 1U) << CAN_FBT_F_SJW_POS)    | \
                    ((pstcCfg->u32Prescaler - 1U) << CAN_FBT_F_PRESC_POS);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set secondary sample point(SSP) of transmitter delay compensatin(TDC)
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TDCSSP               Secondary sample point. It is recommended to be the same as F_SEG_1.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_FD_TDCSetSSP(M4_CAN_TypeDef *CANx, uint8_t u8TDCSSP)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        MODIFY_REG8(CANx->TDC, CAN_TDC_SSPOFF, u8TDCSSP);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable transmitter delay compensation(TDC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the TDC.
 *   @arg Disable:                      Disable the TDC.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_FD_TDCCmd(M4_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
        BIT_BAND(CANx->TDC, CAN_TDC_TDCEN_POS) = (uint32_t)enNewState;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable CAN FD.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable CAN FD.
 *   @arg  Disable:                     Disable CAN FD.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_FD_Cmd(const M4_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    uint8_t u8Temp;
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u8Temp = (((uint32_t)&CANx->RBUF - CAN_BASE_ADDR) == 0U) ? 0U : 1U;
        BIT_BAND(M4_PERIC->CAN_SYCTLREG, u8Temp) = (uint32_t)enNewState;

        enRet = Ok;
    }

    return enRet;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Configures the specified CAN TTC(time-triggered communication) according to the specified parameters
 *         in the stc_can_ttc_cfg_t type structure.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcCfg                Pointer to a stc_can_ttc_cfg_t structure value that
 *                                      contains the configuration information for the CAN TTC.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -pstcCfg == NULL.
 */
en_result_t CAN_TTC_Config(M4_CAN_TypeDef *CANx, const stc_can_ttc_cfg_t *pstcCfg)
{
    //TODO:
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcCfg != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));

        CAN_TTC_SetTmrPresc(CANx, pstcCfg->u8TmrPresc);
        CAN_TTC_SetRefIDE(CANx, pstcCfg->u32RefIDE);
        CAN_TTC_SetRefID(CANx, pstcCfg->u32RefID);
        CAN_TTC_SetTBS(CANx, pstcCfg->u8TBS);
        CAN_TTC_SetTransTrigTBS(CANx, (uint8_t)(pstcCfg->u16TxTrigTBS));
        CAN_TTC_SetTrigType(CANx, pstcCfg->u16TrigType);
        CAN_TTC_SetTransEnWindow(CANx, pstcCfg->u16TxEnWindow);
        CAN_TTC_SetTransTrigTime(CANx, pstcCfg->u16TxTrigTime);
        CAN_TTC_SetWatchTrigTime(CANx, pstcCfg->u16WatchTrigTime);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the CAN TTC(time-triggered communication) configuration structure.
 * @param  [in]  pstcInit               Pointer to a stc_can_ttc_cfg_t structure value that
 *                                      contains the configuration information for the CAN TTC.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        pstcCfg == NULL.
 */
en_result_t CAN_TTC_StructInit(stc_can_ttc_cfg_t *pstcCfg)
{
    //TODO:
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {/*
        pstcCfg->u8TmrPresc = ;
        pstcCfg->enRefIDE = ;
        pstcCfg->u32RefID = ;
        pstcCfg->u8TBS = ;
        pstcCfg->u16TxTrigTBS = ;
        pstcCfg->u16TrigType = ;
        pstcCfg->u16TxEnWindow = ;
        pstcCfg->u16TxTrigTime = ;
        pstcCfg->u16WatchTrigTime = ;*/

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifies transmit buffer slot(TBS) for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16SlotPtr             Transmit-trigger transmit buffer slot.
 *                                      This parameter can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB_S1:          TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB_S2:          TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB_S3:          TBS pointer points to STB slot 3.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTBS(M4_CAN_TypeDef *CANx, uint8_t u8SlotPtr)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_TBS(u8SlotPtr));
        MODIFY_REG8(CANx->TBSLOT, CAN_TBSLOT_TBPTR, u8SlotPtr);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get transmit buffer slot(TBS) of specified CAN unit's time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of transmit buffer slot pointer. It is can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB_S1:          TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB_S2:          TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB_S3:          TBS pointer points to STB slot 3.
 *   @arg  0xFF:                        Invalid value if CANx == NULL.
 */
uint8_t CAN_TTC_GetTBS(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0xFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = (CANx->TBSLOT & CAN_TBSLOT_TBPTR);
    }

    return u8Ret;
}

#if 0
/**
 * @brief  Specifies transmit buffer(TB) state for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TBSetState           Transmit buffer state.
 *                                      This parameter can be a value of @ref CAN_TTC_Set_TB_State
 *   @arg  CAN_TTC_SET_TB_FILLED:       Set TB slot that pointed by TB slot pointer to "filled".
 *   @arg  CAN_TTC_SET_TB_EMPTY:        Set TB slot that pointed by TB slot pointer to "empty".
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * //TODO:This function maybe used for transmission.
 */
en_result_t CAN_TTC_SetTBState(M4_CAN_TypeDef *CANx, uint8_t u8TBSetState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_TB_STATE(u8TBSetState));
        MODIFY_REG8(CANx->TBSLOT, CAN_TTC_TB_STATE_MSK, u8TBSetState);
        enRet = Ok;
    }

    return enRet;
}
#endif

/**
 * @brief  Enable or disable time-triggered communication(TTC) of the specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable TTC.
 *   @arg  Disable:                     Disable TTC.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 0.
 */
en_result_t CAN_TTC_Cmd(M4_CAN_TypeDef *CANx, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        BIT_BAND(CANx->TTCFG, CAN_TTCFG_TTEN_POS) = (uint32_t)enNewState;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifies time-triggered communication(TTC) timer prescaler.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8TmrPresc             Time-triggered communication timer prescaler.
 *                                      This parameter can be a value of @ref CAN_TTC_Timer_Prescaler
 *   @arg  CAN_TTC_TMR_PRESC_1          //TODO:
 *   @arg  CAN_TTC_TMR_PRESC_2
 *   @arg  CAN_TTC_TMR_PRESC_4
 *   @arg  CAN_TTC_TMR_PRESC_8
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTmrPresc(M4_CAN_TypeDef *CANx, uint8_t u8TmrPresc)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_TMR_PRESC(u8TmrPresc));

        MODIFY_REG8(CANx->TTCFG, CAN_TTCFG_T_PRESC, u8TmrPresc);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified interrupts of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8IntType              Interrupt type of TTC.
 *                                      This parameter can be values of @ref CAN_TTC_Interrupt_Type
 *   @arg  CAN_TTC_INT_TTI:             Time trigger interrupt.
 *   @arg  CAN_TTC_INT_WTI:             Watch trigger interrupt.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_IntCmd(M4_CAN_TypeDef *CANx, uint8_t u8IntType, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        u8IntType &= CAN_TTC_INT_TYPE_MSK;
        if (enNewState == Enable)
        {
            SET_REG8_BIT(CANx->TTCFG, u8IntType);
        }
        else
        {
            CLEAR_REG8_BIT(CANx->TTCFG, u8IntType);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get flag status of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8Flag                 Status flag of TTC.
 *                                      This parameter can be a value of @ref CAN_TTC_Status_Flag
 *   @arg  CAN_TTC_FLAG_TTI:            Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_TEI:            Trigger error interrupt flag.
 *   @arg  CAN_TTC_FLAG_WTI:            Watch trigger interrupt flag.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg Set:                          The specified flag is set.
 *   @arg Reset:                       -The specified flag is reset.
 *                                     -CANx == NULL.
 */
en_flag_status_t CAN_TTC_GetStatus(const M4_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    en_flag_status_t enFlag = Reset;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Flag &= CAN_TTC_GET_FLAG_MSK;
        if ((CANx->TTCFG & u8Flag) != 0U)
        {
            enFlag = Set;
        }
    }

    return enFlag;
}

/**
 * @brief  Clear flag status of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u8Flag                 Status flag of TTC.
 *                                      This parameter can be a value of @ref CAN_TTC_Status_Flag except CAN_TTC_FLAG_TEI.
 *   @arg  CAN_TTC_FLAG_TTI:            Time trigger interrupt flag.
 *   @arg  CAN_TTC_FLAG_WTI:            Watch trigger interrupt flag.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_ClrStatus(M4_CAN_TypeDef *CANx, uint8_t u8Flag)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        SET_REG8_BIT(CANx->TTCFG, (u8Flag & CAN_TTC_CLR_FLAG_MSK));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifies reference message ID of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32ID                  Reference message ID.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_TTC_SetRefID(M4_CAN_TypeDef *CANx, uint32_t u32ID)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        MODIFY_REG32(CANx->REF_MSG, CAN_REF_MSG_REF_ID, u32ID);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifiy IDE of TTC(time-triggered communication) reference message.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u32IDE                 IDE bit.
 *   @arg  0:                           Standard ID.
 *   @arg  1:                           Extended ID.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetRefIDE(M4_CAN_TypeDef *CANx, uint32_t u32IDE)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_IDE(u32IDE));
        BIT_BAND(CANx->REF_MSG, CAN_REF_MSG_REF_IDE_POS) = u32IDE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get reference message ID of time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint32_t value of reference message ID.
 *   @arg 0xFFFFFFFFUL:                 An invalid value if CANx == NULL.
 */
uint32_t CAN_TTC_GetID(const M4_CAN_TypeDef *CANx)
{
    uint32_t u32Ret = 0xFFFFFFFFUL;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u32Ret = CANx->REF_MSG & CAN_REF_MSG_REF_ID;
    }

    return u32Ret;
}

/**
 * @brief  Specifies transmit-trigger transmit buffer slot(TBS) for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16SlotPtr             Transmit-trigger transmit buffer slot.
 *                                      This parameter can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB_S1:          TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB_S2:          TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB_S3:          TBS pointer points to STB slot 3.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTransTrigTBS(M4_CAN_TypeDef *CANx, uint8_t u8SlotPtr)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_TBS(u8SlotPtr));
        MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTPTR, u8SlotPtr);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get transmit-trigger transmit buffer slot(TBS) of specified CAN unit's time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint8_t type value of transmit buffer slot pointer. It is can be a value of @ref CAN_TTC_TBS_Pointer
 *   @arg  CAN_TTC_TBS_PTB:             TBS pointer points to PTB.
 *   @arg  CAN_TTC_TBS_STB_S1:          TBS pointer points to STB slot 1.
 *   @arg  CAN_TTC_TBS_STB_S2:          TBS pointer points to STB slot 2.
 *   @arg  CAN_TTC_TBS_STB_S3:          TBS pointer points to STB slot 3.
 *   @arg  0xFF:                        Invalid value if CANx == NULL.
 */
uint8_t CAN_TTC_GetTransTrigTBS(const M4_CAN_TypeDef *CANx)
{
    uint8_t u8Ret = 0xFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u8Ret = (uint8_t)(CANx->TRG_CFG & CAN_TRG_CFG_TTPTR);
    }

    return u8Ret;
}

/**
 * @brief  Specifies trigger type for time-triggered communication(TTC) of specified CAN unit.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16TrigType            Time-triggered communication trigger type.
 *                                      This parameter can be a value of @ref CAN_TTC_Trigger_Type
 *   @arg  CAN_TTC_TRIG_IMMED:          Immediate trigger for immediate transmission.
 *   @arg  CAN_TTC_TRIG_TIME:           Time trigger for receive triggers.
 *   @arg  CAN_TTC_TRIG_SSHOT_TRANS:    Single shot transmit trigger for exclusive time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STRT:     Transmit start trigger for merged arbitrating time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STOP:     Transmit stop trigger for merged arbitrating time windows.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTrigType(M4_CAN_TypeDef *CANx, uint16_t u16TrigType)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_TRIG_TYPE(u16TrigType));
        MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TTYPE, u16TrigType);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get trigger type of specified CAN unit's time-triggered communication(TTC).
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of TTC trigger type.
 *   @arg  CAN_TTC_TRIG_IMMED:          Immediate trigger for immediate transmission.
 *   @arg  CAN_TTC_TRIG_TIME:           Time trigger for receive triggers.
 *   @arg  CAN_TTC_TRIG_SSHOT_TRANS:    Single shot transmit trigger for exclusive time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STRT:     Transmit start trigger for merged arbitrating time windows.
 *   @arg  CAN_TTC_TRIG_TRANS_STOP:     Transmit stop trigger for merged arbitrating time windows.
 *   @arg  0xFFFF:                      Invalid value if CANx == NULL.
 */
uint16_t CAN_TTC_GetTrigType(const M4_CAN_TypeDef *CANx)
{
    uint16_t u16Ret = 0xFFFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u16Ret = CANx->TRG_CFG & CAN_TRG_CFG_TTYPE;
    }

    return u16Ret;
}

/**
 * @brief  Specifies transmit enable window for single shot transmit trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16Time                //TODO:
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTransEnWindow(M4_CAN_TypeDef *CANx, uint16_t u16Time)
{
    //TODO:
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_TTC_SST_TW(u16Time));

        u16Time <<= CAN_TRG_CFG_TEW_POS;
        MODIFY_REG16(CANx->TRG_CFG, CAN_TRG_CFG_TEW, u16Time);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set cycle time for timer-trigger communication(TTC) trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16Time                Cycle time of trigger.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TTC_SetTransTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16Time)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        CANx->TT_TRIG = u16Time;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get cycle time of timer-trigger communication(TTC) trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of cycle time.
 */
uint16_t CAN_TTC_GetTransTrigTime(const M4_CAN_TypeDef *CANx)
{
    uint16_t u16Ret = 0xFFFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u16Ret = CANx->TT_TRIG;
    }

    return u16Ret;
}

/**
 * @brief  Set cycle time for timer-trigger communication(TTC) watch-trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  u16Time                Cycle time of watch-trigger.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 * @note Call this function when CFG_STAT.RESET is 1.
 */
en_result_t CAN_TTC_SetWatchTrigTime(M4_CAN_TypeDef *CANx, uint16_t u16Time)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        CANx->TT_WTRIG = u16Time;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get cycle time of timer-trigger communication(TTC) watch-trigger.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @retval An uint16_t type value of cycle time.
 */
uint16_t CAN_TTC_GetWatchTrigTime(const M4_CAN_TypeDef *CANx)
{
    uint16_t u16Ret = 0xFFFFU;

    if (CANx != NULL)
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        u16Ret = CANx->TT_WTRIG;
    }

    return u16Ret;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * @brief  CAN bus transmits data.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param  [in]  pstcTx                 Points to a stc_can_tx_t structure type data which stores the frames to be transmitted.
 * @param  [in]  u8TBType               CAN transmit buffer type.
 *                                      This parameter can be a value of @ref CAN_Transmit_Buffer_Type
 *   @arg  CAN_PTB:                     Primary transmit buffer.
 *   @arg  CAN_STB:                     Secondary transmit buffer.
 * @param  [in]  u8STBTxCtrl            STB transmission control. If transmit via PTB, set u8STBTxCtrl to 0.
 *                                      This parameter can be a value of @ref CAN_STB_Trans_Control
 *   @arg  CAN_STB_TRANS_ALL:           Transmit all of STB slots.
 *   @arg  CAN_STB_TRANS_ONE:           Transmit one STB slot.
 * @param  [in]  u32Timeout
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:        CANx == NULL.
 */
en_result_t CAN_TransData(M4_CAN_TypeDef *CANx, const stc_can_tx_t *pstcTx,
                          uint8_t u8TBType, uint8_t u8STBTxCtrl, uint32_t u32Timeout)
{
    uint32_t i;
    uint8_t u8WordLen;
    uint32_t u32TimeCnt;
    uint32_t u32SrcDataAddr;
    uint32_t u32TBAddr;
    uint8_t au8TxEn[2U][2U] = {{CAN_TCMD_TPE, CAN_TCMD_TPE}, \
                               {CAN_TCMD_TSALL, CAN_TCMD_TSONE}};
    uint8_t au8Check[2U] = {CAN_RTIF_TPIF, CAN_RTIF_TSIF};
    en_result_t enRet = ErrorInvalidParameter;

    if ((CANx != NULL) && (pstcTx != NULL))
    {
        DDL_ASSERT(IS_CAN_UNIT(CANx));
        DDL_ASSERT(IS_CAN_TB_TYPE(u8TBType));
        DDL_ASSERT(IS_CAN_STB_TX_CTRL(u8STBTxCtrl));

        //TODO: full state check. write data, do not enable transmission, check the TB full status.
        if ((CANx->TCTRL & CAN_TB_STAT_FULL) == CAN_TB_STAT_FULL)
        {
            enRet = ErrorBufferFull;
        }
        else
        {
            u8WordLen  = (uint8_t)(pstcTx->DLC / 4U);
            u8WordLen += (pstcTx->DLC % 4U) ? 1U : 0U;

            /* Specify the transmit buffer, PTB or STB. */
            BIT_BAND(CANx->TCMD, CAN_TCMD_TBSEL_POS) = (uint32_t)u8TBType;

            u32TBAddr = (uint32_t)&CANx->TBUF;
            RW_MEM32(u32TBAddr) = pstcTx->u32ID;
            RW_MEM32(u32TBAddr + 4U) = pstcTx->u32Ctrl;

            /* //TODO: Address alignment check!!! */
            u32SrcDataAddr = (uint32_t)pstcTx->pu8Data;
            i = 0U;
            u32TBAddr += 8U;
            while (i < u8WordLen)
            {
                RW_MEM32(u32TBAddr + i * 4U) = *(uint32_t *)u32SrcDataAddr;
                u32SrcDataAddr += 4U;
                i++;
            }

            if (u8TBType == CAN_STB)
            {
                /* After writes the data in transmit buffer(TB), sets the TSNEXT bit to indicate that the current \
                   STB slot has been filled, so that the hardware will point TB to the next STB slot. */
                SET_REG8_BIT(CANx->TCTRL, CAN_TCTRL_TSNEXT);
            }

            /* Enable transmission. */
            SET_REG8_BIT(CANx->TCMD, au8TxEn[u8TBType][u8STBTxCtrl]);

            if (u32Timeout == 0U)
            {
                enRet = Ok;
            }
            else
            {
                /* Check transmission. */
                //TODO: arbitration lost check.
                u32TimeCnt = u32Timeout * (SystemCoreClock / 10u / 1000u);
                enRet = ErrorTimeout;
                while (u32TimeCnt--)
                {
                    if ((CANx->RTIF & au8Check[u8TBType]) != 0U)
                    {
                        enRet = Ok;
                        break;
                    }
                }
            }
        }
    }

    return enRet;
}

/**
 * @brief  CAN bus receives data.
 * @param  [in]  CANx                   Pointer to CAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_CAN1:                     CAN unit 1 instance register base.
 *   @arg  M4_CAN2:                     CAN unit 2 instance register base.
 * @param [out]  pstcRx                 Points to a stc_can_rx_t structure type array which is used to \
 *                                      store the received frames.
 * @param [out]  pu32RxFrameCnt         The number of frames received.
 * @retval An en_result_t enumeration type value.
 *   @arg Ok:                           No error occurred.
 *   @arg ErrorInvalidParameter:       -CANx == NULL.
 *                                     -pstcRx == NULL.
 *                                     -pu32RxFrameCnt == NULL.
 */
en_result_t CAN_ReceiveData(M4_CAN_TypeDef *CANx, stc_can_rx_t *pstcRx, uint32_t *pu32RxFrameCnt)
{
    uint32_t i;
    uint32_t u32DLC;
    uint32_t u32WordLen;
    uint32_t u32FrameCnt = 0;
    uint32_t u32DestDataAddr;
    uint32_t u32RBAddr;
    en_result_t enRet;

    if ((CANx == NULL) || (pstcRx == NULL) || (pu32RxFrameCnt == NULL))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        u32RBAddr = (uint32_t)&CANx->RBUF;
        while ((CANx->RCTRL & CAN_RCTRL_RSTAT) != CAN_RB_STAT_EMPTY)
        {
            pstcRx[u32FrameCnt].u32ID   = RW_MEM32(u32RBAddr);
            pstcRx[u32FrameCnt].u32Ctrl = RW_MEM32(u32RBAddr + 4U);

            u32DLC      = pstcRx[u32FrameCnt].DLC;
            u32WordLen  = u32DLC / 4U;
            u32WordLen += (u32DLC % 4U) ? 1U : 0U;

            u32DestDataAddr = (uint32_t)pstcRx[u32FrameCnt].pu8Data;
            i = 0U;
            u32RBAddr += 8U;
            while (i < u32WordLen)
            {
                *(uint32_t *)u32DestDataAddr = RW_MEM32(u32RBAddr + i * 4U);
                u32DestDataAddr += 4U;
                i++;
            }

            /* Set RB to point to the next RB slot. */
            SET_REG8_BIT(CANx->RCTRL, CAN_RCTRL_RREL);
            u32FrameCnt++;
        }

        *pu32RxFrameCnt = u32FrameCnt;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_CAN_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
