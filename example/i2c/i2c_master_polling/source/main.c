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
#define I2C_SCL_PORT                    (GPIO_PORT_C)
#define I2C_SCL_PIN                     (GPIO_PIN_04)
#define I2C_SDA_PORT                    (GPIO_PORT_C)
#define I2C_SDA_PIN                     (GPIO_PIN_05)

#define TIMEOUT                         ((uint32_t)0x10000)

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

/* Define for RGB LED */
#define LED_R_PORT                      (GPIO_PORT_A)
#define LED_G_PORT                      (GPIO_PORT_B)
#define LED_B_PORT                      (GPIO_PORT_C)
#define LED_R_PIN                       (GPIO_PIN_00)
#define LED_G_PIN                       (GPIO_PIN_00)
#define LED_B_PIN                       (GPIO_PIN_01)
#define LED_G_TOGGLE()                  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))
#define LED_R_TOGGLE()                  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))



/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static uint8_t Master_StartOrRestart(uint8_t u8Start);
static uint8_t Master_SendAdr(uint8_t u8Adr);
static uint8_t Master_WriteData(uint8_t const pTxData[], uint32_t u32Size);
static uint8_t Master_RevData(uint8_t pRxData[], uint32_t u32Size);
uint8_t Master_Stop(void);
uint8_t Master_Initialize(void);
static void JudgeResult(uint8_t u8Result);
static void SystemClockConfig(void);
static void LedConfig(void);
static void WaitSwX_ShortPress(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
uint8_t u8TxBuf[TEST_DATA_LEN];
uint8_t u8RxBuf[TEST_DATA_LEN];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of i2c_at24c02 project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{

    uint32_t i;
    uint8_t u8Ret = I2C_RET_OK;

    /* Configure system clock. */
    SystemClockConfig();

    /* Test buffer initialize */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8TxBuf[i] = (uint8_t)(i+1U);
    }
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8RxBuf[i] = 0U;
    }

    /* Initialize I2C port*/
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_FUNC_51_I2C1_SCL, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_FUNC_50_I2C1_SDA, PIN_SUBFUNC_DISABLE);

    /* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_IIC1, Enable);

    /* Initialize I2C peripheral and enable function*/
    Master_Initialize();

    /*TODO: Short press key SWX */
    WaitSwX_ShortPress();

    /* RGB LED configuration */
    LedConfig();

    /* I2C master data write*/
    u8Ret = Master_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1U)|ADDRESS_W);
    JudgeResult(u8Ret);
    u8Ret = Master_WriteData(u8TxBuf, TEST_DATA_LEN);
    JudgeResult(u8Ret);
    u8Ret = Master_Stop();
    JudgeResult(u8Ret);

    /* 5mS delay for device*/
    DDL_Delay1ms(1U);

    /* I2C master data read*/
    u8Ret = Master_StartOrRestart(GENERATE_START);
    JudgeResult(u8Ret);
    u8Ret = Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1U)|ADDRESS_R);
    JudgeResult(u8Ret);
    u8Ret = Master_RevData(u8RxBuf, TEST_DATA_LEN);
    JudgeResult(u8Ret);
    u8Ret = Master_Stop();
    JudgeResult(u8Ret);

    /* Compare the data */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* Data write error*/
            while(1)
            {
                LED_R_TOGGLE();
                DDL_Delay1ms(500U);
            }
        }
    }

    /* I2C master polling comunication success */
    while(1)
    {
        LED_G_TOGGLE();
        DDL_Delay1ms(500U);
    }

}

/**
 * @brief  Wait SWX key short press.
 * @param  None
 * @retval None
 */
static void WaitSwX_ShortPress(void)
{

}

/**
 * @brief   Send start or restart condition
 * @param   [in]  u8Start  Indicate the start mode, start or restart
 * @retval  Process result
 *          - I2C_RET_ERROR  Send start or restart failed
 *          - I2C_RET_OK     Send start or restart success
 */
static uint8_t Master_StartOrRestart(uint8_t u8Start)
{
    uint32_t u32TimeOut = TIMEOUT;
    en_flag_status_t enBusyFlag, enStartFlag;
    uint8_t u8Ret = I2C_RET_OK;

    /* generate start or restart signal */
    if(GENERATE_START == u8Start)
    {
        I2C_GenerateStart(M4_I2C1);
    }
    else
    {
        /* Clear start status flag */
        I2C_ClearStatus(M4_I2C1, I2C_CLR_STARTFCLR);
        /* Send restart condition */
        I2C_GenerateReStart(M4_I2C1);
    }

    /* Judge if start success*/
    //while((Reset == I2C_GetStatus(M4_I2C1, I2C_SR_BUSY)) ||
    //        (Reset == I2C_GetStatus(M4_I2C1, I2C_SR_STARTF)))  /* MISRAC 2004*/
    while(1)
    {
        enBusyFlag = I2C_GetStatus(M4_I2C1, I2C_SR_BUSY);
        enStartFlag = I2C_GetStatus(M4_I2C1, I2C_SR_STARTF);
        u32TimeOut--;
        if(((Set == enBusyFlag) && (Set == enStartFlag))||(0U == u32TimeOut))
        {
            break;
        }
    }
    if(0U == u32TimeOut)
    {
        u8Ret = I2C_RET_ERROR;
    }

    return u8Ret;
}
/**
 * @brief   Wait status
 * @param   [in]  u32SRFlag  The slave address
 * @retval  Process result
 *          - I2C_RET_ERROR  Status of flag wait fail
 *          - I2C_RET_OK     Status of flag wait success
 */
