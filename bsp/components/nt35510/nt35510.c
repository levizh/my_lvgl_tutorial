/**
 *******************************************************************************
 * @file  nt35510.c
 * @brief This file provides firmware functions for LCD NT35510.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "nt35510.h"

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
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//LCD分辨率设置
#define SSD_HOR_RESOLUTION      800                                       //LCD水平分辨率
#define SSD_VER_RESOLUTION      480                                       //LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH     1                                         //水平脉宽
#define SSD_HOR_BACK_PORCH      46                                        //水平前廊
#define SSD_HOR_FRONT_PORCH     210                                       //水平后廊

#define SSD_VER_PULSE_WIDTH     1                                         //垂直脉宽
#define SSD_VER_BACK_PORCH      23                                        //垂直前廊
#define SSD_VER_FRONT_PORCH     22                                        //垂直前廊
//如下几个参数，自动计算
#define SSD_HT  (SSD_HOR_RESOLUTION + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS (SSD_HOR_BACK_PORCH)
#define SSD_VT  (SSD_VER_RESOLUTION + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void LCD_SSD_BackLightSet(uint8_t pwm);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
stc_lcd_dev_t lcddev;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup NT35510_Global_Functions NT35510 Global Functions
 * @{
 */
/**
 * @brief  LCD device initialize.
 * @param  none
 * @retval none
 */
