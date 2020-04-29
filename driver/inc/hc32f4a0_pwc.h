/**
 *******************************************************************************
 * @file  hc32f4a0_pwc.h
 * @brief This file contains all the functions prototypes of the PWC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-17       Zhangxl         First version
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
#ifndef __HC32F4A0_PWC_H__
#define __HC32F4A0_PWC_H__

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
 * @addtogroup DDL_PWC
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Types PWC Global Types
 * @{
 */

typedef struct stc_pwc_ram_config
{
    uint32_t u32RamCtrl;    /*!< Internal RAM power setting. */
    uint32_t u32PRamCtrl;   /*!< Peripheral RAM power setting. */
    uint16_t u16RamMode;    /*!< RAM setting for Operating mode, @ref PWC_RAM_config for details */
} stc_pwc_ram_config_t;

typedef struct stc_pwc_lvd_config
{
    uint8_t u8LvdEn;        /*!< LVD function setting, @ref PWC_LVD1_Config and @ref PWC_LVD2_Config for details */
    uint8_t u8Lvd2ExtInEn;  /*!< LVD2 ext. pin input function setting, @ref PWC_LVD2_ExtIn_Config */
    uint8_t u8LvdCmpOutEn;  /*!< LVD compare output function setting, @ref PWC_LVD1_CMP_Config and @ref PWC_LVD2_CMP_Config for details */
    uint8_t u8LvdIntRstSel; /*!< LVD interrupt or reset selection, @ref PWC_LVD1_IntRst_Sel nad @ref PWC_LVD3_IntRst_Sel for details */
    uint8_t u8LvdIntRstEn;  /*!< LVD interrupt or reset function setting, @ref PWC_LVD1_IR_Config and @ref PWC_LVD2_IR_Config for details */
    uint8_t u8FilterEn;     /*!< LVD digital filter function setting, @ref PWC_LVD1_DF_Config and @ref PWC_LVD2_DF_Config for details */
    uint8_t u8FilterClk;    /*!< LVD digital filter clock setting, @ref PWC_LVD1_DFS_Clk_Sel and @ref PWC_LVD2_DFS_Clk_Sel for details */
    uint8_t u8LvdVoltage;   /*!< LVD detect voltage setting, @ref PWC_LVD1_detection_Vol and @ref PWC_LVD2_detection_Vol for details */
    uint8_t u8LvdNmiEn;     /*!< LVD NMI function setting, @ref PWC_LVD1_Int_Mode_Config and @ref PWC_LVD2_Int_Mode_Config for details */
    uint8_t u8LvdTrigger;   /*!< LVD trigger setting, @ref PWC_LVD1_Trigger_Sel and @ref PWC_LVD2_Trigger_Sel for details */
} stc_pwc_lvd_config_t;

typedef struct stc_pwc_pd_mode_config
{
    uint8_t u8PDMode;       /*!< Power down mode, @ref PWC_PDMode_Sel for details. */
    uint8_t u8IOState;      /*!< IO state in power down mode, @ref PWC_PDMode_IO_Sel for details. */
    uint8_t u8WkUpSpeed;    /*!< Wakeup speed selection, @ref PWC_PDMode_WKUP_TIME_Sel for details. */
}stc_pwc_pd_mode_config_t;

