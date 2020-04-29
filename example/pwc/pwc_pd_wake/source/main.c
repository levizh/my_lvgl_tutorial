/**
 *******************************************************************************
 * @file  pwc/pwc_pd_wake/source/main.c
 * @brief Main program of PWC for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-13       Zhangxl         First version
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
 * @addtogroup PWC_Stop_wake
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define KEY10_PORT      (GPIO_PORT_I)
#define KEY10_PIN       (GPIO_PIN_08)

#define WKTM_IRQn       (Int131_IRQn)

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
 * @brief  Wakeup timer IRQ handler
 * @param  None
 * @retval None
 */
void PWC_WakeupTimer_IrqHandler(void)
{
    if (Set == PWC_WKT_GetFlag())
    {
        PWC_WKT_ClearFlag();
    }
}

/**
 * @brief  Power down mode behavior config.
 * @param  None
 * @retval None
 */
void PowerDownModeConfig(void)
{
    stc_pwc_pd_mode_config_t stcPDModeConfig;

    PWC_PowerDownStructInit(&stcPDModeConfig);

    stcPDModeConfig.u8IOState = PWC_PD_IO_STATE1;
    stcPDModeConfig.u8PDMode = PWC_PD_MODE3;
    stcPDModeConfig.u8WkUpSpeed = PWC_PD_WKUP_SLOW;

    PWC_PowerDownConfig(&stcPDModeConfig);

    /* Wake up by WKTM */
    PWC_PdWakeup2Cmd(PWC_PDWKE2_WKTMWKE, Enable);

    /* Disable WKTM inadvance */
    PWC_WKT_Cmd(Disable);
    /* RTCLRC for WKTM */
    CLK_RtcLrcCmd(Enable);
    /* WKTM init */
    PWC_WKT_Init(PWC_WKT_CLK_SRC_RTCLRC, 0xFFFU);

    /* Wakeup timer NVIC config, not mandatory for this sample */
    INTC_ShareIrqCmd(INT_WKTM_PRD, Enable);
    NVIC_ClearPendingIRQ(WKTM_IRQn);
    NVIC_SetPriority(WKTM_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(WKTM_IRQn);

}

/**
 * @brief  Reset cause info. print.
 * @param  None
 * @retval None
 */
void ResetCausePrint(void)
{
    stc_rmu_rstcause_t stcRst;

    RMU_GetStatus(&stcRst);

    if (Set == stcRst.enRstPinRst)
    {
        printf("Pin reset occurs.\n");
    }
    if (Set == stcRst.enPowerDownRst)
    {
        printf("Power down mode reset occurs.\n");
    }
    RMU_ClrStatus();
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8Cnt = 0U;
    
    BSP_CLK_Init();
    BSP_IO_Init();
    BSP_LED_Init();

    DDL_PrintfInit();

    PowerDownModeConfig();

    ResetCausePrint();

    /* KEY10 */
    while(Pin_Reset != GPIO_ReadInputPortPin(KEY10_PORT, KEY10_PIN))
    {
        ;
    }

    while(1)
    {
        u8Cnt = 2U;
        do
        {
            BSP_LED_Toggle(LED_BLUE);
            DDL_Delay1ms(DLY_MS);
        } while(--u8Cnt);
        PWC_WKT_Cmd(Enable);
        PWC_EnterPowerDownMode();
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