void NT35510_Init(void)
{
    lcddev.width  = 480;
    lcddev.height = 800;
    lcddev.id = 0x5510;
    lcddev.wramcmd=0x2C00;
    lcddev.setxcmd=0x2A00;
    lcddev.setycmd=0x2B00;
    LCD_Init();

    /* read ID: 8000H (5510H) */
    NT35510_WriteReg(0x0000,0x0001);
    lcddev.id = NT35510_ReadReg(0x0000U);

    LCD_WriteReg(0xDA00);
    LCD_Delay(10);
    lcddev.id=LCD_ReadData();
    LCD_Delay(10);
    LCD_WriteReg(0XDB00);
    LCD_Delay(10);
    lcddev.id=LCD_ReadData();
    LCD_Delay(10);
    lcddev.id<<=8;
    LCD_WriteReg(0XDC00);
    LCD_Delay(10);
    lcddev.id |= LCD_ReadData();
    LCD_Delay(10);

    if (lcddev.id == 0x8000)
    {
        lcddev.id = 0x5510;
    }
    else
    {
        /* read ID: 5761H (1963H) */
        LCD_WriteReg(0xA1);
        LCD_Delay(10);
        lcddev.id=LCD_ReadData();
        LCD_Delay(10);
        lcddev.id=LCD_ReadData();
        LCD_Delay(10);
        lcddev.id<<=8;
        lcddev.id |= LCD_ReadData();
        LCD_Delay(10);
        if (lcddev.id == 0x5761)
        {
            lcddev.id = 0x1963;
        }
    }

    if (0x5510 == lcddev.id)
    {
        /* Config LCD */
        NT35510_WriteReg(0xF000,0x55);
        NT35510_WriteReg(0xF001,0xAA);
        NT35510_WriteReg(0xF002,0x52);
        NT35510_WriteReg(0xF003,0x08);
        NT35510_WriteReg(0xF004,0x01);
        /* AVDD Set AVDD 5.2V */
        NT35510_WriteReg(0xB000,0x0D);
        NT35510_WriteReg(0xB001,0x0D);
        NT35510_WriteReg(0xB002,0x0D);
        /* AVDD ratio */
        NT35510_WriteReg(0xB600,0x34);
        NT35510_WriteReg(0xB601,0x34);
        NT35510_WriteReg(0xB602,0x34);
        /* AVEE -5.2V */
        NT35510_WriteReg(0xB100,0x0D);
        NT35510_WriteReg(0xB101,0x0D);
        NT35510_WriteReg(0xB102,0x0D);
        /* AVEE ratio */
        NT35510_WriteReg(0xB700,0x34);
        NT35510_WriteReg(0xB701,0x34);
        NT35510_WriteReg(0xB702,0x34);
        /* VCL -2.5V */
        NT35510_WriteReg(0xB200,0x00);
        NT35510_WriteReg(0xB201,0x00);
        NT35510_WriteReg(0xB202,0x00);
        /* VCL ratio */
        NT35510_WriteReg(0xB800,0x24);
        NT35510_WriteReg(0xB801,0x24);
        NT35510_WriteReg(0xB802,0x24);
        /* VGH 15V (Free pump) */
        NT35510_WriteReg(0xBF00,0x01);
        NT35510_WriteReg(0xB300,0x0F);
        NT35510_WriteReg(0xB301,0x0F);
        NT35510_WriteReg(0xB302,0x0F);
        /* VGH ratio */
        NT35510_WriteReg(0xB900,0x34);
        NT35510_WriteReg(0xB901,0x34);
        NT35510_WriteReg(0xB902,0x34);
        /* VGL_REG -10V */
        NT35510_WriteReg(0xB500,0x08);
        NT35510_WriteReg(0xB501,0x08);
        NT35510_WriteReg(0xB502,0x08);
        NT35510_WriteReg(0xC200,0x03);
        /* VGLX ratio */
        NT35510_WriteReg(0xBA00,0x24);
        NT35510_WriteReg(0xBA01,0x24);
        NT35510_WriteReg(0xBA02,0x24);
        /* VGMP/VGSP 4.5V/0V */
        NT35510_WriteReg(0xBC00,0x00);
        NT35510_WriteReg(0xBC01,0x78);
        NT35510_WriteReg(0xBC02,0x00);
        /* VGMN/VGSN -4.5V/0V */
        NT35510_WriteReg(0xBD00,0x00);
        NT35510_WriteReg(0xBD01,0x78);
        NT35510_WriteReg(0xBD02,0x00);
        /* VCOM */
        NT35510_WriteReg(0xBE00,0x00);
        NT35510_WriteReg(0xBE01,0x64);
        /* Gamma Setting */
        NT35510_WriteReg(0xD100,0x00);
        NT35510_WriteReg(0xD101,0x33);
        NT35510_WriteReg(0xD102,0x00);
        NT35510_WriteReg(0xD103,0x34);
        NT35510_WriteReg(0xD104,0x00);
        NT35510_WriteReg(0xD105,0x3A);
        NT35510_WriteReg(0xD106,0x00);
        NT35510_WriteReg(0xD107,0x4A);
        NT35510_WriteReg(0xD108,0x00);
        NT35510_WriteReg(0xD109,0x5C);
        NT35510_WriteReg(0xD10A,0x00);
        NT35510_WriteReg(0xD10B,0x81);
        NT35510_WriteReg(0xD10C,0x00);
        NT35510_WriteReg(0xD10D,0xA6);
        NT35510_WriteReg(0xD10E,0x00);
        NT35510_WriteReg(0xD10F,0xE5);
        NT35510_WriteReg(0xD110,0x01);
        NT35510_WriteReg(0xD111,0x13);
        NT35510_WriteReg(0xD112,0x01);
        NT35510_WriteReg(0xD113,0x54);
        NT35510_WriteReg(0xD114,0x01);
        NT35510_WriteReg(0xD115,0x82);
        NT35510_WriteReg(0xD116,0x01);
        NT35510_WriteReg(0xD117,0xCA);
        NT35510_WriteReg(0xD118,0x02);
        NT35510_WriteReg(0xD119,0x00);
        NT35510_WriteReg(0xD11A,0x02);
        NT35510_WriteReg(0xD11B,0x01);
        NT35510_WriteReg(0xD11C,0x02);
        NT35510_WriteReg(0xD11D,0x34);
        NT35510_WriteReg(0xD11E,0x02);
        NT35510_WriteReg(0xD11F,0x67);
        NT35510_WriteReg(0xD120,0x02);
        NT35510_WriteReg(0xD121,0x84);
        NT35510_WriteReg(0xD122,0x02);
        NT35510_WriteReg(0xD123,0xA4);
        NT35510_WriteReg(0xD124,0x02);
        NT35510_WriteReg(0xD125,0xB7);
        NT35510_WriteReg(0xD126,0x02);
        NT35510_WriteReg(0xD127,0xCF);
        NT35510_WriteReg(0xD128,0x02);
        NT35510_WriteReg(0xD129,0xDE);
        NT35510_WriteReg(0xD12A,0x02);
        NT35510_WriteReg(0xD12B,0xF2);
        NT35510_WriteReg(0xD12C,0x02);
        NT35510_WriteReg(0xD12D,0xFE);
        NT35510_WriteReg(0xD12E,0x03);
        NT35510_WriteReg(0xD12F,0x10);
        NT35510_WriteReg(0xD130,0x03);
        NT35510_WriteReg(0xD131,0x33);
        NT35510_WriteReg(0xD132,0x03);
        NT35510_WriteReg(0xD133,0x6D);
        NT35510_WriteReg(0xD200,0x00);
        NT35510_WriteReg(0xD201,0x33);
        NT35510_WriteReg(0xD202,0x00);
        NT35510_WriteReg(0xD203,0x34);
        NT35510_WriteReg(0xD204,0x00);
        NT35510_WriteReg(0xD205,0x3A);
        NT35510_WriteReg(0xD206,0x00);
        NT35510_WriteReg(0xD207,0x4A);
        NT35510_WriteReg(0xD208,0x00);
        NT35510_WriteReg(0xD209,0x5C);
        NT35510_WriteReg(0xD20A,0x00);
        NT35510_WriteReg(0xD20B,0x81);
        NT35510_WriteReg(0xD20C,0x00);
        NT35510_WriteReg(0xD20D,0xA6);
        NT35510_WriteReg(0xD20E,0x00);
        NT35510_WriteReg(0xD20F,0xE5);
        NT35510_WriteReg(0xD210,0x01);
        NT35510_WriteReg(0xD211,0x13);
        NT35510_WriteReg(0xD212,0x01);
        NT35510_WriteReg(0xD213,0x54);
        NT35510_WriteReg(0xD214,0x01);
        NT35510_WriteReg(0xD215,0x82);
        NT35510_WriteReg(0xD216,0x01);
        NT35510_WriteReg(0xD217,0xCA);
        NT35510_WriteReg(0xD218,0x02);
        NT35510_WriteReg(0xD219,0x00);
        NT35510_WriteReg(0xD21A,0x02);
        NT35510_WriteReg(0xD21B,0x01);
        NT35510_WriteReg(0xD21C,0x02);
        NT35510_WriteReg(0xD21D,0x34);
        NT35510_WriteReg(0xD21E,0x02);
        NT35510_WriteReg(0xD21F,0x67);
        NT35510_WriteReg(0xD220,0x02);
        NT35510_WriteReg(0xD221,0x84);
        NT35510_WriteReg(0xD222,0x02);
        NT35510_WriteReg(0xD223,0xA4);
        NT35510_WriteReg(0xD224,0x02);
        NT35510_WriteReg(0xD225,0xB7);
        NT35510_WriteReg(0xD226,0x02);
        NT35510_WriteReg(0xD227,0xCF);
        NT35510_WriteReg(0xD228,0x02);
        NT35510_WriteReg(0xD229,0xDE);
        NT35510_WriteReg(0xD22A,0x02);
        NT35510_WriteReg(0xD22B,0xF2);
        NT35510_WriteReg(0xD22C,0x02);
        NT35510_WriteReg(0xD22D,0xFE);
        NT35510_WriteReg(0xD22E,0x03);
        NT35510_WriteReg(0xD22F,0x10);
        NT35510_WriteReg(0xD230,0x03);
        NT35510_WriteReg(0xD231,0x33);
        NT35510_WriteReg(0xD232,0x03);
        NT35510_WriteReg(0xD233,0x6D);
        NT35510_WriteReg(0xD300,0x00);
        NT35510_WriteReg(0xD301,0x33);
        NT35510_WriteReg(0xD302,0x00);
        NT35510_WriteReg(0xD303,0x34);
        NT35510_WriteReg(0xD304,0x00);
        NT35510_WriteReg(0xD305,0x3A);
        NT35510_WriteReg(0xD306,0x00);
        NT35510_WriteReg(0xD307,0x4A);
        NT35510_WriteReg(0xD308,0x00);
        NT35510_WriteReg(0xD309,0x5C);
        NT35510_WriteReg(0xD30A,0x00);
        NT35510_WriteReg(0xD30B,0x81);
        NT35510_WriteReg(0xD30C,0x00);
        NT35510_WriteReg(0xD30D,0xA6);
        NT35510_WriteReg(0xD30E,0x00);
        NT35510_WriteReg(0xD30F,0xE5);
        NT35510_WriteReg(0xD310,0x01);
        NT35510_WriteReg(0xD311,0x13);
        NT35510_WriteReg(0xD312,0x01);
        NT35510_WriteReg(0xD313,0x54);
        NT35510_WriteReg(0xD314,0x01);
        NT35510_WriteReg(0xD315,0x82);
        NT35510_WriteReg(0xD316,0x01);
        NT35510_WriteReg(0xD317,0xCA);
        NT35510_WriteReg(0xD318,0x02);
        NT35510_WriteReg(0xD319,0x00);
        NT35510_WriteReg(0xD31A,0x02);
        NT35510_WriteReg(0xD31B,0x01);
        NT35510_WriteReg(0xD31C,0x02);
        NT35510_WriteReg(0xD31D,0x34);
        NT35510_WriteReg(0xD31E,0x02);
        NT35510_WriteReg(0xD31F,0x67);
        NT35510_WriteReg(0xD320,0x02);
        NT35510_WriteReg(0xD321,0x84);
        NT35510_WriteReg(0xD322,0x02);
        NT35510_WriteReg(0xD323,0xA4);
        NT35510_WriteReg(0xD324,0x02);
        NT35510_WriteReg(0xD325,0xB7);
        NT35510_WriteReg(0xD326,0x02);
        NT35510_WriteReg(0xD327,0xCF);
        NT35510_WriteReg(0xD328,0x02);
        NT35510_WriteReg(0xD329,0xDE);
        NT35510_WriteReg(0xD32A,0x02);
        NT35510_WriteReg(0xD32B,0xF2);
        NT35510_WriteReg(0xD32C,0x02);
        NT35510_WriteReg(0xD32D,0xFE);
        NT35510_WriteReg(0xD32E,0x03);
        NT35510_WriteReg(0xD32F,0x10);
        NT35510_WriteReg(0xD330,0x03);
        NT35510_WriteReg(0xD331,0x33);
        NT35510_WriteReg(0xD332,0x03);
        NT35510_WriteReg(0xD333,0x6D);
        NT35510_WriteReg(0xD400,0x00);
        NT35510_WriteReg(0xD401,0x33);
        NT35510_WriteReg(0xD402,0x00);
        NT35510_WriteReg(0xD403,0x34);
        NT35510_WriteReg(0xD404,0x00);
        NT35510_WriteReg(0xD405,0x3A);
        NT35510_WriteReg(0xD406,0x00);
        NT35510_WriteReg(0xD407,0x4A);
        NT35510_WriteReg(0xD408,0x00);
        NT35510_WriteReg(0xD409,0x5C);
        NT35510_WriteReg(0xD40A,0x00);
        NT35510_WriteReg(0xD40B,0x81);
        NT35510_WriteReg(0xD40C,0x00);
        NT35510_WriteReg(0xD40D,0xA6);
        NT35510_WriteReg(0xD40E,0x00);
        NT35510_WriteReg(0xD40F,0xE5);
        NT35510_WriteReg(0xD410,0x01);
        NT35510_WriteReg(0xD411,0x13);
        NT35510_WriteReg(0xD412,0x01);
        NT35510_WriteReg(0xD413,0x54);
        NT35510_WriteReg(0xD414,0x01);
        NT35510_WriteReg(0xD415,0x82);
        NT35510_WriteReg(0xD416,0x01);
        NT35510_WriteReg(0xD417,0xCA);
        NT35510_WriteReg(0xD418,0x02);
        NT35510_WriteReg(0xD419,0x00);
        NT35510_WriteReg(0xD41A,0x02);
        NT35510_WriteReg(0xD41B,0x01);
        NT35510_WriteReg(0xD41C,0x02);
        NT35510_WriteReg(0xD41D,0x34);
        NT35510_WriteReg(0xD41E,0x02);
        NT35510_WriteReg(0xD41F,0x67);
        NT35510_WriteReg(0xD420,0x02);
        NT35510_WriteReg(0xD421,0x84);
        NT35510_WriteReg(0xD422,0x02);
        NT35510_WriteReg(0xD423,0xA4);
        NT35510_WriteReg(0xD424,0x02);
        NT35510_WriteReg(0xD425,0xB7);
        NT35510_WriteReg(0xD426,0x02);
        NT35510_WriteReg(0xD427,0xCF);
        NT35510_WriteReg(0xD428,0x02);
        NT35510_WriteReg(0xD429,0xDE);
        NT35510_WriteReg(0xD42A,0x02);
        NT35510_WriteReg(0xD42B,0xF2);
        NT35510_WriteReg(0xD42C,0x02);
        NT35510_WriteReg(0xD42D,0xFE);
        NT35510_WriteReg(0xD42E,0x03);
        NT35510_WriteReg(0xD42F,0x10);
        NT35510_WriteReg(0xD430,0x03);
        NT35510_WriteReg(0xD431,0x33);
        NT35510_WriteReg(0xD432,0x03);
        NT35510_WriteReg(0xD433,0x6D);
        NT35510_WriteReg(0xD500,0x00);
        NT35510_WriteReg(0xD501,0x33);
        NT35510_WriteReg(0xD502,0x00);
        NT35510_WriteReg(0xD503,0x34);
        NT35510_WriteReg(0xD504,0x00);
        NT35510_WriteReg(0xD505,0x3A);
        NT35510_WriteReg(0xD506,0x00);
        NT35510_WriteReg(0xD507,0x4A);
        NT35510_WriteReg(0xD508,0x00);
        NT35510_WriteReg(0xD509,0x5C);
        NT35510_WriteReg(0xD50A,0x00);
        NT35510_WriteReg(0xD50B,0x81);
        NT35510_WriteReg(0xD50C,0x00);
        NT35510_WriteReg(0xD50D,0xA6);
        NT35510_WriteReg(0xD50E,0x00);
        NT35510_WriteReg(0xD50F,0xE5);
        NT35510_WriteReg(0xD510,0x01);
        NT35510_WriteReg(0xD511,0x13);
        NT35510_WriteReg(0xD512,0x01);
        NT35510_WriteReg(0xD513,0x54);
        NT35510_WriteReg(0xD514,0x01);
        NT35510_WriteReg(0xD515,0x82);
        NT35510_WriteReg(0xD516,0x01);
        NT35510_WriteReg(0xD517,0xCA);
        NT35510_WriteReg(0xD518,0x02);
        NT35510_WriteReg(0xD519,0x00);
        NT35510_WriteReg(0xD51A,0x02);
        NT35510_WriteReg(0xD51B,0x01);
        NT35510_WriteReg(0xD51C,0x02);
        NT35510_WriteReg(0xD51D,0x34);
        NT35510_WriteReg(0xD51E,0x02);
        NT35510_WriteReg(0xD51F,0x67);
        NT35510_WriteReg(0xD520,0x02);
        NT35510_WriteReg(0xD521,0x84);
        NT35510_WriteReg(0xD522,0x02);
        NT35510_WriteReg(0xD523,0xA4);
        NT35510_WriteReg(0xD524,0x02);
        NT35510_WriteReg(0xD525,0xB7);
        NT35510_WriteReg(0xD526,0x02);
        NT35510_WriteReg(0xD527,0xCF);
        NT35510_WriteReg(0xD528,0x02);
        NT35510_WriteReg(0xD529,0xDE);
        NT35510_WriteReg(0xD52A,0x02);
        NT35510_WriteReg(0xD52B,0xF2);
        NT35510_WriteReg(0xD52C,0x02);
        NT35510_WriteReg(0xD52D,0xFE);
        NT35510_WriteReg(0xD52E,0x03);
        NT35510_WriteReg(0xD52F,0x10);
        NT35510_WriteReg(0xD530,0x03);
        NT35510_WriteReg(0xD531,0x33);
        NT35510_WriteReg(0xD532,0x03);
        NT35510_WriteReg(0xD533,0x6D);
        NT35510_WriteReg(0xD600,0x00);
        NT35510_WriteReg(0xD601,0x33);
        NT35510_WriteReg(0xD602,0x00);
        NT35510_WriteReg(0xD603,0x34);
        NT35510_WriteReg(0xD604,0x00);
        NT35510_WriteReg(0xD605,0x3A);
        NT35510_WriteReg(0xD606,0x00);
        NT35510_WriteReg(0xD607,0x4A);
        NT35510_WriteReg(0xD608,0x00);
        NT35510_WriteReg(0xD609,0x5C);
        NT35510_WriteReg(0xD60A,0x00);
        NT35510_WriteReg(0xD60B,0x81);
        NT35510_WriteReg(0xD60C,0x00);
        NT35510_WriteReg(0xD60D,0xA6);
        NT35510_WriteReg(0xD60E,0x00);
        NT35510_WriteReg(0xD60F,0xE5);
        NT35510_WriteReg(0xD610,0x01);
        NT35510_WriteReg(0xD611,0x13);
        NT35510_WriteReg(0xD612,0x01);
        NT35510_WriteReg(0xD613,0x54);
        NT35510_WriteReg(0xD614,0x01);
        NT35510_WriteReg(0xD615,0x82);
        NT35510_WriteReg(0xD616,0x01);
        NT35510_WriteReg(0xD617,0xCA);
        NT35510_WriteReg(0xD618,0x02);
        NT35510_WriteReg(0xD619,0x00);
        NT35510_WriteReg(0xD61A,0x02);
        NT35510_WriteReg(0xD61B,0x01);
        NT35510_WriteReg(0xD61C,0x02);
        NT35510_WriteReg(0xD61D,0x34);
        NT35510_WriteReg(0xD61E,0x02);
        NT35510_WriteReg(0xD61F,0x67);
        NT35510_WriteReg(0xD620,0x02);
        NT35510_WriteReg(0xD621,0x84);
        NT35510_WriteReg(0xD622,0x02);
        NT35510_WriteReg(0xD623,0xA4);
        NT35510_WriteReg(0xD624,0x02);
        NT35510_WriteReg(0xD625,0xB7);
        NT35510_WriteReg(0xD626,0x02);
        NT35510_WriteReg(0xD627,0xCF);
        NT35510_WriteReg(0xD628,0x02);
        NT35510_WriteReg(0xD629,0xDE);
        NT35510_WriteReg(0xD62A,0x02);
        NT35510_WriteReg(0xD62B,0xF2);
        NT35510_WriteReg(0xD62C,0x02);
        NT35510_WriteReg(0xD62D,0xFE);
        NT35510_WriteReg(0xD62E,0x03);
        NT35510_WriteReg(0xD62F,0x10);
        NT35510_WriteReg(0xD630,0x03);
        NT35510_WriteReg(0xD631,0x33);
        NT35510_WriteReg(0xD632,0x03);
        NT35510_WriteReg(0xD633,0x6D);
        /* LV2 Page 0 enable */
        NT35510_WriteReg(0xF000,0x55);
        NT35510_WriteReg(0xF001,0xAA);
        NT35510_WriteReg(0xF002,0x52);
        NT35510_WriteReg(0xF003,0x08);
        NT35510_WriteReg(0xF004,0x00);
        /* Display control */
        NT35510_WriteReg(0xB100, 0xCC);
        NT35510_WriteReg(0xB101, 0x00);
        /* Source hold time */
        NT35510_WriteReg(0xB600,0x05);
        /* Gate EQ control */
        NT35510_WriteReg(0xB700,0x70);
        NT35510_WriteReg(0xB701,0x70);
        /* Source EQ control (Mode 2) */
        NT35510_WriteReg(0xB800,0x01);
        NT35510_WriteReg(0xB801,0x03);
        NT35510_WriteReg(0xB802,0x03);
        NT35510_WriteReg(0xB803,0x03);
        /* Inversion mode (2-dot) */
        NT35510_WriteReg(0xBC00,0x02);
        NT35510_WriteReg(0xBC01,0x00);
        NT35510_WriteReg(0xBC02,0x00);
        /* Timing control 4H w/ 4-delay */
        NT35510_WriteReg(0xC900,0xD0);
        NT35510_WriteReg(0xC901,0x02);
        NT35510_WriteReg(0xC902,0x50);
        NT35510_WriteReg(0xC903,0x50);
        NT35510_WriteReg(0xC904,0x50);
        NT35510_WriteReg(0x3500,0x00);
        NT35510_WriteReg(0x3A00,0x55);  /* 16-bit/pixel */
        LCD_WriteReg(0x1100);
        LCD_Delay(120);
        LCD_WriteReg(0x2900);
    }
    else if (0x1963 == lcddev.id)
    {
        LCD_WriteReg(0xE2);                                                                     //Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz
        LCD_WriteData(0x1D);                                                                    //参数1
        LCD_WriteData(0x02);                                                                    //参数2 Divider M = 2, PLL = 300/(M+1) = 100MHz
        LCD_WriteData(0x04);                                                                    //参数3 Validate M and N values
        LCD_Delay(1);
        LCD_WriteReg(0xE0);                                                                     // Start PLL command
        LCD_WriteData(0x01);                                                                    // enable PLL
        LCD_Delay(10);
        LCD_WriteReg(0xE0);                                                                     // Start PLL command again
        LCD_WriteData(0x03);                                                                    // now, use PLL output as system clock
        LCD_Delay(12);
        LCD_WriteReg(0x01);                                                                     //软复位
        LCD_Delay(10);

        LCD_WriteReg(0xE6);                                                                     //设置像素频率,33Mhz
        LCD_WriteData(0x2F);
        LCD_WriteData(0xFF);
        LCD_WriteData(0xFF);

        LCD_WriteReg(0xB0);                                                                     //设置LCD模式
        LCD_WriteData(0x20);                                                                    //24位模式
        LCD_WriteData(0x00);                                                                    //TFT 模式

        LCD_WriteData((SSD_HOR_RESOLUTION - 1) >> 8);                                           //设置LCD水平像素
        LCD_WriteData(SSD_HOR_RESOLUTION - 1);
        LCD_WriteData((SSD_VER_RESOLUTION - 1) >> 8);                                           //设置LCD垂直像素
        LCD_WriteData(SSD_VER_RESOLUTION - 1);
        LCD_WriteData(0x00);                                                                    //RGB序列

        LCD_WriteReg(0xB4);                                                                     //Set horizontal period
        LCD_WriteData((SSD_HT - 1) >> 8);
        LCD_WriteData(SSD_HT - 1);
        LCD_WriteData(SSD_HPS >> 8);
        LCD_WriteData(SSD_HPS);
        LCD_WriteData(SSD_HOR_PULSE_WIDTH - 1);
        LCD_WriteData(0x00);
        LCD_WriteData(0x00);
        LCD_WriteData(0x00);
        LCD_WriteReg(0xB6);                                                                     //Set vertical period
        LCD_WriteData((SSD_VT - 1) >> 8);
        LCD_WriteData(SSD_VT - 1);
        LCD_WriteData(SSD_VPS >> 8);
        LCD_WriteData(SSD_VPS);
        LCD_WriteData(SSD_VER_FRONT_PORCH - 1);
        LCD_WriteData(0x00);
        LCD_WriteData(0x00);

        LCD_WriteReg(0xF0);                                                                     //设置SSD1963与CPU接口为16bit
        LCD_WriteData(0x03);                                                                    //16-bit(565 format) data for 16bpp

        LCD_WriteReg(0x29);                                                                     //开启显示
        //设置PWM输出  背光通过占空比可调
        LCD_WriteReg(0xD0);                                                                     //设置自动白平衡DBC
        LCD_WriteData(0x00);                                                                    //disable

        LCD_WriteReg(0xBE);                                                                     //配置PWM输出
        LCD_WriteData(0x05);                                                                    //1设置PWM频率
        LCD_WriteData(0xFE);                                                                    //2设置PWM占空比
        LCD_WriteData(0x01);                                                                    //3设置C
        LCD_WriteData(0x00);                                                                    //4设置D
        LCD_WriteData(0x00);                                                                    //5设置E
        LCD_WriteData(0x00);                                                                    //6设置F

        LCD_WriteReg(0xB8);                                                                     //设置GPIO配置
        LCD_WriteData(0x03);                                                                    //2个IO口设置成输出
        LCD_WriteData(0x01);                                                                    //GPIO使用正常的IO功能
        LCD_WriteReg(0xBA);
        LCD_WriteData(0X01);                                                                    //GPIO[1:0]=01,控制LCD方向

        LCD_SSD_BackLightSet(100);                                                            //背光设置为最亮
    }

    NT35510_SetDirection(0);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval LCD Register Value.
  */
uint16_t NT35510_ReadID(void)
{
    LCD_Init();
    //return ((uint16_t)NT35510_ReadData(LCD_READ_ID4, LCD_READ_ID4_SIZE));
    return (0x5510U);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void NT35510_DisplayOn(void)
{
  /* Display On */
  //NT35510_WriteReg(LCD_DISPLAY_ON);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void NT35510_DisplayOff(void)
{
  /* Display Off */
  //NT35510_WriteReg(LCD_DISPLAY_OFF);
}

/**
  * @brief  Writes to the selected LCD register.
  * @param  Reg: address of the selected register.
  * @param  Data: Data to be written
  * @retval None
  */
void NT35510_WriteReg(uint16_t Reg, uint16_t Data)
{
    LCD_WriteReg(Reg);

    LCD_WriteData(Data);
}

/**
  * @brief  Read the selected LCD register.
  * @param  Reg: address of the selected register.
  * @retval reg value
  */
uint16_t NT35510_ReadReg(uint16_t Reg)
{
    LCD_WriteReg(Reg);

    return LCD_ReadData();
}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void NT35510_WriteData(uint16_t RegValue)
{
  LCD_WriteData(RegValue);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  None
  * @retval LCD ram Value.
  */
uint32_t NT35510_ReadData(void)
{
  /* Read a max of 4 bytes */
  return (LCD_ReadData());
}

/**
  * @brief  Get LCD PIXEL WIDTH.
  * @param  None
  * @retval LCD PIXEL WIDTH.
  */
uint16_t NT35510_GetLcdPixelWidth(void)
{
  /* Return LCD PIXEL WIDTH */
  return 0;//NT35510_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Get LCD PIXEL HEIGHT.
  * @param  None
  * @retval LCD PIXEL HEIGHT.
  */
uint16_t NT35510_GetLcdPixelHeight(void)
{
  /* Return LCD PIXEL HEIGHT */
  return 0;//NT35510_LCD_PIXEL_HEIGHT;
}

/**
 * @brief  Set Cursor position.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @retval None
 */
void NT35510_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    if (lcddev.id == 0x5510)
    {
        NT35510_WriteReg(lcddev.setxcmd, Xpos>>8);
        NT35510_WriteReg(lcddev.setxcmd+1, Xpos&0XFF);
        NT35510_WriteReg(lcddev.setycmd, Ypos>>8);
        NT35510_WriteReg(lcddev.setycmd+1, Ypos&0XFF);
    }
    else if (lcddev.id == 0x1963)
    {
        if (lcddev.dir == 0)                                                                                                      //x坐标需要变换
        {
            Xpos = lcddev.width - 1 - Xpos;
            LCD_WriteReg(lcddev.setxcmd);
            LCD_WriteData(0); LCD_WriteData(0);
            LCD_WriteData(Xpos >> 8); LCD_WriteData(Xpos & 0XFF);
        }else
        {
            LCD_WriteReg(lcddev.setxcmd);
            LCD_WriteData(Xpos >> 8); LCD_WriteData(Xpos & 0XFF);
            LCD_WriteData((lcddev.width - 1) >> 8); LCD_WriteData((lcddev.width - 1) & 0XFF);
        }
        LCD_WriteReg(lcddev.setycmd);
        LCD_WriteData(Ypos >> 8); LCD_WriteData(Ypos & 0XFF);
        LCD_WriteData((lcddev.height - 1) >> 8); LCD_WriteData((lcddev.height - 1) & 0XFF);
    }
    else
    {
    }
}

/**
 * @brief  Write pixel.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  RGBCode: the RGB pixel color in RGB565 format
 * @retval None
 */
void NT35510_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
    /* Set cursor */
    NT35510_SetCursor(Xpos, Ypos);

    /* Prepare to write to LCD RAM */
    LCD_WriteReg(lcddev.wramcmd);

    LCD_WriteData(RGBCode);

}

/**
 * @brief  Write line.
 * @param  x1: specifies the X position 1.
 * @param  x2: specifies the X position 2.
 * @param  y1: specifies the Y position 1.
 * @param  y2: specifies the Y position 2.
 * @param  RGBCode: the RGB pixel color in RGB565 format
 * @retval None
 */
void NT35510_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t RGBCode)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x = 0, delta_y = 0, distance = 0;
    int incx = 0, incy = 0, Row = 0, Col = 0;
    delta_x = x2 - x1;      /* calc delta X, Y*/
    delta_y = y2 - y1;
    Row = x1;
    Col = y1;
    if (delta_x > 0)
    {
        incx = 1;           /* forward direction */
    }
    else if (delta_x == 0)
    {
        incx = 0;           /* vertical line */
    }
    else
    {
        incx = -1;          /* reverse direction */
        delta_x = -delta_x;
    }

    if (delta_y > 0)        /* downward direction */
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy=0;             /* horizontal line */
    }
    else
    {
        incy=-1;            /* upward direction */
        delta_y=-delta_y;
    }

    if (delta_x > delta_y)
    {
        distance = delta_x; /* set axis */
    }
    else
    {
        distance = delta_y;
    }
    for(t = 0;t <= distance+1; t++ )
    {
        NT35510_WritePixel(Row,Col, RGBCode);   /* draw pixel */
        xerr += delta_x ;
        yerr += delta_y ;
        if(xerr > distance)
        {
            xerr -= distance;
            Row += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            Col += incy;
        }
    }
}


