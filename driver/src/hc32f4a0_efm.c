/**
 *******************************************************************************
 * @file  hc32f4a0_efm.c
 * @brief This file provides firmware functions to manage the Embedded Flash
 *        Management unit (EFM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-06       Heqb           First version
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
#include "hc32f4a0_efm.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EFM EFM
 * @brief Embedded Flash Management Driver Library
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Local_Macros EFM Local Macros
 * @{
 */
#define SECTOR_SIZE                  ((uint32_t)0x2000U)
#define REG_LENGTH                   ((uint32_t)32U)
#define OTP_LOCK_ADDR_START          ((uint32_t)0x03001800U)
#define OTP_LOCK_ADDR_END            ((uint32_t)0x03001AD7U)
#define OTP_ENABLE_ADDR              ((uint32_t)0x03001AD8U)
/**
 * @defgroup EFM_Configuration_Bit_Mask EFM Configuration Bit Mask
 * @{
 */
#define EFM_CLR_FLAG_MASK      (EFM_FLAG_CLR_OTPWERR0 | EFM_FLAG_CLR_PRTWERR0 | EFM_FLAG_CLR_PGSZERR0 | \
                                EFM_FLAG_CLR_MISMTCH0 | EFM_FLAG_CLR_OPTEND0  | EFM_FLAG_CLR_CLOLERR0 | \
                                EFM_FLAG_CLR_PRTWERR1 | EFM_FLAG_CLR_PGSZERR1 | EFM_FLAG_CLR_MISMTCH1 | \
                                EFM_FLAG_CLR_OPTEND1  | EFM_FLAG_CLR_CLOLERR1)

#define EFM_CHCHE_MASK         (EFM_FRMC_CRST | EFM_FRMC_PREFE | EFM_FRMC_DCACHE | EFM_FRMC_ICACHE)
/**
 * @}
 */

/**
 * @defgroup EFM_Check_Parameters_Validity EFM Check Parameters Validity
 * @{
 */
/*  Parameter validity check for pointer. */
#define IS_VALID_POINTER(x)                     (NULL != (x))

/*  Parameter validity check for flash latency. */
#define IS_VALID_EFM_WAIT_CYCLE(x)                                  \
(   ((x) == EFM_WAIT_CYCLE_0)         ||                            \
    ((x) == EFM_WAIT_CYCLE_1)         ||                            \
    ((x) == EFM_WAIT_CYCLE_2)         ||                            \
    ((x) == EFM_WAIT_CYCLE_3)         ||                            \
    ((x) == EFM_WAIT_CYCLE_4)         ||                            \
    ((x) == EFM_WAIT_CYCLE_5)         ||                            \
    ((x) == EFM_WAIT_CYCLE_6)         ||                            \
    ((x) == EFM_WAIT_CYCLE_7)         ||                            \
    ((x) == EFM_WAIT_CYCLE_8)         ||                            \
    ((x) == EFM_WAIT_CYCLE_9)         ||                            \
    ((x) == EFM_WAIT_CYCLE_10)        ||                            \
    ((x) == EFM_WAIT_CYCLE_11)        ||                            \
    ((x) == EFM_WAIT_CYCLE_12)        ||                            \
    ((x) == EFM_WAIT_CYCLE_13)        ||                            \
    ((x) == EFM_WAIT_CYCLE_14)        ||                            \
    ((x) == EFM_WAIT_CYCLE_15))

/*  Parameter validity check for operate mode. */
#define IS_VALID_EFM_OPERATE_MD(x)                                   \
(   ((x) == EFM_MODE_PROGRAMSINGLE)   ||                             \
    ((x) == EFM_MODE_PROGRAMREADBACK) ||                             \
    ((x) == EFM_MODE_PROGRAMSEQUENCE) ||                             \
    ((x) == EFM_MODE_ERASESECTOR)     ||                             \
    ((x) == EFM_MODE_ERASECHIP1)      ||                             \
    ((x) == EFM_MODE_ERASECHIP2)      ||                             \
    ((x) == EFM_MODE_READONLY)        ||                             \
    ((x) == EFM_MODE_READONLY1))

/*  Parameter validity check for flash interrupt select. */
#define IS_VALID_EFM_INT_SEL(x)                                      \
(   ((x) == EFM_INT_OPTEND)           ||                             \
    ((x) == EFM_INT_PEERR)            ||                             \
    ((x) == EFM_INT_RDCOLERR)         ||                             \
    ((x) == EFM_INT_PEERR_OPTEND)     ||                             \
    ((x) == EFM_INT_PEERR_RDCOLERR)   ||                             \
    ((x) == EFM_INT_OPTEND_RDCOLERR)  ||                             \
    ((x) == EFM_INT_ALL))

