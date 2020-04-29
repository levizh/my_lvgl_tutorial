/**
 *******************************************************************************
 * @file  hc32f4a0_rmu.h
 * @brief This file contains all the functions prototypes of the RMU driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-12-30       Heqb            First version
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
#ifndef __HC32F4A0_RMU_H__
#define __HC32F4A0_RMU_H__

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
 * @addtogroup DDL_RMU
 * @{
 */
#if (DDL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup RMU_Global_Types RMU Global Types
 * @{
 */

/**
  * @brief  system reset cause flag
  */
typedef struct

{
    en_flag_status_t   enMultiRst;                  /*!< Multiply reset cause*/
    en_flag_status_t   enCpuLockErrRst;             /*!< M4 Lockup reset*/
    en_flag_status_t   enXtalErrRst;                /*!< Xtal error reset*/
    en_flag_status_t   enClkFreqErrRst;             /*!< Clk freqence error reset*/
    en_flag_status_t   enRamEccRst;                 /*!< Ram ECC reset*/
    en_flag_status_t   enRamParityErrRst;           /*!< Ram parity error reset*/
    en_flag_status_t   enMpuErrRst;                 /*!< Mpu error reset*/
    en_flag_status_t   enSoftwareRst;               /*!< Software reset*/
    en_flag_status_t   enPowerDownRst;              /*!< Power down reset*/
    en_flag_status_t   enSwdtRst;                   /*!< Special watchdog timer reset*/
    en_flag_status_t   enWdtRst;                    /*!< Watchdog timer reset*/
    en_flag_status_t   enPvd2Rst;                   /*!< Program voltage Dectection 2 reset*/
    en_flag_status_t   enPvd1Rst;                   /*!< Program voltage Dectection 1 reset*/
    en_flag_status_t   enBrownOutRst;               /*!< Brown-out reset*/
    en_flag_status_t   enRstPinRst;                 /*!< Reset pin reset*/
    en_flag_status_t   enPowerOnRst;                /*!< Power on reset*/
}stc_rmu_rstcause_t;

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Global_Macros RMU Global Macros
 * @{
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
 * @addtogroup RMU_Global_Functions
 * @{
 */
en_result_t RMU_GetStatus(stc_rmu_rstcause_t *pstcData);
en_result_t RMU_ClrStatus(void);
void RMU_CPULockUpCmd(en_functional_state_t enNewState);
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
#ifdef __cplusplus
}
#endif



#endif /* __HC32F4A0_RMU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