void NT35510_SetScanDir(uint32_t dir)
{
    uint16_t regval=0;
    uint16_t dirreg=0;
    if((lcddev.dir==1) || (lcddev.dir == 0 && lcddev.id == 0X1963))
    {
        switch(dir)
        {
            case 0:dir=6;break;
            case 1:dir=7;break;
            case 2:dir=4;break;
            case 3:dir=5;break;
            case 4:dir=1;break;
            case 5:dir=0;break;
            case 6:dir=3;break;
            case 7:dir=2;break;
        }
    }
    if(lcddev.id==0X5310 || lcddev.id==0X5510 || lcddev.id == 0X1963)
    {
        switch(dir)
        {
            case L2R_U2D://麓脫脳贸碌陆脫脪,麓脫脡脧碌陆脧脗
                regval|=(0<<7)|(0<<6)|(0<<5);
                break;
            case L2R_D2U://麓脫脳贸碌陆脫脪,麓脫脧脗碌陆脡脧
                regval|=(1<<7)|(0<<6)|(0<<5);
                break;
            case R2L_U2D://麓脫脫脪碌陆脳贸,麓脫脡脧碌陆脧脗
                regval|=(0<<7)|(1<<6)|(0<<5);
                break;
            case R2L_D2U://麓脫脫脪碌陆脳贸,麓脫脧脗碌陆脡脧
                regval|=(1<<7)|(1<<6)|(0<<5);
                break;
            case U2D_L2R://麓脫脡脧碌陆脧脗,麓脫脳贸碌陆脫脪
                regval|=(0<<7)|(0<<6)|(1<<5);
                break;
            case U2D_R2L://麓脫脡脧碌陆脧脗,麓脫脫脪碌陆脳贸
                regval|=(0<<7)|(1<<6)|(1<<5);
                break;
            case D2U_L2R://麓脫脧脗碌陆脡脧,麓脫脳贸碌陆脫脪
                regval|=(1<<7)|(0<<6)|(1<<5);
                break;
            case D2U_R2L://麓脫脧脗碌陆脡脧,麓脫脫脪碌陆脳贸
                regval|=(1<<7)|(1<<6)|(1<<5);
                break;
        }
        if (lcddev.id == 0X5510)
        {
            dirreg=0x3600;
        }
        else
        {
            dirreg=0x36;
        }
        NT35510_WriteReg(dirreg,regval);
        if (lcddev.id == 0X5510)
        {
            LCD_WriteReg(lcddev.setxcmd);LCD_WriteData(0);
            LCD_WriteReg(lcddev.setxcmd+1);LCD_WriteData(0);
            LCD_WriteReg(lcddev.setxcmd+2);LCD_WriteData((lcddev.width-1)>>8);
            LCD_WriteReg(lcddev.setxcmd+3);LCD_WriteData((lcddev.width-1)&0XFF);
            LCD_WriteReg(lcddev.setycmd);LCD_WriteData(0);
            LCD_WriteReg(lcddev.setycmd+1);LCD_WriteData(0);
            LCD_WriteReg(lcddev.setycmd+2);LCD_WriteData((lcddev.height-1)>>8);
            LCD_WriteReg(lcddev.setycmd+3);LCD_WriteData((lcddev.height-1)&0XFF);
        }
        else
        {
            LCD_WriteReg(lcddev.setxcmd);
            LCD_WriteData(0); LCD_WriteData(0);
            LCD_WriteData((lcddev.width - 1) >> 8); LCD_WriteData((lcddev.width - 1) & 0XFF);
            LCD_WriteReg(lcddev.setycmd);
            LCD_WriteData(0); LCD_WriteData(0);
            LCD_WriteData((lcddev.height - 1) >> 8); LCD_WriteData((lcddev.height - 1) & 0XFF);
        }
    }
}

