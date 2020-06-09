/**
 *******************************************************************************
 * @file  usart/uart_multiple_processor_slave/source/main.c
 * @brief This example demonstrates UART multi-processor receive and transfer.
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup UART_Multiple_Processor_Slave
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Ring buffer structure definition
 */
typedef struct
{
    uint16_t u16Capacity;
    __IO uint16_t u16UsedSize;
    uint16_t u16InIdx;
    uint16_t u16OutIdx;
    uint8_t  au8Buf[50];
} stc_ring_buffer_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* UART RX/TX Port/Pin definition */
#define USART_RX_PORT                   (GPIO_PORT_H)   /* PH6: USART6_RX */
#define USART_RX_PIN                    (GPIO_PIN_06)
#define USART_RX_GPIO_FUNC              (GPIO_FUNC_37_USART6_RX)

#define USART_TX_PORT                   (GPIO_PORT_E)   /* PE6: USART6_TX */
#define USART_TX_PIN                    (GPIO_PIN_06)
#define USART_TX_GPIO_FUNC              (GPIO_FUNC_36_USART6_TX)

/* UART unit definition */
#define USART_UNIT                      (M4_USART6)
#define USART_FUNCTION_CLK_GATE         (PWC_FCG3_USART6)

/* UART unit interrupt definition */
#define USART_UNIT_ERR_INT_SRC          (INT_USART6_EI)
#define USART_UNIT_ERR_INT_IRQn         (Int000_IRQn)

#define USART_UNIT_RX_INT_SRC           (INT_USART6_RI)
#define USART_UNIT_RX_INT_IRQn          (Int001_IRQn)

#define USART_UNIT_TX_INT_SRC           (INT_USART6_TI)
#define USART_UNIT_TX_INT_IRQn          (Int002_IRQn)

#define USART_UNIT_TCI_INT_SRC          (INT_USART6_TCI)
#define USART_UNIT_TCI_INT_IRQn         (Int003_IRQn)

/* UART multiple processor ID definition */
#define UART_MASTER_STATION_ID          (0x20U)
#define UART_SLAVE_STATION_ID           (0x21U)

/* Ring buffer size */
#define IS_RING_BUFFER_EMPYT(x)         (0U == ((x)->u16UsedSize))

/* Multi-processor silence mode */
#define USART_UART_NORMAL_MODE          ((uint8_t)0U)
#define USART_UART_SILENCE_MODE         ((uint8_t)1U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void USART_TxEmpty_IrqCallback(void);
static void USART_TxComplete_IrqCallback(void);
static void USART_Rx_IrqCallback(void);
static void USART_RxErr_IrqCallback(void);
static en_result_t RingBufWrite(stc_ring_buffer_t *pstcBuffer, uint8_t u8Data);
static en_result_t RingBufRead(stc_ring_buffer_t *pstcBuffer, uint8_t *pu8Data);
static void UsartSetSilenceMode(uint8_t u8Mode);
static uint8_t UsartGetSilenceMode(void);
static void InstalIrqHandler(const stc_irq_signin_config_t *pstcConfig,
                                    uint32_t u32Priority);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t m_u8UartSilenceMode;

static stc_ring_buffer_t m_stcRingBuf = {
    .u16InIdx = 0,
    .u16OutIdx = 0,
    .u16UsedSize = 0,
    .u16Capacity = sizeof (m_stcRingBuf.au8Buf),
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  UART TX Empty IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxEmpty_IrqCallback(void)
{
    uint8_t u8Data = 0u;
    en_flag_status_t enFlag = USART_GetFlag(USART_UNIT, USART_FLAG_TXE);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_TXE);

    if ((Set == enFlag) && (Enable == enState))
    {
        USART_SendId(USART_UNIT, UART_MASTER_STATION_ID);

        while (Reset == USART_GetFlag(USART_UNIT, USART_FLAG_TXE))   /* Wait Tx data register empty */
        {
        }

        if (Ok == RingBufRead(&m_stcRingBuf, &u8Data))
        {
            USART_SendData(USART_UNIT, (uint16_t)u8Data);
        }

        if (IS_RING_BUFFER_EMPYT(&m_stcRingBuf))
        {
            USART_FuncCmd(USART_UNIT, USART_INT_TXE, Disable);
            USART_FuncCmd(USART_UNIT, USART_INT_TC, Enable);
        }
    }
}

