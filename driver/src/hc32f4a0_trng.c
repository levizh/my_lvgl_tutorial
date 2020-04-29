/**
 *******************************************************************************
 * @file  hc32f4a0_trng.c
 * @brief This file provides firmware functions to manage the True Random 
 *        Number Generator(TRNG).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-21       Heqb          First version
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
#include "hc32f4a0_trng.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TRNG TRNG
 * @brief TRNG Driver Library
 * @{
 */

#if (DDL_TRNG_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TRNG_Local_Macros TRNG Local Macros
 * @{
 */
#define TIMEOUT              (0x1000U)

/**
 * @defgroup TRNG_Check_Parameters_Validity TRNG Check Parameters Validity
 * @{
 */
#define IS_VALID_SHIFT_CNT(x)                                                  \
(   ((x) == TRNG_SHIFT_COUNT_32)                ||                             \
    ((x) == TRNG_SHIFT_COUNT_64)                ||                             \
    ((x) == TRNG_SHIFT_COUNT_128)               ||                             \
    ((x) == TRNG_SHIFT_COUNT_256))

#define IS_VALID_RELOAD(x)                                                     \
(   ((x) == TRNG_RELOAD_ENABLE)                 ||                             \
    ((x) == TRNG_RELOAD_DISABLE))

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
 * @defgroup TRNG_Global_Functions TRNG Global Functions
 * @{
 */

/**
 * @brief  Set shift times
 * @param  [in] u32ShiftCount            Config the shift times.
 *  This parameter can be a value of the following:
 *   @arg  TRNG_SHIFT_COUNT_32           Shift 32 times
 *   @arg  TRNG_SHIFT_COUNT_64           Shift 64 times
 *   @arg  TRNG_SHIFT_COUNT_128          Shift 128 times
 *   @arg  TRNG_SHIFT_COUNT_256          Shift 256 times
 * @retval None
 */
void TRNG_SetShiftCnt(uint32_t u32ShiftCount)
{
    DDL_ASSERT(IS_VALID_SHIFT_CNT(u32ShiftCount));
    MODIFY_REG32(M4_TRNG->MR, TRNG_MR_CNT, u32ShiftCount);
}

/**
 * @brief  Enable or disable load new value
 * @param  [in] u32LoadCmd              Enable or disable load new value.
 *  This parameter can be a value of the following:
 *   @arg  TRNG_RELOAD_ENABLE           Enable the function
 *   @arg  TRNG_RELOAD_DISABLE          Disable the function
 * @retval None
 */
void TRNG_LoadCmd(uint32_t u32LoadCmd)
{
    DDL_ASSERT(IS_VALID_RELOAD(u32LoadCmd));
    MODIFY_REG32(M4_TRNG->MR, TRNG_MR_LOAD, u32LoadCmd);
}

/**
 * @brief  Start TRNG and generate random number
 * @param  [in] u32Random       The destination address where the random number will be stored.
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t TRNG_Generate(uint32_t u32Random[])
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32TimeCount = 0U;
    if(u32Random != NULL)
    {
        enRet = Ok;
        /* Turn on TRNG circuit. */
        bM4_TRNG->CR_b.EN = 1U;
        /* Start TRNG */
        bM4_TRNG->CR_b.RUN = 1U;
        /* Wait for the TRNG to stop */
        while(bM4_TRNG->CR_b.RUN == 1U)
        {
            if(u32TimeCount++ > TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        if(enRet == Ok)
        {
            /* Get the random number. */
            u32Random[0U] = M4_TRNG->DR0;
            u32Random[1U] = M4_TRNG->DR1;
        }
        /* Stop TRNG generating. */
        bM4_TRNG->CR_b.RUN = 0U;

        /* Turn off TRNG circuit. */
        bM4_TRNG->CR_b.EN = 0U;
    }
    return enRet;
}

/**
 * @}
 */

#endif /* DDL_TRNG_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

