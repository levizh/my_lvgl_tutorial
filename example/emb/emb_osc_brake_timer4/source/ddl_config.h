/**
 *******************************************************************************
 * @file  emb/emb_osc_brake_timer4/source/ddl_config.h
 * @brief This file contains HC32 Series Device Driver Library usage management.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-03       Yangjp          First version
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
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
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
#ifndef __DDL_CONFIG_H__
#define __DDL_CONFIG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Chip module on-off define */
#define DDL_ON                                      (1u)
#define DDL_OFF                                     (0u)

/**
 * @brief This is the list of modules to be used in the Device Driver Library.
 * Select the modules you need to use to DDL_ON.
 * @note DDL_ICG_ENABLE must be turned on(DDL_ON) to ensure that the chip works
 * properly.
 * @note DDL_UTILITY_ENABLE must be turned on(DDL_ON) if using Device Driver
 * Library.
 * @note DDL_PRINT_ENABLE must be turned on(DDL_ON) if using printf function.
 */
#define DDL_ICG_ENABLE                              (DDL_ON)
#define DDL_UTILITY_ENABLE                          (DDL_ON)
#define DDL_PRINT_ENABLE                            (DDL_OFF)

#define DDL_ADC_ENABLE                              (DDL_OFF)
#define DDL_AES_ENABLE                              (DDL_OFF)
#define DDL_CAN_ENABLE                              (DDL_OFF)
#define DDL_CLK_ENABLE                              (DDL_ON)
#define DDL_CMP_ENABLE                              (DDL_OFF)
#define DDL_CRC_ENABLE                              (DDL_OFF)
#define DDL_CTC_ENABLE                              (DDL_OFF)
#define DDL_DAC_ENABLE                              (DDL_OFF)
#define DDL_DCU_ENABLE                              (DDL_OFF)
#define DDL_DMA_ENABLE                              (DDL_OFF)
#define DDL_DMC_ENABLE                              (DDL_OFF)
#define DDL_DVP_ENABLE                              (DDL_OFF)
#define DDL_EFM_ENABLE                              (DDL_OFF)
#define DDL_EMB_ENABLE                              (DDL_ON)
#define DDL_ETH_ENABLE                              (DDL_OFF)
#define DDL_EVENT_PORT_ENABLE                       (DDL_OFF)
#define DDL_FCM_ENABLE                              (DDL_OFF)
#define DDL_FMAC_ENABLE                             (DDL_OFF)
#define DDL_GPIO_ENABLE                             (DDL_ON)
#define DDL_HASH_ENABLE                             (DDL_OFF)
#define DDL_HRPWM_ENABLE                            (DDL_OFF)
#define DDL_I2C_ENABLE                              (DDL_OFF)
#define DDL_I2S_ENABLE                              (DDL_OFF)
#define DDL_INTERRUPTS_ENABLE                       (DDL_ON)
#define DDL_KEYSCAN_ENABLE                          (DDL_OFF)
#define DDL_MAU_ENABLE                              (DDL_OFF)
#define DDL_MPU_ENABLE                              (DDL_OFF)
#define DDL_NFC_ENABLE                              (DDL_OFF)
#define DDL_OTS_ENABLE                              (DDL_OFF)
#define DDL_PWC_ENABLE                              (DDL_ON)
#define DDL_QSPI_ENABLE                             (DDL_OFF)
#define DDL_RMU_ENABLE                              (DDL_OFF)
#define DDL_RTC_ENABLE                              (DDL_OFF)
#define DDL_SDIOC_ENABLE                            (DDL_OFF)
#define DDL_SMC_ENABLE                              (DDL_OFF)
#define DDL_SPI_ENABLE                              (DDL_OFF)
#define DDL_SRAM_ENABLE                             (DDL_OFF)
#define DDL_SWDT_ENABLE                             (DDL_OFF)
#define DDL_TMR0_ENABLE                             (DDL_OFF)
#define DDL_TMR2_ENABLE                             (DDL_OFF)
#define DDL_TMR4_ENABLE                             (DDL_ON)
#define DDL_TMR6_ENABLE                             (DDL_OFF)
#define DDL_TMRA_ENABLE                             (DDL_OFF)
#define DDL_TRNG_ENABLE                             (DDL_OFF)
#define DDL_USART_ENABLE                            (DDL_OFF)
#define DDL_USBFS_ENABLE                            (DDL_OFF)
#define DDL_USBHS_ENABLE                            (DDL_OFF)
#define DDL_VBAT_ENABLE                             (DDL_OFF)
#define DDL_WDT_ENABLE                              (DDL_OFF)

/* Midware module on-off define */
#define MW_ON                                       (1u)
#define MW_OFF                                      (0u)

/**
 * @brief This is the list of midware modules to be used.
 * Select the modules you need to use to MW_ON.
 */
#define MW_FS_ENABLE                                (MW_OFF)
#define MW_SDRAM_IS42S16400J7TLI_ENABLE             (MW_OFF)
#define MW_SRAM_IS62WV51216_ENABLE                  (MW_OFF)
#define MW_LIN_ENABLE                               (MW_OFF)
#define MW_NANDFLASH_MT29F2G08AB_ENABLE             (MW_OFF)
#define MW_W25QXX_ENABLE                            (MW_OFF)
#define MW_WM8731_ENABLE                            (MW_OFF)

