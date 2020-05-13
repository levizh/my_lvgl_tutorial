/**
 *******************************************************************************
 * @file  usart/clksync_polling/source/main.c
 * @brief This example demonstrates CLKSYNC data receive and transfer by polling.
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
#include <string.h>
#include "hc32_ddl.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup CLKSYNC_Polling
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Key definition */
#define USER_KEY                        (BSP_KEY_1)

/* CLKSYNC CK/RX/TX Port/Pin definition */
#define CLKSYNC_CK_PORT                 (GPIO_PORT_E)   /* PE3: USART6_CK */
#define CLKSYNC_CK_PIN                  (GPIO_PIN_03)
#define CLKSYNC_CK_GPIO_FUNC            (GPIO_FUNC_7)

#define CLKSYNC_RX_PORT                 (GPIO_PORT_H)   /* PH6: USART6_RX */
#define CLKSYNC_RX_PIN                  (GPIO_PIN_06)
#define CLKSYNC_RX_GPIO_FUNC            (GPIO_FUNC_37_USART6_RX)

#define CLKSYNC_TX_PORT                 (GPIO_PORT_E)   /* PE6: USART6_TX */
#define CLKSYNC_TX_PIN                  (GPIO_PIN_06)
#define CLKSYNC_TX_GPIO_FUNC            (GPIO_FUNC_36_USART6_TX)

/* USART unit definition */
#define CLKSYNC_UNIT                    (M4_USART6)
#define USART_FUNCTION_CLK_GATE         (PWC_FCG3_USART6)

/* Timeout max definition  */
#define TIMEOUT_MAX                     (0xFFFFFFFFUL)

/* CLKSYNC device mode definition */
#define CLKSYNC_MASTER_MODE             (0U)
#define CLKSYNC_SLAVE_MODE              (1U)

/* USART master or slave mode selection */
#define CLKSYNC_DEVICE_MODE             (CLKSYNC_SLAVE_MODE)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static en_result_t USART_WaitOnFlagUntilTimeout(M4_USART_TypeDef *USARTx,
                                                uint32_t u32Flag,
                                                en_flag_status_t enStatus,
                                                uint32_t u32TickStart,
                                                uint32_t u32Timeout);
static en_result_t CLKSYNC_TransmitReceive(M4_USART_TypeDef *USARTx,
                                           const uint8_t au8TxData[],
                                           uint8_t au8RxData[],
                                           uint32_t u32Size,
                                           uint32_t u32Timeout);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  This function handles USART Communication Timeout.
 * @param  [in] USARTx                  pointer to a USART instance.
 * @param  [in] u32Flag                 specifies the USART flag to check.
 * @param  [in] enStatus                The new Flag status (Set or Reset).
 * @param  [in] u32TickStart            Tick start value.
 * @param  [in] u32Timeout              Timeout duration.
 * @retval An en_result_t enumeration value:
 *           - Ok: success
 *           - ErrorTimeout: timeout
 */
