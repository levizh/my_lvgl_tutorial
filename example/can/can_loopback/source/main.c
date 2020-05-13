/**
 *******************************************************************************
 * @file  can/can_loopback/source/main.c
 * @brief Main program of CAN loopback for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-31       Wuze            First version
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
 * @addtogroup CAN_Loopback
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Unit definition of CAN in this example. */
#define APP_CAN_SEL_U1                      (1U)
#define APP_CAN_SEL_U2                      (2U)

/* Select one unit. */
#define APP_CAN_SEL                         (APP_CAN_SEL_U2)

/* Definitions according to 'APP_CAN'. */
#if (APP_CAN_SEL == APP_CAN_SEL_U1)
    #define APP_CAN_UNIT                    (M4_CAN1)
    #define APP_CAN_PERIP_CLK               (PWC_FCG1_CAN1)

    #define APP_CAN_TX_PORT                 (GPIO_PORT_D)
    #define APP_CAN_TX_PIN                  (GPIO_PIN_05)
    #define APP_CAN_TX_PIN_FUNC             (GPIO_FUNC_60_CAN1_TX)

    #define APP_CAN_RX_PORT                 (GPIO_PORT_D)
    #define APP_CAN_RX_PIN                  (GPIO_PIN_04)
    #define APP_CAN_RX_PIN_FUNC             (GPIO_FUNC_61_CAN1_RX)

    #define APP_CAN_CLK_CH                  (CLK_CAN_CH1)
    #define APP_CAN_CLK_DIV                 (CLK_CAN1_CLK_MCLK_DIV3)

#elif (APP_CAN_SEL == APP_CAN_SEL_U2)
    #define APP_CAN_UNIT                    (M4_CAN2)
    #define APP_CAN_PERIP_CLK               (PWC_FCG1_CAN2)

    #define APP_CAN_TX_PORT                 (GPIO_PORT_D)
    #define APP_CAN_TX_PIN                  (GPIO_PIN_07)
    #define APP_CAN_TX_PIN_FUNC             (GPIO_FUNC_62_CAN2_TX)

    #define APP_CAN_RX_PORT                 (GPIO_PORT_D)
    #define APP_CAN_RX_PIN                  (GPIO_PIN_06)
    #define APP_CAN_RX_PIN_FUNC             (GPIO_FUNC_63_CAN2_RX)

    #define APP_CAN_CLK_CH                  (CLK_CAN_CH2)
    #define APP_CAN_CLK_DIV                 (CLK_CAN2_CLK_MCLK_DIV3)
#else
    #error "The unit is NOT supported!!!"
#endif

/* Acceptance filter. */
#define APP_CAN_AF_SEL                      (CAN_AF1 | CAN_AF2 | CAN_AF3)

#define APP_CAN_AF1_ID                      (0xA1)
#define APP_CAN_AF1_ID_MSK                  (0x00)                  /* Only accept messages with ID '1010 0001'. */
#define APP_CAN_AF1_MSK_TYPE                (CAN_AF_MSK_STD)        /* Only accept standard ID. */

#define APP_CAN_AF2_ID                      (0xB2)
#define APP_CAN_AF2_ID_MSK                  (0xB0)                  /* Accept messages with ID 'x0xx 0010'. */
#define APP_CAN_AF2_MSK_TYPE                (CAN_AF_MSK_EXT)        /* Accept extended ID. */

#define APP_CAN_AF3_ID                      (0xC3)
#define APP_CAN_AF3_ID_MSK                  (0x03)                  /* Accept messages with ID '1100 00xx'. */
#define APP_CAN_AF3_MSK_TYPE                (CAN_AF_MSK_STD_EXT)    /* Accept standard ID and extended ID. */

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         printf
#else
#define DBG(...)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);

static void CanConfig(void);

static void CanTx(void);
static void CanRx(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#if (DDL_PRINT_ENABLE == DDL_ON)
    const static char *IDTypeStr[] = {
        "standard",
        "extended",
    };
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of CAN loopback project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configures the system clock as 120MHz. */
    SystemClockConfig();

#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    DDL_PrintfInit();
#endif /* #if (DDL_PRINT_ENABLE == DDL_ON) */

    /* Configures CAN. */
    CanConfig();

    /***************** Configuration end, application start **************/

    while (1U)
    {
        CanTx();

        CanRx();

        /* Delay to transmitting to observe the received data. */
        DDL_Delay1ms(200U);
    }
}

/**
 * @brief  CAN transmits data.
 * @param  None
 * @retval None
 */
