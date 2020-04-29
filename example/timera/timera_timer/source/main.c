/**
 *******************************************************************************
 * @file  timera/timera_timer/source/main.c
 * @brief Main program TIMERA timer for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-31       Wuze            First version
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
 * @addtogroup TimerA_Timer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * Function of this example.
 * This example is going to use TIMERA to count 10 milliseconds.
 */

/*
 * TIMERA unit and channel definitions for this example.
 * 'APP_TMRA_UNIT' can be defined as M4_TMRA_<t>(t=1 ~ 12).
 * 'APP_TMRA_CH' can be defined as TMRA_CH_x(x=1 ~ 4).
 *
 * NOTE!!! The following definitions are depend on the definitions of 'APP_TMRA_UNIT' and 'APP_TMRA_CH'.
 *
 *         APP_TMRA_TRIG_PORT
 *         APP_TMRA_TRIG_PIN
 *         APP_TMRA_TRIG_PIN_FUNC
 *         APP_TMRA_INT_SRC
 *         APP_TMRA_IRQ_CB
 *         APP_TMRA_IRQn
 */
#define APP_TMRA_UNIT                       (M4_TMRA_1)
#define APP_TMRA_CH                         (TMRA_CH_1)
#define APP_TMRA_PERIP_CLK                  (PWC_FCG2_TMRA_1)
#define APP_FCG2_PERIP_CLK                  (APP_TMRA_PERIP_CLK)

/*
 * Clock source of TIMERA in this example.
 * The only valid clock source of TIMERA in this example is PCLK1.
 */
#define APP_TMRA_CLK                        (TMRA_CLK_PCLK1)

/* The clock division of PCLK1. */
#define APP_TMRA_PCLK1_DIV                  (TMRA_CLK_DIV_8)

/* The counting mode of TIMERA. */
#define APP_TMRA_MODE                       (TMRA_MODE_TRIANGLE)

/* The counting direction of TIMERA. */
#define APP_TMRA_DIR                        (TMRA_DIR_UP)

/*
 * Function control of TIMERA.
 * Defines the following macro as non-zero to enable the corresponding function.
 *
 * 'APP_TMRA_USE_INTERRUPT': Interrupt function control.
 * 'APP_TMRA_USE_HW_TRIG': Hardware trigger conditions control. The conditions that can start TIMERA, \
 *                         stop TIMERA or clear counting register of TIMERA
 * 'APP_TMRA_USE_FILTER': Filter function control. Enable or disable the filter of pin TIMA_<t>_TRIG. \
 *                        If there is a pin TIMA_<t>_TRIG is used, the filter can be used if needed.
 *                        In this example, the only pin with filter function used is TIMA_<t>_TRIG.
 */
#define APP_TMRA_USE_INTERRUPT              (0U)
#define APP_TMRA_USE_HW_TRIG                (1U)
#if (APP_TMRA_USE_HW_TRIG > 0U)
    #define APP_TMRA_USE_FILTER             (1U)
#endif

/*
 * In this example:
 *      Timing period is 10ms.
 * A simple formula for calculating the compare value is:
 *      TmrACompareVal = TmrAPeriod(us) * [TmrAClockSource(MHz) / TmrAClockPrescaler].
 */
#if (APP_TMRA_MODE == TMRA_MODE_SAWTOOTH)
    #if (APP_TMRA_DIR == TMRA_DIR_UP)
        #define APP_TMRA_CMP_VAL            (50000U)
    #else
        #define APP_TMRA_CMP_VAL            (50000U)
    #endif
#else /* (APP_TMRA_MODE == TMRA_MODE_TRIANGLE) */
    #if (APP_TMRA_DIR == TMRA_DIR_UP)
        #define APP_TMRA_CMP_VAL            (50000U / 2U)
    #else
        #define APP_TMRA_CMP_VAL            (50000U / 2U)
    #endif
#endif /* #if (APP_TMRA_DIR == TMRA_MODE_SAWTOOTH) */

/*
 * Definitions about TIMERA interrupt for the example.
 * IRQn of TIMERA:
 *      M4_TMRA_x(x=1, 2): [Int000_IRQn, Int031_IRQn], [Int074_IRQn, Int079_IRQn]; [Int135_IRQn]
 *      M4_TMRA_x(x=3, 4): [Int000_IRQn, Int031_IRQn], [Int080_IRQn, Int085_IRQn]; [Int136_IRQn]
 *      M4_TMRA_x(x=5 ~ 8): [Int000_IRQn, Int031_IRQn], [Int092_IRQn, Int097_IRQn]; [Int138_IRQn]
 *      M4_TMRA_x(x=9 ~ 12): [Int000_IRQn, Int031_IRQn], [Int098_IRQn, Int103_IRQn]; [Int139_IRQn]
 *
 * NOTE!!! 'APP_TMRA_INT_TYPE' can only be defined as 'TMRA_INT_MATCH_x'(x=1 ~ 4, depends on 'APP_TMRA_CH') for this example.
 */