/**
 * @brief Ethernet and PHY Configuration.
 * @note  PHY delay these values are based on a 1 ms Systick interrupt.
 */
/* MAC ADDRESS */
#define ETH_MAC_ADDR0                   ((uint8_t)2U)
#define ETH_MAC_ADDR1                   ((uint8_t)0U)
#define ETH_MAC_ADDR2                   ((uint8_t)0U)
#define ETH_MAC_ADDR3                   ((uint8_t)0U)
#define ETH_MAC_ADDR4                   ((uint8_t)0U)
#define ETH_MAC_ADDR5                   ((uint8_t)0U)

/* Ethernet driver buffers size and count */
#define ETH_TXBUF_SIZE                  ETH_PACKET_MAX_SIZE   /* Buffer size for receive              */
#define ETH_RXBUF_SIZE                  ETH_PACKET_MAX_SIZE   /* Buffer size for transmit             */
#define ETH_TXBUF_NUMBER                ((uint32_t)4UL)       /* 4 Rx buffers of size ETH_RX_BUF_SIZE */
#define ETH_RXBUF_NUMBER                ((uint32_t)4UL)       /* 4 Tx buffers of size ETH_TX_BUF_SIZE */

/* PHY Address*/
#define PHY_ADDRESS                     0x00U                 /* RTL8201F */

/* PHY Configuration delay */
#define PHY_HW_RESET_DEALY              ((uint32_t)0x00000020UL)
#define PHY_RESET_DELAY                 ((uint32_t)0x00000040UL)
#define PHY_CONFIG_DELAY                ((uint32_t)0x0000007FUL)
#define PHY_READ_TIMEOUT                ((uint32_t)0x000000FFUL)
#define PHY_WRITE_TIMEOUT               ((uint32_t)0x000000FFUL)

/* Common PHY Registers */
#define PHY_BCR                         ((uint16_t)0x00U)    /*!< Basic Control Register */
#define PHY_BSR                         ((uint16_t)0x01U)    /*!< Basic Status Register  */

#define PHY_SOFT_RESET                  ((uint16_t)0x8000U)  /*!< PHY Soft Reset                       */
#define PHY_LOOPBACK                    ((uint16_t)0x4000U)  /*!< Select loop-back mode                */
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100U)  /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000U)  /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100U)  /*!< Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000U)  /*!< Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION             ((uint16_t)0x1000U)  /*!< Enable auto-negotiation function     */
#define PHY_POWERDOWN                   ((uint16_t)0x0800U)  /*!< Select the power down mode           */
#define PHY_ISOLATE                     ((uint16_t)0x0400U)  /*!< Isolate PHY from MII                 */
#define PHY_RESTART_AUTONEGOTIATION     ((uint16_t)0x0200U)  /*!< Restart auto-negotiation function    */

#define PHY_100BASE_TX_FD               ((uint16_t)0x4000U)  /*!< 100Base-TX full duplex support       */
#define PHY_100BASE_TX_HD               ((uint16_t)0x2000U)  /*!< 100Base-TX half duplex support       */
#define PHY_10BASE_T_FD                 ((uint16_t)0x1000U)  /*!< 10Base-T full duplex support         */
#define PHY_10BASE_T_HD                 ((uint16_t)0x0800U)  /*!< 10Base-T half duplex support         */
#define PHY_AUTONEGO_COMPLETE           ((uint16_t)0x0020U)  /*!< Auto-Negotiation process completed   */
#define PHY_LINK_STATUS                 ((uint16_t)0x0004U)  /*!< Valid link established               */
#define PHY_JABBER_DETECTION            ((uint16_t)0x0002U)  /*!< Jabber condition detected            */

/* Extended PHY Registers */
#define PHY_RMSR                        ((uint16_t)0x10U)    /*!< PHY RMII Mode Setting Register                         */
#define PHY_IWLFR                       ((uint16_t)0x13U)    /*!< PHY Interrupt, WOL Enable, and LEDs Function Registers */
#define PHY_IISDR                       ((uint16_t)0x1EU)    /*!< PHY Interrupt Indicators and SNR Display Register      */

/* The following parameters will return to default values after a software reset */
#define PHY_RMII_CLK_DIR                ((uint16_t)0x1000U)  /*!< TXC direction in RMII Mode, 0: Output, 1: Input        */
#define PHY_RMII_MODE                   ((uint16_t)0x0008U)  /*!< RMII Mode, 0: MII Mode, 1: RMII Mode                   */
#define PHY_RMII_RXDV_CRSDV             ((uint16_t)0x0004U)  /*!< RXDV select, 0: CRS_DV, 1: RXDV                        */

#define PHY_LINK_INT_EN                 ((uint16_t)0x2000U)  /*!< Link Change Interrupt Mask.  */

#define PHY_LINK_INTERRUPT              ((uint16_t)0x0800U)  /*!< Link Status Change Interrupt */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __DDL_CONFIG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
