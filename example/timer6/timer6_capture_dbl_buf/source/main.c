/**
 *******************************************************************************
 * @file  template/source/main.c
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
 * @addtogroup TMR6_Capture_Double_Buffer
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

#define         TMR6_2_PWMA_PORT       (GPIO_PORT_B)
#define         TMR6_2_PWMA_PIN        (GPIO_PIN_07)

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
uint32_t u32CaptureC;
uint32_t u32CaptureE;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  TIMER6 overflow interrupt handler callback.
 * @param  None
 * @retval None
 */
void Tmr6_OverFlow_CallBack(void)
{
    static uint8_t i = 0U;

    if( 0U == i)
    {
        TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_E, 0x4000u);
        i = 1U;
    }
    else if(1U == i)
    {
        TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_E, 0x6000u);
        i = 2U;
    }
    else
    {
        TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_E, 0x2000u);
        i = 0U;
    }
}

/**
 * @brief  TIMER6 capture input interrupt handler callback.
 * @param  None
 * @retval None
 */
void Tmr6_2_CapInputCallBack(void)
{
    u32CaptureA = TMR6_GetGenCmpReg(M4_TMR6_2, TMR6_CMP_REG_A);
    u32CaptureC = TMR6_GetGenCmpReg(M4_TMR6_2, TMR6_CMP_REG_C);
    u32CaptureE = TMR6_GetGenCmpReg(M4_TMR6_2, TMR6_CMP_REG_E);
}

