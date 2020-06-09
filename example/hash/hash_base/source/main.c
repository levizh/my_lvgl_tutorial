/**
 *******************************************************************************
 * @file  hash/hash_base/source/main.c
 * @brief Main program HASH for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-10       Heqb          First version
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
 * @addtogroup HASH_Base
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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8HashMsgDigest[32U];
static uint8_t u8ExpectDigest[32U] = \
{0x16,0x08,0x06,0xa6,0x18,0x41,0x75,0x8a,0xa4,0x42,0xfa,0xe7,0xa2,0x7b,\
 0x39,0xd0,0x04,0x59,0x65,0x1c,0x74,0x6b,0x9f,0x7a,0xbd,0x2b,0x2e,0xa1,\
 0xc7,0x56,0x77,0x4f};

static char *c8SrcData = \
"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789\
!@#$%^&*()000011112222333344445555666677778888999910101010AAAABBBBCCCCDD\
abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\
123456789ABCDEFGHHGFEDCBAABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcddeffghh\
abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\
01234567890123456789--HDSC-HC32F4A0";

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of hash_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Enable HASH. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_HASH, Enable);
    /* Config UART for printing. Baud rate 115200. */
    DDL_PrintfInit();
    /* Disable HASH interrupt */
    HASH_IntCmd(HASH_INT_BOTH, Disable);
    /* Use HASH. */
    HASH_Calculate((uint8_t *)c8SrcData, strlen((char *)c8SrcData),u8HashMsgDigest);
    if ((uint8_t)memcmp(u8HashMsgDigest, u8ExpectDigest, sizeof(u8HashMsgDigest)) == 0U)
    {
        printf("message digest:\n");
        for (uint8_t i = 0U; i < sizeof(u8HashMsgDigest); i++)
        {
            printf("%.2x ", u8HashMsgDigest[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Computation Errors\n");
    }
    while (1)
    {

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
