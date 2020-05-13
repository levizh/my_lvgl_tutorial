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
#define CMP_PERIP_CLK                   (PWC_FCG3_CMP1)
/* Define port and pin for CMP */
/* CMP1 compare voltage CMP1_INP3 */
#define CMP1_INP3_PORT                  (GPIO_PORT_E)
#define CMP1_INP3_PIN                   (GPIO_PIN_10)
/* CMP1 reference voltage CMP1_INM4*/
#define CMP1_INM4_PORT                  (GPIO_PORT_C)
#define CMP1_INM4_PIN                   (GPIO_PIN_03)
/* CMP1_VCOUT */
#define CMP_VCOUT_PORT                  (GPIO_PORT_B)
#define CMP_VCOUT_PIN                   (GPIO_PIN_12)

/* Select PWM as window signal of CMP1 */
#define CMP_TW_PWM_TMR4                 (0U)
#define CMP_TW_PWM_TMR6                 (1U)
#define CMP_TW_PWM_TMRA                 (2U)
#define CMP_TW_PWM_SOURCE               (CMP_TW_PWM_TMRA)

#if (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMRA)
    #define TMRA_UNIT                   (M4_TMRA_1)
    #define TMRA_CH                     (TMRA_CH_1)
    #define TMRA_PERIP_CLK              (PWC_FCG2_TMRA_1)

    #define TMRA_PWM_A_PORT             (GPIO_PORT_E)
    #define TMRA_PWM_A_PIN              (GPIO_PIN_09)
    #define TMRA_PWM_A_PIN_FUNC         (GPIO_FUNC_4_TIMA1_PWM1)

    #define TMRA_CLOCK                  (TMRA_CLK_PCLK)
    #define TMRA_CLOCK_DIV              (TMRA_PCLK_DIV_1024)
    #define TMRA_MODE                   (TMRA_MODE_SAWTOOTH)
    #define TMRA_DIR                    (TMRA_DIR_UP)
    #define TMRA_PERIOD_VAL             (4000UL)
    #define TMRA_PWM_A_CMP_VAL          (2000UL)
    /* select TMRA_1_PWM1 as window signal of CMP1 */
    #define CMP_TW_PWM                  (CMP_TIMERWIN_TIMA_x_PWM1)
#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR4)
    #define TMR4_UNIT                   (M4_TMR4_1)
    #define TMR4_CH                     (TMR4_CH_1)
    #define TMR4_PERIP_CLK              (PWC_FCG2_TMR4_1)
    #define TMR4_CNT_CYCLE_VAL          (4000UL)

    #define TMR4_OUH_PORT               (GPIO_PORT_E)
    #define TMR4_OUH_PIN                (GPIO_PIN_09)
    #define TMR4_OUH_GPIO_FUNC          (GPIO_FUNC_2_TIM41_OUH)

    #define TMR4_OUL_PORT               (GPIO_PORT_E)
    #define TMR4_OUL_PIN                (GPIO_PIN_08)
    #define TMR4_OUL_GPIO_FUNC          (GPIO_FUNC_2_TIM41_OUL)
    /* select TMR4_1_OWH as window signal of CMP1 */
    #define CMP_TW_PWM                  (CMP_TIMERWIN_TIM4_x_OUH)
    /* Timer4 PWM get channel by OCO high channel */
    #define TMR4_PWM_CH(x)              (((x) == TMR4_OCO_UH) ? TMR4_PWM_U : \
                                        (((x) == TMR4_OCO_VH) ? TMR4_PWM_V : TMR4_PWM_W))
#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR6)
    #define TMR6_UNIT                   (M4_TMR6_1)
    #define TMR6_PERIP_CLK              (PWC_FCG2_TMR6_1)
    #define TMR6_PERIOD_VAL             (60000UL)
    #define TMR6_CPMPARE_VAl            (40000UL)

    #define TMR6_1_PWMA_PORT            (GPIO_PORT_B)
    #define TMR6_1_PWMA_PIN             (GPIO_PIN_09)
    #define TMR6_1_PWMB_PORT            (GPIO_PORT_B)
    #define TMR6_1_PWMB_PIN             (GPIO_PIN_08)
    /* select TMR6_1_PWMA as window signal of CMP1 */
    #define CMP_TW_PWM                  (CMP_TIMERWIN_TIM6_a_PWMb)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void CmpConfig(void);
