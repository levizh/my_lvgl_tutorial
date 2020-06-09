/**
 *******************************************************************************
 * @file  swdt/swdt_reset_sw_startup/source/main.c
 * @brief Main program of SWDT Reset for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-03       Yangjp          First version
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
 * @addtogroup SWDT_Reset
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SW1 Port/Pin definition */
#define SW1_IN_PORT                             (GPIO_PORT_H)
#define SW1_IN_PIN                              (GPIO_PIN_07)
#define SW1_IN_EXINT_CH                         (EXINT_CH07)
#define SW1_IN_INT_SRC                          (INT_PORT_EIRQ7)
#define SW1_IN_IRQn                             (Int032_IRQn)

#define SW1_OUT_PORT                            (GPIO_PORT_A)
#define SW1_OUT_PIN                             (GPIO_PIN_06)

/* SWDT count cycle definition */
#define SWDT_COUNT_CYCLE                        (256U)

/* Reset source definition */
#define RESET_SOURCE_SWDT                       (0U)
#define RESET_SOURCE_OTHER                      (1U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8ExIntFlag = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  SW1 interrupt callback function.
 * @param  None
 * @retval None
 */
void SW1_IrqCallback(void)
{
    if (Set == EXINT_GetExIntSrc(SW1_IN_EXINT_CH))
    {
        u8ExIntFlag = 1U;
        EXINT_ClrExIntSrc(SW1_IN_EXINT_CH);
    }
}

/**
 * @brief  SW1 configuration.
 * @param  None
 * @retval None
 */
static void SW1_Config(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_RESET;
    GPIO_Init(SW1_OUT_PORT, SW1_OUT_PIN, &stcGpioInit);

    stcGpioInit.u16PinDir = PIN_DIR_IN;
    stcGpioInit.u16ExInt  = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(SW1_IN_PORT, SW1_IN_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh  = SW1_IN_EXINT_CH;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc    = SW1_IN_INT_SRC;
    stcIrqSignConfig.enIRQn      = SW1_IN_IRQn;
    stcIrqSignConfig.pfnCallback = &SW1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}

/**
 * @brief  SWDT configuration.
 * @param  None
 * @retval None
 */
static void SWDT_Config(void)
{
    stc_swdt_init_t stcSwdtInit;

    /* SWDT configure */
    stcSwdtInit.u32CountCycle    = SWDT_COUNTER_CYCLE_256;
    stcSwdtInit.u32ClockDivision = SWDT_CLOCK_DIV32;
    stcSwdtInit.u32RefreshRange  = SWDT_RANGE_0TO25PCT;
    stcSwdtInit.u32LPModeCountEn = SWDT_LPW_MODE_COUNT_STOP;
    stcSwdtInit.u32TrigType      = SWDT_TRIG_EVENT_RESET;
    SWDT_Init(&stcSwdtInit);
}

/**
 * @brief  Main function of SWDT Reset.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint16_t u16CmpVal;
    uint8_t u8ResetSource;
    stc_rmu_rstcause_t stRstCause;

    /* Configure clock */
    BSP_CLK_Init();
    /* Configure BSP */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Configure UART */
    DDL_PrintfInit();

    /* Get RMU information */
    RMU_GetStatus(&stRstCause);
    if (Set == stRstCause.enSwdtRst)
    {
        u8ResetSource = RESET_SOURCE_SWDT;
        BSP_LED_On(LED_RED);
    }
    else
    {
        u8ResetSource = RESET_SOURCE_OTHER;
    }
    RMU_ClrStatus();

    /* SWDT configuration */
    SWDT_Config();
    /* SW1 configuration */
    SW1_Config();
    /* First reload counter to start SWDT */
    SWDT_ReloadCounter();
    /* Wait for SWDT module to complete initial */
    DDL_Delay1ms(10U);
    /* Count cycle=256,range=0%-25% */
    u16CmpVal = SWDT_COUNT_CYCLE / 4U;

    while (1)
    {
        if (1U == u8ExIntFlag)
        {
            u8ExIntFlag = 0U;
            u16CmpVal = SWDT_COUNT_CYCLE / 2U;
        }

        if (SWDT_GetCountValue() < u16CmpVal)
        {
            SWDT_ReloadCounter();
            /* Wait for the count value to update */
            DDL_Delay1ms(10U);
            if (RESET_SOURCE_OTHER == u8ResetSource)
            {
                BSP_LED_Toggle(LED_RED);
            }
        }
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
