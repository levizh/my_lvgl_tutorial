/**
 *******************************************************************************
 * @file  sdioc/sdioc_mmc/source/main.c
 * @brief Main program of SDIOC SD MMC for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-09       Yangjp          First version
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
#include "mmc.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup SDIOC_SD_Mmc
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SD DMA transfer mode, Use polling mode to comment the following macro */
#define SDIOC_DMA_TRANS_MODE

#ifdef SDIOC_DMA_TRANS_MODE
#define SDIOC_DMA_UNIT                          (M4_DMA1)
#define SDIOC_DMA_DATA_CH                       (DMA_CH0)
#endif

/* CK = PC12 */
#define SDIOC_CK_PORT                           (GPIO_PORT_C)
#define SDIOC_CK_PIN                            (GPIO_PIN_12)
/* CMD = PD02 */
#define SDIOC_CMD_PORT                          (GPIO_PORT_D)
#define SDIOC_CMD_PIN                           (GPIO_PIN_02)
/* D0 = PB07 */
#define SDIOC_D0_PORT                           (GPIO_PORT_B)
#define SDIOC_D0_PIN                            (GPIO_PIN_07)
/* D1 = PA08 */
#define SDIOC_D1_PORT                           (GPIO_PORT_A)
#define SDIOC_D1_PIN                            (GPIO_PIN_08)
/* D2 = PC10 */
#define SDIOC_D2_PORT                           (GPIO_PORT_C)
#define SDIOC_D2_PIN                            (GPIO_PIN_10)
/* D3 = PB05 */
#define SDIOC_D3_PORT                           (GPIO_PORT_B)
#define SDIOC_D3_PIN                            (GPIO_PIN_05)

