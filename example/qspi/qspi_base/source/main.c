/**
 *******************************************************************************
 * @file  qspi/qspi_base/source/main.c
 * @brief Main program of QSPI base for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-10       wuze            First version
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
#include "w25q64.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup QSPI_BASE
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Pin definitions. */
#define QSPI_CS_PORT            (GPIO_PORT_C)
#define QSPI_CS_PIN             (GPIO_PIN_07)
#define QSPI_SCK_PORT           (GPIO_PORT_C)
#define QSPI_SCK_PIN            (GPIO_PIN_06)
#define QSPI_IO0_PORT           (GPIO_PORT_B)
#define QSPI_IO0_PIN            (GPIO_PIN_13)
#define QSPI_IO1_PORT           (GPIO_PORT_B)
#define QSPI_IO1_PIN            (GPIO_PIN_12)
#define QSPI_IO2_PORT           (GPIO_PORT_B)
#define QSPI_IO2_PIN            (GPIO_PIN_10)
#define QSPI_IO3_PORT           (GPIO_PORT_B)
#define QSPI_IO3_PIN            (GPIO_PIN_02)
#define QSPI_PIN_FUNC           (GPIO_FUNC_18_QSPI)

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         printf
#else
#define DBG(...)
#endif

/* Macro of word-to-byte. */
#define WORD_TO_BYTE(__word__, __au8__)                       \
        do {                                                  \
                (__au8__)[0U] = (uint8_t)(__word__);          \
                (__au8__)[1U] = (uint8_t)((__word__) >> 8U);  \
                (__au8__)[2U] = (uint8_t)((__word__) >> 16U); \
                (__au8__)[3U] = (uint8_t)((__word__) >> 24U); \
        } while (0U)

/* Data size definition for this example. */
#define APP_TEST_DATA_SIZE                  (1024UL * 4UL)

/* External QSPI flash address definition. */
#define APP_TEST_ADDRESS                    (1024UL * 4UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void QspiConfig(void);
static void QspiPinConfig(void);
static void QspiInitConfig(void);

void W25Q64_ReadUniqueID(uint8_t pu8ID[], uint32_t u32IDSize);
void W25Q64_WriteEnable(void);
void W25Q64_WriteDisable(void);

void W25Q64_EraseChip(void);
void W25Q64_EraseSector(uint32_t u32SectorAddress);
void W25Q64_EraseBlock(uint8_t u8EraseBlockInstr, uint32_t u32BlockAddress);

void W25Q64_WriteData(uint32_t u32Address, const uint8_t pu8WriteBuf[], uint32_t u32NumByteToWrite);
void W25Q64_ReadData(uint32_t u32Address, uint8_t pu8ReadBuf[], uint32_t u32NumByteToRead);
void W25Q64_ReadDataStd(uint32_t u32Address, uint8_t pu8ReadBuf[], uint32_t u32NumByteToRead);

void W25Q64_WriteCommand(uint8_t u8Instr, uint8_t pu8InstrData[], uint32_t u32InstrDataSize, uint32_t u32DummyBytes);
en_result_t W25Q64_CheckProcessDone(void);

void AppLoadData(void);
void AppClearData(void);
void AppCheckPageProgram(void);
void AppCheckErase(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
uint8_t m_au8WriteData[APP_TEST_DATA_SIZE];
uint8_t m_au8ReadData[APP_TEST_DATA_SIZE];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of qspi_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    DDL_UartInit();
    QspiConfig();
    LoadData();
    //while (1)
    {
        DBG("W25Q64 read unique ID......\n");
        W25Q64_ReadUniqueID(m_au8ReadData, W25Q64_UNIQUE_ID_SIZE);
        DBG("W25Q64 unique ID:\n");
        for (i = 0UL; i < W25Q64_UNIQUE_ID_SIZE; i++)
        {
            DBG("0x%.2x ", m_au8ReadData[i]);
        }
        DBG("\n");
        DDL_Delay1ms(100U);
        DBG("W25Q64 erase sector test......\n");
        ClearData();
        W25Q64_EraseSector(APP_TEST_ADDRESS);
        W25Q64_ReadData(APP_TEST_ADDRESS, m_au8ReadData, APP_TEST_DATA_SIZE);
        if (CheckErase(APP_TEST_DATA_SIZE))
        {
            DBG("W25Q64 erase sector test failed.\n");
        }
        else
        {
            DBG("W25Q64 erase sector test successfully.\n");
        }

        DDL_Delay1ms(100U);
        DBG("W25Q64 page program test......\n");
        ClearData();
        W25Q64_WriteData(APP_TEST_ADDRESS, m_au8WriteData, APP_TEST_DATA_SIZE);
        DDL_Delay1ms(10U);
        W25Q64_ReadData(APP_TEST_ADDRESS, m_au8ReadData, APP_TEST_DATA_SIZE);
        if (CheckPageProgram())
        {
            DBG("W25Q64 page program test failed.\n");
        }
        else
        {
            DBG("W25Q64 page program test successfully.\n");
        }

        ClearData();
        W25Q64_ReadDataStd(APP_TEST_ADDRESS, m_au8ReadData, APP_TEST_DATA_SIZE);
        if (CheckPageProgram())
        {
            DBG("STD read W25Q64 page program test failed.\n");
        }
        else
        {
            DBG("STD read W25Q64 page program test successfully.\n");
        }

        DDL_Delay1ms(100U);
    }
    while (1U);
}

