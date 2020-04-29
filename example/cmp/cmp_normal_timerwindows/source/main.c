/**
 *******************************************************************************
 * @file  cmp/cmp_normal_timerwindows/source/main.c
 * @brief Main program of CMP for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-23       Heqb         First version
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
 * @addtogroup CMP_Normal_TimerWindows
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMP_TEST_UNIT                   (M4_CMP1)

/* Define port and pin for CMP */
/* CMP1_VCOUT1*/
#define CMP1_VCOUT1_PORT                (GPIO_PORT_A)
#define CMP1_VCOUT1_PIN                 (GPIO_PIN_00)

/* TIMERB unit & interrupt number & counter period/compare value definition */
#define TIMERA_ODD_UNIT                 (M4_TMRA_1)
#define TIMERA_ODD_UNIT_CMP_INT         (INT_TMRA_1_CMP)
#define TIMERA_ODD_UNIT_CMP_IRQn        (Int022_IRQn)
#define TIMERA_ODD_UNIT_PERIOD_VALUE    ((SystemCoreClock/512U))
#define TIMERA_ODD_UNIT_COMPARE_VALUE   ((TIMER_ODD_UNIT_PERIOD_VALUE/2U))
/* TIMERB TIMB_t_PWM1 Port/Pin definition */
#define TIMERA_ODD_UNIT_PWM1_PORT       (GPIO_PORT_A)     /* PA8: TIMA_1_PWM1 */
#define TIMERA_ODD_UNIT_PWM1_PIN        (GPIO_PIN_08)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_tmra_init_t m_stcTmraInit = {
    .u32CntDir = TMRA_DIR_UP,
    .u32ClkDiv = TMRA_CLK_DIV_512,
    .u32CntMode = TMRA_MODE_SAWTOOTH,
    .u32CntOvfOp = TMRA_OVF_KEEP_CNT,
};

static stc_tmra_pwm_cfg_t m_stcTmraPwmCfgInit = {
    .u32StartPolarity = TMRA_PWM_START_LOW,
    .u32StopPolarity = TMRA_PWM_STOP_KEEP,
    .u32CMPolarity = TMRA_PWM_CM_REVERSE,
    .u32PMPolarity = TMRA_PWM_PM_KEEP,
    .u32ForcePolarity = TMRA_PWM_FORCE_LOW,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of cmp_normal_timerwindows project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_cmp_init_t stcCmpCfg;
    stc_cmp_timerwindows_t stcTimerWindowsInit;

    /* Configure system clock. */
    SystemClockConfig();

    /* Port function configuration for CMP*/
    GPIO_SetFunc(CMP1_VCOUT1_PORT, CMP1_VCOUT1_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE);

    /* Port function configuration for Timerb PWM */
    GPIO_SetFunc(TIMERA_ODD_UNIT_PWM1_PORT, TIMERA_ODD_UNIT_PWM1_PIN, GPIO_FUNC_4_TIMA1_PWM1, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock for Timerb*/
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TIMERA_1, Enable);

    /* Initialize TMRA odd unit. */
    m_stcTmraInit.u32PeriodRefVal = (uint16_t)TMRA_ODD_UNIT_PERIOD_VALUE;
    TIMERA_Init(TIMERA_ODD_UNIT, &m_stcTimeraInit);

    /* Initialize TMRA even unit output compare function . */
    TMRA_PWM_Config(TMRA_ODD_UNIT, TMRA_CH_1, &m_stcTmraPwmCfgInit);
    /* Start TMRA_1 counter. */
    TMRA_Start(TMRA_ODD_UNIT);

    /* Configuration TmrA pwm function */
    /* Enable peripheral clock */
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TIMERA_1, Enable);

    /* Enable peripheral clock for CMP*/
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_CMP1, Enable);

    /* Clear structure */
    CMP_StructInit(&stcCmpCfg);
    /* De-initialize CMP unit */
    CMP_DeInit(CMP_TEST_UNIT);

    /* Configuration for normal compare function */
    stcCmpCfg.u8CmpCh = CMP_CVSL_INP1;
    stcCmpCfg.u8RefVol = CMP_RVSL_INM1;
    stcCmpCfg.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpCfg.u8OutFilter = CMP_OUT_FILTER_PCLKDIV8;
    stcCmpCfg.u8OutPolarity = CMP_OUT_REVERSE_ON;
    CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpCfg);

    /* Enable VCOUT if need */
    CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);

    /* Timer windows function configuration if need */
    stcTimerWindowsInit.u16TWSelect = CMP_TIMERWIN_TIMA_x_PWM1;
    stcTimerWindowsInit.u8TWOutLevel = CMP_TIMERWIN_OUT_LEVEL_HIGH;
    stcTimerWindowsInit.u8TWInvalidLevel = CMP_TIMERWIN_INVALID_LEVEL_LOW;
    CMP_TimerWindowConfig(CMP_TEST_UNIT, &stcTimerWindowsInit);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /* Configuration finished */
    while(1)
    {
        ;
    }
}

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXTALInit;

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_8MS;

    /* Initialize XTAL clock */
    CLK_XtalInit(&stcXTALInit);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_XTAL);
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
