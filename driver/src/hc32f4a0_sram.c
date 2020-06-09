/**
 *******************************************************************************
 * @file  hc32f4a0_sram.c
 * @brief This file provides firmware functions to manage the SRAM.
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
#include "hc32f4a0_sram.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SRAM SRAM
 * @brief SRAM Driver Library
 * @{
 */

#if (DDL_SRAM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SRAM_Local_Macros SRAM Local Macros
 * @{
 */

/**
 * @defgroup SRAM_Configuration_Bits_Mask SRAM Configuration Bits Mask
 * @{
 */
#define SRAM_ECC_MODE_MSK           (SRAMC_CKCR_ECCMOD)
#define SRAM_CYCLE_MSK              (SRAMC_WTCR_SRAM123RWT)
/**
 * @}
 */

/**
 * @defgroup SRAM_Register_Protect_Command SRAM Register Protect Command
 * @{
 */
#define SRAM_LOCK_CMD               (0x76U)
#define SRAM_UNLOCK_CMD             (0x77U)
/**
 * @}
 */

/**
 * @defgroup SRAM_Check_Parameters_Validity SRAM check parameters validity
 * @{
 */
#define IS_SRAM_ERR_OP(x)                                                      \
(   ((x) == SRAM_ERR_OP_NMI)                ||                                 \
    ((x) == SRAM_ERR_OP_RESET))

#define IS_SRAM_CYCLE(x)                                                       \
(   ((x) <= SRAM_WAIT_CYCLE_7))

#define IS_SRAM_ECC_MODE(x)                                                    \
(   ((x) == SRAM_ECC_MODE_INVALID)          ||                                 \
    ((x) == SRAM_ECC_MODE_1)                ||                                 \
    ((x) == SRAM_ECC_MODE_2)                ||                                 \
    ((x) == SRAM_ECC_MODE_3))

#define IS_SRAM_1_BIT_MSK(x)                                                   \
(   ((x) != 0U)                             &&                                 \
    (((x) & ((x) - 1U)) == 0U))

#define IS_SRAM_BIT_MSK(x, msk)                                                \
(   ((x) != 0U)                             &&                                 \
    (((x) | (msk)) == (msk)))

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
static void SRAM_LockWTCR(void);
static void SRAM_UnlockWTCR(void);

static void SRAM_LockCKCR(void);
static void SRAM_UnlockCKCR(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SRAM_Global_Functions SRAM Global Functions
 * @{
 */

/**
 * @brief   nitializes SRAM.
 * @param  None
 * @retval None
 */
void SRAM_Init(void)
{
    SET_REG32_BIT(M4_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  De-initializes SRAM. Reset the registers of SRAM.
 * @param  None
 * @retval None
 */
void SRAM_DeInit(void)
{
    SRAM_UnlockWTCR();
    CLEAR_REG32(M4_SRAMC->WTCR);
    SRAM_LockWTCR();

    SRAM_UnlockCKCR();
    CLEAR_REG32(M4_SRAMC->CKCR);
    SRAM_LockCKCR();

    SET_REG32_BIT(M4_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  Set access wait cycle for SRAM(s).
 * @param  [in]  u32SramIndex       The SRAM(s) index bit mask.
 *                                  This parameter can be values of @ref SRAM_Index_Bit_Mask
 *   @arg  SRAMH:                   SRAMH.
 *   @arg  SRAM123:                 SRAM1, SRAM2 and SRAM3. When the CPU clock frequency is higher
 *                                  than 200MHz, access wait cycle is needed.
 *   @arg  SRAM4:                   SRAM4. When the CPU clock frequency is higher than 200MHz,
 *                                  access wait cycle is needed.
 *   @arg  SRAMB:                   SRAMB. When the CPU clock frequency is higher than 120MHz,
 *                                  access wait cycle is needed.
 * @param  [in]  u32WriteCycle      The write access wait cycle for the specified SRAM(s)
 *                                  This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 *   @arg  SRAM_WAIT_CYCLE_1:       Wait 1 CPU cycle.
 *   @arg  SRAM_WAIT_CYCLE_2:       Wait 2 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_3:       Wait 3 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_4:       Wait 4 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_5:       Wait 5 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_6:       Wait 6 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_7:       Wait 7 CPU cycles.
 * @param  [in]  u32ReadCycle       The read access wait cycle for the specified SRAM(s)
 *                                  This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 *                                  The arguments are same as u32WriteCycle.
 * @retval None
 */
void SRAM_SetWaitCycle(uint32_t u32SramIndex, uint32_t u32WriteCycle, uint32_t u32ReadCycle)
{
    uint8_t i;
    uint8_t u8OfsWt;
    uint8_t u8OfsRd;
    uint32_t au32SramList[4U] = {SRAM123, SRAM4, SRAMH, SRAMB};

    DDL_ASSERT(IS_SRAM_CYCLE(u32WriteCycle));
    DDL_ASSERT(IS_SRAM_CYCLE(u32ReadCycle));

    SRAM_UnlockWTCR();
    for (i=0U; i<4U; i++)
    {
        if ((u32SramIndex & au32SramList[i]) != 0U)
        {
            u8OfsWt = i << 3U;
            u8OfsRd = u8OfsWt + 4U;
            MODIFY_REG32(M4_SRAMC->WTCR,
                         ((SRAM_CYCLE_MSK << u8OfsWt) | (SRAM_CYCLE_MSK << u8OfsRd)),
                         ((u32WriteCycle << u8OfsWt) | (u32ReadCycle << u8OfsRd)));
        }
    }
    SRAM_LockWTCR();
}

/**
 * @brief  Set ECC mode for SRAM4 and SRAMB.
 * @param  [in]  u32SramIndex       The SRAM(s) index bit mask.This function is used to set the
 *                                  ECC mode of SRAM4 and SRAMB, so u32SramIndex must contain
 *                                  SRAM4 or SRAMB or both, from @ref SRAM_Index_Bit_Mask
 * @param  [in]  u32EccMode         The ECC mode of SRAM4 and SRAMB.
 *                                  This parameter can be a value of @ref SRAM_ECC_Mode
 *   @arg  SRAM_ECC_MODE_INVALID:   The ECC mode is invalid.
 *   @arg  SRAM_ECC_MODE_1:         When 1-bit error occurred:
 *                                  ECC error corrects.
 *                                  No 1-bit-error status flag setting, no interrupt or reset.
 *                                  When 2-bit error occurred:
 *                                  ECC error detects.
 *                                  2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MODE_2:         When 1-bit error occurred:
 *                                  ECC error corrects.
 *                                  1-bit-error status flag sets, no interrupt or reset.
 *                                  When 2-bit error occurred:
 *                                  ECC error detects.
 *                                  2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MODE_3:         When 1-bit error occurred:
 *                                  ECC error corrects.
 *                                  1-bit-error status flag sets and interrupt or reset occurred.
 *                                  When 2-bit error occurred:
 *                                  ECC error detects.
 *                                  2-bit-error status flag sets and interrupt or reset occurred.
 * @retval None
 */
void SRAM_SetEccMode(uint32_t u32SramIndex, uint32_t u32EccMode)
{
    DDL_ASSERT(IS_SRAM_ECC_MODE(u32EccMode));

    SRAM_UnlockCKCR();
    if ((u32SramIndex & SRAM4) != 0U)
    {
        MODIFY_REG32(M4_SRAMC->CKCR, SRAM_ECC_MODE_MSK, u32EccMode);
    }

    if ((u32SramIndex & SRAMB) != 0U)
    {
        MODIFY_REG32(M4_SRAMC->CKCR, SRAM_ECC_MODE_MSK<<2U, u32EccMode);
    }
    SRAM_LockCKCR();
}

/**
 * @brief  Set the operation which is operated after check error occurred.
 * @param  [in]  u32SramIndex       The SRAM(s) index bit mask.
 *                                  This parameter can be values of @ref SRAM_Index_Bit_Mask
 *   @arg  SRAMH:                   SRAMH.
 *   @arg  SRAM123:                 SRAM1, SRAM2 and SRAM3.
 *   @arg  SRAM4:                   SRAM4.
 *   @arg  SRAMB:                   SRAMB.
 * @param  [out] u32OpAfterError    The operation after check error occurred.
 *                                  This parameter can be a value of @ref SRAM_Operation_After_Check_Error
 *   @arg  SRAM_ERR_OP_NMI:         Check error generates NMI(non-maskable interrupt).
 *   @arg  SRAM_ERR_OP_RESET:       Check error generates system reset.
 * @retval None
 */
void SRAM_SetErrOperation(uint32_t u32SramIndex, uint32_t u32OpAfterError)
{
    DDL_ASSERT(IS_SRAM_ERR_OP(u32OpAfterError));

    SRAM_UnlockCKCR();
    if ((u32SramIndex & (SRAM123 | SRAMH)) != 0U)
    {
        bM4_SRAMC->CKCR_b.PYOAD = u32OpAfterError;
    }

    if ((u32SramIndex & SRAM4) != 0U)
    {
        bM4_SRAMC->CKCR_b.ECCOAD = u32OpAfterError;
    }

    if ((u32SramIndex & SRAMB) != 0U)
    {
        bM4_SRAMC->CKCR_b.BECCOAD = u32OpAfterError;
    }
    SRAM_LockCKCR();
}

/**
 * @brief  Get the status of the specified flag of SRAM.
 * @param  [in]  u32Flag            The flag of SRAM.
 *                                  This parameter can be a value of @ref SRAM_Check_Status_Flag
 *   @arg  SRAM_FLAG_SRAM1_PYERR:   SRAM1 parity error.
 *   @arg  SRAM_FLAG_SRAM2_PYERR:   SRAM2 parity error.
 *   @arg  SRAM_FLAG_SRAM3_PYERR:   SRAM3 parity error.
 *   @arg  SRAM_FLAG_SRAMH_PYERR:   SRAMH parity error.
 *   @arg  SRAM_FLAG_SRAM4_1ERR:    SRAM4 ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAM4_2ERR:    SRAM4 ECC 2-bit error.
 *   @arg  SRAM_FLAG_SRAMB_1ERR:    SRAMB ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAMB_2ERR:    SRAMB ECC 2-bit error.
 *   @arg  SRAM_FLAG_CACHE_PYERR:   Cache RAM parity error.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                     The specified flag is set.
 *   @arg  Reset:                   The specified flag is not set.
 */
en_flag_status_t SRAM_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlag = Reset;

    DDL_ASSERT(IS_SRAM_1_BIT_MSK(u32Flag));

    u32Flag &= SRAM_FLAG_ALL;
    if ((M4_SRAMC->CKSR & u32Flag) != 0U)
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear the status of the specified flag of SRAM.
 * @param  [in]  u32Flag            The flag of SRAM.
 *                                  This parameter can be a value(s) of @ref SRAM_Check_Status_Flag
 *   @arg  SRAM_FLAG_SRAM1_PYERR:   SRAM1 parity error.
 *   @arg  SRAM_FLAG_SRAM2_PYERR:   SRAM2 parity error.
 *   @arg  SRAM_FLAG_SRAM3_PYERR:   SRAM3 parity error.
 *   @arg  SRAM_FLAG_SRAMH_PYERR:   SRAMH parity error.
 *   @arg  SRAM_FLAG_SRAM4_1ERR:    SRAM4 ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAM4_2ERR:    SRAM4 ECC 2-bit error.
 *   @arg  SRAM_FLAG_SRAMB_1ERR:    SRAMB ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAMB_2ERR:    SRAMB ECC 2-bit error.
 *   @arg  SRAM_FLAG_CACHE_PYERR:   Cache RAM parity error.
 * @retval None
 */
void SRAM_ClrStatus(uint32_t u32Flag)
{
    u32Flag &= SRAM_FLAG_ALL;
    SET_REG32_BIT(M4_SRAMC->CKSR, u32Flag);
}

/**
 * @}
 */

/**
 * @defgroup SRAM_Local_Functions SRAM Local Functions
 * @{
 */

/**
 * @brief  Lock access wait cycle control register.
 * @param  None
 * @retval None
 */
static void SRAM_LockWTCR(void)
{
    WRITE_REG32(M4_SRAMC->WTPR, SRAM_LOCK_CMD);
}

/**
 * @brief  Unlock access wait cycle control register.
 * @param  None
 * @retval None
 */
static void SRAM_UnlockWTCR(void)
{
    WRITE_REG32(M4_SRAMC->WTPR, SRAM_UNLOCK_CMD);
}

/**
 * @brief  Lock check control register.
 * @param  None
 * @retval None
 */
static void SRAM_LockCKCR(void)
{
    WRITE_REG32(M4_SRAMC->CKPR, SRAM_LOCK_CMD);
}

/**
 * @brief  Unlock check control register.
 * @param  None
 * @retval None
 */
static void SRAM_UnlockCKCR(void)
{
    WRITE_REG32(M4_SRAMC->CKPR, SRAM_UNLOCK_CMD);
}

/**
 * @}
 */

#endif /* DDL_SRAM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