static void QspiConfig(void)
{
    QspiPinConfig();
    QspiInitConfig();
}

static void QspiPinConfig(void)
{
    GPIO_SetFunc(QSPI_CS_PORT, QSPI_CS_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(QSPI_SCK_PORT, QSPI_SCK_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(QSPI_IO0_PORT, QSPI_IO0_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(QSPI_IO1_PORT, QSPI_IO1_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(QSPI_IO2_PORT, QSPI_IO2_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(QSPI_IO3_PORT, QSPI_IO3_PIN, \
                 QSPI_PIN_FUNC, PIN_SUBFUNC_DISABLE);
}

static void QspiInitConfig(void)
{
    stc_qspi_init_t stcInit;

    PWC_Fcg1PeriphClockCmd(PWC_FCG1_QSPI, Enable);
    QSPI_StructInit(&stcInit);

    stcInit.u32CSIdleTime      = QSPI_CS_IDLE_8_CYCLE;
    stcInit.u32CSExtendTime    = QSPI_CS_EXTEND_32_CYCLE;
    QSPI_Init(&stcInit);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_WriteCommand(uint8_t u8Instr, uint8_t pu8InstrData[], uint32_t u32InstrDataSize, uint32_t u32DummyBytes)
{
    uint32_t i;

    QSPI_EnterDirectCommMode();
    QSPI_WriteDirectCommValue(u8Instr);
    if ((pu8InstrData != NULL) && (u32InstrDataSize > 0U))
    {
        for (i=0UL; i<u32InstrDataSize; i++)
        {
            QSPI_WriteDirectCommValue(pu8InstrData[i]);
        }
    }
    if (u32DummyBytes > 0UL)
    {
        for (i=0UL; i<u32DummyBytes; i++)
        {
            QSPI_WriteDirectCommValue(W25Q64_DUMMY_BYTE_VALUE);
        }
    }
    QSPI_ExitDirectCommMode();
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
en_result_t W25Q64_CheckProcessDone(void)
{
    uint8_t u8Status = 0u;
    __IO uint32_t u32TimeCnt;
    stc_clk_freq_t stcClkFreq;
    en_result_t enRet = ErrorTimeout;

    CLK_GetClockFreq(&stcClkFreq);
    u32TimeCnt = stcClkFreq.sysclkFreq / 1000U;

    QSPI_EnterDirectCommMode();
    QSPI_WriteDirectCommValue(W25Q64_READ_STATUS_REGISTER_1);
    while (u32TimeCnt--)
    {
        u8Status = QSPI_ReadDirectCommValue();
        if ((u8Status & W25Q64_FLAG_BUSY) == 0U)
        {
            enRet = Ok;
            break;
        }
    }
    QSPI_ExitDirectCommMode();

    return enRet;
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_ReadUniqueID(uint8_t pu8ID[], uint32_t u32IDSize)
{
    stc_qspi_cmd_t stcCmd = {
        .u32ReadMode        = QSPI_READ_STANDARD_READ,
        .u32CommMode        = QSPI_COMM_DIRECT_COMM,
        .u32Instruction     = W25Q64_READ_UNIQUE_ID,
        .u32AddrWidth       = QSPI_ADDR_WIDTH_3_BYTE,
        .u32DummyCycles     = QSPI_DUMMY_CYCLE_4,
        .u32InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .u32AddrMode        = QSPI_ADDR_NONE,
        .u32DataMode        = QSPI_DATA_1_LINE,
        .u32CmdDummyBytes   = 4U,
    };
    QSPI_ReadData(&stcCmd, pu8ID, u32IDSize);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_WriteEnable(void)
{
    W25Q64_WriteCommand(W25Q64_WRITE_ENABLE, NULL, 0U, 0U);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_WriteDisable(void)
{
    W25Q64_WriteCommand(W25Q64_WRITE_DISABLE, NULL, 0U, 0U);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_EraseChip(void)
{
    W25Q64_WriteEnable();
    W25Q64_WriteCommand(W25Q64_CHIP_ERASE, NULL, 0U, 0U);
    W25Q64_CheckProcessDone();
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_EraseSector(uint32_t u32SectorAddress)
{
    uint8_t au8Address[4U];
    WORD_TO_BYTE(u32SectorAddress, au8Address);
    W25Q64_WriteEnable();
    W25Q64_WriteCommand(W25Q64_SECTOR_ERASE, au8Address, 3U, 0U);
    W25Q64_CheckProcessDone();
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_EraseBlock(uint8_t u8EraseBlockInstr, uint32_t u32BlockAddress)
{
    uint8_t au8Address[4U];
    WORD_TO_BYTE(u32BlockAddress, au8Address);
    W25Q64_WriteEnable();
    W25Q64_WriteCommand(u8EraseBlockInstr, au8Address, 3U, 0U);
    W25Q64_CheckProcessDone();
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_WriteData(uint32_t u32Address, const uint8_t pu8WriteBuf[], uint32_t u32NumByteToWrite)
{
    uint32_t u32TempSize;
    uint32_t u32AddrOfst = 0U;
    stc_qspi_cmd_t stcCmd = {
        .u32Instruction     = W25Q64_PAGE_PROGRAM,
        .u32Address         = u32Address,
        .u32AddrWidth       = QSPI_ADDR_WIDTH_3_BYTE,
        .u32CmdDummyBytes   = 0U,
    };

    while (u32NumByteToWrite)
    {
        if (u32NumByteToWrite >= W25Q64_PAGE_SIZE)
        {
            u32TempSize = W25Q64_PAGE_SIZE;
        }
        else
        {
            u32TempSize = u32NumByteToWrite;
        }

        DBG("Program address %.8lx\n", stcCmd.u32Address);
        W25Q64_WriteEnable();
        QSPI_WriteData(&stcCmd, (uint8_t *)&pu8WriteBuf[u32AddrOfst], u32TempSize);

        u32NumByteToWrite -= u32TempSize;
        u32AddrOfst += u32TempSize;
        stcCmd.u32Address += u32TempSize;
    }
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void W25Q64_ReadData(uint32_t u32Address, uint8_t pu8ReadBuf[], uint32_t u32NumByteToRead)
{
    stc_qspi_cmd_t stcCmd = {
        .u32ReadMode        = QSPI_READ_FAST_READ_DUAL_IO,
        .u32CommMode        = QSPI_COMM_ROM_ACCESS,
        .u32Instruction     = W25Q64_FAST_READ_DUAL_IO,
        .u32Address         = u32Address,
        .u32AddrWidth       = QSPI_ADDR_WIDTH_3_BYTE,
        .u32DummyCycles     = QSPI_DUMMY_CYCLE_4,
        .u32InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .u32AddrMode        = QSPI_ADDR_1_LINE,
        .u32DataMode        = QSPI_DATA_1_LINE,
        .u32CmdDummyBytes   = 0U,
    };

    QSPI_ReadData(&stcCmd, pu8ReadBuf, u32NumByteToRead);
}

void W25Q64_ReadDataStd(uint32_t u32Address, uint8_t pu8ReadBuf[], uint32_t u32NumByteToRead)
{
    stc_qspi_cmd_t stcCmd = {
        .u32ReadMode        = QSPI_READ_STANDARD_READ,
        .u32CommMode        = QSPI_COMM_DIRECT_COMM,
        .u32Instruction     = W25Q64_READ_DATA,
        .u32Address         = u32Address,
        .u32AddrWidth       = QSPI_ADDR_WIDTH_3_BYTE,
        .u32DummyCycles     = QSPI_DUMMY_CYCLE_6,
        .u32InstructionMode = QSPI_INSTRUCTION_1_LINE,
        .u32AddrMode        = QSPI_ADDR_1_LINE,
        .u32DataMode        = QSPI_DATA_1_LINE,
        .u32CmdDummyBytes   = 0U,
    };

    QSPI_ReadData(&stcCmd, pu8ReadBuf, u32NumByteToRead);
}


void AppLoadData(void)
{
    uint32_t i;
    for (i=0UL; i<APP_TEST_DATA_SIZE; i++)
    {
        m_au8WriteData[i] = (uint8_t)(i % 256);
    }
}

void AppClearData(void)
{
    uint32_t i;
    for (i=0UL; i<APP_TEST_DATA_SIZE; i++)
    {
        m_au8ReadData[i] = 0U;
    }
}

uint8_t AppCheckPageProgram(void)
{
    uint32_t i;
    for (i=0UL; i<APP_TEST_DATA_SIZE; i++)
    {
        if (m_au8ReadData[i] != m_au8WriteData[i])
        {
            return 1U;
        }
    }

    return 0U;
}

uint8_t AppCheckErase(uint32_t u32Szie)
{
    uint32_t i;
    for (i=0UL; i<u32Szie; i++)
    {
        if (m_au8ReadData[i] != 0xFFU)
        {
            return 1U;
        }
    }

    return 0U;
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
