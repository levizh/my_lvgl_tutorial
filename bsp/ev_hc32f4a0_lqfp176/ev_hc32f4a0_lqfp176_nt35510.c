/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_nt35510.c
 * @brief This file provides firmware functions for LCD.
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
#include "ev_hc32f4a0_lqfp176_nt35510.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/** @defgroup EV_HC32F4A0_LQFP176_NT35510 HC32F4A0 EVB NT35510
  * @{
  */

#if (BSP_NT35510_ENABLE == BSP_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
typedef struct
{
    __IO uint16_t REG;
    __IO uint16_t RAM;
} LCD_Controller_Typedef;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Use EXMC CS3, A12 as the RS signal */
#define LCD_BASE        (((unsigned int)(0x60000000 | ((1UL << 13U)-2U))))
#define LCD             ((LCD_Controller_Typedef *) LCD_BASE)


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
 * @defgroup EV_HC32F4A0_LQFP176_NT35510_Global_Functions HC32F4A0 LQFP176 EVB NT35510 Global Functions
 * @{
 */

/************************************ LCD **************************************/

/**
 * @brief  Initializes LCD gpio.
 */
void LCD_Port_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* LCD_CS */
    GPIO_Init(LCD_CS_PORT, LCD_CS_PIN, &stcGpioInit);

    /* LCD_WE */
    GPIO_Init(LCD_WE_PORT, LCD_WE_PIN, &stcGpioInit);

    /* LCD_OE */
    GPIO_Init(LCD_OE_PORT, LCD_OE_PIN, &stcGpioInit);

    /* DMC_DATA[0:15] */
    GPIO_Init(LCD_DATA0_PORT,  LCD_DATA0_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA1_PORT,  LCD_DATA1_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA2_PORT,  LCD_DATA2_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA3_PORT,  LCD_DATA3_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA4_PORT,  LCD_DATA4_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA5_PORT,  LCD_DATA5_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA6_PORT,  LCD_DATA6_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA7_PORT,  LCD_DATA7_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA8_PORT,  LCD_DATA8_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA9_PORT,  LCD_DATA9_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA10_PORT, LCD_DATA10_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA11_PORT, LCD_DATA11_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA12_PORT, LCD_DATA12_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA13_PORT, LCD_DATA13_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA14_PORT, LCD_DATA14_PIN, &stcGpioInit);
    GPIO_Init(LCD_DATA15_PORT, LCD_DATA15_PIN, &stcGpioInit);

    GPIO_Init(LCD_RS_PORT, LCD_RS_PIN, &stcGpioInit);

    /* LCD_DATA[0:15] */
    GPIO_SetFunc(LCD_DATA0_PORT,  LCD_DATA0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA1_PORT,  LCD_DATA1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA2_PORT,  LCD_DATA2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA3_PORT,  LCD_DATA3_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA4_PORT,  LCD_DATA4_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA5_PORT,  LCD_DATA5_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA6_PORT,  LCD_DATA6_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA7_PORT,  LCD_DATA7_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA8_PORT,  LCD_DATA8_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA9_PORT,  LCD_DATA9_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA10_PORT, LCD_DATA10_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA11_PORT, LCD_DATA11_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA12_PORT, LCD_DATA12_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA13_PORT, LCD_DATA13_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA14_PORT, LCD_DATA14_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_DATA15_PORT, LCD_DATA15_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    GPIO_SetFunc(LCD_CS_PORT, LCD_CS_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_RS_PORT, LCD_RS_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_WE_PORT, LCD_WE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(LCD_OE_PORT, LCD_OE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
}


/**
 * @brief  Initializes LCD low level.
 */
void LCD_Init(void)
{
    stc_exmc_smc_init_t stcSmcInit;
    en_result_t enRet = Error;

    LCD_Port_Init();

    /* Enable SMC module clk */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_SMC, Enable);

    /* Enable SMC. */
    EXMC_SMC_Enable();

    EXMC_SMC_ExitLowPower();
    while (EXMC_SMC_READY != EXMC_SMC_GetStatus())
    {}

    EXMC_SMC_StructInit(&stcSmcInit);

    /*0x6000_0000 ~ 0x60FFFFFF, 16Mb area */
    stcSmcInit.stcChipCfg.u32AddressMatch = 0x60;
    stcSmcInit.stcChipCfg.u32AddressMask  = 0xFF;
    stcSmcInit.stcChipCfg.u32SmcMemWidth  = EXMC_SMC_MEM_WIDTH_16;
    stcSmcInit.stcChipCfg.u32BAA  = EXMC_SMC_BAA_PORT_DISABLE;
    stcSmcInit.stcChipCfg.u32ADV  = EXMC_SMC_ADV_PORT_DISABLE;
    stcSmcInit.stcChipCfg.u32BLS  = EXMC_SMC_BLS_SYNC_CS;
    stcSmcInit.stcChipCfg.u32ReadBurstLen  = EXMC_SMC_MEM_READ_BURST_4;
    stcSmcInit.stcChipCfg.u32WriteBurstLen  = EXMC_SMC_MEM_WRITE_BURST_4;
    stcSmcInit.stcChipCfg.u32ReadMode  = EXMC_SMC_MEM_READ_SYNC;
    stcSmcInit.stcChipCfg.u32WriteMode  = EXMC_SMC_MEM_WRITE_SYNC;

    stcSmcInit.stcTimingCfg.u32RC = 6UL;
    stcSmcInit.stcTimingCfg.u32WC = 4UL;
    stcSmcInit.stcTimingCfg.u32CEOE = 1UL;
    stcSmcInit.stcTimingCfg.u32WP = 2UL;
    stcSmcInit.stcTimingCfg.u32PC = 4UL;
    stcSmcInit.stcTimingCfg.u32TR = 1UL;

    EXMC_SMC_Init(LCD_CS, &stcSmcInit);

    /* Set command: updateregs */
    EXMC_SMC_SetCommand(LCD_CS, EXMC_SMC_CMD_UPDATEREGS, 0UL, 0UL);

    /* Check timing status */
    do {
        enRet = EXMC_SMC_CheckTimingStatus(LCD_CS, &stcSmcInit.stcTimingCfg);
    } while (Ok != enRet);

    /* Check chip status */
    do {
        enRet = EXMC_SMC_CheckChipStatus(LCD_CS, &stcSmcInit.stcChipCfg);
    } while (Ok != enRet);
}

/**
 * @brief  Writes data on LCD data register.
 * @param  Data: Data to be written
 */
void LCD_WriteData(uint16_t Data)
{
    /* Write 16-bit Reg */
    //FMC_BANK1_WriteData(RegValue);
    LCD->RAM = Data;

}

/**
 * @brief  Writes several data on LCD data register.
 * @param  pData: pointer on data to be written
 * @param  Size: data amount in 16bits short unit
 */
void LCD_WriteMultipleData(uint16_t *pData, uint32_t Size)
{
  uint32_t  i;

    for (i = 0; i < Size; i++)
    {
        //FMC_BANK1_WriteData(pData[i]);
        LCD->RAM = pData[i];
    }
}

/**
 * @brief  Writes register on LCD register.
 * @param  Reg: Register to be written
 */
void LCD_WriteReg(uint16_t Reg)
{
    /* Write 16-bit Index, then Write Reg */
    //FMC_BANK1_WriteReg(Reg);
    LCD->REG = Reg;
}

/**
 * @brief  Reads data from LCD data register.
 * @retval Read data.
 */
uint16_t LCD_ReadData(void)
{
    return LCD->RAM;
}

/**
 * @brief  LCD delay
 * @param  delay: Delay in ms
 * @retval None
 */
void LCD_Delay(uint32_t delay)
{
    DDL_Delay1ms(delay);
}

/**
  * @brief  Draws a circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  */
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t RGBCode)
{
    int32_t  decision;        /* Decision Variable */
    uint32_t  current_x;      /* Current X Value */
    uint32_t  current_y;      /* Current Y Value */

    decision = 3 - (Radius << 1);
    current_x = 0;
    current_y = Radius;

    while (current_x <= current_y)
    {
        NT35510_WritePixel((Xpos + current_x), (Ypos - current_y), RGBCode);
        NT35510_WritePixel((Xpos + current_y), (Ypos - current_x), RGBCode);
        NT35510_WritePixel((Xpos + current_y), (Ypos + current_x), RGBCode);
        NT35510_WritePixel((Xpos + current_x), (Ypos + current_y), RGBCode);
        NT35510_WritePixel((Xpos - current_x), (Ypos + current_y), RGBCode);
        NT35510_WritePixel((Xpos - current_y), (Ypos + current_x), RGBCode);
        NT35510_WritePixel((Xpos - current_x), (Ypos - current_y), RGBCode);
        NT35510_WritePixel((Xpos - current_y), (Ypos - current_x), RGBCode);
        current_x++;
        /* Bresenham algorithm */
        if(decision<0)
        {
          decision +=4*current_x+6;
        }
        else
        {
            decision+=10+4*(current_x-current_y);
            current_y--;
        }
    }
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @param  x3: Point 3 X position
  * @param  y3: Point 3 Y position
  */
void BSP_LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3, uint16_t RGBCode)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
    yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
    curpixel = 0;

    deltax = ABS(x2 - x1);          /* The difference between the x's */
    deltay = ABS(y2 - y1);          /* The difference between the y's */
    x = x1;                         /* Start x off at the first pixel */
    y = y1;                         /* Start y off at the first pixel */

    if (x2 >= x1)                   /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else                            /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1)                   /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else                            /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay)           /* There is at least one x-value for every y-value */
    {
        xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
        yinc2 = 0;                  /* Don't change the y for every iteration */
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         /* There are more x-values than y-values */
    }
    else                            /* There is at least one y-value for every x-value */
    {
        xinc2 = 0;                  /* Don't change the x for every iteration */
        yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         /* There are more y-values than x-values */
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        NT35510_DrawLine(x, y, x3, y3, RGBCode);

        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den;             /* Calculate the new numerator value */
            x += xinc1;             /* Change the x as appropriate */
            y += yinc1;             /* Change the y as appropriate */
        }
        x += xinc2;                 /* Change the x as appropriate */
        y += yinc2;                 /* Change the y as appropriate */
    }
}


void BSP_LCD_Clear(uint16_t RGBCode)
{
    uint32_t index=0;
    /* Set cursor */
    NT35510_SetCursor(0U, 0U);

    /* Prepare to write to LCD RAM */
    LCD_WriteReg(NT35510_WRITE_RAM);
    for(index = 0; index < (NT35510_LCD_PIXEL_WIDTH*NT35510_LCD_PIXEL_HEIGHT); index++)
    {
        LCD_WriteData(RGBCode);
    }
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
