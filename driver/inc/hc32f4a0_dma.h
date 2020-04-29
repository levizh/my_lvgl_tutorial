/**
 *******************************************************************************
 * @file  hc32f4a0_dma.h
 * @brief This file contains all the functions prototypes of the DMA driver
 *        library.
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
#ifndef __HC32F4A0_DMA_H__
#define __HC32F4A0_DMA_H__

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
 * @addtogroup DDL_DMA
 * @{
 */

#if (DDL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DMA_Global_Types DMA Global Types
 * @{
 */

/**
 * @brief  DMA basical configuration
 */
typedef struct stc_dma_init
{
    uint32_t u32IntEn;          /*!< Specifies the DMA interrupt function. 
                                    This parameter can be a value of @ref DMA_Int_Config                */

    uint32_t u32SrcAddr;        /*!< Specifies the DMA source address.                                  */

    uint32_t u32DestAddr;       /*!< Specifies the DMA destination address.                             */

    uint32_t u32DataWidth;      /*!< Specifies the DMA transfer data width.
                                    This parameter can be a value of @ref DMA_DataWidth                 */

    uint32_t u32BlockSize;      /*!< Specifies the DMA block size.                                      */

    uint32_t u32TransCnt;       /*!< Specifies the DMA transfer count.                                  */

    uint32_t u32SrcInc;         /*!< Specifies the source address increment mode.
                                    This parameter can be a value of @ref DMA_SrcAddr_Incremented_Mode  */

    uint32_t u32DestInc;        /*!< Specifies the destination address increment mode.
                                    This parameter can be a value of @ref DMA_DesAddr_Incremented_Mode  */

} stc_dma_init_t;

/**
 * @brief  DMA repeat mode configuration
 */
typedef struct stc_dma_rpt_init
{
    uint32_t u32SrcRptEn;       /*!< Specifies the DMA source repeat function. 
                                    This parameter can be a value of @ref DMA_Repeat_Config */

    uint32_t u32SrcRptSize;     /*!< Specifies the DMA source repeat size. */

    uint32_t u32DestRptEn;      /*!< Specifies the DMA destination repeat function. 
                                    This parameter can be a value of @ref DMA_Repeat_Config */
    
    uint32_t u32DestRptSize;    /*!< Specifies the DMA destination repeat size. */

} stc_dma_rpt_init_t;

/**
 * @brief  DMA non-sequence mode configuration
 */
typedef struct stc_dma_nonseq_init
{
    uint32_t u32SrcNonSeqEn;    /*!< Specifies the DMA source non-sequence function. 
                                    This parameter can be a value of @ref DMA_NonSeq_Config */
    
    uint32_t u32SrcNonSeqCnt;   /*!< Specifies the DMA source non-sequence function count. */

    uint32_t u32SrcNonSeqOfs;   /*!< Specifies the DMA source non-sequence function offset. */

    uint32_t u32DestNonSeqEn;   /*!< Specifies the DMA destination non-sequence function.
                                    This parameter can be a value of @ref DMA_NonSeq_Config */

    uint32_t u32DestNonSeqCnt;  /*!< Specifies the DMA destination non-sequence function count. */
    
    uint32_t u32DestNonSeqOfs;  /*!< Specifies the DMA destination non-sequence function offset. */

} stc_dma_nonseq_init_t;

/**
 * @brief  DMA Link List Pointer (LLP) mode configuration
 */
typedef struct stc_dma_llp_init
{
    uint32_t u32LlpEn;          /*!< Specifies the DMA LLP function. 
                                    This parameter can be a value of @ref DMA_Llp_En */

    uint32_t u32LlpRun;         /*!< Specifies the DMA LLP auto or wait REQ. 
                                    This parameter can be a value of @ref DMA_Llp_Mode */

    uint32_t u32Llp;            /*!< Specifies the DMA list pointer address for LLP function. */

} stc_dma_llp_init_t;

/**
 * @brief  DMA re-config function configuration
 */
typedef struct stc_dma_reconfig_init
{
    uint32_t u32CntMode;        /*!< Specifies the DMA reconfig function count mode.
                                    This parameter can be a value of @ref DMA_ReConfig_Cnt_Sel */

    uint32_t u32DestAddrMode;   /*!< Specifies the DMA reconfig function destination address mode.
                                    This parameter can be a value of @ref DMA_ReConfig_DestAddr_Sel */

    uint32_t u32SrcAddrMode;    /*!< Specifies the DMA reconfig function source address mode.
                                    This parameter can be a value of @ref DMA_ReConfig_SrcAddr_Sel */

} stc_dma_reconfig_init_t;

/**
 * @brief  Dma LLP(linked list pointer) descriptor structure definition
 */
typedef struct
{
    uint32_t SARx;          /*!< LLP source address */
    uint32_t DARx;          /*!< LLP destination address */
    uint32_t DTCTLx;        /*!< LLP transfer count and block size */
    uint32_t RPTx;          /*!< LLP source & destination repeat size */
    uint32_t SNSEQCTLx;     /*!< LLP source non-seq count and offset */
    uint32_t DNSEQCTLx;     /*!< LLP destination non-seq count and offset */
    uint32_t LLPx;          /*!< LLP next list pointer */
    uint32_t CHCTLx;        /*!< LLP channel control */
} stc_dma_llp_descriptor_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DMA_Global_Macros DMA Global Macros
 * @{
 */

/**
 * @defgroup DMA_Channel_selection DMA Channel Position selection
 * @{
 */
#define DMA_CH0                     ((uint8_t)0x00U)        /*!< DMA Channel 0 */
#define DMA_CH1                     ((uint8_t)0x01U)        /*!< DMA Channel 1 */
#define DMA_CH2                     ((uint8_t)0x02U)        /*!< DMA Channel 2 */
#define DMA_CH3                     ((uint8_t)0x03U)        /*!< DMA Channel 3 */
#define DMA_CH4                     ((uint8_t)0x04U)        /*!< DMA Channel 4 */
#define DMA_CH5                     ((uint8_t)0x05U)        /*!< DMA Channel 5 */
#define DMA_CH6                     ((uint8_t)0x06U)        /*!< DMA Channel 6 */
#define DMA_CH7                     ((uint8_t)0x07U)        /*!< DMA Channel 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Mx_Channel_selection DMA Multiplex Channel selection
 * @{
 */
#define DMA_MX_CH0                  ((uint32_t)0x01UL)      /*!< DMA Channel 0 position */
#define DMA_MX_CH1                  ((uint32_t)0x02UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH2                  ((uint32_t)0x04UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH3                  ((uint32_t)0x08UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH4                  ((uint32_t)0x10UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH5                  ((uint32_t)0x20UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH6                  ((uint32_t)0x40UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH7                  ((uint32_t)0x80UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH_ALL               ((uint32_t)0xFFUL)      /*!< DMA Channel 1 position */
/**
 * @}
 */

/**
 * @defgroup DMA_ReqErrIrq_Sel DMA request error interrupt selection
 * @{
 */
#define DMA_REQ_ERR0                (DMA_INTSTAT0_REQERR_0) /*!< DMA request error interrupt 0 */
#define DMA_REQ_ERR1                (DMA_INTSTAT0_REQERR_1) /*!< DMA request error interrupt 1 */
#define DMA_REQ_ERR2                (DMA_INTSTAT0_REQERR_2) /*!< DMA request error interrupt 2 */
#define DMA_REQ_ERR3                (DMA_INTSTAT0_REQERR_3) /*!< DMA request error interrupt 3 */
#define DMA_REQ_ERR4                (DMA_INTSTAT0_REQERR_4) /*!< DMA request error interrupt 4 */
#define DMA_REQ_ERR5                (DMA_INTSTAT0_REQERR_5) /*!< DMA request error interrupt 5 */
#define DMA_REQ_ERR6                (DMA_INTSTAT0_REQERR_6) /*!< DMA request error interrupt 6 */
#define DMA_REQ_ERR7                (DMA_INTSTAT0_REQERR_7) /*!< DMA request error interrupt 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_TransErrIrq_Sel DMA transfer error interrupt selection
 * @{
 */
#define DMA_TRANS_ERR0              (DMA_INTSTAT0_TRNERR_0) /*!< DMA transfer error interrupt 0 */
#define DMA_TRANS_ERR1              (DMA_INTSTAT0_TRNERR_1) /*!< DMA transfer error interrupt 1 */
#define DMA_TRANS_ERR2              (DMA_INTSTAT0_TRNERR_2) /*!< DMA transfer error interrupt 2 */
#define DMA_TRANS_ERR3              (DMA_INTSTAT0_TRNERR_3) /*!< DMA transfer error interrupt 3 */
#define DMA_TRANS_ERR4              (DMA_INTSTAT0_TRNERR_4) /*!< DMA transfer error interrupt 4 */
#define DMA_TRANS_ERR5              (DMA_INTSTAT0_TRNERR_5) /*!< DMA transfer error interrupt 5 */
#define DMA_TRANS_ERR6              (DMA_INTSTAT0_TRNERR_6) /*!< DMA transfer error interrupt 6 */
#define DMA_TRANS_ERR7              (DMA_INTSTAT0_TRNERR_7) /*!< DMA transfer error interrupt 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_BtcIrq_Sel DMA block transfer completed interrupt selection
 * @{
 */
#define DMA_BTC_INT0                (DMA_INTSTAT1_BTC_0)    /*!< DMA block transfer completed interrupt 0 */
#define DMA_BTC_INT1                (DMA_INTSTAT1_BTC_1)    /*!< DMA block transfer completed interrupt 1 */
#define DMA_BTC_INT2                (DMA_INTSTAT1_BTC_2)    /*!< DMA block transfer completed interrupt 2 */
#define DMA_BTC_INT3                (DMA_INTSTAT1_BTC_3)    /*!< DMA block transfer completed interrupt 3 */
#define DMA_BTC_INT4                (DMA_INTSTAT1_BTC_4)    /*!< DMA block transfer completed interrupt 4 */
#define DMA_BTC_INT5                (DMA_INTSTAT1_BTC_5)    /*!< DMA block transfer completed interrupt 5 */
#define DMA_BTC_INT6                (DMA_INTSTAT1_BTC_6)    /*!< DMA block transfer completed interrupt 6 */
#define DMA_BTC_INT7                (DMA_INTSTAT1_BTC_7)    /*!< DMA block transfer completed interrupt 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_TcIrq_Sel DMA transfer completed interrupt selection
 * @{
 */
#define DMA_TC_INT0                 (DMA_INTSTAT1_TC_0)     /*!< DMA transfer completed interrupt 0 */
#define DMA_TC_INT1                 (DMA_INTSTAT1_TC_1)     /*!< DMA transfer completed interrupt 1 */
#define DMA_TC_INT2                 (DMA_INTSTAT1_TC_2)     /*!< DMA transfer completed interrupt 2 */
#define DMA_TC_INT3                 (DMA_INTSTAT1_TC_3)     /*!< DMA transfer completed interrupt 3 */
#define DMA_TC_INT4                 (DMA_INTSTAT1_TC_4)     /*!< DMA transfer completed interrupt 4 */
#define DMA_TC_INT5                 (DMA_INTSTAT1_TC_5)     /*!< DMA transfer completed interrupt 5 */
#define DMA_TC_INT6                 (DMA_INTSTAT1_TC_6)     /*!< DMA transfer completed interrupt 6 */
#define DMA_TC_INT7                 (DMA_INTSTAT1_TC_7)     /*!< DMA transfer completed interrupt 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_IntMsk_Sel DMA interrupt mask selection
 * @{
 */
#define DMA_ERR_INT_MASK            ((uint32_t)0x00FF00FFUL)    /*!< DMA error interrupt mask */
#define DMA_TRANS_INT_MASK          ((uint32_t)0x00FF00FFUL)    /*!< DMA transfer interrupt mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Req_Status_Sel DMA request status
 * @{
 */
#define DMA_REQ_CH0                 (DMA_REQSTAT_CHREQ_0)   /*!< DMA request from Channel 0 */
#define DMA_REQ_CH1                 (DMA_REQSTAT_CHREQ_1)   /*!< DMA request from Channel 1 */
#define DMA_REQ_CH2                 (DMA_REQSTAT_CHREQ_2)   /*!< DMA request from Channel 2 */
#define DMA_REQ_CH3                 (DMA_REQSTAT_CHREQ_3)   /*!< DMA request from Channel 3 */
#define DMA_REQ_CH4                 (DMA_REQSTAT_CHREQ_4)   /*!< DMA request from Channel 4 */
#define DMA_REQ_CH5                 (DMA_REQSTAT_CHREQ_5)   /*!< DMA request from Channel 5 */
#define DMA_REQ_CH6                 (DMA_REQSTAT_CHREQ_6)   /*!< DMA request from Channel 6 */
#define DMA_REQ_CH7                 (DMA_REQSTAT_CHREQ_7)   /*!< DMA request from Channel 7 */
#define DMA_REQ_RECONFIG            (DMA_REQSTAT_RCFGREQ)   /*!< DMA request from reconfig */
#define DMA_REQ_STAT_MASK           ((uint32_t)0x80FFUL)    /*!< DMA request mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Trans_Status_Sel DMA transfer status
 * @{
 */
#define DMA_TRANS_CH0               (DMA_CHSTAT_CHACT_0)    /*!< DMA transfer status of Channel 0 */
#define DMA_TRANS_CH1               (DMA_CHSTAT_CHACT_1)    /*!< DMA transfer status of Channel 1 */
#define DMA_TRANS_CH2               (DMA_CHSTAT_CHACT_2)    /*!< DMA transfer status of Channel 2 */
#define DMA_TRANS_CH3               (DMA_CHSTAT_CHACT_3)    /*!< DMA transfer status of Channel 3 */
#define DMA_TRANS_CH4               (DMA_CHSTAT_CHACT_4)    /*!< DMA transfer status of Channel 4 */
#define DMA_TRANS_CH5               (DMA_CHSTAT_CHACT_5)    /*!< DMA transfer status of Channel 5 */
#define DMA_TRANS_CH6               (DMA_CHSTAT_CHACT_6)    /*!< DMA transfer status of Channel 6 */
#define DMA_TRANS_CH7               (DMA_CHSTAT_CHACT_7)    /*!< DMA transfer status of Channel 7 */
#define DMA_TRANS_RECONFIG          (DMA_CHSTAT_RCFGACT)    /*!< DMA reconfig status */
#define DMA_TRANS_DMA               (DMA_CHSTAT_DMAACT)     /*!< DMA transfer status of the DMA */
#define DMA_TRANS_STAT_MASK         ((uint32_t)0xFF03UL)    /*!< DMA request mask */
/**
 * @}
 */

/**
 * @defgroup DMA_DataWidth_Sel DMA transfer data width
 * @{
 */
#define DMA_DATAWIDTH_8BIT          ((uint32_t)0x00UL)      /*!< DMA transfer data width 8bit  */
#define DMA_DATAWIDTH_16BIT         (DMA_CHCTL_HSIZE_0)     /*!< DMA transfer data width 16bit */
#define DMA_DATAWIDTH_32BIT         (DMA_CHCTL_HSIZE_1)     /*!< DMA transfer data width 32bit */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_En DMA LLP(linked list pinter) enable or disable
 * @{
 */
#define DMA_LLP_ENABLE              (DMA_CHCTL_LLPEN)       /*!< DMA LLP(linked list pinter) enable     */
#define DMA_LLP_DISABLE             ((uint32_t)0x00UL)      /*!< DMA LLP(linked list pinter) disable    */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_Mode DMA linked list pinter mode while transferring complete
 * @{
 */
#define DMA_LLP_RUN                 (DMA_CHCTL_LLPRUN)      /*!< DMA Llp run right now while transfering complete     */
#define DMA_LLP_WAIT                ((uint32_t)0x00UL)      /*!< DMA Llp wait next request while transfering complete */
/**
 * @}
 */

/**
 * @defgroup DMA_SrcAddr_Incremented_Mode DMA source address increment mode
 * @{
 */
#define DMA_SRC_ADDR_FIX            ((uint32_t)0x00UL)      /*!< DMA source address fix             */
#define DMA_SRC_ADDR_INC            (DMA_CHCTL_SINC_0)      /*!< DMA source address increment       */
#define DMA_SRC_ADDR_DEC            (DMA_CHCTL_SINC_1)      /*!< DMA source address decrement       */
/**
 * @}
 */

/**
 * @defgroup DMA_DesAddr_Incremented_Mode DMA destination address increment mode
 * @{
 */
#define DMA_DEST_ADDR_FIX           ((uint32_t)0x00UL)      /*!< DMA destination address fix        */
#define DMA_DEST_ADDR_INC           (DMA_CHCTL_DINC_0)      /*!< DMA destination address increment  */
#define DMA_DEST_ADDR_DEC           (DMA_CHCTL_DINC_1)      /*!< DMA destination address decrement  */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Config DMA interrupt function config
 * @{
 */
#define DMA_INT_ENABLE              (DMA_CHCTL_IE)          /*!< DMA interrupt enable */
#define DMA_INT_DISABLE             ((uint32_t)0x00UL)      /*!< DMA interrupt disable */
/**
 * @}
 */

/**
 * @defgroup DMA_Repeat_Config DMA repeat mode function config
 * @{
 */
#define DMA_SRC_RPT_ENABLE          (DMA_CHCTL_SRTPEN)      /*!< DMA source repeat enable */
#define DMA_SRC_RPT_DISABLE         ((uint32_t)0x00UL)      /*!< DMA source repeat disable */
#define DMA_DEST_RPT_ENABLE         (DMA_CHCTL_DRPTEN)      /*!< DMA destination repeat enable */
#define DMA_DEST_RPT_DISABLE        ((uint32_t)0x00UL)      /*!< DMA destination repeat disable */
/**
 * @}
 */

/**
 * @defgroup DMA_NonSeq_Config DMA non-sequence mode function config
 * @{
 */
#define DMA_SRC_NS_ENABLE           (DMA_CHCTL_SNSEQEN)     /*!< DMA source non-sequence enable */
#define DMA_SRC_NS_DISABLE          ((uint32_t)0x00UL)      /*!< DMA source non-sequence disable */
#define DMA_DEST_NS_ENABLE          (DMA_CHCTL_DNSEQEN)     /*!< DMA destination non-sequence enable */
#define DMA_DEST_NS_DISABLE         ((uint32_t)0x00UL)      /*!< DMA destination non-sequence disable */
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_Cnt_Sel DMA reconfig count mode selection
 * @{
 */
#define DMA_RC_CNT_FIX              ((uint32_t)0x00UL)      
#define DMA_RC_CNT_SRC              ((uint32_t)DMA_RCFGCTL_CNTMD_0)      
#define DMA_RC_CNT_DEST             ((uint32_t)DMA_RCFGCTL_CNTMD_1)      
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_DestAddr_Sel DMA reconfig destination address mode selection
 * @{
 */
#define DMA_RC_DA_FIX               ((uint32_t)0x00UL)      
#define DMA_RC_DA_NS                ((uint32_t)DMA_RCFGCTL_DARMD_0)      
#define DMA_RC_DA_RPT               ((uint32_t)DMA_RCFGCTL_DARMD_1)      
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_SrcAddr_Sel DMA reconfig source address mode selection
 * @{
 */
#define DMA_RC_SA_FIX               ((uint32_t)0x00UL)      
#define DMA_RC_SA_NS                ((uint32_t)DMA_RCFGCTL_SARMD_0)      
#define DMA_RC_SA_RPT               ((uint32_t)DMA_RCFGCTL_SARMD_1)      
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
 * @addtogroup DMA_Global_Functions
 * @{
 */
void DMA_Cmd(M4_DMA_TypeDef *stcDmaReg, en_functional_state_t enNewState);

void DMA_ErrIntCmd(M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetErrIntStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt);
void DMA_ClearErrIntStatus(M4_DMA_TypeDef *stcDmaReg, uint32_t u32ErrInt);

void DMA_TransIntCmd(M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetTransIntStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt);
void DMA_ClearTransIntStatus(M4_DMA_TypeDef *stcDmaReg, uint32_t u32TransInt);

void DMA_MxChannelCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8MxCh, en_functional_state_t enNewState);
void DMA_ChannelCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState);

void DMA_SetReConfigTrigSrc(en_event_src_t enSrc);
void DMA_SetTrigSrc(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_event_src_t enSrc);

en_flag_status_t DMA_GetReqStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32Status);
en_flag_status_t DMA_GetTransStatus(const M4_DMA_TypeDef *stcDmaReg, uint32_t u32Status);

void DMA_SetSrcAddr(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Addr);
void DMA_SetDestAddr(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Addr);
void DMA_SetTransCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Cnt);
void DMA_SetBlockSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size);

void DMA_SetSrcRptSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size);
void DMA_SetDestRptSize(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint16_t u16Size);
void DMA_SetNonSeqSrcCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Cnt);
void DMA_SetNonSeqDestCnt(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Cnt);
void DMA_SetNonSeqSrcOffset(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Ofs);
void DMA_SetNonSeqDestOffset(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Ofs);

void DMA_SetLLP(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, uint32_t u32Llp);

en_result_t DMA_Init(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_rpt_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_llp_init_t *pstcDmaLlpInit);
en_result_t DMA_ReConfigInit(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, const stc_dma_reconfig_init_t *pstcDmaRCInit);

en_result_t DMA_StructInit(stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatStructInit(stc_dma_rpt_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit);
en_result_t DMA_ReConfigStructInit(stc_dma_reconfig_init_t *pstcDmaRCInit);


void DMA_LlpCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState);
void DMA_ReConfigCmd(M4_DMA_TypeDef *stcDmaReg, en_functional_state_t enNewState);
void DMA_ReConfigLlpCmd(M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch, en_functional_state_t enNewState);

uint32_t DMA_GetSrcAddr(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetDestAddr(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetTransCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetBlockSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetSrcRptSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetDestRptSize(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestCnt(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcOffset(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestOffset(const M4_DMA_TypeDef *stcDmaReg, uint8_t u8Ch);
/**
 * @}
 */

#endif /* DDL_DMA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DMA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
