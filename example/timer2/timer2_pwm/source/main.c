/**
 *******************************************************************************
 * @file  timer2/timer2_pwm/source/main.c
 * @brief Main program TIMER2 pwm for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-16       Wuze            First version
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
 * @addtogroup Timer2_Pwm
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*
 * Functions of this example.
 * Use one channel of TIMER2 to output one PWM.
 */

/*
 * TIMER2 unit and channel definitions for this example.
 * 'APP_TMR2_UNIT' can be defined as M4_TMR2_<t>(t=1 ~ 4).
 * 'APP_TMR2_CH' can be defined as TMR2_CH_x(x=A, B).
 * 
 * NOTE!!! The following definitions are depend on the definitions of 'APP_TMR2_UNIT' and 'APP_TMR2_CH'.
 *
 *         APP_TMR2_PWM_PORT
 *         APP_TMR2_PWM_PIN
 *         APP_TMR2_PWM_PIN_FUNC
 */
#define APP_TMR2_UNIT                       (M4_TMR2_1)
#define APP_TMR2_CH                         (TMR2_CH_A)
#define APP_TMR2_PERIP_CLK                  (PWC_FCG2_TMR2_1)

/* TIMER2 PWM pin definitions. */
#define APP_TMR2_PWM_PORT                   (GPIO_PORT_A)
#define APP_TMR2_PWM_PIN                    (GPIO_PIN_02)
#define APP_TMR2_PWM_PIN_FUNC               (GPIO_FUNC_16_TIM21_PWMA)

/* TIMER2 clock source definitions. */
#define APP_TMR2_CLK_SRC                    (TMR2_CLK_SYNC_PCLK1)
#define APP_TMR2_CLK_DIV                    (TMR2_CLK_DIV_4)

/*
 * Calculate the comparison value register according to clock source, the prescaler of the clock source and PWM frequency.
 * CmpVal = TIMER2ClockFrequency(Hz) / PwmFrequency(Hz) / 2.
 *      In this example:
 *      TIMER2ClockFrequency = MRC(8MHz) / Timer2ClockPrescaler(4) = 2000000Hz;
 *      PwmFrequency = 1000000Hz;
 *      CmpVal = (2000000 / 1000000 / 2) - 1 = 0.
 *
 * NOTE!!! Duty cycle is a fixed value 50%.
 */
#define APP_TMR2_CMP_VAL                    (0U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void Tmr2Config(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of timer2_pwm project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configures the XTAL(8MHz) as the system clock. */
    SystemClockConfig();

    /* Configures TIMER2. */
    Tmr2Config();

    /* Starts TIMER2 to start PWM output. */
    TMR2_Start(APP_TMR2_UNIT, APP_TMR2_CH);

    /***************** Configuration end, application start **************/

    while (1U)
    {
        /* Use TMR2_Stop(APP_TMR2_UNIT, APP_TMR2_CH) to stop the PWM output. */
    }
}

/**
 * @brief  Configures the XTAL(8MHz) as the system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXtalInit;

    /* Xtal config */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    stcXtalInit.u8XtalDrv   = CLK_XTALDRV_LOW;
    stcXtalInit.u8XtalMode  = CLK_XTALMODE_OSC;
    stcXtalInit.u8XtalStb   = CLK_XTALSTB_499US;
    CLK_XtalInit(&stcXtalInit);
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_XTAL);
}

/**
 * @brief  TIMER2 configuration.
 * @param  None
 * @retval None
 */
static void Tmr2Config(void)
{
    stc_tmr2_init_t stcInit;
    stc_tmr2_pwm_cfg_t stcCfg;

    /* 1. Enable TIMER2 peripheral clock. */
    PWC_Fcg2PeriphClockCmd(APP_TMR2_PERIP_CLK, Enable);

    /* 2. Set a default initialization value for stcInit. */
    TMR2_StructInit(&stcInit);

    /* 3. Modifies the initialization values depends on the application. */
    stcInit.u32ClkSrc = APP_TMR2_CLK_SRC;
    stcInit.u32ClkDiv = APP_TMR2_CLK_DIV;
    stcInit.u32CmpVal = APP_TMR2_CMP_VAL;
    TMR2_Init(APP_TMR2_UNIT, APP_TMR2_CH, &stcInit);

    /* 4. PWM configuration. */
    GPIO_SetFunc(APP_TMR2_PWM_PORT, APP_TMR2_PWM_PIN, APP_TMR2_PWM_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    TMR2_PWM_StructInit(&stcCfg);
    TMR2_PWM_Config(APP_TMR2_UNIT, APP_TMR2_CH, &stcCfg);
    TMR2_PWM_Cmd(APP_TMR2_UNIT, APP_TMR2_CH, Enable);
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
