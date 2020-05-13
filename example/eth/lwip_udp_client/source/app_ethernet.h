/**
 *******************************************************************************
 * @file  eth/lwip_udp_client/source/app_ethernet.h
 * @brief Header for app_ethernet.c module.
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
#ifndef __APP_ETHERNET_H__
#define __APP_ETHERNET_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "lwip/netif.h"

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Number of milliseconds when to check for link status from PHY */
#ifndef LINK_TIMER_INTERVAL
    #define LINK_TIMER_INTERVAL                 (1000U)
#endif

/* DHCP process states */
#define DHCP_OFF                                (0U)
#define DHCP_START                              (1U)
#define DHCP_WAIT_ADDRESS                       (2U)
#define DHCP_ADDRESS_ASSIGNED                   (3U)
#define DHCP_TIMEOUT                            (4U)
#define DHCP_LINK_DOWN                          (5U)

/* Enable DHCP, if disabled, Use static address */
//#define USE_DHCP

/* Static IP Address */
#define IP_ADDR0                                (192U)
#define IP_ADDR1                                (168U)
#define IP_ADDR2                                (1U)
#define IP_ADDR3                                (20U)

/* Static Netmask */
#define NETMASK_ADDR0                           (255U)
#define NETMASK_ADDR1                           (255U)
#define NETMASK_ADDR2                           (255U)
#define NETMASK_ADDR3                           (0U)

/* Static Gateway Address*/
#define GW_ADDR0                                (192U)
#define GW_ADDR1                                (168U)
#define GW_ADDR2                                (1U)
#define GW_ADDR3                                (1U)

/* Destination IP Address*/
#define DEST_IP_ADDR0                           (192U)
#define DEST_IP_ADDR1                           (168U)
#define DEST_IP_ADDR2                           (1U)
#define DEST_IP_ADDR3                           (120U)

/* Define the UDP remote connection port */
#define UDP_SERVER_PORT                         (3000U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void Ethernet_NotifyConnStatus(struct netif *netif);
void LwIP_PeriodicHandle(struct netif *netif);

#ifdef USE_DHCP
void LwIP_DhcpProcess(struct netif *netif);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __APP_ETHERNET_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
