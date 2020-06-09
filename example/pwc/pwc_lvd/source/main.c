/**
 *******************************************************************************
 * @file  pwc/pwc_lvd/source/main.c
 * @brief Main program of PWC for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-10       Zhangxl         First version
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup PWC_Lvd
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define LVD1_INT_SRC    (INT_PVD_PVD1)
#define LVD1_IRQn       (Int003_IRQn)

#define LVD2_INT_SRC    (INT_PVD_PVD2)
#define LVD2_IRQn       (Int002_IRQn)

#define DLY_MS          (500UL)
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
 * @brief  LVD1 IRQ callback function
 * @param  None
 * @retval None
 */
void PWC_LVD1_IrqCallback(void)
{
    uint8_t u8Cnt = 10U;
    do
    {
        BSP_LED_Toggle(LED_RED);
        DDL_Delay1ms(DLY_MS);
    } while(--u8Cnt);

    PWC_LVD_ClrFlag();
}

/**
 * @brief  LVD2 IRQ callback function
 * @param  None
 * @retval None
 */
void PWC_LVD2_IrqCallback(void)
{
    uint8_t u8Cnt = 10U;
    do
    {
        BSP_LED_Toggle(LED_BLUE);
        DDL_Delay1ms(DLY_MS);
    } while(--u8Cnt);

    PWC_LVD_ClrFlag();
}

void LVD_IntInit(void)
{
    stc_irq_signin_config_t stcIrqSignConfig;

    /* Clear LVD flag */
    PWC_LVD_ClrFlag();

    /* Set LVD interrupt. */
    INTC_ShareIrqCmd(INT_PVD_PVD1, Enable);

    /* LVD1 IRQ sign-in */
    stcIrqSignConfig.enIntSrc = LVD1_INT_SRC;
    stcIrqSignConfig.enIRQn   = LVD1_IRQn;
    stcIrqSignConfig.pfnCallback = &PWC_LVD1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* LVD2 IRQ sign-in */
    stcIrqSignConfig.enIntSrc = LVD2_INT_SRC;
    stcIrqSignConfig.enIRQn   = LVD2_IRQn;
    stcIrqSignConfig.pfnCallback = &PWC_LVD2_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* Enable interrupt. */
    NVIC_ClearPendingIRQ(LVD1_IRQn);
    NVIC_SetPriority(LVD1_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(LVD1_IRQn);

    /* Enable interrupt. */
    NVIC_ClearPendingIRQ(LVD2_IRQn);
    NVIC_SetPriority(LVD2_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(LVD2_IRQn);
}

en_result_t LVD_Init(void)
{
    en_result_t enRet;
    stc_pwc_lvd_config_t  stcPwcLvdConfig;
    
    PWC_LVD_StructInit(&stcPwcLvdConfig);
    /* Config LVD */
    /* LVD1: 2.8V */
    stcPwcLvdConfig.u8LvdVoltage  = PWC_LVD1_2V8_LVD2_2V9;
    stcPwcLvdConfig.u8LvdCmpOutEn = PWC_LVD_CMP_ON;
    stcPwcLvdConfig.u8LvdEn       = PWC_LVD_ON;
    stcPwcLvdConfig.u8LvdIntRstEn = PWC_LVD_IR_ON;
    stcPwcLvdConfig.u8LvdIntRstSel= PWC_LVD_INT;
    stcPwcLvdConfig.u8LvdNmiEn    = PWC_LVD_INT_MASK;
    stcPwcLvdConfig.u8FilterEn    = PWC_LVD_DF_OFF;
    stcPwcLvdConfig.u8FilterClk   = PWC_LVD_DFS_DIV1;
    enRet = PWC_LVD_Init(PWC_LVD_CH1, &stcPwcLvdConfig);
    if (Ok == enRet)
    {
        /* LVD2: 2.3V */
        stcPwcLvdConfig.u8LvdVoltage  = PWC_LVD1_2V1_LVD2_2V3;
        enRet = PWC_LVD_Init(PWC_LVD_CH2, &stcPwcLvdConfig);
    }
    return enRet;
}

/**
 * @brief  Main function of LVD project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* unlock GPIO register in advance */
    GPIO_Unlock();
    
    BSP_IO_Init();
    BSP_LED_Init();

    LVD_Init();

    LVD_IntInit();

    while(1)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
