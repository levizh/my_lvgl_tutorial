/**
 *******************************************************************************
 * @file  timera/timera_capture/source/main.c
 * @brief Main program TIMERA capture for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-28       Wuze            First version
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
 * @addtogroup TimerA_Capture
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*
 * TIMERA unit and channel definitions for this example.
 * 'APP_TMRA_UNIT' can be defined as M4_TMRA_<t>(t=1 ~ 12).
 * 'APP_TMRA_CH' can be defined as TMRA_CH_x(x=1 ~ 4).
 */
#define APP_TMRA_UNIT                       (M4_TMRA_1)
#define APP_TMRA_CH                         (TMRA_CH_4)
#define APP_TMRA_PERIP_CLK                  (PWC_FCG2_TMRA_1)

/*
 * Specify conditions for TIMERA capturing in this example.
 * The conditions are included in @ref TMRA_Channel_Capture_Condition except 'TMRA_CAPT_COND_INVALID'
 */
#define APP_CAPTURE_CONDITION               (TMRA_CAPT_COND_EVENT)

/* Feasibility check. */
#if (APP_CAPTURE_CONDITION & (TMRA_CAPT_COND_TRIGR | TMRA_CAPT_COND_TRIGF))
    #if (APP_TMRA_CH != TMRA_CH_4)
        #error "Only channel 4 of TIMERA supports capturing the edge of TRIG pin."
    #endif
#endif

/* Specifies the pin or the event to be used according to the capture-condition. */
#if (APP_CAPTURE_CONDITION & (TMRA_CAPT_COND_PWMR | TMRA_CAPT_COND_PWMF))
    #define APP_TMRA_CAPT_PWM_PORT          (GPIO_PORT_A)
    #define APP_TMRA_CAPT_PWM_PIN           (GPIO_PIN_11)
    #define APP_TMRA_CAPT_PWM_PIN_FUNC      (GPIO_FUNC_4_TIMA1_PWM4)
#endif

#if (APP_CAPTURE_CONDITION & TMRA_CAPT_COND_EVENT)
    #define APP_TMRA_CAPT_EVENT             (EVT_PORT_EIRQ0)
#endif

#if (APP_CAPTURE_CONDITION & (TMRA_CAPT_COND_TRIGR | TMRA_CAPT_COND_TRIGF))
    #define APP_TMRA_CAPT_TRIG_PORT         (GPIO_PORT_A)
    #define APP_TMRA_CAPT_TRIG_PIN          (GPIO_PIN_12)
    #define APP_TMRA_CAPT_TRIG_PIN_FUNC     (GPIO_FUNC_4_TIMA1_TRIG)
#endif

/*
 * Clock source of TIMERA in this example.
 * The only valid clock source of TIMERA in this example is PCLK(PCLK0 for unit1 ~ uint4. PCLK1 for unit5 ~ uint12).
 */
#define APP_TMRA_CLK                        (TMRA_CLK_PCLK)

/* The divider of the clock source. @ref TMRA_PCLK_Divider */
#define APP_TMRA_PCLK_DIV                   (TMRA_PCLK_DIV_1)

/*
 * Definitions of interrupt.
 * IRQn of TIMERA:
 *      M4_TMRA_x(x=1, 2): [Int000_IRQn, Int031_IRQn], [Int074_IRQn, Int079_IRQn]; [Int135_IRQn]
 *      M4_TMRA_x(x=3, 4): [Int000_IRQn, Int031_IRQn], [Int080_IRQn, Int085_IRQn]; [Int136_IRQn]
 *      M4_TMRA_x(x=5 ~ 8): [Int000_IRQn, Int031_IRQn], [Int092_IRQn, Int097_IRQn]; [Int138_IRQn]
 *      M4_TMRA_x(x=9 ~ 12): [Int000_IRQn, Int031_IRQn], [Int098_IRQn, Int103_IRQn]; [Int139_IRQn]
 *
 * NOTE!!! 'APP_TMRA_INT_TYPE' can only be defined as 'TMRA_INT_CMP_CHx'(x=1 ~ 4, depends on 'APP_TMRA_CH') for this example.
 */
#define TMRA_SHARE_IRQn_BASE                (Int135_IRQn)

#define APP_TMRA_IRQn                       (Int025_IRQn)
#define APP_TMRA_INT_SRC                    (INT_TMRA_1_CMP)
#define APP_TMRA_INT_PRIO                   (DDL_IRQ_PRIORITY_03)
#define APP_TMRA_INT_TYPE                   (TMRA_INT_CMP_CH4)
#define APP_TMRA_IRQ_CB                     TMRA_1_Cmp4_IrqHandler
#define APP_TMRA_FLAG                       (TMRA_FLAG_CMP_CH4)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);

static void TmrAConfig(void);
static void TmrACaptCondConfig(void);
static void TmrAIrqConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of timera_capture project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configures the system clock. */
    SystemClockConfig();

    /* Configures TIMERA. */
    TmrAConfig();

    /* Starts TIMERA. */
    TMRA_Start(APP_TMRA_UNIT);

    /***************** Configuration end, application start **************/
    while (1U)
    {
    }
}

