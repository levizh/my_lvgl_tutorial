/**
 *******************************************************************************
 * @file  usart/uart_halfduplex_polling_slave/source/main.c
 * @brief This example demonstrates UART half-duplex data receive and transfer
 *        by polling mode.
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
 * @addtogroup UART_Halfduplex_Polling_Slave
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

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void UartRxErrProcess(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  USART RX error process function.
 * @param  None
 * @retval None
 */
static void UartRxErrProcess(void)
{
    if (Set == USART_GetFlag(USART_SLAVE_UNIT, (USART_FLAG_PE | USART_FLAG_FE | USART_FLAG_ORE)))
    {
        USART_ClearFlag(USART_SLAVE_UNIT, (USART_CLEAR_FLAG_PE | USART_CLEAR_FLAG_FE | USART_CLEAR_FLAG_ORE));
    }
}

/**
 * @brief  Main function of UART halfduplex polling slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t u8SlaveRxData = 0u;
    const stc_usart_uart_init_t stcUartInit = {
        .u32Baudrate = 19200ul,
        .u32BitDirection = USART_LSB,
        .u32StopBit = USART_STOP_BITS_1,
        .u32Parity = USART_PARITY_NONE,
        .u32DataWidth = USART_DATA_WIDTH_BITS_8,
        .u32ClkMode = USART_INTCLK_NONE_OUTPUT,
        .u32OversamplingBits = USART_OVERSAMPLING_BITS_8,
        .u32NoiseFilterState = USART_NOISE_FILTER_DISABLE,
        .u32SbDetectPolarity = USART_SB_DETECT_FALLING,
    };

    /* Initialize system clock. */
    BSP_CLK_Init();
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV16 | CLK_PCLK1_DIV16 | \
                              CLK_PCLK2_DIV4  | CLK_PCLK3_DIV16 | \
                              CLK_PCLK4_DIV2  | CLK_EXCLK_DIV2  | CLK_HCLK_DIV1));

    /* Configure USART TX pin. */
    GPIO_Unlock();
    GPIO_SetFunc(USART_SLAVE_TX_PORT, USART_SLAVE_TX_PIN, USART_SLAVE_TX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_Lock();

    /* Enable peripheral clock */
    PWC_Fcg3PeriphClockCmd(USART_FUNCTION_CLK_GATE, Enable);

    /* Initialize UART function. */
    USART_HalfduplexInit(USART_SLAVE_UNIT, &stcUartInit);

    /* Enable RX function */
    USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Enable);

    while (1)
    {
        /* Wait slave unit Rx data register no empty */
        while (Reset == USART_GetFlag(USART_SLAVE_UNIT, USART_FLAG_RXNE))
        {
        }

        /* Slave unit receive data */
        u8SlaveRxData = (uint8_t)USART_RecData(USART_SLAVE_UNIT);

        /* Enable slave RX function && Disable slave TX function*/
        USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Disable);
        USART_FuncCmd(USART_SLAVE_UNIT, USART_TX, Enable);

        /* Slave unit send data */
        USART_SendData(USART_SLAVE_UNIT, (uint16_t)u8SlaveRxData);

        /* Wait slave unit Tx complete */
        while (Reset == USART_GetFlag(USART_SLAVE_UNIT, USART_FLAG_TC))
        {
        }

        /* Enable slave RX function && Disable slave TX function*/
        USART_FuncCmd(USART_SLAVE_UNIT, USART_RX, Enable);
        USART_FuncCmd(USART_SLAVE_UNIT, USART_TX, Disable);

        /* USART error handle */
        UartRxErrProcess();
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