/**
 * @brief  UART TX Complete IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_TxComplete_IrqCallback(void)
{
    en_flag_status_t enFlag = USART_GetFlag(USART_UNIT, USART_FLAG_TC);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_TC);

    if ((Set == enFlag) && (Enable == enState))
    {
        /* Disable TX function */
        USART_FuncCmd(USART_UNIT, (USART_TX | USART_RX | USART_INT_TC), Disable);

        /* Enable RX/TX function */
        USART_FuncCmd(USART_UNIT, (USART_RX | USART_INT_RX), Enable);
    }
}

/**
 * @brief  UART RX IRQ callback.
 * @param  None
 * @retval None
 */
static void USART_Rx_IrqCallback(void)
{
    uint8_t u8RxData = 0U;
    en_flag_status_t enFlag = USART_GetFlag(USART_UNIT, USART_FLAG_RXNE);
    en_functional_state_t enState = USART_GetFuncState(USART_UNIT, USART_INT_RX);

    if ((Set == enFlag) && (Enable == enState))
    {
        u8RxData = (uint8_t)USART_RecData(USART_UNIT);

        if ((Reset == USART_GetFlag(USART_UNIT, USART_FLAG_MPB)) &&
            (USART_UART_NORMAL_MODE == UsartGetSilenceMode()))
        {
            RingBufWrite(&m_stcRingBuf, u8RxData);
        }
        else
        {
            if (UART_SLAVE_STATION_ID != u8RxData)
            {
                USART_SilenceCmd(USART_UNIT, Enable);
                UsartSetSilenceMode(USART_UART_SILENCE_MODE);
            }
            else
            {
                UsartSetSilenceMode(USART_UART_NORMAL_MODE);
            }
        }
    }
}

/**
 * @brief  UART RX Error IRQ callback.
 * @param  None.
 * @retval None
 */
static void USART_RxErr_IrqCallback(void)
{
    USART_ClearFlag(USART_UNIT, (USART_CLEAR_FLAG_FE | USART_CLEAR_FLAG_PE | USART_CLEAR_FLAG_ORE));
}

/**
 * @brief  Write ring buffer.
 * @param  [in] pstcBuffer              Pointer to a @ref stc_ring_buffer_t structure
 * @param  [in] u8Data                  Data to write
 * @retval An en_result_t enumeration value:
 *           - Ok: Write success.
 *           - ErrorBufferFull: Buffer is full.
 */
