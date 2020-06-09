/**
 *******************************************************************************
 * @file  timer4/timer4_oco_single_high_ch/source/main.c
 * @brief This example demonstrates how to use the single high channel of Timer4
 *        OCO function.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-19       Hongjh          First version
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
 * @addtogroup TIMER4_OCO_Single_High_Channel
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Wave I/O Port/Pin definition */
#define WAVE_IO_PORT                    (GPIO_PORT_E)
#define WAVE_IO_PIN                     (GPIO_PIN_09)

/* Timer4 unit& fcg & counter period value definition */
#define TMR4_UNIT                       (M4_TMR4_1)
#define TMR4_FUNCTION_CLK_GATE          (PWC_FCG2_TMR4_1)
#define TMR4_CNT_CYCLE_VAL(div)         ((uint16_t)(Tmr4PclkFreq() /  (2UL * (1UL << (uint32_t)(div))))) /* Period_Value(500ms) */

/* Timer4 OCO Channel definition */
#define TMR4_OCO_CH                     (TMR4_OCO_UH)    /* only TMR4_OCO_UH  TMR4_OCO_VH  TMR4_OCO_WH */

/* Timer4 OCO get interrupt source number definition */
#define TMR4_1_OCO_INT_SRC(x)           ((en_int_src_t)((uint32_t)INT_TMR4_1_GCMUH + ((uint32_t)((x) - TMR4_OCO_UH))))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void WaveIoConfig(void);
static uint32_t Tmr4PclkFreq(void);
static void TMR4_OcoMatch_IrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Configure Wave I/O.
 * @param  None
 * @retval None
 */
static void WaveIoConfig(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_Unlock();
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_RESET;
    GPIO_Init(WAVE_IO_PORT, WAVE_IO_PIN, &stcGpioInit);
    GPIO_Lock();
}

/**
 * @brief  Get TIMER4 PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t Tmr4PclkFreq(void)
{
    stc_clk_freq_t stcClkFreq;

    CLK_GetClockFreq(&stcClkFreq);
    return stcClkFreq.pclk0Freq;
}

/**
 * @brief  TIMER4 OCO match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_OcoMatch_IrqCallback(void)
{
    GPIO_TogglePins(WAVE_IO_PORT, WAVE_IO_PIN);
    TMR4_OCO_ClearFlag(TMR4_UNIT, TMR4_OCO_CH);
}

/**
 * @brief  Main function of TIMER4 OCO single high channel
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqSigninCfg;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;

    /* Initialize clock. */
    BSP_CLK_Init();
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV32 | CLK_PCLK1_DIV32 | \
                              CLK_PCLK2_DIV4  | CLK_PCLK3_DIV32 | \
                              CLK_PCLK4_DIV2  | CLK_EXCLK_DIV2  | CLK_HCLK_DIV1));

    /* Configure Wave I/O. */
    WaveIoConfig();

    /* Enable peripheral clock */
    PWC_Fcg2PeriphClockCmd(TMR4_FUNCTION_CLK_GATE, Enable);

    /* Initialize TIMER4 Counter */
    TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClkDiv = TMR4_CNT_CLK_DIV1024;
    stcTmr4CntInit.u16CntMode = TMR4_CNT_MODE_TRIANGLE_WAVE;
    stcTmr4CntInit.u16CycleVal = TMR4_CNT_CYCLE_VAL(stcTmr4CntInit.u16ClkDiv);
    TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);

    /* Initialize TIMER4 OCO */
    TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16CompareVal = stcTmr4CntInit.u16CycleVal/2U;
    TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_CH, &stcTmr4OcoInit);
    TMR4_OCO_IntCmd(TMR4_UNIT, TMR4_OCO_CH, Enable);

    if (!(TMR4_OCO_CH%2UL))
    {
        /* OCMR[15:0] = 0x0FFF = b 0000 1111 1111 1111   */
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

        TMR4_OCO_SetHighChCompareMode(TMR4_UNIT, TMR4_OCO_CH, &stcHighChCmpMode);  /* Set OCO high channel compare mode */
    }

    /* Register IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = Int000_IRQn;
    stcIrqSigninCfg.enIntSrc = TMR4_1_OCO_INT_SRC(TMR4_OCO_CH);
    stcIrqSigninCfg.pfnCallback = &TMR4_OcoMatch_IrqCallback;
    INTC_IrqSignIn(&stcIrqSigninCfg);
    NVIC_ClearPendingIRQ(stcIrqSigninCfg.enIRQn);
    NVIC_SetPriority(stcIrqSigninCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSigninCfg.enIRQn);

    /* Start TIMER4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

    while (1)
    {
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
