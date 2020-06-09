/**
 *******************************************************************************
 * @file  cmp/cmp_window/source/main.c
 * @brief Main program of CMP for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-06       Heqb         First version
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
 * @addtogroup CMP_Window
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMP_TEST_UNIT1                  (M4_CMP1)
#define CMP_TEST_UNIT2                  (M4_CMP2)
#define DAC_TEST_UNIT                   (M4_DAC1)
#define CMP_PERIP_CLK                   (PWC_FCG3_CMP1)
/* Define port and pin of CMP */
/* CMP1 compare voltage CMP1_INP3 */
#define CMP1_INP3_PORT                  (GPIO_PORT_E)
#define CMP1_INP3_PIN                   (GPIO_PIN_10)
/* CMP2 compare voltage CMP2_INP2(PGA2) */
#define CMP2_INP2_PORT                  (GPIO_PORT_A)
#define CMP2_INP2_PIN                   (GPIO_PIN_01)
/* CMP1 reference low voltage CMP1_INM2(DAC1_OUT2)*/
#define CMP1_INM2_PORT                  (GPIO_PORT_A)
#define CMP1_INM2_PIN                   (GPIO_PIN_05)
/* CMP2 reference high voltage CMP2_INM1(DAC1_OUT1)*/
#define CMP2_INM1_PORT                  (GPIO_PORT_A)
#define CMP2_INM1_PIN                   (GPIO_PIN_04)
/* CMP2_VCOUT2*/
#define CMP2_VCOUT2_PORT                (GPIO_PORT_B)
#define CMP2_VCOUT2_PIN                 (GPIO_PIN_13)

/* LED_B */
#define LED_B_PORT                      (GPIO_PORT_E)
#define LED_B_PIN                       (GPIO_PIN_01)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void CmpConfig(void);
static void DacConfig(void);
static void LEDConfig(void);
static void PgaConfig(void);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t u16SinTable[2] = {1614U, 2234U};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of cmp_window project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* LED Init */
    LEDConfig();
    /* Configure system clock. */
    SystemClockConfig();
    /* Configure DAC */
    DacConfig();
    /* Configure PGA */
    PgaConfig();
    /* Configure CMP */
    CmpConfig();

    while(1)
    {
        if(GPIO_ReadInputPortPin(CMP2_VCOUT2_PORT, CMP2_VCOUT2_PIN))
        {
            GPIO_ResetPins(LED_B_PORT, LED_B_PIN);
        }
        else
        {
            GPIO_SetPins(LED_B_PORT, LED_B_PIN);
        }
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
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 | \
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
    EFM_SetWaitCycle(EFM_WAIT_CYCLE_5);   /* 5-wait @ 240MHz */
    EFM_Lock();

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
    stc_cmp_win_ref_t stcCmpWinRef;
    stc_gpio_init_t stcGpioInit;
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_CMBIAS, Enable);
    PWC_Fcg3PeriphClockCmd(CMP_PERIP_CLK, Enable);
    /* Port function configuration for CMP*/
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(CMP1_INP3_PORT, CMP1_INP3_PIN, &stcGpioInit); /* CMP compare voltage */
    GPIO_Init(CMP2_INP2_PORT, CMP2_INP2_PIN, &stcGpioInit);
    GPIO_Init(CMP1_INM2_PORT, CMP1_INM2_PIN, &stcGpioInit); /* CMP1 reference low voltage */
    GPIO_Init(CMP2_INM1_PORT, CMP2_INM1_PIN, &stcGpioInit); /* CMP2 reference high voltage */
    GPIO_SetFunc(CMP2_VCOUT2_PORT, CMP2_VCOUT2_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE); /* CMP2_VCOUT2 */

    /* Clear structure */
    CMP_StructInit(&stcCmpInit);

    /* Configuration for normal compare function */
    /*For CMP1 and CMP3, when selecting channels inp2 and inp3, there are
    variety of compara voltage available, so you need to configure channels
    and voltage sources, and for others, you only need to configure channels*/
    stcCmpWinRef.u8CmpCh1       = CMP_CVSL_INP3;
    stcCmpWinRef.u16CmpVol      = CMP1_INP3_CMP1_INP3;
    stcCmpWinRef.u8CmpCh2       = CMP_CVSL_INP2;
    stcCmpWinRef.u8WinVolHigh   = CMP_RVSL_INM1;
    stcCmpWinRef.u8WinVolLow    = CMP_RVSL_INM2;
    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpInit.u8OutFilter      = CMP_OUT_FILTER_PCLK3_DIV32;
    stcCmpInit.u8OutPolarity    = CMP_OUT_REVERSE_OFF;
    CMP_WindowModeInit(CMP_TEST_UNIT2, &stcCmpInit, &stcCmpWinRef);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT1, Enable);
    CMP_OutputCmd(CMP_TEST_UNIT2, Enable);

    /* Enable VCOUT */
    CMP_VCOUTCmd(CMP_TEST_UNIT2, Enable);
}

/**
 * @brief  Configure DAC.
 * @param  None
 * @retval None
 */
static void DacConfig(void)
{
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_DAC1, Enable);
    /*Config DAC1 */
    /* Right alignment of data */
    DAC_DataPatternConfig(DAC_TEST_UNIT, DAC_Align_12b_R);
    /* Write Data :V = (Conversion Data / 4096) * VREFH */
    DAC_SetChannel1Data(DAC_TEST_UNIT, u16SinTable[0U]);
    DAC_SetChannel2Data(DAC_TEST_UNIT, u16SinTable[1U]);
    /* Output Enable */
    DAC_ChannelAllCmd(DAC_TEST_UNIT, Enable);
    /* Start Convert */
    DAC_ChannelCmd(DAC_TEST_UNIT, DAC_Channel_1, Enable);
    DAC_ChannelCmd(DAC_TEST_UNIT, DAC_Channel_2, Enable);
}

/**
 * @brief  Configure LED.
 * @param  None
 * @retval None
 */
static void LEDConfig(void)
{
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    /* Config LED_B(PE1) */
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    GPIO_Init(LED_B_PORT, LED_B_PIN, &stcGpioInit);
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
    /* Enable PGA */
    ADC_PGA_Cmd(ADC_PGA_2, Enable);
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
