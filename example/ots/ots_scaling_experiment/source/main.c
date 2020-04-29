/**
 *******************************************************************************
 * @file  ots/ots_scaling_experiment/source/main.c
 * @brief Main program OTS scaling experiment for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-21       Wuze            First version
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
 * @addtogroup OTS_Scaling_Experiment
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* This example will show how to do scaling experiment */

/* Average count. */
#define OTS_AVG_COUNT               (10U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

static void ButtonConfig(void);
static void ButtonWait(void);

static void OtsHrcConfig(void);
static void OtsXtalConfig(void);
static void OtsScalingExperiment(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of ots_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* The system clock is MRC(8MHz) by default. */

    ButtonConfig();

    /***************** Configuration end, application start **************/

    while (1U)
    {
        /* 1. HRC 16MHz. */
        OTS_DeInit();
        OtsHrcConfig();

        /* 2.  */
        //TODO:DBG printing.

        /* 3. Button waiting and scaling experiment. */
        OtsScalingExperiment();

        /* 4. XTAL 8MHz. */
        OTS_DeInit();
        OtsXtalConfig();

        /* 5.  */
        //TODO:DBG printing.

        /* 6. Button waiting and scaling experiment. */
        OtsScalingExperiment();
    }
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
static void ButtonConfig(void)
{}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
static void ButtonWait(void)
{}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
static void OtsHrcConfig(void)
{
    stc_ots_init_t stcInit;

    OTS_StructInit();
    stcInit.u16ClkSel = OTS_CLK_HRC;
    /* Initials OTS. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_OTS, Enable);
    OTS_Init(&stcInit);

    /* Clock configuration. */
    CLK_HrcCmd(Enable);
    CLK_Xtal32Cmd(Enable);
    CLK_LrcCmd(Enable);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
static void OtsXtalConfig(void)
{
    stc_ots_init_t stcInit;

    OTS_StructInit();
    stcInit.u16ClkSel = OTS_CLK_XTAL;
    /* Initials OTS. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_OTS, Enable);
    OTS_Init(&stcInit);

    /* Clock configuration. */
    CLK_XtalCmd(Enable);
    CLK_LrcCmd(Enable);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
static void OtsScalingExperiment(void)
{
    uint32_t i;
    uint16_t u16Dr1;
    uint16_t u16Dr2;
    uint16_t u16Ecr;
    float32_t f32A;
    float32_t f32ASum = 0U;

    ButtonWait();

    for (i=0U; i<OTS_AVG_COUNT; i++)
    {
        DDL_Delay1ms(100U);
        OTS_ScalingExperiment(&u16Dr1, &u16Dr2, &u16Ecr, &f32A);
        //TODO:DBG printing.
        f32ASum += f32A;
    }

    f32A = f32ASum / (float32_t)OTS_AVG_COUNT;
    //TODO:DBG printing.
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
