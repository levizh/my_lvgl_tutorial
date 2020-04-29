/**
 *******************************************************************************
 * @file  usart/lin_master/source/main.c
 * @brief This example demonstrates LIN data receive and transfer.
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
#include "lin.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup LIN_Master
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief Key state definition
 */
typedef enum
{
    KeyIdle,
    KeyRelease,
} en_key_state_t;

/**
 * @brief Key instance structure definition
 */
typedef struct
{
    uint8_t u8Port;                     /*!< GPIO_PORT_x: x can be (0~7, 12~14) to select the GPIO peripheral */

    uint8_t u8Pin;                      /*!< GPIO_PIN_x: x can be (0~7) to select the PIN index */

    en_pin_state_t enPressPinState;     /*!< Pin level state when key is pressed */
} stc_key_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Key Port/Pin definition */
#define KEY_PORT                        (GPIO_PORT_A)
#define KEY_PIN                         (GPIO_PIN_00)

/* Red LED Port/Pin definition */
#define LED_R_PORT                      (GPIO_PORT_A)
#define LED_R_PIN                       (GPIO_PIN_00)
#define LED_R_ON()                      (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_OFF()                     (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_TOGGLE()                  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))

/* Green LED Port/Pin definition */
#define LED_G_PORT                      (GPIO_PORT_B)
#define LED_G_PIN                       (GPIO_PIN_00)
#define LED_G_ON()                      (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))
#define LED_G_OFF()                     (GPIO_SetPins(LED_G_PORT, LED_G_PIN))
#define LED_G_TOGGLE()                  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))

/* USART Channel && RX/TX Port/Pin definition */
#define LIN_CH                          (M4_USART10)

#define LIN_RX_PORT                     (GPIO_PORT_I)   /* PI9: USART10_RX */
#define LIN_RX_PIN                      (GPIO_PIN_09)
#define LIN_RX_GPIO_FUNC                (GPIO_FUNC_39_USART10_RX)

#define LIN_TX_PORT                     (GPIO_PORT_I)   /* PI11: USART10_TX */
#define LIN_TX_PIN                      (GPIO_PIN_11)
#define LIN_TX_GPIO_FUNC                (GPIO_FUNC_38_USART10_TX)

/* Interrupt number definition */
#define LIN_RX_IRQn                     (Int000_IRQn)
#define LIN_RXERR_IRQn                  (Int001_IRQn)
#define LIN_BREAKWKUP_IRQn              (Int001_IRQn)

#define LIN_MASTER_REQUESET_FRAME_PID   (0x3CU)
#define LIN_SLAVE_RESPONSE_FRAME_PID    (0x3DU)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);
static en_key_state_t KeyGetState(const stc_key_t *pstcKey);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

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
 * @brief  Configure RGB LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
}

/**
 * @brief  Get key state.
 * @param  [in] pstcKey    Pointer to stc_key_t structure
 * @retval An en_result_t enumeration value:
 *           - KeyIdle: Key isn't pressed.
 *           - KeyRelease: Released after key is pressed.
 */
static en_key_state_t KeyGetState(const stc_key_t *pstcKey)
{
    en_key_state_t enKeyState = KeyIdle;

    if (NULL != pstcKey)
    {
        if (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
        {
            DDL_Delay1ms(20UL);

            if (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
            {
                while (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
                {
                    ;
                }
                enKeyState = KeyRelease;
            }
        }
    }

    return enKeyState;
}

/**
 * @brief  Main function of LIN master project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint8_t i;
    const stc_key_t stcKeySw = {
        .u8Port = KEY_PORT,
        .u8Pin = KEY_PIN,
        .enPressPinState = Pin_Reset,
    };

    static stc_lin_frame_t m_stcTxFrame = {
        .u8PID = LIN_MASTER_REQUESET_FRAME_PID,
    };

    static stc_lin_frame_t m_stcRxFrame = {
        .u8PID = LIN_SLAVE_RESPONSE_FRAME_PID,
    };

    static stc_lin_hanlde_t m_stcLinHandle = {
        .USARTx = LIN_CH,
        .u32LinMode = LIN_MASTER,
        .stcLinInit = {
            .u32Baudrate = 9600UL,
            .u32ClkMode = USART_INTCLK_NONE_OUTPUT,
            .u32ClkPrescaler = USART_CLK_PRESCALER_DIV4,
            .u32BmcClkPrescaler = USART_LIN_BMC_CLK_PRESCALER_DIV4,
            .u32OversamplingBits = USART_OVERSAMPLING_BITS_8,
            .u32SbDetectPolarity = USART_SB_DETECT_FALLING,
            .u32SendBreakLen = USART_LIN_SEND_BREAK_13B,
            .u32SendBreakMode = USART_LIN_SEND_BREAK_MODE_SBK,
        },
        .stcPinCfg = {
            .u16RxPort = LIN_RX_PORT,
            .u16RxPin = LIN_RX_PIN,
            .u16RxPinFunc = LIN_RX_GPIO_FUNC,
            .u16TxPort = LIN_TX_PORT,
            .u16TxPin = LIN_TX_PIN,
            .u16RxPinFunc = LIN_TX_GPIO_FUNC,
        },
        .stcIrqnCfg = {
            .RxIntIRQn = LIN_RX_IRQn,
            .RxErrIntIRQn = LIN_RXERR_IRQn,
            .BreakWkupIntIRQn = LIN_BREAKWKUP_IRQn,
        },
        .enLinState = LinStateWakeup,
    };

    /* Configure system clock. */
    SystemClockConfig();

    /* Configure LED. */
    LedConfig();

    /* Configure LIN transceiver chip sleep pin. */
    #warning "todo"

    LIN_Init(&m_stcLinHandle);

    while (1)
    {
        /* Wait key release */
        while (KeyRelease !=  KeyGetState(&stcKeySw))
        {
            ;
        }

        /* Send wakeup signal */
        LIN_SendWakeupSignal(&m_stcLinHandle);

        /* Node must prepare to receive frame in range of 100ms after wakeup signal*/
        DDL_Delay1ms(100UL);

        /* LIN master send frame */
        LIN_MASTER_SendFrame(&m_stcLinHandle, &m_stcTxFrame);

        /* LIN master receive frame */
        LIN_MASTER_RecFrame(&m_stcLinHandle, &m_stcRxFrame, LIN_REC_WAITING_FOREVER);

        /* Compare TX/RX frame data */
        if (memcmp(m_stcRxFrame.au8Data , m_stcTxFrame.au8Data, sizeof (m_stcTxFrame.au8Data)) == 0)
        {
            LED_R_OFF();
            LED_G_TOGGLE();
        }
        else
        {
            LED_R_ON();
            LED_G_OFF();
        }

        for (i = 0U; i < sizeof (m_stcTxFrame.au8Data); i++)
        {
            m_stcTxFrame.au8Data[i]++;
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
