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

#define APP_CAN_UNIT                    (M4_CAN1)
#define APP_CAN_PERIP_CLK               (PWC_FCG1_CAN1)

#define APP_CAN_TX_PORT                 (GPIO_PORT_D)
#define APP_CAN_TX_PIN                  (GPIO_PIN_05)
#define APP_CAN_TX_PIN_FUNC             (GPIO_FUNC_60_CAN1_TX)

#define APP_CAN_RX_PORT                 (GPIO_PORT_D)
#define APP_CAN_RX_PIN                  (GPIO_PIN_04)
#define APP_CAN_RX_PIN_FUNC             (GPIO_FUNC_61_CAN1_RX)


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

static void CANConfig(void);
static void CANRegRWTest(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

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
    uint32_t i = 0;
    uint32_t u32RxCnt = 0;
    stc_can_tx_t stcTxPkg;
    stc_can_rx_t stcRxPkg;
    uint8_t au8TxPayload[8U];
    uint8_t au8RxPayload[8U];

    /* . */
    SystemClockConfig();

#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    DDL_UartInit();
#endif // #if (DDL_PRINT_ENABLE == DDL_ON)

    /* Configures CAN. */
    CANConfig();

    DBG("CAN test start......\n");
    DDL_Delay1ms(10);
    //DBG("\nCAN test start......");
    /***************** Configuration end, application start **************/

    au8TxPayload[0U] = 0x12;
    au8TxPayload[1U] = 0x34;

    stcTxPkg.u32Ctrl = 0x0U;
    stcTxPkg.u32ID   = 0xA1U + i;
    stcTxPkg.DLC     = 2U;
    stcTxPkg.IDE     = 1U;

    stcTxPkg.pu8Data = (uint8_t *)&au8TxPayload[0U];
    stcRxPkg.pu8Data = (uint8_t *)&au8RxPayload[0U];

#if 1
    while (1U)
    {
        //if (CAN_GetStatus(APP_CAN_UNIT, CAN_FLAG_RX) == Set)
        {
            //CAN_ClrStatus(APP_CAN_UNIT, CAN_FLAG_RX);
            CAN_ReceiveData(APP_CAN_UNIT, &stcRxPkg, &u32RxCnt);
            if (u32RxCnt > 0U)
            {
                DBG("CAN received data:");
                for (i=0; i<stcRxPkg.DLC; i++)
                {
                    DBG(" %.2x.", stcRxPkg.pu8Data[i]);
                }
                DBG("\n");
            }
        }

        /*if (CAN_GetStatus(APP_CAN_UNIT, CAN_FLAG_RB_ALMOST_FULL) == Set)
        {
            CAN_ClrStatus(APP_CAN_UNIT, CAN_FLAG_RB_ALMOST_FULL);
            DBG("\nCAN RB almost full: %d.", i);
        }*/

        /*if (CAN_GetStatus(APP_CAN_UNIT, CAN_FLAG_RB_FIFO_FULL) == Set)
        {
            CAN_ClrStatus(APP_CAN_UNIT, CAN_FLAG_RB_FIFO_FULL);
            DBG("\nCAN RB full: %d.", i);
        }*/
    }
#else
    while (1U)
    {
        stcTxPkg.u32ID = 0xA1U + i;

        CAN_TransData(APP_CAN_UNIT, &stcTxPkg,
                      CAN_STB, CAN_STB_TRANS_ONE, 1000U);
        //CAN_ReceiveData(APP_CAN_UNIT, &stcRxPkg, &u32RxCnt);
        i++;
        if (i >= 10U)
        {
            i = 0U;
        }
        DDL_Delay1ms(200U);
    }
#endif
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
 * @brief
 * @param  [in]
 * @param  [out]
 * @retval None
 */
static void CANConfig(void)
{
    stc_can_init_t stcInit;
    stc_can_af_id_t astcID[] = { \
        {0xA1U, 0xA0U, CAN_AF_MSK_STD_EXT}, \
        {0xA2U, 0xA0U, CAN_AF_MSK_STD},     \
        {0xA3U, 0xF0U, CAN_AF_MSK_EXT},     \
    };

    /* CAN clock selection. */
    CLK_CAN_ClkConfig(CLK_CAN_CH1, CLK_CAN1_CLK_MCLK_DIV3);

    /* */
    CAN_StructInit(&stcInit);
    stcInit.u8WorkMode = CAN_MODE_ELB;
    stcInit.pstcID = astcID;
    stcInit.u8SelfACKCmd = CAN_SELF_ACK_ENABLE;
    stcInit.u8RBOvfOp = CAN_RB_OVF_SAVE_NEW;
    stcInit.u16AFSel = CAN_AF1 | CAN_AF2 | CAN_AF3;

    GPIO_SetFunc(APP_CAN_TX_PORT, APP_CAN_TX_PIN, \
                 APP_CAN_TX_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(APP_CAN_RX_PORT, APP_CAN_RX_PIN, \
                 APP_CAN_RX_PIN_FUNC, PIN_SUBFUNC_DISABLE);

    PWC_Fcg1PeriphClockCmd(APP_CAN_PERIP_CLK, Enable);
    CAN_Init(APP_CAN_UNIT, &stcInit);
}

static void CANRegRWTest(void)
{
#define CAN_BASE                            (0x40009000UL)
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(__reg__)                  ((__reg__) - __PERIP_BASE)
#define __BIT_BAND_ADDR(__reg__, __pos__)   ((__REG_OFS(__reg__) << 5U) + ((uint32_t)(__pos__) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(__reg__, __pos__)          (*(__IO uint32_t *)__BIT_BAND_ADDR((__reg__), (__pos__)))

    uint32_t j;
    uint32_t i;
    uint32_t u32Size;
    uint32_t u32Wt;

    typedef struct
    {
        char *cRegName;
        uint8_t u8BitW;
        uint32_t u32RegAddr;
        uint32_t u32RegMsk;
    } stc_can_reg_t;

    stc_can_reg_t astcReg[] = {
        {"CFG_STAT", 8, CAN_BASE+0xA0, 0x79},
        {"TCMD", 8, CAN_BASE+0xA1, 0xDF},
        {"TCTRL", 8, CAN_BASE+0xA2, 0x70},
        {"RCTRL", 8, CAN_BASE+0xA3, 0xD8},
        {"RTIE", 8, CAN_BASE+0xA4, 0xFE},
        {"ERRINT", 8, CAN_BASE+0xA6, 0xBF},
        {"SBT", 32, CAN_BASE+0xA8, 0x01010101},
        {"FBT", 32, CAN_BASE+0xAC, 0x01010101},
        {"TDC", 8, CAN_BASE+0xB1, 0x81},
        {"EALCAP", 8, CAN_BASE+0xB0, 0x01},
        {"LIMIT", 8, CAN_BASE+0xA7, 0x11},
        {"RECNT", 8, CAN_BASE+0xB2, 0x01},
        {"TECNT", 8, CAN_BASE+0xB3, 0x01},
        {"ACFCTRL", 8, CAN_BASE+0xB4, 0x20},
        {"ACFEN", 16, CAN_BASE+0xB6, 0x01},
        {"ACF", 32, CAN_BASE+0xB8, 0x60000001},
        {"TBSLOT", 8, CAN_BASE+0xBE, 0xC1},
        {"TTCFG", 8, CAN_BASE+0xBF, 0xDF},
        {"REF_MSG", 32, CAN_BASE+0xC0, 0x80000100},
        {"TRG_CFG", 16, CAN_BASE+0xC4, 0x1101},
        {"TT_TRIG", 16, CAN_BASE+0xC6, 0x1},
        {"TT_WTRIG", 16, CAN_BASE+0xC8, 0x1},
    };

    PWC_Fcg1PeriphClockCmd(APP_CAN_PERIP_CLK, Enable);

    u32Size = ARRAY_SZ(astcReg);

    for (i=0; i<u32Size; i++)
    {
        for (j=0; j<astcReg[i].u8BitW; j++)
        {
            if (astcReg[i].u32RegMsk & (1UL << j))
            {
                CAN_SWReset(APP_CAN_UNIT);
                u32Wt = BIT_BAND(astcReg[i].u32RegAddr, j) ^ 0x1;
                BIT_BAND(astcReg[i].u32RegAddr, j) = u32Wt;
                if (BIT_BAND(astcReg[i].u32RegAddr, j) == u32Wt)
                {
                #if 1
                    CAN_EnterNormalComm(APP_CAN_UNIT);
                    u32Wt = BIT_BAND(astcReg[i].u32RegAddr, j) ^ 0x1;
                    BIT_BAND(astcReg[i].u32RegAddr, j) = u32Wt;
                    if (BIT_BAND(astcReg[i].u32RegAddr, j) == u32Wt)
                    {
                        DBG("\n%s[%d], write under NORMAL and RESET mode.", astcReg[i].cRegName, j);
                    }
                    else
                    {
                        DBG("\n%s[%d], write under RESET mode.", astcReg[i].cRegName, j);
                    }
                #else
                    DBG("\n%s[%d], write under RESET mode.", astcReg[i].cRegName, j);
                #endif
                    continue;
                }

                CAN_EnterNormalComm(APP_CAN_UNIT);
                u32Wt = BIT_BAND(astcReg[i].u32RegAddr, j) ^ 0x1;
                BIT_BAND(astcReg[i].u32RegAddr, j) = u32Wt;
                if (BIT_BAND(astcReg[i].u32RegAddr, j) == u32Wt)
                {
                    DBG("\n%s[%d], write under NORMAL mode.", astcReg[i].cRegName, j);
                    continue;
                }

                DBG("\n%s[%d], NG.", astcReg[i].cRegName, j);
            }
        }
    }
}

static void CAN_DETest(void)
{

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
