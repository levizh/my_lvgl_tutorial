/**
 *******************************************************************************
 * @file  hc32f4a0_qspi.h
 * @brief This file contains all the functions prototypes of the QSPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-10       Wuze            First version
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
#ifndef __HC32F4A0_QSPI_H__
#define __HC32F4A0_QSPI_H__

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
 * @addtogroup DDL_QSPI
 * @{
 */

#if (DDL_QSPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Types QSPI Global Types
 * @{
 */

/**
 * @brief QSPI initialization structure.
 */
typedef struct
{
    uint32_t u32ClkDiv;                             /*!< Specifies the clock divider for QSCK.
                                                         This parameter can be a value of @ref QSPI_Clock_Divider */
    uint32_t u32CSSetupTiming;                      /*!< Specifies the setup timing of CS.
                                                         This parameter can be a value of @ref QSPI_CS_Setup_Timing */
    uint32_t u32CSReleaseTiming;                    /*!< Specifies the hold timing of CS.
                                                         This parameter can be a value of @ref QSPI_CS_Release_Timing */
    uint32_t u32CSIdleTime;                         /*!< Specifies the minimum idle time for CS. CS needs idle(stay high) for several cycles between commands.
                                                         This parameter can be a value of @ref QSPI_CS_Idle_Time */
    uint32_t u32CSExtendTime;                       /*!< Extend the time of chip-select signal after SPI bus access.
                                                         This parameter can be a value of @ref QSPI_CS_Extend_Time */
    uint32_t u32SPIMode;                            /*!< Specifies the SPI mode. The difference between SPI modes 0 and 3 is the standby level of the QSCK signal.
                                                         The standby level of the QSCK signal in SPI mode 0 is low, and high in SPI mode 3.
                                                         This parameter can be a value of @ref QSPI_SPI_Mode */
    uint32_t u32PrefetchCmd;                        /*!< Enable or disable prefeth function.
                                                         This parameter can be a value of @ref QSPI_Prefetch_Cmd */
    uint32_t u32PrefetchStopPos;                    /*!< Specifies the position of prefetch stop.
                                                         This parameter can be a value of @ref QSPI_Prefetch_Stop_Position */
    uint32_t u32WPLevel;                            /*!< Specifies the level of pin WP(IO2).
                                                         This parameter can be a value of @ref QSPI_WP_Level */
    uint32_t u32ReadMode;                           /*!< Specifies the read mode.
                                                         This parameter can be a value of @ref QSPI_Read_Mode */
    uint32_t u32CommMode;                           /*!< Specifies the communication mode.
                                                         This parameter can be a value of @ref QSPI_Communication_Mode */
    uint32_t u32AddrWidth;                          /*!< Specifies the address width.
                                                         This parameter can be a value of @ref QSPI_Addr_Width */
    uint32_t u32RomAccessInstr;                     /*!< Instruction of ROM access mode.
                                                         This parameter can be a value (8-bit) between 0x00 and 0xFF */
    uint32_t u32DummyCycles;                        /*!< Specifies the number of dummy cycles for fast read. 
                                                         This parameter can be a value of @ref QSPI_Dummy_Cycles. */
    uint32_t u32InstrMode;                          /*!< Specifies the instruction mode.
                                                         This parameter can be a value of @ref QSPI_Instruction_Mode */
    uint32_t u32AddrMode;                           /*!< Specifies the address mode.
                                                         This parameter can be a value of @ref QSPI_Addr_Mode */
    uint32_t u32DataMode;                           /*!< Specifies the data mode (used for dummy cycles and data phases)
                                                         This parameter can be a value of @ref QSPI_Data_Mode */
} stc_qspi_init_t;

/**
 * @brief QSPI command structure.
 */
typedef struct
{

    uint32_t u32Instr;                              /*!< Specifies the instruction to be sent.
                                                         This parameter can be a value (8-bit) between 0x00 and 0xFF */
    uint32_t u32Address;                            /*!< Specifies the address to be sent (width from 1 to 4 bytes according to u32AddrWidth)
                                                         This parameter can be a value (32-bits) between 0x00 and 0xFFFFFFFFU */
    uint32_t u32DummyBytes;                         /*!< Specifies the number of dummy bytes that follows behind instruction.
                                                         See the descriptions about the instructions in the SPI flash datasheet for details.
                                                         This parameter is only for direct communication mode. */
} stc_qspi_cmd_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Macros QSPI Global Macros
 * @{
 */

/**
 * @defgroup QSPI_Read_Mode QSPI Read Mode
 * @{
 */
#define QSPI_READ_STANDARD_READ             (0x0U)                  /*!< Standard read mode (no dummy cycles). */
#define QSPI_READ_FAST_READ                 (QSPI_CR_MDSEL_0)       /*!< Fast read mode (dummy cycles between address and data). */
#define QSPI_READ_FAST_READ_DUAL_OUTPUT     (QSPI_CR_MDSEL_1)       /*!< Fast read dual output mode (data on 2 lines). */
#define QSPI_READ_FAST_READ_DUAL_IO         (QSPI_CR_MDSEL_1 | \
                                             QSPI_CR_MDSEL_0)       /*!< Fast read dual I/O mode (address and data on 2 lines). */
#define QSPI_READ_FAST_READ_QUAD_OUTPUT     (QSPI_CR_MDSEL_2)       /*!< Fast read quad output mode (data on 4 lines). */
#define QSPI_READ_FAST_READ_QUAD_IO         (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_0)       /*!< Fast read quad I/O mode (address and data on 4 lines). */
#define QSPI_READ_CUSTOM_STANDARD_READ      (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_1)       /*!< Custom standard read mode. */
#define QSPI_READ_CUSTOM_FAST_READ          (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_1 | \
                                             QSPI_CR_MDSEL_0)       /*!< Custom fast read mode. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Prefetch_Cmd QSPI Prefetch Cmd
 * @{
 */
