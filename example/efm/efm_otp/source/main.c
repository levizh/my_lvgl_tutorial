/**
 *******************************************************************************
 * @file  efm/efm_otp/source/main.c
 * @brief Main program of EFM for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-24       Heqb          First version
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
 * @addtogroup EFM_Otp
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

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of EFM project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_efm_cfg_t stcEfmCfg;
    uint32_t flag1, flag2;
    uint32_t u32Data = 0x5A5A5A5AU;

    /* LED & KEY Init */
    BSP_IO_Init();
    BSP_LED_Init();
    BSP_KEY_Init();
    /* Turn on LED_B */
    BSP_LED_On(LED_BLUE);

    /* Unlock EFM. */
    EFM_Unlock();
    /* EFM default config. */
    EFM_StrucInit(&stcEfmCfg);
    /* EFM config */
    EFM_Init(&stcEfmCfg);

    /* Wait flash0, flash1 ready. */
    do{
        flag1 = EFM_GetFlagStatus(EFM_FLAG_RDY0);
        flag2 = EFM_GetFlagStatus(EFM_FLAG_RDY1);
    }while((Set != flag1) || (Set != flag2));
    /* Sector 15 disables write protection */
    EFM_SectorUnlock(EFM_SECTOR15_ADDR, sizeof(u32Data), Enable);
    /* Erase sector 15.  sector 15: 0x0001E000~0x0001FFFF */
    EFM_SectorErase(EFM_SECTOR15_ADDR);
    /* Write data to sector 15 */
    EFM_SingleProgram(EFM_OTP_BLOCK15, 0xEEEEEEEEUL);
    /* SW1 */
    while(Reset == BSP_KEY_GetStatus(BSP_KEY_1))
    {
        ;
    }
    /* SW2 */
    while(Reset == BSP_KEY_GetStatus(BSP_KEY_2))
    {
        ;
    }
    /*  Flash sector 15(OTP block 15) is latched 
        Please fill in the lock address correctly */
    EFM_OTPLock(0x03001AD0);  /* 0x03001AD0 is the latch address of the OTP block 15 */
    /* Single program */
    if(Ok != EFM_SingleProgram(EFM_OTP_BLOCK15, u32Data))
    {
        /* Turn off LED_B */
        BSP_LED_Off(LED_BLUE);
        /* Turn on LED_R */
        BSP_LED_On(LED_RED);
    }
    /* Lock EFM. */
    EFM_Lock();

    while(1)
    {
        ;
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
