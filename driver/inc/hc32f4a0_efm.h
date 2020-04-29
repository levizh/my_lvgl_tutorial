/**
 *******************************************************************************
 * @file  hc32f4a0_efm.h
 * @brief This file contains all the functions prototypes of the EFM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-02       Heqb           First version
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
#ifndef __HC32F4A0_EFM_H__
#define __HC32F4A0_EFM_H__

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
 * @addtogroup DDL_EFM
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Types EFM Global Types
 * @{
 */

/**
 * @brief EFM configure structure
 */
typedef struct
{
    uint32_t            u32WaitCycle;   /*!< Specifies the efm read wait cycles.
                                            This parameter can be a value of @ref EFM_Wait_Cycle.             */

    uint32_t            u32CacheRst;    /*!< Specifies the data cache reset on or off.
                                            This parameter can be a value of @ref EFM_CacheRst_Func.       */

    uint32_t            u32Prefetch;    /*!< Specifies the prefetch on or off.
                                            This parameter can be a value of @ref EFM_Prefetch_Func.       */

    uint32_t            u32InsCache;    /*!< Specifies the instruction cache on or off.
                                            This parameter can be a value of @ref EFM_INSCache_Func.         */

    uint32_t            u32DataCache;   /*!< Specifies the data cache on or off.
                                            This parameter can be a value of @ref EFM_DCache_Func.          */

    uint32_t            u32LowVolRead;  /*!< Specifies the read of low-voltage mode on or off.          
                                            This parameter can be a value of @ref EFM_LowVolRead_Mode.        */                                          

    uint32_t            u32BusState;    /*!< Specifies the bus state busy or release while program & erase.
                                            This parameter can be a value of @ref EFM_Bus_State.           */

    uint32_t            u32OperateMode; /*!< Specifies the operate mode.
                                            This parameter can be a value of @EFM_Mode_definition*/

    uint32_t            u32FlashStatus; /*!< Specifies the Flash status.
                                            This parameter can be a value of @EFM_Status */
} stc_efm_cfg_t;

/**
 * @brief EFM unique ID definition
 */
