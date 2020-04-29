/**
 *******************************************************************************
 * @file  spi/spi_master_base/source/main.c
 * @brief Main program SPI master base for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-16       Wangmin         First version
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

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup SPI_TX_RX_IRQ
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Configuration for Example */

/* Define the communication mode of application, should be COM_MASTER or COM_SLAVE*/
#define APP_TEST_MODE           COM_MASTER

/* SPI wire mode, can be SPI_WIRE_4/SPI_WIRE_3 */
#define EXAMPLE_WIRE_MODE       (SPI_WIRE_3)

/* SPI mode, can be SPI_MODE_0/SPI_MODE_1/SPI_MODE_2/SPI_MODE_3 */
#define EXAMPLE_SPI_MODE        (SPI_MODE_3)

/* Clock delay function configurated for master if define SCK_DELAY_FUNC_ON */
#define SCK_DELAY_FUNC_ON       1UL

#if (EXAMPLE_WIRE_MODE == SPI_WIRE_3)
    #if ((EXAMPLE_SPI_MODE == SPI_MODE_0) || (EXAMPLE_SPI_MODE == SPI_MODE_2))
        #error "SPI_WIRE_3 mode can't support SPI_MODE_0 and SPI_MODE_2"
    #endif
#endif

#define COM_MASTER              1UL
#define COM_SLAVE               0UL

/* Test SPI unit */
#define SPI_UNIT         (M4_SPI1)

/* SPI port definition */
#define SPI_NSS_PORT          (GPIO_PORT_A)
#define SPI_NSS_PIN           (GPIO_PIN_04)
#define SPI_SCK_PORT          (GPIO_PORT_A)
#define SPI_SCK_PIN           (GPIO_PIN_05)
#define SPI_MOSI_PORT         (GPIO_PORT_C)
#define SPI_MOSI_PIN          (GPIO_PIN_01)
#define SPI_MISO_PORT         (GPIO_PORT_F)
#define SPI_MISO_PIN          (GPIO_PIN_06)


#define BUF_LENGTH              128UL
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
#if (APP_TEST_MODE == COM_MASTER)
static void Master_Init(void);
#else
static void Slave_Init(void);
#endif
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static char u8MasterTxBuf[BUF_LENGTH] = "SPI master tx buffer data: abcdefg!";
static char u8SlaveTxBuf[BUF_LENGTH] = "SPI slave tx buffer data: 1234567!";

#if (APP_TEST_MODE == COM_MASTER)
static char u8MasterRxBuf[BUF_LENGTH];
static uint32_t u32MasterTxIndex = 0UL, u32MasterRxIndex = 0UL;
#else
static char u8SlaveRxBuf[BUF_LENGTH];
static uint32_t u32SlaveTxIndex = 0UL, u32SlaveRxIndex = 0UL;
#endif
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/


/**
 * @brief  Main function of spi_master_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_gpio_init_t stcGpioCfg;
#if (APP_TEST_MODE == COM_MASTER)
#ifdef SCK_DELAY_FUNC_ON
    stc_spi_delay_t stcSpiDelay;
#endif
#endif
    /* System clock and LED initialize */
    BSP_CLK_Init();
    BSP_LED_Init();
    //todo add key control

    /* Clear receive buffer */
    for(uint32_t i = 0UL; i < BUF_LENGTH; i++)
    {
#if (APP_TEST_MODE == COM_MASTER)
        u8MasterRxBuf[i] = 0x00U;
#else
        u8SlaveRxBuf[i] = 0x00U;
#endif
    }

    /* Configure peripheral clock */
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_SPI1, Enable);

    /* Port configurate, High driving capacity for output pin. */
    GPIO_StructInit(&stcGpioCfg);

#if (APP_TEST_MODE == COM_MASTER)
    stcGpioCfg.u16PinDrv = PIN_HIGH_DRV;
#if (EXAMPLE_WIRE_MODE == SPI_WIRE_4)
    GPIO_Init(SPI_NSS_PORT,  SPI_NSS_PIN, &stcGpioCfg);
#endif
    GPIO_Init(SPI_SCK_PORT,  SPI_SCK_PIN, &stcGpioCfg);
    GPIO_Init(SPI_MOSI_PORT, SPI_MOSI_PIN, &stcGpioCfg);

    /* CMOS input for input pin */
    stcGpioCfg.u16PinIType = PIN_ITYPE_CMOS;
    GPIO_Init(SPI_MISO_PORT, SPI_MISO_PIN, &stcGpioCfg);