#if (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMRA)
    static void TMRAConfig(void);

#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR4)
    static void TMR4Config(void);

#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR6)
    static void TMR6Config(void);
#endif
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

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
    /* Configure system clock. */
    SystemClockConfig();
#if (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMRA)
    /* Configure TMRA */
    TMRAConfig();
#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR4)
    /* Configure TMR4 */
    TMR4Config();
#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR6)
    /* Configure TMR6 */
    TMR6Config();
#endif
    /* Configure CMP */
    CmpConfig();
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
               (CLK_PCLK0_DIV4 | CLK_PCLK1_DIV4 | CLK_PCLK2_DIV4 | \
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 | \
                CLK_HCLK_DIV1));

    CLK_PLLHStrucInit(&stcPLLHInit);
    /*
     * PLLP_freq = ((PLL_source / PLLM) * PLLN) / PLLP
     *           = (8 / 1) * 120 / 4
     *           = 240
     */
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = (1UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLN = (120UL - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLP = (4UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLQ = (16UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLR = (16UL  - 1UL);

    /* stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL; */
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM123 | SRAM4 | SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);
    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_5);   /* 5-wait @ 240MHz */
    EFM_Unlock();

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  Configure CMP.
 * @param  None
 * @retval None
 */
static void CmpConfig(void)
{
    stc_cmp_init_t stcCmpInit;
    stc_cmp_timerwindow_t stcCmptimerWindow;
    stc_gpio_init_t stcGpioInit;
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(CMP_PERIP_CLK, Enable);
    /* Port function configuration for CMP*/
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(CMP1_INP3_PORT, CMP1_INP3_PORT, &stcGpioInit); /* CMP1 compare voltage */
    GPIO_Init(CMP1_INM4_PORT, CMP1_INM4_PIN, &stcGpioInit);  /* CMP1 reference voltage */
    GPIO_SetFunc(CMP_VCOUT_PORT, CMP_VCOUT_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE); /* CMP1_VCOUT1 */
    /* Clear structure */
    CMP_StructInit(&stcCmpInit);

    /* Configuration for normal compare function */
    /*For CMP1 and CMP3, when selecting channels inp2 and inp3, there are
    variety of compara voltage available, so you need to configure channels
    and voltage sources, and for others, you only need to configure channels*/
    stcCmpInit.u8CmpCh          = CMP_CVSL_INP3;
    stcCmpInit.u16CmpVol        = CMP1_INP3_CMP1_INP3;
    stcCmpInit.u8RefVol         = CMP_RVSL_INM4;
    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpInit.u8OutFilter      = CMP_OUT_FILTER_PCLKDIV32;
    stcCmpInit.u8OutPolarity    = CMP_OUT_REVERSE_OFF;
    CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpInit);
    /* Configuration for timer window function */
    stcCmptimerWindow.u16TWSelect      = CMP_TW_PWM;
    stcCmptimerWindow.u8TWInvalidLevel = CMP_TIMERWIN_INVALID_LEVEL_LOW;
    stcCmptimerWindow.u8TWOutLevel     = CMP_TIMERWIN_OUT_LEVEL_HIGH;
    CMP_TimerWindowConfig(CMP_TEST_UNIT, &stcCmptimerWindow);
    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /* Enable VCOUT */
    CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);
}

#if (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMRA)
/**
 * @brief  Configure TMRA.
 * @param  None
 * @retval None
 */
