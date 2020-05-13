/**
 *******************************************************************************
 * @file  hc32f4a0_usart.h
 * @brief This file contains all the functions prototypes of the USART driver
 *        library.
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
#ifndef __HC32F4A0_USART_H__
#define __HC32F4A0_USART_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_USART
 * @{
 */

#if (DDL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Types USART Global Types
 * @{
 */

/**
 * @brief UART mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32ClkPrescaler;           /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_Clock_Prescaler_Division */

    uint32_t u32Parity;                 /*!< Parity format.
                                             This parameter can be a value of @ref USART_Parity_Control */

    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Width_Bits */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32NoiseFilterState;       /*!< RX pin noise filter state.
                                             This parameter can be a value of @ref USART_Noise_Filter_State */

    uint32_t u32SbDetectPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Detect_Polarity */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_uart_init_t;

/**
 * @brief UART multiple-processor initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32ClkPrescaler;           /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_Clock_Prescaler_Division */

    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Width_Bits */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32NoiseFilterState;       /*!< RX pin noise filter state.
                                             This parameter can be a value of @ref USART_Noise_Filter_State */

    uint32_t u32SbDetectPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Detect_Polarity */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_multiprocessor_init_t;

/**
 * @brief LIN mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32ClkPrescaler;           /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_Clock_Prescaler_Division */

    uint32_t u32BmcClkPrescaler;        /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_LIN_Baudrate_Measure_Counter_Clock_Prescaler_Division */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32DetectBreakLen;         /*!< Detect break length.
                                             This parameter can be a value of @ref USART_LIN_Detect_Break_Length */

    uint32_t u32SendBreakLen;           /*!< Send break length.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Length */

    uint32_t u32SendBreakMode;          /*!< Send break mode.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Mode */
} stc_usart_lin_init_t;

/**
 * @brief Smart card mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32ClkPrescaler;           /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_Clock_Prescaler_Division */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */
} stc_usart_smartcard_init_t;

