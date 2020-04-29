/**
 *******************************************************************************
 * @file  is62wv51216.c
 * @brief This midware file provides firmware functions to manage the SRAM 
 *        midware library for is62wv51216.
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

#include "is62wv51216.h"

/**
 * @addtogroup HC32F4A0_DDL_Midware
 * @{
 */

/**
 * @defgroup MW_SRAM SRAM
 * @brief SRAM Midware Library
 * @{
 */

#if (MW_SRAM_IS62WV51216_ENABLE == DDL_ON)

#if (DDL_CLK_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_CLK_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_GPIO_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_GPIO_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_PWC_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_PWC_ENABLE to DDL_ON in ddl_config.h"
#endif

#if (DDL_SMC_ENABLE == DDL_OFF)
#error "please configure macro definition DDL_SMC_ENABLE to DDL_ON in ddl_config.h"
#endif

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IS62WV51216_Local_Macros IS62WV51216 Local Macros
 * @{
 */

/**
 * @defgroup SMC_Interface_Pin DMC Interface Pin
 * @{
 */

#define SMC_CS2_PORT                            (GPIO_PORT_G)   /* PG10 - EXMC_CE2 */
#define SMC_CS2_PIN                             (GPIO_PIN_10)

#define SMC_WE_PORT                             (GPIO_PORT_D)   /* PD5 - EXMC_WE */
#define SMC_WE_PIN                              (GPIO_PIN_05)

#define SMC_BLS0_PORT                           (GPIO_PORT_E)   /* PE0 - EXMC_CE4 */
#define SMC_BLS0_PIN                            (GPIO_PIN_00)
#define SMC_BLS1_PORT                           (GPIO_PORT_E)   /* PE1 - EXMC_CE5 */
#define SMC_BLS1_PIN                            (GPIO_PIN_01)

#define DMC_OE_PORT                             (GPIO_PORT_D)   /* PD4 - EXMC_OE */
#define DMC_OE_PIN                              (GPIO_PIN_04)

#define SMC_ADD0_PORT                           (GPIO_PORT_F)   /* PF0 - EXMC_ADD0 */
#define SMC_ADD0_PIN                            (GPIO_PIN_00)
#define SMC_ADD1_PORT                           (GPIO_PORT_F)   /* PF1 - EXMC_ADD1 */
#define SMC_ADD1_PIN                            (GPIO_PIN_01)
#define SMC_ADD2_PORT                           (GPIO_PORT_F)   /* PF2 - EXMC_ADD2 */
#define SMC_ADD2_PIN                            (GPIO_PIN_02)
#define SMC_ADD3_PORT                           (GPIO_PORT_F)   /* PF3 - EXMC_ADD3 */
#define SMC_ADD3_PIN                            (GPIO_PIN_03)
#define SMC_ADD4_PORT                           (GPIO_PORT_F)   /* PF4 - EXMC_ADD4 */
#define SMC_ADD4_PIN                            (GPIO_PIN_04)
#define SMC_ADD5_PORT                           (GPIO_PORT_F)   /* PF5 - EXMC_ADD5 */
#define SMC_ADD5_PIN                            (GPIO_PIN_05)
#define SMC_ADD6_PORT                           (GPIO_PORT_F)   /* PF12 - EXMC_ADD6 */
#define SMC_ADD6_PIN                            (GPIO_PIN_12)
#define SMC_ADD7_PORT                           (GPIO_PORT_F)   /* PF13 - EXMC_ADD7 */
#define SMC_ADD7_PIN                            (GPIO_PIN_13)
#define SMC_ADD8_PORT                           (GPIO_PORT_F)   /* PF14 - EXMC_ADD8 */
#define SMC_ADD8_PIN                            (GPIO_PIN_14)
#define SMC_ADD9_PORT                           (GPIO_PORT_F)   /* PF15 - EXMC_ADD9 */
#define SMC_ADD9_PIN                            (GPIO_PIN_15)
#define SMC_ADD10_PORT                          (GPIO_PORT_G)   /* PG0 - EXMC_ADD10 */
#define SMC_ADD10_PIN                           (GPIO_PIN_00)
#define SMC_ADD11_PORT                          (GPIO_PORT_G)   /* PG1 - EXMC_ADD11 */
#define SMC_ADD11_PIN                           (GPIO_PIN_01)
#define SMC_ADD12_PORT                          (GPIO_PORT_G)   /* PG2 - EXMC_ADD12 */
#define SMC_ADD12_PIN                           (GPIO_PIN_02)
#define SMC_ADD13_PORT                          (GPIO_PORT_G)   /* PG3 - EXMC_ADD13 */
#define SMC_ADD13_PIN                           (GPIO_PIN_03)
#define SMC_ADD14_PORT                          (GPIO_PORT_G)   /* PG4 - EXMC_ADD14 */
#define SMC_ADD14_PIN                           (GPIO_PIN_04)
#define SMC_ADD15_PORT                          (GPIO_PORT_G)   /* PG5 - EXMC_ADD15 */
#define SMC_ADD15_PIN                           (GPIO_PIN_05)
#define SMC_ADD16_PORT                          (GPIO_PORT_D)   /* PD11 - EXMC_ADD16 */
#define SMC_ADD16_PIN                           (GPIO_PIN_11)
#define SMC_ADD17_PORT                          (GPIO_PORT_D)   /* PD12 - EXMC_ADD17 */
#define SMC_ADD17_PIN                           (GPIO_PIN_12)
#define SMC_ADD18_PORT                          (GPIO_PORT_D)   /* PD13 - EXMC_ADD18 */
#define SMC_ADD18_PIN                           (GPIO_PIN_13)

#define SMC_DATA0_PORT                          (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define SMC_DATA0_PIN                           (GPIO_PIN_14)
#define SMC_DATA1_PORT                          (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define SMC_DATA1_PIN                           (GPIO_PIN_15)
#define SMC_DATA2_PORT                          (GPIO_PORT_D)   /* PD0 - EXMC_DATA2 */
#define SMC_DATA2_PIN                           (GPIO_PIN_00)
#define SMC_DATA3_PORT                          (GPIO_PORT_D)   /* PD1 - EXMC_DATA3 */
#define SMC_DATA3_PIN                           (GPIO_PIN_01)
#define SMC_DATA4_PORT                          (GPIO_PORT_E)   /* PE7 - EXMC_DATA4 */
#define SMC_DATA4_PIN                           (GPIO_PIN_07)
#define SMC_DATA5_PORT                          (GPIO_PORT_E)   /* PE8 - EXMC_DATA5 */
#define SMC_DATA5_PIN                           (GPIO_PIN_08)
#define SMC_DATA6_PORT                          (GPIO_PORT_E)   /* PE9 - EXMC_DATA6 */
#define SMC_DATA6_PIN                           (GPIO_PIN_09)
#define SMC_DATA7_PORT                          (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define SMC_DATA7_PIN                           (GPIO_PIN_10)
#define SMC_DATA8_PORT                          (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define SMC_DATA8_PIN                           (GPIO_PIN_11)
#define SMC_DATA9_PORT                          (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define SMC_DATA9_PIN                           (GPIO_PIN_12)
#define SMC_DATA10_PORT                         (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define SMC_DATA10_PIN                          (GPIO_PIN_13)
#define SMC_DATA11_PORT                         (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define SMC_DATA11_PIN                          (GPIO_PIN_14)
#define SMC_DATA12_PORT                         (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define SMC_DATA12_PIN                          (GPIO_PIN_15)
#define SMC_DATA13_PORT                         (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define SMC_DATA13_PIN                          (GPIO_PIN_08)
#define SMC_DATA14_PORT                         (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define SMC_DATA14_PIN                          (GPIO_PIN_09)
#define SMC_DATA15_PORT                         (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define SMC_DATA15_PIN                          (GPIO_PIN_10)
/**
 * @}
 */

/**
 * @defgroup IS62WV51216_SMC_Address_Space IS62WV51216 DMC Address Space
 * @{
 */
#define IS62WV51216_SMC_MATCH_ADDR              (0x60UL)
#define IS62WV51216_SMC_MASK_ADDR               (0xFFUL)
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
static void EXMC_SMC_PortInit(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup IS62WV51216_Global_Functions IS62WV51216 Global Functions
 * @{
 */

/**
 * @brief  Initialize SMC for IS62WV51216.
 * @param  None
 * @retval None
 */
void IS62WV_Init(void)
{
    stc_exmc_smc_init_t stcSmcInit;

    /* Initialize SMC port. */
    EXMC_SMC_PortInit();

    /* Enable SMC module clk */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_SMC, Enable);

    /* Enable SMC. */
    EXMC_SMC_Enable();

    /* Disable SMC MUX. */
    EXMC_SMC_MuxDisable();

    /* Configure SMC width && refresh period & CS &chip & timing. */
    EXMC_SMC_StructInit(&stcSmcInit);
    stcSmcInit.stcCsCfg.u32AddrMatch = IS62WV51216_SMC_MATCH_ADDR;
    stcSmcInit.stcCsCfg.u32AddrMask = IS62WV51216_SMC_MASK_ADDR;
    EXMC_SMC_Init(IS62WV51216_MAP_SMC_CHIP, &stcSmcInit);

    /* Update registers command. */
    EXMC_SMC_Cmd(IS62WV51216_MAP_SMC_CHIP, EXMC_SMC_CMD_UPDATEREGS, 0UL, 0UL);
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
en_result_t IS62WV_WriteMem8(const uint8_t au8Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au8Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i++)
        {
            *(uint8_t *)(u32Addr + i) = au8Buf[i];
        }
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
en_result_t IS62WV_ReadMem8(uint8_t au8Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au8Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i++)
        {
            au8Buf[i] = *(uint8_t *)(u32Addr + i);
        }
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
en_result_t IS62WV_WriteMem16(const uint16_t au16Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 2UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));
    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au16Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 2UL)
        {
            *(uint16_t *)(u32Addr + i) = au16Buf[i];
        }
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
en_result_t IS62WV_ReadMem16(uint16_t au16Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 2UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_HALFWORD(u32Addr));
    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au16Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 2UL)
        {
            au16Buf[i] = *(uint16_t *)(u32Addr + i);
        }
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
en_result_t IS62WV_WriteMem32(const uint32_t au32Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 4UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));
    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au32Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 4UL)
        {
            *(uint32_t *)(u32Addr + i) = au32Buf[i];
        }
    }

    return enRet;
}

