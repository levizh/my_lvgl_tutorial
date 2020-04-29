#ifndef __I2C_DRV_H__
#define __I2C_DRV_H__

#include "hc32f4a0_i2c.h"

en_result_t I2Cx_Start(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To);
en_result_t I2Cx_Restart(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To);
en_result_t I2Cx_SendAddr(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Adr, uint32_t u32To);
en_result_t I2Cx_SendData(M4_I2C_TypeDef* pstcI2Cx, uint8_t *pTxData, uint32_t u32Size, uint32_t u32To);
en_result_t I2Cx_RcvData(M4_I2C_TypeDef* pstcI2Cx, uint8_t *pRxData, uint32_t u32Size, uint32_t u32To);
en_result_t I2Cx_Stop(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To);

#endif