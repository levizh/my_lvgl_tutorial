/**
 *******************************************************************************
 * @file  hc32f4a0_exmc_smc.h
 * @brief This file contains all the functions prototypes of the EXMC SMC
 *        (External Memory Controller: Static Memory Controller) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-09       Hongjh          First version
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
#ifndef __HC32F4A0_EXMC_SMC_H__
#define __HC32F4A0_EXMC_SMC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_EXMC_SMC
 * @{
 */

#if (DDL_SMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Global_Types Static Memory Controller Global Types
 * @{
 */

/**
 * @brief  EXMC SMC Chip Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32ReadMode;        /*!< Defines the read sync enable.
                                         This parameter can be a value of @ref EXMC_SMC_Memory_Read_Mode */

    uint32_t    u32WriteMode;       /*!< Defines the write sync enable.
                                         This parameter can be a value of @ref EXMC_SMC_Memory_Write_Mode */

    uint32_t    u32ReadBurstLen;    /*!< Defines the number of read data access.
                                         This parameter can be a value of @ref EXMC_SMC_Memory_Read_Burst_Length. */

    uint32_t    u32WriteBurstLen;   /*!< Defines the number of write data access.
                                         This parameter can be a value of @ref EXMC_SMC_Memory_Write_Burst_Length. */

    uint32_t    u32SmcMemWidth;     /*!< Defines the SMC memory width.
                                         This parameter can be a value of @ref EXMC_SMC_Memory_Width. */

    uint32_t    u32BAA;             /*!< Defines the SMC BAA signal enable.
                                         This parameter can be a value of @ref EXMC_SMC_BAA_Port_Selecton. */

    uint32_t    u32ADV;             /*!< Defines the SMC ADVS signal enable.
                                         This parameter can be a value of @ref EXMC_SMC_ADVS_Port_Selecton. */

    uint32_t    u32BLS;             /*!< Defines the SMC BLS signal selection.
                                         This parameter can be a value of @ref EXMC_SMC_BLS_Synchronization_Selection. */

    uint32_t    u32AddressMask;     /*!< Defines the address mask.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32AddressMatch;    /*!< Defines the address match.
                                         This parameter can be a value between Min_Data = 0x60 and Max_Data = 0x7F */
}stc_exmc_smc_chip_cfg_t;

/**
 * @brief  EXMC SMC Timing Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32RC;      /*!< Defines the RC in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */

    uint32_t    u32WC;      /*!< Defines the WC in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */

    uint32_t    u32CEOE;    /*!< Defines the CEOE in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    u32WP;      /*!< Defines the WP in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    u32PC;      /*!< Defines the PC in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    u32TR;      /*!< Defines the TR in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
} stc_exmc_smc_timing_cfg_t;

/**
 * @brief  EXMC SMC Initialization Structure definition 
 */
