/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_ov5640.c
 * @brief This file provides firmware functions for Camera.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-06       Zhangxl         First version
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
#include "ev_hc32f4a0_lqfp176_ov5640.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/** @defgroup EV_HC32F4A0_LQFP176_OV5640 HC32F4A0 EVB OV5640
  * @{
  */

#if (BSP_OV5640_ENABLE == BSP_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Global_Functions HC32F4A0 LQFP176 EVB OV5640 Global Functions
 * @{
 */

/************************************ Camera **********************************/

/**
 * @brief  Initializes Camera gpio.
 */
static void CAM_Port_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinIType = PIN_ITYPE_CMOS;

    /* DVP_PIXCLK */
    GPIO_Init(DVP_PIXCLK_PORT, DVP_PIXCLK_PIN, &stcGpioInit);

    /* DVP_HSYNC */
    GPIO_Init(DVP_HSYNC_PORT, DVP_HSYNC_PIN, &stcGpioInit);

    /* DVP_VSYNC */
    GPIO_Init(DVP_VSYNC_PORT, DVP_VSYNC_PIN, &stcGpioInit);

    /* DVP_DATA[0:7] */
    GPIO_Init(DVP_DATA0_PORT,  DVP_DATA0_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA1_PORT,  DVP_DATA1_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA2_PORT,  DVP_DATA2_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA3_PORT,  DVP_DATA3_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA4_PORT,  DVP_DATA4_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA5_PORT,  DVP_DATA5_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA6_PORT,  DVP_DATA6_PIN, &stcGpioInit);
    GPIO_Init(DVP_DATA7_PORT,  DVP_DATA7_PIN, &stcGpioInit);

    /* DVP_DATA[0:7] */
    GPIO_SetFunc(DVP_DATA0_PORT,  DVP_DATA0_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA1_PORT,  DVP_DATA1_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA2_PORT,  DVP_DATA2_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA3_PORT,  DVP_DATA3_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA4_PORT,  DVP_DATA4_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA5_PORT,  DVP_DATA5_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA6_PORT,  DVP_DATA6_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_DATA7_PORT,  DVP_DATA7_PIN,  GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);

    GPIO_SetFunc(DVP_PIXCLK_PORT, DVP_PIXCLK_PIN, GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_HSYNC_PORT, DVP_HSYNC_PIN, GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DVP_VSYNC_PORT, DVP_VSYNC_PIN, GPIO_FUNC_13_DVP, PIN_SUBFUNC_DISABLE);
}


/**
 * @brief  Initializes Camera low level.
 */
void BSP_CAM_Init(void)
{
    CAM_Port_Init();

    /* Enable DVP module clk */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_DVP, Enable);

    OV5640_Init();
}

/**
 * @brief  Writes data on LCD data register.
 * @param  Data: Data to be written
 */
void CAM_WriteData(uint16_t Data)
{

}

/**
 * @brief  Writes several data on LCD data register.
 * @param  pData: pointer on data to be written
 * @param  Size: data amount in 16bits short unit
 */
void CAM_WriteMultipleData(uint16_t *pData, uint32_t Size)
{

}

void BSP_CAM_SetOutSize(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height)
{
    uint8_t reg_val = 0U;
    reg_val = 0x03;
    BSP_CAM_WriteReg(0x3212U, (uint8_t *)&reg_val, 1U); //start group 3
    reg_val = width >> 8U;
    BSP_CAM_WriteReg(0x3808U, (uint8_t *)&reg_val, 1U);
    reg_val = width & 0xFFU;
    BSP_CAM_WriteReg(0x3809U, (uint8_t *)&reg_val, 1U);
    reg_val = height >> 8U;
    BSP_CAM_WriteReg(0x380AU, (uint8_t *)&reg_val, 1U);
    reg_val = height & 0xFFU;
    BSP_CAM_WriteReg(0x380BU, (uint8_t *)&reg_val, 1U);
    reg_val = offx >> 8U;
    BSP_CAM_WriteReg(0x3810U, (uint8_t *)&reg_val, 1U);
    reg_val = offx & 0xFFU;
    BSP_CAM_WriteReg(0x3811U, (uint8_t *)&reg_val, 1U);
    reg_val = offy >> 8U;
    BSP_CAM_WriteReg(0x3812U, (uint8_t *)&reg_val, 1U);
    reg_val = offy & 0xFFU;
    BSP_CAM_WriteReg(0x3813U, (uint8_t *)&reg_val, 1U);
    reg_val = 0x13U;
    BSP_CAM_WriteReg(0x3212U, (uint8_t *)&reg_val, 1U); //end group 3
    reg_val = 0xA3U;
    BSP_CAM_WriteReg(0x3212U, (uint8_t *)&reg_val, 1U); //launch group 3
}