/*  Parameter validity check for flash flag. */
#define IS_VALID_EFM_FLAG(x)                                         \
(   ((x) == EFM_FLAG_OTPWERR0)        ||                             \
    ((x) == EFM_FLAG_PRTWERR0)        ||                             \
    ((x) == EFM_FLAG_PGSZERR0)        ||                             \
    ((x) == EFM_FLAG_MISMTCH0)        ||                             \
    ((x) == EFM_FLAG_OPTEND0)         ||                             \
    ((x) == EFM_FLAG_CLOLERR0)        ||                             \
    ((x) == EFM_FLAG_RDY0)            ||                             \
    ((x) == EFM_FLAG_PRTWERR1)        ||                             \
    ((x) == EFM_FLAG_PGSZERR1)        ||                             \
    ((x) == EFM_FLAG_MISMTCH1)        ||                             \
    ((x) == EFM_FLAG_OPTEND1)         ||                             \
    ((x) == EFM_FLAG_CLOLERR1)        ||                             \
    ((x) == EFM_FLAG_RDY1))

/*  Parameter validity check for flash clear flag. */
#define IS_VALID_EFM_CLRFLAG(x)                                      \
(   ((x) == EFM_FLAG_CLR_OTPWERR0)     ||                            \
    ((x) == EFM_FLAG_CLR_PRTWERR0)     ||                            \
    ((x) == EFM_FLAG_CLR_PGSZERR0)     ||                            \
    ((x) == EFM_FLAG_CLR_MISMTCH0)     ||                            \
    ((x) == EFM_FLAG_CLR_OPTEND0)      ||                            \
    ((x) == EFM_FLAG_CLR_CLOLERR0)     ||                            \
    ((x) == EFM_FLAG_CLR_PRTWERR1)     ||                            \
    ((x) == EFM_FLAG_CLR_PGSZERR1)     ||                            \
    ((x) == EFM_FLAG_CLR_MISMTCH1)     ||                            \
    ((x) == EFM_FLAG_CLR_OPTEND1)      ||                            \
    ((x) == EFM_FLAG_CLR_CLOLERR1)     ||                            \
    ((x) == EFM_CLR_FLAG_MASK))

/*  Parameter validity check for bus state while flash program or erase. */
#define IS_VALID_EFM_BUS_STATE(x)                                    \
(   ((x) == EFM_BUS_BUSY)              ||                            \
    ((x) == EFM_BUS_RELEASE))

/*  Parameter validity check for efm data cache reset state. */
#define IS_VALID_EFM_CACHERST_STATE(x)                               \
(   ((x) == EFM_CACHERST_ON)           ||                            \
    ((x) == EFM_CACHERST_OFF))

/*  Parameter validity check for efm prefetch function. */
#define IS_VALID_EFM_PREFETCH_STATE(x)                               \
(   ((x) == EFM_PREFETCH_ON)           ||                            \
    ((x) == EFM_PREFETCH_OFF))

/*  Parameter validity check for efm data cache function. */
#define IS_VALID_EFM_DCHEEN_STATE(x)                                 \
(   ((x) == EFM_DATACACHE_ON)          ||                            \
    ((x) == EFM_DATACACHE_OFF))

/*  Parameter validity check for efm instruction cache function. */
#define IS_VALID_EFM_ICHEEN_STATE(x)                                 \
(   ((x) == EFM_INSCACHE_ON)           ||                            \
    ((x) == EFM_INSCACHE_OFF))

/*  Parameter validity check for efm address. */
#define IS_VALID_EFM_ADDR(x)                                         \
(   ((x) <= EFM_END_ADDR)              ||                            \
    (((x) >= EFM_OTP_BLOCK16) && ((x) <= EFM_OTP_BLOCK181)))

/*  Parameter validity check for sector protected register locking. */
#define IS_VALID_EFM_REG_LOCK(x)                                     \
(   ((x) == EFM_WRLOCK0)               ||                            \
    ((x) == EFM_WRLOCK1)               ||                            \
    ((x) == EFM_WRLOCK2)               ||                            \
    ((x) == EFM_WRLOCK3)               ||                            \
    ((x) == EFM_WRLOCK4)               ||                            \
    ((x) == EFM_WRLOCK5)               ||                            \
    ((x) == EFM_WRLOCK6)               ||                            \
    ((x) == EFM_WRLOCK7))

/*  Parameter validity check for efm protect register . */
#define IS_VALID_EFM_PRTREG(x)                                       \
(   ((x) == EFM_PROTECT_FWMC)          ||                            \
    ((x) == EFM_PROTECT_OTP))

/*  Parameter validity check for efm state . */
#define IS_VALID_EFM_STATE(x)                                        \
(   ((x) == EFM_F0ACT_F1ACT)           ||                            \
    ((x) == EFM_F0STP_F1ACT)           ||                            \
    ((x) == EFM_F0ACT_F1STP)           ||                            \
    ((x) == EFM_F0STP_F1STP))

/*  Parameter validity check for efm read mode . */
#define IS_VALID_EFM_LVREAD_MODE(x)                                  \
(   ((x) == EFM_LOWVOLREAD_ON)         ||                            \
    ((x) == EFM_LOWVOLREAD_OFF))

