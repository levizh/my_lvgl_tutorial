/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_ov5640.h
 * @brief This file contains all the functions prototypes of the
 *        ev_hc32f4a0_lqfp176_ov5640.c driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-20       Zhangxl         First version
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
#ifndef __EV_HC32F4A0_LQFP176_OV5640_H__
#define __EV_HC32F4A0_LQFP176_OV5640_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f4a0_lqfp176.h"
#include "ov5640.h"

/**
 * @addtogroup BSP
 * @{
 */

/** @addtogroup EV_HC32F4A0_LQFP176
  * @{
  */

#if (BSP_OV5640_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/** @defgroup HC32F4A0_EV_IO_Exported_Constants LCD Constants
  * @{
  */
#define DVP_PIXCLK_PORT                         (GPIO_PORT_F)   /* PF09 - DVP_PIXCLK */
#define DVP_PIXCLK_PIN                          (GPIO_PIN_09)

#define DVP_HSYNC_PORT                          (GPIO_PORT_H)   /* PH08 - DVP_HSYNC */
#define DVP_HSYNC_PIN                           (GPIO_PIN_08)   /* Line sync */

#define DVP_VSYNC_PORT                          (GPIO_PORT_I)   /* PI05 - DVP_VSYNC */
#define DVP_VSYNC_PIN                           (GPIO_PIN_05)   /* Frame sync */

#define DVP_DATA0_PORT                          (GPIO_PORT_H)   /* PH09 - DVP_DATA0 */
#define DVP_DATA0_PIN                           (GPIO_PIN_09)
#define DVP_DATA1_PORT                          (GPIO_PORT_H)   /* PH10 - DVP_DATA1 */
#define DVP_DATA1_PIN                           (GPIO_PIN_10)
#define DVP_DATA2_PORT                          (GPIO_PORT_H)   /* PH11 - DVP_DATA2 */
#define DVP_DATA2_PIN                           (GPIO_PIN_11)
#define DVP_DATA3_PORT                          (GPIO_PORT_H)   /* PH12 - DVP_DATA3 */
#define DVP_DATA3_PIN                           (GPIO_PIN_12)
#define DVP_DATA4_PORT                          (GPIO_PORT_H)   /* PH14 - DVP_DATA4 */
#define DVP_DATA4_PIN                           (GPIO_PIN_14)
#define DVP_DATA5_PORT                          (GPIO_PORT_I)   /* PI04 - DVP_DATA5 */
#define DVP_DATA5_PIN                           (GPIO_PIN_04)
#define DVP_DATA6_PORT                          (GPIO_PORT_I)   /* PI06 - DVP_DATA6 */
#define DVP_DATA6_PIN                           (GPIO_PIN_06)
#define DVP_DATA7_PORT                          (GPIO_PORT_I)   /* PI07 - DVP_DATA7 */
#define DVP_DATA7_PIN                           (GPIO_PIN_07)

/**
 * @}
 */

/** @defgroup HC32F4A0_EV_LCD_Function_Sel Camera function definition
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
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Global_Functions HC32F4A0 EV Camera Functions
 * @{
 */
void BSP_CAM_Init(void);
void BSP_CAM_SetOutSize(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height);
void BSP_CAM_WriteReg(uint16_t reg, uint8_t *pTxBuf, uint32_t len);
void BSP_CAM_ReadReg(uint16_t reg, uint8_t *pRxBuf, uint32_t len);

/**
 * @}
 */

#endif /* BSP_OV5640_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F4A0_LQFP176_OV5640__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
