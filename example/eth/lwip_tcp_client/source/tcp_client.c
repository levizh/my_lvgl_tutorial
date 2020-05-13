/**
 *******************************************************************************
 * @file  eth/lwip_tcp_client/source/tcp_client.c
 * @brief TCP client application using LwIP.
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
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include <stdio.h>
#include <string.h>

#if LWIP_TCP
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/* TCP protocol state */
typedef enum
{
    TCP_CLIENT_NOT_CONNECTED = 0U,
    TCP_CLIENT_CONNECTED     = 1U,
    TCP_CLIENT_RECEIVED      = 2U,
    TCP_CLIENT_CLOSING       = 3U,
} en_tcp_client_state_t;

/* Structure to be passed as argument to the tcp callbacks */
typedef struct
{
    en_tcp_client_state_t enTcpState;   /* Connection status                 */
    struct tcp_pcb        *pcb;         /* Pointer on the current tcp_pcb    */
    struct pbuf           *p_tx;        /* Pointer on pbuf to be transmitted */
} stc_tcp_client_param_t;

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
static err_t TcpClient_Recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void  TcpClient_ConnectClose(struct tcp_pcb *tpcb, stc_tcp_client_param_t *tcpClient);
static err_t TcpClient_Poll(void *arg, struct tcp_pcb *tpcb);
static err_t TcpClient_Sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void  TcpClient_Send(struct tcp_pcb *tpcb, stc_tcp_client_param_t *tcpClient);
static err_t TcpClient_Connected(void *arg, struct tcp_pcb *tpcb, err_t err);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
struct tcp_pcb *TcpClient_Pcb;
stc_tcp_client_param_t *TcpClient_Param;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Connects to the TCP server
 * @param  None
 * @retval None
 */
void TcpClient_Connect(void)
{
    ip_addr_t DestIPaddr;

    /* create new tcp pcb */
    TcpClient_Pcb = tcp_new();
    if (NULL != TcpClient_Pcb)
    {
        IP4_ADDR(&DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);
        /* connect to destination address/port */
        tcp_connect(TcpClient_Pcb, &DestIPaddr, DEST_PORT, TcpClient_Connected);
    }
    else
    {
        /* deallocate the pcb */
        memp_free(MEMP_TCP_PCB, TcpClient_Pcb);
    }
}

/**
 * @brief  Disconnect to the TCP server
 * @param  None
 * @retval None
 */
void TcpClient_Disconnect(void)
{
    /* close connection */
    TcpClient_ConnectClose(TcpClient_Pcb, TcpClient_Param);
}

/**
 * @brief  Function called when TCP connection established
 * @param  tpcb: Pointer on the connection contol block
 * @param  err:  When connection correctly established err should be ERR_OK 
 * @retval err_t: Returned error 
 */
static err_t TcpClient_Connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    stc_tcp_client_param_t *tcpClient = NULL;
    
    if ((err == ERR_OK) && (NULL != tpcb))
    {
        /* allocate structure stc_tcp_client_param_t to maintain tcp connection informations */
        tcpClient = (stc_tcp_client_param_t *)mem_malloc(sizeof(stc_tcp_client_param_t));
        TcpClient_Param = tcpClient;
        if (NULL != tcpClient)
        {
            tcpClient->enTcpState = TCP_CLIENT_CONNECTED;
            tcpClient->pcb = tpcb;

            sprintf((char*)u8TransData, "TCP client connection successful!\r\n");
            /* allocate pbuf */
            tcpClient->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)u8TransData), PBUF_POOL);
            if (tcpClient->p_tx)
            {
                /* copy data to pbuf */
                pbuf_take(tcpClient->p_tx, (char*)u8TransData, strlen((char*)u8TransData));
                /* pass newly allocated stc_tcp_client_param_t structure as argument to tpcb */
                tcp_arg(tpcb, tcpClient);
                /* initialize LwIP tcp_recv callback function */ 
                tcp_recv(tpcb, TcpClient_Recv);
                /* initialize LwIP tcp_sent callback function */
                tcp_sent(tpcb, TcpClient_Sent);
                /* initialize LwIP tcp_poll callback function */
                tcp_poll(tpcb, TcpClient_Poll, 1U);
                /* send data */
                TcpClient_Send(tpcb, tcpClient);

                return ERR_OK;
            }
        }
        else
        {
            /* close connection */
            TcpClient_ConnectClose(tpcb, tcpClient);
            /* return memory allocation error */
            return ERR_MEM;  
        }
    }
    else
    {
        /* close connection */
        TcpClient_ConnectClose(tpcb, tcpClient);
    }
    return err;
}
    
/**
 * @brief  Tcp client receive callback
 * @param  arg:  Argument to be passed to receive callback 
 * @param  tpcb: Tcp connection control block 
 * @param  err:  Receive error code 
 * @retval err_t: Returned error  
 */