typedef struct
{
    stc_exmc_smc_chip_cfg_t     stcChipCfg;         /*!< SMC memory chip configure.
                                                         This structure details refer @ref stc_exmc_smc_chip_cfg_t.    */

    stc_exmc_smc_timing_cfg_t   stcTimingCfg;       /*!< SMC memory timing configure.
                                                         This structure details refer @ref stc_exmc_smc_timing_cfg_t.    */
} stc_exmc_smc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Global_Macros Static Memory Controller Global Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Chip EXMC SMC Chip
 * @{
 */
#define EXMC_SMC_CHIP_0                         ((uint32_t)0UL)     /*!< Chip 0 */
#define EXMC_SMC_CHIP_1                         ((uint32_t)1UL)     /*!< Chip 1 */
#define EXMC_SMC_CHIP_2                         ((uint32_t)2UL)     /*!< Chip 2 */
#define EXMC_SMC_CHIP_3                         ((uint32_t)3UL)     /*!< Chip 3 */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Read_Mode EXMC SMC Memory Read Mode
 * @{
 */
#define EXMC_SMC_MEM_READ_ASYNC                 ((uint32_t)0UL)
#define EXMC_SMC_MEM_READ_SYNC                  (SMC_CPCR_RSYN)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Write_Mode EXMC SMC Memory Write Mode
 * @{
 */
#define EXMC_SMC_MEM_WRITE_ASYNC                ((uint32_t)0UL)
#define EXMC_SMC_MEM_WRITE_SYNC                 (SMC_CPCR_WSYN)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Read_Burst_Length EXMC SMC Memory Read Burst Length
 * @{
 */
#define EXMC_SMC_MEM_READ_BURST_1               ((uint32_t)0UL)         /*!< 1 beat */
#define EXMC_SMC_MEM_READ_BURST_4               (SMC_CPCR_RBL_0)        /*!< 4 beats */
#define EXMC_SMC_MEM_READ_BURST_8               (SMC_CPCR_RBL_1)        /*!< 8 beats */
#define EXMC_SMC_MEM_READ_BURST_16              (SMC_CPCR_RBL_1 | \
                                                 SMC_CPCR_RBL_0)        /*!< 16 beats */
#define EXMC_SMC_MEM_READ_BURST_32              (SMC_CPCR_RBL_2)        /*!< 32 beats */
#define EXMC_SMC_MEM_READ_BURST_CONTINUOUS      (SMC_CPCR_RBL_2 | \
                                                 SMC_CPCR_RBL_0)        /*!< continuous */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Write_Burst_Length EXMC SMC Memory Write Burst Length
 * @{
 */
#define EXMC_SMC_MEM_WRITE_BURST_1              ((uint32_t)0UL)         /*!< 1 beat */
#define EXMC_SMC_MEM_WRITE_BURST_4              (SMC_CPCR_WBL_0)        /*!< 4 beats */
#define EXMC_SMC_MEM_WRITE_BURST_8              (SMC_CPCR_WBL_1)        /*!< 8 beats */
#define EXMC_SMC_MEM_WRITE_BURST_16             (SMC_CPCR_WBL_1 | \
                                                 SMC_CPCR_WBL_0)        /*!< 16 beats */
#define EXMC_SMC_MEM_WRITE_BURST_32             (SMC_CPCR_WBL_2)        /*!< 32 beats */
#define EXMC_SMC_MEM_WRITE_BURST_CONTINUOUS     (SMC_CPCR_WBL_2 | \
                                                 SMC_CPCR_WBL_0)        /*!< continuous */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Width EXMC SMC Memory Width
 * @{
 */
#define EXMC_SMC_MEM_WIDTH_16                   (SMC_CPCR_MW_0)
#define EXMC_SMC_MEM_WIDTH_32                   (SMC_CPCR_MW_1)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_BAA_Port_Selecton EXMC SMC BAA Port Selecton
 * @{
 */
#define EXMC_SMC_BAA_PORT_DISABLE               ((uint32_t)0UL)
#define EXMC_SMC_BAA_PORT_ENABLE                (SMC_CPCR_BAAS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_ADV_Port_Selecton EXMC SMC ADV Port Selecton
 * @{
 */
#define EXMC_SMC_ADV_PORT_DISABLE               ((uint32_t)0UL)
#define EXMC_SMC_ADV_PORT_ENABLE                (SMC_CPCR_ADVS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_BLS_Synchronization_Selection EXMC SMC BLS Synchronization Selection
 * @{
 */
#define EXMC_SMC_BLS_SYNC_CS                    ((uint32_t)0UL)
#define EXMC_SMC_BLS_SYNC_WE                    (SMC_CPCR_BLSS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Command EXMC SMC Command
 * @{
 */
#define EXMC_SMC_CMD_MDREGCONFIG                (SMC_CMDR_CMD_0)    /*!< Command: MdRetConfig */
#define EXMC_SMC_CMD_UPDATEREGS                 (SMC_CMDR_CMD_1)    /*!< Command: UpdateRegs */
#define EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS (SMC_CMDR_CMD)      /*!< Command: MdRetConfig & UpdateRegs */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_CRE_Polarity EXMC SMC CRE Polarity
 * @{
 */
#define EXMC_SMC_CRE_POLARITY_LOW               ((uint32_t)0UL)     /*!< CRE is LOW */
#define EXMC_SMC_CRE_POLARITY_HIGH              (SMC_CMDR_CRES)     /*!< CRE is HIGH when ModeReg write occurs */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Status EXMC SMC Status
 * @{
 */
#define EXMC_SMC_READY                          ((uint32_t)0UL)     /*!< SMC is ready */
#define EXMC_SMC_LOWPOWER                       (SMC_STSR_STATUS)   /*!< SMC is low power */
/**
 * @}
 */

/**
  * @brief  SMC device memory address shifting.
  * @param  [in] mem_base_address       SMC base address
  * @param  [in] mem_width              SMC memory width
  * @param  address                     SMC device memory address
  * @retval SMC device shifted address value
  */
#define SMC_ADDR_SHIFT(mem_base_address, mem_width, address)                  \
(    ((EXMC_SMC_MEM_WIDTH_16 == (mem_width))? (((mem_base_address) + ((address) << 1UL))):\
                                               (((mem_base_address) + ((address) << 2UL)))))

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EXMC_EXMC_Global_Functions Static Memory Controller Global Functions
 * @{
 */

/**
 * @brief  Enable SMC.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_Enable(void)
{
    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.SMCEN, 1UL);
}

/**
 * @brief  Disable SMC.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_Disable(void)
{
    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.SMCEN, 0UL);
}

/**
 * @brief  SMC entry low power state
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_EntryLowPower(void)
{
    WRITE_REG32(M4_SMC->STCR0, SMC_STCR0_LPWIR);
}

/**
 * @brief  SMC exit low power state
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_ExitLowPower(void)
{
    WRITE_REG32(M4_SMC->STCR1, SMC_STCR1_LPWOR);
}

/**
 * @brief  Get SMC status
 * @param  None
 * @retval Returned value can be one of the following values:
 *           @arg EXMC_SMC_READY: SMC is ready
 *           @arg EXMC_SMC_LOWPOWER: SMC is low power
 */
__STATIC_INLINE uint32_t EXMC_SMC_GetStatus(void)
{
    return READ_REG32_BIT(M4_SMC->STSR, SMC_STSR_STATUS);
}

/* Initialization and configuration EXMC SMC functions */
en_result_t EXMC_SMC_Init(uint32_t u32Chip, const stc_exmc_smc_init_t *pstcInit);
en_result_t EXMC_SMC_DeInit(void);
en_result_t EXMC_SMC_StructInit(stc_exmc_smc_init_t *pstcInit);

en_result_t EXMC_SMC_SetCommand(uint32_t u32Chip,
                                    uint32_t u32Cmd,
                                    uint32_t u32CrePolarity,
                                    uint32_t u32Addr);

uint32_t EXMC_SMC_ChipStartAddress(uint32_t u32Chip);
uint32_t EXMC_SMC_ChipEndAddress(uint32_t u32Chip);

en_result_t EXMC_SMC_CheckChipStatus(uint32_t u32Chip,
                                    const stc_exmc_smc_chip_cfg_t *pstcChipCfg);
en_result_t EXMC_SMC_CheckTimingStatus(uint32_t u32Chip,
                                const stc_exmc_smc_timing_cfg_t *pstcTimingCfg);

void EXMC_SMC_PinMuxCmd(en_functional_state_t enNewState);
void EXMC_SMC_SetRefreshPeriod(uint32_t u32PeriodVal);

/**
 * @}
 */

#endif /* DDL_SMC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_EXMC_SMC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
