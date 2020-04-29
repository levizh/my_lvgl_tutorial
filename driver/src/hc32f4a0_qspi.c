/**
 *******************************************************************************
 * @file  hc32f4a0_qspi.c
 * @brief This file provides firmware functions to manage the QSPI.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-10       Wuze            First version
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
#include "hc32f4a0_qspi.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_QSPI QSPI
 * @brief QSPI Driver Library
 * @{
 */

#if (DDL_QSPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup QSPI_Local_Macros QSPI Local Macros
 * @{
 */

/**
 * @defgroup QSPI_Configuration_Bit_Mask QSPI Configuration Bit Mask
 * @{
 */
#define QSPI_FLAG_CLR_MSK                   (QSPI_FLAG_ROM_ACCESS_ERR)
#define QSPI_FLAG_GET_MSK                   (QSPI_FLAG_DIRECT_COMM_BUSY | \
                                             QSPI_FLAG_XIP_MODE | \
                                             QSPI_FLAG_ROM_ACCESS_ERR | \
                                             QSPI_FLAG_PREFETCH_BUF_FULL | \
                                             QSPI_FLAG_PREFETCH_ACTIVE)
/**
 * @}
 */

/**
 * @defgroup QSPI_Common_Instruction QSPI Common Instruction
 * @{
 */
#define QSPI_INS_ENTER_4BA                  (0xB7U)
#define QSPI_INS_EXIT_4BA                   (0xE9U)
/**
 * @}
 */

/**
 * @defgroup QSPI_Check_Parameters_Validity QSPI check parameters validity
 * @{
 */


/**
 * @}
 */

/**
 * @defgroup QSPI_Miscellaneous_Macros QSPI Miscellaneous Macros
 * @{
 */
#define QSPI_WORD_2_BYTE(__word__, __au8__)                   \
        do {                                                  \
                (__au8__)[0U] = (uint8_t)(__word__);          \
                (__au8__)[1U] = (uint8_t)((__word__) >> 8U);  \
                (__au8__)[2U] = (uint8_t)((__word__) >> 16U); \
                (__au8__)[3U] = (uint8_t)((__word__) >> 24U); \
        } while (0U)

#define QSPI_ROM_MAP_BASE                   (0x98000000UL)

/**
 * @}
 */

/**
 * @}
 */

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
 * @defgroup QSPI_Global_Functions QSPI Global Functions
 * @{
 */

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
en_result_t QSPI_Init(const stc_qspi_init_t *pstcInit)
{
    uint32_t u32DutyCorrection = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        if ((pstcInit->u32ClkDiv != 0U) && (pstcInit->u32ClkDiv & QSPI_CR_DIV_0) == 0U)
        {
            u32DutyCorrection = QSPI_FCR_DUTY;
        }

        WRITE_REG32(M4_QSPI->CR, (pstcInit->u32ClkDiv  | \
                                  pstcInit->u32SPIMode | \
                                  pstcInit->u32PrefetchStopPos));

        WRITE_REG32(M4_QSPI->CSCR, (pstcInit->u32CSExtendTime | \
                                    pstcInit->u32CSIdleTime));

        WRITE_REG32(M4_QSPI->FCR, (pstcInit->u32CSSetupTiming   | \
                                   pstcInit->u32CSReleaseTiming | \
                                   QSPI_WRITE_PROTECT_DISABLE   | \
                                   u32DutyCorrection));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
en_result_t QSPI_StructInit(stc_qspi_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u32ClkDiv          = QSPI_CLK_DIV_8;
        pstcInit->u32CSSetupTiming   = QSPI_CS_SETUP_BEFORE_0P5_CYCLE;
        pstcInit->u32CSReleaseTiming = QSPI_CS_RELEASE_AFTER_0P5_CYCLE;
        pstcInit->u32CSIdleTime      = QSPI_CS_IDLE_4_CYCLE;
        pstcInit->u32CSExtendTime    = QSPI_CS_EXTEND_0_CYCLE;
        pstcInit->u32SPIMode         = QSPI_SPI_MODE_0;
        pstcInit->u32PrefetchStopPos = QSPI_PREFETCH_STOP_BYTE_EDGE;

        enRet = Ok;
    }

    return enRet;
}


en_result_t QSPI_Write(const stc_qspi_cmd_t *pstcCmd, const uint8_t pu8Src[], uint32_t u32Length)
{
    uint32_t i;
    uint32_t u32AddrWidth;
    en_result_t enRet = ErrorInvalidParameter;

    if ((pstcCmd != NULL))
    {
        u32AddrWidth = (pstcCmd->u32AddrWidth >> QSPI_FCR_AWSL_POS) + 1UL;

        CLEAR_REG32_BIT(M4_QSPI->CR, (QSPI_CR_MDSEL | QSPI_CR_DCOME | QSPI_CR_IPRSL | QSPI_CR_APRSL | QSPI_CR_DPRSL));
        MODIFY_REG32(M4_QSPI->FCR, QSPI_FCR_AWSL, pstcCmd->u32AddrWidth);

        /* Enter direct communication mode. */
        SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
        /* Send instruction. */
        WRITE_REG32(M4_QSPI->DCOM, pstcCmd->u32Instruction);

        /* Dummy bytes follows behind the instruction which has been sent. */
        for (i=0U; i<pstcCmd->u32CmdDummyBytes; i++)
        {
            WRITE_REG32(M4_QSPI->DCOM, 0xFFUL);
        }

        /* Write data at last. */
        for (i=0U; i<u32Length; i++)
        {
            WRITE_REG32(M4_QSPI->DCOM, pu8Src[i]);
        }
        /* Exit direct communication mode. */
        CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);

        enRet = Ok;
    }

    return enRet;
}


