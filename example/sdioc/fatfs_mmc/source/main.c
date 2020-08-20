/**
 *******************************************************************************
 * @file  sdioc/fatfs_mmc/source/main.c
 * @brief Main program of FatFs MMC Card for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-07-15       Zhangxl         Use XTAL 8MHz as PLL source
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
#include "gen_drv.h"
#include "mmc_diskio.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup FatFS_Mmc_Card
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
FATFS MMCFatFs;     /* File system object */
FIL TestFile;       /* File object */
char MMCPath[4];    /* MMC card logical drive path */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/* A work buffer for the f_mkfs() */
static uint8_t u8WorkBuffer[FF_MAX_SS];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  MCU Peripheral registers write unprotected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WE(void)
{
    /* Unlock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    GPIO_Unlock();
    /* Unlock PWC register: FCG0 */
    PWC_FCG0_Unlock();
    /* Unlock PWC, CLK, PVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    PWC_Unlock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1);
    /* Unlock SRAM register: WTCR */
    SRAM_WTCR_Unlock();
    /* Unlock SRAM register: CKCR */
    // SRAM_CKCR_Unlock();
    /* Unlock all EFM registers */
    EFM_Unlock();
    /* Unlock EFM register: FWMC */
    // EFM_FWMC_Unlock();
    /* Unlock EFM OTP write protect registers */
    // EFM_OTP_WP_Unlock();
}

/**
 * @brief  MCU Peripheral registers write protected.
 * @param  None
 * @retval None
 * @note Comment/uncomment each API depending on APP requires.
 */
static void Peripheral_WP(void)
{
    /* Lock GPIO register: PSPCR, PCCR, PINAER, PCRxy, PFSRxy */
    // GPIO_Lock();
    /* Lock PWC register: FCG0 */
    PWC_FCG0_Lock();
    /* Lock PWC, CLK, PVD registers, @ref PWC_REG_Write_Unlock_Code for details */
    // PWC_Lock(PWC_UNLOCK_CODE_0 | PWC_UNLOCK_CODE_1 | PWC_UNLOCK_CODE_2);
    /* Lock SRAM register: WTCR */
    SRAM_WTCR_Lock();
    /* Lock SRAM register: CKCR */
    // SRAM_CKCR_Lock();
    /* Lock EFM OTP write protect registers */
    // EFM_OTP_WP_Lock();
    /* Lock EFM register: FWMC */
    // EFM_FWMC_Lock();
    /* Lock all EFM registers */
    EFM_Lock();
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
    /* VCO = (8/1)*100 = 800MHz*/
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 100UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
    CLK_PLLHInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM_SRAM123 | SRAM_SRAM4 | SRAM_SRAMB), SRAM_WAIT_CYCLE_2, SRAM_WAIT_CYCLE_2);

    /* 0-wait @ 40MHz */
    EFM_SetWaitCycle(EFM_WAIT_CYCLE_5);   

    /* 4 cycles for 200 ~ 250MHz */
    GPIO_SetReadWaitCycle(GPIO_READ_WAIT_4);

    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);
}

/**
 * @brief  Main function of FatFs MMC card.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    FRESULT fRet;
    uint32_t u32WBNbr, u32RBNbr;
    uint8_t u8WriteText[] = "This is a string used to test the FatFs";
    uint8_t u8ReadText[100];
    en_result_t enTestRet = Error;
    MKFS_PARM opt;

    /* Peripheral registers write unprotected */
    Peripheral_WE();
    /* Configure clock */
    SYS_CLK_Init();
    /* Configure BSP */
    BSP_IO_Init();
    BSP_LED_Init();
    /* Configure UART */
    DDL_PrintfInit();

    /* Link the micro MMC disk I/O driver */
    if (0U == FatFS_LinkDriver(&gMMCDriver, MMCPath))
    {
        /* Register the file system object to the FatFs module */
        if (FR_OK != f_mount(&MMCFatFs, (TCHAR const*)MMCPath, 0U))
        {
            printf("FatFs Initialization Error!\r\n");
        }
        else
        {
            memset(&opt, 0, sizeof(MKFS_PARM));
            opt.fmt = (BYTE)FM_ANY;
            /* Create a FAT file system (format) on the logical drive */
            if (FR_OK != f_mkfs((TCHAR const*)MMCPath, &opt, u8WorkBuffer, sizeof(u8WorkBuffer)))
            {
                printf("FatFs Format Error!\r\n");
            }
            else
            {
                /* Create and Open a new text file object with write access */
                if (FR_OK != f_open(&TestFile, "Test.txt", ((BYTE)FA_CREATE_ALWAYS | (BYTE)FA_WRITE)))
                {
                    printf("\"Test.txt\" file Open for write Error!\r\n");
                }
                else
                {
                    /* Write data to the text file */
                    fRet = f_write(&TestFile, u8WriteText, sizeof(u8WriteText), (void *)&u32WBNbr);
                    if ((0UL == u32WBNbr) || (FR_OK != fRet))
                    {
                        printf("\"Test.txt\" file Write or EOF Error!\r\n");
                    }
                    else
                    {
                        /* Close the open text file */
                        f_close(&TestFile);
                        /* Open the text file object with read access */
                        if (FR_OK != f_open(&TestFile, "Test.txt", (BYTE)FA_READ))
                        {
                            printf("\"Test.txt\" file Open for read Error!\r\n");
                        }
                        else
                        {
                            memset(u8ReadText, 0, sizeof(u8ReadText));
                            /* Read data from the text file */
                            fRet = f_read(&TestFile, u8ReadText, sizeof(u8ReadText), (UINT*)&u32RBNbr);
                            if ((0UL == u32RBNbr) || (FR_OK != fRet))
                            {
                                printf("\"Test.txt\" file Read or EOF Error!\r\n");
                            }
                            else
                            {
                                /* Close the open text file */
                                f_close(&TestFile);
                                /* Compare read data with the expected data */
                                if (u32RBNbr == u32WBNbr)
                                {
                                    /* Check data value */
                                    if (0 == memcmp(u8WriteText, u8ReadText, u32RBNbr))
                                    {
                                        enTestRet = Ok;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /* Unlink the micro MMC disk I/O driver */
    FatFS_UnLinkDriver(MMCPath);

    if (Ok != enTestRet)
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
    /* Peripheral registers write protected */
    Peripheral_WP();

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