/**
 * @brief  Read memory for word.
 * @param  [in] au32Buf                 Data buffer to read
 * @param  [in] u32Addr                 Memory address to read
 * @param  [in] u32Size                 Number word to read
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       The pointer au32Buf value is NULL.
 */
en_result_t IS62WV_ReadMem32(uint32_t au32Buf[],
                                    uint32_t u32Addr,
                                    uint32_t u32Size)
{
    uint32_t u32SizeBytes = u32Size * 4UL;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(u32Addr));
    DDL_ASSERT(u32Addr >= SRAM_IS62WV_START_ADDR);
    DDL_ASSERT((u32Addr + u32SizeBytes) <= SRAM_IS62WV_END_ADDR);

    if (NULL != au32Buf)
    {
        for (uint32_t i = 0UL; i < u32SizeBytes; i += 4UL)
        {
            au32Buf[i] = *(uint32_t *)(u32Addr + i);
        }
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup IS62WV51216_Local_Functions IS62WV51216 Local Functions
 * @{
 */

/**
 * @brief  Initialize SMC port.
 * @param  None
 * @retval None
 */
static void EXMC_SMC_PortInit(void)
{
    GPIO_Unlock();

    /* SMC_CS */
    GPIO_SetFunc(SMC_CS2_PORT, SMC_CS2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* SMC_WE */
    GPIO_SetFunc(SMC_WE_PORT, SMC_WE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* SMC_BLS[0:1] */
    GPIO_SetFunc(SMC_BLS0_PORT, SMC_BLS0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_BLS1_PORT, SMC_BLS1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* SMC_OE */
    GPIO_SetFunc(DMC_OE_PORT, DMC_OE_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* SMC_DATA[0:15] */
    GPIO_SetFunc(SMC_DATA0_PORT, SMC_DATA0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA1_PORT, SMC_DATA1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA2_PORT, SMC_DATA2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA3_PORT, SMC_DATA3_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA4_PORT, SMC_DATA4_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA5_PORT, SMC_DATA5_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA6_PORT, SMC_DATA6_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA7_PORT, SMC_DATA7_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA8_PORT, SMC_DATA8_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA9_PORT, SMC_DATA9_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA10_PORT, SMC_DATA10_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA11_PORT, SMC_DATA11_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA12_PORT, SMC_DATA12_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA13_PORT, SMC_DATA13_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA14_PORT, SMC_DATA14_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_DATA15_PORT, SMC_DATA15_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    /* SMC_ADD[0:18]*/
    GPIO_SetFunc(SMC_ADD0_PORT, SMC_ADD0_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD1_PORT, SMC_ADD1_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD2_PORT, SMC_ADD2_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD3_PORT, SMC_ADD3_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD4_PORT, SMC_ADD4_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD5_PORT, SMC_ADD5_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD6_PORT, SMC_ADD6_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD7_PORT, SMC_ADD7_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD8_PORT, SMC_ADD8_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD9_PORT, SMC_ADD9_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD10_PORT, SMC_ADD10_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD11_PORT, SMC_ADD11_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD12_PORT, SMC_ADD12_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD13_PORT, SMC_ADD13_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD14_PORT, SMC_ADD14_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD15_PORT, SMC_ADD15_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD16_PORT, SMC_ADD16_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD17_PORT, SMC_ADD17_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SMC_ADD18_PORT, SMC_ADD18_PIN, GPIO_FUNC_12_EXMC, PIN_SUBFUNC_DISABLE);

    GPIO_Lock();
}

/**
 * @}
 */

#endif /* MW_SRAM_IS62WV51216_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
