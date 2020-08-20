/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_gt9147.h
 * @brief This file contains all the functions prototypes of the
 *        ev_hc32f4a0_lqfp176_gt9147 driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-24       Zhangxl         First version
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
#ifndef __EV_HC32F4A0_LQFP176_GT9147_H__
#define __EV_HC32F4A0_LQFP176_GT9147_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f4a0_lqfp176.h"
#include "gt9147.h"

/**
 * @addtogroup BSP
 * @{
 */

/** @addtogroup EV_HC32F4A0_LQFP176
  * @{
  */

#if (BSP_GT9147_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/** @defgroup HC32F4A0_EV_IO_Exported_Constants IO Exported Constants
  * @{
  */

/**
 * @}
 */

/** @defgroup HC32F4A0_EV_IO_Function_Sel Expand IO function definition
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
 * @defgroup EV_HC32F4A0_LQFP176_GT9147_Global_Functions HC32F4A0 EV Expand IO Global Functions
 * @{
 */
void BSP_IO_Init(void);
void BSP_IO_WritePortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState);
void BSP_IO_ConfigPortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir);
uint8_t BSP_IO_ReadPortPin(uint8_t u8Port, uint8_t u8Pin);
void BSP_IO_TogglePortPin(uint8_t u8Port, uint8_t u8Pin);

void BSP_TS_Init(void);
void BSP_TS_ReadReg(uint16_t reg, uint8_t *pRxBuf, uint32_t len);
void BSP_TS_WriteReg(uint16_t reg, uint8_t *pTxBuf, uint32_t len);

/**
 * @}
 */

#endif /* BSP_GT9147_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F4A0_LQFP176_GT9147__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
