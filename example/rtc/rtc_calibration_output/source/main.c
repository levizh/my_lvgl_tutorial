/**
 *******************************************************************************
 * @file  rtc/rtc_calibration_output/source/main.c
 * @brief Main program of RTC Calibration Output for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-02       Yangjp          First version
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
 * @addtogroup RTC_Calibration_Output
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* RTC 1Hz output Port/Pin definition */
#define RTC_ONEHZ_OUTPUT_PORT                   (GPIO_PORT_B)
#define RTC_ONEHZ_OUTPUT_PIN                    (GPIO_PIN_15)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8SecIntFlag = 0U;
static int16_t u16CompenVal = 0x20;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  RTC period interrupt callback function.
 * @param  None
 * @retval None
 */
static void RTC_Period_IrqCallback(void)
{
    u8SecIntFlag = 1U;
    RTC_ClearStatus(RTC_FLAG_PRDF);
}

/**
 * @brief  RTC configuration.
 * @param  None
 * @retval None
 */
static void RTC_Config(void)
{
    uint8_t u8Ret;
    stc_rtc_init_t stcRtcInit;
    stc_irq_signin_config_t stcIrqConfig;

    /* Configuration RTC output pin */
    GPIO_SetFunc(RTC_ONEHZ_OUTPUT_PORT, RTC_ONEHZ_OUTPUT_PIN, GPIO_FUNC_1_RTCOUT, PIN_SUBFUNC_DISABLE);

    /* Reset RTC counter */
    if (ErrorTimeout == RTC_DeInit())
    {
        printf("Reset RTC failed!\r\n");
    }
    else
    {
        /* Configure structure initialization */
        RTC_StructInit(&stcRtcInit);

        /* Configuration RTC structure */
        stcRtcInit.u8ClockSource     = RTC_CLOCK_SOURCE_XTAL32;
        stcRtcInit.u8HourFormat      = RTC_HOUR_FORMAT_24;
        stcRtcInit.u8PeriodInterrupt = RTC_PERIOD_INT_ONE_SECOND;
        stcRtcInit.u8ClkCompenEn     = RTC_CLOCK_COMPEN_ENABLE;
        stcRtcInit.u16ClkCompenValue = (uint16_t)u16CompenVal;
        stcRtcInit.u8CompenMode      = RTC_OUTPUT_COMPEN_MODE_UNIFORM;
        RTC_Init(&stcRtcInit);

        /* RTC period interrupt configure */
        stcIrqConfig.enIntSrc    = INT_RTC_PRD;
        stcIrqConfig.enIRQn      = Int052_IRQn;
        stcIrqConfig.pfnCallback = &RTC_Period_IrqCallback;
        INTC_IrqSignOut(stcIrqConfig.enIRQn);
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

        /* Enable 1HZ output */
        RTC_OneHzOutputCmd(Enable);
        /* Enable period interrupt */
        RTC_IntCmd(RTC_INT_PRDIE, Enable);
        /* Startup RTC count */
        RTC_Cmd(Enable);
    }
}

/**
 * @brief  XTAL32 clock initialize.
 * @param  None
 * @retval None
 */
static void XTAL32_ClkInit(void)
{
    stc_clk_xtal32_init_t stcXtal32Init;

    /* Xtal32 config */
    stcXtal32Init.u8Xtal32State = CLK_XTAL32_ON;
    stcXtal32Init.u8Xtal32Drv   = CLK_XTAL32DRV_HIGH;
    stcXtal32Init.u8Xtal32NF    = CLK_XTAL32NF_PART;
    CLK_Xtal32Init(&stcXtal32Init);
    /* Waiting for XTAL32 stabilization */
    DDL_Delay1ms(1000U);
}

/**
 * @brief  Main function of RTC calibration output.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configure clock */
    BSP_CLK_Init();
    XTAL32_ClkInit();
    /* Configure BSP */
    BSP_IO_Init();
    BSP_LED_Init();
    BSP_KEY_Init();
    /* Configure UART */
    DDL_PrintfInit();
    /* Configure RTC */
    RTC_Config();

    while (1)
    {
        /* SW1 */
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1))
        {
            while (Set == BSP_KEY_GetStatus(BSP_KEY_1));
            if (u16CompenVal < 255)
            {
                u16CompenVal++;
            }
            RTC_SetClkCompenValue((uint16_t)u16CompenVal & 0x1FFU);
        }
        /* SW2 */
        if (Set == BSP_KEY_GetStatus(BSP_KEY_2))
        {
            while (Set == BSP_KEY_GetStatus(BSP_KEY_2));
            if (u16CompenVal > -256)
            {
                u16CompenVal--;
            }
            RTC_SetClkCompenValue((uint16_t)u16CompenVal & 0x1FFU);
        }

        if (1u == u8SecIntFlag)
        {
            u8SecIntFlag = 0U;
            BSP_LED_Toggle(LED_RED);
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
