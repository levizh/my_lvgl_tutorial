/**
 *******************************************************************************
 * @file  hc32f4a0_mau.h
 * @brief This file contains all the functions prototypes of the MAU driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-09       Hexiao          First version
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
#ifndef __HC32F4A0_MAU_H__
#define __HC32F4A0_MAU_H__

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
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_MAU
 * @{
 */

#if (DDL_MAU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup MAU_Global_Macros MAU Global Macros
 * @{
 */
#define MAU_SQRT_TIMEOUT            (0x1000UL)
#define MAU_SQRT_OUTPUT_LSHIFT_MAX  (16U)
#define MAU_SIN_Q15_SCALAR          (0x8000UL)
#define MAU_SIN_ANG_TOTAL           (0x1000UL)

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
 * @addtogroup MAU_Global_Functions
 * @{
 */

/**
 * @brief   Square root
 * @param  [in]  pstMAUx       Pointer to MAU instance register base
 *         This parameter can only be: @arg M4_MAU
 * @param  [in]  u32Radicand   data to be square rooted
 * @param  [out] pu32Result    Result of square root,range is [0,0x10000]
 * @retval None
 */
__STATIC_INLINE en_result_t MAU_Sqrt(M4_MAU_TypeDef * pstMAUx, uint32_t u32Radicand, uint32_t *pu32Result)
{
    DDL_ASSERT(M4_MAU == pstMAUx);
    DDL_ASSERT(NULL != pu32Result);

    uint32_t u32TimeCount = 0UL;
    en_result_t enRet = Ok;
    uint32_t const u32WaitBusyHCount = 3UL;

    WRITE_REG32(pstMAUx->DTR0, u32Radicand);
    SET_REG32_BIT(pstMAUx->CSR, MAU_CSR_START);
    for(uint32_t i = 0UL; i < u32WaitBusyHCount; i++)
    {
        __ASM("NOP");
    }

    while((pstMAUx->CSR & MAU_CSR_BUSY) != 0UL)
    {
        if(u32TimeCount++ > MAU_SQRT_TIMEOUT)
        {
            enRet = Error;
            break;
        }
    }

    if(Ok == enRet)
    {
        *pu32Result = READ_REG32(pstMAUx->RTR0);
    }

    return enRet;
}

/**
 * @brief  Read result of sqrt
 * @param  [in] pstMAUx   Pointer to MAU instance register base
 *         This parameter can only be: @arg M4_MAU
 * @retval Result of square root,range is [0,0x10000]
 */
__STATIC_INLINE uint32_t MAU_SqrtRead(M4_MAU_TypeDef *const pstMAUx)
{
    DDL_ASSERT(M4_MAU == pstMAUx);

    return READ_REG32(pstMAUx->RTR0);
}

/**
 * @brief  Sine
 * @param  [in] pstMAUx   Pointer to MAU instance register base
 *         This parameter can only be: @arg M4_MAU
 * @param  AngleIdx: Angle index,range is [0,0xFFF], calculation method for reference:
           AngleIdx=(uint32_t)(Angle * 4096.0F / 360.0F + 0.5F) % 4096U
 * @retval Result of Sine in Q15 format
 */
__STATIC_INLINE int16_t MAU_Sin(M4_MAU_TypeDef * pstMAUx, uint16_t u16AngleIdx)
{
    WRITE_REG16(pstMAUx->DTR1, u16AngleIdx);

    __ASM("NOP");
    return (int16_t)READ_REG16(pstMAUx->RTR1);
}

void MAU_SqrtResultLShiftCfg(M4_MAU_TypeDef * pstMAUx, uint8_t u8LShBitsNumber);
void MAU_SqrtIntCmd(M4_MAU_TypeDef * pstMAUx, en_functional_state_t enNewState);
__STATIC_INLINE en_result_t MAU_Sqrt(M4_MAU_TypeDef * pstMAUx, uint32_t u32Radicand, uint32_t *pu32Result);
__STATIC_INLINE uint32_t MAU_SqrtRead(M4_MAU_TypeDef * pstMAUx);
__STATIC_INLINE int16_t MAU_Sin(M4_MAU_TypeDef * pstMAUx, uint16_t u16AngleIdx);

/**
 * @}
 */

#endif /* DDL_MAU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_MAU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