/**
 * @brief clock synchronization mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32ClkPrescaler;           /*!< Clock prescaler.
                                             This parameter can be a value of @ref USART_Clock_Prescaler_Division */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_clksync_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Macros USART Global Macros
 * @{
 */

/**
 * @defgroup USART_Flag USART Flag
 * @{
 */
#define USART_FLAG_PE                       (USART_SR_PE)       /*!< Parity error flag */
#define USART_FLAG_FE                       (USART_SR_FE)       /*!< Framing error flag */
#define USART_FLAG_ORE                      (USART_SR_ORE)      /*!< Overrun error flag */
#define USART_FLAG_BE                       (USART_SR_BE)       /*!< LIN bus error flag */
#define USART_FLAG_RXNE                     (USART_SR_RXNE)     /*!< Receive data register not empty flag */
#define USART_FLAG_TC                       (USART_SR_TC)       /*!< Transmission complete flag */
#define USART_FLAG_TXE                      (USART_SR_TXE)      /*!< Transmit data register empty flag */
#define USART_FLAG_RTOF                     (USART_SR_RTOF)     /*!< Receive timeout flag */
#define USART_FLAG_LBD                      (USART_SR_LBD)      /*!< LIN break signal detection flag */
#define USART_FLAG_WKUP                     (USART_SR_WKUP)     /*!< LIN wakeup signal detection flag */
#define USART_FLAG_MPB                      (USART_SR_MPB)      /*!< Receive processor ID flag */
/**
 * @}
 */

/**
 * @defgroup USART_Transmission_Type USART Transmission Type
 * @{
 */
#define USART_TRANSMISSION_ID               (USART_DR_MPID)
#define USART_TRANSMISSION_DATA             ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup USART_Clear_Flag USART Clear Flag
 * @{
 */
#define USART_CLEAR_FLAG_PE                 (USART_CR1_CPE)     /*!< Clear Parity error flag */
#define USART_CLEAR_FLAG_FE                 (USART_CR1_CFE)     /*!< Clear Framing error flag */
#define USART_CLEAR_FLAG_ORE                (USART_CR1_CORE)    /*!< Clear Overrun error flag */
#define USART_CLEAR_FLAG_RTOF               (USART_CR1_CRTOF)   /*!< Clear RX timeout flag */
#define USART_CLEAR_FLAG_BE                 (USART_CR1_CBE)     /*!< Clear LIN bus error flag */
#define USART_CLEAR_FLAG_WKUP               (USART_CR1_CWKUP)   /*!< Clear LIN wakeup signal flag */
#define USART_CLEAR_FLAG_LBD                (USART_CR1_CLBD)    /*!< Clear LIN break detection flag */
/**
 * @}
 */

/**
 * @defgroup USART_Transmit_Receive_Function USART Transmit/Receive Function
 * @{
 */
#define USART_RX                            (USART_CR1_RE)      /*!< USART RX function */
#define USART_TX                            (USART_CR1_TE)      /*!< USART TX function */
#define USART_RTO                           (USART_CR1_RTOE)    /*!< USART RX timerout function */
#define USART_INT_RX                        (USART_CR1_RIE)     /*!< USART receive data register not empty && receive error interrupt */
#define USART_INT_TXE                       (USART_CR1_TXEIE)   /*!< USART transmit data register empty interrupt */
#define USART_INT_TC                        (USART_CR1_TCIE)    /*!< USART transmission complete interrupt */
#define USART_INT_RTO                       (USART_CR1_RTOIE)   /*!< USART RX timerout interrupt */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Function USART LIN Function
 * @{
 */
#define USART_LIN                           (USART_CR2_LINEN)   /*!< USART LIN function */
#define USART_LIN_WKUP                      (USART_CR2_WKUPE)   /*!< USART LIN wakeup signal detect function */
#define USART_LIN_INT_WKUP                  (USART_CR2_WKUPIE)  /*!< USART LIN wakeup signal detect interrupt function */
#define USART_LIN_BUSERR                    (USART_CR2_BEE)     /*!< USART LIN bus error detect function */
#define USART_LIN_INT_BUSERR                (USART_CR2_BEIE)    /*!< USART LIN bus error detect interrupt function */
#define USART_LIN_INT_BREAK                 (USART_CR2_LBDIE)   /*!< USART LIN break field detect interrupt function */
/**
 * @}
 */

/**
 * @defgroup USART_Parity_Control USART Parity Control
 * @{
 */
#define USART_PARITY_NONE                   ((uint32_t)0UL)     /*!< Parity control disabled */
#define USART_PARITY_EVEN                   (USART_CR1_PCE)     /*!< Parity control enabled and Even Parity is selected */
#define USART_PARITY_ODD                    (USART_CR1_PCE | \
                                             USART_CR1_PS)      /*!< Parity control enabled and Odd Parity is selected */
/**
 * @}
 */

/**
 * @defgroup USART_Data_Width_Bits Data Width Bits
 * @{
 */
#define USART_DATA_WIDTH_BITS_9             (USART_CR1_M)       /*!< 9 bits word length : Start bit, 9 data bits, n stop bits */
#define USART_DATA_WIDTH_BITS_8             ((uint32_t)0UL)     /*!< 8 bits word length : Start bit, 8 data bits, n stop bits */
/**
 * @}
 */

/**
 * @defgroup USART_Oversampling_Bits USART Oversampling Bits
 * @{
 */
#define USART_OVERSAMPLING_BITS_8           (USART_CR1_OVER8)   /*!< Oversampling by 8 bits */
#define USART_OVERSAMPLING_BITS_16          ((uint32_t)0UL)     /*!< Oversampling by 16 bits */
/**
 * @}
 */

/**
 * @defgroup USART_Significant_Bit USART Significant Bit
 * @{
 */
#define USART_MSB                           (USART_CR1_ML)      /*!< MSB(Most Significant Bit) */
#define USART_LSB                           ((uint32_t)0UL)     /*!< LSB(Least Significant Bit) */
/**
 * @}
 */

/**
 * @defgroup USART_Noise_Filter_State USART Noise Filter State
 * @{
 */
#define USART_NOISE_FILTER_ENABLE           (USART_CR1_NFE)     /*!< Enable noise filter */
#define USART_NOISE_FILTER_DISABLE          ((uint32_t)0UL)     /*!< Disable noise filter */
/**
 * @}
 */

/**
 * @defgroup USART_Start_Bit_Detect_Polarity USART Start Bit Detect Polarity
 * @{
 */
#define USART_SB_DETECT_FALLING             (USART_CR1_SBS)     /*!< Detect RX pin falling edge */
#define USART_SB_DETECT_LOW                 ((uint32_t)0UL)     /*!< Detect RX pin low level */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Mode USART LIN Send Break Mode
 * @{
 */
#define USART_LIN_SEND_BREAK_MODE_SBK       ((uint32_t)0UL)     /*!< Start send break after USART_CR2 SBK bit set 1 value */
#define USART_LIN_SEND_BREAK_MODE_TDR       (USART_CR2_SBKM)    /*!< Start send break after USART_DR TDR wrtie 0x00 value */
/**
 * @}
 */

/**
 * @defgroup USART_Multiple_Processor_State USART Multiple Processor State
 * @{
 */
#define USART_MULTIPLE_PROCESSOR_ENABLE     (USART_CR2_MPE)     /*!< Enable multiple processor function */
#define USART_MULTIPLE_PROCESSOR_DISABLE    ((uint32_t)0UL)     /*!< Disable multiple processor function */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Detect_Break_Length USART LIN Detect Break Length
 * @{
 */
#define USART_LIN_DETECT_BREAK_10B          ((uint32_t)0UL)     /*!< Detect break 10-bit */
#define USART_LIN_DETECT_BREAK_11B          (USART_CR2_LBDL)    /*!< Detect break 11-bit */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Length USART LIN Send Break Length
 * @{
 */
#define USART_LIN_SEND_BREAK_10B            ((uint32_t)0UL)     /*!< Send break 10-bit */
#define USART_LIN_SEND_BREAK_11B            (USART_CR2_SBKL_0)  /*!< Send break 11-bit */
#define USART_LIN_SEND_BREAK_13B            (USART_CR2_SBKL_1)  /*!< Send break 13-bit */
#define USART_LIN_SEND_BREAK_14B            (USART_CR2_SBKL)    /*!< Send break 14-bit */
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Mode USART Clock Mode Selection
 * @{
 */
#define USART_EXTCLK                        (USART_CR2_CLKC_1)  /*!< Select external clock source. */
#define USART_INTCLK_OUTPUT                 (USART_CR2_CLKC_0)  /*!< Select internal clock source and output clock. */
#define USART_INTCLK_NONE_OUTPUT            ((uint32_t)0UL)     /*!< Select internal clock source and don't output clock */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Bits USART Stop Bits
 * @{
 */
#define USART_STOP_BITS_1                   ((uint32_t)0UL)     /*!< 1 stop bit */
#define USART_STOP_BITS_2                   (USART_CR2_STOP)    /*!< 2 stop bit */
/**
 * @}
 */

/**
 * @defgroup USART_DUPLEX_SEL USART Half-duplex/Full-duplex Selection
 * @{
 */
#define USART_FULLDUPLEX_MODE               ((uint32_t)0UL)     /*!< USART full-duplex mode */
#define USART_HALFDUPLEX_MODE               (USART_CR3_HDSEL)   /*!< USART half-duplex mode */
/**
 * @}
 */

/**
 * @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control RTS/CTS
 * @{
 */
#define USART_HWFLOWCTRL_NONE               ((uint32_t)0UL)     /*!< Disable USART hardware flow controle */
#define USART_HWFLOWCTRL_RTS                (USART_CR3_RTSE)    /*!< USART hardware flow control RTS mode */
#define USART_HWFLOWCTRL_CTS                (USART_CR3_CTSE)    /*!< USART hardware flow control CTS mode */
#define USART_HWFLOWCTRL_RTS_CTS            (USART_CR3_RTSE | \
                                             USART_CR3_CTSE)    /*!< USART hardware flow control RTS and CTS mode */
/**
 * @}
 */

/**
 * @defgroup USART_Smartcard_ETU_Clock USART Smartcard ETU Clock
 * @{
 */
#define USART_SC_ETU_CLK_32                 ((uint32_t)0UL)     /*!< 1 etu = 32/f */
#define USART_SC_ETU_CLK_64                 (USART_CR3_BCN_0)   /*!< 1 etu = 64/f */
#define USART_SC_ETU_CLK_128                (USART_CR3_BCN_1 | \
                                             USART_CR3_BCN_0)   /*!< 1 etu = 128/f */
#define USART_SC_ETU_CLK_256                (USART_CR3_BCN_2 | \
                                             USART_CR3_BCN_0)   /*!< 1 etu = 256/f */
#define USART_SC_ETU_CLK_372                (USART_CR3_BCN_2 | \
                                             USART_CR3_BCN_1)   /*!< 1 etu = 372/f */
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Prescaler_Division USART Clock Prescaler Division
 * @{
 */
#define USART_CLK_PRESCALER_DIV1            ((uint32_t)0UL)     /*!< PCLK */
#define USART_CLK_PRESCALER_DIV4            (USART_PR_PSC_0)    /*!< PCLK/4 */
#define USART_CLK_PRESCALER_DIV16           (USART_PR_PSC_1)    /*!< PCLK/16 */
#define USART_CLK_PRESCALER_DIV64           (USART_PR_PSC)      /*!< PCLK/64 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Baudrate_Measure_Counter_Clock_Prescaler_Division USART 
 *           LIN Baudrate Measure Counter Clock Prescaler Division
 * @{
 */
#define USART_LIN_BMC_CLK_PRESCALER_DIV1    ((uint32_t)0UL)     /*!< PCLK */
#define USART_LIN_BMC_CLK_PRESCALER_DIV2    (USART_PR_LBMPSC_0) /*!< PCLK/2 */
#define USART_LIN_BMC_CLK_PRESCALER_DIV4    (USART_PR_LBMPSC_1) /*!< PCLK/4 */
#define USART_LIN_BMC_CLK_PRESCALER_DIV8    (USART_PR_LBMPSC)   /*!< PCLK/8 */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Mode_Noise_Filter USART Stop Mode Noise_Filter
 * @{
 */
#define USART_STOP_MODE_FILTER_NONE         ((uint32_t)0UL)             /*!< Disable noise filter */
#define USART_STOP_MODE_FILTER_WIDTH_0P5_US (PERIC_USART1_NFC_NFE)      /*!< Filter range less 0.5uS */
#define USART_STOP_MODE_FILTER_WIDTH_1P0_US (PERIC_USART1_NFC_NFE | \
                                             PERIC_USART1_NFC_NFS_0)    /*!< Filter range less 1.0uS */
#define USART_STOP_MODE_FILTER_WIDTH_1P1_US (PERIC_USART1_NFC_NFE | \
                                             PERIC_USART1_NFC_NFS_1)    /*!< Filter range less 1.1uS */
#define USART_STOP_MODE_FILTER_WIDTH_2P0_US (PERIC_USART1_NFC_NFE | \
                                             PERIC_USART1_NFC_NFS)      /*!< Filter range less 2.0uS */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup USART_Global_Functions
 * @{
 */

/**
 * @brief  Enable USART silence mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
__STATIC_INLINE void USART_EnableSilenceMode(M4_USART_TypeDef *USARTx)
{
    SET_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
}

/**
 * @brief  Disable USART silence mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval None
 */
__STATIC_INLINE void USART_DisableSilenceMode(M4_USART_TypeDef *USARTx)
{
    CLEAR_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
}

/**
 * @brief  Enable USART loop function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
__STATIC_INLINE void USART_EnableLoop(M4_USART_TypeDef *USARTx)
{
    SET_REG32_BIT(USARTx->CR3, USART_CR3_LOOP);
}

/**
 * @brief  Disable USART loop function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval None
 */
__STATIC_INLINE void USART_DisableLoop(M4_USART_TypeDef *USARTx)
{
    CLEAR_REG32_BIT(USARTx->CR1, USART_CR3_LOOP);
}

/**
 * @brief  Request break sending
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
__STATIC_INLINE void USART_RequestBreakSending(M4_USART_TypeDef *USARTx)
{
    SET_REG32_BIT(USARTx->CR2, USART_CR2_SBK);
}

/**
 * @brief  Get request break sending status
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Sending break
 *           - Reset: Send break completely
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
__STATIC_INLINE en_flag_status_t USART_GetRequestBreakStatus(const M4_USART_TypeDef *USARTx)
{
    return READ_REG32_BIT(USARTx->CR2, USART_CR2_SBK) ? Set : Reset;
}

/**
 * @brief  USART receive data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Receive data
 */
__STATIC_INLINE uint16_t USART_RecData(const M4_USART_TypeDef *USARTx)
{
    return (uint16_t)(READ_REG32(USARTx->DR) >> USART_DR_RDR_POS);
}

/**
 * @brief  USART send data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 ** \param [in] u16Data                 Transmit data
 * @retval None
 */
__STATIC_INLINE void USART_SendData(M4_USART_TypeDef *USARTx,
                                            uint16_t u16Data)
{
    WRITE_REG32(USARTx->DR, ((uint32_t)u16Data & 0x01FFUL));
}

/**
 * @brief  USART send processor ID.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 ** \param [in] u16ID                   Processor ID
 * @retval None
 */
__STATIC_INLINE void USART_SendId(M4_USART_TypeDef *USARTx,
                                        uint16_t u16ID)
{
    WRITE_REG32(USARTx->DR, (USART_DR_MPID | ((uint32_t)u16ID & 0x01FFUL)));
}

en_result_t USART_UartInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_uart_init_t *pstcInit);
en_result_t USART_HalfduplexInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_uart_init_t *pstcInit);
en_result_t USART_UartStructInit(stc_usart_uart_init_t *pstcInit);
en_result_t USART_MultiProcessorInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_multiprocessor_init_t *pstcInit);
en_result_t USART_MultiProcessorStructInit(stc_usart_multiprocessor_init_t *pstcInit);
en_result_t USART_LinInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_lin_init_t *pstcInit);
en_result_t USART_LinStructInit(stc_usart_lin_init_t *pstcInit);
en_result_t USART_SmartcardInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_smartcard_init_t *pstcInit);
en_result_t USART_SmartcardStructInit(stc_usart_smartcard_init_t *pstcInit);
en_result_t USART_ClkSyncInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_clksync_init_t *pstcInit);
en_result_t USART_ClkSyncStructInit(stc_usart_clksync_init_t *pstcInit);
void USART_DeInit(M4_USART_TypeDef *USARTx);
void USART_FuncCmd(M4_USART_TypeDef *USARTx,
                        uint32_t u32Func,
                        en_functional_state_t enNewState);