#if (APP_TMRA_USE_INTERRUPT > 0U)
    #define APP_TMRA_INT_TYPE               (TMRA_INT_MATCH_1)
    #define APP_TMRA_INT_PRIO               (DDL_IRQ_PRIORITY_03)
    #define APP_TMRA_INT_SRC                (INT_TMRA_1_CMP)
    #define APP_TMRA_IRQ_CB                 TMRA_1_Cmp1_IrqHandler
    #define APP_TMRA_IRQn                   (Int074_IRQn)
#endif /* #if (APP_TMRA_USE_INTERRUPT > 0U) */

/* The status flag of TIMERA in this example, depends on 'APP_TMRA_CH'. */
#define APP_TMRA_FLAG                       (TMRA_FLAG_MATCH_1)

/*
 * Specify the hardware trigger conditions if enabled(APP_TMRA_USE_HW_TRIG > 0U).
 * 'APP_TMRA_START_COND' specifies the condition of starting TIMERA.
 * 'APP_TMRA_STOP_COND' specifies the condition of stoping TIMERA.
 *
 * NOTE!!! CANNOT specify a condition as both the start condition and the stop condition.
 */
#if (APP_TMRA_USE_HW_TRIG > 0U)
    //TODO: A UART event to trigger?
    #define APP_TMRA_START_COND             (TMRA_START_COND_TRIGR)
    #define APP_TMRA_STOP_COND              (TMRA_STOP_COND_TRIGF)
    #define APP_TMRA_TRIG_PORT              (GPIO_PORT_C)
    #define APP_TMRA_TRIG_PIN               (GPIO_PIN_00)
    #define APP_TMRA_TRIG_PIN_FUNC          (GPIO_FUNC_6_TIMA1_TRIG)
#endif /* #if (APP_TMRA_USE_HW_TRIG > 0U) */

/* Specifying clock divider of filter of each channel depends on the signal that input from pin TIM2_<t>_PWMA/B. */
#if (APP_TMRA_USE_FILTER > 0U)
    #define APP_TMRA_FILTER_CLK_DIV         (TMRA_FILTER_CLK_DIV_16)
#endif

/* LED pin definition in this example. */
#define LED_R_PORT                          (GPIO_PORT_A)
#define LED_R_PIN                           (GPIO_PIN_09)
#define LED_R_ON()                          (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_OFF()                         (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_TOGGLE()                      (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);

static void TmrAConfig(void);
#if (APP_TMRA_USE_INTERRUPT > 0U)
    static void TmrAIrqConfig(void);
#endif
#if (APP_TMRA_USE_HW_TRIG > 0U)
    static void TmrATrigCondConfig(void);
#endif
static void TmrAStart(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of timera_base_timer project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configures the system clock. */
    SystemClockConfig();

    /* Configures LED. */
    LedConfig();

    /* Configures TIMERA. */
    TmrAConfig();

    /* Starts TIMERA. */
    TmrAStart();

    /***************** Configuration end, application start **************/
    while (1U)
    {
#if (APP_TMRA_USE_INTERRUPT > 0U)
        /* See APP_TMRA_IRQ_CB in this file. */
#else
        /* Call TMRA_GetStatus to check the flag state. */
        if (TMRA_GetStatus(APP_TMRA_UNIT, APP_TMRA_FLAG) == Set)
        {
            TMRA_ClrStatus(APP_TMRA_UNIT, APP_TMRA_FLAG);
            LED_R_TOGGLE();
        }
#endif /* #if (APP_TMRA_USE_INTERRUPT > 0U) */
    }
}

/**
 * @brief  Configures a new system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
}

/**
 * @brief  TIMERA configuration.
 * @param  None
 * @retval None
 */
