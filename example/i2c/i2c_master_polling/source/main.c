/**
 *******************************************************************************
 * @file  i2c/i2c_master_polling/source/main.c
 * @brief Main program of I2C for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-26       Hexiao         First version
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
 * @addtogroup I2C_Master_Polling
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Define slave device address for example */
#define DEVICE_ADDRESS                  0x06U
/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_D)
#define I2C_SCL_PIN                     (GPIO_PIN_03)
#define I2C_SDA_PORT                    (GPIO_PORT_F)
#define I2C_SDA_PIN                     (GPIO_PIN_10)

#define I2C_RET_OK                      0U
#define I2C_RET_ERROR                   1U

#define GENERATE_START                  0x00U
#define GENERATE_RESTART                0x01U

#define ADDRESS_W                       0x00U
#define ADDRESS_R                       0x01U

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   128U
/* Define i2c baudrate */
#define I2C_BAUDRATE                    400000UL

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint32_t gu32TimeOutCnt = 0x10000;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 /**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_pllh_init_t stcPLLHInit;
    
    /* HCLK  Max 240MHz */
    CLK_ClkDiv(CLK_CATE_ALL,                                                    \
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 |                \
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 |                \
                CLK_HCLK_DIV1));

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_6);
    EFM_Unlock();
    
    /* PLLH config */
    CLK_PLLHStrucInit(&stcPLLHInit);
    /*
    16MHz/M*N/P = 16/1*60/4 =240MHz
    */
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = (1UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLN = (60UL - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLP = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLR = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLQ = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_HRC;
    CLK_PLLHInit(&stcPLLHInit);
    CLK_PLLHCmd(Enable);
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);

    /* Config clock output system clock */
    CLK_MCO1Config(CLK_MCOSOURCCE_SYSCLK, CLK_MCODIV_128);
    /* Config clock output pin */
    GPIO_SetFunc(GPIO_PORT_A, GPIO_PIN_08, GPIO_FUNC_1_MCO, Disable);
    /* MCO1 output enable */
    CLK_MCO1Cmd(Enable);
}

/**
 * @brief   Send start or restart condition
 * @param   [in]  u8Start  Indicate the start mode, start or restart
 * @retval  Process result
 *          - I2C_RET_ERROR  Send start or restart failed
 *          - I2C_RET_OK     Send start or restart success
 */
static en_result_t Master_StartOrRestart(uint8_t u8Start)
{
    en_result_t enRet = Ok;

    /* generate start or restart signal */
    if(GENERATE_START == u8Start)
    {
        enRet = I2C_Start(M4_I2C1,gu32TimeOutCnt);
    }
    else
    {
        /* Clear start status flag */
        enRet = I2C_Restart(M4_I2C1,gu32TimeOutCnt);

    }

    return enRet;
}

/**
 * @brief   Send slave address
 * @param   [in]  u8Adr  The slave address
 * @retval  Process result
 *          - I2C_RET_ERROR  Send failed
 *          - I2C_RET_OK     Send success
 */
static en_result_t Master_SendAdr(uint8_t u8Adr)
{
   return I2C_SendAddr(M4_I2C1,u8Adr,gu32TimeOutCnt);
}

/**
 * @brief   Send data to slave
 * @param   [in]  pTxData  Pointer to the data buffer
 * @param   [in]  u32Size  Data size
 * @retval  Process result
 *          - I2C_RET_ERROR  Send failed
 *          - I2C_RET_OK     Send success
 */
static en_result_t Master_WriteData(uint8_t const pTxData[], uint32_t u32Size)
{
    return I2C_SendData(M4_I2C1, pTxData, u32Size,gu32TimeOutCnt);
}

/**
 * @brief   Write address and receive data from slave
 * @param   [in]  pRxData  Pointer to the data buffer
 * @param   [in]  u32Size  Data size
 * @retval  Process result
 *          - I2C_RET_ERROR  Process failed
 *          - I2C_RET_OK     Process success
 */
static en_result_t Master_RevData(uint8_t pRxData[], uint32_t u32Size)
{
    return I2C_RcvData(M4_I2C1,pRxData, u32Size,gu32TimeOutCnt);
}