/*  Parameter validity check for efm erase mode . */
#define IS_VALID_EFM_ERASE_MODE(x)                                   \
(   ((x) == EFM_MODE_ERASECHIP1)       ||                            \
    ((x) == EFM_MODE_ERASECHIP2))

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
 * @defgroup EFM_Global_Functions EFM Global Functions
 * @{
 */

/**
 * @brief  EFM Protect Unlock.
 * @param  None
 * @retval None
 */
void EFM_Unlock(void)
{
    M4_EFM->FAPRT = EFM_SECRET_KEY1;
    M4_EFM->FAPRT = EFM_SECRET_KEY2;
}

/**
 * @brief  EFM Protect Lock.
 * @param  None
 * @retval None
 */
void EFM_Lock(void)
{
    M4_EFM->FAPRT = (uint16_t)0x1111U;
}

/**
 * @brief  EFM_FWMC or OPT write unlock.
 * @param  [in] u8ProtectReg    specifies the unlock for register.
 *  This parameter can be one of the following values:
 *   @arg  EFM_PROTECT_FWMC      EFM_FWMC remove write protection
 *   @arg  EFM_PROTECT_OTP       OTP remove write protection
 * @retval None
 */
void EFM_KEYRegWriteUnlock(uint8_t u8ProtectReg)
{   
    DDL_ASSERT(IS_VALID_EFM_PRTREG(u8ProtectReg));
    if(u8ProtectReg == EFM_PROTECT_FWMC)
    {
        M4_EFM->KEY1 = (uint32_t)0x01234567U;
        M4_EFM->KEY1 = (uint32_t)0xFEDCBA98U;
    }
    else
    {
        M4_EFM->KEY2 = (uint32_t)0x10325476U;
        M4_EFM->KEY2 = (uint32_t)0xEFCDAB89U;
    }
}

/**
 * @brief  EFM_FWMC or OPT write lock.
 * @param  [in] u8ProtectReg    specifies the Lock for register.
 *  This parameter can be one of the following values:
 *   @arg  EFM_PROTECT_FWMC     EFM_FWMC write protection
 *   @arg  EFM_PROTECT_OTP      OTP write protection
 * @retval None
 * @note   EFM_FWMC register need remove write protection
 */
void EFM_KEYRegWriteLock(uint8_t u8ProtectReg)
{   
    DDL_ASSERT(IS_VALID_EFM_PRTREG(u8ProtectReg));
    if(u8ProtectReg == EFM_PROTECT_FWMC)
    {
        bM4_EFM->FWMC_b.KEY1LOCK = Set;
    }
    else
    {
        bM4_EFM->FWMC_b.KEY2LOCK = Set;
    }
}

/**
 * @brief  Enable or disable EFM.
 * @param  [in] u32efmstate       Specifies the flash state.
 *  This parameter can be one of the following values:
 *   @arg  EFM_F0ACT_F1ACT         flash 0 activity,flash 1 activity
 *   @arg  EFM_F0STP_F1ACT         flash 0 stop,flash 1 activity
 *   @arg  EFM_F0ACT_F1STP         flash 0 activity,flash 1 stop
 *   @arg  EFM_F0STP_F1STP         flash 0 stop,flash 1 stop
 * @retval None
 */

void EFM_Cmd(uint32_t u32efmstate)
{
    DDL_ASSERT(IS_VALID_EFM_STATE(u32efmstate));
    M4_EFM->FSTP = u32efmstate;
}

/**
 * @brief  Init efm config structure with default value.
 * @param  [in] pstcEfmCfg         The pointer of efm config structure.
 *   @arg  u32WaitCycle            Specifies the efm read wait cycles.
 *   @arg  u32Prefetch             Specifies the prefetch on or off.
 *   @arg  u32CacheRst             Specifies the data cache reset on or off.
 *   @arg  u32InsCache             Specifies the instruction cache on or off.
 *   @arg  u32DataCache            Specifies the data cache on or off.
 *   @arg  u32LowVolRead           Specifies the read of low-voltage mode on or off.
 *   @arg  u32BusState             Specifies the bus state busy or release while program & erase.
 *   @arg  u32OperateMode          Specifies the operate mode.
 *   @arg  u32FlashStatus          Specifies the Flash status.
 * @retval An en_result_t enumeration value:
 *         - Ok: Initialize successfully
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_StrucInit(stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcEfmCfg->u32WaitCycle   = EFM_WAIT_CYCLE_0;
        pstcEfmCfg->u32Prefetch    = EFM_PREFETCH_OFF;
        pstcEfmCfg->u32CacheRst    = EFM_CACHERST_OFF;
        pstcEfmCfg->u32InsCache    = EFM_INSCACHE_OFF;
        pstcEfmCfg->u32DataCache   = EFM_DATACACHE_OFF; 
        pstcEfmCfg->u32LowVolRead  = EFM_LOWVOLREAD_OFF;
        pstcEfmCfg->u32BusState    = EFM_BUS_BUSY;
        pstcEfmCfg->u32OperateMode = EFM_MODE_READONLY;
        pstcEfmCfg->u32FlashStatus = EFM_F0ACT_F1ACT;
    }

    return enRet;
}

/**
 * @brief  Efm Config.
 * @param  [in] pstcEfmCfg         The pointer of efm config structure.
 *   @arg  u32WaitCycle            Specifies the efm read wait cycles.
 *   @arg  u32Prefetch             Specifies the prefetch on or off.
 *   @arg  u32CacheRst             Specifies the data cache reset on or off.
 *   @arg  u32InsCache             Specifies the instruction cache on or off.
 *   @arg  u32DataCache            Specifies the data cache on or off.
 *   @arg  u32LowVolRead           Specifies the read of low-voltage mode on or off.
 *   @arg  u32BusState             Specifies the bus state busy or release while program & erase.
 *   @arg  u32OperateMode          Specifies the operate mode.
 *   @arg  u32FlashStatus          Specifies the Flash status.
 * @retval An en_result_t enumeration value:
 *         - Ok: Configure success
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;
    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Param valid check */
        DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(pstcEfmCfg->u32WaitCycle));
        DDL_ASSERT(IS_VALID_EFM_BUS_STATE(pstcEfmCfg->u32BusState));
        DDL_ASSERT(IS_VALID_EFM_CACHERST_STATE(pstcEfmCfg->u32CacheRst));
        DDL_ASSERT(IS_VALID_EFM_PREFETCH_STATE(pstcEfmCfg->u32Prefetch));
        DDL_ASSERT(IS_VALID_EFM_DCHEEN_STATE(pstcEfmCfg->u32DataCache));
        DDL_ASSERT(IS_VALID_EFM_ICHEEN_STATE(pstcEfmCfg->u32InsCache));
        DDL_ASSERT(IS_VALID_EFM_LVREAD_MODE(pstcEfmCfg->u32LowVolRead));
        DDL_ASSERT(IS_VALID_EFM_OPERATE_MD(pstcEfmCfg->u32OperateMode));
        DDL_ASSERT(IS_VALID_EFM_STATE(pstcEfmCfg->u32FlashStatus));
        /* EFM_FWMC remove write protection. */
        EFM_KEYRegWriteUnlock(EFM_PROTECT_FWMC);
        u32Temp = pstcEfmCfg->u32WaitCycle | pstcEfmCfg->u32InsCache | pstcEfmCfg->u32DataCache | \
                  pstcEfmCfg->u32Prefetch | pstcEfmCfg->u32CacheRst | pstcEfmCfg->u32LowVolRead;
        /* Config efm. */
        MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT | EFM_FRMC_PREFE | EFM_FRMC_LVM | \
                                   EFM_FRMC_ICACHE | EFM_FRMC_DCACHE | EFM_FRMC_CRST, u32Temp);
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL | EFM_FWMC_PEMOD, \
                                    pstcEfmCfg->u32BusState | pstcEfmCfg->u32OperateMode);
        MODIFY_REG32(M4_EFM->FSTP, EFM_FSTP_F0STP | EFM_FSTP_F1STP, pstcEfmCfg->u32FlashStatus);
        /* EFM_FWMC Lock */
        EFM_KEYRegWriteLock(EFM_PROTECT_FWMC);
    }

    return enRet;
}

