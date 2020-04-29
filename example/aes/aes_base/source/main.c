/**
 *******************************************************************************
 * @file  aes/aes_base/source/main.c
 * @brief Main program of AES for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-02       Heqb         First version
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup AES base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void AesFillData(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
const static uint8_t u8AesKey[24U] =
{
    0x12, 0x34, 0x56, 0x78, 0x9A, 0xCD, 0xEC, 0xED,
    0xEE, 0xEF, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
    0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE
};
/* Word alignment. */
static uint8_t u8Plaintext[64U] = {0U};
static uint8_t u8Ciphertext[64U];
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of example project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t length;
    /* Enable AES peripheral clock. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_AES, Enable);

    /* Config UART for printing. Baud rate 115200. */
    DDL_PrintfInit();

    /* AES filling data */
    AesFillData();

    while(1U)
    {
        /* AES encryption. */
        AES_Encrypt(u8Plaintext, sizeof(u8Plaintext), u8AesKey, (uint8_t)sizeof(u8AesKey), u8Ciphertext);
        printf("\nAES encryption.");
        printf("\nPlaintext:\n");
        for (length = 0U; length < sizeof(u8Plaintext); length++)
        {
            printf("%.2x ", u8Plaintext[length]);
        }
        printf("\nCiphertext:\n");
        for (length = 0U; length < sizeof(u8Ciphertext); length++)
        {
            printf("%.2x ", u8Ciphertext[length]);
        }

        /* AES decryption */
        AES_Decrypt(u8Ciphertext, sizeof(u8Ciphertext), u8AesKey, (uint8_t)sizeof(u8AesKey), u8Plaintext);
        printf("\nAES decryption.");
        printf("\nCiphertext:\n");
        for (length = 0U; length < sizeof(u8Ciphertext); length++)
        {
            printf("%.2x ", u8Ciphertext[length]);
        }
        printf("\nPlaintext:\n");
        for (length = 0U; length < sizeof(u8Plaintext); length++)
        {
            printf("%.2x ", u8Plaintext[length]);
        }

        /* Main loop cycle 500ms. */
        DDL_Delay1ms(500U);
    };
}

/**
 * @brief  Filling data.
 * @param  None
 * @retval None
 */
static void AesFillData(void)
{
    uint32_t i;

    for (i = 0U; i < sizeof(u8Plaintext); i++)
    {
        u8Plaintext[i] = (uint8_t)(i + 1U);
    }
}
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