void NT35510_SetDirection(uint32_t dir)
{
    if(dir==0)              /* Vertical */
    {
        lcddev.dir=0;
        if (0x1963 == lcddev.id)
        {
            lcddev.wramcmd=0x2C;
            lcddev.setxcmd=0x2B;
            lcddev.setycmd=0x2A;
        }
        else //5510
        {
            lcddev.wramcmd=0x2C00;
            lcddev.setxcmd=0x2A00;
            lcddev.setycmd=0x2B00;
        }
        lcddev.width=480;
        lcddev.height=800;

    }
    else                    /* Horizontal */
    {
        lcddev.dir=1;
        lcddev.wramcmd=0X2C00;
        lcddev.setxcmd=0X2A00;
        lcddev.setycmd=0X2B00;
        lcddev.width=800;
        lcddev.height=480;
    }
    NT35510_SetScanDir(DFT_SCAN_DIR);
}


//SSD1963 背光设置
//pwm:背光等级,0~100.越大越亮.
void LCD_SSD_BackLightSet(uint8_t pwm)
{
    LCD_WriteReg(0xBE);                                                                                                             //配置PWM输出
    LCD_WriteData(0x05);                                                                                                            //1设置PWM频率
    LCD_WriteData(pwm * 2.55);                                                                                                      //2设置PWM占空比
    LCD_WriteData(0x01);                                                                                                            //3设置C
    LCD_WriteData(0xFF);                                                                                                            //4设置D
    LCD_WriteData(0x00);                                                                                                            //5设置E
    LCD_WriteData(0x00);                                                                                                            //6设置F
}
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
