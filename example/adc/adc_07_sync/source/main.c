/**
 *******************************************************************************
 * @file  adc/adc_07_sync/source/main.c
 * @brief Main program ADC synchronous for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-12       Wuze            First version
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
 * @addtogroup ADC_Sync
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* 'ADC_SYNC_ADC1_ADC2' and 'ADC_SYNC_ADC1_ADC2_ADC3' can be used. */
#define APP_SYNC_UNITS                      (ADC_SYNC_ADC1_ADC2_ADC3)

/* ADC synchronous mode. */
#define APP_SYNC_MODE_SSHOT_SEQUENTIAL      (0U)
#define APP_SYNC_MODE_SSHOT_SIMULTANEOUS    (1U)
#define APP_SYNC_MODE_CONT_SEQUENTIAL       (2U)
#define APP_SYNC_MODE_CONT_SIMULTANEOUS     (3U)

#define APP_SYNC_MODE                       (APP_SYNC_MODE_CONT_SEQUENTIAL)

#if (APP_SYNC_MODE == APP_SYNC_MODE_SSHOT_SEQUENTIAL)
    #define APP_ADC_SYNC_MODE               (ADC_SYNC_SSHOT_SEQUENTIAL)
    #define APP_ADC_SYNC_SAMPLE_TIME        (11U)
    #define APP_ADC_SYNC_TRIG_DELAY         (12U)
    #define APP_ADC_MODE                    (ADC_MODE_SA_CONT)

#elif (APP_SYNC_MODE == APP_SYNC_MODE_SSHOT_SIMULTANEOUS)
    #define APP_ADC_SYNC_MODE               (ADC_SYNC_SSHOT_SIMULTANEOUS)
    #define APP_ADC_SYNC_SAMPLE_TIME        (11U)
    #define APP_ADC_SYNC_TRIG_DELAY         (11U)
    #define APP_ADC_MODE                    (ADC_MODE_SA_SSHOT)

#elif (APP_SYNC_MODE == APP_SYNC_MODE_CONT_SEQUENTIAL)
    #define APP_ADC_SYNC_MODE               (ADC_SYNC_CONT_SEQUENTIAL)
    #define APP_ADC_SYNC_SAMPLE_TIME        (11U)
    #define APP_ADC_SYNC_TRIG_DELAY         (17U)
    #define APP_ADC_MODE                    (ADC_MODE_SA_SSHOT)

#else /* (APP_SYNC_MODE == APP_SYNC_MODE_CONT_SIMULTANEOUS) */
    #define APP_ADC_SYNC_MODE               (ADC_SYNC_CONT_SIMULTANEOUS)
    #define APP_ADC_SYNC_SAMPLE_TIME        (11U)
    #define APP_ADC_SYNC_TRIG_DELAY         (40U)
    #define APP_ADC_MODE                    (ADC_MODE_SA_SSHOT)

#endif /* #if (APP_SYNC_MODE == APP_SYNC_MODE_SSHOT_SEQUENTIAL) */

/* ADC peripheral clock for this example. */
#if (APP_SYNC_UNITS == ADC_SYNC_ADC1_ADC2)
    #define APP_ADC_PERIP_CLK               (PWC_FCG3_ADC1 | PWC_FCG3_ADC2)
#else
    #define APP_ADC_PERIP_CLK               (PWC_FCG3_ADC1 | PWC_FCG3_ADC2 | PWC_FCG3_ADC3)
#endif

/* 
 * ADC channels definition for this example.
 * NOTE!!! DO NOT enable sequence B, otherwise it will disturb the synchronization timing.
 */
#define APP_ADC_SA_CH                       (ADC_CH0)
#define APP_ADC_SA_CH_COUNT                 (1U)

/* ADC channel sampling time.                        ADC_CH0 */
#define APP_ADC_SA_SAMPLE_TIME              { APP_ADC_SYNC_SAMPLE_TIME }

/* 
 * Trigger source definitions.
 * Set pin ADTRG1(PE7) to trigger sequence A. Make a falling edge on ADTRG1 and hold the low level \
 *   at least 1.5 cycles of PCLK4 to trigger sequence A.
 * Both sequences can be set triggered by event or the falling edge of pin ADTRGx(x is ADC unit number, x=1, 2, 3).
 * Only the falling edge of pin ADTRGx and the low level of pin ADTRGx must be held at least 1.5 cycles of PCLK4 can trigger ADC start sampling.
 * ADTRG1: PB7, PD6, PD14, PE7.
 */
