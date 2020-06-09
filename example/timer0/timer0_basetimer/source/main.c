/**
 *******************************************************************************
 * @file  timer0/timer0_basetimer/source/main.c
 * @brief Main program of TIMER0 for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-15       Heqb         First version
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
 * @addtogroup TMR0 Basetimer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TMR0 interrupt source and number define */
#define TMR0_IRQn                      (Int014_IRQn)
#define TMR0_SOURCE                    (INT_TMR0_1_CMPA)
/* EIRQ0 Port and Pin define */
#define KEY1_PORT                      (GPIO_PORT_A)
#define KEY1_PIN                       (GPIO_PIN_00)
#define KEY1_EXINT_CH                  (EXINT_CH00)

#define TMR0x                          (M4_TMR0_1)
#define TMR0_CH                        (TMR0_ChannelA)
/* TMR0 Clock source define*/
#define TMR0_CLKSRC_PCLK               (0U)
#define TMR0_CLKSRC_XTAL32             (1U)
#define TMR0_CLKSRC_LRC                (2U)
#define TMR0_CLKSRC                    (TMR0_CLKSRC_PCLK)

/* Period = 1 / (Clock / div) * (Compare Value - 1) 
   Period = 500ms */
#if (TMR0_CLKSRC == TMR0_CLKSRC_PCLK)
    #define TMR0_CLK_SRC               (TMR0_CLK_SRC_PCLK1)
    #define TMR0_CLK_DIV               (TMR0_CLK_DIV1024)
    #define TMR0_CMP_VAL               (3905U)

#elif (TMR0_CLKSRC == TMR0_CLKSRC_LRC)
    #define TMR0_CLK_SRC               (TMR0_CLK_SRC_LRC)
    #define TMR0_CLK_DIV               (TMR0_CLK_DIV16)
    #define TMR0_CMP_VAL               (1023U)

#elif (TMR0_CLKSRC == TMR0_CLKSRC_XTAL32)
    #define TMR0_CLK_SRC               (TMR0_CLK_SRC_XTAL32)
    #define TMR0_CLK_DIV               (TMR0_CLK_DIV16)
    #define TMR0_CMP_VAL               (1023U)
#endif
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void TMR0_Config(void);
static void EXINT_IRQ_Config(void);
static void LED_KEY_Config(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  TMR0_1 channelA compare IRQ callback
 * @param  None
 * @retval None
 */
static void TMR0_1_ChACmp_IrqCallback(void)
{
    BSP_LED_Toggle(LED_BLUE);
    GPIO_TogglePins(GPIO_PORT_A, GPIO_PIN_10);
    /* Clear the compare matching flag */
    TMR0_ClearStatus(TMR0x, TMR0_CH);
}

/**
 * @brief  Main function of example project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Enable AOS function */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_AOS, Enable);
    /* Configure LED & Key */
    LED_KEY_Config();
    GPIO_OE(GPIO_PORT_A, GPIO_PIN_10, Enable);
    /*Configure EXINT and IRQ handler && NVIC*/
    EXINT_IRQ_Config();
    /*Configure TMR0*/
    TMR0_Config();
    /* Timer0 ch1 start counting */
    TMR0_Cmd(TMR0x, TMR0_CH, Enable);

    while(1)
    {

    };
}

/**
 * @brief  Configure TMR0.
 * @param  None
 * @retval None
 */
static void TMR0_Config(void)
{
    stc_tmr0_init_t stcTmr0Init;

    /* Enable timer0 peripheral clock */
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR0_1, Enable);

    /* TIMER0 basetimer function initialize */
    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDivision = TMR0_CLK_DIV;        /* Config clock division */
    stcTmr0Init.u32ClockSource = TMR0_CLK_SRC;          /* Chose clock source */
    stcTmr0Init.u32Tmr0Func = TMR0_FUNC_CMP;            /* Timer0 compare mode */
    stcTmr0Init.u32HwTrigFunc = TMR0_BT_HWTRG_FUNC_STOP;/* Config Hardware trigger function */
    stcTmr0Init.u16CmpValue = TMR0_CMP_VAL;             /* Set compara register data */
    TMR0_Init(TMR0x, TMR0_CH, &stcTmr0Init);

    /* Timer0 interrupt function Enable */
    TMR0_IntCmd(TMR0x, TMR0_CH, Enable);
    /* Set internal hardware capture source */
    TMR0_SetTriggerSrc(EVT_PORT_EIRQ0);

}

/**
 * @brief  Configure EXINT and IRQ handler && NVIC.
 * @param  None
 * @retval None
 */
static void EXINT_IRQ_Config(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY1_PORT, KEY1_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY1_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* Register IRQ handler && configure NVIC. */
    stcIrqSignConfig.enIRQn = TMR0_IRQn;
    stcIrqSignConfig.enIntSrc = TMR0_SOURCE;
    stcIrqSignConfig.pfnCallback = &TMR0_1_ChACmp_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIORITY_15);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}

/**
 * @brief  Configure LED and Key.
 * @param  None
 * @retval None
 */
static void LED_KEY_Config(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_keyscan_init_t stcKeyscanInit;

    BSP_IO_Init();
    BSP_LED_Init();
    GPIO_StructInit(&stcGpioInit);
    KEYSCAN_StructInit(&stcKeyscanInit);

    GPIO_Init(BSP_KEYOUT1_PORT, BSP_KEYOUT1_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_KEYOUT0_PORT, BSP_KEYOUT0_PIN, GPIO_FUNC_8_KEYSCAN, Disable);

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_KEY, Enable);

    stcKeyscanInit.u32HizCycle = KEYSCAN_HIZ_CLC_4;
    stcKeyscanInit.u32LowCycle = KEYSCAN_LOW_CLC_128K;
    stcKeyscanInit.u32KeyClk   = KEYSCAN_CLK_HCLK;
    stcKeyscanInit.u32Keyout   = KEYSCAN_OUT_0T1;
    stcKeyscanInit.u32Keyin    = KEYSCAN_IN_0;

    KEYSCAN_Init(&stcKeyscanInit);

    KEYSCAN_Cmd(Enable);
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
