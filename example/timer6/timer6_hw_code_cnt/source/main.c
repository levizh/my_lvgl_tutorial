/**
 *******************************************************************************
 * @file  timer6\timer6_hw_code_cnt\source\main.c
 * @brief Main program template for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-09       Wangmin          First version
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
 * @addtogroup TMR6_hw_code_cnt
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define         TMR6_1_PWMA_PORT       (GPIO_PORT_B)
#define         TMR6_1_PWMA_PIN        (GPIO_PIN_09)

#define         TMR6_1_PWMB_PORT       (GPIO_PORT_B)
#define         TMR6_1_PWMB_PIN        (GPIO_PIN_08)

#define         TEST_IO_A_PORT         (GPIO_PORT_I)
#define         TEST_IO_B_PORT         (GPIO_PORT_I)

#define         TEST_IO_A_PIN          (GPIO_PIN_06)
#define         TEST_IO_B_PIN          (GPIO_PIN_05)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
uint32_t u32CaptureA;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/


static void GenClkIn(void)
{
    uint32_t i;
    static volatile uint32_t u32Timer6Cnt0 = 0U;

    uint8_t bAin[17] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1};
    uint8_t bBin[17] = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};


    for (i = 0ul; i < 17ul; i++)
    {
        u32Timer6Cnt0 = TMR6_GetCntReg(M4_TMR6_1);

        if(0U == bAin[i])
        {
            GPIO_ResetPins(TEST_IO_A_PORT, TEST_IO_A_PIN);
        }
        else
        {
            GPIO_SetPins(TEST_IO_A_PORT, TEST_IO_A_PIN);
        }

        if(0U == bBin[i])
        {
            GPIO_ResetPins(TEST_IO_B_PORT, TEST_IO_B_PIN);
        }
        else
        {
            GPIO_SetPins(TEST_IO_B_PORT, TEST_IO_B_PIN);
        }

        DDL_Delay1ms(500UL);
    }

    u32Timer6Cnt0 = TMR6_GetCntReg(M4_TMR6_1);
}


/**
 * @brief  Main function of TIMER6 compare output mode project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_tmr6_basecnt_cfg_t         stcTIM6BaseCntCfg;
    stc_tmr6_port_input_cfg_t      stcTIM6PortInCfg;
    stc_gpio_init_t                stcGpioCfg;

    TMR6_BaseCntStructInit(&stcTIM6BaseCntCfg);
    TMR6_PortInputStructInit(&stcTIM6PortInCfg);

    BSP_CLK_Init();

    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR6_1, Enable);

    /* Timer6 PWM port configuration */
    GPIO_SetFunc(TMR6_1_PWMA_PORT, TMR6_1_PWMA_PIN, GPIO_FUNC_3_TIM61_PWMA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(TMR6_1_PWMB_PORT, TMR6_1_PWMB_PIN, GPIO_FUNC_3_TIM61_PWMB, PIN_SUBFUNC_DISABLE);

    /* GPIO configurate */
    GPIO_StructInit(&stcGpioCfg);
    stcGpioCfg.u16PinDir = PIN_DIR_OUT;
    GPIO_Init(TEST_IO_A_PORT, TEST_IO_A_PIN, &stcGpioCfg);
    GPIO_Init(TEST_IO_B_PORT, TEST_IO_B_PIN, &stcGpioCfg);

    /* De-initialize */
    TMR6_DeInit(M4_TMR6_1);
    /* Timer6 general count function configuration */
    stcTIM6BaseCntCfg.u32CntMode = TMR6_MODE_SAWTOOTH;
    stcTIM6BaseCntCfg.u32CntDir = TMR6_CNT_INCREASE;
    stcTIM6BaseCntCfg.u32CntClkDiv = TMR6_CLK_PCLK0_DIV512;
    stcTIM6BaseCntCfg.u32CntStpAftOvf = TMR6_CNT_CONTINUOUS;
    TMR6_Init(M4_TMR6_1, &stcTIM6BaseCntCfg);

    /* Capture input port configuration */
    stcTIM6PortInCfg.u32PortMode = TMR6_PORT_CAPTURE_INPUT;
    stcTIM6PortInCfg.u32FilterStd = TMR6_PORT_INPUT_FITLER_OFF;
    stcTIM6PortInCfg.u32FltClk = TMR6_INPUT_FILTER_PCLK0;
    TMR6_PortInputConfig(M4_TMR6_1,TMR6_IO_PWMA, &stcTIM6PortInCfg);

    TMR6_PortInputConfig(M4_TMR6_1,TMR6_IO_PWMB, &stcTIM6PortInCfg);

     while(1)
    {

        GPIO_ResetPins(TEST_IO_A_PORT, TEST_IO_A_PIN);
        GPIO_SetPins(TEST_IO_B_PORT, TEST_IO_B_PIN);

        DDL_Delay1ms(1000UL);
        TMR6_HwIncreaseFuncRegClr(M4_TMR6_1);
        TMR6_HwDecreaseFuncRegClr(M4_TMR6_1);

        TMR6_HwIncreaseFuncCfg(M4_TMR6_1, TMR6_HW_CNT_PWMBH_PWMARISING); /* PWMA Rising trigger when PWMB is high level */
        TMR6_HwDecreaseFuncCfg(M4_TMR6_1, TMR6_HW_CNT_PWMBL_PWMARISING); /* PWMA Rising trigger when PWMB is low level */

        TMR6_CountCmd(M4_TMR6_1, Enable);

        GenClkIn();

        TMR6_CountCmd(M4_TMR6_1, Disable);
        TMR6_SetCntReg(M4_TMR6_1, 0UL);

        GPIO_ResetPins(TEST_IO_A_PORT, TEST_IO_A_PIN);
        GPIO_SetPins(TEST_IO_B_PORT, TEST_IO_B_PIN);

        DDL_Delay1ms(1000UL);

        TMR6_HwIncreaseFuncRegClr(M4_TMR6_1);
        TMR6_HwDecreaseFuncRegClr(M4_TMR6_1);

        /* PWMA Rising trigger when PWMB is high level, PWMA falling trigger when PWMB is low level */
        TMR6_HwIncreaseFuncCfg(M4_TMR6_1, TMR6_HW_CNT_PWMBH_PWMARISING | TMR6_HW_CNT_PWMBL_PWMAFAILLING);
        /* PWMB Rising trigger when PWMA is high level, PWMB falling trigger when PWMA is low level */
        TMR6_HwDecreaseFuncCfg(M4_TMR6_1, TMR6_HW_CNT_PWMAH_PWMBRISING | TMR6_HW_CNT_PWMAL_PWMBFAILLING);

        TMR6_CountCmd(M4_TMR6_1, Enable);

        GenClkIn();

        TMR6_CountCmd(M4_TMR6_1, Disable);
        TMR6_SetCntReg(M4_TMR6_1, 0UL);
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
