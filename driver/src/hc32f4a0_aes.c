/**
 *******************************************************************************
 * @file  hc32f4a0_aes.c
 * @brief This file provides firmware functions to manage the Advanced Encryption
 *        Standard(AES).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-12       Heqb          First version
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
#include "hc32f4a0_aes.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_AES AES
 * @brief AES Driver Library
 * @{
 */

#if (DDL_AES_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup AES_Local_Macros AES Local Macros
 * @{
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
static void AES_WriteData(uint32_t u32Addr);
static void AES_ReadData(uint32_t u32Addr);
static void AES_WriteKey(const uint8_t *pu8Key, uint8_t u8KeyLength);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup AES_Global_Functions AES Global Functions
 * @{
 */

/**
 * @brief  AES encryption.
 * @param  [in] pu8Plaintext       Pointer to ciphertext(the source data which will be encrypted).
 * @param  [in] u32PlaintextSize   Length of plaintext in bytes.
 * @param  [in] pu8Key             Pointer to the AES key.
 * @param  [in] u8KeyLength        Length of key in bytes.
 * @param  [in] pu8Ciphertext      The destination address to store the result of the encryption.
 * @retval An en_result_t enumeration value:
 *         Ok: program successfully.
 *         ErrorInvalidParameter: Invalid parameter
 *         ErrorTimeout: program error timeout
 */
en_result_t AES_Encrypt(const uint8_t pu8Plaintext[],
                        uint32_t u32PlaintextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        const uint8_t pu8Ciphertext[])
{
    en_result_t   enRet = ErrorInvalidParameter;
    uint32_t u32TimeCount = 0U;
    uint32_t u32Index = 0U;
    uint32_t Temp;
    if((pu8Plaintext != NULL) && (u32PlaintextSize != 0U)   \
          && (pu8Key != NULL) && (u8KeyLength != 0U)        \
          && (pu8Ciphertext != NULL))
    {
        enRet = Ok;
        while(u32PlaintextSize)
        {
            /* Wait for AES to stop */
            while(bM4_AES->CR_b.START == 1U)
            {
                if(u32TimeCount++ >= TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
            }
            Temp = (uint32_t)&pu8Plaintext[u32Index];
            AES_WriteData(Temp);
            AES_WriteKey(pu8Key, u8KeyLength);
            switch (u8KeyLength)
            {
            case 16U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_128);
                break;

            case 24U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_192);
                break;

            case 32U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_256);
                break;

            default:
                break;
            }
            /* Set AES encrypt. */
            bM4_AES->CR_b.MODE = 0U;
            /* Start AES calculating. */
            bM4_AES->CR_b.START = 1U;
            /* Wait for AES to stop */
            while(bM4_AES->CR_b.START == 1U)
            {
                if(u32TimeCount++ > TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
            }
            Temp = (uint32_t)&pu8Ciphertext[u32Index];
            AES_ReadData(Temp);
            u32PlaintextSize -= AES_BLOCK_LEN;
            u32Index += AES_BLOCK_LEN;
        }
    }

    return enRet;
}

/**
 * @brief  AES decryption.
 * @param  [in] pu8Ciphertext       Pointer to ciphertext(the source data which will be decrypted).
 * @param  [in] u32CiphertextSize   Length of ciphertext in bytes.
 * @param  [in] pu8Key              Pointer to the AES key.
 * @param  [in] u8KeyLength         Length of key in bytes.
 * @param  [in] pu8Plaintext        The destination address to store the result of the decryption.
 * @retval An en_result_t enumeration value:
 *         Ok: program successfully.
 *         ErrorInvalidParameter: Invalid parameter
 *         ErrorTimeout: program error timeout
 */
en_result_t AES_Decrypt(const uint8_t pu8Ciphertext[],
                        uint32_t u32CiphertextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        const uint8_t pu8Plaintext[])
{
    en_result_t   enRet = Ok;
    uint32_t u32TimeCount = 0U;
    uint32_t u32Index = 0U;
    uint32_t u32Temp;
    if((pu8Plaintext != NULL) && (u32CiphertextSize != 0U)   \
          && (pu8Key != NULL) && (u8KeyLength != 0U)         \
          && (pu8Ciphertext != NULL))
    {
        enRet = Ok;
        while(u32CiphertextSize)
        {
            /* Wait for AES to stop */
            while(bM4_AES->CR_b.START == 1U)
            {
                if(u32TimeCount++ > TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
            }
            u32Temp = (uint32_t)&pu8Ciphertext[u32Index];
            AES_WriteData(u32Temp);
            AES_WriteKey(pu8Key, u8KeyLength);
            switch (u8KeyLength)
            {
            case 16U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_128);
                break;

            case 24U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_192);
                break;

            case 32U:
                MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_256);
                break;

            default:
                break;
            }
            /* Set AES decrypt. */
            bM4_AES->CR_b.MODE  = 1U;
            /* Start AES calculating. */
            bM4_AES->CR_b.START = 1U;
            /* Wait for AES to stop */
            while(bM4_AES->CR_b.START == 1U)
            {
                if(u32TimeCount++ > TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
            }
            u32Temp = pu8Plaintext[u32Index];
            AES_ReadData(u32Temp);
            u32CiphertextSize -= AES_BLOCK_LEN;
            u32Index += AES_BLOCK_LEN;
        }
    }
    return enRet;
}

/**
 * @brief  Write the input buffer in data register.
 * @param  [in] u32Addr    Pointer to source data buffer.
 *
 * @retval None
 */
static void AES_WriteData(uint32_t u32Addr)
{
    uint8_t  cnt;
    uint32_t u32DrAddr  = (uint32_t)&(M4_AES->DR0);

    for(cnt = 0U; cnt < 4U; cnt++)
    {
        *(__IO uint32_t *)u32DrAddr = *(uint32_t*)u32Addr;
        u32Addr += 4U;
        u32DrAddr  += 4U;
    }
}

/**
 * @brief  Read the from data register.
 * @param  [in] u32Addr    Pointer to the destination buffer.
 *
 * @retval None
 */
static void AES_ReadData(uint32_t u32Addr)
{
    uint8_t  cnt;
    uint32_t u32DrAddr   = (uint32_t)&(M4_AES->DR0);

    for(cnt = 0U; cnt < 4U; cnt++)
    {
        *(uint32_t*)u32Addr = *(__IO uint32_t *)u32DrAddr;
        u32DrAddr += 4U;
        u32Addr   += 4U;
    }
}

/**
 * @brief  Write the input buffer in key register.
 * @param  [in] pu8Key        Pointer to the kry buffer.
 * @param  [in] u8KeyLength    Length of key in bytes.
 * @retval None
 */
static void AES_WriteKey(const uint8_t *pu8Key, uint8_t u8KeyLength)
{
    uint8_t cnt;
    uint8_t length = 0U;
    uint32_t u32SrcKeyAddr = (uint32_t)pu8Key;
    uint32_t u32KeyAddr    = (uint32_t)&(M4_AES->KR0);
    switch (u8KeyLength)
    {
        case 16U:
            length = 4U;
            break;
        case 24U:
            length = 6U;
            break;
        case 32U:
            length = 8U;
            break;
        default:
            break;
    }
    for(cnt = 0U; cnt < length; cnt++)
    {
        *(__IO uint32_t *)u32KeyAddr = *(uint32_t*)u32SrcKeyAddr;
        u32SrcKeyAddr += 4U;
        u32KeyAddr    += 4U;
    }
}

#endif /* DDL_AES_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

