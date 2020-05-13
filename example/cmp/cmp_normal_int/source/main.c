/**
 *******************************************************************************
 * @file  cmp/cmp_normal_int/source/main.c
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
/* CMP1 compare voltage CMP1_INP2(PGA2) */
#define CMP1_INP2_PORT                  (GPIO_PORT_A)
#define CMP1_INP2_PIN                   (GPIO_PIN_01)
/* CMP1 reference voltage CMP1_INM3*/
#define CMP1_INM3_PORT                  (GPIO_PORT_A)
#define CMP1_INM3_PIN                   (GPIO_PIN_07)
/* CMP1_VCOUT1*/
#define CMP1_VCOUT1_PORT                (GPIO_PORT_B)
#define CMP1_VCOUT1_PIN                 (GPIO_PIN_12)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void CMP1_IrqCallback(void);
static void CmpConfig(void);
static void PgaConfig(void);
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

    /* LED Init */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Configure system clock. */
    SystemClockConfig();
    /* Configure PGA */
    PgaConfig();
    /* Configure CMP */
    CmpConfig();

    /*NVIC configuration for interrupt */
    stcIrqRegCfg.enIRQn = Int010_IRQn;
    stcIrqRegCfg.enIntSrc = INT_CMP1;
    stcIrqRegCfg.pfnCallback = &CMP1_IrqCallback;
    INTC_IrqSignIn(&stcIrqRegCfg);
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRIORITY_15);
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
    if(GPIO_ReadInputPortPin(CMP1_VCOUT1_PORT, CMP1_VCOUT1_PIN))
    {
        BSP_LED_On(LED_RED);
        BSP_LED_Off(LED_BLUE);
    }
    else
    {
        BSP_LED_On(LED_BLUE);
        BSP_LED_Off(LED_RED);
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
    stc_gpio_init_t stcGpioInit;
    /* Enable peripheral Clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_CMP1, Enable);
    /* Port function configuration for CMP*/
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(CMP1_INP2_PORT, CMP1_INP2_PIN, &stcGpioInit); /* CMP1 compare voltage */
    GPIO_Init(CMP1_INM3_PORT, CMP1_INM3_PIN, &stcGpioInit); /* CMP1 reference voltage */
    GPIO_SetFunc(CMP1_VCOUT1_PORT, CMP1_VCOUT1_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE); /* CMP1_VCOUT1 */
    GPIO_OE(CMP1_VCOUT1_PORT, CMP1_VCOUT1_PIN, Enable); /* GPIO_B_12 output Enable */
    /* Clear structure */
    CMP_StructInit(&stcCmpInit);

    /* Configuration for normal compare function */
    /*For CMP1 and CMP3, when selecting channels inp2 and inp3, there are
    variety of compara voltage available, so you need to configure channels
    and voltage sources, and for others, you only need to configure channels*/
    stcCmpInit.u8CmpCh = CMP_CVSL_INP2;
    stcCmpInit.u16CmpVol = CMP1_INP2_PGA2;
    stcCmpInit.u8RefVol = CMP_RVSL_INM3;
    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpInit.u8OutFilter = CMP_OUT_FILTER_PCLKDIV32;
    stcCmpInit.u8OutPolarity = CMP_OUT_REVERSE_OFF;
    CMP_NormalModeInit(CMP_TEST_UNIT, &stcCmpInit);

    /* Enable interrupt if need */
    CMP_IntCmd(CMP_TEST_UNIT, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT, Enable);

    /* Enable VCOUT */
    CMP_VCOUTCmd(CMP_TEST_UNIT, Enable);
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