#else

    stcGpioCfg.u16PinIType = PIN_ITYPE_CMOS;
#if (EXAMPLE_WIRE_MODE == SPI_WIRE_4)
    GPIO_Init(SPI_NSS_PORT,  SPI_NSS_PIN, &stcGpioCfg);
#endif
    GPIO_Init(SPI_SCK_PORT,  SPI_SCK_PIN, &stcGpioCfg);
    GPIO_Init(SPI_MOSI_PORT, SPI_MOSI_PIN, &stcGpioCfg);

    stcGpioCfg.u16PinDrv = PIN_HIGH_DRV;
    GPIO_Init(SPI_MISO_PORT, SPI_MISO_PIN, &stcGpioCfg);

#endif
    /* Configure SPI Port function for master */
#if (EXAMPLE_WIRE_MODE == SPI_WIRE_4)
    GPIO_SetFunc(SPI_NSS_PORT,  SPI_NSS_PIN,  GPIO_FUNC_19_SPI1_NSS0, PIN_SUBFUNC_DISABLE);
#endif
    GPIO_SetFunc(SPI_SCK_PORT,  SPI_SCK_PIN,  GPIO_FUNC_40_SPI1_SCK, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, GPIO_FUNC_41_SPI1_MOSI, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, GPIO_FUNC_42_SPI1_MISO, PIN_SUBFUNC_DISABLE);

    SPI_DeInit(SPI_UNIT);
    /* Configuration SPI function for master*/
#if (APP_TEST_MODE == COM_MASTER)
    Master_Init();
#ifdef SCK_DELAY_FUNC_ON
    /* SPI Singnal delay configurate, for wait slave */
    SPI_DelayStructInit(&stcSpiDelay);
    stcSpiDelay.u32IntervalDelay = SPI_INTERVAL_TIME_8SCK_2PCLK1;
    stcSpiDelay.u32ReleaseDelay = SPI_RELEASE_TIME_8SCK;
    stcSpiDelay.u32SetupDelay = SPI_SETUP_TIME_8SCK;
    SPI_DelayTimeCfg(SPI_UNIT, &stcSpiDelay);
#endif
#else
    /* Configuration SPI function for slave*/
    Slave_Init();
#endif

    /* Interrupt configurate */
    SPI_IntCmd(SPI_UNIT, SPI_INT_TX_BUFFER_EMPTY | SPI_INT_RX_BUFFER_FULL, Enable);

    /* Command SPI function */
    SPI_FunctionCmd(SPI_UNIT, Enable);

    /* Wait transfer finish */
#if (APP_TEST_MODE == COM_MASTER)
    while(u32MasterRxIndex < BUF_LENGTH)
#else
    while(u32SlaveRxIndex < BUF_LENGTH)
#endif
    {
        ;
    }

    SPI_DeInit(SPI_UNIT);

#if (APP_TEST_MODE == COM_MASTER)
    /* Compare u8TxBuffer and u8RxBuffer */
    if(0U == memcmp(u8SlaveTxBuf, u8MasterRxBuf, BUF_LENGTH))
#else
    if(0U == memcmp(u8MasterTxBuf, u8SlaveRxBuf, BUF_LENGTH))
#endif
    {
        /* Communication success */
        while(1)
        {
            BSP_LED_Toggle(LED_BLUE);
            DDL_Delay1ms(500UL);
        }
    }
    else
    {
        /* Communication data error */
        while(1)
        {
            BSP_LED_Toggle(LED_RED);
            DDL_Delay1ms(500UL);
        }
    }
}

#if (APP_TEST_MODE == COM_MASTER)
/**
 * @brief  Master Tx buffer empty interrupt
 * @param  None
 * @retval None
 */
static void SpiMasterTx_IrqCallback(void)
{
    if(u32MasterTxIndex < BUF_LENGTH)
    {
        SPI_WriteDataReg(SPI_UNIT, u8MasterTxBuf[u32MasterTxIndex++]);
    }
    else
    {
        SPI_IntCmd(SPI_UNIT, SPI_INT_TX_BUFFER_EMPTY, Disable);
    }
}

/**
 * @brief  Master Rx buffer full interrupt
 * @param  None
 * @retval None
 */
static void SpiMasterRx_IrqCallback(void)
{
    if(u32MasterRxIndex < BUF_LENGTH)
    {
        u8MasterRxBuf[u32MasterRxIndex++] = (uint8_t)SPI_ReadDataReg(SPI_UNIT);
    }
    else
    {
        SPI_IntCmd(SPI_UNIT, SPI_INT_RX_BUFFER_FULL, Disable);
    }
}