static en_result_t USART_WaitOnFlagUntilTimeout(M4_USART_TypeDef *USARTx,
                                                uint32_t u32Flag,
                                                en_flag_status_t enStatus,
                                                uint32_t u32TickStart,
                                                uint32_t u32Timeout)
{
    en_result_t enRet = Ok;

    /* Wait until flag is set */
    while((USART_GetFlag(USARTx, u32Flag) ? Set : Reset) == enStatus)
    {
        /* Check for the Timeout */
        if (TIMEOUT_MAX - u32Timeout)
        {
            if (((SysTick_GetTick() - u32TickStart) > u32Timeout) || (!u32Timeout))
            {
                enRet = ErrorTimeout;
                break;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Send && receive an amount of data in full-duplex mode (blocking mode).
 * @param  [in] USARTx                  Pointer to a USART instance.
 * @param  [in] au8TxData               Data transmitted buffer
 * @param  [out] au8RxData              Data received buffer
 * @param  [in] u32Size                 Amount of data to be sent
 * @param  [in] u32Timeout              Timeout duration
 * @retval An en_result_t enumeration value:
 *           - Ok: success
 *           - ErrorInvalidParameter: USARTx/pu8TxData/pu8RxData/u16Size is invalid
 */
static en_result_t CLKSYNC_TransmitReceive(M4_USART_TypeDef *USARTx,
                                           const uint8_t au8TxData[],
                                           uint8_t au8RxData[],
                                           uint32_t u32Size,
                                           uint32_t u32Timeout)
{
    uint32_t i = 0UL;
    uint32_t u32Flag;
    uint32_t u32TickStart = 0UL;
    uint32_t u32XferCount = u32Size;
    en_result_t enRet = ErrorInvalidParameter;

    if(USARTx && au8TxData && au8RxData && u32Size)
    {
        enRet = Ok;

        /* Init tickstart for timeout managment */
        u32TickStart = SysTick_GetTick();

        /* Check the remain data to be received */
        while (u32XferCount > 0UL)
        {
            u32XferCount--;

            /* Wait for TX empty or TX complete flag in order to write data in DR */
            u32Flag = (USART_INTCLK_OUTPUT == USART_GetClockMode(USARTx)) ? USART_FLAG_TC : USART_FLAG_TXE;
            if (USART_WaitOnFlagUntilTimeout(USARTx, u32Flag, Reset, u32TickStart, u32Timeout) != Ok)
            {
                enRet = ErrorTimeout;
            }
            else
            {
                USART_SendData(USARTx, (uint16_t)(au8TxData[i]));

                /* Wait for RXNE Flag */
                if (USART_WaitOnFlagUntilTimeout(USARTx, USART_FLAG_RXNE, Reset, u32TickStart, u32Timeout) != Ok)
                {
                    enRet = ErrorTimeout;
                }
                else
                {
                    /* Receive data */
                    au8RxData[i] = (uint8_t)USART_RecData(USARTx);
                }
                i++;
            }

            if (enRet != Ok)
            {
                break;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Main function of CLKSYNC polling project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_usart_clksync_init_t stcClksyncInit;
    /* Buffer used for transmission */
    char au8TxBuffer[] = "CLKSYNC TX/RX example: Communication between two boards using usart interface!";
    /* Buffer used for reception */
    uint8_t au8RxBuffer[(ARRAY_SZ(au8TxBuffer))];

    /* Initialize system clock. */
    BSP_CLK_Init();
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV16 | CLK_PCLK1_DIV16 | \
                              CLK_PCLK2_DIV4  | CLK_PCLK3_DIV16 | \
                              CLK_PCLK4_DIV2  | CLK_EXCLK_DIV2  | CLK_HCLK_DIV1));

    /* Configure system tick. */
    SysTick_Init(100UL);

    /* Initialize IO. */
    BSP_IO_Init();

    /* Initialize LED. */
    BSP_LED_Init();

    /* Initialize key. */
    BSP_KEY_Init();

    /* Configure USART CK/RX/TX pin. */
    GPIO_SetFunc(CLKSYNC_CK_PORT, CLKSYNC_CK_PIN, CLKSYNC_CK_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(CLKSYNC_RX_PORT, CLKSYNC_RX_PIN, CLKSYNC_RX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(CLKSYNC_TX_PORT, CLKSYNC_TX_PIN, CLKSYNC_TX_GPIO_FUNC, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock */
    PWC_Fcg3PeriphClockCmd(USART_FUNCTION_CLK_GATE, Enable);

    /* Initialize CLKSYNC function. */
    USART_ClkSyncStructInit(&stcClksyncInit);
    stcClksyncInit.u32Baudrate = 38400UL;
#if (CLKSYNC_DEVICE_MODE == CLKSYNC_MASTER_MODE)
    stcClksyncInit.u32ClkMode = USART_INTCLK_OUTPUT;
#else
    stcClksyncInit.u32ClkMode = USART_EXTCLK;
#endif
    USART_ClkSyncInit(CLKSYNC_UNIT, &stcClksyncInit);

    /* Enable RX/TX function */
    USART_FuncCmd(CLKSYNC_UNIT, (USART_RX | USART_TX), Enable);

    /* User key */
    while (Reset == BSP_KEY_GetStatus(USER_KEY))
    {
    }

    /* Start the transmission process*/
    CLKSYNC_TransmitReceive(CLKSYNC_UNIT, (uint8_t *)au8TxBuffer, au8RxBuffer, (ARRAY_SZ(au8TxBuffer)), TIMEOUT_MAX);

    /* Compare m_u8TxBuffer and m_u8RxBuffer data */
    if (memcmp(au8TxBuffer, au8RxBuffer, (ARRAY_SZ(au8TxBuffer))) == 0)
    {
        BSP_LED_On(LED_BLUE);
    }
    else
    {
        BSP_LED_On(LED_RED);
    }

    while (1)
    {
    }
}

/**
 * @brief  systick callback function
 * @param  [in]  None
 * @retval None
 *
 */
void SysTick_IrqHandler(void)
{
    SysTick_IncTick();
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