/**
 * @brief  Writes register on Camera register.
 * @param  Reg: Register to be written
 */
void BSP_CAM_WriteReg(uint16_t reg, uint8_t *pTxBuf, uint32_t len)
{
    uint16_t tmp = 0U;
    tmp = ((reg & 0xFFU) << 8U) | ((reg & 0xFF00U) >> 8U);

    I2C_Start(OV5640_I2C_CH, OV5640_TIMEOUT);

    I2C_SendAddr(OV5640_I2C_CH, OV5640_WRITE, OV5640_TIMEOUT);

    I2C_SendData(OV5640_I2C_CH, (uint8_t *)&tmp, 2UL, OV5640_TIMEOUT);
    I2C_SendData(OV5640_I2C_CH, pTxBuf, len, OV5640_TIMEOUT);

    I2C_Stop(OV5640_I2C_CH, OV5640_TIMEOUT);
}

/**
 * @brief  Read register on Camera register.
 * @param  Reg: Register to be read
 */
void BSP_CAM_ReadReg(uint16_t reg, uint8_t *pRxBuf, uint32_t len)
{
    uint16_t tmp = 0U;
    tmp = ((reg & 0xFFU) << 8U) | ((reg & 0xFF00U) >> 8U);

    I2C_Start(OV5640_I2C_CH, OV5640_TIMEOUT);

    I2C_SendAddr(OV5640_I2C_CH, OV5640_WRITE, OV5640_TIMEOUT);

    I2C_SendData(OV5640_I2C_CH, (uint8_t*)&tmp, 2UL, OV5640_TIMEOUT);

    I2C_Restart(OV5640_I2C_CH, OV5640_TIMEOUT);

    I2C_SendAddr(OV5640_I2C_CH, OV5640_READ, OV5640_TIMEOUT);

    I2C_RcvData(OV5640_I2C_CH, pRxBuf, len, OV5640_TIMEOUT);

    I2C_Stop(OV5640_I2C_CH, OV5640_TIMEOUT);
}

/**
 * @brief  Reads data from LCD data register.
 * @retval Read data.
 */
uint16_t CAM_ReadData(void)
{
    return 0;
}

/**
 * @brief  CAM delay
 * @param  delay: Delay in ms
 * @retval None
 */
void CAM_Delay(uint32_t delay)
{
    DDL_DelayMS(delay);
}


void BSP_OV5640_Light_Ctrl(uint8_t OnOff)
{
    uint8_t reg_val;

    reg_val = 0x02U;
  	BSP_CAM_WriteReg(0x3016U, (uint8_t *)&reg_val, 1U);
	BSP_CAM_WriteReg(0x301CU, (uint8_t *)&reg_val, 1U);
	if (0U == OnOff)
    {
        reg_val = 0x00U;
    }
    BSP_CAM_WriteReg(0X3019, (uint8_t *)&reg_val, 1U);
}


void BSP_OV5640_Test_Pattern(uint8_t mode)
{
    uint8_t reg_val;
    switch (mode)
    {
        case 0:
          reg_val = 0x00;
          break;
        case 1:
          reg_val = 0x80;
          break;
        case 2:
          reg_val = 0x82;
          break;
        default:
          break;
    }
    BSP_CAM_WriteReg(0x503d, (uint8_t *)&reg_val, 1U);
}

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

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