static en_result_t RingBufWrite(stc_ring_buffer_t *pstcBuffer, uint8_t u8Data)
{
    en_result_t enRet = ErrorBufferFull;

    if (pstcBuffer->u16UsedSize < pstcBuffer->u16Capacity)
    {
        pstcBuffer->au8Buf[pstcBuffer->u16InIdx++] = u8Data;
        pstcBuffer->u16InIdx %= pstcBuffer->u16Capacity;
        pstcBuffer->u16UsedSize++;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Write ring buffer.
 * @param  [in] pstcBuffer              Pointer to a @ref stc_ring_buffer_t structure
 * @param  [in] pu8Data                 Pointer to data buffer to read
 * @retval An en_result_t enumeration value:
 *           - Ok: Write success.
 *           - ErrorNotReady: Buffer is empty.
 */
static en_result_t RingBufRead(stc_ring_buffer_t *pstcBuffer, uint8_t *pu8Data)
{
    en_result_t enRet = ErrorNotReady;

    if (pstcBuffer->u16UsedSize)
    {
        *pu8Data = pstcBuffer->au8Buf[pstcBuffer->u16OutIdx++];
        pstcBuffer->u16OutIdx %= pstcBuffer->u16Capacity;
        pstcBuffer->u16UsedSize--;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set silence mode.
 * @param  [in] u8Mode                  Silence mode state
 *         This parameter can be one of the following values:
 *           @arg USART_UART_SILENCE_MODE:  UART silence mode
 *           @arg USART_UART_NORMAL_MODE:   UART normal mode
 * @retval None.
 */
static void UsartSetSilenceMode(uint8_t u8Mode)
{
    m_u8UartSilenceMode = u8Mode;
}

/**
 * @brief  Get silence mode.
 * @param  [in] None
 * @retval Returned value can be one of the following values:
 *           @arg USART_UART_SILENCE_MODE:  UART silence mode
 *           @arg USART_UART_NORMAL_MODE:   UART normal mode
 */
static uint8_t UsartGetSilenceMode(void)
{
    return m_u8UartSilenceMode;
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
 * @brief  Main function of UART multiple processor slave project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqSigninCfg;
    const stc_usart_multiprocessor_init_t stcUartMultiProcessorInit = {
        .u32Baudrate = 9600UL,
        .u32BitDirection = USART_LSB,
        .u32StopBit = USART_STOP_BITS_1,
        .u32DataWidth = USART_DATA_WIDTH_BITS_8,
        .u32ClkMode = USART_INTCLK_NONE_OUTPUT,
        .u32ClkPrescaler = USART_CLK_PRESCALER_DIV4,
        .u32OversamplingBits = USART_OVERSAMPLING_BITS_8,
        .u32NoiseFilterState = USART_NOISE_FILTER_DISABLE,
        .u32SbDetectPolarity = USART_SB_DETECT_FALLING,
    };

    /* Initialize system clock. */
    BSP_CLK_Init();
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV16 | CLK_PCLK1_DIV16 | \
                              CLK_PCLK2_DIV4  | CLK_PCLK3_DIV16 | \
                              CLK_PCLK4_DIV2  | CLK_EXCLK_DIV2  | CLK_HCLK_DIV1));

    /* Configure USART RX/TX pin. */
    GPIO_Unlock();
    GPIO_SetFunc(USART_RX_PORT, USART_RX_PIN, USART_RX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_Lock();

    /* Enable peripheral clock */
    PWC_Fcg3PeriphClockCmd(USART_FUNCTION_CLK_GATE, Enable);

    /* Set silence mode */
    UsartSetSilenceMode(USART_UART_SILENCE_MODE);

    /* Initialize UART function. */
    USART_MultiProcessorInit(USART_UNIT, &stcUartMultiProcessorInit);

    /* Register error IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_UNIT_ERR_INT_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_UNIT_ERR_INT_SRC;
    stcIrqSigninCfg.pfnCallback = &USART_RxErr_IrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Register RX IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_UNIT_RX_INT_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_UNIT_RX_INT_SRC;
    stcIrqSigninCfg.pfnCallback = &USART_Rx_IrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_00);

    /* Register TX IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_UNIT_TX_INT_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_UNIT_TX_INT_SRC;
    stcIrqSigninCfg.pfnCallback = &USART_TxEmpty_IrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Register TC IRQ handler && configure NVIC. */
    stcIrqSigninCfg.enIRQn = USART_UNIT_TCI_INT_IRQn;
    stcIrqSigninCfg.enIntSrc = USART_UNIT_TCI_INT_SRC;
    stcIrqSigninCfg.pfnCallback = &USART_TxComplete_IrqCallback;
    InstalIrqHandler(&stcIrqSigninCfg, DDL_IRQ_PRIORITY_DEFAULT);

    /* Enable RX/TX function */
    USART_FuncCmd(USART_UNIT, (USART_RX | USART_INT_RX), Enable);

    while (1)
    {
        if (!IS_RING_BUFFER_EMPYT(&m_stcRingBuf))
        {
            USART_FuncCmd(USART_UNIT, (USART_TX | USART_INT_TXE), Enable);
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
