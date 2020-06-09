/**
 *******************************************************************************
 * @file  eth/lwip_tcp_client/source/main.c
 * @brief This sample code implements a tcp client application based on LwIP
 *        Raw API of LwIP stack.
 * @note  The communication is done with a remote PC.
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
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "app_ethernet.h"
#include "tcp_client.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup ETH_LWIP_TCP_Client_RAW
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#ifdef ETH_INTERFACE_RMII
    /* RMII_INTB */
    #define ETH_RMII_INTB_PORT                  (GPIO_PORT_B)
    #define ETH_RMII_INTB_PIN                   (GPIO_PIN_00)
    #define ETH_RMII_INTB_EXINT_CH              (EXINT_CH00)
    #define ETH_RMII_INTB_INT_SRC               (INT_PORT_EIRQ0)
    #define ETH_RMII_INTB_IRQn                  (Int037_IRQn)
#endif

/* SW1 Port/Pin definition */
#define SW1_IN_PORT                             (GPIO_PORT_H)
#define SW1_IN_PIN                              (GPIO_PIN_07)
#define SW1_IN_EXINT_CH                         (EXINT_CH07)
#define SW1_IN_INT_SRC                          (INT_PORT_EIRQ7)
#define SW1_IN_IRQn                             (Int032_IRQn)
#define SW1_IN_WAKEUP                           (INTC_WUPEN_EIRQWUEN_7)

#define SW1_OUT_PORT                            (GPIO_PORT_A)
#define SW1_OUT_PIN                             (GPIO_PIN_06)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
struct netif gnetif;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  SysTick interrupt callback function.
 * @param  None
 * @retval None
 */
void SysTick_IrqHandler(void)
{
    SysTick_IncTick();
}

/**
 * @brief  SW1 interrupt callback function.
 * @param  None
 * @retval None
 */
void SW1_IrqCallback(void)
{
    static uint8_t u8ConnSta = 0U;

    if (Set == EXINT_GetExIntSrc(SW1_IN_EXINT_CH))
    {
        if (0U == u8ConnSta)
        {
            u8ConnSta = 1U;
            /* Connect to tcp server */
            TcpClient_Connect();
        }
        else
        {
            u8ConnSta = 0U;
            /* Disconnect to tcp server */
            TcpClient_Disconnect();
        }
        EXINT_ClrExIntSrc(SW1_IN_EXINT_CH);
    }
}

#ifdef ETH_INTERFACE_RMII
/**
 * @brief  ETH RMII interrupt callback function.
 * @param  None
 * @retval None
 */
void ETH_RMII_LinkIrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(ETH_RMII_INTB_EXINT_CH))
   {
        EthernetIF_UpdateLink(&gnetif);
        EXINT_ClrExIntSrc(ETH_RMII_INTB_EXINT_CH);
   }
}

/**
 * @brief  ETH RMII link interrupt configuration.
 * @param  None
 * @retval None
 */
static void ETH_RMII_LinkIntConfig(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt  = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(ETH_RMII_INTB_PORT, ETH_RMII_INTB_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh  = ETH_RMII_INTB_EXINT_CH;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc    = ETH_RMII_INTB_INT_SRC;
    stcIrqSignConfig.enIRQn      = ETH_RMII_INTB_IRQn;
    stcIrqSignConfig.pfnCallback = &ETH_RMII_LinkIrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}
#endif /* ETH_INTERFACE_RMII */

/**
 * @brief  SW1 configuration.
 * @param  None
 * @retval None
 */
static void SW1_Config(void)
{
    stc_exint_init_t stcExintInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* GPIO config */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_RESET;
    GPIO_Init(SW1_OUT_PORT, SW1_OUT_PIN, &stcGpioInit);

    stcGpioInit.u16PinDir = PIN_DIR_IN;
    stcGpioInit.u16ExInt  = PIN_EXINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    GPIO_Init(SW1_IN_PORT, SW1_IN_PIN, &stcGpioInit);

    /* Exint config */
    EXINT_StructInit(&stcExintInit);
    stcExintInit.u32ExIntCh  = SW1_IN_EXINT_CH;
    stcExintInit.u32ExIntLvl = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc    = SW1_IN_INT_SRC;
    stcIrqSignConfig.enIRQn      = SW1_IN_IRQn;
    stcIrqSignConfig.pfnCallback = &SW1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}

/**
 * @brief  Configurate the BSP.
 * @param  None
 * @retval None
 */
static void BSP_Config(void)
{
    /* Configure BSP */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Configure UART */
    DDL_PrintfInit();
    /* SysTick configuration */
    SysTick_Init(1000U);
    /* Set Systick Interrupt to the highest priority */
    NVIC_SetPriority(SysTick_IRQn, DDL_IRQ_PRIORITY_00);
    /* Configure link interrupt IO for ETH RMII */
#ifdef ETH_INTERFACE_RMII
    ETH_RMII_LinkIntConfig();
#endif
}

/**
 * @brief  Configurate the network interface
 * @param  None
 * @retval None
 */
static void Netif_Config(void)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

#ifdef USE_DHCP
    ip_addr_set_zero_ip4(&ipaddr);
    ip_addr_set_zero_ip4(&netmask);
    ip_addr_set_zero_ip4(&gw);
#else
    IP_ADDR4(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
    IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#endif /* USE_DHCP */

    /* Add the network interface */
    netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
    /*  Registers the default network interface */
    netif_set_default(&gnetif);

    if (netif_is_link_up(&gnetif))
    {
        /* When the netif is fully configured this function must be called */
        netif_set_up(&gnetif);
    }
    else
    {
        /* When the netif link is down this function must be called */
        netif_set_down(&gnetif);
    }
    /* Set the link callback function, this function is called on change of link status*/
    netif_set_link_callback(&gnetif, EthernetIF_LinkCallback);
}

/**
 * @brief  Main function of ETH LWIP_TCP_Client_RAW.
 * @param  None
 * @retval int32_t return value, if needed
 */
int main(void)
{
    /* Configure clock */
    BSP_CLK_Init();
    /* Configure the BSP */
    BSP_Config();
    /* SW1 configuration */
    SW1_Config();
    /* Initialize the LwIP stack */
    lwip_init();
    /* Configure the Network interface */
    Netif_Config();
    /* Notify user about the network interface config */
    Ethernet_NotifyConnStatus(&gnetif);

    while (1)
    {
        /* Read a received packet from the ETH buffers and send it
           to the lwIP for handling */
        ethernetif_input(&gnetif);

        /* Handle timeouts */
        sys_check_timeouts();
        /* Handle periodic timers */
        LwIP_PeriodicHandle(&gnetif);
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
