/**
 *******************************************************************************
 * @file  gt9147.h
 * @brief This file contains all the functions prototypes of the GT9147 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-24       Zhangxl         First version
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
#ifndef __GT9147_H__
#define __GT9147_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @defgroup GT9147
  * @{
  */

#if (BSP_GT9147_ENABLE == BSP_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GT9147_Global_Macros GT9147 Global Macros
 * @{
 */
#define GT9147_REG_CTRL         ((uint16_t)0x8040)      /*!< GT9147 contrl */
#define GT9147_REG_CFGS         ((uint16_t)0x8047)      /*!< GT9147 config */
#define GT9147_REG_CHECK        ((uint16_t)0x80FF)      /*!< GT9147 checksum */
#define GT9147_REG_PID          ((uint16_t)0x8140)      /*!< GT9147 PID */

#define GT9147_REG_GSTID        ((uint16_t)0x814E)      /*!< touch status */
#define GT9147_REG_TP1          ((uint16_t)0x8150)      /*!< TP1 info */
#define GT9147_REG_TP2          ((uint16_t)0x8158)      /*!< TP2 info */
#define GT9147_REG_TP3          ((uint16_t)0x8160)      /*!< TP3 info */
#define GT9147_REG_TP4          ((uint16_t)0x8168)      /*!< TP4 info */
#define GT9147_REG_TP5          ((uint16_t)0x8170)      /*!< TP5 info */

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
 * @defgroup GT9147_Global_Functions GT9147 Global Functions
 * @{
 */
void GT9147_Init(void);
void GT9147_IntInit(void);
void GT9147_Reset(void);
en_result_t GT9147_WriteReg(uint8_t u8Reg, uint8_t u8Val);
en_result_t GT9147_ReadReg(uint8_t u8Reg, uint8_t *u8Val);

void EIO_Init(void);
void EIO_Reset(void);
void EIO_Delay(uint32_t u32Delay);
en_result_t EIO_Write(uint8_t u8Reg, uint8_t u8Val);
en_result_t EIO_Read(uint8_t u8Reg, uint8_t *u8Val);
void EIO_IntInit(void);

/**
 * @}
 */

#endif /* BSP_GT9147_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GT9147_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
