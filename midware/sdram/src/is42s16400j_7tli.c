/**
 *******************************************************************************
 * @file  is42s16400j_7tli.c
 * @brief This midware file provides firmware functions to manage the SDRAM 
 *        midware library for is42s16400j_7tli.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_clk.h"
#include "hc32f4a0_gpio.h"
#include "hc32f4a0_pwc.h"
#include "hc32f4a0_utility.h"

#include "is42s16400j_7tli.h"

/**
 * @addtogroup HC32F4A0_DDL_Midware
 * @{
 */

/**
 * @defgroup MW_SDRAM SDRAM
 * @brief SDRAM Midware Library
 * @{
 */

#if (MW_SDRAM_IS42S16400J7TLI_ENABLE == DDL_ON)

#if (DDL_CLK_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_CLK_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_DMC_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_DMC_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_GPIO_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_GPIO_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_PWC_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_PWC_ENABLE to DDL_ON in ddl_config.h"
#endif

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IS42S16400J_Local_Macros IS42S16400J Local Macros
 * @{
 */

/**
 * @defgroup DMC_Interface_Pin DMC Interface Pin
 * @{
 */
#define DMC_CKE_PORT                            (GPIO_PORT_B)   /* PB5 - EXMC_ALE */
#define DMC_CKE_PIN                             (GPIO_PIN_05)

#define DMC_CLK_PORT                            (GPIO_PORT_D)   /* PD3 - EXMC_CLK */
#define DMC_CLK_PIN                             (GPIO_PIN_03)

#define DMC_DQM0_PORT                           (GPIO_PORT_E)   /* PE0 - EXMC_CE4 */
#define DMC_DQM0_PIN                            (GPIO_PIN_00)
#define DMC_DQM1_PORT                           (GPIO_PORT_E)   /* PE1 - EXMC_CE5 */
#define DMC_DQM1_PIN                            (GPIO_PIN_01)

#define DMC_BA0_PORT                            (GPIO_PORT_D)   /* PD11 - EXMC_ADD16 */
#define DMC_BA0_PIN                             (GPIO_PIN_11)
#define DMC_BA1_PORT                            (GPIO_PORT_D)   /* PD12 - EXMC_ADD17 */
#define DMC_BA1_PIN                             (GPIO_PIN_12)

#define DMC_CS1_PORT                            (GPIO_PORT_G)   /* PG9 - EXMC_CE1 */
#define DMC_CS1_PIN                             (GPIO_PIN_09)

#define DMC_RAS_PORT                            (GPIO_PORT_D)   /* PD4 - EXMC_OE */
#define DMC_RAS_PIN                             (GPIO_PIN_04)

#define DMC_CAS_PORT                            (GPIO_PORT_G)   /* PG15 - EXMC_BAA */
#define DMC_CAS_PIN                             (GPIO_PIN_15)

#define DMC_WE_PORT                             (GPIO_PORT_D)   /* PD5 - EXMC_WE */
#define DMC_WE_PIN                              (GPIO_PIN_05)

#define DMC_ADD0_PORT                           (GPIO_PORT_F)   /* PF0 - EXMC_ADD0 */
#define DMC_ADD0_PIN                            (GPIO_PIN_00)
#define DMC_ADD1_PORT                           (GPIO_PORT_F)   /* PF1 - EXMC_ADD1 */
#define DMC_ADD1_PIN                            (GPIO_PIN_01)
#define DMC_ADD2_PORT                           (GPIO_PORT_F)   /* PF2 - EXMC_ADD2 */
#define DMC_ADD2_PIN                            (GPIO_PIN_02)
#define DMC_ADD3_PORT                           (GPIO_PORT_F)   /* PF3 - EXMC_ADD3 */
#define DMC_ADD3_PIN                            (GPIO_PIN_03)
#define DMC_ADD4_PORT                           (GPIO_PORT_F)   /* PF4 - EXMC_ADD4 */
#define DMC_ADD4_PIN                            (GPIO_PIN_04)
#define DMC_ADD5_PORT                           (GPIO_PORT_F)   /* PF5 - EXMC_ADD5 */
#define DMC_ADD5_PIN                            (GPIO_PIN_05)
#define DMC_ADD6_PORT                           (GPIO_PORT_F)   /* PF12 - EXMC_ADD6 */
#define DMC_ADD6_PIN                            (GPIO_PIN_12)
#define DMC_ADD7_PORT                           (GPIO_PORT_F)   /* PF13 - EXMC_ADD7 */
#define DMC_ADD7_PIN                            (GPIO_PIN_13)
#define DMC_ADD8_PORT                           (GPIO_PORT_F)   /* PF14 - EXMC_ADD8 */
#define DMC_ADD8_PIN                            (GPIO_PIN_14)
#define DMC_ADD9_PORT                           (GPIO_PORT_F)   /* PF15 - EXMC_ADD9 */
#define DMC_ADD9_PIN                            (GPIO_PIN_15)
#define DMC_ADD10_PORT                          (GPIO_PORT_G)   /* PG0 - EXMC_ADD10 */
#define DMC_ADD10_PIN                           (GPIO_PIN_00)
#define DMC_ADD11_PORT                          (GPIO_PORT_G)   /* PG1 - EXMC_ADD11 */
#define DMC_ADD11_PIN                           (GPIO_PIN_01)

#define DMC_DATA0_PORT                          (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define DMC_DATA0_PIN                           (GPIO_PIN_14)
#define DMC_DATA1_PORT                          (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define DMC_DATA1_PIN                           (GPIO_PIN_15)
#define DMC_DATA2_PORT                          (GPIO_PORT_D)   /* PD0 - EXMC_DATA2 */
#define DMC_DATA2_PIN                           (GPIO_PIN_00)
#define DMC_DATA3_PORT                          (GPIO_PORT_D)   /* PD1 - EXMC_DATA3 */
#define DMC_DATA3_PIN                           (GPIO_PIN_01)
#define DMC_DATA4_PORT                          (GPIO_PORT_E)   /* PE7 - EXMC_DATA4 */
#define DMC_DATA4_PIN                           (GPIO_PIN_07)
#define DMC_DATA5_PORT                          (GPIO_PORT_E)   /* PE8 - EXMC_DATA5 */
#define DMC_DATA5_PIN                           (GPIO_PIN_08)
#define DMC_DATA6_PORT                          (GPIO_PORT_E)   /* PE9 - EXMC_DATA6 */
#define DMC_DATA6_PIN                           (GPIO_PIN_09)
#define DMC_DATA7_PORT                          (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define DMC_DATA7_PIN                           (GPIO_PIN_10)
#define DMC_DATA8_PORT                          (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define DMC_DATA8_PIN                           (GPIO_PIN_11)
#define DMC_DATA9_PORT                          (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define DMC_DATA9_PIN                           (GPIO_PIN_12)
#define DMC_DATA10_PORT                         (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define DMC_DATA10_PIN                          (GPIO_PIN_13)
#define DMC_DATA11_PORT                         (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define DMC_DATA11_PIN                          (GPIO_PIN_14)
#define DMC_DATA12_PORT                         (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define DMC_DATA12_PIN                          (GPIO_PIN_15)
#define DMC_DATA13_PORT                         (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define DMC_DATA13_PIN                          (GPIO_PIN_08)
#define DMC_DATA14_PORT                         (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define DMC_DATA14_PIN                          (GPIO_PIN_09)
#define DMC_DATA15_PORT                         (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define DMC_DATA15_PIN                          (GPIO_PIN_10)
/**
 * @}
 */

/**
 * @defgroup IS42S16400J_Mode_Register_Field IS42S16400J Mode Register Field
 * @{
 */

/* IS42S16400J burst length definition */
#define IS42S16400J_MR_BURST_LEN_1                  (0UL)
#define IS42S16400J_MR_BURST_LEN_2                  (1UL)
#define IS42S16400J_MR_BURST_LEN_4                  (2UL)
#define IS42S16400J_MR_BURST_LEN_8                  (3UL)
#define IS42S16400J_MR_BURST_LEN_FULLPAGE           (7UL)

/* IS42S16400J burst type definition */
#define IS42S16400J_MR_BURST_TYPE_SEQUENTIAL        (0UL)
#define IS42S16400J_MR_BURST_TYPE_INTERLEAVED       (1UL << 3)

/* IS42S16400J CAS latency definition */
#define IS42S16400J_MR_CAS_LATENCY_2                (2UL << 4)
#define IS42S16400J_MR_CAS_LATENCY_3                (3UL << 4)

/* IS42S16400J operating mode definition */
#define IS42S16400J_MR_OPERATON_MODE_STANDARD       (0UL)

/* IS42S16400J write burst mode definition */
#define IS42S16400J_MR_WRITEBURST_MODE_PROGRAMMED   (0UL)
#define IS42S16400J_MR_WRITEBURST_MODE_SINGLE       (1UL << 9)

/**
 * @}
 */

/**
 * @defgroup IS42S16400J_Mode_Register_Value IS42S16400J Mode Register Value
 * @{
 */
#define IS42S16400J_MR_VALUE                                                   \
(   IS42S16400J_MR_BURST_LEN_8                  |                              \
    IS42S16400J_MR_BURST_TYPE_SEQUENTIAL        |                              \
    IS42S16400J_MR_CAS_LATENCY_2                |                              \
    IS42S16400J_MR_OPERATON_MODE_STANDARD       |                              \
    IS42S16400J_MR_WRITEBURST_MODE_PROGRAMMED)
/**
 * @}
 */

/**
 * @defgroup IS42S16400J_Map_DMC_Address_Space IS42S16400J Map DMC Address Space
 * @{
 */
#define IS42S16400J_MAP_DMC_MATCH_ADDR          (EXMC_DMC_MATCH_ADDR_0X80000000)
#define IS42S16400J_MAP_DMC_MASK_ADDR           (EXMC_DMC_MASK_ADDR_SIZE_16MB)
/**
 * @}
 */

/**
 * @defgroup Address_Align Address Align
 * @{
 */
#define IS_ADDRESS_ALIGN(address, align)        (!((address) & ((uint32_t)(~((align) - 1UL)))))
#define IS_ADDRESS_ALIGN_HALFWORD(address)      (IS_ADDRESS_ALIGN(address, 2UL))
#define IS_ADDRESS_ALIGN_WORD(address)          (IS_ADDRESS_ALIGN(address, 4UL))
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
static void EXMC_DMC_PortInit(void);
static void SDRAM_IS42S16400J_InitSequence(uint32_t u32Chip,
                                                    uint32_t u32MdRegVal);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup IS42S16400J_Global_Functions IS42S16400J Global Functions
 * @{
 */

/**
 * @brief  Initialize DMC for IS42S16400J.
 * @param  None
 * @retval None
 */
void IS42S_Init(void)
{
    stc_exmc_dmc_init_t stcDmcInit;
    stc_exmc_dmc_cs_cfg_t stcCsCfg;

    /* Initialization DMC port.*/
    EXMC_DMC_PortInit();

    /* Enable DMC module clk */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_DMC, Enable);

    /* Enable DMC. */
    EXMC_DMC_Enable();

    /* Set configure state.*/
    EXMC_DMC_SetState(EXMC_DMC_CTL_STATE_CONFIGURE);

    /* Configure DMC width && refresh period & chip & timing. */
    EXMC_DMC_StructInit(&stcDmcInit);
    stcDmcInit.stcChipCfg.u32AutoRefreshChips = EXMC_DMC_AUTO_REFRESH_2_CHIPS;
    EXMC_DMC_Init(&stcDmcInit);

    /* Configure DMC address space. */
    stcCsCfg.u32AddrMask = IS42S16400J_MAP_DMC_MASK_ADDR;
    stcCsCfg.u32AddrMatch = IS42S16400J_MAP_DMC_MATCH_ADDR;
    stcCsCfg.u32AddrDecodeMode = EXMC_DMC_CS_DECODE_ROWBANKCOL;
    EXMC_DMC_CsConfig(IS42S16400J_MAP_DMC_CHIP, &stcCsCfg);

    /* SDRAM initialization sequence. */
    SDRAM_IS42S16400J_InitSequence(IS42S16400J_MAP_DMC_CHIP, IS42S16400J_MR_VALUE);

    /* Switch configure to ready. */
    EXMC_DMC_SetState(EXMC_DMC_CTL_STATE_GO);
    EXMC_DMC_SetState(EXMC_DMC_CTL_STATE_WAKEUP);
    EXMC_DMC_SetState(EXMC_DMC_CTL_STATE_GO);
}

/**
 * @brief  Write memory for byte.
 * @param  [in] au8Buf                  Data buffer to write
 * @param  [in] u32Addr                 Memory address to write
 * @param  [in] u32Size                 Number bytes to write
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.

 */
en_result_t IS42S_WriteMem8(const uint8_t au8Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au8Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i++)
        {
            *(uint8_t *)(u32Addr + i) = au8Buf[i];
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Read memory for byte.
 * @param  [in] au8Buf                  Data buffer to read
 * @param  [in] u32Addr                 Memory address to read
 * @param  [in] u32Size                 Number bytes to read
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 */
en_result_t IS42S_ReadMem8(uint8_t au8Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32Size) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au8Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i++)
        {
            au8Buf[i] = *(uint8_t *)(u32Addr + i);
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Write memory for half-word.
 * @param  [in] au16Buf                 Data buffer to write
 * @param  [in] u32Addr                 Memory address to write
 * @param  [in] u32Size                 Number half-word to write
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au16Buf value is NULL.
 */
en_result_t IS42S_WriteMem16(const uint16_t au16Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 2UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));
    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au16Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 2UL)
        {
            *(uint16_t *)(u32Addr + i) = au16Buf[i];
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Read memory for half-word.
 * @param  [in] au16Buf                 Data buffer to read
 * @param  [in] u32Addr                 Memory address to read
 * @param  [in] u32Size                 Number half-word to read
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au16Buf value is NULL.
 */
en_result_t IS42S_ReadMem16(uint16_t au16Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 2UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));
    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au16Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 2UL)
        {
            au16Buf[i] = *(uint16_t *)(u32Addr + i);
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Write memory for word.
 * @param  [in] au32Buf                 Data buffer to write
 * @param  [in] u32Addr                 Memory address to write
 * @param  [in] u32Size                 Number word to write
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au32Buf value is NULL.
 */
en_result_t IS42S_WriteMem32(const uint32_t au32Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 4UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));
    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au32Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 4UL)
        {
            *(uint32_t *)(u32Addr + i) = au32Buf[i];
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Read memory for word.
 * @param  [in] au2Buf                 Data buffer to read
 * @param  [in] u32Addr                 Memory address to read
 * @param  [in] u32Size                 Number word to read
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au32Buf value is NULL.
 */
en_result_t IS42S_ReadMem32(uint32_t au32Buf[],
                                uint32_t u32Addr,
                                uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 4UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));
    DDL_ASSERT(u32Addr >= SDRAM_IS42S_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SDRAM_IS42S_END_ADDR);

    if (NULL != au32Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 4UL)
        {
            au32Buf[i] = *(uint32_t *)(u32Addr + i);
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup IS42S16400J_Local_Functions IS42S16400J Local Functions
 * @{
 */

/**
 * @brief  Initialize DMC port.
 * @param  None
 * @retval None
 */
static void EXMC_DMC_PortInit(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_Unlock();

    /* DMC_CKE */
    GPIO_SetFunc(DMC_CKE_PORT, DMC_CKE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_CLK */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_MID_DRV;
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    GPIO_Init(DMC_CLK_PORT, DMC_CLK_PIN, &stcGpioInit);
    GPIO_SetFunc(DMC_CLK_PORT, DMC_CLK_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_LDQM && DMC_UDQM */
    GPIO_SetFunc(DMC_DQM0_PORT, DMC_DQM0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DQM1_PORT, DMC_DQM1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_BA[0:1] */
    GPIO_SetFunc(DMC_BA0_PORT, DMC_BA0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_BA1_PORT, DMC_BA1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_CS */
    GPIO_SetFunc(DMC_CS1_PORT, DMC_CS1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_CAS && DMC_RAS */
    GPIO_SetFunc(DMC_CAS_PORT, DMC_CAS_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_RAS_PORT, DMC_RAS_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_WE */
    GPIO_SetFunc(DMC_WE_PORT, DMC_WE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_DATA[0:15] */
    GPIO_SetFunc(DMC_DATA0_PORT, DMC_DATA0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA1_PORT, DMC_DATA1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA2_PORT, DMC_DATA2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA3_PORT, DMC_DATA3_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA4_PORT, DMC_DATA4_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA5_PORT, DMC_DATA5_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA6_PORT, DMC_DATA6_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA7_PORT, DMC_DATA7_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA8_PORT, DMC_DATA8_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA9_PORT, DMC_DATA9_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA10_PORT, DMC_DATA10_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA11_PORT, DMC_DATA11_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA12_PORT, DMC_DATA12_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA13_PORT, DMC_DATA13_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA14_PORT, DMC_DATA14_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_DATA15_PORT, DMC_DATA15_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* DMC_ADD[0:11]*/
    GPIO_SetFunc(DMC_ADD0_PORT, DMC_ADD0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD1_PORT, DMC_ADD1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD2_PORT, DMC_ADD2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD3_PORT, DMC_ADD3_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD4_PORT, DMC_ADD4_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD5_PORT, DMC_ADD5_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD6_PORT, DMC_ADD6_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD7_PORT, DMC_ADD7_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD8_PORT, DMC_ADD8_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD9_PORT, DMC_ADD9_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD10_PORT, DMC_ADD10_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(DMC_ADD11_PORT, DMC_ADD11_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    GPIO_Lock();
}

/**
 * @brief  SDRAM IS42S16400J initialization sequence.
 * @param  None
 * @retval None
 */
static void SDRAM_IS42S16400J_InitSequence(uint32_t u32Chip,
                                                    uint32_t u32MdRegVal)
{
    /* SDRAM initialization sequence:
       CMD NOP->PrechargeAll->AutoRefresh->AutoRefresh->MdRegConfig->NOP */
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_NOP, 0UL);
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_PRECHARGEALL, 0UL);
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_AUTOREFRESH, 0UL);
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_AUTOREFRESH, 0UL);
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_MDREGCONFIG, u32MdRegVal);
    EXMC_DMC_Cmd(u32Chip, EXMC_DMC_BANK_0, EXMC_DMC_CMD_NOP, 0UL);
}

/**
 * @}
 */

#endif /* MW_IS42S16400J_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