#define QSPI_PREFETCH_DISABLE               (0x0U)                  /*!< Disable prefetch. */
#define QSPI_PREFETCH_ENABLE                (QSPI_CR_PFE)           /*!< Enable prefetch. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Prefetch_Stop_Position QSPI Prefetch Stop Position
 * @{
 */
#define QSPI_PREFETCH_STOP_BYTE_EDGE        (0x0U)                  /*!< Stop prefetch at the edge of byte. */
#define QSPI_PREFETCH_STOP_IMMED            (QSPI_CR_PFSAE)         /*!< Stop prefetch at current position immediately. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Communication_Mode QSPI Communication Mode
 * @{
 */
#define QSPI_COMM_ROM_ACCESS                (0x0U)                  /*!< ROM access mode. */
#define QSPI_COMM_DIRECT_COMM               (QSPI_CR_DCOME)         /*!< Direct communication mode. */
/**
 * @}
 */

/**
 * @defgroup QSPI_XIP_Mode_Command QSPI XIP Mode Command
 * @{
 */
#define QSPI_XIP_DISABLE                    (0x0U)                  /*!< XIP mode disable. */
#define QSPI_XIP_ENABLE                     (QSPI_CR_XIPE)          /*!< XIP mode enable. */
/**
 * @}
 */

/**
 * @defgroup QSPI_SPI_Mode QSPI SPI Mode
 * @{
 */
#define QSPI_SPI_MODE_0                     (0x0U)                  /*!< Selects SPI mode 0. */
#define QSPI_SPI_MODE_3                     (QSPI_CR_SPIMD3)        /*!< Selects SPI mode 3. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Instruction_Mode QSPI Instruction Mode
 * @{
 */
#define QSPI_INSTR_1_LINE                   (0x0U)                  /*!< Instruction on a single line. */
#define QSPI_INSTR_2_LINE                   (QSPI_CR_IPRSL_0)       /*!< Instruction on 2 lines. */
#define QSPI_INSTR_4_LINE                   (QSPI_CR_IPRSL_1)       /*!< Instruction on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Mode QSPI Address Mode
 * @{
 */
#define QSPI_ADDR_1_LINE                    (0x0U)                  /*!< Address on a single line. */
#define QSPI_ADDR_2_LINE                    (QSPI_CR_APRSL_0)       /*!< Address on 2 lines. */
#define QSPI_ADDR_4_LINE                    (QSPI_CR_APRSL_1)       /*!< Address on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Data_Mode QSPI Data Mode
 * @{
 */
#define QSPI_DATA_1_LINE                    (0x0U)                  /*!< Data on a single line. */
#define QSPI_DATA_2_LINE                    (QSPI_CR_DPRSL_0)       /*!< Data on 2 lines. */
#define QSPI_DATA_4_LINE                    (QSPI_CR_DPRSL_1)       /*!< Data on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Clock_Divider QSPI Clock Divider
 * @{
 */
#define QSPI_CLK_DIV_2                      (1UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 2 */
#define QSPI_CLK_DIV_3                      (2UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 3 */
#define QSPI_CLK_DIV_4                      (3UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 4 */
#define QSPI_CLK_DIV_5                      (4UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 5 */
#define QSPI_CLK_DIV_6                      (5UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 6 */
#define QSPI_CLK_DIV_7                      (6UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 7 */
#define QSPI_CLK_DIV_8                      (7UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 8 */
#define QSPI_CLK_DIV_9                      (8UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 9 */
#define QSPI_CLK_DIV_10                     (9UL << QSPI_CR_DIV_POS)    /*!< QSCK = HCLK / 10 */
#define QSPI_CLK_DIV_11                     (10UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 11 */
#define QSPI_CLK_DIV_12                     (11UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 12 */
#define QSPI_CLK_DIV_13                     (12UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 13 */
#define QSPI_CLK_DIV_14                     (13UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 14 */
#define QSPI_CLK_DIV_15                     (14UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 15 */
#define QSPI_CLK_DIV_16                     (15UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 16 */
#define QSPI_CLK_DIV_17                     (16UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 17 */
#define QSPI_CLK_DIV_18                     (17UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 18 */
#define QSPI_CLK_DIV_19                     (18UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 19 */
#define QSPI_CLK_DIV_20                     (19UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 20 */
#define QSPI_CLK_DIV_21                     (20UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 21 */
#define QSPI_CLK_DIV_22                     (21UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 22 */
#define QSPI_CLK_DIV_23                     (22UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 23 */
#define QSPI_CLK_DIV_24                     (23UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 24 */
#define QSPI_CLK_DIV_25                     (24UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 25 */
#define QSPI_CLK_DIV_26                     (25UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 26 */
#define QSPI_CLK_DIV_27                     (26UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 27 */
#define QSPI_CLK_DIV_28                     (27UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 28 */
#define QSPI_CLK_DIV_29                     (28UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 29 */
#define QSPI_CLK_DIV_30                     (29UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 30 */
#define QSPI_CLK_DIV_31                     (30UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 31 */
#define QSPI_CLK_DIV_32                     (31UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 32 */
#define QSPI_CLK_DIV_33                     (32UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 33 */
#define QSPI_CLK_DIV_34                     (33UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 34 */
#define QSPI_CLK_DIV_35                     (34UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 35 */
#define QSPI_CLK_DIV_36                     (35UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 36 */
#define QSPI_CLK_DIV_37                     (36UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 37 */
#define QSPI_CLK_DIV_38                     (37UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 38 */
#define QSPI_CLK_DIV_39                     (38UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 39 */
#define QSPI_CLK_DIV_40                     (39UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 40 */
#define QSPI_CLK_DIV_41                     (40UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 41 */
#define QSPI_CLK_DIV_42                     (41UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 42 */
#define QSPI_CLK_DIV_43                     (42UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 43 */
#define QSPI_CLK_DIV_44                     (43UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 44 */
#define QSPI_CLK_DIV_45                     (44UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 45 */
#define QSPI_CLK_DIV_46                     (45UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 46 */
#define QSPI_CLK_DIV_47                     (46UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 47 */
#define QSPI_CLK_DIV_48                     (47UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 48 */
#define QSPI_CLK_DIV_49                     (48UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 49 */
#define QSPI_CLK_DIV_50                     (49UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 50 */
#define QSPI_CLK_DIV_51                     (50UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 51 */
#define QSPI_CLK_DIV_52                     (51UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 52 */
#define QSPI_CLK_DIV_53                     (52UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 53 */
#define QSPI_CLK_DIV_54                     (53UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 54 */
#define QSPI_CLK_DIV_55                     (54UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 55 */
#define QSPI_CLK_DIV_56                     (55UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 56 */
#define QSPI_CLK_DIV_57                     (56UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 57 */
#define QSPI_CLK_DIV_58                     (57UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 58 */
#define QSPI_CLK_DIV_59                     (58UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 59 */
#define QSPI_CLK_DIV_60                     (59UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 60 */
#define QSPI_CLK_DIV_61                     (60UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 61 */
#define QSPI_CLK_DIV_62                     (61UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 62 */
#define QSPI_CLK_DIV_63                     (62UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 63 */
#define QSPI_CLK_DIV_64                     (63UL << QSPI_CR_DIV_POS)   /*!< QSCK = HCLK / 64 */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Idle_Time QSPI Chip-select Minimum Idle Time
 * @{
 */
#define QSPI_CS_IDLE_1_CYCLE                (0UL)                   /*!< CS stay high for at least 1 clock cycle between commands. */
#define QSPI_CS_IDLE_2_CYCLE                (1UL)                   /*!< CS stay high for at least 2 clock cycle between commands. */
#define QSPI_CS_IDLE_3_CYCLE                (2UL)                   /*!< CS stay high for at least 3 clock cycle between commands. */
#define QSPI_CS_IDLE_4_CYCLE                (3UL)                   /*!< CS stay high for at least 4 clock cycle between commands. */
#define QSPI_CS_IDLE_5_CYCLE                (4UL)                   /*!< CS stay high for at least 5 clock cycle between commands. */
#define QSPI_CS_IDLE_6_CYCLE                (5UL)                   /*!< CS stay high for at least 6 clock cycle between commands. */
#define QSPI_CS_IDLE_7_CYCLE                (6UL)                   /*!< CS stay high for at least 7 clock cycle between commands. */
#define QSPI_CS_IDLE_8_CYCLE                (7UL)                   /*!< CS stay high for at least 8 clock cycle between commands. */
#define QSPI_CS_IDLE_9_CYCLE                (8UL)                   /*!< CS stay high for at least 9 clock cycle between commands. */
#define QSPI_CS_IDLE_10_CYCLE               (9UL)                   /*!< CS stay high for at least 10 clock cycle between commands. */
#define QSPI_CS_IDLE_11_CYCLE               (10UL)                  /*!< CS stay high for at least 11 clock cycle between commands. */
#define QSPI_CS_IDLE_12_CYCLE               (11UL)                  /*!< CS stay high for at least 12 clock cycle between commands. */
#define QSPI_CS_IDLE_13_CYCLE               (12UL)                  /*!< CS stay high for at least 13 clock cycle between commands. */
#define QSPI_CS_IDLE_14_CYCLE               (13UL)                  /*!< CS stay high for at least 14 clock cycle between commands. */
#define QSPI_CS_IDLE_15_CYCLE               (14UL)                  /*!< CS stay high for at least 15 clock cycle between commands. */
#define QSPI_CS_IDLE_16_CYCLE               (15UL)                  /*!< CS stay high for at least 16 clock cycle between commands. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Extend_Time QSPI Chip-select Extend Time
 * @{
 */
#define QSPI_CS_EXTEND_0_CYCLE              (0x0U)                  /*!< Do not extend chip-select signal time. */
#define QSPI_CS_EXTEND_32_CYCLE             (QSPI_CSCR_SSNW_0)      /*!< Extend chip-select time by 32 QSCK cycles. */
#define QSPI_CS_EXTEND_128_CYCLE            (QSPI_CSCR_SSNW_1)      /*!< Extend chip-select time by 128 QSCK cycles. */
#define QSPI_CS_EXTEND_INFINITE             (QSPI_CSCR_SSNW_1 | \
                                             QSPI_CSCR_SSNW_0)      /*!< Extend chip-select time infinitely. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Width QSPI Address Width
 * @{
 */
#define QSPI_ADDR_WIDTH_1_BYTE              (0x0U)                  /*!< QSPI address width is 1 byte. */
#define QSPI_ADDR_WIDTH_2_BYTE              (QSPI_FCR_AWSL_0)       /*!< QSPI address width is 2 bytes. */
#define QSPI_ADDR_WIDTH_3_BYTE              (QSPI_FCR_AWSL_1)       /*!< QSPI address width is 3 bytes. */
#define QSPI_ADDR_WIDTH_4_BYTE              (QSPI_FCR_AWSL_1 | \
                                             QSPI_FCR_AWSL_0)       /*!< QSPI address width is 4 bytes. */
/**
 * @}
 */

/**
 * @defgroup QSPI_4BIC_Command QSPI 4-Byte Address Instruction Read Code Command
 * @note Valid when the serial interface address width is 4 bytes.
 * @{
 */
#define QSPI_4BIC_DISABLE                   (0x0U)                  /*!< Do not use 4-byte address read instruction code. */
#define QSPI_4BIC_ENABLE                    (QSPI_FCR_4BIC)         /*!< Use 4-byte address read instruction code. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Release_Timing QSPI Chip-select Hold Timing
 * @{
 */
#define QSPI_CS_RELEASE_AFTER_0P5_CYCLE     (0x0U)                  /*!< Release chip-select signal 0.5 QSCK cycles after the last rising edge of QSCK. */
#define QSPI_CS_RELEASE_AFTER_1P5_CYCLE     (QSPI_FCR_SSNHD)        /*!< Release chip-select signal 1.5 QSCK cycles after the last rising edge of QSCK. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Setup_Timing QSPI Chip-select Setup Timing
 * @{
 */
#define QSPI_CS_SETUP_BEFORE_0P5_CYCLE      (0x0U)                  /*!< Output chip-select signal 0.5 QSCK cycles before the first rising edge of QSCK. */
#define QSPI_CS_SETUP_BEFORE_1P5_CYCLE      (QSPI_FCR_SSNLD)        /*!< Output chip-select signal 1.5 QSCK cycles before the first rising edge of QSCK. */
/**
 * @}
 */

/**
 * @defgroup QSPI_WP_Level QSPI Write Protect Pin Level
 * @{
 */
#define QSPI_WP_LOW                         (0x0U)                  /*!< WP(QIO2) output low. */
#define QSPI_WP_HIGH                        (QSPI_FCR_WPOL)         /*!< WP(QIO2) output high. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Dummy_Cycles QSPI Dummy Cycles For Fast Read
 * @{
 */
#define QSPI_DUMMY_CYCLE_3                  (0UL << QSPI_FCR_DMCYCN_POS)    /*!< 3 dummy cycles. */
#define QSPI_DUMMY_CYCLE_4                  (1UL << QSPI_FCR_DMCYCN_POS)    /*!< 4 dummy cycles. */
#define QSPI_DUMMY_CYCLE_5                  (2UL << QSPI_FCR_DMCYCN_POS)    /*!< 5 dummy cycles. */
#define QSPI_DUMMY_CYCLE_6                  (3UL << QSPI_FCR_DMCYCN_POS)    /*!< 6 dummy cycles. */
#define QSPI_DUMMY_CYCLE_7                  (4UL << QSPI_FCR_DMCYCN_POS)    /*!< 7 dummy cycles. */
#define QSPI_DUMMY_CYCLE_8                  (5UL << QSPI_FCR_DMCYCN_POS)    /*!< 8 dummy cycles. */
#define QSPI_DUMMY_CYCLE_9                  (6UL << QSPI_FCR_DMCYCN_POS)    /*!< 9 dummy cycles. */
#define QSPI_DUMMY_CYCLE_10                 (7UL << QSPI_FCR_DMCYCN_POS)    /*!< 10 dummy cycles. */
#define QSPI_DUMMY_CYCLE_11                 (8UL << QSPI_FCR_DMCYCN_POS)    /*!< 11 dummy cycles. */
#define QSPI_DUMMY_CYCLE_12                 (9UL << QSPI_FCR_DMCYCN_POS)    /*!< 12 dummy cycles. */
#define QSPI_DUMMY_CYCLE_13                 (10UL << QSPI_FCR_DMCYCN_POS)   /*!< 13 dummy cycles. */
#define QSPI_DUMMY_CYCLE_14                 (11UL << QSPI_FCR_DMCYCN_POS)   /*!< 14 dummy cycles. */
#define QSPI_DUMMY_CYCLE_15                 (12UL << QSPI_FCR_DMCYCN_POS)   /*!< 15 dummy cycles. */
#define QSPI_DUMMY_CYCLE_16                 (13UL << QSPI_FCR_DMCYCN_POS)   /*!< 16 dummy cycles. */
#define QSPI_DUMMY_CYCLE_17                 (14UL << QSPI_FCR_DMCYCN_POS)   /*!< 17 dummy cycles. */
#define QSPI_DUMMY_CYCLE_18                 (15UL << QSPI_FCR_DMCYCN_POS)   /*!< 18 dummy cycles. */
/**
 * @}
 */

/**
 * @defgroup QSPI_QSCK_Duty_Correction_Command QSPI QSCK Duty Correction Command
 * @{
 */
#define QSPI_DUTY_CORRECTION_DISABLE        (0x0U)                  /*!< Make no duty ratio correction on QSCK. */
#define QSPI_DUTY_CORRECTION_ENABLE         (QSPI_FCR_DUTY)         /*!< Delay the rising of the QSCK signal by 0.5 HCLK cycles. \
                                                                         (Valid when HCLK is multiplied by an odd number.) */
/**
 * @}
 */

/**
 * @defgroup QSPI_Status_Flag QSPI Status Flag
 * @{
 */
#define QSPI_FLAG_DIRECT_COMM_BUSY          (QSPI_SR_BUSY)          /*!< Serial transfer being processed. */
#define QSPI_FLAG_XIP_MODE                  (QSPI_SR_XIPF)          /*!< XIP mode. */
#define QSPI_FLAG_ROM_ACCESS_ERR            (QSPI_SR_RAER)          /*!< ROM access detection status in direct communication mode. */
#define QSPI_FLAG_PREFETCH_BUF_FULL         (QSPI_SR_PFFUL)         /*!< Prefetch buffer is full. */
#define QSPI_FLAG_PREFETCH_ACTIVE           (QSPI_SR_PFAN)          /*!< Prefetch function operating. */

#define QSPI_FLAG_ALL                       (QSPI_FLAG_DIRECT_COMM_BUSY  | \
                                             QSPI_FLAG_XIP_MODE          | \
                                             QSPI_FLAG_ROM_ACCESS_ERR    | \
                                             QSPI_FLAG_PREFETCH_BUF_FULL | \
                                             QSPI_FLAG_PREFETCH_ACTIVE)
/**
 * @}
 */

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
 * @addtogroup QSPI_Global_Functions
 * @{
 */

/**
 * @brief  Enter direct communication mode.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void QSPI_EnterDirectCommMode(void)
{
    /* Set standard read mode. */
    CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_MDSEL);
    /* Enter direct communication mode. */
    SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

/**
 * @brief  Exit direct communication mode.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void QSPI_ExitDirectCommMode(void)
{
    CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

/**
 * @brief  Write data in direct communication mode.
 * @param  [in]  u8Val              Byte data.
 * @retval None
 */
__STATIC_INLINE void QSPI_WriteDirectCommValue(uint8_t u8Val)
{
    WRITE_REG32(M4_QSPI->DCOM, u8Val);
}

/**
 * @brief  Read data in communication mode.
 * @param  None
 * @retval Byte data.
 */
__STATIC_INLINE uint8_t QSPI_ReadDirectCommValue(void)
{
    return (uint8_t)M4_QSPI->DCOM;
}

/**
 * @brief  Set ROM access instruction.
 * @param  [in]  u8Instr                ROM access instruction.
 * @retval None
 */
__STATIC_INLINE void QSPI_SetRomAccressInstr(uint8_t u8Instr)
{
    WRITE_REG32(M4_QSPI->CCMD, u8Instr);
}


en_result_t QSPI_Init(const stc_qspi_init_t *pstcInit);
void QSPI_DeInit(void);
en_result_t QSPI_StructInit(stc_qspi_init_t *pstcInit);

en_result_t QSPI_WriteData(uint32_t u32Instr, uint32_t u32Address, \
                           const uint8_t pu8Src[], uint32_t u32SrcSize);
en_result_t QSPI_ReadData(uint32_t u32ReadMode, uint32_t u32Address, \
                          uint8_t pu8Dest[], uint32_t u32DestSize);

void QSPI_SetReadMode(uint32_t u32ReadMode);
void QSPI_PrefetchCmd(en_functional_state_t enNewState);
void QSPI_XIPModeCmd(en_functional_state_t enNewState);
void QSPI_SetWPPinLevel(uint32_t u32Level);
void QSPI_4ByteAddrModeCmd(en_functional_state_t enNewState);
void QSPI_SelectBlock(uint32_t u32Block);

uint32_t QSPI_GetPrefetchedSize(void);
en_flag_status_t QSPI_GetStatus(uint32_t u32Flag);
void QSPI_ClrStatus(uint32_t u32Flag);

void QSPI_EnterDirectCommMode(void);
void QSPI_ExitDirectCommMode(void);
void QSPI_WriteDirectCommValue(uint8_t u8Val);
uint8_t QSPI_ReadDirectCommValue(void);
void QSPI_SetRomAccressInstr(uint8_t u8Instr);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_QSPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