en_result_t QSPI_WriteData(const stc_qspi_cmd_t *pstcCmd, const uint8_t pu8Src[], uint32_t u32Length)
{
    uint32_t i;
    uint8_t au8Address[4U];
    uint32_t u32AddrWidth;
    en_result_t enRet = ErrorInvalidParameter;

    if ((pstcCmd != NULL) && (pu8Src != NULL))
    {
        QSPI_WORD_2_BYTE(pstcCmd->u32Address, au8Address);
        u32AddrWidth = (pstcCmd->u32AddrWidth >> QSPI_FCR_AWSL_POS) + 1UL;

        CLEAR_REG32_BIT(M4_QSPI->CR, (QSPI_CR_MDSEL | QSPI_CR_DCOME | QSPI_CR_IPRSL | QSPI_CR_APRSL | QSPI_CR_DPRSL));
        MODIFY_REG32(M4_QSPI->FCR, QSPI_FCR_AWSL, pstcCmd->u32AddrWidth);

        /* Enter direct communication mode. */
        SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
        /* Send instruction. */
        WRITE_REG32(M4_QSPI->DCOM, pstcCmd->u32Instruction);
        /* Send ROM address. */
        for (i=0U; i<u32AddrWidth; i++)
        {
            WRITE_REG32(M4_QSPI->DCOM, au8Address[i]);
        }
        /* Dummy bytes follows behind the instruction which has been sent. */
        for (i=0U; i<pstcCmd->u32CmdDummyBytes; i++)
        {
            WRITE_REG32(M4_QSPI->DCOM, 0xFFUL);
        }
        /* Write data at last. */
        for (i=0U; i<u32Length; i++)
        {
            WRITE_REG32(M4_QSPI->DCOM, pu8Src[i]);
        }
        /* Exit direct communication mode. */
        CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);

        enRet = Ok;
    }

    return enRet;
}