static void CanTx(void)
{
    stc_can_tx_t stcTxPkg;
    uint8_t au8TxPayload[8U];

    au8TxPayload[1U] = 0x12;
    au8TxPayload[2U] = 0x34;
    stcTxPkg.u32Ctrl = 0x0U;
    stcTxPkg.pu8Data = (uint8_t *)&au8TxPayload[0U];
    stcTxPkg.DLC     = 3U;

    stcTxPkg.u32ID   = APP_CAN_AF1_ID;
    /* Standard ID. */
    stcTxPkg.IDE     = 0U;
    au8TxPayload[0U] = (uint8_t)stcTxPkg.u32ID;
    CAN_TransData(APP_CAN_UNIT, &stcTxPkg,
                  CAN_STB, CAN_STB_TRANS_ONE, 1000U);
    DBG("CAN transmitted data with %s ID: %.8lx\n", IDTypeStr[stcTxPkg.IDE], stcTxPkg.u32ID);

    stcTxPkg.u32ID   = APP_CAN_AF2_ID;
    /* Extended ID. */
    stcTxPkg.IDE     = 1U;
    au8TxPayload[0U] = (uint8_t)stcTxPkg.u32ID;
    CAN_TransData(APP_CAN_UNIT, &stcTxPkg,
                  CAN_STB, CAN_STB_TRANS_ONE, 1000U);
    DBG("CAN transmitted data with %s ID: %.8lx\n", IDTypeStr[stcTxPkg.IDE], stcTxPkg.u32ID);

    stcTxPkg.u32ID   = APP_CAN_AF3_ID;
    /* Extended ID. */
    stcTxPkg.IDE     = 1U;
    au8TxPayload[0U] = (uint8_t)stcTxPkg.u32ID;
    CAN_TransData(APP_CAN_UNIT, &stcTxPkg,
                  CAN_STB, CAN_STB_TRANS_ONE, 1000U);
    DBG("CAN transmitted data with %s ID: %.8lx\n", IDTypeStr[stcTxPkg.IDE], stcTxPkg.u32ID);
}

/**
 * @brief  CAN receives data.
 * @param  None
 * @retval None
 */
static void CanRx(void)
{
    uint32_t i = 0;
    uint32_t u32RxCnt = 0;
    uint32_t u32RxFrameCnt = 0;
    stc_can_rx_t stcRxPkg[3U];
    uint8_t au8RxPayload1[8U] = {0U};
    uint8_t au8RxPayload2[8U] = {0U};
    uint8_t au8RxPayload3[8U] = {0U};

    stcRxPkg[0U].pu8Data = (uint8_t *)&au8RxPayload1[0U];
    stcRxPkg[1U].pu8Data = (uint8_t *)&au8RxPayload2[0U];
    stcRxPkg[2U].pu8Data = (uint8_t *)&au8RxPayload3[0U];

    CAN_ReceiveData(APP_CAN_UNIT, &stcRxPkg[0U], &u32RxFrameCnt);
    for (u32RxCnt=0U; u32RxCnt<u32RxFrameCnt; u32RxCnt++)
    {
        DBG("CAN received data with %s ID %.8lx:\n", IDTypeStr[stcRxPkg[u32RxCnt].IDE], stcRxPkg[u32RxCnt].u32ID);
        for (i=0; i<stcRxPkg[u32RxCnt].DLC; i++)
        {
            DBG(" %.2x.", stcRxPkg[u32RxCnt].pu8Data[i]);
        }
        DBG("\n");
    }
}

/**
 * @brief Configures PLLHP(120MHz) as the system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_pllh_init_t stcPLLHInit;
    stc_clk_xtal_init_t stcXtalInit;

    /* Configures XTAL. PLLH input source is XTAL. */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    stcXtalInit.u8XtalDrv   = CLK_XTALDRV_LOW;
    stcXtalInit.u8XtalMode  = CLK_XTALMODE_OSC;
    stcXtalInit.u8XtalStb   = CLK_XTALSTB_499US;
    CLK_XtalInit(&stcXtalInit);

    /* PCLK0, HCLK  Max 240MHz */
    /* PCLK1, PCLK4 Max 120MHz */
    /* PCLK2, PCLK3 Max 60MHz  */
    /* EX BUS Max 120MHz */
    CLK_ClkDiv(CLK_CATE_ALL,                                                    \
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 |              \
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 |              \
                CLK_HCLK_DIV1));

    CLK_PLLHStrucInit(&stcPLLHInit);
    /* VCO = 8/1*120 = 960MHz*/
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 120UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 8UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;

    /* stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL; */
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM123 | SRAM4 | SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);
    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_5);   /* 0-wait @ 40MHz */
    EFM_Unlock();

    CLK_PLLHCmd(Enable);
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  CAN configuration.
 * @param  None
 * @retval None
 */
static void CanConfig(void)
{
    stc_can_init_t stcInit;
    stc_can_af_id_t astcID[] = { \
        {APP_CAN_AF1_ID, APP_CAN_AF1_ID_MSK, APP_CAN_AF1_MSK_TYPE}, \
        {APP_CAN_AF2_ID, APP_CAN_AF2_ID_MSK, APP_CAN_AF2_MSK_TYPE},     \
        {APP_CAN_AF3_ID, APP_CAN_AF3_ID_MSK, APP_CAN_AF3_MSK_TYPE},     \
    };

    /* CAN clock selection. */
    CLK_CAN_ClkConfig(APP_CAN_CLK_CH, APP_CAN_CLK_DIV);

    CAN_StructInit(&stcInit);
    stcInit.u8WorkMode   = CAN_MODE_ELB;
    stcInit.pstcID       = astcID;
    stcInit.u8SelfACKCmd = CAN_SELF_ACK_ENABLE;
    stcInit.u8RBOvfOp    = CAN_RB_OVF_SAVE_NEW;
    stcInit.u16AFSel     = APP_CAN_AF_SEL;

    GPIO_SetFunc(APP_CAN_TX_PORT, APP_CAN_TX_PIN, \
                 APP_CAN_TX_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(APP_CAN_RX_PORT, APP_CAN_RX_PIN, \
                 APP_CAN_RX_PIN_FUNC, PIN_SUBFUNC_DISABLE);

    PWC_Fcg1PeriphClockCmd(APP_CAN_PERIP_CLK, Enable);
    CAN_Init(APP_CAN_UNIT, &stcInit);
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
