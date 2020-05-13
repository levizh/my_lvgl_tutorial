/**
 *******************************************************************************
 * @file  i2c/i2c_at24c02/source/main.c
 * @brief Main program of I2C for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-26       Hexiao          First version
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

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Define I2C unit used for the example */
#define I2C_CH                          (M4_I2C1)
/* Define E2PROM device address */
#define E2_ADDRESS                      0x50u
/* AT24C02 page length is 8byte*/
#define PAGE_LEN                        8u
/* Define test address for read and write */
#define DATA_TEST_ADDR                  0x00u
/* Define port and pin for SDA and SCL */
#define I2C1_SCL_PORT                   (GPIO_PORT_D)
#define I2C1_SCL_PIN                    (GPIO_PIN_03)
#define I2C1_SDA_PORT                   (GPIO_PORT_F)
#define I2C1_SDA_PIN                    (GPIO_PIN_10)
/* Define i2c baudrate */
#define I2C_BAUDRATE                    400000UL

#define TIMEOUT                         0x10000ul

#define I2C_RET_OK                      0u
#define I2C_RET_ERROR                   1u

#define GENERATE_START                  0x00u
#define GENERATE_RESTART                0x01u

#define E2_ADDRESS_W                    0x00u
#define E2_ADDRESS_R                    0x01u
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
 ******************************************************************************
 ** \brief  Send start or restart condition
 **
 ** \param  none
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
static uint8_t E2_StartOrRestart(uint8_t u8Start)
{
    en_result_t enRet = Ok;

    /* generate start or restart signal */
    if(GENERATE_START == u8Start)
    {
        enRet = I2C_Start(M4_I2C1,TIMEOUT);
    }
    else
    {
        /* Clear start status flag */
        enRet = I2C_Restart(M4_I2C1,TIMEOUT);

    }

    return enRet;
}


/**
 ******************************************************************************
 ** \brief  Send e2prom device address
 **
 ** \param  u16Adr  The slave address
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
static uint8_t E2_SendAdr(uint8_t u8Adr)
{
    return I2C_SendAddr(M4_I2C1,u8Adr,TIMEOUT);
}

/**
 ******************************************************************************
 ** \brief  Send data address to e2prom
 **
 ** \param  u8DataAdr  Data address to be send
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
static uint8_t E2_SendDataAdr(uint8_t u8DataAdr)
{
    return I2C_SendData(M4_I2C1, &u8DataAdr, 1, TIMEOUT);
}

/**
 ******************************************************************************
 ** \brief  Send data to e2prom
 **
 ** \param  pTxData  Pointer to the data buffer
 ** \param  u32Size  Data size
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
static uint8_t E2_WriteData(uint8_t *pTxData, uint32_t u32Size)
{
    return I2C_SendData(M4_I2C1, pTxData, u32Size, TIMEOUT);
}

/**
 ******************************************************************************
 ** \brief  Receive data from e2prom
 **
 ** \param  pTxData  Pointer to the data buffer
 ** \param  u32Size  Data size
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
static uint8_t E2_RevData(uint8_t *pRxData, uint32_t u32Size)
{
    return I2C_RcvData(M4_I2C1,pRxData, u32Size,TIMEOUT);
}

/**
 ******************************************************************************
 ** \brief  General stop condition to e2prom
 **
 ** \param  None
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  Send failed
 **         - I2C_RET_OK     Send success
 ******************************************************************************/
uint8_t E2_Stop(void)
{
    return I2C_Stop(M4_I2C1,TIMEOUT);
}

/**
 ******************************************************************************
 ** \brief  Initialize the I2C peripheral for e2prom
 **
 ** \param  None
 **
 ** \retval Process result
 **         - I2C_RET_ERROR  failed
 **         - I2C_RET_OK     success
 ******************************************************************************/
uint8_t E2_Initialize(void)
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
 ******************************************************************************
 ** \brief  Judge the result. LED0 toggle when result is error status.
 **
 ** \param  u8Result
 **
 ** \retval None
 ******************************************************************************/
