/**
 *******************************************************************************
 * @file  system_hc32f4a0.c
 * @brief This file provides two functions and one global variable to be called
 *        from  user application
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-26       Zhangxl         First version
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
#include "hc32_common.h"

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32F4A0_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Variable
 * @{
 */

uint32_t SystemCoreClock = HRC_VALUE;  /*!< System clock frequency (Core clock) */

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Functions
 * @{
 */

/**
 * @brief  Setup the microcontroller system. Initialize the System and update
 *         the SystemCoreClock variable.
 * @param  None
 * @retval None
 */
void SystemInit(void)
{
    (*((volatile unsigned short*)(0x400543FEUL)))=0xA50FU;
    (*((volatile unsigned int*)(0x4004CCE8UL)))=0x00040000UL;
    (*((volatile unsigned short*)(0x400543FEUL)))=0xA500U;
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 * @param  None
 * @retval None
 */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp = 0UL;
    uint32_t plln = 19UL, pllp = 1UL, pllm = 0UL;

    tmp = M4_CMU->CKSWR & CMU_CKSWR_CKSW;
    switch(tmp)
    {
        case 0x00UL:  /* use internal high speed RC */
            SystemCoreClock = HRC_VALUE;
            break;
        case 0x01UL:  /* use internal middle speed RC */
            SystemCoreClock = MRC_VALUE;
            break;
        case 0x02UL:  /* use internal low speed RC */
            SystemCoreClock = LRC_VALUE;
            break;
        case 0x03UL:  /* use external high speed RC */
            SystemCoreClock = XTAL_VALUE;
            break;
        case 0x04UL:  /* use external low speed RC */
            SystemCoreClock = XTAL32_VALUE;
            break;
        case 0x05UL:  /* use PLLH */
            /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
            pllp = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHP_POS) & 0x0FUL);
            plln = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHN_POS) & 0xFFUL);
            pllm = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHM_POS) & 0x03UL);

            /* use exteranl high speed OSC as PLL source */
            if (0UL == bM4_CMU->PLLHCFGR_b.PLLSRC)
            {
                SystemCoreClock = (XTAL_VALUE) / (pllm + 1UL) * (plln + 1UL) / (pllp + 1UL);
            }
            /* use interanl high RC as PLL source */
            else
            {
                SystemCoreClock = (HRC_VALUE) / (pllm + 1UL) * (plln + 1UL) / (pllp + 1UL);
            }
            break;
    }
}

#if defined (__CC_ARM) || defined (__CLANG_ARM)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemCoreClockUpdate();
    $Super$$main();
    return 0;
}
#elif defined (__ICCARM__)
extern int32_t main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int __low_level_init(void)
{
    // call IAR table copy function.
    __iar_data_init3();
    SystemCoreClockUpdate();
    main();
    return 0;
}
#elif defined (__GNUC__)
/* Add entry to arm-none-eabi-gcc argument */
int entry(void)
{
    SystemCoreClockUpdate();
    return 0;
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
