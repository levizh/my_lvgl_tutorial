/**
 *******************************************************************************
 * @file  exint/exint_key/source/main.c
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
#define GLOBAL_IRQ      (1U)
#define GROUP_IRQ       (0U)
#define SHARE_IRQ       (0U)

#if (1U < (GLOBAL_IRQ + GROUP_IRQ + SHARE_IRQ))
#error "Please don't enable more than one IRQ type."
#elif (0U == (GLOBAL_IRQ + GROUP_IRQ + SHARE_IRQ))
#error "Please select one IRQ category."
#endif

#define KEY10_PORT      (GPIO_PORT_A)
#define KEY10_PIN       (GPIO_PIN_00)
#define KEY10_EXINT_CH  (EXINT_CH00)
#define KEY10_INT_SRC   (INT_PORT_EIRQ0)
#define KEY10_IRQn      (Int001_IRQn)
#define KEY10_GroupIRQn (Int033_IRQn)
#define KEY10_ShareIRQn (Int128_IRQn)

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
#if (GLOBAL_IRQ == 1U)
/**
 * @brief  KEY10 External interrupt Ch.0 callback function
 *         IRQ No.0 in Global IRQ entry No.0~31 is used for EXINT0
 * @param  None
 * @retval None
 */
void EXINT_KEY10_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY10_EXINT_CH))
   {
        BSP_LED_Toggle(LED_BLUE);
        while (Pin_Reset == GPIO_ReadInputPins(KEY10_PORT, KEY10_PIN))
        {
            ;
        }
        EXINT_ClrExIntSrc(KEY10_EXINT_CH);
   }
}

/**
 * @brief  KEY10 initialize
 * @param  None
 * @retval None
 */
void Key10_Init(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY10_PORT, KEY10_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY10_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc = KEY10_INT_SRC;
    stcIrqSignConfig.enIRQn   = KEY10_IRQn;
    stcIrqSignConfig.pfnCallback = &EXINT_KEY10_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY10_IRQn);
    NVIC_SetPriority(KEY10_IRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY10_IRQn);
}

#elif (GROUP_IRQ == 1U)
/**
 * @brief  KEY10 External interrupt Ch.0 callback function
 *         IRQ No.33 in Group IRQ entry No.32~37 is used for EXINT0
 * @param  None
 * @retval None
 */
void EXINT_KEY10_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY10_EXINT_CH))
   {
        BSP_LED_Toggle(LED_RED);
        while (Pin_Reset == GPIO_ReadInputPins(KEY10_PORT, KEY10_PIN))
        {
            ;
        }
        EXINT_ClrExIntSrc(KEY10_EXINT_CH);
   }
}

/**
 * @brief  KEY10 initialize
 * @param  None
 * @retval None
 */
void Key10_Init(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY10_PORT, KEY10_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY10_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc = KEY10_INT_SRC;
    stcIrqSignConfig.enIRQn   = KEY10_GroupIRQn;
    stcIrqSignConfig.pfnCallback = &EXINT_KEY10_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY10_GroupIRQn);
    NVIC_SetPriority(KEY10_GroupIRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY10_GroupIRQn);
}

#elif (SHARE_IRQ == 1U)
/**
  * @brief  KEY10 External interrupt Ch.0 ISR
  *         Share IRQ entry No.128 is used for EXINT0
  * @param  None
  * @retval None
  */
 void EXTINT_00_IrqHandler(void)
 {
    if (Set == EXINT_GetExIntSrc(KEY10_EXINT_CH))
    {
         BSP_LED_Toggle(LED_YELLOW);
         while (Pin_Reset == GPIO_ReadInputPins(KEY10_PORT, KEY10_PIN))
         {
             ;
         }
         EXINT_ClrExIntSrc(KEY10_EXINT_CH);
    }
 }

/**
 * @brief  KEY10 initialize
 * @param  None
 * @retval None
 */
void Key10_Init(void)
{
    stc_exint_init_t stcExintInit;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(KEY10_PORT, KEY10_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh = KEY10_EXINT_CH;
    stcExintInit.u32ExIntLvl= EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    INTC_ShareIrqCmd(KEY10_INT_SRC, Enable);

    /* NVIC config */
    NVIC_ClearPendingIRQ(KEY10_ShareIRQn);
    NVIC_SetPriority(KEY10_ShareIRQn,DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(KEY10_ShareIRQn);
}
#endif

/**
 * @brief  Main function of EXINT project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* unlock GPIO register in advance */
    GPIO_Unlock();
    
    BSP_IO_Init();
    BSP_LED_Init();

    Key10_Init();

    while (1)
    {
        ;// wait KEY10 key pressed
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
