/**
 *******************************************************************************
 * @file  pwc/pwc_stop_wake/source/main.c
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
#define KEY10_EXINT_CH  (EXINT_CH08)
#define KEY10_INT_SRC   (INT_PORT_EIRQ8)
#define KEY10_IRQn      (Int000_IRQn)

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
uint8_t u8Cnt = 10U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  KEY10 External interrupt Ch.8 callback function
 *         IRQ No.0 in Global IRQ entry No.0~31 is used for EXINT8
 * @param  None
 * @retval None
 */
void EXINT_KEY10_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY10_EXINT_CH))
   {
        BSP_IO_Init();
        BSP_LED_Init();
        BSP_LED_Off(LED_RED);

        while (Pin_Reset == GPIO_ReadInputPortPin(KEY10_PORT, KEY10_PIN))
        {
        }
        EXINT_ClrExIntSrc(KEY10_EXINT_CH);
   }
}

/**
 * @brief  KEY10 Init
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
    stcExintInit.u32ExIntFAE = EXINT_FILTER_A_ON;
    stcExintInit.u32ExIntFAClk = EXINT_FACLK_HCLK_DIV8;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
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

/**
 * @brief  Whether ready to entry stop mode.
 * @param  None
 * @retval None
 * @note Ensure DMA stops transmit and no flash erase/program operation.
 */
en_result_t STOP_IsReady(void)
{
    en_result_t enRet = Ok;
    uint8_t tmp1 = 0x00U, tmp2 = 0x00U, tmp3 = 0x00U;

    tmp1 = ((READ_REG32(M4_EFM->FSR) & (EFM_FSR_RDY0 | EFM_FSR_RDY1)) ==        \
            (EFM_FSR_RDY0 | EFM_FSR_RDY1));

    tmp2 = ((READ_REG32(M4_DMA1->CHSTAT) & DMA_CHSTAT_DMAACT) == 0x00U);
    tmp3 = ((READ_REG32(M4_DMA1->CHSTAT) & DMA_CHSTAT_DMAACT) == 0x00U);

    if (0U == (tmp1 & tmp2 & tmp3))
    {
        enRet = ErrorNotReady;
    }
    return enRet;
}

/**
 * @brief  MCU behavior config for stop mode.
 * @param  None
 * @retval None
 */
void STOP_Config(void)
{
    stc_pwc_stop_mode_config stcStopConfig;

    PWC_StopStructInit(&stcStopConfig);

    stcStopConfig.u8StopDrv = PWC_STOP_DRV_HIGH;
    stcStopConfig.u16ExBusHold = PWC_STOP_EXBUS_HIZ;
    stcStopConfig.u16ClkKeep = PWC_STOP_CLK_KEEP;
    stcStopConfig.u16FlashWait = PWC_STOP_FLASH_WAIT;

    PWC_StopConfig(&stcStopConfig);

    /* Wake-up source config (EXINT Ch.8 here) */
    INTC_WakeupSrcCmd(INTC_WUPEN_EIRQWUEN_8, Enable);

}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    BSP_CLK_Init();
    BSP_IO_Init();
    BSP_LED_Init();

    STOP_Config();

    /* KEY10 */
    while(Pin_Reset != GPIO_ReadInputPortPin(KEY10_PORT, KEY10_PIN))
    {
        ;
    }
    DDL_Delay1ms(DLY_MS);
    Key10_Init();

    while(1)
    {
        u8Cnt = 10U;
        do
        {
            BSP_LED_Toggle(LED_BLUE);
            DDL_Delay1ms(DLY_MS);
        } while(--u8Cnt);

        if (Ok == STOP_IsReady())
        {
            BSP_LED_On(LED_RED);
            PWC_EnterStopMode();
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