/**
 * @brief  Initialization for master
 * @param  None
 * @retval None
 */
static void Master_Init(void)
{
    stc_spi_init_t stcSpiInit;
    stc_irq_signin_config_t stcIrqRegiConf;

    SPI_StructInit(&stcSpiInit);   /* Clear initialize structure */
    stcSpiInit.u32WireMode          = EXAMPLE_WIRE_MODE;
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = SPI_MASTER;
    stcSpiInit.u32SuspMode          = SPI_COM_SUSP_FUNC_OFF;
    stcSpiInit.u32Modfe             = SPI_MODFE_DISABLE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVALID;
    stcSpiInit.u32SpiMode           = EXAMPLE_SPI_MODE;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_DIV_8;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    SPI_Init(SPI_UNIT, &stcSpiInit);

    stcIrqRegiConf.enIRQn = Int002_IRQn;                   /* Register INT_SPI1_SPTI Int to Vect.No.002 */
    stcIrqRegiConf.enIntSrc = INT_SPI1_SPTI;               /* Select Event interrupt of SPI1 */
    stcIrqRegiConf.pfnCallback = &SpiMasterTx_IrqCallback; /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                       /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */

    stcIrqRegiConf.enIRQn = Int003_IRQn;                    /* Register INT_SPI1_SPRI Int to Vect.No.003 */
    stcIrqRegiConf.enIntSrc = INT_SPI1_SPRI;                /* Select Event interrupt of SPI1 */
    stcIrqRegiConf.pfnCallback = &SpiMasterRx_IrqCallback;  /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                        /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_14);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */

}

#else

/**
 * @brief  Slave Tx buffer empty interrupt
 * @param  None
 * @retval None
 */
static void SpiSlaveTx_IrqCallback(void)
{
    if(u32SlaveTxIndex < BUF_LENGTH)
    {
        SPI_WriteDataReg(SPI_UNIT, u8SlaveTxBuf[u32SlaveTxIndex++]);
    }
    else
    {
        SPI_IntCmd(SPI_UNIT, SPI_INT_TX_BUFFER_EMPTY, Disable);
    }
}

/**
 * @brief  Slave Rx buffer full interrupt
 * @param  None
 * @retval None
 */
static void SpiSlaveRx_IrqCallback(void)
{
    if(u32SlaveRxIndex < BUF_LENGTH)
    {
        u8SlaveRxBuf[u32SlaveRxIndex++] = (uint8_t)SPI_ReadDataReg(SPI_UNIT);
    }
    else
    {
        SPI_IntCmd(SPI_UNIT, SPI_INT_RX_BUFFER_FULL, Disable);
    }
}

/**
 * @brief  Initialization for slave
 * @param  None
 * @retval None
 */
static void Slave_Init(void)
{
    stc_spi_init_t stcSpiInit;
    stc_irq_signin_config_t stcIrqRegiConf;

    SPI_StructInit(&stcSpiInit);   /* Clear initialize structure */
    stcSpiInit.u32WireMode          = EXAMPLE_WIRE_MODE;
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = SPI_SLAVE;
    stcSpiInit.u32SuspMode          = SPI_COM_SUSP_FUNC_OFF;
    stcSpiInit.u32Modfe             = SPI_MODFE_DISABLE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVALID;
    stcSpiInit.u32SpiMode           = EXAMPLE_SPI_MODE;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_DIV_8;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    SPI_Init(SPI_UNIT, &stcSpiInit);

    stcIrqRegiConf.enIRQn = Int004_IRQn;                    /* Register INT_SPI2_SPTI Int to Vect.No.004 */
    stcIrqRegiConf.enIntSrc = INT_SPI1_SPTI;                /* Select Event interrupt of SPI1 */
    stcIrqRegiConf.pfnCallback = &SpiSlaveTx_IrqCallback;   /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                        /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_13);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */

    stcIrqRegiConf.enIRQn = Int005_IRQn;                    /* Register INT_SPI2_SPRI Int to Vect.No.005 */
    stcIrqRegiConf.enIntSrc = INT_SPI1_SPRI;                /* Select Event interrupt of SPI */
    stcIrqRegiConf.pfnCallback = &SpiSlaveRx_IrqCallback;   /* Callback function */
    INTC_IrqSignIn(&stcIrqRegiConf);                        /* Registration IRQ */

    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);            /* Clear Pending */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_13);/* Set priority */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);                  /* Enable NVIC */
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
