/**
 *******************************************************************************
 * @file  eth/lwip_udp_client/source/udp_client.c
 * @brief udp client application using LwIP.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ddl.h"
#include "app_ethernet.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>

#if LWIP_UDP
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint8_t u8TransData[100];

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void UdpClient_ReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
struct udp_pcb *UdpClient_Pcb;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Connects to the UDP server
 * @param  None
 * @retval None
 */
void UdpClient_Connect(void)
{
    ip_addr_t DestIPaddr;
    err_t err;
    struct pbuf *p;

    /* Create a new UDP control block  */
    UdpClient_Pcb = udp_new();
    if (NULL != UdpClient_Pcb)
    {
        /* assign destination IP address */
        IP4_ADDR(&DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);
        /* configure destination IP address and port */
        err = udp_connect(UdpClient_Pcb, &DestIPaddr, UDP_SERVER_PORT);
        if (err == ERR_OK)
        {
            /* Set a receive callback for the UdpClient_Pcb */
            udp_recv(UdpClient_Pcb, UdpClient_ReceiveCallback, NULL);

            sprintf((char*)u8TransData, "UDP client connection successful!\r\n");
            /* allocate pbuf from pool*/
            p = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)u8TransData), PBUF_POOL);
            if (NULL != p)
            {
                /* copy data to pbuf */
                pbuf_take(p, (char*)u8TransData, strlen((char*)u8TransData));
                /* send udp data */
                udp_send(UdpClient_Pcb, p);
                /* free pbuf */
                pbuf_free(p);
            }
            else
            {
                udp_remove(UdpClient_Pcb);
            }
        }
        else
        {
            udp_remove(UdpClient_Pcb);
        }
    }
}

/**
 * @brief  Disconnect to the UDP server
 * @param  None
 * @retval None
 */
void UdpClient_Disconnect(void)
{
    udp_remove(UdpClient_Pcb);
}

/**
 * @brief This function is called when an UDP datagram has been received on the port.
 * @param arg user supplied argument (udp_pcb.recv_arg)
 * @param pcb the udp_pcb which received data
 * @param p the packet buffer that was received
 * @param addr the remote IP address from which the packet was received
 * @param port the remote port from which the packet was received
 * @retval None
 */
static void UdpClient_ReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    if (NULL != p)
    {
        /* send received packet back to sender */
        udp_send(upcb, p);
        /* free the pbuf */
        pbuf_free(p);
    }
}

#endif /* LWIP_UDP */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