/**
 * @brief  Set the code latency value.
 * @param  [in] u32WaitCycle              Specifies the FLASH Latency value.
 *  This parameter can be one of the following values:
 *   @arg  EFM_WAIT_CYCLE_0             Don't insert read wait cycle
 *   @arg  EFM_WAIT_CYCLE_1             Insert 1 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_2             Insert 2 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_3             Insert 3 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_4             Insert 4 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_5             Insert 5 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_6             Insert 6 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_7             Insert 7 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_8             Insert 8 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_9             Insert 9 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_10            Insert 10 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_11            Insert 11 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_12            Insert 12 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_13            Insert 13 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_14            Insert 14 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_15            Insert 15 read wait cycles
 * @retval None
 */
void EFM_SetLatency(uint32_t u32WaitCycle)
{
    /* Param valid check */
    DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(u32WaitCycle));
    /* Set the code latency value. */
    MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT, u32WaitCycle);
}

/**
 * @brief  Enable or disable the flash data cache reset.
 * @param  [in] enNewState           The new status of the flash data cache reset.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_DataCacheRstCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_CRST);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_CRST);
    }
}

/**
 * @brief  Enable or disable the flash prefetch.
 * @param  [in] enNewState                The new state of the flash prefetch.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_PrefetchCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_PREFE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_PREFE);
    }
}

/**
 * @brief  Enable or disable the flash data cache.
 * @param  [in] enNewState                The new state of the flash DCODE cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_DataCacheCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_DCACHE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_DCACHE);
    }
}

/**
 * @brief  Enable or disable the flash instruction cache.
 * @param  [in] enNewState                The new state of the flash instruction cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_InsCacheCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_ICACHE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_ICACHE);
    }
}

/**
 * @brief  Set the FLASH erase program mode .
 * @param  [in] u32PgmMode                Specifies the FLASH erase program mode.
 *  This parameter can be one of the following values:
 *   @arg  EFM_MODE_PROGRAMSINGLE           Program single at a specified address
 *   @arg  EFM_MODE_PROGRAMREADBACK         Program and read back at a specified address
 *   @arg  EFM_MODE_PROGRAMSEQUENCE         Program sequence at sequence address
 *   @arg  EFM_MODE_ERASESECTOR             Sector erase
 *   @arg  EFM_MODE_ERASECHIP1              A flash Chip erase
 *   @arg  EFM_MODE_ERASECHIP2              Two flash Chip erase
 *   @arg  EFM_MODE_READONLY                Read only
 *   @arg  EFM_MODE_READONLY1               Read only
 * @retval None
 */