/**
 * @brief   General stop condition to slave
 * @param   None
 * @retval  Process result
 *          - I2C_RET_ERROR  Process failed
 *          - I2C_RET_OK     Process success
 */
en_result_t Master_Stop(void)
{
   return I2C_Stop(M4_I2C1,gu32TimeOutCnt);
}

/**
 * @brief   Initialize the I2C peripheral for master
 * @param   None
 * @retval  Process result
 *          - I2C_RET_ERROR  Process failed
 *          - I2C_RET_OK     Process success
 */
uint8_t Master_Initialize(void)
{
    stc_i2c_init_t stcI2cInit;
    float32_t fErr;

    I2C_DeInit(M4_I2C1);

    I2C_StructInit(&stcI2cInit);
    stcI2cInit.u32Baudrate = I2C_BAUDRATE;
    stcI2cInit.u32SclTime = 5U;
    stcI2cInit.u32I2cClkDiv = I2C_CLK_DIV1;
    I2C_Init(M4_I2C1, &stcI2cInit, &fErr);

    I2C_Cmd(M4_I2C1, Enable);

    return I2C_RET_OK;
}

/**
 * @brief   Judge the result. LED0 toggle when result is error status.
 * @param   [in]  u8Result    Result to be judged
 * @retval  None
 */
static void JudgeResult(en_result_t enRet)
{
    if(Ok != enRet)
    {
        while(1)
        {
            DDL_Delay1ms(500U);
        }
    }
}


/**
 * @brief  systick callback function
 * @param  [in]  None
 * @retval None
 *
 */
void SysTick_IrqHandler(void)
{
    SysTick_IncTick();
}

#ifdef Debug
uint32_t TimeCntForWaitAStatus(uint32_t u32MS)
{
    SysTick_Init(1000u);
    SysTick_Resume();
    uint32_t testTimeCnt = 0x1000000u;
    uint32_t t1 =  SysTick_GetTick();
    I2C_WaitStatus(M4_I2C1, I2C_SR_STARTF, Set, testTimeCnt);
    uint32_t t2 =  SysTick_GetTick();
    uint32_t u32CntForWaitAStatus = testTimeCnt/(t2 - t1);

    return u32CntForWaitAStatus * u32MS;
}
#endif

/**
 * @brief  Main function of i2c_master_polling project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    en_result_t enRet = Ok;
    uint8_t u8TxBuf[TEST_DATA_LEN];
    uint8_t u8RxBuf[TEST_DATA_LEN] = {0};

    SystemClockConfig();
    /* Test buffer initialize */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8TxBuf[i] = (uint8_t)(i+1U);
    }

    /* Initialize I2C port*/
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(I2C_SCL_PORT, I2C_SCL_PIN, &stcGpioInit);
    GPIO_Init(I2C_SDA_PORT, I2C_SDA_PIN, &stcGpioInit);
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_FUNC_49_I2C1_SCL, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_FUNC_48_I2C1_SDA, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_IIC1, Enable);

    /* Initialize I2C peripheral and enable function*/
    Master_Initialize();
    #ifdef Debug
    gu32TimeOutCnt = TimeCntForWaitAStatus(5);
    #endif

    /* I2C master data write*/
    enRet = Master_StartOrRestart(GENERATE_START);
    JudgeResult(enRet);
    enRet = Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1u)|ADDRESS_W);
    JudgeResult(enRet);
    enRet = Master_WriteData(u8TxBuf, TEST_DATA_LEN);
    JudgeResult(enRet);
    enRet = Master_Stop();
    JudgeResult(enRet);

    /* 5mS delay for device*/
    DDL_Delay1ms(5u);

    /* I2C master data read*/
    enRet = Master_StartOrRestart(GENERATE_START);
    JudgeResult(enRet);
    enRet = Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1u)|ADDRESS_R);
    JudgeResult(enRet);
    enRet = Master_RevData(u8RxBuf, TEST_DATA_LEN);
    JudgeResult(enRet);
    enRet = Master_Stop();
    JudgeResult(enRet);

    /* Compare the data */
    for(i=0u; i<TEST_DATA_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* Data write error*/
            while(1)
            {
                DDL_Delay1ms(500u);
            }
        }
    }

    /* I2C master polling communication success */
    while(1)
    {
        DDL_Delay1ms(500u);
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
