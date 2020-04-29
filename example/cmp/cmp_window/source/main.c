/**
 *******************************************************************************
 * @file  cmp/cmp_window/source/main.c
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
#define DAC_TEST_UNIT1                  (M4_DAC1)
/* Define port and pin for CMP */
/* CMP2_VCOUT2*/
#define CMP2_VCOUT2_PORT                (GPIO_PORT_B)
#define CMP2_VCOUT2_PIN                 (GPIO_PIN_13)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void CmpConfig(void);
static void DacConfig(void);
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
    /* Configure system clock. */
    SystemClockConfig();

    /* Configure CMP */
    CmpConfig();

    /* Configure DAC */
    DacConfig();

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
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void CmpConfig(void)
{
    stc_cmp_init_t stcCmpInit;
    stc_cmp_win_ref_t stcCmpWinRef;
    stc_gpio_init_t stcGpioInit;

    /* Enable peripheral clock */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_CMP1, Enable);
    /* Port function configuration for CMP */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_SetFunc(CMP2_VCOUT2_PORT, CMP2_VCOUT2_PIN, GPIO_FUNC_1, PIN_SUBFUNC_DISABLE); /* CMP2_VCOUT2 */

    /* Clear structure */
    CMP_StructInit(&stcCmpInit);
    /* Configuration for normal compare function */
    stcCmpWinRef.u8WinVolLow = CMP_RVSL_INM1;     /* DA1O1 = 1.3V */
    stcCmpWinRef.u8WinVolHigh = CMP_RVSL_INM2;    /* DA2O2 = 1.8V */

    stcCmpInit.u8OutDetectEdges = CMP_DETECT_EDGS_BOTH;
    stcCmpInit.u8OutFilter = CMP_OUT_FILTER_PCLKDIV32;
    stcCmpInit.u8OutPolarity = CMP_OUT_REVERSE_OFF;
    CMP_WindowModeInit(CMP_TEST_UNIT1, &stcCmpInit, &stcCmpWinRef);

    /* Enable VCOUT if need */
    CMP_VCOUTCmd(CMP_TEST_UNIT2, Enable);

    /* Enable CMP output */
    CMP_OutputCmd(CMP_TEST_UNIT2, Enable);
    CMP_OutputCmd(CMP_TEST_UNIT1, Enable);
}

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void DacConfig(void)
{
    /*Config DAC1 */
    /* Align data right */
    DAC_DataPatternConfig(DAC_TEST_UNIT1, DAC_Align_12b_R);
    /* Write Data :V = (Conversion Data / 4096) * VREFH */
    DAC_SetChannel1Data(DAC_TEST_UNIT1, u16SinTable[0U]);
    DAC_SetChannel2Data(DAC_TEST_UNIT1, u16SinTable[1U]);
    /* Output Enable */
    DAC_OutputCmd(DAC_TEST_UNIT1, DAC_Channel_1, Enable);
    DAC_OutputCmd(DAC_TEST_UNIT1, DAC_Channel_2, Enable);
    /* Start Convert */
    DAC_ChannelCmd(DAC_TEST_UNIT1, DAC_Channel_1, Enable);
    DAC_ChannelCmd(DAC_TEST_UNIT1, DAC_Channel_2, Enable);
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