void EFM_SetOperateMode(uint32_t u32PgmMode)
{
    /* EFM_FWMC remove write protection. */
    EFM_KEYRegWriteUnlock(EFM_PROTECT_FWMC);
    /* Set the program or erase mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, u32PgmMode);
    /* EFM_FWMC Lock */
    EFM_KEYRegWriteLock(EFM_PROTECT_FWMC);
}

/**
 * @brief  Enable or Disable EFM interrupt.
 * @param  [in] u32EfmInt               Specifies the FLASH interrupt source and state.
 *  This parameter can be one of the following values:
 *   @arg  EFM_INT_OPTEND               End of EFM Operation Interrupt source
 *   @arg  EFM_INT_PEERR                Program/erase error Interrupt source
 *   @arg  EFM_INT_RDCOLERR             Read collide error Interrupt source
 *   @arg  EFM_INT_PEERR_OPTEND         Program/erase error and End of EFM operation
 *   @arg  EFM_INT_PEERR_RDCOLERR       Program/erase error and Read collide error
 *   @arg  EFM_INT_OPTEND_RDCOLERR      End of EFM operation and Read collide error
 *   @arg  EFM_INT_ALL                  All Interrupt source
 * @param  [in] enNewState              The new state of specified interrupt.
 *  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_EFM_INT_SEL(u32EfmInt));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @param  [in] u32Flag                  Specifies the FLASH flag to check.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_OTPWERR0               Flash0 otp Programming/erase error flag.
 *   @arg  EFM_FLAG_PRTWERR0               Flash0 write protect address error flag.
 *   @arg  EFM_FLAG_PGSZERR0               Flash0 programming size error flag.
 *   @arg  EFM_FLAG_MISMTCH0               Flash0 programming missing match error flag.
 *   @arg  EFM_FLAG_OPTEND0                Flash0 end of operation flag.
 *   @arg  EFM_FLAG_CLOLERR0               Flash0 read write error flag.
 *   @arg  EFM_FLAG_RDY0                   Flash0 ready flag.
 *   @arg  EFM_FLAG_PRTWERR1               Flash1 write protect address error flag.
 *   @arg  EFM_FLAG_PGSZERR1               Flash1 programming size error flag.
 *   @arg  EFM_FLAG_MISMTCH1               Flash1 programming missing match error flag.
 *   @arg  EFM_FLAG_OPTEND1                Flash1 end of operation flag.
 *   @arg  EFM_FLAG_CLOLERR1               Flash1 read write error flag.
 *   @arg  EFM_FLAG_RDY1                   Flash1 ready flag.
 * @retval An en_flag_status_t enumeration value:
 *         - Set: flag is set
 *         - Reset: flag is reset
 */
en_flag_status_t EFM_GetFlagStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_FLAG(u32Flag));
    return ((0UL == (M4_EFM->FSR & u32Flag)) ? Reset :Set);
}

/**
 * @brief  Clear the flash flag.
 * @param  [in] u32Flag                  Specifies the FLASH flag to clear.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_CLR_OTPWERR0         Clear Flash0 otp Programming/erase error flag
 *   @arg  EFM_FLAG_CLR_PRTWERR0         Clear Flash0 write protect address error flag
 *   @arg  EFM_FLAG_CLR_PGSZERR0         Clear Flash0 programming size error flag
 *   @arg  EFM_FLAG_CLR_MISMTCH0         Clear Flash0 programming miss match error flag
 *   @arg  EFM_FLAG_CLR_OPTEND0          Clear Flash0 end of operation flag
 *   @arg  EFM_FLAG_CLR_CLOLERR0         Clear Flash0 read collide error flag
 *   @arg  EFM_FLAG_CLR_PRTWERR1         Clear Flash1 write protect address error flag
 *   @arg  EFM_FLAG_CLR_PGSZERR1         Clear Flash1 programming size error flag
 *   @arg  EFM_FLAG_CLR_MISMTCH1         Clear Flash1 programming miss match error flag
 *   @arg  EFM_FLAG_CLR_OPTEND1          Clear Flash1 end of operation flag
 *   @arg  EFM_FLAG_CLR_CLOLERR1         Clear Flash1 read collide error flag
 * @retval None
 */
