/**
 *******************************************************************************
 * @file  eth/lwip_tcp_server/source/tcp_server.c
 * @brief TCP server application using LwIP.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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

#if LWIP_TCP
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/* TCP protocol state */
typedef enum
{
    TCP_SERVER_NONE     = 0U,
    TCP_SERVER_ACCEPTED = 1U,
    TCP_SERVER_RECEIVED = 2U,
    TCP_SERVER_CLOSING  = 3U,
} en_tcp_server_state_t;

/* Structure to be passed as argument to the tcp callbacks */
typedef struct
{
    en_tcp_server_state_t enTcpState;   /* Current connection status         */
    u8_t                  retries;
    struct tcp_pcb        *pcb;         /* Pointer on the current tcp_pcb    */
    struct pbuf           *p_tx;        /* Pointer on pbuf to be transmitted */
} stc_tcp_server_param_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static err_t TcpServer_Accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t TcpServer_Recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void  TcpServer_Error(void *arg, err_t err);
static void  TcpServer_ConnectClose(struct tcp_pcb *tpcb, stc_tcp_server_param_t *tcpServer);
static err_t TcpServer_Poll(void *arg, struct tcp_pcb *tpcb);
static err_t TcpServer_Sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void  TcpServer_Send(struct tcp_pcb *tpcb, stc_tcp_server_param_t *tcpServer);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
struct tcp_pcb *TcpServerPcb;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Initializes the TCP server
 * @param  None
 * @retval None
 */
void TcpServer_Init(void)
{
    err_t err;

    /* create new tcp pcb */
    TcpServerPcb = tcp_new();
    if (NULL != TcpServerPcb)
    {
        /* Bind ServerPcb to port SERVER_PORT */
        err = tcp_bind(TcpServerPcb, IP_ADDR_ANY, SERVER_PORT);
        if (ERR_OK == err)
        {
            /* start tcp listening for ServerPcb */
            TcpServerPcb = tcp_listen(TcpServerPcb);
            /* initialize LwIP tcp_accept callback function */
            tcp_accept(TcpServerPcb, TcpServer_Accept);
        }
        else
        {
            /* deallocate the pcb */
            memp_free(MEMP_TCP_PCB, TcpServerPcb);
        }
    }
    else
    {
        /* deallocate the pcb */
        memp_free(MEMP_TCP_PCB, TcpServerPcb);
    }
}

/**
 * @brief  This function is the implementation of tcp_accept LwIP callback
 * @param  arg: not used
 * @param  newpcb: pointer on tcp_pcb struct for the newly created tcp connection
 * @param  err: not used
 * @retval err_t: error status
 */
static err_t TcpServer_Accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    err_t ret_err;
    stc_tcp_server_param_t *tcpServer = NULL;

    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(err);
    /* set priority for the newly accepted tcp connection newpcb */
    tcp_setprio(newpcb, TCP_PRIO_MIN);

    /* allocate structure stc_tcp_server_param_t to maintain tcp connection informations */
    tcpServer = (stc_tcp_server_param_t *)mem_malloc(sizeof(stc_tcp_server_param_t));
    if (NULL != tcpServer)
    {
        tcpServer->enTcpState = TCP_SERVER_ACCEPTED;
        tcpServer->pcb        = newpcb;
        tcpServer->retries    = 0;
        tcpServer->p_tx       = NULL;

        /* pass newly allocated stc_tcp_server_param_t structure as argument to newpcb */
        tcp_arg(newpcb, tcpServer);
        /* initialize lwip tcp_recv callback function for newpcb  */
        tcp_recv(newpcb, TcpServer_Recv);
        /* initialize lwip tcp_err callback function for newpcb  */
        tcp_err(newpcb, TcpServer_Error);
        /* initialize lwip tcp_poll callback function for newpcb */
        tcp_poll(newpcb, TcpServer_Poll, 0U);
        /* initialize lwip tcp_sent callback function for newpcb */
        tcp_sent(newpcb, TcpServer_Sent);
        ret_err = ERR_OK;
    }
    else
    {
        /* close connection */
        TcpServer_ConnectClose(newpcb, tcpServer);
        /* return memory error */
        ret_err = ERR_MEM;
    }

    return ret_err;
}