static void TMRAConfig(void)
{
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_cfg_t stcTrmaPwmCfg;

    /* Enable TMRA peripheral clock. */
    PWC_Fcg2PeriphClockCmd(TMRA_PERIP_CLK, Enable);

    /* Set a default initialization value for stcInit. */
    TMRA_StructInit(&stcTmraInit);
    /* Modifies the initialization values depends on the application. */
    stcTmraInit.u32ClkSrc       = TMRA_CLOCK;
    stcTmraInit.u32PCLKDiv       = TMRA_CLOCK_DIV;
    stcTmraInit.u32CntDir       = TMRA_DIR;
    stcTmraInit.u32CntMode      = TMRA_MODE;
    stcTmraInit.u32PeriodVal = TMRA_PERIOD_VAL;
    TMRA_Init(TMRA_UNIT, &stcTmraInit);
    /* Set compare value */
    TMRA_SetCmpVal(TMRA_UNIT, TMRA_CH, TMRA_PWM_A_CMP_VAL);
    GPIO_SetFunc(TMRA_PWM_A_PORT, TMRA_PWM_A_PIN, TMRA_PWM_A_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    //GPIO_OE(TMRA_PWM_A_PORT, TMRA_PWM_A_PIN, Enable); /* GPIO_E_09 output Enable */
    TMRA_PWM_StructInit(&stcTrmaPwmCfg);
    TMRA_PWM_Config(TMRA_UNIT, TMRA_CH, &stcTrmaPwmCfg);
    /* Enable PWM output */
    TMRA_PWM_Cmd(TMRA_UNIT, TMRA_CH, Enable);
    /* Starts TIMERA. */
    TMRA_Start(TMRA_UNIT);
}

#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR4)
/**
 * @brief  Configure TMR4.
 * @param  None
 * @retval None
 */
static void TMR4Config(void)
{
    uint32_t u32PwmCh;
    uint32_t u32OcoLowCh = TMR4_OCO_UH + 1UL;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;

    /* Enable TMR4 peripheral clock */
    PWC_Fcg2PeriphClockCmd(TMR4_PERIP_CLK, Enable);

    /* Initialize TIMER4 Counter */
    TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClkDiv = TMR4_CNT_CLK_DIV512;
    stcTmr4CntInit.u16CycleVal = TMR4_CNT_CYCLE_VAL;
    TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);
    /* Initialize TIMER4 OCO high&&low channel */
    TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16OcoInvalidOp = TMR4_OCO_INVAILD_OP_LOW;
    stcTmr4OcoInit.u16CompareVal = stcTmr4CntInit.u16CycleVal/2U;

    TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_UH, &stcTmr4OcoInit);
    TMR4_OCO_IntCmd(TMR4_UNIT, TMR4_OCO_UH, TMR4_OCO_INT_MATCH, Enable);

    TMR4_OCO_Init(TMR4_UNIT, u32OcoLowCh, &stcTmr4OcoInit);
    TMR4_OCO_IntCmd(TMR4_UNIT, u32OcoLowCh, TMR4_OCO_INT_MATCH, Enable);

    if (!(TMR4_OCO_UH % 2UL))
    {
        /* OCMR[15:0] = 0x0FFF = b 0000 1111 1111 1111 */
        stcHighChCmpMode.OCMRx_f.OCFDCH = TMR4_OCO_OCF_SET;   /* bit[0] 1 */
        stcHighChCmpMode.OCMRx_f.OCFPKH = TMR4_OCO_OCF_SET;   /* bit[1] 1 */
        stcHighChCmpMode.OCMRx_f.OCFUCH = TMR4_OCO_OCF_SET;   /* bit[2] 1 */
        stcHighChCmpMode.OCMRx_f.OCFZRH = TMR4_OCO_OCF_SET;   /* bit[3] 1 */

        stcHighChCmpMode.OCMRx_f.OPDCH = TMR4_OCO_OP_INVERT;  /* Bit[5:4]    11 */
        stcHighChCmpMode.OCMRx_f.OPPKH = TMR4_OCO_OP_INVERT;  /* Bit[7:6]    11 */
        stcHighChCmpMode.OCMRx_f.OPUCH = TMR4_OCO_OP_INVERT;  /* Bit[9:8]    11 */
        stcHighChCmpMode.OCMRx_f.OPZRH = TMR4_OCO_OP_INVERT;  /* Bit[11:10]  11 */
        stcHighChCmpMode.OCMRx_f.OPNPKH = TMR4_OCO_OP_HOLD;   /* Bit[13:12]  00 */
        stcHighChCmpMode.OCMRx_f.OPNZRH = TMR4_OCO_OP_HOLD;   /* Bit[15:14]  00 */
        stcHighChCmpMode.u16ExtendMatch = TMR4_OCO_EXTEND_MATCH_DISABLE;
        TMR4_OCO_SetHighChCompareMode(TMR4_UNIT, TMR4_OCO_UH, &stcHighChCmpMode);  /* Set OCO high channel compare mode */
    }

    if (u32OcoLowCh % 2UL)
    {
        /* OCMR[31:0] 0x0FF0 0FFF = b 0000 1111 1111 0000   0000 1111 1111 1111 */
        stcLowChCmpMode.OCMRx_f.OCFDCL = TMR4_OCO_OCF_SET;    /* bit[0] 1 */
        stcLowChCmpMode.OCMRx_f.OCFPKL = TMR4_OCO_OCF_SET;    /* bit[1] 1 */
        stcLowChCmpMode.OCMRx_f.OCFUCL = TMR4_OCO_OCF_SET;    /* bit[2] 1 */
        stcLowChCmpMode.OCMRx_f.OCFZRL = TMR4_OCO_OCF_SET;    /* bit[3] 1 */

        stcLowChCmpMode.OCMRx_f.OPDCL = TMR4_OCO_OP_INVERT;   /* bit[5:4]    11 */
        stcLowChCmpMode.OCMRx_f.OPPKL = TMR4_OCO_OP_INVERT;   /* bit[7:6]    11 */
        stcLowChCmpMode.OCMRx_f.OPUCL = TMR4_OCO_OP_INVERT;   /* bit[9:8]    11 */
        stcLowChCmpMode.OCMRx_f.OPZRL = TMR4_OCO_OP_INVERT;   /* bit[11:10]  11 */
        stcLowChCmpMode.OCMRx_f.OPNPKL = TMR4_OCO_OP_HOLD;    /* bit[13:12]  00 */
        stcLowChCmpMode.OCMRx_f.OPNZRL = TMR4_OCO_OP_HOLD;    /* bit[15:14]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNDCL = TMR4_OCO_OP_HOLD;   /* bit[17:16]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNUCL = TMR4_OCO_OP_HOLD;   /* bit[19:18]  00 */
        stcLowChCmpMode.OCMRx_f.EOPDCL = TMR4_OCO_OP_INVERT;  /* bit[21:20]  11 */
        stcLowChCmpMode.OCMRx_f.EOPPKL = TMR4_OCO_OP_INVERT;  /* bit[23:22]  11 */
        stcLowChCmpMode.OCMRx_f.EOPUCL = TMR4_OCO_OP_INVERT;  /* bit[25:24]  11 */
        stcLowChCmpMode.OCMRx_f.EOPZRL = TMR4_OCO_OP_INVERT;  /* bit[27:26]  11 */
        stcLowChCmpMode.OCMRx_f.EOPNPKL = TMR4_OCO_OP_HOLD;   /* bit[29:28]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNZRL = TMR4_OCO_OP_HOLD;   /* bit[31:30]  00 */
        stcLowChCmpMode.u16ExtendMatch = TMR4_OCO_EXTEND_MATCH_DISABLE;
        TMR4_OCO_SetLowChCompareMode(TMR4_UNIT, u32OcoLowCh, &stcLowChCmpMode);  /* Set OCO low channel compare mode */
    }

    /* Initialize PWM I/O */
    GPIO_SetFunc(TMR4_OUH_PORT, TMR4_OUH_PIN, TMR4_OUH_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(TMR4_OUL_PORT, TMR4_OUL_PIN, TMR4_OUL_GPIO_FUNC, PIN_SUBFUNC_DISABLE);

    /* Timer4 PWM: Get pwm couple channel */
    u32PwmCh = TMR4_PWM_CH(TMR4_OCO_UH);

    /* Initialize Timer4 PWM */
    TMR4_PWM_StructInit(&stcTmr4PwmInit);
    TMR4_PWM_Init(TMR4_UNIT, u32PwmCh, &stcTmr4PwmInit);

    /* Start TIMER4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

}

#elif (CMP_TW_PWM_SOURCE == CMP_TW_PWM_TMR6)
/**
 * @brief  Configure TMR6.
 * @param  None
 * @retval None
 */
static void TMR6Config(void)
{
    stc_tmr6_basecnt_cfg_t         stcTIM6BaseCntCfg;
    stc_tmr6_port_output_cfg_t     stcTIM6PortOutCfg;
    stc_gpio_init_t                stcGpioInit;

    TMR6_BaseCntStructInit(&stcTIM6BaseCntCfg);
    TMR6_PortOutputStructInit(&stcTIM6PortOutCfg);
    GPIO_StructInit(&stcGpioInit);

    PWC_Fcg2PeriphClockCmd(TMR6_PERIP_CLK, Enable);

    /* Timer6 PWM output port configuration */
    GPIO_SetFunc(TMR6_1_PWMA_PORT, TMR6_1_PWMA_PIN, GPIO_FUNC_3_TIM61_PWMA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(TMR6_1_PWMB_PORT, TMR6_1_PWMB_PIN, GPIO_FUNC_3_TIM61_PWMB, PIN_SUBFUNC_DISABLE);

    TMR6_CountCmd(M4_TMR6_1, Disable);
    /* Timer6 general count function configuration */
    stcTIM6BaseCntCfg.u32CntMode = TMR6_MODE_SAWTOOTH;
    stcTIM6BaseCntCfg.u32CntDir = TMR6_CNT_INCREASE;
    stcTIM6BaseCntCfg.u32CntClkDiv = TMR6_CLK_PCLK0_DIV128;
    stcTIM6BaseCntCfg.u32CntStpAftOvf = TMR6_CNT_CONTINUOUS;
    TMR6_Init(TMR6_UNIT, &stcTIM6BaseCntCfg);

    /* Period register set */
    TMR6_SetPeriodReg(TMR6_UNIT, TMR6_PERIOD_REG_A, TMR6_PERIOD_VAL);

    /* Set General Compare RegisterA Value */
    TMR6_SetGenCmpReg(TMR6_UNIT, TMR6_CMP_REG_A, TMR6_CPMPARE_VAl);

    /* Set General Compare RegisterB Value */
    TMR6_SetGenCmpReg(TMR6_UNIT, TMR6_CMP_REG_B, TMR6_CPMPARE_VAl);

     /* Configurate PWM output */
    stcTIM6PortOutCfg.u32PortMode = TMR6_PORT_COMPARE_OUTPUT;
    stcTIM6PortOutCfg.u32NextPeriodForceStd = TMR6_FORCE_PORT_OUTPUT_INVALID;
    stcTIM6PortOutCfg.u32DownCntMatchAnotherCmpRegStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32UpCntMatchAnotherCmpRegStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32DownCntMatchCmpRegStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32UpCntMatchCmpRegStd = TMR6_PORT_OUTPUT_STD_HIGH;
    stcTIM6PortOutCfg.u32UnderflowStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32OverflowStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32StopStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32StartStd = TMR6_PORT_OUTPUT_STD_LOW;
    TMR6_PortOutputConfig(TMR6_UNIT, TMR6_IO_PWMA, &stcTIM6PortOutCfg);

    TMR6_PortOutputConfig(TMR6_UNIT, TMR6_IO_PWMB, &stcTIM6PortOutCfg);

    /* Start timer6 */
    TMR6_CountCmd(TMR6_UNIT, Enable);

}
#endif
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