#define APP_ADC_SA_TRIG_SRC_TYPE            (ADC_TRIG_SRC_ADTRG)
#define APP_ADC_SA_TRIG_SRC_PORT            (GPIO_PORT_E)
#define APP_ADC_SA_TRIG_SRC_PIN             (GPIO_PIN_07)
#define APP_ADC_SA_TRIG_PIN_FUNC            (GPIO_FUNC_1_ADTRG)

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         printf
#else
#define DBG(...)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);

static void AdcConfig(void);
static void AdcClockConfig(void);
static void AdcInitConfig(void);
static void AdcChannelConfig(void);
static void AdcSyncConfig(void);
static void AdcTrigSrcConfig(void);

static void AdcSetChannelPinAnalogMode(const M4_ADC_TypeDef *ADCx, uint32_t u32Channel);
static void AdcSetPinAnalogMode(const M4_ADC_TypeDef *ADCx, uint8_t u8PinNum);

static void IndicateConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*static uint16_t m_au16AdcSaVal[APP_ADC_SA_CH_COUNT];*/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_07_sync project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configures the PLLHP(240MHz) as the system clock. */
    SystemClockConfig();

#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */

    /* Configures ADC. */
    AdcConfig();

    /* Use TIMERA's PWM to indicate the scan timing of ADC synchronous mode. */
    IndicateConfig();

    /***************** Configuration end, application start **************/

    while (1u)
    {
    }
}

/**
 * @brief  Configures the PLLHP(240MHz) as the system clock.
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
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV4 | CLK_EXCLK_DIV2 | \
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

    /* Set EFM wait cycle. 5 wait cycles needed when system clock is 240MHz */
    EFM_Unlock();
    EFM_SetWaitCycle(EFM_WAIT_CYCLE_5);
    EFM_Lock();

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  ADC configuration, including clock configuration, initial configuration
 *         and channel configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcClockConfig();
    AdcInitConfig();
    AdcChannelConfig();
    AdcSyncConfig();
    AdcTrigSrcConfig();
}

/**
 * @brief  Configures ADC clock.
 * @param  None
 * @retval None
 */
static void AdcClockConfig(void)
{
    /*
     * Specify the clock source of ADC.
     * 'CLK_PERI_CLK_PCLK' , 'CLK_PERI_CLK_PLLHQ' and 'CLK_PERI_CLK_PLLHR' can be used.
     */
    CLK_PERI_ClkConfig(CLK_PERI_CLK_PLLHQ);
}

/**
 * @brief  Initializes ADC.
 * @param  None
 * @retval None
 */
static void AdcInitConfig(void)
{
    stc_adc_init_t stcInit;

    /* Set a default value. */
    ADC_StructInit(&stcInit);

    /* 1. Modify the default value depends on the application. It is not needed in this example. */
    stcInit.u16ScanMode = APP_ADC_MODE;

    /* 2. Enable ADC peripheral clock. */
    PWC_Fcg3PeriphClockCmd(APP_ADC_PERIP_CLK, Enable);

    /* 3. Initializes ADC. */
    ADC_Init(M4_ADC1, &stcInit);
    ADC_Init(M4_ADC2, &stcInit);

#if (APP_SYNC_UNITS == ADC_SYNC_ADC1_ADC2_ADC3)
    ADC_Init(M4_ADC3, &stcInit);
#endif
}

/**
 * @brief  Configures ADC channel(s).
 * @param  None
 * @retval None
 */
static void AdcChannelConfig(void)
{
    uint8_t au8AdcSASplTime[] = APP_ADC_SA_SAMPLE_TIME;

    /* 1. Set the ADC pin to analog input mode. */
    AdcSetChannelPinAnalogMode(M4_ADC1, APP_ADC_SA_CH);

    /* 2. Enable the ADC channels. */
    ADC_ChannelCmd(M4_ADC1, ADC_SEQ_A, \
                   APP_ADC_SA_CH, au8AdcSASplTime, \
                   Enable);

    ADC_ChannelCmd(M4_ADC2, ADC_SEQ_A, \
                   APP_ADC_SA_CH, au8AdcSASplTime, \
                   Enable);

#if (APP_SYNC_UNITS == ADC_SYNC_ADC1_ADC2_ADC3)
    ADC_ChannelCmd(M4_ADC3, ADC_SEQ_A, \
                   APP_ADC_SA_CH, au8AdcSASplTime, \
                   Enable);
#endif
}

/**
 * @brief  Synchronous mode configuration.
 * @param  None
 * @retval None
 */
