/**
 *******************************************************************************
 * @file  ots/ots_base/source/main.c
 * @brief Main program OTS base for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-21       Wuze            First version
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
 * @addtogroup OTS_Base
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
 * This example is going to get the temperature of the chip inside.
 */

/*
 * Specifies a clock source for OTS in this example.
 * 'APP_OTS_CLK' can be defined as 'OTS_CLK_XTAL' or 'OTS_CLK_HRC'. */
#define APP_OTS_CLK                         (OTS_CLK_XTAL)

/*
 * Function control of OTS.
 * Defines the following macro as non-zero to enable the corresponding function.
 *
 * 'APP_OTS_USE_INTERRUPT': Interrupt function control.
 * 'APP_OTS_USE_TRIG': Hardware trigger conditions control. The conditions that used to start OTS.
 */
#define APP_OTS_USE_TRIG                    (0U)

#if (APP_OTS_USE_TRIG > 0U)
    #define APP_OTS_USE_INTERRUPT           (APP_OTS_USE_TRIG)
#else
    #define APP_OTS_USE_INTERRUPT           (0U)
#endif

/*
 * Definitions about OTS interrupt for the example.
 * OTS independent IRQn: [Int000_IRQn, Int031_IRQn], [Int116_IRQn, Int121_IRQn].
 */
#if (APP_OTS_USE_INTERRUPT > 0U)
    #define APP_OTS_INT_PRIO                (DDL_IRQ_PRIORITY_03)
    #define APP_OTS_INT_SRC                 (INT_OTS)
    #define APP_OTS_IRQn                    (Int116_IRQn)
#endif /* #if (APP_OTS_USE_INTERRUPT > 0U) */

/* OTS parameters. */
#define OTS_XTAL_K                          (737272.7273f)
#define OTS_XTAL_M                          (27.549f)
#define OTS_HRC_K                           (0.0f)
#define OTS_HRC_M                           (0.0f)

/* Timeout value. */
#define TIMEOUT_MS                          (500U)

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

static void OtsConfig(void);
static void OtsInitConfig(void);
static void OtsClkConfig(void);

#if (APP_OTS_USE_INTERRUPT > 0U)
    static void OtsIrqConfig(void);
    static void OTS_IrqCallback(void);
#endif

#if (APP_OTS_USE_TRIG > 0U)
    static void OtsTrigConfig(void);
#endif

#if ((APP_OTS_USE_INTERRUPT > 0U) || (APP_OTS_USE_TRIG > 0U))
    static void OtsStart(void);
#endif

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__UNUSED static float32_t m_f32Temperature;

#if (APP_OTS_USE_INTERRUPT > 0U)
static uint8_t m_u8OtsIntFlag = 0U;
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of ots_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* The system clock is MRC(8MHz) by default. */

#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */

    /* Configures OTS. */
    OtsConfig();

#if ((APP_OTS_USE_INTERRUPT > 0U) || (APP_OTS_USE_TRIG > 0U))
    /* Starts OTS. */
    OtsStart();
#endif

    /***************** Configuration end, application start **************/

    while (1U)
    {
#if (APP_OTS_USE_INTERRUPT > 0U)
        if (m_u8OtsIntFlag != 0U)
        {
            m_u8OtsIntFlag = 0U;
            DBG("\nTemperature: %.2f", m_f32Temperature);
        }
#else
        OTS_Polling(&m_f32Temperature, TIMEOUT_MS);
        DBG("\nTemperature: %.2f", m_f32Temperature);
        m_f32Temperature = 0.0f;
        DDL_Delay1ms(1000U);
#endif
    }
}

/**
 * @brief  OTS configuration.
 * @param  None
 * @retval None
 */
static void OtsConfig(void)
{
    OtsInitConfig();
    OtsClkConfig();
}

/**
 * @brief  OTS initialization configuration.
 * @param  None
 * @retval None
 */