en_result_t QSPI_ReadData(const stc_qspi_cmd_t *pstcCmd, uint8_t pu8Dest[], uint32_t u32Length)
{
    uint8_t au8Address[4U];
    uint32_t u32AddrWidth;
    uint32_t u32Address;
    uint32_t i;
    uint32_t u32InstructionMode = pstcCmd->u32InstructionMode;
    uint32_t u32AddrMode = pstcCmd->u32AddrMode;
    uint32_t u32DataMode = pstcCmd->u32DataMode;
    en_result_t enRet = ErrorInvalidParameter;

    if ((pstcCmd != NULL) && (pu8Dest != NULL))
    {
        if (u32InstructionMode == QSPI_INSTRUCTION_NONE)
        {
            u32InstructionMode = QSPI_INSTRUCTION_1_LINE;
        }
        if (u32AddrMode == QSPI_ADDR_NONE)
        {
            u32AddrMode = QSPI_ADDR_1_LINE;
        }
        if (u32DataMode == QSPI_DATA_NONE)
        {
            u32DataMode = QSPI_DATA_1_LINE;
        }

        MODIFY_REG32(M4_QSPI->CR, \
                     (QSPI_CR_MDSEL | QSPI_CR_DCOME | QSPI_CR_IPRSL | QSPI_CR_APRSL | QSPI_CR_DPRSL), \
                     (pstcCmd->u32ReadMode | pstcCmd->u32CommMode | u32InstructionMode | u32AddrMode | u32DataMode));
        MODIFY_REG32(M4_QSPI->FCR, \
                     (QSPI_FCR_DMCYCN | QSPI_FCR_AWSL), \
                     (pstcCmd->u32DummyCycles | pstcCmd->u32AddrWidth));

        QSPI_WORD_2_BYTE(pstcCmd->u32Address, au8Address);
        u32AddrWidth = (pstcCmd->u32AddrWidth >> QSPI_FCR_AWSL_POS) + 1UL;

        if (pstcCmd->u32CommMode == QSPI_COMM_DIRECT_COMM)
        {
            /* Enter direct communication mode. */
            SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
            /* Send instruction. */
            if (pstcCmd->u32InstructionMode != QSPI_INSTRUCTION_NONE)
            {
                WRITE_REG32(M4_QSPI->DCOM, pstcCmd->u32Instruction);
            }
            /* Send address if needed. */
            if (pstcCmd->u32AddrMode != QSPI_ADDR_NONE)
            {
                for (i=0U; i<u32AddrWidth; i++)
                {
                    WRITE_REG32(M4_QSPI->DCOM, au8Address[i]);
                }
            }
            /* Dummy bytes follows behind the instruction that has been sent. */
            for (i=0U; i<pstcCmd->u32CmdDummyBytes; i++)
            {
                WRITE_REG32(M4_QSPI->DCOM, 0xFFUL);
            }

            /* Read data at last. */
            for (i=0U; i<u32Length; i++)
            {
                pu8Dest[i] = (uint8_t)M4_QSPI->DCOM;
            }
            /* Exit direct communication mode. */
            CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
        }
        else
        {
            /* Send instruction. */
            if (pstcCmd->u32InstructionMode != QSPI_INSTRUCTION_NONE)
            {
                WRITE_REG32(M4_QSPI->CCMD, pstcCmd->u32Instruction);
            }
            u32Address = QSPI_ROM_MAP_BASE + pstcCmd->u32Address;
            for (i=0U; i<u32Length; i++)
            {
                pu8Dest[i] = *(uint8_t *)(u32Address + i);
            }
        }

        enRet = Ok;
    }

    return enRet;
}

void QSPI_EnterDirectCommMode(void)
{
    SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

void QSPI_ExitDirectCommMode(void)
{
    CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

void QSPI_WriteDirectCommValue(uint8_t u8Val)
{
    WRITE_REG32(M4_QSPI->DCOM, u8Val);
}

uint8_t QSPI_ReadDirectCommValue(void)
{
    return (uint8_t)M4_QSPI->DCOM;
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void QSPI_DutyCorrectionCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_DUTY);
    }
    else
    {
        CLEAR_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_DUTY);
    }
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void QSPI_PrefetchCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_PFE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_PFE);
    }
}

/**
 * @brief  Enable or disable XIP mode.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable XIP mode.
 *   @arg Disable:                      Disable XIP mode.
 * @retval None
 */
void QSPI_XIPModeCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_XIPE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_XIPE);
    }
}

/**
 * @brief  Enable or disable write protect.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable write protect.
 *   @arg Disable:                      Disable write protect.
 * @retval None
 */
void WriteProtectCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        CLEAR_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_WPOL);
    }
    else
    {
        SET_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_WPOL);
    }
}

/**
 * @brief  Enable or disable 4-byte address mode.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable 4-byte address mode.
 *   @arg Disable:                      Disable 4-byte address mode.
 * @retval None
 */
void QSPI_4ByteAddrModeCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_FOUR_BIC);
    }
    else
    {
        CLEAR_REG32_BIT(M4_QSPI->FCR, QSPI_FCR_FOUR_BIC);
    }
}

/**
 * @brief  Selects the block to access.
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void QSPI_SelectBlock(uint32_t u32Block)
{

}

/**
 * @brief  //TODO:QSSR
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
uint32_t QSPI_GetPrefetchedSize(void)
{
    return ((M4_QSPI->SR & QSPI_SR_PFNUM) >> QSPI_SR_PFNUM_POS);
}

/**
 * @brief  Get the status of the specified QSPI flag.
 * @param  [in]  u32Flag                //TODO:
 * @retval None
 */
en_flag_status_t QSPI_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlag = Reset;

    u32Flag &= QSPI_FLAG_GET_MSK;
    if ((M4_QSPI->SR & u32Flag) != 0U)
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  
 * @param  [in]  u32Flag                //TODO:
 *   @arg  QSPI_FLAG_RA_EER
 * @retval None
 */
void QSPI_ClrStatus(uint32_t u32Flag)
{
    u32Flag &= QSPI_FLAG_CLR_MSK;
    M4_QSPI->SR2 |= u32Flag;
}

/**
 * @}
 */

#endif /* DDL_QSPI_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
