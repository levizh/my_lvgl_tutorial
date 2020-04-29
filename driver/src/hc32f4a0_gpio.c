/**
 *******************************************************************************
 * @file  hc32f4a0_gpio.c
 * @brief This file provides firmware functions to manage the General Purpose
 *        Input/Output(GPIO).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-2       Zhangxl         First version
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
#include "hc32f4a0_gpio.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO
 * @brief GPIO Driver Library
 * @{
 */

#if (DDL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Macros GPIO Local Macros
 * @{
 */
/**
 * @defgroup GPIO_Registers_Reset_Value GPIO Registers Reset Value
 * @{
 */
#define GPIO_PSPCR_RESET_VALUE          ((uint16_t)0x001FU)
#define GPIO_PCCR_RESET_VALUE           ((uint16_t)0x1000U)
#define GPIO_PINAER_RESET_VALUE         ((uint16_t)0x0000U)
/**
 * @}
 */

/**
 * @defgroup GPIO_Check_Parameters_Validity GPIO Check Parameters Validity
 * @{
 */
/*  Parameter validity check for pin state. */
#define IS_GPIO_PIN_STATE(state)                                                \
(   ((state) == PIN_STATE_RESET)                ||                              \
    ((state) == PIN_STATE_SET))

/*  Parameter validity check for pin direction. */
#define IS_GPIO_DIR(dir)                                                        \
(   ((dir) == PIN_DIR_IN)                       ||                              \
    ((dir) == PIN_DIR_OUT))

/*  Parameter validity check for pin output type. */
#define IS_GPIO_OTYPE(otype)                                                    \
(   ((otype) == PIN_OTYPE_CMOS)                 ||                              \
    ((otype) == PIN_OTYPE_NMOS))

/*  Parameter validity check for pin driver capacity. */
#define IS_GPIO_PIN_DRV(drv)                                                    \
(   ((drv) == PIN_LOW_DRV)                      ||                              \
    ((drv) == PIN_MID_DRV)                      ||                              \
    ((drv) == PIN_HIGH_DRV))

/*  Parameter validity check for pin latch function. */
#define IS_GPIO_LATCH(latch)                                                    \
(   ((latch) == PIN_LATCH_OFF)                  ||                              \
    ((latch) == PIN_LATCH_ON))

/*  Parameter validity check for internal pull-up resistor. */
#define IS_GPIO_PIN_PU(pu)                                                      \
(   ((pu) == PIN_PU_OFF)                        ||                              \
    ((pu) == PIN_PU_ON))

/*  Parameter validity check for pin state invert. */
#define IS_GPIO_PIN_INVERT(invert)                                              \
(   ((invert) == PIN_INVERT_OFF)                ||                              \
    ((invert) == PIN_INVERT_ON))

/*  Parameter validity check for pin input type. */
#define IS_GPIO_ITYPE(itype)                                                    \
(   ((itype) == PIN_ITYPE_SMT)                  ||                              \
    ((itype) == PIN_ITYPE_CMOS))

/*  Parameter validity check for external interrupt function. */
#define IS_GPIO_EXINT(exint)                                                    \
(   ((exint) == PIN_EXINT_OFF)                  ||                              \
    ((exint) == PIN_EXINT_ON))

/*  Parameter validity check for pin attribute. */
#define IS_GPIO_ATTR(attr)                                                      \
(   ((attr) == PIN_ATTR_DIGITAL)                ||                              \
    ((attr) == PIN_ATTR_ANALOG))

/*  Parameter validity check for pin number. */
#define IS_GPIO_PIN(pin)    (((pin) & GPIO_PIN_MASK ) != (uint16_t)0x0000U)

/*  Parameter validity check for get pin index. */
#define IS_GET_GPIO_PIN(pin)                                                    \
(   ((pin) == GPIO_PIN_00)                      ||                              \
    ((pin) == GPIO_PIN_01)                      ||                              \
    ((pin) == GPIO_PIN_02)                      ||                              \
    ((pin) == GPIO_PIN_03)                      ||                              \
    ((pin) == GPIO_PIN_04)                      ||                              \
    ((pin) == GPIO_PIN_05)                      ||                              \
    ((pin) == GPIO_PIN_06)                      ||                              \
    ((pin) == GPIO_PIN_07)                      ||                              \
    ((pin) == GPIO_PIN_08)                      ||                              \
    ((pin) == GPIO_PIN_09)                      ||                              \
    ((pin) == GPIO_PIN_10)                      ||                              \
    ((pin) == GPIO_PIN_11)                      ||                              \
    ((pin) == GPIO_PIN_12)                      ||                              \
    ((pin) == GPIO_PIN_13)                      ||                              \
    ((pin) == GPIO_PIN_14)                      ||                              \
    ((pin) == GPIO_PIN_15))

/*  Parameter validity check for port source. */
#define IS_GPIO_PORT(port)  (((port) & GPIO_PORT_MASK) != (uint16_t)0x0000u)

/*  Parameter validity check for port source. */
#define IS_GPIO_PORT_SOURCE(port)                                               \
(   ((port) == GPIO_PORT_A)                     ||                              \
    ((port) == GPIO_PORT_B)                     ||                              \
    ((port) == GPIO_PORT_C)                     ||                              \
    ((port) == GPIO_PORT_D)                     ||                              \
    ((port) == GPIO_PORT_E)                     ||                              \
    ((port) == GPIO_PORT_F)                     ||                              \
    ((port) == GPIO_PORT_G)                     ||                              \
    ((port) == GPIO_PORT_H)                     ||                              \
    ((port) == GPIO_PORT_I))

/*  Parameter validity check for pin function. */
#define IS_GPIO_FUNC(func)                                                      \
(   ((func) == GPIO_FUNC_0)                     ||                              \
    (((func) >= GPIO_FUNC_1)                    &&                              \
    ((func) <= GPIO_FUNC_20))                   ||                              \
    (((func) >= GPIO_FUNC_32)                   &&                              \
    ((func) <= GPIO_FUNC_63)))

/*  Parameter validity check for debug pin definition. */
#define IS_GPIO_DEBUG_PORT(port)    (((port) & GPIO_PIN_DEBUG_JTAG) != (uint8_t)0x00)

/*  Parameter validity check for pin sub-function setting. */
#define IS_GPIO_PIN_BFE(bfe)                                                    \
(   ((bfe) == PIN_SUBFUNC_ENABLE)               ||                              \
    ((bfe) == PIN_SUBFUNC_DISABLE))

/*  Parameter validity check for pin read wait cycle. */
#define IS_GPIO_READ_WAIT(wait)                                                 \
(   ((wait) == GPIO_READ_WAIT_0)                ||                              \
    ((wait) == GPIO_READ_WAIT_1)                ||                              \
    ((wait) == GPIO_READ_WAIT_2)                ||                              \
    ((wait) == GPIO_READ_WAIT_3)                ||                              \
    ((wait) == GPIO_READ_WAIT_4)                ||                              \
    ((wait) == GPIO_READ_WAIT_5))

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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Functions GPIO Global Functions
 * @{
 */

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval Ok: GPIO initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_Init(uint8_t u8Port, uint16_t u16Pin, const stc_gpio_init_t *pstcGpioInit)
{
    uint16_t *PCRx;
    uint16_t u16PinPos = 0U;
    uint16_t u16PCRVal;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
        DDL_ASSERT(IS_GPIO_PIN(u16Pin));
        DDL_ASSERT(IS_GPIO_PIN_STATE(pstcGpioInit->u16PinState));
        DDL_ASSERT(IS_GPIO_DIR(pstcGpioInit->u16PinDir));
        DDL_ASSERT(IS_GPIO_OTYPE(pstcGpioInit->u16PinOType));
        DDL_ASSERT(IS_GPIO_PIN_DRV(pstcGpioInit->u16PinDrv));
        DDL_ASSERT(IS_GPIO_LATCH(pstcGpioInit->u16Latch));
        DDL_ASSERT(IS_GPIO_PIN_PU(pstcGpioInit->u16PullUp));
        DDL_ASSERT(IS_GPIO_PIN_INVERT(pstcGpioInit->u16Invert));
        DDL_ASSERT(IS_GPIO_ITYPE(pstcGpioInit->u16PinIType));
        DDL_ASSERT(IS_GPIO_EXINT(pstcGpioInit->u16ExInt));

        GPIO_Unlock();

        for (u16PinPos = 0U; u16PinPos < 16U; u16PinPos++)
        {
            if (u16Pin & (1UL<<u16PinPos))
            {
                PCRx = (uint16_t *)((uint32_t)(&M4_GPIO->PCRA0) +                   \
                                  u8Port * 0x40UL + u16PinPos * 4UL);

                u16PCRVal = pstcGpioInit->u16ExInt  | pstcGpioInit->u16PinIType |   \
                            pstcGpioInit->u16Invert | pstcGpioInit->u16PullUp   |   \
                            pstcGpioInit->u16Latch  | pstcGpioInit->u16PinDrv   |   \
                            pstcGpioInit->u16PinOType | pstcGpioInit->u16PinState | \
                            pstcGpioInit->u16PinDir | pstcGpioInit->u16PinAttr;
                WRITE_REG16(*PCRx, u16PCRVal);
            }
        }

        GPIO_Lock();
    }
    return enRet;
}

/**
 * @brief  De-init GPIO register to default value
 * @param  None
 * @retval None
 */
void GPIO_DeInit(void)
{
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);

    /* PORT register unprotect */
    WRITE_REG16(M4_GPIO->PWPR, GPIO_REG_UNPROTECT);

    /* PORTA reset */
    GPIO_Init(GPIO_PORT_A, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTB reset */
    GPIO_Init(GPIO_PORT_B, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTC reset */
    GPIO_Init(GPIO_PORT_C, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTD reset */
    GPIO_Init(GPIO_PORT_D, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTE reset */
    GPIO_Init(GPIO_PORT_E, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTF reset */
    GPIO_Init(GPIO_PORT_F, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTG reset */
    GPIO_Init(GPIO_PORT_G, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTH reset */
    GPIO_Init(GPIO_PORT_H, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTI reset */
    GPIO_Init(GPIO_PORT_I, (GPIO_PIN_00 | GPIO_PIN_01 | GPIO_PIN_02 |   \
                            GPIO_PIN_03 | GPIO_PIN_04 | GPIO_PIN_05 |   \
                            GPIO_PIN_06 | GPIO_PIN_07 | GPIO_PIN_08 |   \
                            GPIO_PIN_09 | GPIO_PIN_10 | GPIO_PIN_11 |   \
                            GPIO_PIN_12 | GPIO_PIN_13), &stcGpioInit);
    /* PORT global register reset */
    WRITE_REG16(M4_GPIO->PSPCR, GPIO_PSPCR_RESET_VALUE);
    WRITE_REG16(M4_GPIO->PCCR, GPIO_PCCR_RESET_VALUE);
    WRITE_REG16(M4_GPIO->PINAER, GPIO_PINAER_RESET_VALUE);

    /* PORT registers protected */
    WRITE_REG16(M4_GPIO->PWPR, GPIO_REG_PROTECT);
}

/**
 * @brief  Initialize GPIO config structure. Fill each pstcGpioInit with default value
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval Ok: GPIO structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset GPIO init structure parameters values */
        pstcGpioInit->u16PinState   = PIN_STATE_RESET;
        pstcGpioInit->u16PinDir     = PIN_DIR_IN;
        pstcGpioInit->u16PinOType   = PIN_OTYPE_CMOS;
        pstcGpioInit->u16PinDrv     = PIN_LOW_DRV;
        pstcGpioInit->u16Latch      = PIN_LATCH_OFF;
        pstcGpioInit->u16PullUp     = PIN_PU_OFF;
        pstcGpioInit->u16Invert     = PIN_INVERT_OFF;
        pstcGpioInit->u16PinIType   = PIN_ITYPE_SMT;
        pstcGpioInit->u16ExInt      = PIN_EXINT_OFF;
        pstcGpioInit->u16PinAttr    = PIN_ATTR_DIGITAL;
    }
    return enRet;
}

/**
 * @brief  GPIO debug port configure. Set debug pins to GPIO
 * @param  [in] u8DebugPort
 *   @arg  GPIO_PIN_SWDIO
 *   @arg  GPIO_PIN_SWCLK
 *   @arg  GPIO_PIN_SWO
 *   @arg  GPIO_PIN_DEBUG_SWD
 *   @arg  GPIO_PIN_TCK
 *   @arg  GPIO_PIN_TMS
 *   @arg  GPIO_PIN_TDO
 *   @arg  GPIO_PIN_TDI
 *   @arg  GPIO_PIN_TRST
 *   @arg  GPIO_PIN_DEBUG_JTAG
 * @param  [in] enNewState
 *   @arg  Enable, set to debug port (SWD/JTAG)
 *   @arg  Disable, set to GPIO
 * @retval None
 */
void GPIO_SetDebugPort(uint8_t u8DebugPort, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_DEBUG_PORT(u8DebugPort));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    GPIO_Unlock();

    if (Enable == enNewState)
    {
        //M4_GPIO->PSPCR |= (uint16_t)((uint16_t)u8DebugPort & 0x1FU);
        SET_REG16_BIT(M4_GPIO->PSPCR, (u8DebugPort & GPIO_PSPCR_SPFE));
    }
    else
    {
        //M4_GPIO->PSPCR &= (uint16_t)(~((uint16_t)u8DebugPort & 0x1FU));
        CLEAR_REG16_BIT(M4_GPIO->PSPCR, (u8DebugPort & GPIO_PSPCR_SPFE));
    }

    GPIO_Lock();
}

/**
 * @brief  Set specified Port Pin function , and turn ON/OFF its sub-funtion
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @param  [in] u8Func: GPIO_FUNC_x, x can be selected from GPIO function definitions
 * @param  [in] u16BFE: GPIO Sub-function enable setting
 *   @arg  PIN_SUBFUNC_ENABLE
 *   @arg  PIN_SUBFUNC_DISABLE
 * @retval None
 */
void GPIO_SetFunc(uint8_t u8Port, uint16_t u16Pin, uint8_t u8Func, uint16_t u16BFE)
{
    __IO uint16_t *PFSRx;
    uint8_t u8PinPos = 0u;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));
    DDL_ASSERT(IS_GPIO_PIN_BFE(u16BFE));

    GPIO_Unlock();

    for (u8PinPos = 0U; u8PinPos < 16U; u8PinPos++)
    {
        if ((u16Pin & (uint16_t)(1UL << u8PinPos)) != 0U)
        {
            PFSRx = (uint16_t *)((uint32_t)(&M4_GPIO->PFSRA0) + \
                                              u8Port * 0x40UL + u8PinPos * 4UL);
            WRITE_REG16(*PFSRx, (u16BFE | u8Func));
        }
    }

    GPIO_Lock();
}

/**
 * @brief  Set the sub-function, it's a global configuration
 * @param  [in] u8Func: GPIO_FUNC_x, x can be selected from GPIO function definitions
 * @retval None
 */
void GPIO_SetSubFunc(uint8_t u8Func)
{
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));

    GPIO_Unlock();

    MODIFY_REG16(M4_GPIO->PCCR, GPIO_PCCR_BFSEL, u8Func);

    GPIO_Lock();
}

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @param  [in] enNewState
 *   @arg  Enable, set specified pin output enable
 *   @arg  Disable, set specified pin output disable
 * @retval None
 */
void GPIO_OE(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO uint16_t *POERx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    POERx = (uint16_t *)((uint32_t)(&M4_GPIO->POERA) + 0x10UL * u8Port);

    if (Enable == enNewState)
    {
        //*POERx |= u16Pin;
        SET_REG16_BIT(*POERx, u16Pin);
    }
    else
    {
        //*POERx &= ((~u16Pin) & 0xFFFFU);
        CLEAR_REG16_BIT(*POERx, u16Pin);
    }
}

/**
 * @brief  GPIO read wait cycle configure.
 * @param  [in] u16ReadWait
 *   @arg  GPIO_READ_WAIT_0
 *   @arg  GPIO_READ_WAIT_1
 *   @arg  GPIO_READ_WAIT_2
 *   @arg  GPIO_READ_WAIT_3
 *   @arg  GPIO_READ_WAIT_4
 *   @arg  GPIO_READ_WAIT_5
 * @retval None
 */
void GPIO_PortReadWait(uint16_t u16ReadWait)
{
    DDL_ASSERT(IS_GPIO_READ_WAIT(u16ReadWait));

    GPIO_Unlock();

    MODIFY_REG16(M4_GPIO->PCCR, GPIO_PCCR_RDWT, u16ReadWait);

    GPIO_Lock();
}

/**
 * @brief  GPIO input MOS always ON configure.
 * @param  [in] u16PortIdx: Port index
 *   @arg  GPIO_PORTA_IDX
 *   @arg  GPIO_PORTB_IDX
 *   @arg  GPIO_PORTC_IDX
 *   @arg  GPIO_PORTD_IDX
 *   @arg  GPIO_PORTE_IDX
 *   @arg  GPIO_PORTF_IDX
 *   @arg  GPIO_PORTG_IDX
 *   @arg  GPIO_PORTH_IDX
 *   @arg  GPIO_PORTI_IDX
 *   @arg  GPIO_PORT_ALL
 * @param  [in] enNewState
 *   @arg  Enable, set input MOS always ON
 *   @arg  Disable, set input MOS turns on while read operation
 * @retval None
 */
void GPIO_AlwaysOn(uint16_t u16PortIdx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_GPIO_PORT(u16PortIdx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    GPIO_Unlock();

    if (Enable == enNewState)
    {
        //M4_GPIO->PINAER |= u16PortIdx;
        SET_REG16_BIT(M4_GPIO->PINAER, u16PortIdx);
    }
    else
    {
        //M4_GPIO->PINAER &= (uint16_t)(~u16PortIdx);
        CLEAR_REG16_BIT(M4_GPIO->PINAER, u16PortIdx);
    }

    GPIO_Lock();
}

/**
 * @brief  Read specified GPIO input data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @retval Specified GPIO port pin input value
 */
en_pin_state_t GPIO_ReadInputPortPin(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PIDRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GET_GPIO_PIN(u16Pin));

    PIDRx = (uint16_t *)((uint32_t)(&M4_GPIO->PIDRA) + 0x10UL * u8Port);

    return (READ_REG16(*PIDRx) & (u16Pin)) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO input data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @retval Specified GPIO port input value
 */
uint16_t GPIO_ReadInputPort(uint8_t u8Port)
{
    __IO uint16_t *PIDRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PIDRx = (uint16_t *)((uint32_t)(&M4_GPIO->PIDRA) + 0x10UL * u8Port);

    return READ_REG16(*PIDRx);
}

/**
 * @brief  Read specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @retval Specified GPIO port pin output value
 */
en_pin_state_t GPIO_ReadOutputPortPin(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GET_GPIO_PIN(u16Pin));

    PODRx = (uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);

    return (*PODRx & (u16Pin)) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO output data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @retval Specified GPIO port output value
 */
uint16_t GPIO_ReadOutputPort(uint8_t u8Port)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PODRx = (uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);

    return READ_REG16(*PODRx);
}

/**
 * @brief  Set specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @retval None
 */
void GPIO_SetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *POSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POSRx = (uint16_t *)((uint32_t)(&M4_GPIO->POSRA) + 0x10UL * u8Port);
    //*POSRx |= u16Pin;
    SET_REG16_BIT(*POSRx, u16Pin);
}

/**
 * @brief  Reset specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @retval None
 */
void GPIO_ResetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PORRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    PORRx = (uint16_t *)((uint32_t)(&M4_GPIO->PORRA) + 0x10UL * u8Port);
    //*PORRx |= u16Pin;
    SET_REG16_BIT(*PORRx, u16Pin);
}

/**
 * @brief  Write specified GPIO data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16PortVal: Pin output value
 *   @arg  PIN_STATE_RESET
 *   @arg  PIN_STATE_SET
 * @retval None
 */
void GPIO_WritePort(uint8_t u8Port, uint16_t u16PortVal)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PODRx = (uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);
    //*PODRx = u16PortVal;
    WRITE_REG16(*PODRx, u16PortVal);

}

/**
 * @brief  Toggle specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (0~15) to select the PIN index
 * @retval None
 */
void GPIO_TogglePins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *POTRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POTRx = (uint16_t *)((uint32_t)(&M4_GPIO->POTRA) + 0x10UL * u8Port);
    //*POTRx |= u16Pin;
    SET_REG16_BIT(*POTRx, u16Pin);
}

/**
 * @}
 */

#endif /* DDL_GPIO_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