static void AdcSyncConfig(void)
{
    ADC_SYNC_Config(APP_SYNC_UNITS, APP_ADC_SYNC_MODE, APP_ADC_SYNC_TRIG_DELAY);
    ADC_SYNC_Cmd(Enable);
}

/**
 * @brief  Trigger source configuration. Specify trigger source synchronous mode.
 * @param  None
 * @retval None
 */
static void AdcTrigSrcConfig(void)
{
    stc_adc_trig_cfg_t stcTrigCfg;

    /*
     * Configures the trigger source of sequence A.
     * One of ADTRGx(x is the ADC unit number, x=1, 2, 3) pins is configured to trigger sequence A.
     * Make a falling edge on ADTRGx and hold the low level at least 1.5 PCLK4 cycles to trigger sequence A.
     */
    ADC_TrigSrcStructInit(&stcTrigCfg);
    stcTrigCfg.u16TrigSrc = APP_ADC_SA_TRIG_SRC_TYPE;
    GPIO_SetFunc(APP_ADC_SA_TRIG_SRC_PORT, APP_ADC_SA_TRIG_SRC_PIN, \
                 APP_ADC_SA_TRIG_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    ADC_TrigSrcConfig(M4_ADC1, ADC_SEQ_A, &stcTrigCfg);
    ADC_TrigSrcCmd(M4_ADC1, ADC_SEQ_A, Enable);
}

/**
 * @brief  Set the pin(s) corresponding to the specified channel(s) to analog mode.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u32Channel             The specified channel(s).
 * @retval None
 */
static void AdcSetChannelPinAnalogMode(const M4_ADC_TypeDef *ADCx, uint32_t u32Channel)
{
    uint8_t u8PinNum;

    u8PinNum = 0u;
    while (u32Channel != 0u)
    {
        if (u32Channel & 0x1u)
        {
            AdcSetPinAnalogMode(ADCx, u8PinNum);
        }

        u32Channel >>= 1u;
        u8PinNum++;
    }
}

/**
 * @brief  Set specified ADC pin to analog mode.
 * @param  [in]  ADCx                   Pointer to ADC instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_ADC1:                     ADC unit 1 instance register base.
 *   @arg  M4_ADC2:                     ADC unit 2 instance register base.
 *   @arg  M4_ADC3:                     ADC unit 3 instance register base.
 * @param  [in]  u8PinNum               The ADC pin number.
 *                                      This parameter can be a value of @ref ADC_Pin_Number
 * @retval None
 */
static void AdcSetPinAnalogMode(const M4_ADC_TypeDef *ADCx, uint8_t u8PinNum)
{
    typedef struct
    {
        uint8_t  u8Port;
        uint16_t u16Pin;
    } stc_adc_pin_t;

    stc_gpio_init_t stcGpioInit;

    stc_adc_pin_t astcADC12[ADC1_CH_COUNT] = { \
            {GPIO_PORT_A, GPIO_PIN_00}, {GPIO_PORT_A, GPIO_PIN_01}, \
            {GPIO_PORT_A, GPIO_PIN_02}, {GPIO_PORT_A, GPIO_PIN_03}, \
            {GPIO_PORT_A, GPIO_PIN_04}, {GPIO_PORT_A, GPIO_PIN_05}, \
            {GPIO_PORT_A, GPIO_PIN_06}, {GPIO_PORT_A, GPIO_PIN_07}, \
            {GPIO_PORT_B, GPIO_PIN_00}, {GPIO_PORT_B, GPIO_PIN_01}, \
            {GPIO_PORT_C, GPIO_PIN_00}, {GPIO_PORT_C, GPIO_PIN_01}, \
            {GPIO_PORT_C, GPIO_PIN_02}, {GPIO_PORT_C, GPIO_PIN_03}, \
            {GPIO_PORT_C, GPIO_PIN_04}, {GPIO_PORT_C, GPIO_PIN_05}, \
    };
    stc_adc_pin_t astcADC3[ADC3_CH_COUNT] = { \
            {GPIO_PORT_A, GPIO_PIN_00}, {GPIO_PORT_A, GPIO_PIN_01}, \
            {GPIO_PORT_A, GPIO_PIN_02}, {GPIO_PORT_A, GPIO_PIN_03}, \
            {GPIO_PORT_F, GPIO_PIN_06}, {GPIO_PORT_F, GPIO_PIN_07}, \
            {GPIO_PORT_F, GPIO_PIN_08}, {GPIO_PORT_F, GPIO_PIN_09}, \
            {GPIO_PORT_F, GPIO_PIN_10}, {GPIO_PORT_F, GPIO_PIN_03}, \
            {GPIO_PORT_C, GPIO_PIN_00}, {GPIO_PORT_C, GPIO_PIN_01}, \
            {GPIO_PORT_C, GPIO_PIN_02}, {GPIO_PORT_C, GPIO_PIN_03}, \
            {GPIO_PORT_F, GPIO_PIN_04}, {GPIO_PORT_F, GPIO_PIN_05}, \
            {GPIO_PORT_H, GPIO_PIN_02}, {GPIO_PORT_H, GPIO_PIN_03}, \
            {GPIO_PORT_H, GPIO_PIN_04}, {GPIO_PORT_H, GPIO_PIN_05}, \
    };

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;

    if ((ADCx == M4_ADC1) || (ADCx == M4_ADC2))
    {
        GPIO_Init(astcADC12[u8PinNum].u8Port, astcADC12[u8PinNum].u16Pin, &stcGpioInit);
    }
    else
    {
        GPIO_Init(astcADC3[u8PinNum].u8Port, astcADC3[u8PinNum].u16Pin, &stcGpioInit);
    }
}

/**
 * @brief  Use TIMERA's PWM to indicate the scan timing of ADC synchronous mode.
 *         The inversion of PWM level indicates the end of ADC scanning.
 *         ADC1: PE11
 *         ADC2: PB10
 *         ADC3: PE15
 * @param  None
 * @retval None
 */
static void IndicateConfig(void)
{
    stc_tmra_init_t stcTmrAInit;
    stc_tmra_pwm_cfg_t stcPwmCfg;

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_AOS, Enable);
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMRA_1 | PWC_FCG2_TMRA_2 | PWC_FCG2_TMRA_7, Enable);

    TMRA_StructInit(&stcTmrAInit);
    stcTmrAInit.u32ClkSrc    = TMRA_CLK_EVENT;
    stcTmrAInit.u32PeriodVal = 0U;
    TMRA_Init(M4_TMRA_1, &stcTmrAInit);
    TMRA_Init(M4_TMRA_2, &stcTmrAInit);
    TMRA_Init(M4_TMRA_7, &stcTmrAInit);
    TMRA_SetCntEvent(M4_TMRA_1, EVT_ADC1_EOCA);
    TMRA_SetCntEvent(M4_TMRA_2, EVT_ADC2_EOCA);
    TMRA_SetCntEvent(M4_TMRA_7, EVT_ADC3_EOCA);

    TMRA_SetFuncMode(M4_TMRA_1, TMRA_CH_2, TMRA_FUNC_COMPARE);
    TMRA_SetFuncMode(M4_TMRA_2, TMRA_CH_3, TMRA_FUNC_COMPARE);
    TMRA_SetFuncMode(M4_TMRA_7, TMRA_CH_4, TMRA_FUNC_COMPARE);

    TMRA_SetCmpVal(M4_TMRA_1, TMRA_CH_2, 0UL);
    TMRA_SetCmpVal(M4_TMRA_2, TMRA_CH_3, 0UL);
    TMRA_SetCmpVal(M4_TMRA_7, TMRA_CH_4, 0UL);

    TMRA_PWM_StructInit(&stcPwmCfg);
    TMRA_PWM_Config(M4_TMRA_1, TMRA_CH_2, &stcPwmCfg);
    TMRA_PWM_Config(M4_TMRA_2, TMRA_CH_3, &stcPwmCfg);
    TMRA_PWM_Config(M4_TMRA_7, TMRA_CH_4, &stcPwmCfg);

    TMRA_PWM_Cmd(M4_TMRA_1, TMRA_CH_2, Enable);
    TMRA_PWM_Cmd(M4_TMRA_2, TMRA_CH_3, Enable);
    TMRA_PWM_Cmd(M4_TMRA_7, TMRA_CH_4, Enable);

    GPIO_SetFunc(GPIO_PORT_E, GPIO_PIN_11, \
                 GPIO_FUNC_4_TIMA1_PWM2, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(GPIO_PORT_B, GPIO_PIN_10, \
                 GPIO_FUNC_4_TIMA2_PWM3, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(GPIO_PORT_E, GPIO_PIN_15, \
                 GPIO_FUNC_4_TIMA7_PWM4, PIN_SUBFUNC_DISABLE);

    TMRA_Start(M4_TMRA_1);
    TMRA_Start(M4_TMRA_2);
    TMRA_Start(M4_TMRA_7);
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