static err_t TcpClient_Recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{ 
    stc_tcp_client_param_t *tcpClient;
    err_t ret_err; 
    struct pbuf *ptr;

    LWIP_ASSERT("arg != NULL",arg != NULL);
    tcpClient = (stc_tcp_client_param_t *)arg;
    /* if we receive an empty tcp frame from server => close connection */
    if (NULL == p)
    {
        /* remote host closed connection */
        tcpClient->enTcpState = TCP_CLIENT_CLOSING;
        if (NULL == tcpClient->p_tx)
        {
            /* we're done sending, close connection */
            TcpClient_ConnectClose(tpcb, tcpClient);
        }
        else
        {    
            /* send remaining data*/
            TcpClient_Send(tpcb, tcpClient);
        }
        ret_err = ERR_OK;
    }   
    /* else : a non empty frame was received from server but for some reason err != ERR_OK */
    else if (err != ERR_OK)
    {
        /* free received pbuf*/
        if (p != NULL)
        {
            pbuf_free(p);
        }
        ret_err = err;
    }
    else if (tcpClient->enTcpState == TCP_CLIENT_CONNECTED)
    {
        /* read some more data */
        if (NULL == tcpClient->p_tx)
        {
            tcpClient->p_tx = p;
            /* send data */
            TcpClient_Send(tpcb, tcpClient);
        }
        else 
        {
            /* chain pbufs to the end of what we received previously  */
            ptr = tcpClient->p_tx;
            pbuf_chain(ptr, p);
        }
        ret_err = ERR_OK;
    }
    /* data received when connection already closed */
    else
    {
        /* Acknowledge data reception */
        tcp_recved(tpcb, p->tot_len);
        /* free pbuf and do nothing */
        tcpClient->p_tx = NULL;
        pbuf_free(p);
        ret_err = ERR_OK;
    }

    return ret_err;
}

/**
 * @brief  Function used to send data
 * @param  tpcb: Tcp control block
 * @param  tcpClient: Pointer on structure of type tcpClient containing info on 
 *                    data to be sent
 * @retval None 
 */
static void TcpClient_Send(struct tcp_pcb *tpcb, stc_tcp_client_param_t * tcpClient)
{
    struct pbuf *ptr;
    err_t wr_err = ERR_OK;

    while ((wr_err == ERR_OK) &&
            (tcpClient->p_tx != NULL) && 
            (tcpClient->p_tx->len <= tcp_sndbuf(tpcb)))
    {
        /* get pointer on pbuf from stc_tcp_client_param_t structure */
        ptr = tcpClient->p_tx;
        /* enqueue data for transmission */
        wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1U);

        if (wr_err == ERR_OK)
        { 
            /* continue with next pbuf in chain (if any) */
            tcpClient->p_tx = ptr->next;
            if (tcpClient->p_tx != NULL)
            {
                /* increment reference count for tcpClient->p_tx */
                pbuf_ref(tcpClient->p_tx);
            }
            /* free pbuf: will free pbufs up to tcpClient->p_tx (because tcpClient->p_tx has a reference count > 0) */
            pbuf_free(ptr);
        }
        else if (wr_err == ERR_MEM)
        {
            /* we are low on memory, try later, defer to poll */
            tcpClient->p_tx = ptr;
        }
        else
        {
            /* other problem */
        }
    }
}

/**
 * @brief  This function implements the tcp_poll callback function
 * @param  arg:  Pointer on argument passed to callback
 * @param  tpcb: Tcp connection control block
 * @retval err_t: error code
 */
static err_t TcpClient_Poll(void *arg, struct tcp_pcb *tpcb)
{
    err_t ret_err;
    stc_tcp_client_param_t *tcpClient;

    tcpClient = (stc_tcp_client_param_t*)arg;
    if (NULL != tcpClient)
    {
        if (NULL != tcpClient->p_tx)
        {
            /* there is a remaining pbuf (chain) , try to send data */
            TcpClient_Send(tpcb, tcpClient);
        }
        else
        {
            /* no remaining pbuf (chain)  */
            if (tcpClient->enTcpState == TCP_CLIENT_CLOSING)
            {
                /* close tcp connection */
                TcpClient_ConnectClose(tpcb, tcpClient);
            }
        }
        ret_err = ERR_OK;
    }
    else
    {
        /* nothing to be done */
        tcp_abort(tpcb);
        ret_err = ERR_ABRT;
    }

    return ret_err;
}

/**
 * @brief  This function implements the tcp_sent LwIP callback (called when ACK
 *         is received from remote host for sent u8TransData) 
 * @param  arg:     Pointer on argument passed to callback
 * @param  tcp_pcb: Tcp connection control block
 * @param  len: Length of data sent 
 * @retval err_t: Returned error code
 */
static err_t TcpClient_Sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
    stc_tcp_client_param_t *tcpClient;

    LWIP_UNUSED_ARG(len);
    tcpClient = (stc_tcp_client_param_t *)arg;
    if (NULL != tcpClient->p_tx)
    {
        /* still got pbufs to send */
        TcpClient_Send(tpcb, tcpClient);
    }
    else
    {
        /* no more pbufs to send */
        if (TCP_CLIENT_CLOSING == tcpClient->enTcpState)
        {
            TcpClient_ConnectClose(tpcb, tcpClient);
        }
    }

    return ERR_OK;
}

/**
 * @brief This function is used to close the tcp connection with server
 * @param tpcb: Tcp connection control block
 * @param tcpClient: Pointer on tcpClient structure
 * @retval None
 */
static void TcpClient_ConnectClose(struct tcp_pcb *tpcb, stc_tcp_client_param_t *tcpClient)
{
    /* Remove callbacks */
    tcp_arg(tpcb, NULL);
    tcp_recv(tpcb, NULL);
    tcp_sent(tpcb, NULL);
    tcp_poll(tpcb, NULL, 0U);

    if (NULL != tcpClient)
    {
        if (NULL != tcpClient->p_tx)
        {
            /* free the buffer chain if present */
            pbuf_free(tcpClient->p_tx);
        }
        mem_free(tcpClient);
    }

    /* close tcp connection */
    tcp_close(tpcb);
}

#endif /* LWIP_TCP */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
