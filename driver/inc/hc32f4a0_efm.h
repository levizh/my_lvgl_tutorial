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

    uint32_t            u32BusStatus;   /*!< Specifies the bus status busy or release while program & erase.
                                            This parameter can be a value of @ref EFM_Bus_Status.           */

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
#define EFM_TIMEOUT                  (0x2000UL)
#define EFM_SWITCH_ADDR              (0x03002000UL)
#define EFM_SWITCH_DATA              (0x005A5A5AUL)
/**
 * @defgroup EFM_Address EFM address area
 * @{
 */
#define EFM_START_ADDR               (0x00000000UL)   /*!< Flash start address */
#define EFM_END_ADDR                 (0x001FFFFFUL)   /*!< Flash end address */
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_SECTOR0_ADDR            (0x00000000UL)   /*!< Sector 0 */
#define EFM_SECTOR1_ADDR            (0x00002000UL)   /*!< Sector 1 */
#define EFM_SECTOR2_ADDR            (0x00004000UL)   /*!< Sector 2 */
#define EFM_SECTOR3_ADDR            (0x00006000UL)   /*!< Sector 3 */
#define EFM_SECTOR4_ADDR            (0x00008000UL)   /*!< Sector 4 */
#define EFM_SECTOR5_ADDR            (0x0000A000UL)   /*!< Sector 5 */
#define EFM_SECTOR6_ADDR            (0x0000C000UL)   /*!< Sector 6 */
#define EFM_SECTOR7_ADDR            (0x0000E000UL)   /*!< Sector 7 */
#define EFM_SECTOR8_ADDR            (0x00010000UL)   /*!< Sector 8 */
#define EFM_SECTOR9_ADDR            (0x00012000UL)   /*!< Sector 9 */
#define EFM_SECTOR10_ADDR           (0x00014000UL)   /*!< Sector 10 */
#define EFM_SECTOR11_ADDR           (0x00016000UL)   /*!< Sector 11 */
#define EFM_SECTOR12_ADDR           (0x00018000UL)   /*!< Sector 12 */
#define EFM_SECTOR13_ADDR           (0x0001A000UL)   /*!< Sector 13 */
#define EFM_SECTOR14_ADDR           (0x0001C000UL)   /*!< Sector 14 */
#define EFM_SECTOR15_ADDR           (0x0001E000UL)   /*!< Sector 15 */
#define EFM_SECTOR16_ADDR           (0x00020000UL)   /*!< Sector 16 */
#define EFM_SECTOR17_ADDR           (0x00022000UL)   /*!< Sector 17 */
#define EFM_SECTOR18_ADDR           (0x00024000UL)   /*!< Sector 18 */
#define EFM_SECTOR19_ADDR           (0x00026000UL)   /*!< Sector 19 */
#define EFM_SECTOR20_ADDR           (0x00028000UL)   /*!< Sector 20 */
#define EFM_SECTOR21_ADDR           (0x0002A000UL)   /*!< Sector 21 */
#define EFM_SECTOR22_ADDR           (0x0002C000UL)   /*!< Sector 22 */
#define EFM_SECTOR23_ADDR           (0x0002E000UL)   /*!< Sector 23 */
#define EFM_SECTOR24_ADDR           (0x00030000UL)   /*!< Sector 24 */
#define EFM_SECTOR25_ADDR           (0x00032000UL)   /*!< Sector 25 */
#define EFM_SECTOR26_ADDR           (0x00034000UL)   /*!< Sector 26 */
#define EFM_SECTOR27_ADDR           (0x00036000UL)   /*!< Sector 27 */
#define EFM_SECTOR28_ADDR           (0x00038000UL)   /*!< Sector 28 */
#define EFM_SECTOR29_ADDR           (0x0003A000UL)   /*!< Sector 29 */
#define EFM_SECTOR30_ADDR           (0x0003C000UL)   /*!< Sector 30 */
#define EFM_SECTOR31_ADDR           (0x0003E000UL)   /*!< Sector 31 */
#define EFM_SECTOR32_ADDR           (0x00040000UL)   /*!< Sector 32 */
#define EFM_SECTOR33_ADDR           (0x00042000UL)   /*!< Sector 33 */
#define EFM_SECTOR34_ADDR           (0x00044000UL)   /*!< Sector 34 */
#define EFM_SECTOR35_ADDR           (0x00046000UL)   /*!< Sector 35 */
#define EFM_SECTOR36_ADDR           (0x00048000UL)   /*!< Sector 36 */
#define EFM_SECTOR37_ADDR           (0x0004A000UL)   /*!< Sector 37 */
#define EFM_SECTOR38_ADDR           (0x0004C000UL)   /*!< Sector 38 */
#define EFM_SECTOR39_ADDR           (0x0004E000UL)   /*!< Sector 39 */
#define EFM_SECTOR40_ADDR           (0x00050000UL)   /*!< Sector 40 */
#define EFM_SECTOR41_ADDR           (0x00052000UL)   /*!< Sector 41 */
#define EFM_SECTOR42_ADDR           (0x00054000UL)   /*!< Sector 42 */
#define EFM_SECTOR43_ADDR           (0x00056000UL)   /*!< Sector 43 */
#define EFM_SECTOR44_ADDR           (0x00058000UL)   /*!< Sector 44 */
#define EFM_SECTOR45_ADDR           (0x0005A000UL)   /*!< Sector 45 */
#define EFM_SECTOR46_ADDR           (0x0005C000UL)   /*!< Sector 46 */
#define EFM_SECTOR47_ADDR           (0x0005E000UL)   /*!< Sector 47 */
#define EFM_SECTOR48_ADDR           (0x00060000UL)   /*!< Sector 48 */
#define EFM_SECTOR49_ADDR           (0x00062000UL)   /*!< Sector 49 */
#define EFM_SECTOR50_ADDR           (0x00064000UL)   /*!< Sector 50 */
#define EFM_SECTOR51_ADDR           (0x00066000UL)   /*!< Sector 51 */
#define EFM_SECTOR52_ADDR           (0x00068000UL)   /*!< Sector 52 */
#define EFM_SECTOR53_ADDR           (0x0006A000UL)   /*!< Sector 53 */
#define EFM_SECTOR54_ADDR           (0x0006C000UL)   /*!< Sector 54 */
#define EFM_SECTOR55_ADDR           (0x0006E000UL)   /*!< Sector 55 */
#define EFM_SECTOR56_ADDR           (0x00070000UL)   /*!< Sector 56 */
#define EFM_SECTOR57_ADDR           (0x00072000UL)   /*!< Sector 57 */
#define EFM_SECTOR58_ADDR           (0x00074000UL)   /*!< Sector 58 */
#define EFM_SECTOR59_ADDR           (0x00076000UL)   /*!< Sector 59 */
#define EFM_SECTOR60_ADDR           (0x00078000UL)   /*!< Sector 60 */
#define EFM_SECTOR61_ADDR           (0x0007A000UL)   /*!< Sector 61 */
#define EFM_SECTOR62_ADDR           (0x0007C000UL)   /*!< Sector 62 */
#define EFM_SECTOR63_ADDR           (0x0007E000UL)   /*!< Sector 63 */
#define EFM_SECTOR64_ADDR           (0x00080000UL)   /*!< Sector 64 */
#define EFM_SECTOR65_ADDR           (0x00082000UL)   /*!< Sector 65 */
#define EFM_SECTOR66_ADDR           (0x00084000UL)   /*!< Sector 66 */
#define EFM_SECTOR67_ADDR           (0x00086000UL)   /*!< Sector 67 */
#define EFM_SECTOR68_ADDR           (0x00088000UL)   /*!< Sector 68 */
#define EFM_SECTOR69_ADDR           (0x0008A000UL)   /*!< Sector 69 */
#define EFM_SECTOR70_ADDR           (0x0008C000UL)   /*!< Sector 70 */
#define EFM_SECTOR71_ADDR           (0x0008E000UL)   /*!< Sector 71 */
#define EFM_SECTOR72_ADDR           (0x00090000UL)   /*!< Sector 72 */
#define EFM_SECTOR73_ADDR           (0x00092000UL)   /*!< Sector 73 */
#define EFM_SECTOR74_ADDR           (0x00094000UL)   /*!< Sector 74 */
#define EFM_SECTOR75_ADDR           (0x00096000UL)   /*!< Sector 75 */
#define EFM_SECTOR76_ADDR           (0x00098000UL)   /*!< Sector 76 */
#define EFM_SECTOR77_ADDR           (0x0009A000UL)   /*!< Sector 77 */
#define EFM_SECTOR78_ADDR           (0x0009C000UL)   /*!< Sector 78 */
#define EFM_SECTOR79_ADDR           (0x0009E000UL)   /*!< Sector 79 */
#define EFM_SECTOR80_ADDR           (0x000A0000UL)   /*!< Sector 80 */
#define EFM_SECTOR81_ADDR           (0x000A2000UL)   /*!< Sector 81 */
#define EFM_SECTOR82_ADDR           (0x000A4000UL)   /*!< Sector 82 */
#define EFM_SECTOR83_ADDR           (0x000A6000UL)   /*!< Sector 83 */
#define EFM_SECTOR84_ADDR           (0x000A8000UL)   /*!< Sector 84 */
#define EFM_SECTOR85_ADDR           (0x000AA000UL)   /*!< Sector 85 */
#define EFM_SECTOR86_ADDR           (0x000AC000UL)   /*!< Sector 86 */
#define EFM_SECTOR87_ADDR           (0x000AE000UL)   /*!< Sector 87 */
#define EFM_SECTOR88_ADDR           (0x000B0000UL)   /*!< Sector 88 */
#define EFM_SECTOR89_ADDR           (0x000B2000UL)   /*!< Sector 89 */
#define EFM_SECTOR90_ADDR           (0x000B4000UL)   /*!< Sector 90 */
#define EFM_SECTOR91_ADDR           (0x000B6000UL)   /*!< Sector 91 */
#define EFM_SECTOR92_ADDR           (0x000B8000UL)   /*!< Sector 92 */
#define EFM_SECTOR93_ADDR           (0x000BA000UL)   /*!< Sector 93 */
#define EFM_SECTOR94_ADDR           (0x000BC000UL)   /*!< Sector 94 */
#define EFM_SECTOR95_ADDR           (0x000BE000UL)   /*!< Sector 95 */
#define EFM_SECTOR96_ADDR           (0x000C0000UL)   /*!< Sector 96 */
#define EFM_SECTOR97_ADDR           (0x000C2000UL)   /*!< Sector 97 */
#define EFM_SECTOR98_ADDR           (0x000C4000UL)   /*!< Sector 98 */
#define EFM_SECTOR99_ADDR           (0x000C6000UL)   /*!< Sector 99 */
#define EFM_SECTOR100_ADDR          (0x000C8000UL)   /*!< Sector 100 */
#define EFM_SECTOR101_ADDR          (0x000CA000UL)   /*!< Sector 101 */
#define EFM_SECTOR102_ADDR          (0x000CC000UL)   /*!< Sector 102 */
#define EFM_SECTOR103_ADDR          (0x000CE000UL)   /*!< Sector 103 */
#define EFM_SECTOR104_ADDR          (0x000D0000UL)   /*!< Sector 104 */
#define EFM_SECTOR105_ADDR          (0x000D2000UL)   /*!< Sector 105 */
#define EFM_SECTOR106_ADDR          (0x000D4000UL)   /*!< Sector 106 */
#define EFM_SECTOR107_ADDR          (0x000D6000UL)   /*!< Sector 107 */
#define EFM_SECTOR108_ADDR          (0x000D8000UL)   /*!< Sector 108 */
#define EFM_SECTOR109_ADDR          (0x000DA000UL)   /*!< Sector 109 */
#define EFM_SECTOR110_ADDR          (0x000DC000UL)   /*!< Sector 110 */
#define EFM_SECTOR111_ADDR          (0x000DE000UL)   /*!< Sector 111 */
#define EFM_SECTOR112_ADDR          (0x000E0000UL)   /*!< Sector 112 */
#define EFM_SECTOR113_ADDR          (0x000E2000UL)   /*!< Sector 113 */
#define EFM_SECTOR114_ADDR          (0x000E4000UL)   /*!< Sector 114 */
#define EFM_SECTOR115_ADDR          (0x000E6000UL)   /*!< Sector 115 */
#define EFM_SECTOR116_ADDR          (0x000E8000UL)   /*!< Sector 116 */
#define EFM_SECTOR117_ADDR          (0x000EA000UL)   /*!< Sector 117 */
#define EFM_SECTOR118_ADDR          (0x000EC000UL)   /*!< Sector 118 */
#define EFM_SECTOR119_ADDR          (0x000EE000UL)   /*!< Sector 119 */
#define EFM_SECTOR120_ADDR          (0x000F0000UL)   /*!< Sector 120 */
#define EFM_SECTOR121_ADDR          (0x000F2000UL)   /*!< Sector 121 */
#define EFM_SECTOR122_ADDR          (0x000F4000UL)   /*!< Sector 122 */
#define EFM_SECTOR123_ADDR          (0x000F6000UL)   /*!< Sector 123 */
#define EFM_SECTOR124_ADDR          (0x000F8000UL)   /*!< Sector 124 */
#define EFM_SECTOR125_ADDR          (0x000FA000UL)   /*!< Sector 125 */
#define EFM_SECTOR126_ADDR          (0x000FC000UL)   /*!< Sector 126 */
#define EFM_SECTOR127_ADDR          (0x000FE000UL)   /*!< Sector 127 */
#define EFM_SECTOR128_ADDR          (0x00100000UL)   /*!< Sector 128 */
#define EFM_SECTOR129_ADDR          (0x00102000UL)   /*!< Sector 129 */
#define EFM_SECTOR130_ADDR          (0x00104000UL)   /*!< Sector 130 */
#define EFM_SECTOR131_ADDR          (0x00106000UL)   /*!< Sector 131 */
#define EFM_SECTOR132_ADDR          (0x00108000UL)   /*!< Sector 132 */
#define EFM_SECTOR133_ADDR          (0x0010A000UL)   /*!< Sector 133 */
#define EFM_SECTOR134_ADDR          (0x0010C000UL)   /*!< Sector 134 */
#define EFM_SECTOR135_ADDR          (0x0010E000UL)   /*!< Sector 135 */
#define EFM_SECTOR136_ADDR          (0x00110000UL)   /*!< Sector 136 */
#define EFM_SECTOR137_ADDR          (0x00112000UL)   /*!< Sector 137 */
#define EFM_SECTOR138_ADDR          (0x00114000UL)   /*!< Sector 138 */
#define EFM_SECTOR139_ADDR          (0x00116000UL)   /*!< Sector 139 */
#define EFM_SECTOR140_ADDR          (0x00118000UL)   /*!< Sector 140 */
#define EFM_SECTOR141_ADDR          (0x0011A000UL)   /*!< Sector 141 */
#define EFM_SECTOR142_ADDR          (0x0011C000UL)   /*!< Sector 142 */
#define EFM_SECTOR143_ADDR          (0x0011E000UL)   /*!< Sector 143 */
#define EFM_SECTOR144_ADDR          (0x00120000UL)   /*!< Sector 144 */
#define EFM_SECTOR145_ADDR          (0x00122000UL)   /*!< Sector 145 */
#define EFM_SECTOR146_ADDR          (0x00124000UL)   /*!< Sector 146 */
#define EFM_SECTOR147_ADDR          (0x00126000UL)   /*!< Sector 147 */
#define EFM_SECTOR148_ADDR          (0x00128000UL)   /*!< Sector 148 */
#define EFM_SECTOR149_ADDR          (0x0012A000UL)   /*!< Sector 149 */
#define EFM_SECTOR150_ADDR          (0x0012C000UL)   /*!< Sector 150 */
#define EFM_SECTOR151_ADDR          (0x0012E000UL)   /*!< Sector 151 */
#define EFM_SECTOR152_ADDR          (0x00130000UL)   /*!< Sector 152 */
#define EFM_SECTOR153_ADDR          (0x00132000UL)   /*!< Sector 153 */
#define EFM_SECTOR154_ADDR          (0x00134000UL)   /*!< Sector 154 */
#define EFM_SECTOR155_ADDR          (0x00136000UL)   /*!< Sector 155 */
#define EFM_SECTOR156_ADDR          (0x00138000UL)   /*!< Sector 156 */
#define EFM_SECTOR157_ADDR          (0x0013A000UL)   /*!< Sector 157 */
#define EFM_SECTOR158_ADDR          (0x0013C000UL)   /*!< Sector 158 */
#define EFM_SECTOR159_ADDR          (0x0013E000UL)   /*!< Sector 159 */
#define EFM_SECTOR160_ADDR          (0x00140000UL)   /*!< Sector 160 */
#define EFM_SECTOR161_ADDR          (0x00142000UL)   /*!< Sector 161 */
#define EFM_SECTOR162_ADDR          (0x00144000UL)   /*!< Sector 162 */
#define EFM_SECTOR163_ADDR          (0x00146000UL)   /*!< Sector 163 */
#define EFM_SECTOR164_ADDR          (0x00148000UL)   /*!< Sector 164 */
#define EFM_SECTOR165_ADDR          (0x0014A000UL)   /*!< Sector 165 */
#define EFM_SECTOR166_ADDR          (0x0014C000UL)   /*!< Sector 166 */
#define EFM_SECTOR167_ADDR          (0x0014E000UL)   /*!< Sector 167 */
#define EFM_SECTOR168_ADDR          (0x00150000UL)   /*!< Sector 168 */
#define EFM_SECTOR169_ADDR          (0x00152000UL)   /*!< Sector 169 */
#define EFM_SECTOR170_ADDR          (0x00154000UL)   /*!< Sector 170 */
#define EFM_SECTOR171_ADDR          (0x00156000UL)   /*!< Sector 171 */
#define EFM_SECTOR172_ADDR          (0x00158000UL)   /*!< Sector 172 */
#define EFM_SECTOR173_ADDR          (0x0015A000UL)   /*!< Sector 173 */
#define EFM_SECTOR174_ADDR          (0x0015C000UL)   /*!< Sector 174 */
#define EFM_SECTOR175_ADDR          (0x0015E000UL)   /*!< Sector 175 */
#define EFM_SECTOR176_ADDR          (0x00160000UL)   /*!< Sector 176 */
#define EFM_SECTOR177_ADDR          (0x00162000UL)   /*!< Sector 177 */
#define EFM_SECTOR178_ADDR          (0x00164000UL)   /*!< Sector 178 */
#define EFM_SECTOR179_ADDR          (0x00166000UL)   /*!< Sector 179 */
#define EFM_SECTOR180_ADDR          (0x00168000UL)   /*!< Sector 180 */
#define EFM_SECTOR181_ADDR          (0x0016A000UL)   /*!< Sector 181 */
#define EFM_SECTOR182_ADDR          (0x0016C000UL)   /*!< Sector 182 */
#define EFM_SECTOR183_ADDR          (0x0016E000UL)   /*!< Sector 183 */
#define EFM_SECTOR184_ADDR          (0x00170000UL)   /*!< Sector 184 */
#define EFM_SECTOR185_ADDR          (0x00172000UL)   /*!< Sector 185 */
#define EFM_SECTOR186_ADDR          (0x00174000UL)   /*!< Sector 186 */
#define EFM_SECTOR187_ADDR          (0x00176000UL)   /*!< Sector 187 */
#define EFM_SECTOR188_ADDR          (0x00178000UL)   /*!< Sector 188 */
#define EFM_SECTOR189_ADDR          (0x0017A000UL)   /*!< Sector 189 */
#define EFM_SECTOR190_ADDR          (0x0017C000UL)   /*!< Sector 190 */
#define EFM_SECTOR191_ADDR          (0x0017E000UL)   /*!< Sector 191 */
#define EFM_SECTOR192_ADDR          (0x00180000UL)   /*!< Sector 192 */
#define EFM_SECTOR193_ADDR          (0x00182000UL)   /*!< Sector 193 */
#define EFM_SECTOR194_ADDR          (0x00184000UL)   /*!< Sector 194 */
#define EFM_SECTOR195_ADDR          (0x00186000UL)   /*!< Sector 195 */
#define EFM_SECTOR196_ADDR          (0x00188000UL)   /*!< Sector 196 */
#define EFM_SECTOR197_ADDR          (0x0018A000UL)   /*!< Sector 197 */
#define EFM_SECTOR198_ADDR          (0x0018C000UL)   /*!< Sector 198 */
#define EFM_SECTOR199_ADDR          (0x0018E000UL)   /*!< Sector 199 */
#define EFM_SECTOR200_ADDR          (0x00190000UL)   /*!< Sector 200 */
#define EFM_SECTOR201_ADDR          (0x00192000UL)   /*!< Sector 201 */
#define EFM_SECTOR202_ADDR          (0x00194000UL)   /*!< Sector 202 */
#define EFM_SECTOR203_ADDR          (0x00196000UL)   /*!< Sector 203 */
#define EFM_SECTOR204_ADDR          (0x00198000UL)   /*!< Sector 204 */
#define EFM_SECTOR205_ADDR          (0x0019A000UL)   /*!< Sector 205 */
#define EFM_SECTOR206_ADDR          (0x0019C000UL)   /*!< Sector 206 */
#define EFM_SECTOR207_ADDR          (0x0019E000UL)   /*!< Sector 207 */
#define EFM_SECTOR208_ADDR          (0x001A0000UL)   /*!< Sector 208 */
#define EFM_SECTOR209_ADDR          (0x001A2000UL)   /*!< Sector 209 */
#define EFM_SECTOR210_ADDR          (0x001A4000UL)   /*!< Sector 210 */
#define EFM_SECTOR211_ADDR          (0x001A6000UL)   /*!< Sector 211 */
#define EFM_SECTOR212_ADDR          (0x001A8000UL)   /*!< Sector 212 */
#define EFM_SECTOR213_ADDR          (0x001AA000UL)   /*!< Sector 213 */
#define EFM_SECTOR214_ADDR          (0x001AC000UL)   /*!< Sector 214 */
#define EFM_SECTOR215_ADDR          (0x001AE000UL)   /*!< Sector 215 */
#define EFM_SECTOR216_ADDR          (0x001B0000UL)   /*!< Sector 216 */
#define EFM_SECTOR217_ADDR          (0x001B2000UL)   /*!< Sector 217 */
#define EFM_SECTOR218_ADDR          (0x001B4000UL)   /*!< Sector 218 */
#define EFM_SECTOR219_ADDR          (0x001B6000UL)   /*!< Sector 219 */
#define EFM_SECTOR220_ADDR          (0x001B8000UL)   /*!< Sector 220 */
#define EFM_SECTOR221_ADDR          (0x001BA000UL)   /*!< Sector 221 */
#define EFM_SECTOR222_ADDR          (0x001BC000UL)   /*!< Sector 222 */
#define EFM_SECTOR223_ADDR          (0x001BE000UL)   /*!< Sector 223 */
#define EFM_SECTOR224_ADDR          (0x001C0000UL)   /*!< Sector 224 */
#define EFM_SECTOR225_ADDR          (0x001C2000UL)   /*!< Sector 225 */
#define EFM_SECTOR226_ADDR          (0x001C4000UL)   /*!< Sector 226 */
#define EFM_SECTOR227_ADDR          (0x001C6000UL)   /*!< Sector 227 */
#define EFM_SECTOR228_ADDR          (0x001C8000UL)   /*!< Sector 228 */
#define EFM_SECTOR229_ADDR          (0x001CA000UL)   /*!< Sector 229 */
#define EFM_SECTOR230_ADDR          (0x001CC000UL)   /*!< Sector 230 */
#define EFM_SECTOR231_ADDR          (0x001CE000UL)   /*!< Sector 231 */
#define EFM_SECTOR232_ADDR          (0x001D0000UL)   /*!< Sector 232 */
#define EFM_SECTOR233_ADDR          (0x001D2000UL)   /*!< Sector 233 */
#define EFM_SECTOR234_ADDR          (0x001D4000UL)   /*!< Sector 234 */
#define EFM_SECTOR235_ADDR          (0x001D6000UL)   /*!< Sector 235 */
#define EFM_SECTOR236_ADDR          (0x001D8000UL)   /*!< Sector 236 */
#define EFM_SECTOR237_ADDR          (0x001DA000UL)   /*!< Sector 237 */
#define EFM_SECTOR238_ADDR          (0x001DC000UL)   /*!< Sector 238 */
#define EFM_SECTOR239_ADDR          (0x001DE000UL)   /*!< Sector 239 */
#define EFM_SECTOR240_ADDR          (0x001E0000UL)   /*!< Sector 240 */
#define EFM_SECTOR241_ADDR          (0x001E2000UL)   /*!< Sector 241 */
#define EFM_SECTOR242_ADDR          (0x001E4000UL)   /*!< Sector 242 */
#define EFM_SECTOR243_ADDR          (0x001E6000UL)   /*!< Sector 243 */
#define EFM_SECTOR244_ADDR          (0x001E8000UL)   /*!< Sector 244 */
#define EFM_SECTOR245_ADDR          (0x001EA000UL)   /*!< Sector 245 */
#define EFM_SECTOR246_ADDR          (0x001EC000UL)   /*!< Sector 246 */
#define EFM_SECTOR247_ADDR          (0x001EE000UL)   /*!< Sector 247 */
#define EFM_SECTOR248_ADDR          (0x001F0000UL)   /*!< Sector 248 */
#define EFM_SECTOR249_ADDR          (0x001F2000UL)   /*!< Sector 249 */
#define EFM_SECTOR250_ADDR          (0x001F4000UL)   /*!< Sector 250 */
#define EFM_SECTOR251_ADDR          (0x001F6000UL)   /*!< Sector 251 */
#define EFM_SECTOR252_ADDR          (0x001F8000UL)   /*!< Sector 252 */
#define EFM_SECTOR253_ADDR          (0x001FA000UL)   /*!< Sector 253 */
#define EFM_SECTOR254_ADDR          (0x001FC000UL)   /*!< Sector 254 */
#define EFM_SECTOR255_ADDR          (0x001FE000UL)   /*!< Sector 255 */
/**
 * @}
 */

