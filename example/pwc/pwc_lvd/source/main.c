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
#define LVD_IRQn        (Int142_IRQn)

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
 * @brief  LVD1 IRQ handler
 * @param  None
 * @retval None
 */
void PWC_Lvd1_IrqHandler(void)
{
    uint8_t u8Cnt = 10U;
    PWC_LVD_ClrFlag(PWC_PVDDSR_PVD1DETFLG);

    do
    {
        BSP_LED_Toggle(LED_RED);
        DDL_Delay1ms(DLY_MS);
    } while(--u8Cnt);
    PWC_LVD_ClrFlag(PWC_PVDDSR_PVD1DETFLG);
}

/**
 * @brief  LVD2 IRQ handler
 * @param  None
 * @retval None
 */
void PWC_Lvd2_IrqHandler(void)
{
    uint8_t u8Cnt = 10U;
    PWC_LVD_ClrFlag(PWC_PVDDSR_PVD2DETFLG);

    do
    {
        BSP_LED_Toggle(LED_BLUE);
        DDL_Delay1ms(DLY_MS);
    } while(--u8Cnt);
}

/**
 * @brief  Main function of LVD project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_pwc_lvd_config_t  stcPwcLvdConfig;

    BSP_IO_Init();
    BSP_LED_Init();

    PWC_LVD_StructInit(&stcPwcLvdConfig);
    /* Config LVD */
    /* LVD1: 2.8V; LVD2: 2.3V */
    stcPwcLvdConfig.u8LvdVoltage  = PWC_LVD1_2V8 | PWC_LVD2_2V3;
    stcPwcLvdConfig.u8LvdCmpOutEn = PWC_LVD1_CMP_ON | PWC_LVD2_CMP_ON;
    stcPwcLvdConfig.u8LvdEn       = PWC_LVD1_ON | PWC_LVD2_ON;
    stcPwcLvdConfig.u8LvdIntRstEn = PWC_LVD1_IR_ON | PWC_LVD2_IR_ON;
    stcPwcLvdConfig.u8LvdIntRstSel= PWC_LVD1_INT | PWC_LVD2_INT;
    stcPwcLvdConfig.u8LvdNmiEn    = PWC_LVD1_INT_MASK | PWC_LVD2_INT_MASK;
    PWC_LVD_Init(&stcPwcLvdConfig);

    /* Set LVD interrupt. */
    INTC_ShareIrqCmd(INT_PVD_PVD1, Enable);
    INTC_ShareIrqCmd(INT_PVD_PVD2, Enable);

    /* Enable interrupt. */
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_SetPriority(LVD_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(LVD_IRQn);

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
