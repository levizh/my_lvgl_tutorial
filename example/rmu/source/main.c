/**
 *******************************************************************************
 * @file  rmu/source/main.c
 * @brief Main program of RMU for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-20       Heqb         First version
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
 * @addtogroup RMU
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Test reset mode enum*/
#define RESET_WDT                       (0U)
#define RESET_SWDT                      (1U)
#define RESET_XTALERR                   (2U)
#define RESET_SOFTWARERST               (3U)
#define RESET_PVD                       (4U)
#define RESET_CLKFREQERR                (5U)

/* Modify for test reset mode */
#define TEST_RESET_MODE                 (RESET_WDT)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void PrintResetMode(stc_rmu_rstcause_t stcRst);
static void MakeReset(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of RMU project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_rmu_rstcause_t stcResetFlag;

    /* Configure system clock. */
    SystemClockConfig();
    /* configuration uart for debug information */
    DDL_PrintfInit();
    /* KEY initialize*/
    BSP_KEY_Init();
    /* Enable CPU lockup reset */
    RMU_CPULockUpCmd(Enable);

    /* Get reset cause */
    RMU_GetStatus(&stcResetFlag);
    /* Printf reset cause */
    PrintResetMode(stcResetFlag);

    printf("\nPress SW10 to config reset condition.\n");
    /* Wait short press key SW10 */
    while(Reset == BSP_KEY_GetStatus(BSP_KEY_1))
    {
        ;
    }
    MakeReset();
    RMU_ClrStatus();
    /* Reset condition configuration finished */
    while(1u)
    {
    }
}