void EFM_ClearFlag(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_CLRFLAG(u32Flag));
    SET_REG32_BIT(M4_EFM->FSCLR, u32Flag);
}

/**
 * @brief  Sector protected register lock.
 * @param  [in] u32EfmRegLock                  Specifies sector protected register locking.
 *  @arg   EFM_WRLOCK0                         F0NWPRT0 controlled sector lock
 *  @arg   EFM_WRLOCK1                         F0NWPRT1 controlled sector lock
 *  @arg   EFM_WRLOCK2                         F0NWPRT2 controlled sector lock
 *  @arg   EFM_WRLOCK3                         F0NWPRT3 controlled sector lock
 *  @arg   EFM_WRLOCK4                         F1NWPRT0 controlled sector lock
 *  @arg   EFM_WRLOCK5                         F1NWPRT1 controlled sector lock
 *  @arg   EFM_WRLOCK6                         F1NWPRT2 controlled sector lock
 *  @arg   EFM_WRLOCK7                         F1NWPRT3 controlled sector lock
 * @retval None
 */
void EFM_SectorRegLock(uint32_t u32EfmRegLock)
{
    DDL_ASSERT(IS_VALID_EFM_REG_LOCK(u32EfmRegLock));
    SET_REG32_BIT(M4_EFM->WLOCK, (uint32_t)u32EfmRegLock);
}

/**
 * @brief  Set setor lock or unlock.
 * @param  [in] u32StartAddr                  Specifies start address for unlock.
 * @param  [in] u32DataSize                   Specifies length for unlock.
 * @param  [in] enNewState                    The new state of specified sector lock.
 *  This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *         - Ok: program successfully.
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_SectorUnlock(uint32_t u32StartAddr, uint32_t u32DataSize, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t *EFM_FxNWPRTy;
    uint32_t StartSect = 0U;
    uint32_t EndSect = 0U;
    uint32_t EndAddr = 0U;
    uint16_t Num = 0U;
    uint16_t NeedSector,StartRegIndex,StartBitPos,EndRegIndex,EndBitPos;
    EndAddr = u32StartAddr + u32DataSize;

    if(EndAddr <= EFM_END_ADDR)
    {
        enRet = Ok;
        StartSect = (uint16_t)(u32StartAddr / SECTOR_SIZE);            /* Calculate the start sector */
        NeedSector = (uint16_t)(u32DataSize / (SECTOR_SIZE +1U) + 1U); /* Calculate the required sectors */
        EndSect = (uint16_t)(StartSect + NeedSector - 1U);             /* Calculate the end sector */
        StartRegIndex = (uint16_t)(StartSect / REG_LENGTH);            /* Register offset for the start sector */
        StartBitPos = (uint16_t)(StartSect % REG_LENGTH);              /* Bit offset for the start sector */
        EndRegIndex = (uint16_t)(EndSect / REG_LENGTH);                /* Register offset for the end sector */
        EndBitPos = (uint16_t)(EndSect % REG_LENGTH);                  /* Bit offset for the end sector */

        EFM_FxNWPRTy = (uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)StartRegIndex << 2U));

        if(StartRegIndex == EndRegIndex)
        {
            for(Num = StartBitPos;Num <= EndBitPos;Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy,(uint32_t)1U<<Num,(uint32_t)enNewState<<Num);
            }
        }
        else
        {
            for(Num = StartBitPos;Num < REG_LENGTH;Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy,(uint32_t)1U<<Num,(uint32_t)enNewState<<Num);
            }
            StartRegIndex += 1U;
            EFM_FxNWPRTy = (uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)EndRegIndex << 2U));
            for(Num = 0U;Num <= EndBitPos;Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy,(uint32_t)1U<<Num,(uint32_t)enNewState<<Num);
            }

            while(StartRegIndex < EndRegIndex)
            {
                EFM_FxNWPRTy = (uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)StartRegIndex << 2U));
                 if(enNewState == Enable)
                 {
                     WRITE_REG32(*EFM_FxNWPRTy, (uint32_t)0xFFFFFFFFUL);
                 }
                 else
                 {
                     WRITE_REG32(*EFM_FxNWPRTy, (uint32_t)0x0UL);
                 }
                StartRegIndex += 1U;
            }
        }
    }
    return enRet;
}

/**
 * @brief  Set bus state while flash program or erase.
 * @param  [in] u32State                  Specifies the new bus state while flash program or erase.
 *  This parameter can be one of the following values:
 *   @arg  EFM_BUS_BUSY                   Bus busy while flash program or erase.
 *   @arg  EFM_BUS_RELEASE                Bus releas while flash program or erase.
 * @retval None
 */