/**
 * @brief  This function is the implementation for tcp_recv LwIP callback
 * @param  arg: pointer on a argument for the tcp_pcb connection
 * @param  tpcb: pointer on the tcp_pcb connection
 * @param  pbuf: pointer on the received pbuf
 * @param  err: error information regarding the received pbuf
 * @retval err_t: error code
 */
static err_t TcpServer_Recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    stc_tcp_server_param_t *tcpServer;
    err_t ret_err;
    struct pbuf *ptr;

    LWIP_ASSERT("arg != NULL", arg != NULL);
    tcpServer = (stc_tcp_server_param_t *)arg;
    /* if we receive an empty tcp frame from client => close connection */
    if (NULL == p)
    {
        /* remote host closed connection */
        tcpServer->enTcpState = TCP_SERVER_CLOSING;
        if (NULL == tcpServer->p_tx)
        {
            /* we're done sending, close connection */
            TcpServer_ConnectClose(tpcb, tcpServer);
        }
        else
        {
            /* we're not done yet */
            /* acknowledge received packet */
            tcp_sent(tpcb, TcpServer_Sent);
            /* send remaining data*/
            TcpServer_Send(tpcb, tcpServer);
        }
        ret_err = ERR_OK;
    }
    /* else : a non empty frame was received from client but for some reason err != ERR_OK */
    else if (err != ERR_OK)
    {
        /* free received pbuf*/
        if (p != NULL)
        {
            tcpServer->p_tx = NULL;
            pbuf_free(p);
        }
        ret_err = err;
    }
    else if (tcpServer->enTcpState == TCP_SERVER_ACCEPTED)
    {
        /* first data chunk in p->payload */
        tcpServer->enTcpState = TCP_SERVER_RECEIVED;
        /* store reference to incoming pbuf (chain) */
        tcpServer->p_tx = p;
        /* initialize LwIP tcp_sent callback function */
        tcp_sent(tpcb, TcpServer_Sent);
        /* send back the received data */
        TcpServer_Send(tpcb, tcpServer);
        ret_err = ERR_OK;
    }
    else if (tcpServer->enTcpState == TCP_SERVER_RECEIVED)
    {
        /* more data received from client and previous data has been already sent*/
        if(NULL == tcpServer->p_tx)
        {
            tcpServer->p_tx = p;
            /* send back received data */
            TcpServer_Send(tpcb, tcpServer);
        }
        else
        {
            /* chain pbufs to the end of what we received previously  */
            ptr = tcpServer->p_tx;
            pbuf_chain(ptr, p);
        }
        ret_err = ERR_OK;
    }
    else if(tcpServer->enTcpState == TCP_SERVER_CLOSING)
    {
        /* odd case, remote side closing twice, trash data */
        tcp_recved(tpcb, p->tot_len);
        tcpServer->p_tx = NULL;
        pbuf_free(p);
        ret_err = ERR_OK;
    }
    else
    {
        /* unkown tcpServer->enTcpState, trash data */
        tcp_recved(tpcb, p->tot_len);
        tcpServer->p_tx = NULL;
        pbuf_free(p);
        ret_err = ERR_OK;
    }

    return ret_err;
}

/**
 * @brief  This function implements the tcp_err callback function (called
 *         when a fatal tcp_connection error occurs.
 * @param  arg: pointer on argument parameter
 * @param  err: not used
 * @retval None
 */
static void TcpServer_Error(void *arg, err_t err)
{
    stc_tcp_server_param_t *tcpServer;

    LWIP_UNUSED_ARG(err);
    tcpServer = (stc_tcp_server_param_t *)arg;
    if (NULL != tcpServer)
    {
        /* free stc_tcp_server_param_t structure */
        if (NULL != tcpServer->p_tx)
        {
            /* free the buffer chain if present */
            pbuf_free(tcpServer->p_tx);
        }
        mem_free(tcpServer);
    }
}