static void JudgeResult(uint8_t u8Result)
{
    if(Ok != u8Result)
    {
        while(1)
        {
            DDL_Delay1ms(500ul);
        }
    }
}

/**
 *******************************************************************************
 ** \brief  Main function of template project
 **
 ** \param  None
 **
 ** \retval int32_t return value, if needed
 **
 ******************************************************************************/
int32_t main(void)
{
    uint8_t u8TxBuf[PAGE_LEN];
    uint8_t u8RxBuf[PAGE_LEN];
    uint32_t i;
    uint8_t u8Ret = I2C_RET_OK;

    /* Configure system clock. */
    BSP_CLK_Init();

    for(i=0ul; i<PAGE_LEN; i++)
    {
        u8TxBuf[i] = (uint8_t)i+1u;
    }
    memset(u8RxBuf, 0x00, PAGE_LEN);

    /* Initialize I2C port*/
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(I2C1_SCL_PORT, I2C1_SCL_PIN, &stcGpioInit);
    GPIO_Init(I2C1_SDA_PORT, I2C1_SDA_PIN, &stcGpioInit);
    GPIO_SetFunc(I2C1_SCL_PORT, I2C1_SCL_PIN, GPIO_FUNC_49_I2C1_SCL, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(I2C1_SDA_PORT, I2C1_SDA_PIN, GPIO_FUNC_48_I2C1_SDA, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_IIC1, Enable);
    /* Initialize I2C peripheral and enable function*/
    E2_Initialize();

    /* E2prom byte write*/
    u8Ret = E2_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_W);
    JudgeResult(u8Ret);
    u8Ret = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(u8Ret);
    u8Ret = E2_WriteData(u8TxBuf, 1u);
    JudgeResult(u8Ret);
    u8Ret = E2_Stop();
    JudgeResult(u8Ret);

    /* 5mS delay for e2prom*/
    DDL_Delay1ms(5ul);

    /* E2prom random read*/
    u8Ret = E2_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_W);
    JudgeResult(u8Ret);
    u8Ret = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(u8Ret);

    u8Ret = E2_StartOrRestart(GENERATE_RESTART);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_R);
    JudgeResult(u8Ret);
    u8Ret = E2_RevData(u8RxBuf, 1u);
    JudgeResult(u8Ret);
    u8Ret = E2_Stop();
    JudgeResult(u8Ret);

    /* Compare the data */
    if(0x01u != u8RxBuf[0])
    {
        /* e2prom byte write error*/
        while(1)
        {
            DDL_Delay1ms(500ul);
        }
    }

    /* 5mS delay for e2prom*/
    DDL_Delay1ms(5ul);
    /* E2prom page write*/
    u8Ret = E2_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_W);
    JudgeResult(u8Ret);
    u8Ret = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(u8Ret);
    u8Ret = E2_WriteData(u8TxBuf, PAGE_LEN);
    JudgeResult(u8Ret);
    u8Ret = E2_Stop();
    JudgeResult(u8Ret);

    /* 5mS delay for e2prom*/
    DDL_Delay1ms(5ul);

    /* E2prom sequential read*/
    u8Ret = E2_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_W);
    JudgeResult(u8Ret);
    u8Ret = E2_SendDataAdr(DATA_TEST_ADDR);
    JudgeResult(u8Ret);

    u8Ret = E2_StartOrRestart(GENERATE_RESTART);
    JudgeResult(u8Ret);
    u8Ret = E2_SendAdr((uint8_t)(E2_ADDRESS<<1u)|E2_ADDRESS_R);
    JudgeResult(u8Ret);
    u8Ret = E2_RevData(u8RxBuf, PAGE_LEN);
    JudgeResult(u8Ret);
    u8Ret = E2_Stop();
    JudgeResult(u8Ret);

    /* Compare the data */
    for(i=0ul; i<PAGE_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* e2prom page write error*/
            while(1)
            {
                DDL_Delay1ms(500ul);
            }
        }
    }

    /* e2prom sample success*/
    while(1)
    {
        DDL_Delay1ms(500ul);
    }
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