en_functional_state_t USART_GetFuncState(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Func);
en_flag_status_t USART_GetFlag(const M4_USART_TypeDef *USARTx,
                                    uint32_t u32Flag);
void USART_ClearFlag(M4_USART_TypeDef *USARTx, uint32_t u32Flag);
void USART_SetTransmissionType(M4_USART_TypeDef *USARTx, uint32_t u32Type);
uint32_t USART_GetTransmissionType(const M4_USART_TypeDef *USARTx);
void USART_SetParity(M4_USART_TypeDef *USARTx, uint32_t u32Parity);
uint32_t USART_GetParity(const M4_USART_TypeDef *USARTx);
void USART_SetDataWidth(M4_USART_TypeDef *USARTx, uint32_t u32DataWidth);
uint32_t USART_GetDataWidth(const M4_USART_TypeDef *USARTx);
void USART_SetOversmaplingBits(M4_USART_TypeDef *USARTx,
                                        uint32_t u32OversamplingBits);
uint32_t USART_GetOversmaplingBits(const M4_USART_TypeDef *USARTx);
void USART_SetBitDirection(M4_USART_TypeDef *USARTx, uint32_t u32BitDir);
uint32_t USART_GetBitDirection(const M4_USART_TypeDef *USARTx);
void USART_SetSbDetectPolarity(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Polarity);
uint32_t USART_GetSbDetectPolarity(const M4_USART_TypeDef *USARTx);
void USART_SetClockMode(M4_USART_TypeDef *USARTx, uint32_t u32ClkMode);
uint32_t USART_GetClockMode(const M4_USART_TypeDef *USARTx);
void USART_SetStopBits(M4_USART_TypeDef *USARTx, uint32_t u32StopBits);
uint32_t USART_GetStopBits(const M4_USART_TypeDef *USARTx);
void USART_SetLinBreakMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode);
uint32_t USART_GetLinBreakMode(const M4_USART_TypeDef *USARTx);
void USART_SetDuplexMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode);
uint32_t USART_GetDuplexMode(const M4_USART_TypeDef *USARTx);
void USART_SetHwFlowCtrl(M4_USART_TypeDef *USARTx, uint32_t u32HwFlowCtrl);
uint32_t USART_GetHwFlowCtrl(const M4_USART_TypeDef *USARTx);
void USART_SetSmartcardEtuClk(M4_USART_TypeDef *USARTx,
                                    uint32_t u32EtuClk);