static void TmrAConfig(void)
{
    stc_tmra_init_t stcInit;

    /* 1. Enable TIMERA peripheral clock. */
    PWC_Fcg2PeriphClockCmd(APP_FCG2_PERIP_CLK, Enable);

    /* 2. Set a default initialization value for stcInit. */
    TMRA_StructInit(&stcInit);

    /* 3. Modifies the initialization values depends on the application. */
    stcInit.u32ClkSrc  = APP_TMRA_CLK;
    stcInit.u32ClkDiv  = APP_TMRA_PCLK1_DIV;
    stcInit.u32CntDir  = APP_TMRA_DIR;
    stcInit.u32CntMode = APP_TMRA_MODE;
    TMRA_Init(APP_TMRA_UNIT, &stcInit);

    /* 4. Set the comparison reference value. */
    TMRA_SetCmpRefVal(APP_TMRA_UNIT, APP_TMRA_CH, APP_TMRA_CMP_VAL);

#if (APP_TMRA_USE_INTERRUPT > 0U)
    /* 5. Configures IRQ if needed. */
    TmrAIrqConfig();
#endif /* #if (APP_TMRA_USE_INTERRUPT > 0U) */

#if (APP_TMRA_USE_HW_TRIG > 0U)
    /* 6. Configures hardware trigger condition if needed. */
    TmrATrigCondConfig();
#endif /* #if (APP_TMRA_USE_HW_TRIG > 0U) */
}

#if (APP_TMRA_USE_INTERRUPT > 0U)
/**
 * @brief  TIMERA interrupt configuration.
 * @param  None
 * @retval None
 */
static void TmrAIrqConfig(void)
{
    uint8_t u8IRQn = (uint8_t)APP_TMRA_IRQn;
    stc_irq_signin_config_t stcCfg;

    stcCfg.enIntSrc    = APP_TMRA_INT_SRC;
    stcCfg.enIRQn      = APP_TMRA_IRQn;
    stcCfg.pfnCallback = &APP_TMRA_IRQ_CB;
    if (u8IRQn >= Int135_IRQn)
    {
        /* Sharing interrupt. */
        INTC_ShareIrqCmd(stcCfg.enIntSrc, Enable);
    }
    else
    {
        /* Independent interrupt. */
        INTC_IrqSignIn(&stcCfg);
    }
    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, APP_TMRA_INT_PRIO);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    /* Enable the specified interrupts of TIMERA. */
    TMRA_IntCmd(APP_TMRA_UNIT, APP_TMRA_INT_TYPE, Enable);
}

/**
 * @brief  TIMERA counter compare match interrupt callback function.
 * @param  None
 * @retval None
 */
void APP_TMRA_IRQ_CB(void)
{
    if (TMRA_GetStatus(APP_TMRA_UNIT, APP_TMRA_FLAG) == Set)
    {
        TMRA_ClrStatus(APP_TMRA_UNIT, APP_TMRA_FLAG);
        LED_R_TOGGLE();
    }
}
#endif /* #if (APP_TMRA_USE_INTERRUPT > 0U) */

#if (APP_TMRA_USE_HW_TRIG > 0U)
/**
 * @brief
 * @param  [in]
 * @param  [out]
 * @retval None
 */
static void TmrATrigCondConfig(void)
{
    stc_tmra_trig_cond_t stcTrigCond;

    /*
     * If a peripheral is used to generate the event which is used as a hardware trigger condition of TIMERA, \
     *     call the API of the peripheral to configure the peripheral.
     * The following operations are only used in this example.
     */

#if (APP_TMRA_USE_FILTER > 0U)
    TMRA_FilterConfig(APP_TMRA_UNIT, TMRA_PIN_TRIG, APP_TMRA_FILTER_CLK_DIV);
    TMRA_FilterCmd(APP_TMRA_UNIT, TMRA_PIN_TRIG, Enable);
#endif
    GPIO_SetFunc(APP_TMRA_TRIG_PORT, APP_TMRA_TRIG_PIN, APP_TMRA_TRIG_PIN_FUNC, PIN_SUBFUNC_DISABLE);

    TMRA_TrigCondStructInit(&stcTrigCond);
    stcTrigCond.u32StartCond = APP_TMRA_START_COND;
    stcTrigCond.u32StopCond  = APP_TMRA_STOP_COND;
    TMRA_SetTrigCond(APP_TMRA_UNIT, &stcTrigCond);
}
#endif

/**
 * @brief  Start TIMERA.
 * @param  None
 * @retval None
 */
static void TmrAStart(void)
{
    /*
     * If a peripheral is used to generate the event which is used as a hardware trigger condition of TIMERA, \
     *     call the API of the peripheral to start the peripheral here or anywhere else you need.
     * The following operations are only used in this example.
     */

#if ((APP_TMRA_USE_HW_TRIG == 0U) || \
     ((APP_TMRA_USE_HW_TRIG > 0U) && (APP_TMRA_START_COND == TMRA_START_COND_INVALID)))
    TMRA_Start(APP_TMRA_UNIT);
#else
    /* Make an rising edge on pin TIMA_<t>_TRIG to start TIMERA. */
#endif
}

/**
 * @brief  Led configuration.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);

    /* LED R initialize */
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);

    /* "Turn off" LED before set to output */
    LED_R_ON();

    /* Output enable */
    GPIO_OE(LED_R_PORT, LED_R_PIN, Enable);
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