static uint8_t Wait_Status(uint32_t u32SRFlag,en_flag_status_t enStatus)
{
    uint8_t u8Ret = I2C_RET_OK;
    uint32_t u32TimeOut = TIMEOUT;

    while(enStatus == I2C_GetStatus(M4_I2C1, u32SRFlag))
    {
        if(0U == (u32TimeOut--))
        {
            u8Ret = I2C_RET_ERROR;
        }
    }
    return u8Ret;
}

/**
 * @brief   Send slave address
 * @param   [in]  u8Adr  The slave address
 * @retval  Process result
 *          - I2C_RET_ERROR  Send failed
 *          - I2C_RET_OK     Send success
 */
static uint8_t Master_SendAdr(uint8_t u8Adr)
{
    uint32_t u32TimeOut = TIMEOUT;
    uint8_t u8Ret = I2C_RET_OK;

    do
    {
        /* Wait tx buffer empty */
        u8Ret = Wait_Status(I2C_SR_TEMPTYF,Reset);
        if(u8Ret == I2C_RET_ERROR)
        {
            break;
        }
        /* Send I2C address */
        I2C_SendData(M4_I2C1, u8Adr);
        if(ADDRESS_W == (u8Adr & 0x01U))
        {
            /* If in master transfer process, Need wait transfer end*/
            u8Ret = Wait_Status(I2C_SR_TENDF,Reset);
        }
        /* Check ACK */
        if(u8Ret == I2C_RET_OK)
        {
            u8Ret = Wait_Status(I2C_SR_ACKRF,Set);
        }
    }while(0);

    return u8Ret;
}

/**
 * @brief   Send data to slave
 * @param   [in]  pTxData  Pointer to the data buffer
 * @param   [in]  u32Size  Data size
 * @retval  Process result
 *          - I2C_RET_ERROR  Send failed
 *          - I2C_RET_OK     Send success
 */
static uint8_t Master_WriteData(uint8_t const pTxData[], uint32_t u32Size)
{
    uint32_t u32TimeOut = TIMEOUT;
    uint8_t u8Ret = I2C_RET_OK;
    uint32_t u32TxDataAdr = (uint32_t)pTxData;
    uint32_t i = 0U;
    while(u32Size--)
    {
        if(u8Ret == I2C_RET_ERROR)
        {
            break;
        }
        /* Wait tx buffer empty */
        u8Ret = Wait_Status(I2C_SR_TEMPTYF,Reset);
        if(I2C_RET_OK == u8Ret)
        {
            /* Send one byte data */
            I2C_SendData(M4_I2C1, pTxData[i]);
            /* Wait transfer end*/
            u8Ret = Wait_Status(I2C_SR_TENDF,Reset);
            if(I2C_RET_OK == u8Ret)
            {
                /* Check ACK */
                u8Ret = Wait_Status(I2C_SR_ACKRF,Set);
            }
        }
    }
    return u8Ret;
}

/**
 * @brief   Write address and receive data from slave
 * @param   [in]  pRxData  Pointer to the data buffer
 * @param   [in]  u32Size  Data size
 * @retval  Process result
 *          - I2C_RET_ERROR  Process failed
 *          - I2C_RET_OK     Process success
 */
static uint8_t Master_RevData(uint8_t pRxData[], uint32_t u32Size)
{
    uint32_t u32TimeOut = TIMEOUT;
    uint8_t u8Ret = I2C_RET_OK;
    uint32_t u32RxDataAdr = (uint32_t)pRxData;

    for(uint32_t i=0U; i<u32Size; i++)
    {
        if(u8Ret == I2C_RET_ERROR)
        {
            break;
        }
        /* if the last byte receive, need config NACK*/
        if(i == (u32Size - 1U))
        {
            I2C_NackConfig(M4_I2C1, Enable);
        }

        /* Wait receive full flag*/
        u32TimeOut = TIMEOUT;
        while(Reset == I2C_GetStatus(M4_I2C1, I2C_SR_RFULLF))
        {
            if(0U == (u32TimeOut--))
            {
                u8Ret = I2C_RET_ERROR;
            }
        }

        /* read data from register*/
       pRxData[i] = I2C_ReadData(M4_I2C1);
    }
    return I2C_RET_OK;
}

/**
 * @brief   General stop condition to slave
 * @param   None
 * @retval  Process result
 *          - I2C_RET_ERROR  Process failed
 *          - I2C_RET_OK     Process success
 */
uint8_t Master_Stop(void)
{
    uint32_t u32TimeOut;
    uint8_t u8Ret = I2C_RET_OK;
    /* Clear stop flag */
    while(Set == I2C_GetStatus(M4_I2C1, I2C_SR_STOPF))
    {
        I2C_ClearStatus(M4_I2C1, I2C_CLR_STOPFCLR);
    }

    I2C_GenerateStop(M4_I2C1);

    /* Wait STOPF */
    u32TimeOut = TIMEOUT;
    while(Reset == I2C_GetStatus(M4_I2C1, I2C_SR_STOPF))
    {
        if(0U == (u32TimeOut--))
        {
            u8Ret = I2C_RET_ERROR;
        }
    }
    return u8Ret;
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
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXTALInit;

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;

    /* Initialize XTAL clock */
    CLK_XtalInit(&stcXTALInit);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_XTAL);
}

/**
 * @brief   Judge the result. LED0 toggle when result is error status.
 * @param   [in]  u8Result    Result to be judged
 * @retval  None
 */
static void JudgeResult(uint8_t u8Result)
{
    if(I2C_RET_ERROR == u8Result)
    {
        while(1)
        {
            LED_R_TOGGLE();
            DDL_Delay1ms(500U);
        }
    }
}

/**
 * @brief  Configure RGB LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit = {0U};

    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
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