/**
 * @brief  Configures the PLLHP(240MHz) as the system clock.
 *         The input source of PLLH is XTAL(8MHz).
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
    CLK_ClkDiv(CLK_CATE_ALL,                                       \
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV8 | CLK_PCLK2_DIV8 | \
                CLK_PCLK3_DIV8 | CLK_PCLK4_DIV8 | CLK_EXCLK_DIV2 | \
                CLK_HCLK_DIV1));

    CLK_PLLHStrucInit(&stcPLLHInit);
    /*
     * PLLP_freq = ((PLL_source / PLLM) * PLLN) / PLLP
     *           = (8 / 1) * 120 / 4
     *           = 240
     */
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = (1UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLN = (120UL - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLP = (4UL   - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLQ = (16UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLR = (16UL  - 1UL);

    /* stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL; */
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM123 | SRAM4 | SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);
    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_5);   /* 5-wait @ 240MHz */
    EFM_Unlock();

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  Print reset information.
 * @param  [in]  stcResetFlag    Reset cause structure
 * @retval None
 */
static void PrintResetMode(stc_rmu_rstcause_t stcResetFlag)
{
    if(Set == stcResetFlag.enXtalErrRst)
    {
        printf("XTAL error reset.\r\n");
    }
    if(Set == stcResetFlag.enCpuLockErrRst)
    {
        printf("M4 CPU lock reset.\r\n");
    }
    if(Set == stcResetFlag.enClkFreqErrRst)
    {
        printf("Clock freqence error reset.\r\n");
    }
    if(Set == stcResetFlag.enRamEccRst)
    {
        printf("Ram ECC reset.\r\n");
    }
    if(Set == stcResetFlag.enRamParityErrRst)
    {
        printf("RAM parity error reset.\r\n");
    }
    if(Set == stcResetFlag.enMpuErrRst)
    {
        printf("Mpu error reset.\r\n");
    }
    if(Set == stcResetFlag.enSoftwareRst)
    {
        printf("Software reset.\r\n");
    }
    if(Set == stcResetFlag.enPowerDownRst)
    {
        printf("Power down reset.\r\n");
    }
    if(Set == stcResetFlag.enSwdtRst)
    {
        printf("Special watchdog timer reset.\r\n");
    }
    if(Set == stcResetFlag.enWdtRst)
    {
        printf("Watchdog timer reset.\r\n");
    }
    if(Set == stcResetFlag.enPvd2Rst)
    {
        printf("Program voltage Dectection 2 reset.\r\n");
    }
    if(Set == stcResetFlag.enPvd1Rst)
    {
        printf("Program voltage Dectection 1 reset.\r\n");
    }
    if(Set == stcResetFlag.enBrownOutRst)
    {
        printf("Low voltage 0 detect reset.\r\n");
    }
    if(Set == stcResetFlag.enRstPinRst)
    {
        printf("Reset pin reset.\r\n");
    }
    if(Set == stcResetFlag.enPowerOnRst)
    {
        printf("Power on reset.\r\n");
    }
}

/**
 * @brief  Make reset condition for test
 * @param  [in]  None
 * @retval None
 */
static void MakeReset(void)
{
#if (TEST_RESET_MODE == RESET_XTALERR)
    /* Config XTAL status detect error reset on*/
    stc_clk_xtalstd_init_t stcXtalStdCfg;
    stc_clk_xtal_init_t    stcXtalInit;

    /* Config XTAL and Enable */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    stcXtalInit.u8XtalMode  = CLK_XTALMODE_OSC;
    stcXtalInit.u8XtalDrv   = CLK_XTALDRV_LOW;
    stcXtalInit.u8XtalStb   = CLK_XTALSTB_499US;
    CLK_XtalInit(&stcXtalInit);

    stcXtalStdCfg.u8XtalStdState = CLK_XTALSTD_ON;
    stcXtalStdCfg.u8XtalStdMode  = CLK_XTALSTD_MODE_RST;
    stcXtalStdCfg.u8XtalStdInt   = CLK_XTALSTD_INT_OFF;
    stcXtalStdCfg.u8XtalStdRst   = CLK_XTALSTD_RST_ON;
    CLK_XtalStdInit(&stcXtalStdCfg);

#elif (TEST_RESET_MODE == RESET_SOFTWARERST)
    /* Software reset MCU */
    NVIC_SystemReset();

#elif (TEST_RESET_MODE == RESET_SWDT)
    /* Configuration  Special Watchdog function */
    stc_swdt_init_t stcSwdtInit;
    /* SWDT configure */
    stcSwdtInit.u32CountCycle    = SWDT_COUNTER_CYCLE_256;
    stcSwdtInit.u32ClockDivision = SWDT_CLOCK_DIV64;
    stcSwdtInit.u32RefreshRange  = SWDT_RANGE_0TO25PCT;
    stcSwdtInit.u32LPModeCountEn = SWDT_LPW_MODE_COUNT_STOP;
    stcSwdtInit.u32TrigType      = SWDT_TRIG_EVENT_RESET;
    SWDT_Init(&stcSwdtInit);
    /* Start SWDT */
    SWDT_ReloadCounter();

#elif (TEST_RESET_MODE == RESET_WDT)
    /* Configuration  Special Watchdog function */
    stc_wdt_init_t stcWdtInit;
    /* WDT configure */
    stcWdtInit.u32CountCycle    = WDT_COUNTER_CYCLE_65536;
    stcWdtInit.u32ClockDivision = WDT_CLOCK_DIV512;
    stcWdtInit.u32RefreshRange  = WDT_RANGE_0TO25PCT;
    stcWdtInit.u32LPModeCountEn = WDT_LPW_MODE_COUNT_STOP;
    stcWdtInit.u32TrigType      = WDT_TRIG_EVENT_RESET;
    WDT_Init(&stcWdtInit);
    /* Start SWDT */
    WDT_ReloadCounter();

#elif (TEST_RESET_MODE == RESET_PVD)
    /* Configuration Program voltage Dectection */
    stc_pwc_lvd_config_t  stcPwcLvdConfig;
    PWC_LVD_StructInit(&stcPwcLvdConfig);
    /* Config PVD */
    /* PVD1: 2.8V; PVD2: 2.7V */
    stcPwcLvdConfig.u8LvdVoltage  = PWC_LVD1_2V8 | PWC_LVD2_2V7;
    stcPwcLvdConfig.u8LvdCmpOutEn = PWC_LVD1_CMP_ON | PWC_LVD2_CMP_ON;
    stcPwcLvdConfig.u8LvdEn       = PWC_LVD1_ON | PWC_LVD2_ON;
    stcPwcLvdConfig.u8LvdIntRstEn = PWC_LVD1_IR_ON | PWC_LVD2_IR_ON;
    stcPwcLvdConfig.u8LvdIntRstSel= PWC_LVD1_RST | PWC_LVD2_RST;
    stcPwcLvdConfig.u8LvdNmiEn    = PWC_LVD1_INT_MASK | PWC_LVD2_INT_MASK;
    PWC_LVD_Init(&stcPwcLvdConfig);

#elif (TEST_RESET_MODE == RESET_CLKFREQERR)
    /* Configuration Clk freqence  measurement function */
    stc_fcm_init_t stcFcmInit;
    stc_clk_xtal_init_t    stcXtalInit;

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_FCM, Enable);

    /* Config XTAL and Enable */
    CLK_XtalStrucInit(&stcXtalInit);
    stcXtalInit.u8XtalState = CLK_XTAL_ON;
    stcXtalInit.u8XtalMode  = CLK_XTALMODE_OSC;
    stcXtalInit.u8XtalDrv   = CLK_XTALDRV_LOW;
    stcXtalInit.u8XtalStb   = CLK_XTALSTB_499US;
    CLK_XtalInit(&stcXtalInit);
    /* Config FCM  Reference Clock: XTAL (8MHZ),  Target Clock: MRC (8MHZ)*/
    FCM_StructInit(&stcFcmInit);
    stcFcmInit.u32RefClk     = FCM_REF_CLK_XTAL;
    stcFcmInit.u32RefClkDiv  = FCM_REF_CLK_DIV8192;
    stcFcmInit.u32RefClkEdge = FCM_REF_CLK_RISING;
    stcFcmInit.u32TarClk     = FCM_TAR_CLK_MRC;
    stcFcmInit.u32TarClkDiv  = FCM_TAR_CLK_DIV1;
    stcFcmInit.u32RstEn      = FCM_RST_ON;
    stcFcmInit.u32IntRstSel  = FCM_ERR_RESET;
    /* idea count value = (tar_freq/tar_div)/(ref_freq/ref_div) */
    stcFcmInit.u16LowerLimit = (uint16_t)((((MRC_VALUE/1U)/(8000000U/8192U))* 80U)/100U);
    stcFcmInit.u16UpperLimit = (uint16_t)((((MRC_VALUE/1U)/(8000000U/8192U))* 85U)/100U);
    FCM_Init(&stcFcmInit);

    /* Enable FMC */
    FCM_Cmd(Enable);
#endif
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