typedef struct
{
    uint32_t            u32UniqueID0;      /*!< unique ID 0.       */
    uint32_t            u32UniqueID1;      /*!< unique ID 1.       */
    uint32_t            u32UniqueID2;      /*!< unique ID 2.       */
} stc_efm_unique_id_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Macros EFM Global Macros
 * @{
 */
#define EFM_TIMEOUT                 ((uint32_t)0x1000U)

/**
 * @defgroup EFM_Address EFM address area
 * @{
 */
#define EFM_START_ADDR              ((uint32_t)0x00000000U)   /*!< Flash start address */
#define EFM_END_ADDR                ((uint32_t)0x001FFFFFU)   /*!< Flash end address */
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_SECTOR0_ADDR            ((uint32_t)0x00000000U)   /*!< Sector 0 */
#define EFM_SECTOR1_ADDR            ((uint32_t)0x00002000U)   /*!< Sector 1 */
#define EFM_SECTOR2_ADDR            ((uint32_t)0x00004000U)   /*!< Sector 2 */
#define EFM_SECTOR3_ADDR            ((uint32_t)0x00006000U)   /*!< Sector 3 */
#define EFM_SECTOR4_ADDR            ((uint32_t)0x00008000U)   /*!< Sector 4 */
#define EFM_SECTOR5_ADDR            ((uint32_t)0x0000A000U)   /*!< Sector 5 */
#define EFM_SECTOR6_ADDR            ((uint32_t)0x0000C000U)   /*!< Sector 6 */
#define EFM_SECTOR7_ADDR            ((uint32_t)0x0000E000U)   /*!< Sector 7 */
#define EFM_SECTOR8_ADDR            ((uint32_t)0x00010000U)   /*!< Sector 8 */
#define EFM_SECTOR9_ADDR            ((uint32_t)0x00012000U)   /*!< Sector 9 */
#define EFM_SECTOR10_ADDR           ((uint32_t)0x00014000U)   /*!< Sector 10 */
#define EFM_SECTOR11_ADDR           ((uint32_t)0x00016000U)   /*!< Sector 11 */
#define EFM_SECTOR12_ADDR           ((uint32_t)0x00018000U)   /*!< Sector 12 */
#define EFM_SECTOR13_ADDR           ((uint32_t)0x0001A000U)   /*!< Sector 13 */
#define EFM_SECTOR14_ADDR           ((uint32_t)0x0001C000U)   /*!< Sector 14 */
#define EFM_SECTOR15_ADDR           ((uint32_t)0x0001E000U)   /*!< Sector 15 */
#define EFM_SECTOR16_ADDR           ((uint32_t)0x00020000U)   /*!< Sector 16 */
#define EFM_SECTOR17_ADDR           ((uint32_t)0x00022000U)   /*!< Sector 17 */
#define EFM_SECTOR18_ADDR           ((uint32_t)0x00024000U)   /*!< Sector 18 */
#define EFM_SECTOR19_ADDR           ((uint32_t)0x00026000U)   /*!< Sector 19 */
#define EFM_SECTOR20_ADDR           ((uint32_t)0x00028000U)   /*!< Sector 20 */
#define EFM_SECTOR21_ADDR           ((uint32_t)0x0002A000U)   /*!< Sector 21 */
#define EFM_SECTOR22_ADDR           ((uint32_t)0x0002C000U)   /*!< Sector 22 */
#define EFM_SECTOR23_ADDR           ((uint32_t)0x0002E000U)   /*!< Sector 23 */
#define EFM_SECTOR24_ADDR           ((uint32_t)0x00030000U)   /*!< Sector 24 */
#define EFM_SECTOR25_ADDR           ((uint32_t)0x00032000U)   /*!< Sector 25 */
#define EFM_SECTOR26_ADDR           ((uint32_t)0x00034000U)   /*!< Sector 26 */
#define EFM_SECTOR27_ADDR           ((uint32_t)0x00036000U)   /*!< Sector 27 */
#define EFM_SECTOR28_ADDR           ((uint32_t)0x00038000U)   /*!< Sector 28 */
#define EFM_SECTOR29_ADDR           ((uint32_t)0x0003A000U)   /*!< Sector 29 */
#define EFM_SECTOR30_ADDR           ((uint32_t)0x0003C000U)   /*!< Sector 30 */
#define EFM_SECTOR31_ADDR           ((uint32_t)0x0003E000U)   /*!< Sector 31 */
#define EFM_SECTOR32_ADDR           ((uint32_t)0x00040000U)   /*!< Sector 32 */
#define EFM_SECTOR33_ADDR           ((uint32_t)0x00042000U)   /*!< Sector 33 */
#define EFM_SECTOR34_ADDR           ((uint32_t)0x00044000U)   /*!< Sector 34 */
#define EFM_SECTOR35_ADDR           ((uint32_t)0x00046000U)   /*!< Sector 35 */
#define EFM_SECTOR36_ADDR           ((uint32_t)0x00048000U)   /*!< Sector 36 */
#define EFM_SECTOR37_ADDR           ((uint32_t)0x0004A000U)   /*!< Sector 37 */
#define EFM_SECTOR38_ADDR           ((uint32_t)0x0004C000U)   /*!< Sector 38 */
#define EFM_SECTOR39_ADDR           ((uint32_t)0x0004E000U)   /*!< Sector 39 */
#define EFM_SECTOR40_ADDR           ((uint32_t)0x00050000U)   /*!< Sector 40 */
#define EFM_SECTOR41_ADDR           ((uint32_t)0x00052000U)   /*!< Sector 41 */
#define EFM_SECTOR42_ADDR           ((uint32_t)0x00054000U)   /*!< Sector 42 */
#define EFM_SECTOR43_ADDR           ((uint32_t)0x00056000U)   /*!< Sector 43 */
#define EFM_SECTOR44_ADDR           ((uint32_t)0x00058000U)   /*!< Sector 44 */
#define EFM_SECTOR45_ADDR           ((uint32_t)0x0005A000U)   /*!< Sector 45 */
#define EFM_SECTOR46_ADDR           ((uint32_t)0x0005C000U)   /*!< Sector 46 */
#define EFM_SECTOR47_ADDR           ((uint32_t)0x0005E000U)   /*!< Sector 47 */
#define EFM_SECTOR48_ADDR           ((uint32_t)0x00060000U)   /*!< Sector 48 */
#define EFM_SECTOR49_ADDR           ((uint32_t)0x00062000U)   /*!< Sector 49 */
#define EFM_SECTOR50_ADDR           ((uint32_t)0x00064000U)   /*!< Sector 50 */
#define EFM_SECTOR51_ADDR           ((uint32_t)0x00066000U)   /*!< Sector 51 */
#define EFM_SECTOR52_ADDR           ((uint32_t)0x00068000U)   /*!< Sector 52 */
#define EFM_SECTOR53_ADDR           ((uint32_t)0x0006A000U)   /*!< Sector 53 */
#define EFM_SECTOR54_ADDR           ((uint32_t)0x0006C000U)   /*!< Sector 54 */
#define EFM_SECTOR55_ADDR           ((uint32_t)0x0006E000U)   /*!< Sector 55 */
#define EFM_SECTOR56_ADDR           ((uint32_t)0x00070000U)   /*!< Sector 56 */
#define EFM_SECTOR57_ADDR           ((uint32_t)0x00072000U)   /*!< Sector 57 */
#define EFM_SECTOR58_ADDR           ((uint32_t)0x00074000U)   /*!< Sector 58 */
#define EFM_SECTOR59_ADDR           ((uint32_t)0x00076000U)   /*!< Sector 59 */
#define EFM_SECTOR60_ADDR           ((uint32_t)0x00078000U)   /*!< Sector 60 */
#define EFM_SECTOR61_ADDR           ((uint32_t)0x0007A000U)   /*!< Sector 61 */
#define EFM_SECTOR62_ADDR           ((uint32_t)0x0007C000U)   /*!< Sector 62 */
#define EFM_SECTOR63_ADDR           ((uint32_t)0x0007E000U)   /*!< Sector 63 */
#define EFM_SECTOR64_ADDR           ((uint32_t)0x00080000U)   /*!< Sector 64 */
#define EFM_SECTOR65_ADDR           ((uint32_t)0x00082000U)   /*!< Sector 65 */
#define EFM_SECTOR66_ADDR           ((uint32_t)0x00084000U)   /*!< Sector 66 */
#define EFM_SECTOR67_ADDR           ((uint32_t)0x00086000U)   /*!< Sector 67 */
#define EFM_SECTOR68_ADDR           ((uint32_t)0x00088000U)   /*!< Sector 68 */
#define EFM_SECTOR69_ADDR           ((uint32_t)0x0008A000U)   /*!< Sector 69 */
#define EFM_SECTOR70_ADDR           ((uint32_t)0x0008C000U)   /*!< Sector 70 */
#define EFM_SECTOR71_ADDR           ((uint32_t)0x0008E000U)   /*!< Sector 71 */
#define EFM_SECTOR72_ADDR           ((uint32_t)0x00090000U)   /*!< Sector 72 */
#define EFM_SECTOR73_ADDR           ((uint32_t)0x00092000U)   /*!< Sector 73 */
#define EFM_SECTOR74_ADDR           ((uint32_t)0x00094000U)   /*!< Sector 74 */
#define EFM_SECTOR75_ADDR           ((uint32_t)0x00096000U)   /*!< Sector 75 */
#define EFM_SECTOR76_ADDR           ((uint32_t)0x00098000U)   /*!< Sector 76 */
#define EFM_SECTOR77_ADDR           ((uint32_t)0x0009A000U)   /*!< Sector 77 */
#define EFM_SECTOR78_ADDR           ((uint32_t)0x0009C000U)   /*!< Sector 78 */
#define EFM_SECTOR79_ADDR           ((uint32_t)0x0009E000U)   /*!< Sector 79 */
#define EFM_SECTOR80_ADDR           ((uint32_t)0x000A0000U)   /*!< Sector 80 */
#define EFM_SECTOR81_ADDR           ((uint32_t)0x000A2000U)   /*!< Sector 81 */
#define EFM_SECTOR82_ADDR           ((uint32_t)0x000A4000U)   /*!< Sector 82 */
#define EFM_SECTOR83_ADDR           ((uint32_t)0x000A6000U)   /*!< Sector 83 */
#define EFM_SECTOR84_ADDR           ((uint32_t)0x000A8000U)   /*!< Sector 84 */
#define EFM_SECTOR85_ADDR           ((uint32_t)0x000AA000U)   /*!< Sector 85 */
#define EFM_SECTOR86_ADDR           ((uint32_t)0x000AC000U)   /*!< Sector 86 */
#define EFM_SECTOR87_ADDR           ((uint32_t)0x000AE000U)   /*!< Sector 87 */
#define EFM_SECTOR88_ADDR           ((uint32_t)0x000B0000U)   /*!< Sector 88 */
#define EFM_SECTOR89_ADDR           ((uint32_t)0x000B2000U)   /*!< Sector 89 */
#define EFM_SECTOR90_ADDR           ((uint32_t)0x000B4000U)   /*!< Sector 90 */
#define EFM_SECTOR91_ADDR           ((uint32_t)0x000B6000U)   /*!< Sector 91 */
#define EFM_SECTOR92_ADDR           ((uint32_t)0x000B8000U)   /*!< Sector 92 */
#define EFM_SECTOR93_ADDR           ((uint32_t)0x000BA000U)   /*!< Sector 93 */
#define EFM_SECTOR94_ADDR           ((uint32_t)0x000BC000U)   /*!< Sector 94 */
#define EFM_SECTOR95_ADDR           ((uint32_t)0x000BE000U)   /*!< Sector 95 */
#define EFM_SECTOR96_ADDR           ((uint32_t)0x000C0000U)   /*!< Sector 96 */
#define EFM_SECTOR97_ADDR           ((uint32_t)0x000C2000U)   /*!< Sector 97 */
#define EFM_SECTOR98_ADDR           ((uint32_t)0x000C4000U)   /*!< Sector 98 */
#define EFM_SECTOR99_ADDR           ((uint32_t)0x000C6000U)   /*!< Sector 99 */
#define EFM_SECTOR100_ADDR          ((uint32_t)0x000C8000U)   /*!< Sector 100 */
#define EFM_SECTOR101_ADDR          ((uint32_t)0x000CA000U)   /*!< Sector 101 */
#define EFM_SECTOR102_ADDR          ((uint32_t)0x000CC000U)   /*!< Sector 102 */
#define EFM_SECTOR103_ADDR          ((uint32_t)0x000CE000U)   /*!< Sector 103 */
#define EFM_SECTOR104_ADDR          ((uint32_t)0x000D0000U)   /*!< Sector 104 */
#define EFM_SECTOR105_ADDR          ((uint32_t)0x000D2000U)   /*!< Sector 105 */
#define EFM_SECTOR106_ADDR          ((uint32_t)0x000D4000U)   /*!< Sector 106 */
#define EFM_SECTOR107_ADDR          ((uint32_t)0x000D6000U)   /*!< Sector 107 */
#define EFM_SECTOR108_ADDR          ((uint32_t)0x000D8000U)   /*!< Sector 108 */
#define EFM_SECTOR109_ADDR          ((uint32_t)0x000DA000U)   /*!< Sector 109 */
#define EFM_SECTOR110_ADDR          ((uint32_t)0x000DC000U)   /*!< Sector 110 */
#define EFM_SECTOR111_ADDR          ((uint32_t)0x000DE000U)   /*!< Sector 111 */
#define EFM_SECTOR112_ADDR          ((uint32_t)0x000E0000U)   /*!< Sector 112 */
#define EFM_SECTOR113_ADDR          ((uint32_t)0x000E2000U)   /*!< Sector 113 */
#define EFM_SECTOR114_ADDR          ((uint32_t)0x000E4000U)   /*!< Sector 114 */
#define EFM_SECTOR115_ADDR          ((uint32_t)0x000E6000U)   /*!< Sector 115 */
#define EFM_SECTOR116_ADDR          ((uint32_t)0x000E8000U)   /*!< Sector 116 */
#define EFM_SECTOR117_ADDR          ((uint32_t)0x000EA000U)   /*!< Sector 117 */
#define EFM_SECTOR118_ADDR          ((uint32_t)0x000EC000U)   /*!< Sector 118 */
#define EFM_SECTOR119_ADDR          ((uint32_t)0x000EE000U)   /*!< Sector 119 */
#define EFM_SECTOR120_ADDR          ((uint32_t)0x000F0000U)   /*!< Sector 120 */
#define EFM_SECTOR121_ADDR          ((uint32_t)0x000F2000U)   /*!< Sector 121 */
#define EFM_SECTOR122_ADDR          ((uint32_t)0x000F4000U)   /*!< Sector 122 */
#define EFM_SECTOR123_ADDR          ((uint32_t)0x000F6000U)   /*!< Sector 123 */
#define EFM_SECTOR124_ADDR          ((uint32_t)0x000F8000U)   /*!< Sector 124 */
#define EFM_SECTOR125_ADDR          ((uint32_t)0x000FA000U)   /*!< Sector 125 */
#define EFM_SECTOR126_ADDR          ((uint32_t)0x000FC000U)   /*!< Sector 126 */
#define EFM_SECTOR127_ADDR          ((uint32_t)0x000FE000U)   /*!< Sector 127 */
#define EFM_SECTOR128_ADDR          ((uint32_t)0x00100000U)   /*!< Sector 128 */
#define EFM_SECTOR129_ADDR          ((uint32_t)0x00102000U)   /*!< Sector 129 */
#define EFM_SECTOR130_ADDR          ((uint32_t)0x00104000U)   /*!< Sector 130 */
#define EFM_SECTOR131_ADDR          ((uint32_t)0x00106000U)   /*!< Sector 131 */
#define EFM_SECTOR132_ADDR          ((uint32_t)0x00108000U)   /*!< Sector 132 */
#define EFM_SECTOR133_ADDR          ((uint32_t)0x0010A000U)   /*!< Sector 133 */
#define EFM_SECTOR134_ADDR          ((uint32_t)0x0010C000U)   /*!< Sector 134 */
#define EFM_SECTOR135_ADDR          ((uint32_t)0x0010E000U)   /*!< Sector 135 */
#define EFM_SECTOR136_ADDR          ((uint32_t)0x00110000U)   /*!< Sector 136 */
#define EFM_SECTOR137_ADDR          ((uint32_t)0x00112000U)   /*!< Sector 137 */
#define EFM_SECTOR138_ADDR          ((uint32_t)0x00114000U)   /*!< Sector 138 */
#define EFM_SECTOR139_ADDR          ((uint32_t)0x00116000U)   /*!< Sector 139 */
#define EFM_SECTOR140_ADDR          ((uint32_t)0x00118000U)   /*!< Sector 140 */
#define EFM_SECTOR141_ADDR          ((uint32_t)0x0011A000U)   /*!< Sector 141 */
#define EFM_SECTOR142_ADDR          ((uint32_t)0x0011C000U)   /*!< Sector 142 */
#define EFM_SECTOR143_ADDR          ((uint32_t)0x0011E000U)   /*!< Sector 143 */
#define EFM_SECTOR144_ADDR          ((uint32_t)0x00120000U)   /*!< Sector 144 */
#define EFM_SECTOR145_ADDR          ((uint32_t)0x00122000U)   /*!< Sector 145 */
#define EFM_SECTOR146_ADDR          ((uint32_t)0x00124000U)   /*!< Sector 146 */
#define EFM_SECTOR147_ADDR          ((uint32_t)0x00126000U)   /*!< Sector 147 */
#define EFM_SECTOR148_ADDR          ((uint32_t)0x00128000U)   /*!< Sector 148 */
#define EFM_SECTOR149_ADDR          ((uint32_t)0x0012A000U)   /*!< Sector 149 */
#define EFM_SECTOR150_ADDR          ((uint32_t)0x0012C000U)   /*!< Sector 150 */
#define EFM_SECTOR151_ADDR          ((uint32_t)0x0012E000U)   /*!< Sector 151 */
#define EFM_SECTOR152_ADDR          ((uint32_t)0x00130000U)   /*!< Sector 152 */
#define EFM_SECTOR153_ADDR          ((uint32_t)0x00132000U)   /*!< Sector 153 */
#define EFM_SECTOR154_ADDR          ((uint32_t)0x00134000U)   /*!< Sector 154 */
#define EFM_SECTOR155_ADDR          ((uint32_t)0x00136000U)   /*!< Sector 155 */
#define EFM_SECTOR156_ADDR          ((uint32_t)0x00138000U)   /*!< Sector 156 */
#define EFM_SECTOR157_ADDR          ((uint32_t)0x0013A000U)   /*!< Sector 157 */
#define EFM_SECTOR158_ADDR          ((uint32_t)0x0013C000U)   /*!< Sector 158 */
#define EFM_SECTOR159_ADDR          ((uint32_t)0x0013E000U)   /*!< Sector 159 */
#define EFM_SECTOR160_ADDR          ((uint32_t)0x00140000U)   /*!< Sector 160 */
#define EFM_SECTOR161_ADDR          ((uint32_t)0x00142000U)   /*!< Sector 161 */
#define EFM_SECTOR162_ADDR          ((uint32_t)0x00144000U)   /*!< Sector 162 */
#define EFM_SECTOR163_ADDR          ((uint32_t)0x00146000U)   /*!< Sector 163 */
#define EFM_SECTOR164_ADDR          ((uint32_t)0x00148000U)   /*!< Sector 164 */
#define EFM_SECTOR165_ADDR          ((uint32_t)0x0014A000U)   /*!< Sector 165 */
#define EFM_SECTOR166_ADDR          ((uint32_t)0x0014C000U)   /*!< Sector 166 */
#define EFM_SECTOR167_ADDR          ((uint32_t)0x0014E000U)   /*!< Sector 167 */
#define EFM_SECTOR168_ADDR          ((uint32_t)0x00150000U)   /*!< Sector 168 */
#define EFM_SECTOR169_ADDR          ((uint32_t)0x00152000U)   /*!< Sector 179 */
#define EFM_SECTOR170_ADDR          ((uint32_t)0x00154000U)   /*!< Sector 170 */
#define EFM_SECTOR171_ADDR          ((uint32_t)0x00156000U)   /*!< Sector 171 */
#define EFM_SECTOR172_ADDR          ((uint32_t)0x00158000U)   /*!< Sector 172 */
#define EFM_SECTOR173_ADDR          ((uint32_t)0x0015A000U)   /*!< Sector 173 */
#define EFM_SECTOR174_ADDR          ((uint32_t)0x0015C000U)   /*!< Sector 174 */
#define EFM_SECTOR175_ADDR          ((uint32_t)0x0015E000U)   /*!< Sector 175 */
#define EFM_SECTOR176_ADDR          ((uint32_t)0x00160000U)   /*!< Sector 176 */
#define EFM_SECTOR177_ADDR          ((uint32_t)0x00162000U)   /*!< Sector 177 */
#define EFM_SECTOR178_ADDR          ((uint32_t)0x00164000U)   /*!< Sector 178 */
#define EFM_SECTOR179_ADDR          ((uint32_t)0x00166000U)   /*!< Sector 179 */
#define EFM_SECTOR180_ADDR          ((uint32_t)0x00168000U)   /*!< Sector 180 */
#define EFM_SECTOR181_ADDR          ((uint32_t)0x0016A000U)   /*!< Sector 181 */
#define EFM_SECTOR182_ADDR          ((uint32_t)0x0016C000U)   /*!< Sector 182 */
#define EFM_SECTOR183_ADDR          ((uint32_t)0x0016E000U)   /*!< Sector 183 */
#define EFM_SECTOR184_ADDR          ((uint32_t)0x00170000U)   /*!< Sector 184 */
#define EFM_SECTOR185_ADDR          ((uint32_t)0x00172000U)   /*!< Sector 185 */
#define EFM_SECTOR186_ADDR          ((uint32_t)0x00174000U)   /*!< Sector 186 */
#define EFM_SECTOR187_ADDR          ((uint32_t)0x00176000U)   /*!< Sector 187 */
#define EFM_SECTOR188_ADDR          ((uint32_t)0x00178000U)   /*!< Sector 188 */
#define EFM_SECTOR189_ADDR          ((uint32_t)0x0017A000U)   /*!< Sector 189 */
#define EFM_SECTOR190_ADDR          ((uint32_t)0x0017C000U)   /*!< Sector 190 */
#define EFM_SECTOR191_ADDR          ((uint32_t)0x0017E000U)   /*!< Sector 191 */
#define EFM_SECTOR192_ADDR          ((uint32_t)0x00180000U)   /*!< Sector 192 */
#define EFM_SECTOR193_ADDR          ((uint32_t)0x00182000U)   /*!< Sector 193 */
#define EFM_SECTOR194_ADDR          ((uint32_t)0x00184000U)   /*!< Sector 194 */
#define EFM_SECTOR195_ADDR          ((uint32_t)0x00186000U)   /*!< Sector 195 */
#define EFM_SECTOR196_ADDR          ((uint32_t)0x00188000U)   /*!< Sector 196 */
#define EFM_SECTOR197_ADDR          ((uint32_t)0x0018A000U)   /*!< Sector 197 */
#define EFM_SECTOR198_ADDR          ((uint32_t)0x0018C000U)   /*!< Sector 198 */
#define EFM_SECTOR199_ADDR          ((uint32_t)0x0018E000U)   /*!< Sector 199 */
#define EFM_SECTOR200_ADDR          ((uint32_t)0x00190000U)   /*!< Sector 200 */
#define EFM_SECTOR201_ADDR          ((uint32_t)0x00192000U)   /*!< Sector 201 */
#define EFM_SECTOR202_ADDR          ((uint32_t)0x00194000U)   /*!< Sector 202 */
#define EFM_SECTOR203_ADDR          ((uint32_t)0x00196000U)   /*!< Sector 203 */
#define EFM_SECTOR204_ADDR          ((uint32_t)0x00198000U)   /*!< Sector 204 */
#define EFM_SECTOR205_ADDR          ((uint32_t)0x0019A000U)   /*!< Sector 205 */
#define EFM_SECTOR206_ADDR          ((uint32_t)0x0019C000U)   /*!< Sector 206 */
#define EFM_SECTOR207_ADDR          ((uint32_t)0x0019E000U)   /*!< Sector 207 */
#define EFM_SECTOR208_ADDR          ((uint32_t)0x001A0000U)   /*!< Sector 208 */
#define EFM_SECTOR209_ADDR          ((uint32_t)0x001A2000U)   /*!< Sector 209 */
#define EFM_SECTOR210_ADDR          ((uint32_t)0x001A4000U)   /*!< Sector 210 */
#define EFM_SECTOR211_ADDR          ((uint32_t)0x001A6000U)   /*!< Sector 211 */
#define EFM_SECTOR212_ADDR          ((uint32_t)0x001A8000U)   /*!< Sector 212 */
#define EFM_SECTOR213_ADDR          ((uint32_t)0x001AA000U)   /*!< Sector 213 */
#define EFM_SECTOR214_ADDR          ((uint32_t)0x001AC000U)   /*!< Sector 214 */
#define EFM_SECTOR215_ADDR          ((uint32_t)0x001AE000U)   /*!< Sector 215 */
#define EFM_SECTOR216_ADDR          ((uint32_t)0x001B0000U)   /*!< Sector 216 */
#define EFM_SECTOR217_ADDR          ((uint32_t)0x001B2000U)   /*!< Sector 217 */
#define EFM_SECTOR218_ADDR          ((uint32_t)0x001B4000U)   /*!< Sector 218 */
#define EFM_SECTOR219_ADDR          ((uint32_t)0x001B6000U)   /*!< Sector 219 */
#define EFM_SECTOR220_ADDR          ((uint32_t)0x001B8000U)   /*!< Sector 220 */
#define EFM_SECTOR221_ADDR          ((uint32_t)0x001BA000U)   /*!< Sector 221 */
#define EFM_SECTOR222_ADDR          ((uint32_t)0x001BC000U)   /*!< Sector 222 */
#define EFM_SECTOR223_ADDR          ((uint32_t)0x001BE000U)   /*!< Sector 223 */
#define EFM_SECTOR224_ADDR          ((uint32_t)0x001C0000U)   /*!< Sector 224 */
#define EFM_SECTOR225_ADDR          ((uint32_t)0x001C2000U)   /*!< Sector 225 */
#define EFM_SECTOR226_ADDR          ((uint32_t)0x001C4000U)   /*!< Sector 226 */
#define EFM_SECTOR227_ADDR          ((uint32_t)0x001C6000U)   /*!< Sector 227 */
#define EFM_SECTOR228_ADDR          ((uint32_t)0x001C8000U)   /*!< Sector 228 */
#define EFM_SECTOR229_ADDR          ((uint32_t)0x001CA000U)   /*!< Sector 229 */
#define EFM_SECTOR230_ADDR          ((uint32_t)0x001CC000U)   /*!< Sector 230 */
#define EFM_SECTOR231_ADDR          ((uint32_t)0x001CE000U)   /*!< Sector 231 */
#define EFM_SECTOR232_ADDR          ((uint32_t)0x001D0000U)   /*!< Sector 232 */
#define EFM_SECTOR233_ADDR          ((uint32_t)0x001D2000U)   /*!< Sector 233 */
#define EFM_SECTOR234_ADDR          ((uint32_t)0x001D4000U)   /*!< Sector 234 */
#define EFM_SECTOR235_ADDR          ((uint32_t)0x001D6000U)   /*!< Sector 235 */
#define EFM_SECTOR236_ADDR          ((uint32_t)0x001D8000U)   /*!< Sector 236 */
#define EFM_SECTOR237_ADDR          ((uint32_t)0x001DA000U)   /*!< Sector 237 */
#define EFM_SECTOR238_ADDR          ((uint32_t)0x001DC000U)   /*!< Sector 238 */
#define EFM_SECTOR239_ADDR          ((uint32_t)0x001DE000U)   /*!< Sector 239 */
#define EFM_SECTOR240_ADDR          ((uint32_t)0x001E0000U)   /*!< Sector 240 */
#define EFM_SECTOR241_ADDR          ((uint32_t)0x001E2000U)   /*!< Sector 241 */
#define EFM_SECTOR242_ADDR          ((uint32_t)0x001E4000U)   /*!< Sector 242 */
#define EFM_SECTOR243_ADDR          ((uint32_t)0x001E6000U)   /*!< Sector 243 */
#define EFM_SECTOR244_ADDR          ((uint32_t)0x001E8000U)   /*!< Sector 244 */
#define EFM_SECTOR245_ADDR          ((uint32_t)0x001EA000U)   /*!< Sector 245 */
#define EFM_SECTOR246_ADDR          ((uint32_t)0x001EC000U)   /*!< Sector 246 */
#define EFM_SECTOR247_ADDR          ((uint32_t)0x001EE000U)   /*!< Sector 247 */
#define EFM_SECTOR248_ADDR          ((uint32_t)0x001F0000U)   /*!< Sector 248 */
#define EFM_SECTOR249_ADDR          ((uint32_t)0x001F2000U)   /*!< Sector 249 */
#define EFM_SECTOR250_ADDR          ((uint32_t)0x001F4000U)   /*!< Sector 250 */
#define EFM_SECTOR251_ADDR          ((uint32_t)0x001F6000U)   /*!< Sector 251 */
#define EFM_SECTOR252_ADDR          ((uint32_t)0x001F8000U)   /*!< Sector 252 */
#define EFM_SECTOR253_ADDR          ((uint32_t)0x001FA000U)   /*!< Sector 253 */
#define EFM_SECTOR254_ADDR          ((uint32_t)0x001FC000U)   /*!< Sector 254 */
#define EFM_SECTOR255_ADDR          ((uint32_t)0x001FE000U)   /*!< Sector 255 */
/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle 
 * @{
 */
#define EFM_WAIT_CYCLE_0                   ((uint32_t)0U)   /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE_1                   ((uint32_t)1U)   /*!< Insert 1 read wait cycle     */
#define EFM_WAIT_CYCLE_2                   ((uint32_t)2U)   /*!< Insert 2 read wait cycles    */
#define EFM_WAIT_CYCLE_3                   ((uint32_t)3U)   /*!< Insert 3 read wait cycles    */
#define EFM_WAIT_CYCLE_4                   ((uint32_t)4U)   /*!< Insert 4 read wait cycles    */
#define EFM_WAIT_CYCLE_5                   ((uint32_t)5U)   /*!< Insert 5 read wait cycles    */
#define EFM_WAIT_CYCLE_6                   ((uint32_t)6U)   /*!< Insert 6 read wait cycles    */
#define EFM_WAIT_CYCLE_7                   ((uint32_t)7U)   /*!< Insert 7 read wait cycles    */
#define EFM_WAIT_CYCLE_8                   ((uint32_t)8U)   /*!< Insert 8 read wait cycles    */
#define EFM_WAIT_CYCLE_9                   ((uint32_t)9U)   /*!< Insert 9 read wait cycles    */
#define EFM_WAIT_CYCLE_10                  ((uint32_t)10U)  /*!< Insert 10 read wait cycles   */
#define EFM_WAIT_CYCLE_11                  ((uint32_t)11U)  /*!< Insert 11 read wait cycles   */
#define EFM_WAIT_CYCLE_12                  ((uint32_t)12U)  /*!< Insert 12 read wait cycles   */
#define EFM_WAIT_CYCLE_13                  ((uint32_t)13U)  /*!< Insert 13 read wait cycles   */
#define EFM_WAIT_CYCLE_14                  ((uint32_t)14U)  /*!< Insert 14 read wait cycles   */
#define EFM_WAIT_CYCLE_15                  ((uint32_t)15U)  /*!< Insert 15 read wait cycles   */
/**
 * @}
 */

/**
 * @defgroup EFM_CacheRst_Func EFM data cache reset function
 * @{
 */
#define EFM_CACHERST_ON             (EFM_FRMC_CRST)        /*!< Enable data cache reset function */
#define EFM_CACHERST_OFF            ((uint32_t)0x00000000UL) /*!< Disable data cache reset function */
/**
 * @}
 */

/**
 * @defgroup EFM_Prefetch_Func EFM prefetch function
 * @{
 */
#define EFM_PREFETCH_ON             (EFM_FRMC_PREFE)        /*!< Enable prefetch function */
#define EFM_PREFETCH_OFF            ((uint32_t)0x00000000UL) /*!< Disable prefetch function */
/**
 * @}
 */

/**
 * @defgroup EFM_DCache_Func EFM data cache function
 * @{
 */
#define EFM_DATACACHE_ON            (EFM_FRMC_DCACHE)       /*!< Enable data cache function */
#define EFM_DATACACHE_OFF           ((uint32_t)0x00000000UL) /*!< Disable data cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_INSCache_Func EFM instruction cache function
 * @{
 */
#define EFM_INSCACHE_ON             (EFM_FRMC_ICACHE)       /*!< Enable instruction cache function */
#define EFM_INSCACHE_OFF            ((uint32_t)0x00000000UL) /*!< Disable instruction cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_LowVolRead_Mode EFM read of low-voltage mode
 * @{
 */
#define EFM_LOWVOLREAD_ON           (EFM_FRMC_LVM)          /*!< Read of low-voltage mode */
#define EFM_LOWVOLREAD_OFF          ((uint32_t)0x00000000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key2Lock_State EFM key2 lock state
 * @{
 */
#define EFM_KEY2_LOCK               (EFM_FWMC_KEY2LOCK)
#define EFM_KEY2_UNLOCK             ((uint32_t)0x00000000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key1Lock_State EFM key1 lock state
 * @{
 */
#define EFM_KEY1_LOCK               (EFM_FWMC_KEY1LOCK)
#define EFM_KEY1_UNLOCK             ((uint32_t)0x00000000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Bus_State EFM Bus state while flash program or erase
 * @{
 */
#define EFM_BUS_BUSY                ((uint32_t)0x00000000UL) /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE             (EFM_FWMC_BUSHLDCTL)    /*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_Mode_definition EFM program or erase mode definition
 * @{
 */
#define EFM_MODE_PROGRAMSINGLE      ((uint32_t)0x00000001UL)         /*!< Program single mode          */
#define EFM_MODE_PROGRAMREADBACK    ((uint32_t)0x00000002UL)         /*!< Program and read back mode   */
#define EFM_MODE_PROGRAMSEQUENCE    ((uint32_t)0x00000003UL)         /*!< Program sequence mode        */
#define EFM_MODE_ERASESECTOR        ((uint32_t)0x00000004UL)         /*!< Sector erase mode            */
#define EFM_MODE_ERASECHIP1         ((uint32_t)0x00000005UL)         /*!< A flash Chip erase mode      */
#define EFM_MODE_ERASECHIP2         ((uint32_t)0x00000006UL)         /*!< Two flash Chip erase mode    */
#define EFM_MODE_READONLY           ((uint32_t)0x00000000UL)         /*!< Read only mode               */
#define EFM_MODE_READONLY1          ((uint32_t)0x00000007UL)         /*!< Read only mode               */    
/**
 * @}
 */

/**
 * @defgroup EFM_Flag_definition EFM Flag definition
 * @{
 */
#define EFM_FLAG_OTPWERR0           (EFM_FSR_OTPWERR0)       /*!< EFM Flash0 otp Programming/erase error flag.       */
#define EFM_FLAG_PRTWERR0           (EFM_FSR_PRTWERR0)       /*!< EFM Flash0 write protect address error flag.       */
#define EFM_FLAG_PGSZERR0           (EFM_FSR_PGSZERR0)       /*!< EFM Flash0 programming size error flag.            */
#define EFM_FLAG_MISMTCH0           (EFM_FSR_MISMTCH0)       /*!< EFM Flash0 programming missing match error flag.   */
#define EFM_FLAG_OPTEND0            (EFM_FSR_OPTEND0)        /*!< EFM Flash0 end of operation flag.                  */
#define EFM_FLAG_CLOLERR0           (EFM_FSR_COLERR0)        /*!< EFM Flash0 read collide error flag.                */
#define EFM_FLAG_RDY0               (EFM_FSR_RDY0)           /*!< EFM Flash0 ready flag.                             */
#define EFM_FLAG_PRTWERR1           (EFM_FSR_PRTWERR1)       /*!< EFM Flash1 write protect address error flag.       */
#define EFM_FLAG_PGSZERR1           (EFM_FSR_PGSZERR1)       /*!< EFM Flash1 programming size error flag.            */
#define EFM_FLAG_MISMTCH1           (EFM_FSR_MISMTCH1)       /*!< EFM Flash1 programming missing match error flag.   */
#define EFM_FLAG_OPTEND1            (EFM_FSR_OPTEND1)        /*!< EFM Flash1 end of operation flag.                  */
#define EFM_FLAG_CLOLERR1           (EFM_FSR_COLERR1)        /*!< EFM Flash1 read collide error flag.                */
#define EFM_FLAG_RDY1               (EFM_FSR_RDY1)           /*!< EFM Flash1 ready flag.                             */

#define EFM_FLAG_CLR_OTPWERR0       (EFM_FSCLR_OTPWERRCLR0)  /*!< EFM Clear Flash0 otp Programming/erase error flag. */
#define EFM_FLAG_CLR_PRTWERR0       (EFM_FSCLR_PRTWERRCLR0)  /*!< EFM Clear Flash0 write protect address error flag. */
#define EFM_FLAG_CLR_PGSZERR0       (EFM_FSCLR_PGSZERRCLR0)  /*!< EFM Clear Flash0 programming size error flag.      */
#define EFM_FLAG_CLR_MISMTCH0       (EFM_FSCLR_MISMTCHCLR0)  /*!< EFM Clear Flash0 programming miss match error flag.*/
#define EFM_FLAG_CLR_OPTEND0        (EFM_FSCLR_OPTENDCLR0)   /*!< EFM Clear Flash0 end of operation flag.            */
#define EFM_FLAG_CLR_CLOLERR0       (EFM_FSCLR_COLERRCLR0)   /*!< EFM Clear Flash0 read collide error flag.          */
#define EFM_FLAG_CLR_PRTWERR1       (EFM_FSCLR_PRTWERRCLR1)  /*!< EFM Clear Flash1 write protect address error flag. */
#define EFM_FLAG_CLR_PGSZERR1       (EFM_FSCLR_PGSZERRCLR1)  /*!< EFM Clear Flash1 programming size error flag.      */
#define EFM_FLAG_CLR_MISMTCH1       (EFM_FSCLR_MISMTCHCLR1)  /*!< EFM Clear Flash1 programming miss match error flag.*/
#define EFM_FLAG_CLR_OPTEND1        (EFM_FSCLR_OPTENDCLR1)   /*!< EFM Clear Flash1 end of operation flag.            */
#define EFM_FLAG_CLR_CLOLERR1       (EFM_FSCLR_COLERRCLR1)   /*!< EFM Clear Flash1 read collide error flag.          */
/**
 * @}
 */

/**
 * @defgroup EFM_Interrupt_definition EFM Interrupt definition
 * @{
 */
#define EFM_INT_PEERR               (EFM_FITE_PEERRITE)      /*!< Program/erase error Interrupt source    */
#define EFM_INT_OPTEND              (EFM_FITE_OPTENDITE)     /*!< End of EFM operation Interrupt source   */
#define EFM_INT_RDCOLERR            (EFM_FITE_COLERRITE)     /*!< Read collide error Interrupt source     */
#define EFM_INT_PEERR_OPTEND        (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_OPTENDITE)      /*!< Program/erase error and End of EFM operation */
#define EFM_INT_PEERR_RDCOLERR      (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_COLERRITE)      /*!< Program/erase error and Read collide error*/
#define EFM_INT_OPTEND_RDCOLERR     (EFM_FITE_OPTENDITE |  \
                                    EFM_FITE_COLERRITE)      /*!< End of EFM operation and Read collide error*/
#define EFM_INT_ALL                 (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_OPTENDITE  |  \
                                    EFM_FITE_COLERRITE)      /*!< Program/erase error and End of EFM operation \
                                                                  and Read collide error Interrupt source */
/**
 * @}
 */

/**
 * @defgroup EFM_WriteLock_Definition EFM Write protect lock definition
 * @{
 */
#define EFM_WRLOCK0                  (EFM_WLOCK_WLOCK0)       /*!< F0NWPRT0 controlled sector lock   */
#define EFM_WRLOCK1                  (EFM_WLOCK_WLOCK1)       /*!< F0NWPRT1 controlled sector lock   */
#define EFM_WRLOCK2                  (EFM_WLOCK_WLOCK2)       /*!< F0NWPRT2 controlled sector lock   */
#define EFM_WRLOCK3                  (EFM_WLOCK_WLOCK3)       /*!< F0NWPRT3 controlled sector lock   */
#define EFM_WRLOCK4                  (EFM_WLOCK_WLOCK4)       /*!< F1NWPRT0 controlled sector lock   */
#define EFM_WRLOCK5                  (EFM_WLOCK_WLOCK5)       /*!< F1NWPRT1 controlled sector lock   */
#define EFM_WRLOCK6                  (EFM_WLOCK_WLOCK6)       /*!< F1NWPRT2 controlled sector lock   */
#define EFM_WRLOCK7                  (EFM_WLOCK_WLOCK7)       /*!< F1NWPRT3 controlled sector lock   */
/**
 * @}
 */


/**
 * @defgroup EFM_Keys EFM Keys
 * @{
 */
#define EFM_SECRET_KEY1              ((uint16_t)0x0123U)
#define EFM_SECRET_KEY2              ((uint16_t)0x3210U)
/**
 * @}
 */

/**
 * @defgroup EFM_Status EFM Status
 * @{
 */
#define EFM_F0ACT_F1ACT             ((uint32_t)0x00000000UL)    /*!< Flash 0 and 1 Enable */
#define EFM_F0STP_F1ACT             ((uint32_t)0x00000001UL)    /*!< Flash 0 Disable, Flash 1 Enable*/
#define EFM_F0ACT_F1STP             ((uint32_t)0x00000002UL)    /*!< Flash 0 Enable ,Flash 1 Disable */
#define EFM_F0STP_F1STP             ((uint32_t)0x00000003UL)    /*!< Flash 0 and 1 Disable */
/**
 * @}
 */

/**
 * @defgroup EFM_ProtectReg_definition EFM Write protect for register definition 
 * @{
 */
#define EFM_PROTECT_FWMC            ((uint8_t)0U)
#define EFM_PROTECT_OTP             ((uint8_t)1U)

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
 * @addtogroup EFM_Global_Functions
 * @{
 */

void EFM_Unlock(void);
void EFM_Lock(void);
void EFM_KEYRegWriteUnlock(uint8_t u8ProtectReg);
void EFM_KEYRegWriteLock(uint8_t u8ProtectReg);

void EFM_Cmd(uint32_t efmstate);
void EFM_SetLatency(uint32_t u32Latency);
void EFM_SetBusState(uint32_t u32State);
void EFM_DataCacheCmd(en_functional_state_t enNewState);
void EFM_InsCacheCmd(en_functional_state_t enNewState);
void EFM_DataCacheRstCmd(en_functional_state_t enNewState);
void EFM_PrefetchCmd(en_functional_state_t enNewState);
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_SectorRegLock(uint32_t u32EfmRegLock);
void EFM_SetOperateMode(uint32_t u32PeMode);
void EFM_ClearFlag(uint32_t u32Flag);
en_result_t EFM_StrucInit(stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_SectorUnlock(uint32_t u32StartAddr, uint32_t u32DataSize,
                                      en_functional_state_t enNewState);
en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramReadBack(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, const uint8_t *u32pBuf);
en_result_t EFM_SectorErase(uint32_t u32Addr);
en_result_t EFM_OTPLock(uint32_t Addr);
en_result_t EFM_ChipErase(uint32_t EraseMode, uint32_t Addr);

en_flag_status_t EFM_GetFlagStatus(uint32_t u32Flag);
stc_efm_unique_id_t EFM_GetUID(void);
uint32_t GetUniqueLogo(void);
/**
 * @}
 */

#endif /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