uint32_t USART_GetSmartcardEtuClk(const M4_USART_TypeDef *USARTx);
void USART_SetClkPrescaler(M4_USART_TypeDef *USARTx,
                                uint32_t u32PrescalerVal);
uint32_t USART_GetClkPrescaler(const M4_USART_TypeDef *USARTx);
void USART_SetLinCntClkPrescaler(M4_USART_TypeDef *USARTx,
                                        uint32_t u32PrescalerVal);
uint32_t USART_GetLinCntClkPrescaler(const M4_USART_TypeDef *USARTx);
void USART_SetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Filter);
uint32_t USART_GetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx);
void USART_LinFuncCmd(M4_USART_TypeDef *USARTx,
                            uint32_t u32Func,
                            en_functional_state_t enNewState);
en_functional_state_t USART_GetLinFuncState(const M4_USART_TypeDef *USARTx,
                                                    uint32_t u32Func);
uint32_t USART_GetLinMeasureCnt(const M4_USART_TypeDef *USARTx);
uint32_t USART_GetLinMeasureBaudrate(const M4_USART_TypeDef *USARTx);
void USART_SetLinDetectBreakLen(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Len);
uint32_t USART_GetLinDetectBreakLen(const M4_USART_TypeDef *USARTx);
void USART_SetLinSendBreakLen(M4_USART_TypeDef *USARTx, uint32_t u32Len);
uint32_t USART_GetLinSendBreakLen(const M4_USART_TypeDef *USARTx);
en_result_t USART_SetBaudrate(M4_USART_TypeDef *USARTx,
                                    uint32_t u32Baudrate,
                                    float32_t *pf32Err);

/**
 * @}
 */

#endif /* DDL_USART_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