/**
 * @brief  This function is used to send data for tcp connection
 * @param  tpcb: pointer on the tcp_pcb connection
 * @param  tcpServer: pointer on stc_tcp_server_param_t structure
 * @retval None
 */
static void TcpServer_Send(struct tcp_pcb *tpcb, stc_tcp_server_param_t * tcpServer)
{
    struct pbuf *ptr;
    err_t wr_err = ERR_OK;
    u16_t plen;
    u8_t freed;

    while ((wr_err == ERR_OK) &&
            (tcpServer->p_tx != NULL) &&
            (tcpServer->p_tx->len <= tcp_sndbuf(tpcb)))
    {
        /* get pointer on pbuf from stc_tcp_server_param_t structure */
        ptr = tcpServer->p_tx;
        /* enqueue data for transmission */
        wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1U);

        if (wr_err == ERR_OK)
        {
            plen = ptr->len;
            /* continue with next pbuf in chain (if any) */
            tcpServer->p_tx = ptr->next;
            if(NULL != tcpServer->p_tx)
            {
                /* increment reference count for tcpServer->p_tx */
                pbuf_ref(tcpServer->p_tx);
            }

            /* chop first pbuf from chain */
            do
            {
                /* try hard to free pbuf */
                freed = pbuf_free(ptr);
            }
            while(freed == 0);
            /* we can read more data now */
            tcp_recved(tpcb, plen);
        }
        else if (wr_err == ERR_MEM)
        {
            /* we are low on memory, try later, defer to poll */
            tcpServer->p_tx = ptr;
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
 * @param  tpcb: Pointer on the tcp_pcb for the current tcp connection
 * @retval err_t: error code
 */
static err_t TcpServer_Poll(void *arg, struct tcp_pcb *tpcb)
{
    err_t ret_err;
    stc_tcp_server_param_t *tcpServer;

    tcpServer = (stc_tcp_server_param_t*)arg;
    if (NULL != tcpServer)
    {
        if (NULL != tcpServer->p_tx)
        {
            tcp_sent(tpcb, TcpServer_Sent);
            /* there is a remaining pbuf (chain) , try to send data */
            TcpServer_Send(tpcb, tcpServer);
        }
        else
        {
            /* no remaining pbuf (chain)  */
            if (tcpServer->enTcpState == TCP_SERVER_CLOSING)
            {
                /* close tcp connection */
                TcpServer_ConnectClose(tpcb, tcpServer);
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
 * @param  None
 * @retval err_t: Returned error code
 */
static err_t TcpServer_Sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
    stc_tcp_server_param_t *tcpServer;

    LWIP_UNUSED_ARG(len);
    tcpServer = (stc_tcp_server_param_t *)arg;
    tcpServer->retries = 0;
    if (NULL != tcpServer->p_tx)
    {
        /* still got pbufs to send */
        tcp_sent(tpcb, TcpServer_Sent);
        TcpServer_Send(tpcb, tcpServer);
    }
    else
    {
        /* if no more data to send and client closed connection*/
        if (TCP_SERVER_CLOSING == tcpServer->enTcpState)
        {
            TcpServer_ConnectClose(tpcb, tcpServer);
        }
    }

    return ERR_OK;
}

/**
 * @brief  This functions closes the tcp connection
 * @param  tcp_pcb: pointer on the tcp connection
 * @param  tcpServer: pointer on stc_tcp_server_param_t structure
 * @retval None
 */
static void TcpServer_ConnectClose(struct tcp_pcb *tpcb, stc_tcp_server_param_t *tcpServer)
{
    /* Remove callbacks */
    tcp_arg(tpcb, NULL);
    tcp_recv(tpcb, NULL);
    tcp_sent(tpcb, NULL);
    tcp_err(tpcb, NULL);
    tcp_poll(tpcb, NULL, 0U);

    if (NULL != tcpServer)
    {
        if (NULL != tcpServer->p_tx)
        {
            /* free the buffer chain if present */
            pbuf_free(tcpServer->p_tx);
        }
        mem_free(tcpServer);
    }

    /* close tcp connection */
    tcp_close(tpcb);
}

#endif /* LWIP_TCP */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
