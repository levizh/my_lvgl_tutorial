/**
 *******************************************************************************
 * @file  swdt/swdt_interrupt_sw_startup/source/main.c
 * @brief Main program of SWDT Interrupt for the Device Driver Library.
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
 * @addtogroup SWDT_Interrupt
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
#define SW1_IN_WAKEUP                           (INTC_WUPEN_EIRQWUEN_7)

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
 * @brief  SWDT interrupt callback function.
 * @param  None
 * @retval None
 */
static void SWDT_IrqCallback(void)
{
    en_flag_status_t enFlagSta;

    enFlagSta = SWDT_GetStatus(SWDT_FLAG_UDF);
    /* SWDT underflow interrupt */
    if (Set == enFlagSta)
    {
        SWDT_ClearStatus(SWDT_FLAG_UDF);
        /* Normal mode */
        if (0U == u8ExIntCnt)
        {
            BSP_LED_Toggle(LED_RED);
        }
        /* Sleep mode */
        else if (1U == u8ExIntCnt)
        {
            BSP_LED_Toggle(LED_BLUE);
        }
        /* Stop mode */
        else
        {
            BSP_LED_Toggle(LED_RED);
            BSP_LED_Toggle(LED_BLUE);
        }
    }
    SWDT_ReloadCounter();
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
        if (u8ExIntCnt >= 3U)
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

    /* Enable stop mode wakeup */
    INTC_WakeupSrcCmd(SW1_IN_WAKEUP, Enable);
}

/**
 * @brief  SWDT configuration.
 * @param  None
 * @retval None
 */
static void SWDT_Config(void)
{
    uint8_t u8Ret;
    stc_swdt_init_t stcSwdtInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* SWDT configure */
    stcSwdtInit.u32CountCycle    = SWDT_COUNTER_CYCLE_256;
    stcSwdtInit.u32ClockDivision = SWDT_CLOCK_DIV32;
    stcSwdtInit.u32RefreshRange  = SWDT_RANGE_0TO100PCT;
    stcSwdtInit.u32LPModeCountEn = SWDT_LPW_MODE_COUNT_CONTINUE;
    stcSwdtInit.u32TrigType      = SWDT_TRIG_EVENT_INT;
    SWDT_Init(&stcSwdtInit);

    /* SWDT NVIC configure */
    stcIrqConfig.enIntSrc    = INT_SWDT_REFUDF;
    stcIrqConfig.enIRQn      = Int050_IRQn;
    stcIrqConfig.pfnCallback = &SWDT_IrqCallback;
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

    /* Enable stop mode wakeup */
    INTC_WakeupSrcCmd(INTC_WUPEN_SWDTWUEN, Enable);
}

/**
 * @brief  Main function of SWDT Interrupt.
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
    DDL_UartInit();
    /* SWDT configuration */
    SWDT_Config();
    /* SW1 configuration */
    SW1_Config();
    /* First reload counter to start SWDT */
    SWDT_ReloadCounter();

    while (1)
    {
        /* Sleep mode */
        if (1U == u8ExIntCnt)
        {
            PWC_EnterSleepMode();
        }
        /* Stop mode */
        else if (2U == u8ExIntCnt)
        {
            PWC_EnterStopMode();
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
