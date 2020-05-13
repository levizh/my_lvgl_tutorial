
#include "hc32_common.h"
#include "i2c_drv.h"

en_result_t I2Cx_Start(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To)
{
    uint32_t u32TimeOut = u32To;
    en_flag_status_t enBusyFlag, enStartFlag;
    en_result_t u8Ret = Ok;

    while (Set == I2C_GetStatus(pstcI2Cx, I2C_SR_BUSY))
    {
        if(0UL == (u32TimeOut--))
        {
            return ErrorTimeout;
        }
    }
    /* generate start signal */
    I2C_GenerateStart(pstcI2Cx);

    /* Judge if start success*/
    //while((Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_BUSY)) ||
    //        (Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_STARTF)))  /* MISRAC 2004*/
    u32TimeOut = u32To;
    while(1)
    {
        enBusyFlag = I2C_GetStatus(pstcI2Cx, I2C_SR_BUSY);
        enStartFlag = I2C_GetStatus(pstcI2Cx, I2C_SR_STARTF);
        u32TimeOut--;
        if(((Set == enBusyFlag) && (Set == enStartFlag))||(0UL == u32TimeOut))
        {
            break;
        }
    }
    if(0UL == u32TimeOut)
    {
        u8Ret = ErrorTimeout;
    }
    return u8Ret;
}

en_result_t I2Cx_Restart(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To)
{
    uint32_t u32TimeOut = u32To;
    en_flag_status_t enBusyFlag, enStartFlag;
    en_result_t u8Ret = Ok;

    /* generate restart signal */
    /* Clear start status flag */
    I2C_ClearStatus(pstcI2Cx, I2C_CLR_STARTFCLR);
    /* Send restart condition */
    I2C_GenerateReStart(pstcI2Cx);

    /* Judge if start success*/
    //while((Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_BUSY)) ||
    //        (Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_STARTF)))  /* MISRAC 2004*/
    u32TimeOut = u32To;
    while(1)
    {
        enBusyFlag = I2C_GetStatus(pstcI2Cx, I2C_SR_BUSY);
        enStartFlag = I2C_GetStatus(pstcI2Cx, I2C_SR_STARTF);
        u32TimeOut--;
        if(((Set == enBusyFlag) && (Set == enStartFlag))||(0UL == u32TimeOut))
        {
            break;
        }
    }
    if(0UL == u32TimeOut)
    {
        u8Ret = ErrorTimeout;
    }
    return u8Ret;
}

en_result_t I2Cx_SendAddr(M4_I2C_TypeDef* pstcI2Cx, uint8_t u8Adr, uint32_t u32To)
{
    uint32_t u32TimeOut = u32To;

    /* Wait tx buffer empty */
    while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_TEMPTYF))
    {
        if(0UL == (u32TimeOut--))
        {
            return ErrorTimeout;
        }
    }

    /* Send I2C address */
    I2C_WriteDataReg(pstcI2Cx, u8Adr);

    if(0U == (u8Adr & 0x01U))
    {
        /* If in master transfer process, Need wait transfer end*/
        uint32_t u32TimeOut = u32To;
        while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_TENDF))
        {
            if(0UL == (u32TimeOut--))
            {
                return ErrorTimeout;
            }
        }
    }
    /* Check ACK */
    u32TimeOut = u32To;
    while(Set == I2C_GetStatus(pstcI2Cx, I2C_SR_ACKRF))
    {
        if(0U == (u32TimeOut--))
        {
            return ErrorTimeout;
        }
    }

    return Ok;
}

en_result_t I2Cx_SendData(M4_I2C_TypeDef* pstcI2Cx, uint8_t *pTxData, uint32_t u32Size, uint32_t u32To)
{
    uint32_t u32TimeOut = u32To;

    while(u32Size--)
    {
        /* Wait tx buffer empty */
        u32TimeOut = u32To;
        while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_TEMPTYF))
        {
            if(0UL == (u32TimeOut--))
            {
                return ErrorTimeout;
            }
        }

        /* Send one byte data */
        I2C_WriteDataReg(pstcI2Cx, *pTxData++);

        /* Wait transfer end*/
        u32TimeOut = u32To;
        while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_TENDF))
        {
            if(0UL == (u32TimeOut--))
            {
                return ErrorTimeout;
            }
        }

        /* Check ACK */
        u32TimeOut = u32To;
        while(Set == I2C_GetStatus(pstcI2Cx, I2C_SR_ACKRF))
        {
            if(0UL == (u32TimeOut--))
            {
                return ErrorTimeout;
            }
        }
    }

    return Ok;
}

en_result_t I2Cx_RcvData(M4_I2C_TypeDef* pstcI2Cx, uint8_t *pRxData, const uint32_t u32Size, uint32_t u32To)
{
    uint32_t u32TimeOut = u32To;

    for(volatile uint32_t i=0UL; i<u32Size; i++)
    {
        /* if the last byte receive, need config NACK*/
        if(i == (u32Size - 1UL))
        {
            I2C_NackConfig(pstcI2Cx, Enable);
        }
        else
        {
            __ASM("NOP");
        }

        /* Wait receive full flag*/
        u32TimeOut = u32To;
        while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_RFULLF))
        {
            if(0UL == (u32TimeOut--))
            {
                return ErrorTimeout;
            }
        }

        /* read data from register*/
        *pRxData++ = I2C_ReadDataReg(pstcI2Cx);
    }
    return Ok;
}

en_result_t I2Cx_Stop(M4_I2C_TypeDef* pstcI2Cx, uint32_t u32To)
{
    uint32_t u32TimeOut;

    /* Clear stop flag */
    while(Set == I2C_GetStatus(pstcI2Cx, I2C_SR_STOPF))
    {
        I2C_ClearStatus(pstcI2Cx, I2C_CLR_STOPFCLR);
    }

    I2C_GenerateStop(pstcI2Cx);

    /* Wait STOPF */
    u32TimeOut = u32To;
    while(Reset == I2C_GetStatus(pstcI2Cx, I2C_SR_STOPF))
    {
        if(0UL == (u32TimeOut--))
        {
            return ErrorTimeout;
        }
    }
    return Ok;
}