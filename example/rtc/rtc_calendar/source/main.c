/**
 *******************************************************************************
 * @file  rtc/rtc_calendar/source/main.c
 * @brief Main program of RTC Calendar for the Device Driver Library.
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
 * @addtogroup RTC_Calendar
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @brief  RTC calendar configuration.
 * @param  None
 * @retval None
 */
static void RTC_CalendarConfig(void)
{
    stc_rtc_date_t stcRtcDate;
    stc_rtc_time_t stcRtcTime;

    /* Date configuration */
    stcRtcDate.u8Year    = 20U;
    stcRtcDate.u8Month   = RTC_MONTH_JANUARY;
    stcRtcDate.u8Day     = 1U;
    stcRtcDate.u8Weekday = RTC_WEEKDAY_WEDNESDAY;

    /* Time configuration */
    stcRtcTime.u8Hour   = 23U;
    stcRtcTime.u8Minute = 59U;
    stcRtcTime.u8Second = 55U;
    stcRtcTime.u8AmPm   = RTC_HOUR12_AM_HOUR24;

    if (Ok != RTC_SetDate(RTC_DATA_FORMAT_DEC, &stcRtcDate))
    {
        printf("Set Date failed!\r\n");
    }

    if (Ok != RTC_SetTime(RTC_DATA_FORMAT_DEC, &stcRtcTime))
    {
        printf("Set Time failed!\r\n");
    }
}

/**
 * @brief  RTC display weekday.
 * @param  [in] u8Weekday               Weekday
 *         This parameter can be one of the following values:
 *           @arg RTC_WEEKDAY_SUNDAY:     Sunday
 *           @arg RTC_WEEKDAY_MONDAY:     Monday
 *           @arg RTC_WEEKDAY_TUESDAY:    Tuesday
 *           @arg RTC_WEEKDAY_WEDNESDAY:  Wednesday
 *           @arg RTC_WEEKDAY_THURSDAY:   Thursday
 *           @arg RTC_WEEKDAY_FRIDAY:     Friday
 *           @arg RTC_WEEKDAY_SATURDAY:   Saturday
 * @retval None
 */
static void RTC_DisplayWeekday(uint8_t u8Weekday)
{
    switch (u8Weekday)
    {
        case RTC_WEEKDAY_SUNDAY:
            printf("Sunday\r\n");
            break;
        case RTC_WEEKDAY_MONDAY:
            printf("Monday\r\n");
            break;
        case RTC_WEEKDAY_TUESDAY:
            printf("Tuesday\r\n");
            break;
        case RTC_WEEKDAY_WEDNESDAY:
            printf("Wednesday\r\n");
            break;
        case RTC_WEEKDAY_THURSDAY:
            printf("Thursday\r\n");
            break;
        case RTC_WEEKDAY_FRIDAY:
            printf("Friday\r\n");
            break;
        case RTC_WEEKDAY_SATURDAY:
            printf("Saturday\r\n");
            break;
        default:
            break;
    }
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

    /* RTC stopped */
    if (Disable == RTC_GetCounterState())
    {
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
            RTC_Init(&stcRtcInit);

            /* Update date and time */
            RTC_CalendarConfig();
            /* Enable period interrupt */
            RTC_IntCmd(RTC_INT_PRDIE, Enable);
            /* Startup RTC count */
            RTC_Cmd(Enable);
        }
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
 * @brief  Main function of RTC Calendar.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_rtc_date_t stcCurrentDate;
    stc_rtc_time_t stcCurrentTime;

    /* Configure clock */
    BSP_CLK_Init();
    XTAL32_ClkInit();
    /* Configure BSP */
    BSP_LED_Init();
    /* Configure UART */
    DDL_UartInit();
    /* Configure RTC */
    RTC_Config();
    
    while (1)
    {
        if (1U == u8SecIntFlag)
        {
            u8SecIntFlag = 0U;
            BSP_LED_Toggle(LED_RED);
            /* Get current date */
            if (Ok == RTC_GetDate(RTC_DATA_FORMAT_DEC, &stcCurrentDate))
            {
                /* Get current time */
                if (Ok == RTC_GetTime(RTC_DATA_FORMAT_DEC, &stcCurrentTime))
                {
                    /* Print current date and time */
                    printf("20%02d/%02d/%02d %02d:%02d:%02d ", stcCurrentDate.u8Year, stcCurrentDate.u8Month,
                                                               stcCurrentDate.u8Day, stcCurrentTime.u8Hour,
                                                               stcCurrentTime.u8Minute, stcCurrentTime.u8Second);
                    RTC_DisplayWeekday(stcCurrentDate.u8Weekday);
                }
                else
                {
                    printf("Get time failed!\r\n");
                }
            }
            else
            {
                printf("Get date failed!\r\n");
            }
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
