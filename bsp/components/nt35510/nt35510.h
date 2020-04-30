/**
 *******************************************************************************
 * @file  nt35510.h
 * @brief This file contains all the functions prototypes of the NT35510 driver
 *        library.
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
#ifndef __NT35510_H__
#define __NT35510_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @defgroup NT35510
  * @{
  */

#if (BSP_NT35510_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup NT35510_Global_Macros NT35510 Global Macros
 * @{
 */
#define NT35510_WRITE_RAM           ((uint16_t)0x2C00U)
#define ABS(X)                      ((X) > 0 ? (X) : -(X))

/**
 * @}
 */

/**
  * @brief  NT35510 ID
  */
#define  NT35510_ID                 ((uint16_t)0x5510U)

/**
  * @brief  NT35510 Size
  */
#define  NT35510_LCD_PIXEL_WIDTH    ((uint16_t)480)
#define  NT35510_LCD_PIXEL_HEIGHT   ((uint16_t)800)


/**
  * @brief  Scan direction
  */
#define L2R_U2D  0 //´Ó×óµ½ÓÒ,´ÓÉÏµ½ÏÂ
#define L2R_D2U  1 //´Ó×óµ½ÓÒ,´ÓÏÂµ½ÉÏ
#define R2L_U2D  2 //´ÓÓÒµ½×ó,´ÓÉÏµ½ÏÂ
#define R2L_D2U  3 //´ÓÓÒµ½×ó,´ÓÏÂµ½ÉÏ
#define U2D_L2R  4 //´ÓÉÏµ½ÏÂ,´Ó×óµ½ÓÒ
#define U2D_R2L  5 //´ÓÉÏµ½ÏÂ,´ÓÓÒµ½×ó
#define D2U_L2R  6 //´ÓÏÂµ½ÉÏ,´Ó×óµ½ÓÒ
#define D2U_R2L  7 //´ÓÏÂµ½ÉÏ,´ÓÓÒµ½×ó
#define DFT_SCAN_DIR  L2R_U2D//R2L_D2U//D2U_L2R//R2L_D2U  //Ä¬ÈÏµÄÉ¨Ãè·½Ïò

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @defgroup NT35510_Global_Functions TCA9539 Global Functions
 * @{
 */
void NT35510_Init(void);
uint16_t NT35510_ReadID(void);
void NT35510_DisplayOn(void);
void NT35510_DisplayOff(void);
//void NT35510_WriteReg(uint16_t LCD_Reg);
void NT35510_WriteReg(uint16_t Reg, uint16_t Data);
uint32_t NT35510_ReadData(void);
uint16_t NT35510_GetLcdPixelWidth(void);
uint16_t NT35510_GetLcdPixelHeight(void);
void NT35510_SetCursor(uint16_t Xpos, uint16_t Ypos);
void NT35510_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
void NT35510_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t RGBCode);
void NT35510_SetDirection(uint32_t dir);

void LCD_Init(void);
void LCD_WriteData(uint16_t Data);
void LCD_WriteMultipleData(uint16_t *pData, uint32_t Size);
void LCD_WriteReg(uint16_t Reg);
uint16_t LCD_ReadData(void);
void LCD_Delay (uint32_t delay);



/**
 * @}
 */

#endif /* BSP_NT35510_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __NT35510_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
