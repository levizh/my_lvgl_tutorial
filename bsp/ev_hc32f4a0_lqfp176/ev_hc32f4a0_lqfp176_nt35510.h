/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_nt35510.h
 * @brief This file contains all the functions prototypes of the
 *        ev_hc32f4a0_lqfp176_nt35510.c driver library.
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
#ifndef __EV_HC32F4A0_LQFP176_NT35510_H__
#define __EV_HC32F4A0_LQFP176_NT35510_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f4a0_lqfp176.h"
#include "nt35510.h"

/**
 * @addtogroup BSP
 * @{
 */

/** @addtogroup EV_HC32F4A0_LQFP176
  * @{
  */

#if (BSP_NT35510_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/** @defgroup HC32F4A0_EV_IO_Exported_Constants LCD Constants
  * @{
  */
#define LCD_CS                                  (EXMC_SMC_CHIP_3)

#define LCD_CS_PORT                             (GPIO_PORT_G)   /* PG10 - EXMC_CE2 */
#define LCD_CS_PIN                              (GPIO_PIN_12)

#define LCD_WE_PORT                             (GPIO_PORT_C)   /* PC00 - EXMC_WE */
#define LCD_WE_PIN                              (GPIO_PIN_00)

#define LCD_OE_PORT                             (GPIO_PORT_F)   /* PF11 - EXMC_OE */
#define LCD_OE_PIN                              (GPIO_PIN_11)

#define LCD_RS_PORT                             (GPIO_PORT_G)   /* PG02 - EXMC_ADD12 for LCD_RS */
#define LCD_RS_PIN                              (GPIO_PIN_02)

#define LCD_DATA0_PORT                          (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define LCD_DATA0_PIN                           (GPIO_PIN_14)
#define LCD_DATA1_PORT                          (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define LCD_DATA1_PIN                           (GPIO_PIN_15)
#define LCD_DATA2_PORT                          (GPIO_PORT_D)   /* PD00 - EXMC_DATA2 */
#define LCD_DATA2_PIN                           (GPIO_PIN_00)
#define LCD_DATA3_PORT                          (GPIO_PORT_D)   /* PD01 - EXMC_DATA3 */
#define LCD_DATA3_PIN                           (GPIO_PIN_01)
#define LCD_DATA4_PORT                          (GPIO_PORT_E)   /* PE07 - EXMC_DATA4 */
#define LCD_DATA4_PIN                           (GPIO_PIN_07)
#define LCD_DATA5_PORT                          (GPIO_PORT_E)   /* PE08 - EXMC_DATA5 */
#define LCD_DATA5_PIN                           (GPIO_PIN_08)
#define LCD_DATA6_PORT                          (GPIO_PORT_E)   /* PE09 - EXMC_DATA6 */
#define LCD_DATA6_PIN                           (GPIO_PIN_09)
#define LCD_DATA7_PORT                          (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define LCD_DATA7_PIN                           (GPIO_PIN_10)
#define LCD_DATA8_PORT                          (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define LCD_DATA8_PIN                           (GPIO_PIN_11)
#define LCD_DATA9_PORT                          (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define LCD_DATA9_PIN                           (GPIO_PIN_12)
#define LCD_DATA10_PORT                         (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define LCD_DATA10_PIN                          (GPIO_PIN_13)
#define LCD_DATA11_PORT                         (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define LCD_DATA11_PIN                          (GPIO_PIN_14)
#define LCD_DATA12_PORT                         (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define LCD_DATA12_PIN                          (GPIO_PIN_15)
#define LCD_DATA13_PORT                         (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define LCD_DATA13_PIN                          (GPIO_PIN_08)
#define LCD_DATA14_PORT                         (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define LCD_DATA14_PIN                          (GPIO_PIN_09)
#define LCD_DATA15_PORT                         (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define LCD_DATA15_PIN                          (GPIO_PIN_10)


//画笔颜色
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40 //棕色
#define BRRED            0XFC07 //棕红色
#define GRAY             0X8430 //灰色
//GUI颜色
#define DARKBLUE         0X01CF	//深蓝色
#define LIGHTBLUE        0X7D7C	//浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色
#define LIGHTGREEN       0X841F //浅绿色
//#define LIGHTGRAY      0XEF5B //浅灰色(PANNEL)
#define LGRAY            0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)




/**
 * @}
 */

/** @defgroup HC32F4A0_EV_LCD_Function_Sel LCD function definition
 * @{
 */

void BSP_LCD_Clear(uint16_t RGBCode);
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t RGBCode);
void BSP_LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3, uint16_t RGBCode);

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
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Global_Functions HC32F4A0 EV LCD Functions
 * @{
 */

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

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F4A0_LQFP176_NT35510__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
