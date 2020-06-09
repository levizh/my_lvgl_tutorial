/**
 *******************************************************************************
 * @file  hc32f4a0_rmu.c
 * @brief This file provides firmware functions to manage the Reset Manage Unit
 *        (RMU).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-12-30       Heqb          First version
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
#include "hc32f4a0_rmu.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_RMU RMU
 * @brief RMU Driver Library
 * @{
 */

#if (DDL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Local_Macros RMU Local Macros
 * @{
 */

#define RMU_FLAG_TIMEOUT            (0x40U)

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
 * @defgroup RMU_Global_Functions RMU Global Functions
 * @{
 */
 
/**
 * @brief  Get the reset cause.
 * @param  [in] pstcData    Pointer to return reset cause structure.
 *                          See the definition for stc_rmu_rstcause_t
 * @retval Ok: Get successfully.
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t RMU_GetStatus(stc_rmu_rstcause_t *pstcData)
{
    en_result_t enRet = Ok;
    uint32_t u32RstReg;

    if(NULL == pstcData)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        u32RstReg = READ_REG32(M4_RMU->RSTF0);
        pstcData->enMultiRst = u32RstReg & RMU_RSTF0_MULTIRF ? Set : Reset;
        pstcData->enCpuLockErrRst = u32RstReg & RMU_RSTF0_LKUPRF ? Set : Reset;
        pstcData->enXtalErrRst = u32RstReg & RMU_RSTF0_XTALERF ? Set : Reset;
        pstcData->enClkFreqErrRst = u32RstReg & RMU_RSTF0_CKFERF ? Set : Reset;
        pstcData->enRamEccRst = u32RstReg & RMU_RSTF0_RAECRF ? Set : Reset;
        pstcData->enRamParityErrRst = u32RstReg & RMU_RSTF0_RAPERF ? Set : Reset;
        pstcData->enMpuErrRst = u32RstReg & RMU_RSTF0_MPUERF ? Set : Reset;
        pstcData->enSoftwareRst = u32RstReg & RMU_RSTF0_SWRF ? Set : Reset;
        pstcData->enPowerDownRst = u32RstReg & RMU_RSTF0_PDRF ? Set : Reset;
        pstcData->enSwdtRst = u32RstReg & RMU_RSTF0_SWDRF ? Set : Reset;
        pstcData->enWdtRst = u32RstReg & RMU_RSTF0_WDRF ? Set : Reset;
        pstcData->enPvd2Rst = u32RstReg & RMU_RSTF0_PVD2RF ? Set : Reset;
        pstcData->enPvd1Rst = u32RstReg & RMU_RSTF0_PVD1RF ? Set : Reset;
        pstcData->enBrownOutRst = u32RstReg & RMU_RSTF0_BORF ? Set : Reset;
        pstcData->enRstPinRst = u32RstReg & RMU_RSTF0_PINRF ? Set : Reset;
        pstcData->enPowerOnRst = u32RstReg & RMU_RSTF0_PORF ? Set : Reset;
    }
    return enRet;
}

/**
 * @brief  Clear reset Status.
 * @param  None
 * @retval Ok: Clear successfully.
 *         ErrorTimeout: Process timeout
 * @note   Clear reset flag should be done after read RMU_RSTF0 register.
 */
en_result_t RMU_ClrStatus(void)
{
    en_result_t enRet = Ok;
    uint32_t u32Status;
    uint8_t  u8Timeout = 0U;
    do
    {
        u8Timeout++;
        SET_REG32_BIT(M4_RMU->RSTF0, RMU_RSTF0_CLRF);
        u32Status = READ_REG32(M4_RMU->RSTF0);
    }while((u8Timeout != RMU_FLAG_TIMEOUT) && u32Status);

     if(u8Timeout >= RMU_FLAG_TIMEOUT)
    {
        enRet = ErrorTimeout;
    }
    return enRet;
}

/**
 * @brief  Enable or disable LOCKUP reset.
 * @param  [in] enNewState    Enable or disable LOCKUP reset.
 * @retval None
 */
void RMU_CPULockUpCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG8(bM4_RMU->PRSTCR0_b.LKUPREN, enNewState);
}

/**
 * @}
 */

#endif /* DDL_RMU_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