/* SD MMC read/write/erase */
#define SD_MMC_BLOCK_SIZE                       (512U)
#define SD_MMC_BLOCK_NUMBER                     (20U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
stc_mmc_handle_t MmcHandle;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint32_t u32WriteBlocks[SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER];
static uint32_t u32ReadBlocks[SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Initializes the SD GPIO.
 * @param  None
 * @retval None
 */
static void SD_GpioInit(void)
{
    /* SDIO1_CD */
    BSP_IO_ConfigPortPin(EIO_PORT0, EIO_SDIC1_CD, EIO_DIR_IN);

    /* SDIOC pins configuration */
    GPIO_SetFunc(SDIOC_CK_PORT,  SDIOC_CK_PIN,  GPIO_FUNC_9_SDIO1_CK,   PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_CMD_PORT, SDIOC_CMD_PIN, GPIO_FUNC_9_SDIO1_CMD,  PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D0_PORT,  SDIOC_D0_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D1_PORT,  SDIOC_D1_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D2_PORT,  SDIOC_D2_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D3_PORT,  SDIOC_D3_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
}

/**
 * @brief  Get SD MMC insert status.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: SD MMC inserted
 *           - Reset: No SD MMC insert
 */
static en_flag_status_t SDMmc_GetInsertStatus(void)
{
    en_flag_status_t enFlagSta = Set;

    /* Check SD MMC detect pin */
    if (0U != BSP_IO_ReadPortPin(EIO_PORT0, EIO_SDIC1_CD))
    {
        enFlagSta = Reset;
    }

    return enFlagSta;
}

/**
 * @brief  SD MMC configuration.
 * @param  None
 * @retval None
 */
static void SDMmc_Config(void)
{
    __IO en_result_t enRet = Error;

    /* Init SD GPIO */
    SD_GpioInit();
    /* Enable ETH clock */
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_SDIOC1, Enable);

    /* Configure structure initialization */
    MmcHandle.SDIOCx = M4_SDIOC1;
    MmcHandle.stcSdiocInit.u32Mode            = SDIOC_MODE_MMC;
    MmcHandle.stcSdiocInit.u8CardDetectSelect = SDIOC_CARD_DETECT_CD_PIN_LEVEL;
    MmcHandle.stcSdiocInit.u8SpeedMode        = SDIOC_SPEED_MODE_NORMAL;
    MmcHandle.stcSdiocInit.u8BusWidth         = SDIOC_BUS_WIDTH_4BIT;
    MmcHandle.stcSdiocInit.u16ClockDiv        = SDIOC_CLOCK_DIV_8;
#ifdef SDIOC_DMA_TRANS_MODE
    MmcHandle.DMAx    = SDIOC_DMA_UNIT;
    MmcHandle.u8DmaCh = SDIOC_DMA_DATA_CH;
#endif

    /* Reset SDIOC */
    if (Ok != SDIOC_SoftwareReset(MmcHandle.SDIOCx, SDIOC_SW_RESET_ALL))
    {
        printf("Reset SDIOC failed!\r\n");
    }
    else
    {
        if (Set != SDMmc_GetInsertStatus())
        {
            printf("No SD MMC insertion!\r\n");
        }

        if (Ok != MMC_Init(&MmcHandle))
        {
            printf("SD MMC initialize failed!\r\n");
        }
        else
        {
            enRet = Ok;
        }
    }

    /* stop read/write test */
    if (Ok != enRet)
    {
        while (1)
        {
            ;
        }
        
    }
}

/**
 * @brief  SD MMC erase.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: SD MMC erase success
 *           - Error: SD MMC erase error
 */
static en_result_t SDMmc_Erase(void)
{
    __IO uint32_t i;
    en_result_t enRet = Ok;

    /* Initialize read/write blocks */
    memset(u32ReadBlocks, 0x12345678UL, (SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER));
    /* Erase SD MMC */
    if (Ok != MMC_Erase(&MmcHandle, 0UL, SD_MMC_BLOCK_NUMBER))
    {
        enRet = Error;
    }
    /* Read SD MMC */
    if (Ok != MMC_ReadBlocks(&MmcHandle, 0UL, SD_MMC_BLOCK_NUMBER, (uint8_t *)u32ReadBlocks, 2000UL))
    {
        enRet = Error;
    }
    /* Check whether data value is OxFFFFFFFF or 0x00000000 after erase SD MMC */
    for (i = 0UL; i < (SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER); i++)
    {
        if ((0xFFFFFFFFUL != u32ReadBlocks[i]) && (0x00000000UL != u32ReadBlocks[i]))
        {
            enRet = Error;
            break;
        }
    }

    if (Ok != enRet)
    {
        printf("SD MMC erase failed!\r\n");
    }

    return enRet;
}

/**
 * @brief  SD MMC multi-block read/write.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: SD MMC multi-block read/write success
 *           - Error: SD MMC multi-block read/write error
 */
static en_result_t SDMmc_RWMultiBlock(void)
{
    en_result_t enRet = Ok;

    /* Initialize read/write blocks */
    memset(u32WriteBlocks, 0x12345678UL, (SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER));
    memset(u32ReadBlocks,  0UL, (SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER));
    /* Erase SD MMC */
    if (Ok != MMC_WriteBlocks(&MmcHandle, 0UL, SD_MMC_BLOCK_NUMBER, (uint8_t *)u32WriteBlocks, 2000U))
    {
        enRet = Error;
    }
    /* Read SD MMC */
    if (Ok != MMC_ReadBlocks(&MmcHandle, 0UL, SD_MMC_BLOCK_NUMBER, (uint8_t *)u32ReadBlocks, 2000UL))
    {
        enRet = Error;
    }
    /* Check data value */
    if (0U != memcmp(u32WriteBlocks, u32ReadBlocks, (SD_MMC_BLOCK_SIZE * SD_MMC_BLOCK_NUMBER)))
    {
        enRet = Error;
    }

    if (Ok != enRet)
    {
        printf("SD MMC multi-block read/write failed!\r\n");
    }

    return enRet;
}

/**
 * @brief  SYS clock initialize.
 * @param  None
 * @retval None
 */
void SYS_CLK_Init(void)
{
    stc_clk_pllh_init_t stcPLLHInit;

    /* PCLK0, HCLK Max 200MHz */
    CLK_ClkDiv(CLK_CATE_ALL, (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 | \
                              CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 | \
                              CLK_HCLK_DIV1));

    CLK_PLLHStrucInit(&stcPLLHInit);
    /* VCO = 16/2*100 = 800MHz*/
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 100UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_HRC;
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM123 | SRAM4 | SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);
    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_5);   /* 0-wait @ 40MHz */
    EFM_Unlock();

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  Main function of SDIOC SD MMC.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    en_result_t enEraseRet = Ok, enMulBlkRet = Ok;

    /* Configure clock */
    SYS_CLK_Init();
    /* Configure BSP */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Configure UART */
    DDL_PrintfInit();
    /* Configure SD MMC */
    SDMmc_Config();

    /* Erase/single-block/multi-block test */
    enEraseRet  = SDMmc_Erase();
    enMulBlkRet = SDMmc_RWMultiBlock();
    if ((Ok != enEraseRet) || (Ok != enMulBlkRet))
    {
        /* Test failed */
        BSP_LED_On(LED_RED);
        BSP_LED_Off(LED_BLUE);
    }
    else
    {
        /* Test success */
        BSP_LED_On(LED_BLUE);
        BSP_LED_Off(LED_RED);
    }

    while (1)
    {        
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
