/**
 *******************************************************************************
 * @file  timer4/timer4_pwm_through_mode_occr_buf/source/main.c
 * @brief This example demonstrates how to use the through mode function of 
 *        Timer4 PWM function and enable OCCR buffer function.
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
 * @addtogroup TIMER4_PWM_Through_Mode_With_OCCR_Buffer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TIM4 PWM Port/Pin definition */
#define TIM4_OXH_PORT                   (GPIO_PORT_E)
#define TIM4_OXH_PIN                    (GPIO_PIN_09)
#define TIM4_OXH_GPIO_FUNC              (GPIO_FUNC_2)

/* Timer4 unit && interrupt number && fcg && counter period value definition */
#define TMR4_UNIT                       (M4_TMR4_1)
#define TMR4_CNT_UDF_IRQn               (Int000_IRQn)
#define TMR4_CNT_UDF_INT                (INT_TMR4_1_GUDF)
#define TMR4_FUNCTION_CLK_GATE          (PWC_FCG2_TMR4_1)
#define TMR4_CNT_CYCLE_VAL(div)         ((uint16_t)(Tmr4PclkFreq() / (1UL << (uint32_t)(div)))) /* Period_Value(100ms) */

/* Timer4 OCO Channel definition */
#define TMR4_OCO_HIGH_CH                (TMR4_OCO_UH)    /* only TMR4_OCO_UH  TMR4_OCO_VH  TMR4_OCO_WH */

#define TMR4_OCO_CMP_BUF_SIZE           (3U)

/* Timer4 PWM get channel by OCO high channel */
#define TMR4_PWM_CH(x)                  (((x) == TMR4_OCO_UH) ? TMR4_PWM_U : \
                                         (((x) == TMR4_OCO_VH) ? TMR4_PWM_V : TMR4_PWM_W))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static uint32_t Tmr4PclkFreq(void);
static void TMR4_ZeroMatch_IrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_u16OcoCmpValIdx = 0U;
static uint16_t m_au16OcoCmpVal[TMR4_OCO_CMP_BUF_SIZE];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

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
 * @brief  TIMER4 Counter zero match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void TMR4_ZeroMatch_IrqCallback(void)
{
    TMR4_CNT_ClearFlag(TMR4_UNIT, TMR4_CNT_FLAG_ZERO);
    TMR4_OCO_SetCompareVal(TMR4_UNIT, TMR4_OCO_HIGH_CH, m_au16OcoCmpVal[m_u16OcoCmpValIdx]);

    if (++m_u16OcoCmpValIdx >= TMR4_OCO_CMP_BUF_SIZE)
    {
        m_u16OcoCmpValIdx = 0U;
    }
}

/**
 * @brief  Main function of TIMER4 PWM through mode with OCCR buffer
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t u32PwmCh;
    stc_irq_signin_config_t stcIrqSigninCfg;
    stc_tmr4_cnt_init_t stcTmr4CntInit;
    stc_tmr4_oco_init_t stcTmr4OcoInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
    stc_oco_high_ch_compare_mode_t stcHighChCmpMode;

    /* Initialize clock. */
    BSP_CLK_Init();
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV32 | CLK_PCLK1_DIV32 | \
                              CLK_PCLK2_DIV4  | CLK_PCLK3_DIV32 | \
                              CLK_PCLK4_DIV2  | CLK_EXCLK_DIV2  | CLK_HCLK_DIV1));

    /* Enable peripheral clock */
    PWC_Fcg2PeriphClockCmd(TMR4_FUNCTION_CLK_GATE, Enable);

    /* Initialize TIMER4 Counter */
    TMR4_CNT_StructInit(&stcTmr4CntInit);
    stcTmr4CntInit.u16ClkDiv = TMR4_CNT_CLK_DIV512;
    stcTmr4CntInit.u16CycleVal = TMR4_CNT_CYCLE_VAL(stcTmr4CntInit.u16ClkDiv);
    TMR4_CNT_Init(TMR4_UNIT, &stcTmr4CntInit);
    TMR4_CNT_IntCmd(TMR4_UNIT, TMR4_CNT_INT_ZERO, Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = TMR4_CNT_UDF_IRQn;
    stcIrqSigninCfg.enIntSrc = TMR4_CNT_UDF_INT;
    stcIrqSigninCfg.pfnCallback = &TMR4_ZeroMatch_IrqCallback;
    INTC_IrqSignIn(&stcIrqSigninCfg);
    NVIC_ClearPendingIRQ(stcIrqSigninCfg.enIRQn);
    NVIC_SetPriority(stcIrqSigninCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSigninCfg.enIRQn);

    /* Initialize TIMER4 OCO high channel */
    m_au16OcoCmpVal[0] = 1U * (stcTmr4CntInit.u16CycleVal / 4U);
    m_au16OcoCmpVal[1] = 2U * (stcTmr4CntInit.u16CycleVal / 4U);
    m_au16OcoCmpVal[2] = 3U * (stcTmr4CntInit.u16CycleVal / 4U);
    TMR4_OCO_StructInit(&stcTmr4OcoInit);
    stcTmr4OcoInit.u16OccrBufMode = TMR4_OCO_OCCR_BUF_CNT_PEAK;
    stcTmr4OcoInit.u16CompareVal = m_au16OcoCmpVal[m_u16OcoCmpValIdx++];
    TMR4_OCO_Init(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcTmr4OcoInit);

    if (!(TMR4_OCO_HIGH_CH % 2UL))
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
        TMR4_OCO_SetHighChCompareMode(TMR4_UNIT, TMR4_OCO_HIGH_CH, &stcHighChCmpMode);  /* Set OCO high channel compare mode */
    }

    /* Initialize PWM I/O */
    GPIO_Unlock();
    GPIO_SetFunc(TIM4_OXH_PORT, TIM4_OXH_PIN, TIM4_OXH_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_Lock();

    /* Timer4 PWM: Get pwm couple channel */
    u32PwmCh = TMR4_PWM_CH(TMR4_OCO_HIGH_CH);

    /* Initialize Timer4 PWM */
    TMR4_PWM_StructInit(&stcTmr4PwmInit);
    TMR4_PWM_Init(TMR4_UNIT, u32PwmCh, &stcTmr4PwmInit);

    /* Start TIMER4 counter. */
    TMR4_CNT_Start(TMR4_UNIT);

    /* Set OCO compare value */
    TMR4_OCO_SetCompareVal(TMR4_UNIT, TMR4_OCO_HIGH_CH, m_au16OcoCmpVal[m_u16OcoCmpValIdx++]);

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
