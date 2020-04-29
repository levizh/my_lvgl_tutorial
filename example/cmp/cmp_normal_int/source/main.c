/**
 *******************************************************************************
 * @file  cmp/cmp_normal_int/source/main.c
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
 * @addtogroup CMP_Normal_Int
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
/* CMP1 compare voltage  INP2_PGA1 */
#define CMP1_INP2_PGA1_PORT             (GPIO_PORT_A)
#define CMP1_INP2_PGA1_PIN              (GPIO_PIN_00)
/* CMP1 reference voltage  CMP123_INM3*/
#define CMP1_CMP123_INM3_PORT           (GPIO_PORT_A)
#define CMP1_CMP123_INM3_PIN            (GPIO_PIN_07)
/* CMP1_VCOUT1*/
#define CMP1_VCOUT1_PORT                (GPIO_PORT_B)
#define CMP1_VCOUT1_PIN                 (GPIO_PIN_12)

/* Define for RGB LED */
#define LED_R_PORT                      (GPIO_PORT_A)
#define LED_G_PORT                      (GPIO_PORT_B)
#define LED_B_PORT                      (GPIO_PORT_C)
#define LED_R_PIN                       (GPIO_PIN_00)
#define LED_G_PIN                       (GPIO_PIN_01)
#define LED_B_PIN                       (GPIO_PIN_01)

#define LED_B_Set()                     (GPIO_SetPins(LED_B_PORT, LED_B_PIN))
#define LED_B_Reset()                   (GPIO_ResetPins(LED_B_PORT, LED_B_PIN))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);
static void CMP1_IrqCallback(void);
static void PgaConfig(void);
static void CmpConfig(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of cmp_normal_int project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqRegCfg;

    /* Configure system clock. */
    SystemClockConfig();

    /* RGB LED Config */
    LedConfig();

    /* PGA Config */
    PgaConfig();

    /* CMP Config */
    CmpConfig();

    /*NVIC configuration for interrupt */
    stcIrqRegCfg.enIRQn = Int010_IRQn;
    stcIrqRegCfg.enIntSrc = INT_CMP1;
    stcIrqRegCfg.pfnCallback = &CMP1_IrqCallback;
    INTC_IrqSignIn(&stcIrqRegCfg);
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(stcIrqRegCfg.enIRQn);

    /* Configuration finished */
    while(1)
    {
        ;
    }
}

/**
 * @brief  CMP1 interrupt call back
 * @param  None
 * @retval None
 */
static void CMP1_IrqCallback(void)
{
    if(Set == CMP_GetResult(CMP_TEST_UNIT))
    {
        LED_B_Set();
    }
    else
    {
        LED_B_Reset();
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
    stcXTALInit.u8XtalStb = CLK_XTALSTB_133US;

    /* Initialize XTAL clock */
    CLK_XtalInit(&stcXTALInit);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_XTAL);
}

/**
 * @brief  Configure RGB LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit = {0};

    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_B_PORT, LED_B_PIN, &stcGpioInit);
}

/**
 * @brief  Configure CMP.
 * @param  None
 * @retval None
 */
static void CmpConfig(void)
{
    stc_cmp_init_t stcCmpInit;
    stc_gpio_init_t stcGpioInit;
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_CMP1, Enable);
    /* Port function configuration for CMP*/
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(CMP1_INP2_PGA1_PORT, CMP1_INP2_PGA1_PIN, &stcGpioInit); /* CMP1 compare voltage */
    GPIO_Init(CMP1_CMP123_INM3_PORT, CMP1_CMP123_INM3_PIN, &stcGpioInit); /* CMP1 reference voltage */
    GPIO_SetFunc(CMP1_VCOUT1_PORT, CMP1_VCOUT1_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE); /* CMP1_VCOUT1 */

    /* Clear structure */
    CMP_StructInit(&stcCmpInit);

    /* Configuration for normal compare function */
    /*For CMP1 and Cmp3, when selecting channels inp2 and inp3, there are
    variety of compara voltage available, so you need to configure channels
    and voltage sources, and for others, you only need to configure channels*/
    stcCmpInit.u8CmpCh = CMP_CVSL_INP2;
    stcCmpInit.u16CmpVol = CMP1_INP2_PGA2;
    stcCmpInit.u8RefVol = CMP_RVSL_INM3;
    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpInit.u8OutFilter = CMP_OUT_FILTER_PCLKDIV32;
    stcCmpInit.u8OutPolarity = CMP_OUT_REVERSE_ON;
    CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpInit);

    /* Enable interrupt if need */
    CMP_IntCmd(CMP_TEST_UNIT, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /* Enable VCOUT if need */
    //CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);
}

/**
 * @brief  Configure PGA.
 * @param  None
 * @retval None
 */
static void PgaConfig(void)
{
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_ADC1, Enable);
    /* Config PGA */
    ADC_PGA_Config(ADC_PGA_1, ADC_PGA_GAIN_2, ADC_PGA_VSS_PGAVSS);
    /* Enable PGA */
    ADC_PGA_Cmd(ADC_PGA_1, Enable);
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