/**
 * @brief  Main function of TIMER6 compare output mode project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t                       u32Period;
    uint32_t                       u32Compare;
    stc_tmr6_basecnt_cfg_t         stcTIM6BaseCntCfg;
    stc_tmr6_port_output_cfg_t     stcTIM6PortOutCfg;
    stc_tmr6_port_input_cfg_t      stcTIM6PortInCfg;
    stc_gpio_init_t                stcGpioInit;
    stc_irq_signin_config_t        stcIrqRegiConf;
    stc_tmr6_buf_func_cfg_t        stcBufCfg;

    TMR6_BaseCntStructInit(&stcTIM6BaseCntCfg);
    TMR6_PortOutputStructInit(&stcTIM6PortOutCfg);
    TMR6_PortInputStructInit(&stcTIM6PortInCfg);
    GPIO_StructInit(&stcGpioInit);
    TMR6_BufFuncStructInit(&stcBufCfg);

    BSP_CLK_Init();

    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR6_1, Enable);
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR6_2, Enable);

    /* Timer6 PWM port configuration */
    GPIO_SetFunc(TMR6_1_PWMA_PORT, TMR6_1_PWMA_PIN, GPIO_FUNC_3_TIM61_PWMA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(TMR6_2_PWMA_PORT, TMR6_2_PWMA_PIN, GPIO_FUNC_3_TIM62_PWMB, PIN_SUBFUNC_DISABLE);

    /******************Config M4_TMR6_1 as output signal*************************/

    /* Timer6 general count function configuration */
    stcTIM6BaseCntCfg.u32CntMode = TMR6_MODE_SAWTOOTH;
    stcTIM6BaseCntCfg.u32CntDir = TMR6_CNT_INCREASE;B
    stcTIM6BaseCntCfg.u32CntClkDiv = TMR6_CLK_PCLK0_DIV1024;
    stcTIM6BaseCntCfg.u32CntStpAftOvf = TMR6_CNT_CONTINUOUS;
    TMR6_Init(M4_TMR6_1, &stcTIM6BaseCntCfg);

    /* Period register set */
    u32Period = 0x8000u;
    TMR6_SetPeriodReg(M4_TMR6_1, TMR6_PERIOD_REG_A, u32Period);

    /* Compare register set */
    u32Compare = 0x2000u;
    TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_A, u32Compare); /* Set General Compare RegisterA Value */
    u32Compare = 0x4000u;
    TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_C, u32Compare); /* Set General Compare RegisterC Value */
    u32Compare = 0x6000u;
    TMR6_SetGenCmpReg(M4_TMR6_1, TMR6_CMP_REG_E, u32Compare); /* Set General Compare RegisterE Value */

    /* General compare buffer function configurate */
    stcBufCfg.u32BufFunCmd = TMR6_BUF_FUNC_ON;
    stcBufCfg.u32BufNum = TMR6_BUF_FUNC_DOUBLE;
    stcBufCfg.u32BufTransTim = TMR6_BUF_TRANS_TIM_OVERFLOW;
    TMR6_GenCmpBufCfg(M4_TMR6_1, TMR6_CMP_CHA, &stcBufCfg);

     /* Configurate PWM output */
    stcTIM6PortOutCfg.u32PortMode = TMR6_PORT_COMPARE_OUTPUT;
    stcTIM6PortOutCfg.u32NextPeriodForceStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32DownCntMatchAnotherCmpRegStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32UpCntMatchAnotherCmpRegStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32DownCntMatchCmpRegStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32UpCntMatchCmpRegStd = TMR6_PORT_OUTPUT_STD_HIGH;
    stcTIM6PortOutCfg.u32UnderflowStd = TMR6_PORT_OUTPUT_STD_HOLD;
    stcTIM6PortOutCfg.u32OverflowStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32StopStd = TMR6_PORT_OUTPUT_STD_LOW;
    stcTIM6PortOutCfg.u32StartStd = TMR6_PORT_OUTPUT_STD_LOW;
    TMR6_PortOutputConfig(M4_TMR6_1, TMR6_IO_PWMA, &stcTIM6PortOutCfg);

    /* Enable interrupt */
    TMR6_IntCmd(M4_TMR6_1, TMR6_IRQ_EN_OVERFLOW, Enable);

    stcIrqRegiConf.enIRQn = Int002_IRQn;                    /* Register INT_TMR6_1_GOVF Int to Vect.No.002 */
    stcIrqRegiConf.enIntSrc = INT_TMR6_1_GOVF;               /* Select Event interrupt of M4_TMR6_1 */
    stcIrqRegiConf.pfnCallback = &Tmr6_OverFlow_CallBack; /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                        /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_03);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */

    /**************Config M4_TMR6_2 as input signal for capture *****************/

    /* Timer6 general count function configuration */
    stcTIM6BaseCntCfg.u32CntMode = TMR6_MODE_SAWTOOTH;
    stcTIM6BaseCntCfg.u32CntDir = TMR6_CNT_INCREASE;
    stcTIM6BaseCntCfg.u32CntClkDiv = TMR6_CLK_PCLK0_DIV1024;
    stcTIM6BaseCntCfg.u32CntStpAftOvf = TMR6_CNT_CONTINUOUS;
    TMR6_Init(M4_TMR6_2, &stcTIM6BaseCntCfg);

    /* Period register set */
    u32Period = 0xFFFFFFFFu;
    TMR6_SetPeriodReg(M4_TMR6_2, TMR6_PERIOD_REG_A, u32Period);

    /* General compare buffer function configurate */
    stcBufCfg.u32BufFunCmd = TMR6_BUF_FUNC_ON;
    stcBufCfg.u32BufNum = TMR6_BUF_FUNC_DOUBLE;
    stcBufCfg.u32BufTransTim = TMR6_BUF_TRANS_TIM_OVERFLOW;
    TMR6_GenCmpBufCfg(M4_TMR6_2, TMR6_CMP_CHA, &stcBufCfg);

    /* Capture input port configuration */
    stcTIM6PortInCfg.u32PortMode = TMR6_PORT_CAPTURE_INPUT;
    stcTIM6PortInCfg.u32FilterStd = TMR6_PORT_INPUT_FITLER_ON;
    stcTIM6PortInCfg.u32FltClk = TMR6_INPUT_FILTER_DIV16;
    TMR6_PortInputConfig(M4_TMR6_2,TMR6_IO_PWMA, &stcTIM6PortInCfg);

    /* Hardware capture: Timer6 PWMA port rise trig*/
    TMR6_HwCaptureFuncChACfg(M4_TMR6_2, TMR6_HW_CTL_PWMA_RISING);
    /* HW Clear: Timer6 PWMA port fall trig and function command */
    TMR6_HwClrFuncCfg(M4_TMR6_2, TMR6_HW_CTL_PWMA_FAILLING);
    TMR6_HwClrFuncCmd(M4_TMR6_2, Enable);

    /* config interrupt */
    /* Enable M4_TMR6_2 GCMAR interrupt */
    TMR6_IntCmd(M4_TMR6_2, TMR6_IRQ_EN_CNT_MATCH_A, Enable);

    stcIrqRegiConf.enIRQn = Int003_IRQn;                    /* Register INT_TMR6_2_GCMA Int to Vect.No.003 */
    stcIrqRegiConf.enIntSrc = INT_TMR6_2_GCMA;               /* Select Event interrupt of M4_TMR6_2 */
    stcIrqRegiConf.pfnCallback = &Tmr6_2_CapInputCallBack; /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                        /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_04);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */

    /* Start timer6 */
    TMR6_SwSyncStart(TMR6_SOFT_SYNC_CTL_U1 | TMR6_SOFT_SYNC_CTL_U2);

    while(1)
    {
        ;
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