typedef struct stc_pwc_stop_mode_config
{
    uint8_t u8StopDrv;      /*!< Stop mode drive capacity, @ref PWC_STOP_DRV_Sel for details. */
    uint16_t u16ExBusHold;  /*!< Exbus status in stop mode, @ref PWC_STOP_EXBUS_Sel for details. */
    uint16_t u16ClkKeep;    /*!< System clock setting after wake-up from stop mode,
                                 @ref PWC_STOP_CLK_Sel for details. */
    uint16_t u16FlashWait;  /*!< Waiting flash stable after wake-up from stop mode, 
                                 @ref STOP_FLASH_WAIT_Sel for details. */
} stc_pwc_stop_mode_config;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Macros PWC Global Macros
 * @{
 */

/**
 * @defgroup PWC_PDMode_Sel Power down mode selection
 * @{
 */
#define PWC_PD_MODE1                (uint8_t)(0x00U)        /*!< Power down mode 0 */
#define PWC_PD_MODE2                (uint8_t)(0x01U)        /*!< Power down mode 1 */
#define PWC_PD_MODE3                (uint8_t)(0x02U)        /*!< Power down mode 2 */
#define PWC_PD_MODE4                (uint8_t)(0x03U)        /*!< Power down mode 3 */
/**
 * @}
 */

/**
 * @defgroup PWC_PDMode_IO_Sel IO state config in Power down mode
 * @{
 */
#define PWC_PD_IO_STATE1            (uint8_t)(0x00U << PWC_PWRC0_IORTN_POS)   /*!< IO state retain in PD mode and configurable after wakeup */
#define PWC_PD_IO_STATE2            (uint8_t)(0x01U << PWC_PWRC0_IORTN_POS)   /*!< IO state retain in PD mode and configurable after wakeup & set IORTN[1:0]=00b */
#define PWC_PD_IO_STATE3            (uint8_t)(0x02U << PWC_PWRC0_IORTN_POS)   /*!< IO state swtich to HiZ */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_DRV_Sel Drive capacity while enter stop mode
 * @{
 */
#define PWC_STOP_DRV_HIGH           (uint8_t)(0x00U << PWC_PWRC1_STPDAS_POS)  /*!< Enter stop mode from high speed mode */
#define PWC_STOP_DRV_LOW            (uint8_t)(0x11U << PWC_PWRC1_STPDAS_POS)  /*!< Enter stop mode from ultra low speed mode */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_EXBUS_Sel ExBus status while enter stop mode
 * @{
 */
#define PWC_STOP_EXBUS_HIZ          (uint16_t)(0x00U)               /*!< Ex-Bus Hiz in stop mode */
#define PWC_STOP_EXBUS_HOLD         (uint16_t)(PWC_STPMCR_EXBUSOE)  /*!< Ex-Bus keep in stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_CLK_Sel System clock setting after wake-up from stop mode
 * @{
 */
#define PWC_STOP_CLK_KEEP           (uint16_t)(0x00U)               /*!< Keep System clock setting after wake-up from stop mode */
#define PWC_STOP_CLK_MRC            (uint16_t)(PWC_STPMCR_CKSMRC)   /*!< System clock switch to MRC after wake-up from stop mode */
/**
 * @}
 */

/**
 * @defgroup STOP_FLASH_WAIT_Sel Whether wait flash stable or not after wake-up from stop mode
 * @{
 */
#define PWC_STOP_FLASH_WAIT         (uint16_t)(0x00U)               /*!< Wait flash stable after wake-up from stop mode */
#define PWC_STOP_FLASH_NOWAIT       (uint16_t)(PWC_STPMCR_FLNWT)    /*!< Don't wait flash stable after wake-up from stop mode */
/**
 * @}
 */


/**
 * @defgroup PWC_PWR_DRV_Sel Drive capacity selection
 * @{
 */
#define PWC_NOR_DRV_HIGH            (uint8_t)(0x11U << PWC_PWRC2_DVS_POS)   /*!< Dirve capacity in high speed operation */
#define PWC_NOR_DRV_LOW             (uint8_t)(0x10U << PWC_PWRC2_DVS_POS)   /*!< Dirve capacity in ultra low speed operation */
/**
 * @}
 */

/**
 * @defgroup PWC_PDMode_WKUP_TIME_Sel IO state config in Power down mode
 * @{
 */
#define PWC_PD_WKUP_SLOW            (uint8_t)(0x00U)        /*!< VCAP1/VCAP2 = 0.1uF x2 or 0.22uF x1 */
#define PWC_PD_WKUP_FAST            (uint8_t)(0x01U)        /*!< VCAP1/VCAP2 = 0.047uF x2 or 0.1uF x1 */
/**
 * @}
 */

/**
 * @defgroup PWC_RAM_Config Operating mode for RAM Config
 * @{
 */
#define PWC_RAM_HIGH                (uint16_t)(0x8043U)     /*!< MCU operating under high frequncy (lower than 240MHz) */
#define PWC_RAM_LOW                 (uint16_t)(0x9062U)     /*!< MCU operating under ultra low frequncy (lower than 8MHz) */
/**
 * @}
 */

/**
 * @defgroup PWC_PWMON_Config PWC Power Monitor Config
 * @{
 */
#define PWC_PWRMON_ON                (PWC_PWRC_PWMONE)
#define PWC_PWRMON_OFF               (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PWMON_Sel PWC Power Monitor Selection
 * @{
 */
#define PWC_PWRMON_VINREF           (0x00U)                /*!< Internal reference voltage */
#define PWC_PWRMON_VOTS             (PWC_PWRC_PWMONSEL)   /*!< temperature sensor voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_DRV_Sel PWC Driver ability selection
 * @{
 */
#define PWC_DRV_LOW                 (0x00U)       /*!< system clock = 32kHz */
#define PWC_DRV_HIGH                (0x07U)       /*!< system clock < 48Mhz */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_Config PWC LVD1 Config
 * @{
 */
#define PWC_LVD1_ON         (uint8_t)(PWC_PVDCR0_PVD1EN)
#define PWC_LVD1_OFF        (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_Config PWC LVD2 Config
 * @{
 */
#define PWC_LVD2_ON         (uint8_t)(PWC_PVDCR0_PVD2EN)
#define PWC_LVD2_OFF        (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_ExtIn_Config PWC LVD2 external input Config
 * @{
 */
#define PWC_LVD2_EXINP_ON   (uint8_t)(PWC_PVDCR0_EXVCCINEN)
#define PWC_LVD2_EXINP_OFF  (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_IR_Config PWC LVD1 Interrupt/Reset Config
 * @{
 */
#define PWC_LVD1_IR_ON      (uint8_t)(PWC_PVDCR1_PVD1IRE)
#define PWC_LVD1_IR_OFF     (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_IR_Config PWC LVD2 Interrupt/Reset Config
 * @{
 */
#define PWC_LVD2_IR_ON      (uint8_t)(PWC_PVDCR1_PVD2IRE)
#define PWC_LVD2_IR_OFF     (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_IntRst_Sel set LVD1 to interrupt or reset
 * @{
 */
#define PWC_LVD1_INT        (uint8_t)(0x00U)
#define PWC_LVD1_RST        (uint8_t)(PWC_PVDCR1_PVD1IRS)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_IntRst_Sel set LVD2 to interrupt or reset
 * @{
 */
#define PWC_LVD2_INT        (uint8_t)(0x00U)
#define PWC_LVD2_RST        (uint8_t)(PWC_PVDCR1_PVD2IRS)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_CMP_Config PWC LVD1 Compare Config
 * @{
 */
#define PWC_LVD1_CMP_ON     (uint8_t)(PWC_PVDCR1_PVD1CMPOE)
#define PWC_LVD1_CMP_OFF    (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_CMP_Config PWC LVD2 Compare Config
 * @{
 */
#define PWC_LVD2_CMP_ON     (uint8_t)(PWC_PVDCR1_PVD2CMPOE)
#define PWC_LVD2_CMP_OFF    (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_DF_Config LVD digital filter ON or OFF
 * @{
 */
#define PWC_LVD1_DF_ON      (uint8_t)(0x0000U)
#define PWC_LVD1_DF_OFF     (uint8_t)(PWC_PVDFCR_PVD1NFDIS)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_DF_config LVD digital filter ON or OFF
 * @{
 */
#define PWC_LVD2_DF_ON      (uint8_t)(0x0000U)
#define PWC_LVD2_DF_OFF     (uint8_t)(PWC_PVDFCR_PVD2NFDIS)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_DFS_Clk_Sel LVD1 digital filter sample ability
 * @note     modified this value must when PWC_LVD1_DF_OFF
 * @{
 */
#define PWC_LVD1_DFS_DIV4   (uint8_t)(0x0000U)   /*!< 0.25 LRC cycle */
#define PWC_LVD1_DFS_DIV2   (uint8_t)(0x0001U)   /*!< 0.5 LRC cycle */
#define PWC_LVD1_DFS_DIV1   (uint8_t)(0x0002U)   /*!< 1 LRC cycle */
#define PWC_LVD1_DFS_MUL2   (uint8_t)(0x0003U)   /*!< 2 LRC cycles */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_DFS_Clk_Sel LVD2 digital filter sample ability
 * @note     modified this value must when PWC_LVD2_DF_OFF
 * @{
 */
#define PWC_LVD2_DFS_DIV4   (uint8_t)(uint8_t)(0x0000U << PWC_PVDFCR_PVD2NFCKS_POS)   /*!< 0.25 LRC cycle */
#define PWC_LVD2_DFS_DIV2   (uint8_t)(uint8_t)(0x0001U << PWC_PVDFCR_PVD2NFCKS_POS)   /*!< 0.5 LRC cycle */
#define PWC_LVD2_DFS_DIV1   (uint8_t)(uint8_t)(0x0002U << PWC_PVDFCR_PVD2NFCKS_POS)   /*!< 1 LRC cycle */
#define PWC_LVD2_DFS_MUL2   (uint8_t)(uint8_t)(0x0003U << PWC_PVDFCR_PVD2NFCKS_POS)   /*!< 2 LRC cycles */
/**
 * @}
 */


/**
 * @defgroup PWC_LVD1_detection_Vol PWC LVD1 Detection voltage
 * @{
 */
#define PWC_LVD1_2V0        (uint8_t)(0x00U)     /*!< Specifies the voltage to 2.0V. */
#define PWC_LVD1_2V1        (uint8_t)(0x01U)     /*!< Specifies the voltage to 2.1V. */
#define PWC_LVD1_2V3        (uint8_t)(0x02U)     /*!< Specifies the voltage to 2.3V. */
#define PWC_LVD1_2V5        (uint8_t)(0x03U)     /*!< Specifies the voltage to 2.5V. */
#define PWC_LVD1_2V6        (uint8_t)(0x04U)     /*!< Specifies the voltage to 2.6V. */
#define PWC_LVD1_2V7        (uint8_t)(0x05U)     /*!< Specifies the voltage to 2.7V. */
#define PWC_LVD1_2V8        (uint8_t)(0x06U)     /*!< Specifies the voltage to 2.8V. */
#define PWC_LVD1_2V9        (uint8_t)(0x07U)     /*!< Specifies the voltage to 2.9V. */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_detection_level PWC LVD2 Detection voltage
 * @{
 */
#define PWC_LVD2_2V1        (uint8_t)(0x00U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.0V. */
#define PWC_LVD2_2V3        (uint8_t)(0x01U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.1V. */
#define PWC_LVD2_2V5        (uint8_t)(0x02U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.3V. */
#define PWC_LVD2_2V6        (uint8_t)(0x03U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.5V. */
#define PWC_LVD2_2V7        (uint8_t)(0x04U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.6V. */
#define PWC_LVD2_2V8        (uint8_t)(0x05U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.7V. */
#define PWC_LVD2_2V9        (uint8_t)(0x06U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 2.8V. */
#define PWC_LVD2_1V1        (uint8_t)(0x07U << PWC_PVDLCR_PVD2LVL_POS)     /*!< Specifies the voltage to 1.1V (only ext. input). */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_Int_Mode_Config LVD1 interrupt set to maskable or non_maskable
 * @{
 */
#define PWC_LVD1_INT_MASK       (uint8_t)(PWC_PVDICR_PVD1NMIS)
#define PWC_LVD1_INT_NONMASK    (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_Int_Mode_Config LVD2 interrupt set to maskable or non_maskable
 * @{
 */
#define PWC_LVD2_INT_MASK       (uint8_t)(PWC_PVDICR_PVD2NMIS)
#define PWC_LVD2_INT_NONMASK    (uint8_t)(0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD1_Trigger_Sel LVD1 trigger setting
 * @{
 */
#define PWC_LVD1_TRIGGER_FALLING    (uint8_t)(0x00U << PWC_PVDICR_PVD1EDGS_POS)
#define PWC_LVD1_TRIGGER_RISING     (uint8_t)(0x01U << PWC_PVDICR_PVD1EDGS_POS)
#define PWC_LVD1_TRIGGER_BOTH       (uint8_t)(0x02U << PWC_PVDICR_PVD1EDGS_POS)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD2_Trigger_Sel LVD2 trigger setting
 * @{
 */
#define PWC_LVD2_TRIGGER_FALLING    (uint8_t)(0x00U << PWC_PVDICR_PVD2EDGS_POS)
#define PWC_LVD2_TRIGGER_RISING     (uint8_t)(0x01U << PWC_PVDICR_PVD2EDGS_POS)
#define PWC_LVD2_TRIGGER_BOTH       (uint8_t)(0x02U << PWC_PVDICR_PVD2EDGS_POS)
/**
 * @}
 */

/**
 * @defgroup PWC_WKIP_Event_Sel Power down mode event selection
 * @{
 */
#define PWC_PD_WKUP_LVD1            (uint8_t)PWC_PDWKES_VD1EGS
#define PWC_PD_WKUP_LVD2            (uint8_t)PWC_PDWKES_VD2EGS
#define PWC_PD_WKUP_WKP0            (uint8_t)PWC_PDWKES_WK0EGS
#define PWC_PD_WKUP_WKP1            (uint8_t)PWC_PDWKES_WK1EGS
#define PWC_PD_WKUP_WKP2            (uint8_t)PWC_PDWKES_WK2EGS
#define PWC_PD_WKUP_WKP3            (uint8_t)PWC_PDWKES_WK3EGS

/**
 * @defgroup PWC_WKUP_Trigger_Edge_Sel Power down mode wakeup trigger edge selection
 * @{
 */
#define PWC_PD_WKUP_FALLING         (uint8_t)(0x00U)
#define PWC_PD_WKUP_RISING          (uint8_t)(0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_DBGC_config PWC Debug Config
 * @{
 */
#define PWC_AD_INTERN_REF           (uint8_t)(0x00U)
#define PWC_AD_VBAT_DIV2            (uint8_t)(0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_VBAT_Voltage_Status PWC VBAT Voltage Status
 * @{
 */
#define PWC_VOL_VBAT_MORE_THAN_VBATREF        (uint8_t)(0x00U)  /*!< Vbat > VbatREF */
#define PWC_VOL_VBAT_LESS_THAN_VBATREF        (uint8_t)(0x01U)  /*!< Vbat < VbatREF */
/**
 * @}
 */

/**
 * @defgroup PWC_VBAT_Reference_Voltage PWC VBAT Reference Voltage
 * @{
 */
#define PWC_VBAT_REF_VOL_1P8V                 (uint8_t)(0x00U)  /*!< Vbat reference voltage is 1.8V */
#define PWC_VBAT_REF_VOL_2P0V                 (uint8_t)(0x01U)  /*!< Vbat reference voltage is 2.0V */
/**
 * @}
 */

/**
 * @defgroup PWC_BACKUP_RAM_Flag PWC Backup RAM Flag
 * @{
 */
#define PWC_BACKUP_RAM_FLAG_RAMPDF            (PWC_VBATCR_RAMPDF)     /*!< Backup RAM power down flag */
#define PWC_BACKUP_RAM_FLAG_RAMVALID          (PWC_VBATCR_RAMVALID)   /*!< Backup RAM read/write flag */
/**
 * @}
 */

/**
 * @defgroup PWC_WKT_Clock_Source PWC WKT Clock Source
 * @{
 */
#define PWC_WKT_CLK_SRC_64HZ                  (0U)                  /*!< 64Hz Clock   */
#define PWC_WKT_CLK_SRC_XTAL32                (PWC_WKTC2_WKCKS_0)   /*!< XTAL32 Clock */
#define PWC_WKT_CLK_SRC_RTCLRC                (PWC_WKTC2_WKCKS_1)   /*!< RTCLRC Clock    */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup PWC_REG_Write_Configuration PWC register write Configuration
 * @{
 */
#define PWC_FCG0_WRITE_ENABLE()         (M4_PWC->FCG0PC = 0xA5A50001UL)
#define PWC_FCG0_WRITE_DISABLE()        (M4_PWC->FCG0PC = 0xA5A50000UL)

#define PWC_REG_WRITE_ENABLE()          (M4_PWC->FPRC |= 0xA502U)
#define PWC_REG_WRITE_DISABLE()         (M4_PWC->FPRC = (0xA500U | (M4_PWC->FPRC & (uint16_t)(~2U))))

#define PWC_LVD_REG_WRITE_ENABLE()      (M4_PWC->FPRC |= 0xA508U)
#define PWC_LVD_REG_WRITE_DISABLE()     (M4_PWC->FPRC = (0xA500U | (M4_PWC->FPRC & (uint16_t)(~8U))))

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
 * @addtogroup PWC_Global_Functions
 * @{
 */
en_result_t PWC_PowerDownStructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig);
en_result_t PWC_PowerDownConfig(const stc_pwc_pd_mode_config_t *pstcPDModeConfig);
void PWC_EnterPowerDownMode(void);
void PWC_EnterStopMode(void);
void PWC_EnterSleepMode(void);

en_result_t PWC_StopStructInit(stc_pwc_stop_mode_config *pstcStopConfig);
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_config *pstcStopConfig);
void PWC_StopDrvConfig(uint8_t u8StopDrv);
void PWC_StopClockKeepConfig(uint16_t u16ClkKeep);
void PWC_StopFlashWaitConfig(uint16_t u16FlashWait);
void PWC_StopExBusHoldConfig(uint16_t u16ExBusHold);

void PWC_HighSpeedToLowSpeed(void);
void PWC_LowSpeedToHighSpeed(void);

void PWC_HrcPwrCmd(en_functional_state_t enNewState);
void PWC_PllAPwrCmd(en_functional_state_t enNewState);
void PWC_PllHPwrCmd(en_functional_state_t enNewState);

void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState);
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState);
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState);
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState);

en_result_t PWC_RamConfig(const stc_pwc_ram_config_t *pstcRamConfig);
en_result_t PWC_LVD_Init(const stc_pwc_lvd_config_t *pstcLvdConfig);
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_config_t *pstcLvdConfig);
en_flag_status_t PWC_LVD_GetFlag(uint8_t u8Flag);
void PWC_LVD_ClrFlag(uint8_t u8Flag);

void PWC_PdWakeup0Cmd(uint8_t u8Wkup0Evt, en_functional_state_t enNewState);
void PWC_PdWakeup1Cmd(uint8_t u8Wkup1Evt, en_functional_state_t enNewState);
void PWC_PdWakeup2Cmd(uint8_t u8Wkup2Evt, en_functional_state_t enNewState);
void PWC_PdWakeupTrigConfig(uint8_t u8WkupEvt, uint8_t u8TrigEdge);
en_flag_status_t PWC_GetWakeup0Flag(uint8_t u8Flag);
en_flag_status_t PWC_GetWakeup1Flag(uint8_t u8Flag);

void PWC_AdcBufCmd(en_functional_state_t enNewState);
void PWC_AdcInternVolSel(uint8_t u8AdcInternVol);

void PWC_VBAT_MonitorVolSel(uint8_t u8RefVol);
void PWC_VBAT_MonitorCmd(en_functional_state_t enNewState);
uint8_t PWC_VBAT_GetVolStatus(void);
void PWC_VBAT_VolMeasureCmd(en_functional_state_t enNewState);
void PWC_VBAT_Reset(void);
void PWC_VBAT_PwrCmd(en_functional_state_t enNewState);

void PWC_BkRamPwrCmd(en_functional_state_t enNewState);
en_flag_status_t PWC_GetBkRamFlag(uint8_t u8Flag);
void PWC_WriteBackupReg(uint8_t u8RegNum, uint8_t u8RegVal);
uint8_t PWC_ReadBackupReg(uint8_t u8RegNum);

void PWC_WKT_Init(uint8_t u8ClkSrc, uint16_t u16CmpVal);
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal);
uint16_t PWC_WKT_GetCompareValue(void);
void PWC_WKT_Cmd(en_functional_state_t enNewState);
en_flag_status_t PWC_WKT_GetFlag(void);
void PWC_WKT_ClearFlag(void);

/**
 * @}
 */

#endif /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
