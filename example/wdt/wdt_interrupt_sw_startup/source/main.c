/**
 *******************************************************************************
 * @file  wdt/wdt_interrupt_sw_startup/source/main.c
 * @brief Main program of WDT Interrupt for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-03       Yangjp          First version
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
 * @addtogroup WDT_Interrupt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SW1 Port/Pin definition */
#define SW1_IN_PORT                             (GPIO_PORT_H)
#define SW1_IN_PIN                              (GPIO_PIN_07)
#define SW1_IN_EXINT_CH                         (EXINT_CH07)
#define SW1_IN_INT_SRC                          (INT_PORT_EIRQ7)
#define SW1_IN_IRQn                             (Int032_IRQn)

#define SW1_OUT_PORT                            (GPIO_PORT_A)
#define SW1_OUT_PIN                             (GPIO_PIN_06)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8ExIntCnt = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  WDT interrupt callback function.
 * @param  None
 * @retval None
 */
static void WDT_IrqCallback(void)
{
    en_flag_status_t enFlagSta;

    enFlagSta = WDT_GetStatus(WDT_FLAG_UDF);
    /* WDT underflow interrupt */
    if (Set == enFlagSta)
    {
        WDT_ClearStatus(WDT_FLAG_UDF);
        /* Normal mode */
        if (0U == u8ExIntCnt)
        {
            BSP_LED_Toggle(LED_RED);
        }
        /* Sleep mode */
        else
        {
            BSP_LED_Toggle(LED_BLUE);
        }
    }
    WDT_ReloadCounter();
}

/**
 * @brief  SW1 interrupt callback function.
 * @param  None
 * @retval None
 */
void SW1_IrqCallback(void)
{
    if (Set == EXINT_GetExIntSrc(SW1_IN_EXINT_CH))
    {
        u8ExIntCnt++;
        if (u8ExIntCnt >= 2U)
        {
            u8ExIntCnt = 0U;
        }
        BSP_LED_Off(LED_RED);
        BSP_LED_Off(LED_BLUE);
        EXINT_ClrExIntSrc(SW1_IN_EXINT_CH);
    }
}

/**
 * @brief  SW1 configuration.
 * @param  None
 * @retval None
 */
static void SW1_Config(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_RESET;
    GPIO_Init(SW1_OUT_PORT, SW1_OUT_PIN, &stcGpioInit);

    stcGpioInit.u16PinDir = PIN_DIR_IN;
    stcGpioInit.u16ExInt  = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(SW1_IN_PORT, SW1_IN_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh  = SW1_IN_EXINT_CH;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc    = SW1_IN_INT_SRC;
    stcIrqSignConfig.enIRQn      = SW1_IN_IRQn;
    stcIrqSignConfig.pfnCallback = &SW1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}

/**
 * @brief  WDT configuration.
 * @param  None
 * @retval None
 */
static void WDT_Config(void)
{
    uint8_t u8Ret;
    stc_wdt_init_t stcWdtInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* WDT configure */
    stcWdtInit.u32CountCycle    = WDT_COUNTER_CYCLE_65536;
    stcWdtInit.u32ClockDivision = WDT_CLOCK_DIV1024;
    stcWdtInit.u32RefreshRange  = WDT_RANGE_0TO100PCT;
    stcWdtInit.u32LPModeCountEn = WDT_LPW_MODE_COUNT_CONTINUE;
    stcWdtInit.u32TrigType      = WDT_TRIG_EVENT_INT;
    WDT_Init(&stcWdtInit);

    /* WDT NVIC configure */
    stcIrqConfig.enIntSrc    = INT_WDT_REFUDF;
    stcIrqConfig.enIRQn      = Int116_IRQn;
    stcIrqConfig.pfnCallback = &WDT_IrqCallback;
    u8Ret = INTC_IrqSignIn(&stcIrqConfig);
    if (Ok != u8Ret)
    {
        /* check parameter */
        while (1)
        {
        }
    }

    /* Clear pending */
    NVIC_ClearPendingIRQ(stcIrqConfig.enIRQn);
    /* Set priority */
    NVIC_SetPriority(stcIrqConfig.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    /* Enable NVIC */
    NVIC_EnableIRQ(stcIrqConfig.enIRQn);
}

/**
 * @brief  Main function of WDT Interrupt.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configure clock */
    BSP_CLK_Init();
    /* Configure BSP */
    BSP_LED_Init();
    /* Configure UART */
    DDL_PrintfInit();
    /* WDT configuration */
    WDT_Config();
    /* SW1 configuration */
    SW1_Config();
    /* First reload counter to start WDT */
    WDT_ReloadCounter();

    while (1)
    {
        /* Sleep mode */
        if (1U == u8ExIntCnt)
        {
            PWC_EnterSleepMode();
        }
        else
        {
            /* Reserved */
        }
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
