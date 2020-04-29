/**
 *******************************************************************************
 * @file  exint/source/main.c
 * @brief Main program EXINT for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-03       Zhangxl         First version
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
 * @addtogroup EXINT
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define KEY1_PORT       (GPIO_PORT_A)
#define KEY1_PIN        (GPIO_PIN_00)
#define KEY1_EXINT_CH   (EXINT_CH00)
#define KEY1_INT_SRC    (INT_PORT_EIRQ0)
#define KEY1_IRQn       (Int000_IRQn)

#define KEY4_PORT       (GPIO_PORT_I)
#define KEY4_PIN        (GPIO_PIN_03)
#define KEY4_EXINT_CH   (EXINT_CH03)
#define KEY4_INT_SRC    (INT_PORT_EIRQ3)
#define KEY4_IRQn       (Int033_IRQn)

#define KEY7_PORT       (GPIO_PORT_H)
#define KEY7_PIN        (GPIO_PIN_07)
#define KEY7_EXINT_CH   (EXINT_CH07)
#define KEY7_INT_SRC    (INT_PORT_EIRQ7)
#define KEY7_IRQn       (Int128_IRQn)

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
 * @brief  KEY1 External interrupt Ch.0 callback function
 *         IRQ No.0 in Global IRQ entry No.0~31 is used for EXINT0
 * @param  None
 * @retval None
 */
void EXINT_KEY1_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY1_EXINT_CH))
   {
        BSP_LED_Toggle(LED_BLUE);
        while (Pin_Reset == GPIO_ReadInputPortPin(KEY1_PORT, KEY1_PIN))
        {
            ;
        }
        EXINT_ClrExIntSrc(KEY1_EXINT_CH);
   }
}

/**
 * @brief  KEY4 External interrupt Ch.3 callback function
 *         IRQ No.33 in Group IRQ entry No.32~37 is used for EXINT3
 * @param  None
 * @retval None
 */
void EXINT_KEY4_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY4_EXINT_CH))
   {
        BSP_LED_Toggle(LED_RED);
        while (Pin_Reset == GPIO_ReadInputPortPin(KEY4_PORT, KEY4_PIN))
        {
            ;
        }
        EXINT_ClrExIntSrc(KEY4_EXINT_CH);
   }
}

/**
 * @brief  KEY7 External interrupt Ch.7 ISR
 *         Share IRQ entry No.128 is used for EXINT7
 * @param  None
 * @retval None
 */
void EXTINT_07_IrqHandler(void)
{
   if (Set == EXINT_GetExIntSrc(KEY7_EXINT_CH))
   {
        BSP_LED_Toggle(LED_RED | LED_BLUE);
        while (Pin_Reset == GPIO_ReadInputPortPin(KEY7_PORT, KEY7_PIN))
        {
            ;
        }
        EXINT_ClrExIntSrc(KEY7_EXINT_CH);
   }
}

/**
 * @brief  Trigger initialize for KEY detect.
 * @param  None
 * @retval None
 */
void KeyTrig_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_keyscan_init_t stcKeyscanInit;

    GPIO_StructInit(&stcGpioInit);
    KEYSCAN_StructInit(&stcKeyscanInit);

//    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(BSP_KEYOUT0_PORT, BSP_KEYOUT0_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_KEYOUT0_PORT, BSP_KEYOUT0_PIN, GPIO_FUNC_8_KEYSCAN, Disable);

    GPIO_Init(BSP_KEYOUT1_PORT, BSP_KEYOUT1_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_KEYOUT1_PORT, BSP_KEYOUT1_PIN, GPIO_FUNC_8_KEYSCAN, Disable);

    GPIO_Init(BSP_KEYOUT2_PORT, BSP_KEYOUT2_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_KEYOUT2_PORT, BSP_KEYOUT2_PIN, GPIO_FUNC_8_KEYSCAN, Disable);

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_KEY, Enable);

    stcKeyscanInit.u32HizCycle = KEYSCAN_HIZ_CLC_4;
    stcKeyscanInit.u32LowCycle = KEYSCAN_LOW_CLC_128K;
    stcKeyscanInit.u32KeyClk   = KEYSCAN_CLK_HCLK;
    stcKeyscanInit.u32Keyout   = KEYSCAN_OUT_0T1;
    stcKeyscanInit.u32Keyin    = (KEYSCAN_IN_0 | KEYSCAN_IN_3 | KEYSCAN_IN_7);

    KEYSCAN_Init(&stcKeyscanInit);

    KEYSCAN_Cmd(Enable);
}

/**
 * @brief  KEY1 initialize
 * @param  None
 * @retval None
 */
void Key1_Init(void)
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

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc = KEY1_INT_SRC;
    stcIrqSignConfig.enIRQn   = KEY1_IRQn;
    stcIrqSignConfig.pfnCallback = &EXINT_KEY1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY1_IRQn);
    NVIC_SetPriority(KEY1_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY1_IRQn);
}

/**
 * @brief  KEY4 initialize
 * @param  None
 * @retval None
 */
void Key4_Init(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY4_PORT, KEY4_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY4_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc = KEY4_INT_SRC;
    stcIrqSignConfig.enIRQn   = KEY4_IRQn;
    stcIrqSignConfig.pfnCallback = &EXINT_KEY4_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY4_IRQn);
    NVIC_SetPriority(KEY4_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY4_IRQn);
}

/**
 * @brief  KEY7 initialize
 * @param  None
 * @retval None
 */
void Key7_Init(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY7_PORT, KEY7_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY7_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    INTC_ShareIrqCmd(KEY7_INT_SRC, Enable);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY7_IRQn);
    NVIC_SetPriority(KEY7_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY7_IRQn);
}


/**
 * @brief  Main function of EXINT project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    BSP_IO_Init();
    BSP_LED_Init();

    /* KEYOUT0 generates Negetive-pulse as the EXINT trigger */
    KeyTrig_Init();

    Key1_Init();
    Key4_Init();
    Key7_Init();

    while (1)
    {
        ;// wait KEY1/4/7 key pressed
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
