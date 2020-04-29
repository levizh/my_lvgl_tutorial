/**
 *******************************************************************************
 * @file  hc32f4a0_mau.h
 * @brief This file contains all the functions prototypes of the MAU dirver
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
/**
 * @defgroup MAU_Global_Types MAU Global Types
 * @{
 */
typedef enum
{
    MAU_SQRT_OUTPUT_LSHIFT_0 = 0U,
    MAU_SQRT_OUTPUT_LSHIFT_1,
    MAU_SQRT_OUTPUT_LSHIFT_2,
    MAU_SQRT_OUTPUT_LSHIFT_3,
    MAU_SQRT_OUTPUT_LSHIFT_4,
    MAU_SQRT_OUTPUT_LSHIFT_5,
    MAU_SQRT_OUTPUT_LSHIFT_6,
    MAU_SQRT_OUTPUT_LSHIFT_7,
    MAU_SQRT_OUTPUT_LSHIFT_8,
    MAU_SQRT_OUTPUT_LSHIFT_9,
    MAU_SQRT_OUTPUT_LSHIFT_10,
    MAU_SQRT_OUTPUT_LSHIFT_11,
    MAU_SQRT_OUTPUT_LSHIFT_12,
    MAU_SQRT_OUTPUT_LSHIFT_13,
    MAU_SQRT_OUTPUT_LSHIFT_14,
    MAU_SQRT_OUTPUT_LSHIFT_15,
    MAU_SQRT_OUTPUT_LSHIFT_16,
} en_sqrt_output_lshift_t;

typedef enum
{
    MAU_SQRT_RESULT_RDY = 0U,
    MAU_SQRT_RESULT_NOTRDY = 1U,
} en_sqrt_result_flag_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup MAU_Global_Macros MAU Global Macros
 * @{
 */
#define MAU_SQRT_TIMEOUT       (0x1000U)
#define MAU_SIN_Q15_SCALAR     (0x8000U)
#define MAU_SIN_ANG_TOTAL      (0x1000U)

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
 * @param  [in] pstMAUx   Pointer to MAU instance register base
 *         This parameter can only be: @arg M4_MAU
 * @param  [in] u32Radicand   data to be square rooted
 * @retval ret   Result of square root,range is [0,0x10000]
 */
__STATIC_INLINE uint32_t MAU_Sqrt(M4_MAU_TypeDef * pstMAUx,uint32_t u32Radicand)
{
    uint32_t u32TimeCount = 0U,u32IsTimeout = 0U;
    uint32_t ret = 0U;
    uint32_t const u32WaitBusyHCount = 3U;

    WRITE_REG32(pstMAUx->DTR0, u32Radicand);
    SET_REG32_BIT(pstMAUx->CSR, MAU_CSR_START);
    for(uint32_t i = 0U; i < u32WaitBusyHCount; i++)
        __ASM("NOP");
    while((pstMAUx->CSR & MAU_CSR_BUSY) != 0U)
    {
        if(u32TimeCount++ > MAU_SQRT_TIMEOUT)
        {
            u32IsTimeout = 1U;
            break;
        }
    }
    if(u32IsTimeout == 0U)
    {
        ret = READ_REG32(pstMAUx->RTR0);
    }
    return ret;
}

/**
 * @brief  Read result of sqrt
 * @param  [in] pstMAUx   Pointer to MAU instance register base
 *         This parameter can only be: @arg M4_MAU
 * @retval Result of square root,range is [0,0x10000]
 */
__STATIC_INLINE uint32_t MAU_SqrtRead(M4_MAU_TypeDef *const pstMAUx)
{
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

void MAU_SqrtResultLShiftCfg(M4_MAU_TypeDef * pstMAUx, en_sqrt_output_lshift_t enSHL);
void MAU_SqrtIntCmd(M4_MAU_TypeDef * pstMAUx, en_functional_state_t enNewState);
__STATIC_INLINE uint32_t MAU_Sqrt(M4_MAU_TypeDef * pstMAUx, uint32_t u32Radicand);
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
