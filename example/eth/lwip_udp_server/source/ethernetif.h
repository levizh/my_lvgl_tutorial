/**
 *******************************************************************************
 * @file  eth/lwip_udp_server/source/ethernetif.h
 * @brief Ethernet interface header file.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-06       Yangjp          First version
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
#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "lwip/err.h"
#include "lwip/netif.h"

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Ethernet PHY interface */
//#define ETH_INTERFACE_RMII

/* Extended PHY Registers */
#define PHY_PSMR                                (0x18U)   /*!< Power Saving Mode Register                         */
#define PHY_IISDR                               (0x1EU)   /*!< Interrupt Indicators and SNR Display Register      */
#define PHY_PSR                                 (0x1FU)   /*!< Page Select Register                               */

#define PHY_P7_RMSR                             (0x10U)   /*!< RMII Mode Setting Register                         */
#define PHY_P7_IWLFR                            (0x13U)   /*!< Interrupt, WOL Enable, and LED Function Registers  */

/* The following parameters will return to default values after a software reset */
#define PHY_EN_PWR_SAVE                         (0x8000U)   /*!< Enable Power Saving Mode               */

#define PHY_FLAG_AUTO_NEGO_ERROR                (0x8000U)   /*!< Auto-Negotiation Error Interrupt Flag  */
#define PHY_FLAG_SPEED_MODE_CHANGE              (0x4000U)   /*!< Speed Mode Change Interrupt Flag       */
#define PHY_FLAG_DUPLEX_MODE_CHANGE             (0x2000U)   /*!< Duplex Mode Change Interrupt Flag      */
#define PHY_FLAG_LINK_STATUS_CHANGE             (0x0800U)   /*!< Link Status Change Interrupt Flag      */

#define PHY_PAGE_ADDR_0                         (0x0000U)   /*!< Page Address 0 (default)               */
#define PHY_PAGE_ADDR_7                         (0x0007U)   /*!< Page Address 7                         */

#define PHY_RMII_CLK_DIR                        (0x1000U)   /*!< TXC direction in RMII Mode             */
#define PHY_RMII_MODE                           (0x0008U)   /*!< RMII Mode or MII Mode                  */
#define PHY_RMII_RXDV_CRSDV                     (0x0004U)   /*!< CRS_DV or RXDV select                  */

#define PHY_INT_LINK_CHANGE                     (0x2000U)   /*!< Link Change Interrupt Mask                         */
#define PHY_INT_DUPLEX_CHANGE                   (0x1000U)   /*!< Duplex Change Interrupt Mask                       */
#define PHY_INT_AUTO_NEGO_ERROR                 (0x0800U)   /*!< Auto-Negotiation Error Interrupt Mask              */
#define PHY_LED_WOL_SELECT                      (0x0400U)   /*!< LED and Wake-On-LAN Function Selection             */
#define PHY_LED_SELECT                          (0x0030U)   /*!< Traditional LED Function Selection.                */
#define PHY_LED_SELECT_00                       (0x0000U)   /*!< LED0: ACT(all)           LED1: LINK(100)           */
#define PHY_LED_SELECT_01                       (0x0010U)   /*!< LED0: LINK(ALL)/ACT(all) LED1: LINK(100)           */
#define PHY_LED_SELECT_10                       (0x0020U)   /*!< LED0: LINK(10)/ACT(all)  LED1: LINK(100)           */
#define PHY_LED_SELECT_11                       (0x0030U)   /*!< LED0: LINK(10)/ACT(10)   LED1: LINK(100)/ACT(100)  */
#define PHY_EN_10M_LED_FUNC                     (0x0001U)   /*!< Enable 10M LPI LED Function                        */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);

void EthernetIF_CheckLink(struct netif *netif);
void EthernetIF_UpdateLink(struct netif *netif);
void EthernetIF_LinkCallback(struct netif *netif);
void EthernetIF_NotifyLinkChange(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* __ETHERNETIF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