void EFM_SetBusState(uint32_t u32State)
{
    DDL_ASSERT(IS_VALID_EFM_BUS_STATE(u32State));
    /* EFM_FWMC remove write protection. */
    EFM_KEYRegWriteUnlock(EFM_PROTECT_FWMC);

    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL, u32State);
    /* EFM_FWMC Lock */
    EFM_KEYRegWriteLock(EFM_PROTECT_FWMC);
}

/**
 * @brief  Flash single program mode.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - Error: program error
 *         - ErrorTimeout: program error timeout
 *         - ErrorInvalidParameter: Invalid parameter
 * @note  The address should be word align.
 */
en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));

    if(u32Addr % 4U == 0U)
    {
        enRet = Ok;
        /* CLear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE state */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE function */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSINGLE);
        /* Program data. */
        *(uint32_t *)u32Addr = (uint32_t)u32Data;
        if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }

            if(u32Data != *(uint32_t*)u32Addr)
            {
                enRet = Error;
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_OPTEND0);
        }
        else
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY1))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            if(u32Data != *(uint32_t*)u32Addr)
            {
                enRet = Error;
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_OPTEND1);
        }

        /* Recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);

    }

    return enRet;
}

/**
 * @brief  Flash single program with read back.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - Error: program error
 *         - ErrorTimeout: program error timeout
 *         - ErrorInvalidParameter: Invalid parameter
 * @note  The address should be word align.
 */
en_result_t EFM_ProgramReadBack(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));

    if(u32Addr % 4U == 0U)
    {
        enRet = Ok;
        /* CLear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE state */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK); 
        /* Set Program and read back mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMREADBACK);
        /* Program data. */
        *(uint32_t*)u32Addr = (uint32_t)u32Data;

        if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* Get the flag MISMTCH0*/
            if(Set == EFM_GetFlagStatus(EFM_FLAG_MISMTCH0))
            {
                /* Clear flag PGMISMTCH */
                EFM_ClearFlag(EFM_FLAG_CLR_MISMTCH0);
                enRet = Error;
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_OPTEND0);
        }
        else
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY1))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* Get the flag MISMTCH1*/
            if(Set == EFM_GetFlagStatus(EFM_FLAG_MISMTCH1))
            {
                /* clear flag PGMISMTCH */
                EFM_ClearFlag(EFM_FLAG_CLR_MISMTCH1);
                enRet = Error;
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_OPTEND1);
        }
        /* recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);

    }

    return enRet;
}

/**
 * @brief  Flash sequence program.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Len                    The len of specified program data.
 * @param  [in] *pBuf                     The pointer of specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorTimeout: program error timeout
 *         - ErrorInvalidParameter: Invalid parameter
 * @note  The address should be word align.
 *        The length has to be a multiple of 4
 */
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, const uint8_t *u32pBuf)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;
    uint32_t u32pSrc = (uint32_t)u32pBuf;
    uint32_t u32pDest = u32Addr;
    uint32_t u32LoopWords = u32Len >> 2;
    uint32_t u32RemainBytes = u32Len % 4UL;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_POINTER(u32pBuf));
    if((u32Addr % 4U == 0U) && (u32RemainBytes == 0U))
    {
        enRet = Ok;
        /* CLear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE state */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK); 
        /* Set sequence program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSEQUENCE);

        /* program data. */
        while(u32LoopWords--)
        {
            *((uint32_t *)u32pDest) = *((uint32_t *)u32pSrc);
            u32pDest += 4U;
            u32pSrc += 4U;
            /* wait operate end. */
            if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
            {
                while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND0))
                {
                    u32Timeout++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                /* clear end flag. */
                EFM_ClearFlag(EFM_FSCLR_OPTENDCLR0);
                while(Reset != EFM_GetFlagStatus(EFM_FLAG_OPTEND0))
                {
                    u32Timeout++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
            }
            else
            {
                while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND1))
                {
                    u32Timeout++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                /* clear end flag. */
                EFM_ClearFlag(EFM_FSCLR_OPTENDCLR1);
                while(Reset != EFM_GetFlagStatus(EFM_FLAG_OPTEND1))
                {
                    u32Timeout++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
            }
        }
        /* Set read only mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSINGLE);
        u32Timeout = 0U;
        /* wait for flash ready . */
        if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
        }
        else
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY1))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
        }
        /* Recover CACHE */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }
    return enRet;
}

/**
 * @brief  Flash sector erase.
 * @param  [in] u32Addr                   The uncertain(random) address in the specified sector.
 * @retval An en_result_t enumeration value:
 *         - Ok: erase success
 *         - ErrorTimeout: program error timeout
 *         - ErrorInvalidParameter: Invalid parameter
 * @note   The address should be word align.
 */
