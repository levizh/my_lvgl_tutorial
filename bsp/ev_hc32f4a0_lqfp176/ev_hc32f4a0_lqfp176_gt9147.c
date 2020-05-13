/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_gt9147.c
 * @brief This file provides firmware functions for touch panel drvier IC GT9147.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f4a0_lqfp176_gt9147.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/** @defgroup EV_HC32F4A0_LQFP176_GT9147 HC32F4A0 EVB GT9147
  * @{
  */

#if (BSP_GT9147_ENABLE == BSP_ON)

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
 * @defgroup EV_HC32F4A0_LQFP176_GT9147_Global_Functions HC32F4A0 LQFP176 EVB GT9147 Global Functions
 * @{
 */

void BSP_TS_Init(void)
{
    uint8_t tmp[10];
    I2C_Start(GT9147_I2C_CH, GT9147_TIMEOUT);

    I2C_SendAddr(GT9147_I2C_CH, GT9147_WRITE, GT9147_TIMEOUT);

    tmp[0] = 0x81;
    tmp[1] = 0x40;
    I2C_SendData(GT9147_I2C_CH, &tmp[0], 2UL, GT9147_TIMEOUT);
    //I2Cx_SendData(GT9147_I2C_CH, 0X40, 1UL, GT9147_TIMEOUT);

    I2C_Restart(GT9147_I2C_CH, GT9147_TIMEOUT);

    I2C_SendAddr(GT9147_I2C_CH, GT9147_READ, GT9147_TIMEOUT);
    I2C_RcvData(GT9147_I2C_CH, &tmp[0], 4UL, GT9147_TIMEOUT);

    I2C_Stop(GT9147_I2C_CH, TCA9539_TIMEOUT);
}

void BSP_TS_ReadReg(uint16_t reg, uint8_t *pRxBuf, uint32_t len)
{
    uint16_t tmp = 0U;
    tmp = ((reg & 0xFFU) << 8U) | ((reg & 0xFF00U) >> 8U);

    I2C_Start(GT9147_I2C_CH, GT9147_TIMEOUT);

    I2C_SendAddr(GT9147_I2C_CH, GT9147_WRITE, GT9147_TIMEOUT);

    //tmp[0] = 0x81;
    //tmp[1] = 0x40;
    I2C_SendData(GT9147_I2C_CH, (uint8_t*)&tmp, 2UL, GT9147_TIMEOUT);
    //I2Cx_SendData(GT9147_I2C_CH, 0X40, 1UL, GT9147_TIMEOUT);

    I2C_Restart(GT9147_I2C_CH, GT9147_TIMEOUT);

    I2C_SendAddr(GT9147_I2C_CH, GT9147_READ, GT9147_TIMEOUT);

    I2C_RcvData(GT9147_I2C_CH, pRxBuf, len, GT9147_TIMEOUT);

    I2C_Stop(GT9147_I2C_CH, GT9147_TIMEOUT);
}

void BSP_TS_WriteReg(uint16_t reg, uint8_t *pTxBuf, uint32_t len)
{
    uint16_t tmp = 0U;
    tmp = ((reg & 0xFFU) << 8U) | ((reg & 0xFF00U) >> 8U);

    I2C_Start(GT9147_I2C_CH, GT9147_TIMEOUT);

    I2C_SendAddr(GT9147_I2C_CH, GT9147_WRITE, GT9147_TIMEOUT);

    I2C_SendData(GT9147_I2C_CH, (uint8_t*)&tmp, 2UL, GT9147_TIMEOUT);
    I2C_SendData(GT9147_I2C_CH, pTxBuf, len, GT9147_TIMEOUT);

    I2C_Stop(GT9147_I2C_CH, TCA9539_TIMEOUT);
}

//uint8_t BSP_TS_GetXY()
//{
//    uint8_t tmp = 0U;
//    if (BSP_TS_DetectTouch())
//    {
//
//    }
//    else
//    {
//        return 1U;
//    }
//
//}


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

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
