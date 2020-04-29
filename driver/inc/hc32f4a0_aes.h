/**
 *******************************************************************************
 * @file  hc32f4a0_aes.h
 * @brief This file contains all the functions prototypes of the AES driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-12       Heqb         First version
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
#ifndef __HC32F4A0_AES_H__
#define __HC32F4A0_AES_H__

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
 * @addtogroup DDL_AES
 * @{
 */

#if (DDL_AES_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup AES_Global_Types AES Global Types
 * @{
 */

/**
 * @brief AES configuration structure
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup AES_Global_Macros AES Global Macros
 * @{
 */
/* Delay count for timeout */
#define TIMEOUT                       (0x1000UL)

/* AES key length in bytes is 16. */
#define AES_BLOCK_LEN                 ((uint8_t)16U)
/**
 * @defgroup AES_STATUS AES Start or Stop
 * @{
 */
#define AES_START                     (AES_CR_START)
#define AES_STOP                      ((uint32_t)0x00000000U)
/**
 * @}
 */

/**
 * @defgroup AES_KEY_SIZE AES Key Size
 * @{
 */
#define AES_KEY_SIZE_128              ((uint32_t)0U << AES_CR_KEYSIZE_POS)
#define AES_KEY_SIZE_192              ((uint32_t)1U << AES_CR_KEYSIZE_POS)
#define AES_KEY_SIZE_256              ((uint32_t)2U << AES_CR_KEYSIZE_POS)
#define AES_KEY_SIZE_128_1            ((uint32_t)3U << AES_CR_KEYSIZE_POS)
/**
 * @}
 */


/** @defgroup 
  * @{
  */
en_result_t AES_Encrypt(const uint8_t pu8Plaintext[],
                        uint32_t u32PlaintextSize,
                        const uint8_t *pu8Key,
                        uint8_t  u8KeyLength,
                        const uint8_t pu8Ciphertext[]);

en_result_t AES_Decrypt(const uint8_t pu8Ciphertext[],
                        uint32_t u32CiphertextSize,
                        const uint8_t *pu8Key,
                        uint8_t  u8KeyLength,
                        const uint8_t pu8Plaintext[]);
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
 * @addtogroup AES_Global_Functions
 * @{
 */

/**
 * @}
 */

#endif /* DDL_AES_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_AES_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