/**
 * @defgroup EFM_OTP_Address EFM otp address
 * @{
 */
#define EFM_OTP_BLOCK0              (0x00000000UL)   /*!< OTP block0   8K Bytes */
#define EFM_OTP_BLOCK1              (0x00002000UL)   /*!< OTP block1   8K Bytes */
#define EFM_OTP_BLOCK2              (0x00004000UL)   /*!< OTP block2   8K Bytes */
#define EFM_OTP_BLOCK3              (0x00006000UL)   /*!< OTP block3   8K Bytes */
#define EFM_OTP_BLOCK4              (0x00008000UL)   /*!< OTP block4   8K Bytes */
#define EFM_OTP_BLOCK5              (0x0000A000UL)   /*!< OTP block5   8K Bytes */
#define EFM_OTP_BLOCK6              (0x0000C000UL)   /*!< OTP block6   8K Bytes */
#define EFM_OTP_BLOCK7              (0x0000E000UL)   /*!< OTP block7   8K Bytes */
#define EFM_OTP_BLOCK8              (0x00010000UL)   /*!< OTP block8   8K Bytes */
#define EFM_OTP_BLOCK9              (0x00012000UL)   /*!< OTP block9   8K Bytes */
#define EFM_OTP_BLOCK10             (0x00014000UL)   /*!< OTP block10  8K Bytes */
#define EFM_OTP_BLOCK11             (0x00016000UL)   /*!< OTP block11  8K Bytes */
#define EFM_OTP_BLOCK12             (0x00018000UL)   /*!< OTP block12  8K Bytes */
#define EFM_OTP_BLOCK13             (0x0001A000UL)   /*!< OTP block13  8K Bytes */
#define EFM_OTP_BLOCK14             (0x0001C000UL)   /*!< OTP block14  8K Bytes */
#define EFM_OTP_BLOCK15             (0x0001E000UL)   /*!< OTP block15  8K Bytes */

