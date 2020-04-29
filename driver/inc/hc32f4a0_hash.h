/**
 *******************************************************************************
 * @file  hc32f4a0_hash.h
 * @brief This file contains all the functions prototypes of the HASH driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-14       Heqb         First version
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
#ifndef __HC32F4A0_HASH_H__
#define __HC32F4A0_HASH_H__

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
 * @addtogroup DDL_HASH
 * @{
 */

#if (DDL_HASH_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup HASH_Global_Types HASH Global Types
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup HASH_Global_Macros HASH Global Macros
 * @{
 */

#define TIMEOUT                      ((uint16_t)0x1000U)
#define HASH_GROUP_LEN               ((uint8_t)64U)
#define LAST_GROUP_MAX_LEN           ((uint8_t)56U)

/** @defgroup HASH_Mode HASH Mode
  * @{
  */
#define HASH_MODE_SHA_256            ((uint32_t)0x00000000U)       /*!< SHA_256 Operating mode */
#define HASH_MODE_HMAC               ((uint32_t)0x00000010U)       /*!< HMAC Operating mode */
/**
 * @}
 */

/**
 * @defgroup HASH_Key_Len HASH Key Length
 * @{
 */
#define HASH_KEY_LEN_LONG            (HASH_CR_LKEY)                /*!< Key length > 64 Bytes */
#define HASH_KEY_LEN_SHORT           ((uint32_t)0x00000000U)       /*!< Key length <= 64 Bytes */
/**
 * @}
 */

/**
 * @defgroup HASH_Interrupt_Definition HASH Interrupt Definition
 * @{
 */
#define HASH_INT_GROUP               (HASH_CR_HEIE)                 /*!< A set of data operations complete interrupt */
#define HASH_INT_ALL                 (HASH_CR_HCIE)                 /*!< All data operations complete interrupt */
#define HASH_INT_BOTH                (HASH_CR_HCIE | HASH_CR_HEIE)  /*!< Both */
/**
 * @}
 */

/**
 * @defgroup HASH_Msg_Group HASH Messages Group
 * @{
 */
#define HASH_MSG_GRP_FIRST           (HASH_CR_FST_GRP)          /*!< The first group of messages or keys */
#define HASH_MSG_GRP_END             (HASH_CR_KMSG_END)         /*!< The last group of messages or keys */
/**
 * @}
 */

/**
 * @defgroup HASH_Status HASH Status
 * @{
 */
#define HASH_FLAG_START              (HASH_CR_START)            /*!< Operation in progress */
#define HASH_FLAG_BUSY               (HASH_CR_BUSY)             /*!< HASH in operation */
#define HASH_FLAG_CYC_END            (HASH_CR_CYC_END)          /*!< key or message operation completed */
#define HASH_FLAG_HMAC_END           (HASH_CR_HMAC_END)         /*!< HMAC operation completed */
/**
 * @}
 */

/**
 * @defgroup HASH_Common_Trigger_Sel HASH common trigger source select
 * @{
 */
#define HASH_COM1_TRIG_DISABLE       ((uint32_t)0x00UL)
#define HASH_COM2_TRIG_DISABLE       ((uint32_t)0x00UL)
#define HASH_COM1_TRIG_ENABLE        ((uint32_t)(0x01UL << 31U))
#define HASH_COM2_TRIG_ENABLE        ((uint32_t)(0x01Ul << 30U))
/**
 * @}
 */

/**
 * @defgroup HASH_Common_Trigger_Reg_Sel HASH common trigger cource select
 * @{
 */
#define HASH_TRIG_REG_BLKCOM         ((uint8_t)0U)              /*!< DMA block transfer complete register */
#define HASH_TRID_REG_TRNCOM         ((uint8_t)1U)              /*!< DMA transfer complete register*/
/**
 * @}
 */

/**
 * @defgroup HASH_Trigger_Source_Sel HASH Trigger Source Select
 * @{
 */
#define HASH_TRG_SRC_DMA1_BTC0         ((uint32_t)EVT_DMA1_BTC0)              /*!< Select the DMA1 ch0 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC1         ((uint32_t)EVT_DMA1_BTC1)              /*!< Select the DMA1 ch1 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC2         ((uint32_t)EVT_DMA1_BTC2)              /*!< Select the DMA1 ch2 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC3         ((uint32_t)EVT_DMA1_BTC3)              /*!< Select the DMA1 ch3 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC4         ((uint32_t)EVT_DMA1_BTC4)              /*!< Select the DMA1 ch4 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC5         ((uint32_t)EVT_DMA1_BTC5)              /*!< Select the DMA1 ch5 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC6         ((uint32_t)EVT_DMA1_BTC6)              /*!< Select the DMA1 ch6 block transfer complete */
#define HASH_TRG_SRC_DMA1_BTC7         ((uint32_t)EVT_DMA1_BTC7)              /*!< Select the DMA1 ch7 block transfer complete */
#define HASH_TRG_SRC_DMA1_TC0          ((uint32_t)EVT_DMA1_TC0)               /*!< Select the DMA1 ch0 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC1          ((uint32_t)EVT_DMA1_TC1)               /*!< Select the DMA1 ch1 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC2          ((uint32_t)EVT_DMA1_TC2)               /*!< Select the DMA1 ch2 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC3          ((uint32_t)EVT_DMA1_TC3)               /*!< Select the DMA1 ch3 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC4          ((uint32_t)EVT_DMA1_TC4)               /*!< Select the DMA1 ch4 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC5          ((uint32_t)EVT_DMA1_TC5)               /*!< Select the DMA1 ch5 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC6          ((uint32_t)EVT_DMA1_TC6)               /*!< Select the DMA1 ch6 transfer complete*/
#define HASH_TRG_SRC_DMA1_TC7          ((uint32_t)EVT_DMA1_TC7)               /*!< Select the DMA1 ch7 transfer complete*/
#define HASH_TRG_SRC_DMA2_BTC0         ((uint32_t)EVT_DMA2_BTC0)              /*!< Select the DMA2 ch0 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC1         ((uint32_t)EVT_DMA2_BTC1)              /*!< Select the DMA2 ch1 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC2         ((uint32_t)EVT_DMA2_BTC2)              /*!< Select the DMA2 ch2 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC3         ((uint32_t)EVT_DMA2_BTC3)              /*!< Select the DMA2 ch3 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC4         ((uint32_t)EVT_DMA2_BTC4)              /*!< Select the DMA2 ch4 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC5         ((uint32_t)EVT_DMA2_BTC5)              /*!< Select the DMA2 ch5 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC6         ((uint32_t)EVT_DMA2_BTC6)              /*!< Select the DMA2 ch6 block transfer complete */
#define HASH_TRG_SRC_DMA2_BTC7         ((uint32_t)EVT_DMA2_BTC7)              /*!< Select the DMA2 ch7 block transfer complete */
#define HASH_TRG_SRC_DMA2_TC0          ((uint32_t)EVT_DMA2_TC0)               /*!< Select the DMA2 ch0 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC1          ((uint32_t)EVT_DMA2_TC1)               /*!< Select the DMA2 ch1 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC2          ((uint32_t)EVT_DMA2_TC2)               /*!< Select the DMA2 ch2 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC3          ((uint32_t)EVT_DMA2_TC3)               /*!< Select the DMA2 ch3 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC4          ((uint32_t)EVT_DMA2_TC4)               /*!< Select the DMA2 ch4 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC5          ((uint32_t)EVT_DMA2_TC5)               /*!< Select the DMA2 ch5 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC6          ((uint32_t)EVT_DMA2_TC6)               /*!< Select the DMA2 ch6 transfer complete*/
#define HASH_TRG_SRC_DMA2_TC7          ((uint32_t)EVT_DMA2_TC7)               /*!< Select the DMA2 ch7 transfer complete*/
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
 * @addtogroup HASH_Global_Functions
 * @{
 */
en_result_t HASH_Calculate(const uint8_t *pu8SrcData,
                           uint32_t u32SrcDataSize,
                           uint8_t u8MsgDigest[]);
en_result_t HMAC_Calculate(const uint8_t *pu8SrcData,
                           uint32_t u32SrcDataSize,
                           const uint8_t pu8Key[],
                           uint32_t u32KeyLength,
                           uint8_t u8MsgDigest[]);
en_result_t HASH_Start(void);
en_result_t HASH_IntCmd(uint32_t u32HashInt, en_functional_state_t enNewState);
en_result_t HASH_SetMode(uint32_t u32HashMode);
en_result_t HASH_SetKeyLength(uint32_t u32KeyLen);
en_result_t HASH_MsgGrpConfig(uint32_t u32MsgGroup);
en_result_t HASH_ClearStatus(uint32_t u32ClearFlag);
en_result_t HASH_SetTriggerSrc(uint32_t u32TrgScr);
en_result_t HASH_ComTrigCmd(uint8_t u8TrigReg, uint32_t u32ComTrigEn);
en_flag_status_t HASH_GetStatus(uint32_t u32HashFlag);
void HASH_GetResult(uint32_t u32MsgDigestAddr);
/**
 * @}
 */

#endif /* DDL_HASH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_HASH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/