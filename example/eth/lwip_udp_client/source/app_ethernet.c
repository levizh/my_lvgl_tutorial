/**
 *******************************************************************************
 * @file  eth/lwip_udp_client/source/app_ethernet.c
 * @brief Ethernet DHCP and Connect status module.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-26       Yangjp          First version
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
#include "lwip/dhcp.h"
#include "app_ethernet.h"
#include "ethernetif.h"
#ifdef USE_LCD
#include "lcd_log.h"
#endif


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#ifdef USE_DHCP
#define DHCP_MAX_TRIES                  4
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
uint32_t u32LinkTimer = 0UL;
#ifdef USE_DHCP
uint32_t u32DHCPfineTimer = 0UL;
__IO uint8_t u8DHCPState = DHCP_OFF;
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Notify network connect status of Ethernet.
 * @param  [in] netif                   Pointer to a struct netif structure
 * @retval None
 */
void Ethernet_NotifyConnStatus(struct netif *netif)
{
    if (netif_is_up(netif))
    {
#ifdef USE_DHCP
        u8DHCPState = DHCP_START;
#else
    #ifdef USE_LCD
        uint8_t iptxt[20];
        sprintf((char*)iptxt, "%s", ip4addr_ntoa((const ip4_addr_t*)&netif->ip_addr));
        LCD_UsrLog("Static IP address: %s\n", iptxt);
    #else
        /* Turn On LED BULE to indicate ETH and LwIP init success*/
        BSP_LED_On(LED_BLUE);
    #endif /* USE_LCD */
#endif /* USE_DHCP */
    }
    else
    {
#ifdef USE_DHCP
        u8DHCPState = DHCP_LINK_DOWN;
#endif  /* USE_DHCP */

#ifdef USE_LCD
        LCD_UsrLog("The network cable is not connected \n");
#else
        /* Turn On LED RED to indicate ETH and LwIP init error */
        BSP_LED_On(LED_RED);
#endif /* USE_LCD */
    }
}

/**
 * @brief  Notify link status change.
 * @param  [in] netif                   Pointer to a struct netif structure
 * @retval None
 */
void ethernetif_notify_link_change(struct netif *netif)
{
#ifndef USE_DHCP
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;
#endif

    if (netif_is_link_up(netif))
    {
#ifdef USE_LCD
        LCD_UsrLog("The network cable is now connected \n");
#else
        BSP_LED_Off(LED_RED);
        BSP_LED_On(LED_BLUE);
#endif /* USE_LCD */

#ifdef USE_DHCP
        /* Update DHCP state machine */
        u8DHCPState = DHCP_START;
#else
        IP_ADDR4(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
        IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
        IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
        netif_set_addr(netif, &ipaddr, &netmask, &gw);
    #ifdef USE_LCD
        uint8_t iptxt[20];
        sprintf((char*)iptxt, "%s", ip4addr_ntoa((const ip4_addr_t*)&netif->ip_addr));
        LCD_UsrLog("Static IP address: %s\n", iptxt);
    #endif /* USE_LCD */
#endif /* USE_DHCP */

        /* When the netif is fully configured this function must be called. */
        netif_set_up(netif);
    }
    else
    {
#ifdef USE_DHCP
        u8DHCPState = DHCP_LINK_DOWN;
#endif /* USE_DHCP */

        /*  When the netif link is down this function must be called. */
        netif_set_down(netif);

#ifdef USE_LCD
        LCD_UsrLog("The network cable is not connected \n");
#else
        BSP_LED_Off(LED_BLUE);
        BSP_LED_On(LED_RED);
#endif /* USE_LCD */
    }
}

/**
 * @brief  LwIP periodic handle
 * @param  [in] netif                   Pointer to a struct netif structure
 * @retval None
 */
void LwIP_PeriodicHandle(struct netif *netif)
{
    __IO uint32_t curTick = 0UL;

    curTick = SysTick_GetTick();
#ifdef USE_DHCP
    /* Fine DHCP periodic process every 500ms */
    if (curTick - u32DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
    {
        u32DHCPfineTimer = curTick;
        DHCP_Process(netif);
    }
#endif /* USE_DHCP */

    /* Check link status periodically */
    if ((curTick - u32LinkTimer) >= LINK_TIMER_INTERVAL)
    {
        u32LinkTimer = curTick;
        ethernetif_check_link(netif);
    }
}

#ifdef USE_DHCP

/**
 * @brief  DHCP Process
 * @param  [in] netif                   Pointer to a struct netif structure
 * @retval None
 */
void DHCP_Process(struct netif *netif)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;
    struct dhcp *dhcp;
#ifdef USE_LCD
    uint8_t iptxt[20];
#endif

    switch (u8DHCPState)
    {
        case DHCP_START:
            ip_addr_set_zero_ip4(&netif->ip_addr);
            ip_addr_set_zero_ip4(&netif->netmask);
            ip_addr_set_zero_ip4(&netif->gw);
            u8DHCPState = DHCP_WAIT_ADDRESS;
            dhcp_start(netif);
#ifdef USE_LCD
            LCD_UsrLog("State: Looking for DHCP server ...\n");
#endif
            break;
        case DHCP_WAIT_ADDRESS:
            if (dhcp_supplied_address(netif))
            {
                u8DHCPState = DHCP_ADDRESS_ASSIGNED;
#ifdef USE_LCD
                sprintf((char*)iptxt, "%s", ip4addr_ntoa((const ip4_addr_t*)&netif->ip_addr));
                LCD_UsrLog("IP address assigned by a DHCP server: %s\n", iptxt);
#else
                BSP_LED_On(LED_BLUE);
#endif
            }
            else
            {
                dhcp = (struct dhcp*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
                /* DHCP timeout */
                if (dhcp->tries > DHCP_MAX_TRIES)
                {
                    u8DHCPState = DHCP_TIMEOUT;
                    dhcp_stop(netif);
                    /* Static address used */
                    IP_ADDR4(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
                    IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
                    IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
                    netif_set_addr(netif, &ipaddr, &netmask, &gw);
#ifdef USE_LCD
                    sprintf((char*)iptxt, "%s", ip4addr_ntoa((const ip4_addr_t*)&netif->ip_addr));
                    LCD_UsrLog("DHCP Timeout !! \n");
                    LCD_UsrLog("Static IP address: %s\n", iptxt);
#else
                    BSP_LED_On(LED_BLUE);
#endif
                }
            }
            break;
        case DHCP_LINK_DOWN:
            /* Stop DHCP */
            dhcp_stop(netif);
            u8DHCPState = DHCP_OFF;
            break;
        default:
            break;
    }
}

#endif

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