#define EFM_OTP_BLOCK16             (0x03000000UL)   /*!< OTP block16  2K Bytes */
#define EFM_OTP_BLOCK17             (0x03000800UL)   /*!< OTP block17  2K Bytes */

#define EFM_OTP_BLOCK18             (0x03001000UL)   /*!< OTP block18  256 Bytes */
#define EFM_OTP_BLOCK19             (0x03001100UL)   /*!< OTP block19  256 Bytes */
#define EFM_OTP_BLOCK20             (0x03001200UL)   /*!< OTP block20  256 Bytes */
#define EFM_OTP_BLOCK21             (0x03001300UL)   /*!< OTP block21  256 Bytes */

#define EFM_OTP_BLOCK22             (0x03001400UL)   /*!< OTP block22  16 Bytes */
#define EFM_OTP_BLOCK23             (0x03001410UL)   /*!< OTP block23  16 Bytes */
#define EFM_OTP_BLOCK24             (0x03001420UL)   /*!< OTP block24  16 Bytes */
#define EFM_OTP_BLOCK25             (0x03001430UL)   /*!< OTP block25  16 Bytes */
#define EFM_OTP_BLOCK26             (0x03001440UL)   /*!< OTP block26  16 Bytes */
#define EFM_OTP_BLOCK27             (0x03001450UL)   /*!< OTP block27  16 Bytes */
#define EFM_OTP_BLOCK28             (0x03001460UL)   /*!< OTP block28  16 Bytes */
#define EFM_OTP_BLOCK29             (0x03001470UL)   /*!< OTP block29  16 Bytes */
#define EFM_OTP_BLOCK30             (0x03001480UL)   /*!< OTP block30  16 Bytes */
#define EFM_OTP_BLOCK31             (0x03001490UL)   /*!< OTP block31  16 Bytes */
#define EFM_OTP_BLOCK32             (0x030014A0UL)   /*!< OTP block32  16 Bytes */
#define EFM_OTP_BLOCK33             (0x030014B0UL)   /*!< OTP block33  16 Bytes */
#define EFM_OTP_BLOCK34             (0x030014C0UL)   /*!< OTP block34  16 Bytes */
#define EFM_OTP_BLOCK35             (0x030014D0UL)   /*!< OTP block35  16 Bytes */
#define EFM_OTP_BLOCK36             (0x030014E0UL)   /*!< OTP block36  16 Bytes */
#define EFM_OTP_BLOCK37             (0x030014F0UL)   /*!< OTP block37  16 Bytes */
#define EFM_OTP_BLOCK38             (0x03001500UL)   /*!< OTP block38  16 Bytes */
#define EFM_OTP_BLOCK39             (0x03001510UL)   /*!< OTP block39  16 Bytes */
#define EFM_OTP_BLOCK40             (0x03001520UL)   /*!< OTP block40  16 Bytes */
#define EFM_OTP_BLOCK41             (0x03001530UL)   /*!< OTP block41  16 Bytes */
#define EFM_OTP_BLOCK42             (0x03001540UL)   /*!< OTP block42  16 Bytes */
#define EFM_OTP_BLOCK43             (0x03001550UL)   /*!< OTP block43  16 Bytes */
#define EFM_OTP_BLOCK44             (0x03001560UL)   /*!< OTP block44  16 Bytes */
#define EFM_OTP_BLOCK45             (0x03001570UL)   /*!< OTP block45  16 Bytes */
#define EFM_OTP_BLOCK46             (0x03001580UL)   /*!< OTP block46  16 Bytes */
#define EFM_OTP_BLOCK47             (0x03001590UL)   /*!< OTP block47  16 Bytes */
#define EFM_OTP_BLOCK48             (0x030015A0UL)   /*!< OTP block48  16 Bytes */
#define EFM_OTP_BLOCK49             (0x030015B0UL)   /*!< OTP block49  16 Bytes */
#define EFM_OTP_BLOCK50             (0x030015C0UL)   /*!< OTP block50  16 Bytes */
#define EFM_OTP_BLOCK51             (0x030015D0UL)   /*!< OTP block51  16 Bytes */
#define EFM_OTP_BLOCK52             (0x030015E0UL)   /*!< OTP block52  16 Bytes */
#define EFM_OTP_BLOCK53             (0x030015F0UL)   /*!< OTP block53  16 Bytes */