en_result_t EFM_SectorErase(uint32_t u32Addr)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    if (u32Addr % 4U == 0U)
    {
        enRet = Ok;
        /* CLear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE state */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK); 
        /* Set sector erase mode. */
        EFM_SetOperateMode(EFM_MODE_ERASESECTOR);

        *(uint32_t*)u32Addr = (uint32_t)0U;
        if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
        }
        else
        {
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY1))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_CLR_OPTEND1);
        }
        /* Recover CACHE */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }

    return enRet;
}

/**
 * @brief  Flash OTP lock.
 * @param  [in]  Addr           Specifies the OTP block
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorInvalidParameter: Invalid parameter
 * @note   The address should be word align.
 */
en_result_t EFM_OTPLock(uint32_t Addr)
{
    en_result_t enRet = ErrorInvalidParameter;

    if((Addr >= OTP_LOCK_ADDR_START) &&
       (Addr < OTP_LOCK_ADDR_END )   &&
       (Addr % 4U == 0U))
    {
        enRet = Ok;
        /* Disable OTP write protection */
        EFM_KEYRegWriteUnlock(EFM_PROTECT_OTP);
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSINGLE);
        /* Enable OTP */
        *(uint32_t *)OTP_ENABLE_ADDR = (uint32_t)0UL;
        /* OTP latch */
        *(uint32_t *)Addr = (uint32_t)0UL;
        /* Enable OTP write protection */
        EFM_KEYRegWriteLock(EFM_PROTECT_OTP);
    }

    return enRet;
}

/**
 * @brief  Flash chip erase.
 * @param  [in]  EraseMode      Specifies the FLASH erase mode.
 *   @arg  EFM_MODE_ERASECHIP1  A flash Chip erase mode
 *   @arg  EFM_MODE_ERASECHIP1  Two flash Chip erase mode
 * @param  [in]  u32Addr        Specifies the FLASH block
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorTimeout: program error timeout
 * @note   The address should be word align.
 */
en_result_t EFM_ChipErase(uint32_t EraseMode, uint32_t u32Addr)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;
    DDL_ASSERT(IS_VALID_EFM_ERASE_MODE(EraseMode));
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));

    if(u32Addr % 4U == 0U)
    {
        enRet = Ok;
        /* CLear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE state */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK); 
        /* Set chip erase mode. */
        EFM_SetOperateMode(EraseMode);

        if(EraseMode == EFM_MODE_ERASECHIP1)
        {
            if((u32Addr < EFM_SECTOR128_ADDR) || (u32Addr >= EFM_OTP_BLOCK16))
            {
                /* Flash1 disables write protection  */
                EFM_SectorUnlock(EFM_SECTOR128_ADDR, 0x000FFFFFUL, Enable);
                *(uint32_t*)EFM_SECTOR128_ADDR = (uint32_t)0UL;
                while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY1))
                {
                    u32Timeout ++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                /* CLear the end of operate flag */
                EFM_ClearFlag(EFM_FLAG_CLR_OPTEND1);
            }
            if(u32Addr < EFM_SECTOR128_ADDR)
            {
                /* Flash0 disables write protection  */
                EFM_SectorUnlock(EFM_SECTOR0_ADDR, 0x000FFFFFUL, Enable);
                *(uint32_t*)EFM_SECTOR16_ADDR = (uint32_t)0UL;
                while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
                {
                    u32Timeout ++;
                    if(u32Timeout >= EFM_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                /* CLear the end of operate flag */
                EFM_ClearFlag(EFM_FLAG_CLR_OPTEND1); 
            }
        }
        else
        {
            /* Flash0 Flash1 disables write protection  */
            EFM_SectorUnlock(EFM_SECTOR0_ADDR, 0x001FFFFFUL, Enable);
            *(uint32_t*)EFM_SECTOR16_ADDR = (uint32_t)0UL;
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* CLear the end of operate flag */
            EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
            EFM_ClearFlag(EFM_FLAG_CLR_OPTEND1);
        }
        /* recover CACHE */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }
    return enRet;
}

/**
 * @brief  Get unique logo.
 * @param  None
 * @retval Returns the value of the Logo
 */
uint32_t GetUniqueLogo(void)
{
    uint32_t Logo = 0U;
    Logo = M4_EFM->FHDFG;
    return Logo;
}

/**
 * @brief  Get unique ID.
 * @param  None
 * @retval An stc_efm_unique_id_t structure value:
 *           - uniqueID0: unique ID 0
 *           - uniqueID1: unique ID 1
 *           - uniqueID2: unique ID 2
 */
stc_efm_unique_id_t EFM_GetUID(void)
{
    stc_efm_unique_id_t stcUID;

    stcUID.u32UniqueID0 = M4_EFM->UQID0;
    stcUID.u32UniqueID1 = M4_EFM->UQID1;
    stcUID.u32UniqueID2 = M4_EFM->UQID2;

    return stcUID;
}

/**
 * @}
 */

#endif  /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