/**
 * @brief  Configures a new system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_pllh_init_t stcPLLHInit;
    stc_clk_xtal_init_t stcXtalInit;

    /* Configures XTAL. PLLH input source is XTAL. */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    stcXtalInit.u8XtalDrv   = CLK_XTALDRV_LOW;
    stcXtalInit.u8XtalMode  = CLK_XTALMODE_OSC;
    stcXtalInit.u8XtalStb   = CLK_XTALSTB_499US;
    CLK_XtalInit(&stcXtalInit);

    /* PCLK0, HCLK  Max 240MHz */
    /* PCLK1, PCLK4 Max 120MHz */
    /* PCLK2, PCLK3 Max 60MHz  */
    /* EX BUS Max 120MHz */
    CLK_ClkDiv(CLK_CATE_ALL,                                       \
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 | \
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 | \
                CLK_HCLK_DIV1));

    CLK_PLLHStrucInit(&stcPLLHInit);
    /*
     * PLLP_freq = ((PLL_source / PLLM) * PLLN) / PLLP
     *           = (8 / 1) * 100 / 4
     *           = 200
     */
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = (1UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLN = (100UL - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLP = (4UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLQ = (16UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLR = (16UL  - 1UL);

    /* stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL; */
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);
    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM123 | SRAM4 | SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);

    /* Set EFM wait cycle. 4 wait cycles needed when system clock is 200MHz */
    EFM_Unlock();
    EFM_SetWaitCycle(EFM_WAIT_CYCLE_5);
    EFM_Lock();

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
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
    PWC_Fcg2PeriphClockCmd(APP_TMRA_PERIP_CLK, Enable);

    /* 2. Set a default initialization value for stcInit. */
    TMRA_StructInit(&stcInit);

    /* 3. Modifies the initialization values depends on the application. */
    stcInit.u32ClkSrc  = APP_TMRA_CLK;
    stcInit.u32PCLKDiv = APP_TMRA_PCLK_DIV;
    TMRA_Init(APP_TMRA_UNIT, &stcInit);

    /* 4. Set function mode as capturing mode. */
    TMRA_SetFuncMode(APP_TMRA_UNIT, APP_TMRA_CH, TMRA_FUNC_CAPTURE);

    /* 5. Configures the capture condition. */
    TmrACaptCondConfig();

    /* 6. Configures IRQ if needed. */
    TmrAIrqConfig();
}

/**
 * @brief  Capture condition configuration.
 * @param  None
 * @retval None
 */
static void TmrACaptCondConfig(void)
{
#if (APP_CAPTURE_CONDITION & (TMRA_CAPT_COND_PWMR | TMRA_CAPT_COND_PWMF))
    GPIO_SetFunc(APP_TMRA_CAPT_PWM_PORT, APP_TMRA_CAPT_PWM_PIN, APP_TMRA_CAPT_PWM_PIN_FUNC, PIN_SUBFUNC_DISABLE);
#endif

#if (APP_CAPTURE_CONDITION & TMRA_CAPT_COND_EVENT)
    /* Configure the peripheral. */
    stc_exint_init_t stcExintInit;
    stc_gpio_init_t stcGpioInit;
    stc_keyscan_init_t stcKeyscanInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt  = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(GPIO_PORT_A, GPIO_PIN_00, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh  = EXINT_CH00;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    GPIO_StructInit(&stcGpioInit);
    KEYSCAN_StructInit(&stcKeyscanInit);
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(GPIO_PORT_A, GPIO_PIN_06, &stcGpioInit);
    GPIO_SetFunc(GPIO_PORT_A, GPIO_PIN_06, GPIO_FUNC_8_KEYSCAN, Disable);

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_KEY, Enable);

    stcKeyscanInit.u32HizCycle = KEYSCAN_HIZ_CLC_512;
    stcKeyscanInit.u32LowCycle = KEYSCAN_LOW_CLC_512;
    stcKeyscanInit.u32KeyClk   = KEYSCAN_CLK_HCLK;
    stcKeyscanInit.u32Keyout   = KEYSCAN_OUT_0T2;
    stcKeyscanInit.u32Keyin    = KEYSCAN_IN_0;
    KEYSCAN_Init(&stcKeyscanInit);
    KEYSCAN_Cmd(Enable);

    /* Enable AOS function. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_AOS, Enable);
    /* Set the event for TIMERA capturing. */
    TMRA_SetCaptEvent(APP_TMRA_UNIT, APP_TMRA_CAPT_EVENT);
#endif

#if (APP_CAPTURE_CONDITION & (TMRA_CAPT_COND_TRIGR | TMRA_CAPT_COND_TRIGF))
    GPIO_SetFunc(APP_TMRA_CAPT_TRIG_PORT, APP_TMRA_CAPT_TRIG_PIN, APP_TMRA_CAPT_TRIG_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    /* The capture-condition is configured via channel 3 when the capture-condition is the edge of pin TRIG. */
    TMRA_SetCaptCond(APP_TMRA_UNIT, TMRA_CH_3, APP_CAPTURE_CONDITION);
#else
    TMRA_SetCaptCond(APP_TMRA_UNIT, APP_TMRA_CH, APP_CAPTURE_CONDITION);
#endif
}

/**
 * @brief  TIMERA interrupt configuration.
 * @param  None
 * @retval None
 */
static void TmrAIrqConfig(void)
{
    stc_irq_signin_config_t stcCfg;

    stcCfg.enIntSrc    = APP_TMRA_INT_SRC;
    stcCfg.enIRQn      = APP_TMRA_IRQn;
    stcCfg.pfnCallback = &APP_TMRA_IRQ_CB;
    if (stcCfg.enIRQn >= TMRA_SHARE_IRQn_BASE)
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
        /* A capture occurred */

        /* Get capture value by calling function TMRA_GetCmpVal. */

        TMRA_ClrStatus(APP_TMRA_UNIT, APP_TMRA_FLAG);
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