#define EFM_OTP_BLOCK54             (0x03001600UL)   /*!< OTP block54  4 Bytes */
#define EFM_OTP_BLOCK55             (0x03001604UL)   /*!< OTP block55  4 Bytes */
#define EFM_OTP_BLOCK56             (0x03001608UL)   /*!< OTP block56  4 Bytes */
#define EFM_OTP_BLOCK57             (0x0300160CUL)   /*!< OTP block57  4 Bytes */
#define EFM_OTP_BLOCK58             (0x03001610UL)   /*!< OTP block58  4 Bytes */
#define EFM_OTP_BLOCK59             (0x03001614UL)   /*!< OTP block59  4 Bytes */
#define EFM_OTP_BLOCK60             (0x03001618UL)   /*!< OTP block60  4 Bytes */
#define EFM_OTP_BLOCK61             (0x0300161CUL)   /*!< OTP block61  4 Bytes */
#define EFM_OTP_BLOCK62             (0x03001620UL)   /*!< OTP block62  4 Bytes */
#define EFM_OTP_BLOCK63             (0x03001624UL)   /*!< OTP block63  4 Bytes */
#define EFM_OTP_BLOCK64             (0x03001628UL)   /*!< OTP block64  4 Bytes */
#define EFM_OTP_BLOCK65             (0x0300162CUL)   /*!< OTP block65  4 Bytes */
#define EFM_OTP_BLOCK66             (0x03001630UL)   /*!< OTP block66  4 Bytes */
#define EFM_OTP_BLOCK67             (0x03001634UL)   /*!< OTP block67  4 Bytes */
#define EFM_OTP_BLOCK68             (0x03001638UL)   /*!< OTP block68  4 Bytes */
#define EFM_OTP_BLOCK69             (0x0300163CUL)   /*!< OTP block69  4 Bytes */
#define EFM_OTP_BLOCK70             (0x03001640UL)   /*!< OTP block70  4 Bytes */
#define EFM_OTP_BLOCK71             (0x03001644UL)   /*!< OTP block71  4 Bytes */
#define EFM_OTP_BLOCK72             (0x03001648UL)   /*!< OTP block72  4 Bytes */
#define EFM_OTP_BLOCK73             (0x0300164CUL)   /*!< OTP block73  4 Bytes */
#define EFM_OTP_BLOCK74             (0x03001650UL)   /*!< OTP block74  4 Bytes */
#define EFM_OTP_BLOCK75             (0x03001654UL)   /*!< OTP block75  4 Bytes */
#define EFM_OTP_BLOCK76             (0x03001658UL)   /*!< OTP block76  4 Bytes */
#define EFM_OTP_BLOCK77             (0x0300165CUL)   /*!< OTP block77  4 Bytes */
#define EFM_OTP_BLOCK78             (0x03001660UL)   /*!< OTP block78  4 Bytes */
#define EFM_OTP_BLOCK79             (0x03001664UL)   /*!< OTP block79  4 Bytes */
#define EFM_OTP_BLOCK80             (0x03001668UL)   /*!< OTP block80  4 Bytes */
#define EFM_OTP_BLOCK81             (0x0300166CUL)   /*!< OTP block81  4 Bytes */
#define EFM_OTP_BLOCK82             (0x03001670UL)   /*!< OTP block82  4 Bytes */
#define EFM_OTP_BLOCK83             (0x03001674UL)   /*!< OTP block83  4 Bytes */
#define EFM_OTP_BLOCK84             (0x03001678UL)   /*!< OTP block84  4 Bytes */
#define EFM_OTP_BLOCK85             (0x0300167CUL)   /*!< OTP block85  4 Bytes */
#define EFM_OTP_BLOCK86             (0x03001680UL)   /*!< OTP block86  4 Bytes */
#define EFM_OTP_BLOCK87             (0x03001684UL)   /*!< OTP block87  4 Bytes */
#define EFM_OTP_BLOCK88             (0x03001688UL)   /*!< OTP block88  4 Bytes */
#define EFM_OTP_BLOCK89             (0x0300168CUL)   /*!< OTP block89  4 Bytes */
#define EFM_OTP_BLOCK90             (0x03001690UL)   /*!< OTP block90  4 Bytes */
#define EFM_OTP_BLOCK91             (0x03001694UL)   /*!< OTP block91  4 Bytes */
#define EFM_OTP_BLOCK92             (0x03001698UL)   /*!< OTP block92  4 Bytes */
#define EFM_OTP_BLOCK93             (0x0300169CUL)   /*!< OTP block93  4 Bytes */
#define EFM_OTP_BLOCK94             (0x030016A0UL)   /*!< OTP block94  4 Bytes */
#define EFM_OTP_BLOCK95             (0x030016A4UL)   /*!< OTP block95  4 Bytes */
#define EFM_OTP_BLOCK96             (0x030016A8UL)   /*!< OTP block96  4 Bytes */
#define EFM_OTP_BLOCK97             (0x030016ACUL)   /*!< OTP block97  4 Bytes */
#define EFM_OTP_BLOCK98             (0x030016B0UL)   /*!< OTP block98  4 Bytes */
#define EFM_OTP_BLOCK99             (0x030016B4UL)   /*!< OTP block99  4 Bytes */
#define EFM_OTP_BLOCK100            (0x030016B8UL)   /*!< OTP block100 4 Bytes */
#define EFM_OTP_BLOCK101            (0x030016BCUL)   /*!< OTP block101 4 Bytes */
#define EFM_OTP_BLOCK102            (0x030016C0UL)   /*!< OTP block102 4 Bytes */
#define EFM_OTP_BLOCK103            (0x030016C4UL)   /*!< OTP block103 4 Bytes */
#define EFM_OTP_BLOCK104            (0x030016C8UL)   /*!< OTP block104 4 Bytes */
#define EFM_OTP_BLOCK105            (0x030016CCUL)   /*!< OTP block105 4 Bytes */
#define EFM_OTP_BLOCK106            (0x030016D0UL)   /*!< OTP block106 4 Bytes */
#define EFM_OTP_BLOCK107            (0x030016D4UL)   /*!< OTP block107 4 Bytes */
#define EFM_OTP_BLOCK108            (0x030016D8UL)   /*!< OTP block108 4 Bytes */
#define EFM_OTP_BLOCK109            (0x030016DCUL)   /*!< OTP block109 4 Bytes */
#define EFM_OTP_BLOCK110            (0x030016E0UL)   /*!< OTP block110 4 Bytes */
#define EFM_OTP_BLOCK111            (0x030016E4UL)   /*!< OTP block111 4 Bytes */
#define EFM_OTP_BLOCK112            (0x030016E8UL)   /*!< OTP block112 4 Bytes */
#define EFM_OTP_BLOCK113            (0x030016ECUL)   /*!< OTP block113 4 Bytes */
#define EFM_OTP_BLOCK114            (0x030016F0UL)   /*!< OTP block114 4 Bytes */
#define EFM_OTP_BLOCK115            (0x030016F4UL)   /*!< OTP block115 4 Bytes */
#define EFM_OTP_BLOCK116            (0x030016F8UL)   /*!< OTP block116 4 Bytes */
#define EFM_OTP_BLOCK117            (0x030016FCUL)   /*!< OTP block117 4 Bytes */
#define EFM_OTP_BLOCK118            (0x03001700UL)   /*!< OTP block118 4 Bytes */
#define EFM_OTP_BLOCK119            (0x03001704UL)   /*!< OTP block119 4 Bytes */
#define EFM_OTP_BLOCK120            (0x03001708UL)   /*!< OTP block120 4 Bytes */
#define EFM_OTP_BLOCK121            (0x0300170CUL)   /*!< OTP block121 4 Bytes */
#define EFM_OTP_BLOCK122            (0x03001710UL)   /*!< OTP block122 4 Bytes */
#define EFM_OTP_BLOCK123            (0x03001714UL)   /*!< OTP block123 4 Bytes */
#define EFM_OTP_BLOCK124            (0x03001718UL)   /*!< OTP block124 4 Bytes */
#define EFM_OTP_BLOCK125            (0x0300171CUL)   /*!< OTP block125 4 Bytes */
#define EFM_OTP_BLOCK126            (0x03001720UL)   /*!< OTP block126 4 Bytes */
#define EFM_OTP_BLOCK127            (0x03001724UL)   /*!< OTP block127 4 Bytes */
#define EFM_OTP_BLOCK128            (0x03001728UL)   /*!< OTP block128 4 Bytes */
#define EFM_OTP_BLOCK129            (0x0300172CUL)   /*!< OTP block129 4 Bytes */
#define EFM_OTP_BLOCK130            (0x03001730UL)   /*!< OTP block130 4 Bytes */
#define EFM_OTP_BLOCK131            (0x03001734UL)   /*!< OTP block131 4 Bytes */
#define EFM_OTP_BLOCK132            (0x03001738UL)   /*!< OTP block132 4 Bytes */
#define EFM_OTP_BLOCK133            (0x0300173CUL)   /*!< OTP block133 4 Bytes */
#define EFM_OTP_BLOCK134            (0x03001740UL)   /*!< OTP block134 4 Bytes */
#define EFM_OTP_BLOCK135            (0x03001744UL)   /*!< OTP block135 4 Bytes */
#define EFM_OTP_BLOCK136            (0x03001748UL)   /*!< OTP block136 4 Bytes */
#define EFM_OTP_BLOCK137            (0x0300174CUL)   /*!< OTP block137 4 Bytes */
#define EFM_OTP_BLOCK138            (0x03001750UL)   /*!< OTP block138 4 Bytes */
#define EFM_OTP_BLOCK139            (0x03001754UL)   /*!< OTP block139 4 Bytes */
#define EFM_OTP_BLOCK140            (0x03001758UL)   /*!< OTP block140 4 Bytes */
#define EFM_OTP_BLOCK141            (0x0300175CUL)   /*!< OTP block141 4 Bytes */
#define EFM_OTP_BLOCK142            (0x03001760UL)   /*!< OTP block142 4 Bytes */
#define EFM_OTP_BLOCK143            (0x03001764UL)   /*!< OTP block143 4 Bytes */
#define EFM_OTP_BLOCK144            (0x03001768UL)   /*!< OTP block144 4 Bytes */
#define EFM_OTP_BLOCK145            (0x0300176CUL)   /*!< OTP block145 4 Bytes */
#define EFM_OTP_BLOCK146            (0x03001770UL)   /*!< OTP block146 4 Bytes */
#define EFM_OTP_BLOCK147            (0x03001774UL)   /*!< OTP block147 4 Bytes */
#define EFM_OTP_BLOCK148            (0x03001778UL)   /*!< OTP block148 4 Bytes */
#define EFM_OTP_BLOCK149            (0x0300177CUL)   /*!< OTP block149 4 Bytes */
#define EFM_OTP_BLOCK150            (0x03001780UL)   /*!< OTP block150 4 Bytes */
#define EFM_OTP_BLOCK151            (0x03001784UL)   /*!< OTP block151 4 Bytes */
#define EFM_OTP_BLOCK152            (0x03001788UL)   /*!< OTP block152 4 Bytes */
#define EFM_OTP_BLOCK153            (0x0300178CUL)   /*!< OTP block153 4 Bytes */
#define EFM_OTP_BLOCK154            (0x03001790UL)   /*!< OTP block154 4 Bytes */
#define EFM_OTP_BLOCK155            (0x03001794UL)   /*!< OTP block155 4 Bytes */
#define EFM_OTP_BLOCK156            (0x03001798UL)   /*!< OTP block156 4 Bytes */
#define EFM_OTP_BLOCK157            (0x0300179CUL)   /*!< OTP block157 4 Bytes */
#define EFM_OTP_BLOCK158            (0x030017A0UL)   /*!< OTP block158 4 Bytes */
#define EFM_OTP_BLOCK159            (0x030017A4UL)   /*!< OTP block159 4 Bytes */
#define EFM_OTP_BLOCK160            (0x030017A8UL)   /*!< OTP block160 4 Bytes */
#define EFM_OTP_BLOCK161            (0x030017ACUL)   /*!< OTP block161 4 Bytes */
#define EFM_OTP_BLOCK162            (0x030017B0UL)   /*!< OTP block162 4 Bytes */
#define EFM_OTP_BLOCK163            (0x030017B4UL)   /*!< OTP block163 4 Bytes */
#define EFM_OTP_BLOCK164            (0x030017B8UL)   /*!< OTP block164 4 Bytes */
#define EFM_OTP_BLOCK165            (0x030017BCUL)   /*!< OTP block165 4 Bytes */
#define EFM_OTP_BLOCK166            (0x030017C0UL)   /*!< OTP block166 4 Bytes */
#define EFM_OTP_BLOCK167            (0x030017C4UL)   /*!< OTP block167 4 Bytes */
#define EFM_OTP_BLOCK168            (0x030017C8UL)   /*!< OTP block168 4 Bytes */
#define EFM_OTP_BLOCK169            (0x030017CCUL)   /*!< OTP block169 4 Bytes */
#define EFM_OTP_BLOCK170            (0x030017D0UL)   /*!< OTP block170 4 Bytes */
#define EFM_OTP_BLOCK171            (0x030017D4UL)   /*!< OTP block171 4 Bytes */
#define EFM_OTP_BLOCK172            (0x030017D8UL)   /*!< OTP block172 4 Bytes */
#define EFM_OTP_BLOCK173            (0x030017DCUL)   /*!< OTP block173 4 Bytes */
#define EFM_OTP_BLOCK174            (0x030017E0UL)   /*!< OTP block174 4 Bytes */
#define EFM_OTP_BLOCK175            (0x030017E4UL)   /*!< OTP block175 4 Bytes */
#define EFM_OTP_BLOCK176            (0x030017E8UL)   /*!< OTP block176 4 Bytes */
#define EFM_OTP_BLOCK177            (0x030017ECUL)   /*!< OTP block177 4 Bytes */
#define EFM_OTP_BLOCK178            (0x030017F0UL)   /*!< OTP block178 4 Bytes */
#define EFM_OTP_BLOCK179            (0x030017F4UL)   /*!< OTP block179 4 Bytes */
#define EFM_OTP_BLOCK180            (0x030017F8UL)   /*!< OTP block180 4 Bytes */
#define EFM_OTP_BLOCK181            (0x030017FCUL)   /*!< OTP block181 4 Bytes */