static void OtsInitConfig(void)
{
    stc_ots_init_t stcInit;

    OTS_StructInit(&stcInit);
    stcInit.u16ClkSel = APP_OTS_CLK;
#if (APP_OTS_CLK == OTS_CLK_XTAL)
    stcInit.f32ParaK  = OTS_XTAL_K;
    stcInit.f32ParaM  = OTS_XTAL_M;
#else
    stcInit.f32ParaK  = OTS_HRC_K;
    stcInit.f32ParaM  = OTS_HRC_M;
#endif

    /* 1. Enable OTS peripheral clock. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_OTS, Enable);

    /* 2. Initialize OTS. */
    OTS_Init(&stcInit);

#if (APP_OTS_USE_INTERRUPT > 0U)
    OtsIrqConfig();
#endif

#if (APP_OTS_USE_TRIG > 0U)
    OtsTrigConfig();
#endif
}

/**
 * @brief  OTS clock configuration.
 * @param  None
 * @retval None
 */
static void OtsClkConfig(void)
{
#if (APP_OTS_CLK == OTS_CLK_HRC)
    /* 1. Enable HRC for OTS. */
    CLK_HrcCmd(Enable);
    /* 2. Enable XTAL32 when clock source of OTS is HRC. */
    CLK_Xtal32Cmd(Enable);
#else
    /* Enable XTAL for OTS. */
    CLK_XtalCmd(Enable);
#endif

    /* Enable LRC for OTS. */
    CLK_LrcCmd(Enable);
}

#if (APP_OTS_USE_INTERRUPT > 0U)
/**
 * @brief  OTS interrupt configuration.
 * @param  None
 * @retval None
 */
static void OtsIrqConfig(void)
{
    stc_irq_signin_config_t stcCfg;

    stcCfg.enIntSrc    = APP_OTS_INT_SRC;
    stcCfg.enIRQn      = APP_OTS_IRQn;
    stcCfg.pfnCallback = &OTS_IrqCallback;

    /* Independent interrupt. */
    INTC_IrqSignIn(&stcCfg);
    NVIC_ClearPendingIRQ(stcCfg.enIRQn);
    NVIC_SetPriority(stcCfg.enIRQn, APP_OTS_INT_PRIO);
    NVIC_EnableIRQ(stcCfg.enIRQn);

    /* Enable the specified interrupts of OTS. */
    OTS_IntCmd(Enable);
}

/**
 * @brief  OTS interrupt callback function.
 * @param  None
 * @retval None
 */
void OTS_IrqCallback(void)
{
    m_f32Temperature = OTS_CalculateTemp();
    m_u8OtsIntFlag = 1U;
}
#endif /* #if (APP_OTS_USE_INTERRUPT > 0U) */

#if (APP_OTS_USE_TRIG > 0U)
/**
 * @brief  Specifies event 'EVT_TMR2_1_CMPA' of TIMER2 uint 1 channel A as the trigger source event of OTS. \
 *         Event 'EVT_TMR2_1_CMPA' occurs each second.
 * @param  None
 * @retval None
 */
static void OtsTrigConfig(void)
{
    /*
     * If a peripheral is used to generate the event which is used as a start trigger condition of OTS, \
     *     call the API of the peripheral to configure the peripheral.
     * The following operations are only used in this example.
     */

    stc_tmr2_init_t stcInit;

    /* Initials TIMER2. */
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR2_1, Enable);
    TMR2_StructInit(&stcInit);
    stcInit.u32ClkSrc = TMR2_CLK_SYNC_PCLK1;
    stcInit.u32ClkDiv = TMR2_CLK_DIV_256;
    stcInit.u32CmpVal = 31250UL;
    TMR2_Init(M4_TMR2_1, TMR2_CH_A, &stcInit);

    /* Specifies event 'EVT_TMR2_1_CMPA' as the trigger source event of OTS. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_AOS, Enable);
    OTS_SetTrigEvent(EVT_TMR2_1_CMPA);
}

#endif /* #if (APP_OTS_USE_TRIG > 0U) */

#if ((APP_OTS_USE_INTERRUPT > 0U) || (APP_OTS_USE_TRIG > 0U))
/**
 * @brief  Start OTS.
 * @param  None
 * @retval None
 */
static void OtsStart(void)
{
    /*
     * If a peripheral is used to generate the event which is used as a start trigger condition of OTS, \
     *     call the API of the peripheral to start the peripheral here or anywhere else you need.
     * The following operations are only used in this example.
     */

#if (APP_OTS_USE_TRIG > 0U)
    TMR2_Start(M4_TMR2_1, TMR2_CH_A);
#elif (APP_OTS_USE_INTERRUPT > 0U)
    OTS_Start();
#endif
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
