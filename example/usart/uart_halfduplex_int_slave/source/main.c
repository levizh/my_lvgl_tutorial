/**
 *******************************************************************************
 * @file  usart/uart_halfduplex_int_slave/source/main.c
 * @brief This example demonstrates UART half-duplex data receive and transfer
 *        by interrupt mode.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-20       Hongjh          First version
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
#include <stdio.h>

#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup UART_Halfduplex_Interrupt_Slave
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* UART TX Port/Pin definition */
#define USART_SLAVE_TX_PORT             (GPIO_PORT_E)   /* PE6: USART6_TX */
#define USART_SLAVE_TX_PIN              (GPIO_PIN_06)
#define USART_SLAVE_TX_GPIO_FUNC        (GPIO_FUNC_36_USART6_TX)

/* UART unit definition */
#define USART_SLAVE_UNIT                (M4_USART6)
#define USART_FUNCTION_CLK_GATE         (PWC_FCG3_USART6)

/* UART unit interrupt definition */
#define USART_SLAVE_UNIT_ERR_INT        (INT_USART6_EI)
#define USART_SLAVE_UNIT_ERR_IRQn       (Int000_IRQn)

#define USART_SLAVE_UNIT_RX_INT         (INT_USART6_RI)
#define USART_SLAVE_UNIT_RX_IRQn        (Int001_IRQn)

#define USART_SLAVE_UNIT_TX_INT         (INT_USART6_TI)
#define USART_SLAVE_UNIT_TX_IRQn        (Int002_IRQn)

#define USART_SLAVE_UNIT_TCI_INT        (INT_USART7_TCI)
#define USART_SLAVE_UNIT_TCI_IRQn       (Int003_IRQn)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void UartSlaveUnitTxIrqCallback(void);
static void UartSlaveUnitTcIrqCallback(void);
static void UartSlaveUnitRxIrqCallback(void);
static void UartSlaveUnitErrIrqCallback(void);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t m_u8UartSlaveRxData = 0u;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXtalInit;

    /* Initialize XTAL clock */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    CLK_XtalInit(&stcXtalInit);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_XTAL);
}

/**
 * @brief  UART slave unit TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void UartSlaveUnitTxIrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetFlag(USART_SLAVE_UNIT, USART_FLAG_TXE);
    en_functional_state_t enState = USART_GetFuncState(USART_SLAVE_UNIT, USART_INT_TXE);

    if ((Set == enFlag) && (Enable == enState))
    {
        USART_SendData(USART_SLAVE_UNIT, (uint16_t)m_u8UartSlaveRxData);

        /* Disable slave TX & Enable TC interrupt function */
        USART_FuncCmd(USART_SLAVE_UNIT, USART_INT_TXE, Disable);
        USART_FuncCmd(USART_SLAVE_UNIT, USART_INT_TC, Enable);
    }
}

/**
 * @brief  UART slave unit TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void UartSlaveUnitTcIrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetFlag(USART_SLAVE_UNIT, USART_FLAG_TC);
    en_functional_state_t enState = USART_GetFuncState(USART_SLAVE_UNIT, USART_INT_TC);

    if ((Set == enFlag) && (Enable == enState))
    {
        /* Enable RX & RX no empty interrupt function && Disable TX & TC interrupt function*/
        USART_FuncCmd(USART_SLAVE_UNIT, (USART_TX | USART_INT_TC), Disable);
        USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Enable);
    }
}

/**
 * @brief  UART slave unit RX IRQ callback.
 * @param  None
 * @retval None
 */
static void UartSlaveUnitRxIrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetFlag(USART_SLAVE_UNIT, USART_FLAG_RXNE);
    en_functional_state_t enState = USART_GetFuncState(USART_SLAVE_UNIT, USART_INT_RX);

    if ((Set == enFlag) && (Enable == enState))
    {
        m_u8UartSlaveRxData = (uint8_t)USART_RecData(USART_SLAVE_UNIT);

        /* Disable slave RX & RX no empty interrupt function && Enable TX & TC interrupt function*/
        USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Disable);
        USART_FuncCmd(USART_SLAVE_UNIT, (USART_TX | USART_INT_TXE), Enable);
    }
}

/**
 * @brief  UART slave RX error IRQ callback.
 * @param  None
 * @retval None
 */
static void UartSlaveUnitErrIrqCallback(void)
{
    if (Set == USART_GetFlag(USART_SLAVE_UNIT, (USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_ORE)))
    {
        USART_ClearFlag(USART_SLAVE_UNIT, (USART_CLEAR_FLAG_PE | USART_CLEAR_FLAG_FE | USART_CLEAR_FLAG_ORE));
    }
}

/**
 * @brief  Instal IRQ handler.
 * @param  [in] pstcConfig      Pointer to struct @ref stc_irq_signin_config_t
 * @param  [in] Priority        Interrupt priority
 * @retval None
 */
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority)
{
    if (NULL != pstcConfig)
    {
        INTC_IrqSignIn(pstcConfig);
        NVIC_ClearPendingIRQ(pstcConfig->enIRQn);
        NVIC_SetPriority(pstcConfig->enIRQn, u32Priority);
        NVIC_EnableIRQ(pstcConfig->enIRQn);
    }
}

/**
 * @brief  Main function of UART halfduplex interrupt slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqSigninCfg;
    const stc_usart_uart_init_t stcUartInit = {
        .u32Baudrate = 19200,
        .u32BitDirection = USART_LSB,
        .u32StopBit = USART_STOP_BITS_1,
        .u32Parity = USART_PARITY_NONE,
        .u32DataWidth = USART_DATA_WIDTH_BITS_8,
        .u32ClkMode = USART_INTCLK_NONE_OUTPUT,
        .u32OversamplingBits = USART_OVERSAMPLING_BITS_8,
        .u32NoiseFilterState = USART_NOISE_FILTER_DISABLE,
        .u32SbDetectPolarity = USART_SB_DETECT_FALLING,
    };

    /* Configure system clock. */
    SystemClockConfig();

    /* Configure USART TX pin. */
    GPIO_SetFunc(USART_SLAVE_TX_PORT, USART_SLAVE_TX_PIN, USART_SLAVE_TX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock */
    PWC_Fcg3PeriphClockCmd(USART_FUNCTION_CLK_GATE, Enable);

    /* Initialize UART slave half-duplex function. */
    USART_HalfduplexInit(USART_SLAVE_UNIT, &stcUartInit);

    /* Register RX IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_SLAVE_UNIT_RX_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_SLAVE_UNIT_RX_INT;
    stcIrqSigninCfg.pfnCallback = &UartSlaveUnitRxIrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Register RX error IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_SLAVE_UNIT_ERR_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_SLAVE_UNIT_ERR_INT;
    stcIrqSigninCfg.pfnCallback = &UartSlaveUnitErrIrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Register TX IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_SLAVE_UNIT_TX_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_SLAVE_UNIT_TX_INT;
    stcIrqSigninCfg.pfnCallback = &UartSlaveUnitTxIrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Register TC IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_SLAVE_UNIT_TCI_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_SLAVE_UNIT_TCI_INT;
    stcIrqSigninCfg.pfnCallback = &UartSlaveUnitTcIrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Enable RX function && RX interrupt function */
    USART_FuncCmd(USART_SLAVE_UNIT, (USART_RX | USART_INT_RX), Enable);

    while (1)
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