/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle 
 * @{
 */
#define EFM_WAIT_CYCLE_0                   (0U)      /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE_1                   (1U)      /*!< Insert 1 read wait cycle     */
#define EFM_WAIT_CYCLE_2                   (2U)      /*!< Insert 2 read wait cycles    */
#define EFM_WAIT_CYCLE_3                   (3U)      /*!< Insert 3 read wait cycles    */
#define EFM_WAIT_CYCLE_4                   (4U)      /*!< Insert 4 read wait cycles    */
#define EFM_WAIT_CYCLE_5                   (5U)      /*!< Insert 5 read wait cycles    */
#define EFM_WAIT_CYCLE_6                   (6U)      /*!< Insert 6 read wait cycles    */
#define EFM_WAIT_CYCLE_7                   (7U)      /*!< Insert 7 read wait cycles    */
#define EFM_WAIT_CYCLE_8                   (8U)      /*!< Insert 8 read wait cycles    */
#define EFM_WAIT_CYCLE_9                   (9U)      /*!< Insert 9 read wait cycles    */
#define EFM_WAIT_CYCLE_10                  (10U)     /*!< Insert 10 read wait cycles   */
#define EFM_WAIT_CYCLE_11                  (11U)     /*!< Insert 11 read wait cycles   */
#define EFM_WAIT_CYCLE_12                  (12U)     /*!< Insert 12 read wait cycles   */
#define EFM_WAIT_CYCLE_13                  (13U)     /*!< Insert 13 read wait cycles   */
#define EFM_WAIT_CYCLE_14                  (14U)     /*!< Insert 14 read wait cycles   */
#define EFM_WAIT_CYCLE_15                  (15U)     /*!< Insert 15 read wait cycles   */
/**
 * @}
 */

/**
 * @defgroup EFM_CacheRst_Func EFM data cache reset function
 * @{
 */
#define EFM_CACHERST_ON             (EFM_FRMC_CRST)         /*!< Enable data cache reset function */
#define EFM_CACHERST_OFF            (0x0UL)                 /*!< Disable data cache reset function */
/**
 * @}
 */

/**
 * @defgroup EFM_Prefetch_Func EFM prefetch function
 * @{
 */
#define EFM_PREFETCH_ON             (EFM_FRMC_PREFE)        /*!< Enable prefetch function */
#define EFM_PREFETCH_OFF            (0x0UL)                 /*!< Disable prefetch function */
/**
 * @}
 */

/**
 * @defgroup EFM_DCache_Func EFM data cache function
 * @{
 */
#define EFM_DATACACHE_ON            (EFM_FRMC_DCACHE)       /*!< Enable data cache function */
#define EFM_DATACACHE_OFF           (0x0UL)                 /*!< Disable data cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_INSCache_Func EFM instruction cache function
 * @{
 */
#define EFM_INSCACHE_ON             (EFM_FRMC_ICACHE)       /*!< Enable instruction cache function */
#define EFM_INSCACHE_OFF            (0x0UL)                 /*!< Disable instruction cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_LowVolRead_Mode EFM read of low-voltage mode
 * @{
 */
#define EFM_LOWVOLREAD_ON           (EFM_FRMC_LVM)          /*!< Read of low-voltage mode */
#define EFM_LOWVOLREAD_OFF          (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key2Lock_Status EFM key2 lock status
 * @{
 */
#define EFM_KEY2_LOCK               (EFM_FWMC_KEY2LOCK)
#define EFM_KEY2_UNLOCK             (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Key1Lock_Status EFM key1 lock status
 * @{
 */
#define EFM_KEY1_LOCK               (EFM_FWMC_KEY1LOCK)
#define EFM_KEY1_UNLOCK             (0x0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Bus_Status EFM Bus status while flash program or erase
 * @{
 */
#define EFM_BUS_BUSY                (0x0UL)                  /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE             (EFM_FWMC_BUSHLDCTL)     /*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_Mode_definition EFM program or erase mode definition
 * @{
 */
#define EFM_MODE_PROGRAMSINGLE      (0x1UL)                  /*!< Program single mode          */
#define EFM_MODE_PROGRAMREADBACK    (0x2UL)                  /*!< Program and read back mode   */
#define EFM_MODE_PROGRAMSEQUENCE    (0x3UL)                  /*!< Program sequence mode        */
#define EFM_MODE_ERASESECTOR        (0x4UL)                  /*!< Sector erase mode            */
#define EFM_MODE_ERASECHIP1         (0x5UL)                  /*!< A flash Chip erase mode      */
#define EFM_MODE_ERASECHIP2         (0x6UL)                  /*!< Two flash Chip erase mode    */
#define EFM_MODE_READONLY           (0x0UL)                  /*!< Read only mode               */
#define EFM_MODE_READONLY1          (0x7UL)                  /*!< Read only mode               */
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
#define EFM_SECRET_KEY1              (0x0123U)
#define EFM_SECRET_KEY2              (0x3210U)
/**
 * @}
 */

/**
 * @defgroup EFM_Status EFM Status
 * @{
 */
#define EFM_F0ACT_F1ACT             (0x00000000UL)            /*!< Flash 0 and 1 Enable */
#define EFM_F0STP_F1ACT             (0x00000001UL)            /*!< Flash 0 Disable, Flash 1 Enable*/
#define EFM_F0ACT_F1STP             (0x00000002UL)            /*!< Flash 0 Enable ,Flash 1 Disable */
#define EFM_F0STP_F1STP             (0x00000003UL)            /*!< Flash 0 and 1 Disable */
/**
 * @}
 */

/**
 * @defgroup EFM_ProtectReg_definition EFM Write protect for register definition 
 * @{
 */
#define EFM_PROTECT_FWMC            (0U)
#define EFM_PROTECT_OTP             (1U)

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

void EFM_Cmd(uint32_t efmstatus);
void EFM_SetWaitCycle(uint32_t u32WaitCycle);
void EFM_SetBusStatus(uint32_t u32Status);
void EFM_DataCacheCmd(en_functional_state_t enNewState);
void EFM_InsCacheCmd(en_functional_state_t enNewState);
void EFM_DataCacheRstCmd(en_functional_state_t enNewState);
void EFM_PrefetchCmd(en_functional_state_t enNewState);
void EFM_SwitchCmd(en_functional_state_t enNewState);
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_SetLowVolRead(uint32_t u32EfmLowVolRead);
void EFM_SectorRegLock(uint32_t u32EfmRegLock);
void EFM_SetOperateMode(uint32_t u32PeMode);
void EFM_ClearFlag(uint32_t u32Flag);
en_result_t EFM_StrucInit(stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_SectorUnlock(uint32_t u32StartAddr, uint32_t u32DataSize,
                                      en_functional_state_t enNewState);
en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramReadBack(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, const uint8_t *u8pBuf);
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
