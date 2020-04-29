/**
 *******************************************************************************
 * @file  hc32f4a0_pwc.c
 * @brief This file provides firmware functions to manage the Power Contorl(PWC).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_pwc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_PWC PWC
 * @brief Power Control Driver Library
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Get the backup register address of PWC */
#define PWC_BKRx(num)       ((uint32_t)(&(M4_PWC->BKR0)) + ((uint32_t)(num) << 2U))

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */

/*! Parameter validity check for peripheral in fcg0. */
#define IS_PWC_FCG0_PERIPH(per)                                                 \
(   ((per) & (PWC_FCG0_DCU8    | PWC_FCG0_DCU7 | PWC_FCG0_DCU6      |           \
              PWC_FCG0_DCU5    | PWC_FCG0_DCU4 | PWC_FCG0_DCU3      |           \
              PWC_FCG0_DCU2    | PWC_FCG0_DCU1 | PWC_FCG0_CRC       |           \
              PWC_FCG0_TRNG    | PWC_FCG0_HASH | PWC_FCG0_AES       |           \
              PWC_FCG0_CORDIC  | PWC_FCG0_CTC  | PWC_FCG0_PTDIS     |           \
              PWC_FCG0_FCM     | PWC_FCG0_DMA2 | PWC_FCG0_DMA1      |           \
              PWC_FCG0_KEY     | PWC_FCG0_SRAMB| PWC_FCG0_SRAM4     |           \
              PWC_FCG0_SRAM3   | PWC_FCG0_SRAM2| PWC_FCG0_SRAM1     |           \
              PWC_FCG0_SRAMH)) != (uint32_t)(0x00000000UL))

/*! Parameter validity check for peripheral in fcg1. */
#define IS_PWC_FCG1_PERIPH(per)                                                 \
(   ((per) & (PWC_FCG1_CAN1    | PWC_FCG1_CAN2 | PWC_FCG1_ETHER     |           \
              PWC_FCG1_QSPI    | PWC_FCG1_IIC1 | PWC_FCG1_IIC2      |           \
              PWC_FCG1_IIC3    | PWC_FCG1_IIC4 | PWC_FCG1_IIC5      |           \
              PWC_FCG1_IIC6    | PWC_FCG1_SDIOC1|PWC_FCG1_SDIOC2    |           \
              PWC_FCG1_I2S1    | PWC_FCG1_I2S2 | PWC_FCG1_I2S3      |           \
              PWC_FCG1_I2S4    | PWC_FCG1_SPI1 | PWC_FCG1_SPI2      |           \
              PWC_FCG1_SPI3    | PWC_FCG1_SPI4 | PWC_FCG1_SPI5      |           \
              PWC_FCG1_SPI6    | PWC_FCG1_USBFS| PWC_FCG1_USBHS     |           \
              PWC_FCG1_FMAC1   | PWC_FCG1_FMAC2| PWC_FCG1_FMAC3     |           \
              PWC_FCG1_FMAC4)) != (uint32_t)(0x00000000UL))

/*! Parameter validity check for peripheral in fcg2. */
#define IS_PWC_FCG2_PERIPH(per)                                                 \
(   ((per) & (PWC_FCG2_TMR6_1 | PWC_FCG2_TMR6_2 | PWC_FCG2_TMR6_3   |           \
              PWC_FCG2_TMR6_4 | PWC_FCG2_TMR6_5 | PWC_FCG2_TMR6_6   |           \
              PWC_FCG2_TMR6_7 | PWC_FCG2_TMR6_8 | PWC_FCG2_TMR4_1   |           \
              PWC_FCG2_TMR4_2 | PWC_FCG2_TMR4_3 | PWC_FCG2_HRPWM    |           \
              PWC_FCG2_TMR0_1 | PWC_FCG2_TMR0_2 | PWC_FCG2_EMB      |           \
              PWC_FCG2_TMR2_1 | PWC_FCG2_TMR2_2 | PWC_FCG2_TMR2_3   |           \
              PWC_FCG2_TMR2_4 | PWC_FCG2_TMRA_1 | PWC_FCG2_TMRA_2   |           \
              PWC_FCG2_TMRA_3 | PWC_FCG2_TMRA_4 | PWC_FCG2_TMRA_5   |           \
              PWC_FCG2_TMRA_6 | PWC_FCG2_TMRA_7 | PWC_FCG2_TMRA_8   |           \
              PWC_FCG2_TMRA_9 | PWC_FCG2_TMRA_10| PWC_FCG2_TMRA_11  |           \
              PWC_FCG2_TMRA_12)) != (uint32_t)(0x00000000UL))

/*! Parameter validity check for peripheral in fcg3. */
#define IS_PWC_FCG3_PERIPH(per)                                                 \
(   ((per) & (PWC_FCG3_ADC1    | PWC_FCG3_ADC2     | PWC_FCG3_ADC3     |        \
              PWC_FCG3_DAC1    | PWC_FCG3_DAC2     | PWC_FCG3_CMP1     |        \
              PWC_FCG3_CMP2    | PWC_FCG3_OTS      | PWC_FCG3_DVP      |        \
              PWC_FCG3_SMC     | PWC_FCG3_DMC      | PWC_FCG3_NFC      |        \
              PWC_FCG3_USART1  | PWC_FCG3_USART2   | PWC_FCG3_USART3   |        \
              PWC_FCG3_USART4  | PWC_FCG3_USART5   | PWC_FCG3_USART6   |        \
              PWC_FCG3_USART7  | PWC_FCG3_USART8   | PWC_FCG3_USART9   |        \
              PWC_FCG3_USART10)) != (uint32_t)(0x00000000UL))

/*  Parameter validity check for internal RAM setting of power mode control */
#define IS_PWC_RAM_CONTROL(ram)                                                 \
(   ((ram) & (PWC_RAMPC0_RAMPDC0 | PWC_RAMPC0_RAMPDC1 | PWC_RAMPC0_RAMPDC2 |    \
             PWC_RAMPC0_RAMPDC3  | PWC_RAMPC0_RAMPDC4 | PWC_RAMPC0_RAMPDC5 |    \
             PWC_RAMPC0_RAMPDC6  | PWC_RAMPC0_RAMPDC7 | PWC_RAMPC0_RAMPDC8 |    \
             PWC_RAMPC0_RAMPDC9  | PWC_RAMPC0_RAMPDC10)) != (uint32_t)(0x00000000UL))

/*  Parameter validity check for peripheral RAM setting of power mode control */
#define IS_PWC_PRAM_CONTROL(pram)                                               \
(   ((pram) & (PWC_PRAMLPC_PRAMPDC0 | PWC_PRAMLPC_PRAMPDC1 |                    \
               PWC_PRAMLPC_PRAMPDC2 | PWC_PRAMLPC_PRAMPDC3 |                    \
               PWC_PRAMLPC_PRAMPDC4 | PWC_PRAMLPC_PRAMPDC5 |                    \
               PWC_PRAMLPC_PRAMPDC6 | PWC_PRAMLPC_PRAMPDC7 |                    \
               PWC_PRAMLPC_PRAMPDC8 | PWC_PRAMLPC_PRAMPDC9)) != (uint32_t)(0x00000000UL))

/*  Parameter validity check for RAM setting of MCU operating mode */
#define IS_PWC_RAM_MODE(mode)                                                   \
(   ((mode) == PWC_RAM_HIGH)                    ||                              \
    ((mode) == PWC_RAM_LOW))

/*  Parameter validity check for LVD2 ext. input function setting. */
#define IS_PWC_LVD2_EXINP(func)                                                 \
(   ((func) == PWC_LVD2_EXINP_ON)               ||                              \
    ((func) == PWC_LVD2_EXINP_OFF))

/*  Parameter validity check for LVD function setting. */
#define IS_PWC_LVD_EN(func)                                                     \
(   ((func) & (~(PWC_LVD1_ON | PWC_LVD2_ON))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD interrupt or reset function setting. */
#define IS_PWC_LVD_IR_EN(func)                                                  \
(   ((func) & (~(PWC_LVD1_IR_ON | PWC_LVD2_IR_ON))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD interrupt or reset selection. */
#define IS_PWC_LVD_IR_SEL(sel)                                                  \
(   ((sel) & (~(PWC_LVD1_RST | PWC_LVD2_RST))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD compare output setting. */
#define IS_PWC_LVD_CMP_EN(out)                                                  \
(   ((out) & (~(PWC_LVD1_CMP_ON | PWC_LVD2_CMP_ON))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD digital noise filter function setting. */
#define IS_PWC_LVD_DFS_EN(func)                                                 \
(   ((func) & (~(PWC_LVD1_DF_OFF | PWC_LVD2_DF_OFF))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD digital noise filter clock setting. */
#define IS_PWC_LVD_DFS_CLK(clk)                                                 \
(   ((clk & PWC_PVDFCR_PVD1NFCKS) == PWC_LVD1_DFS_DIV1)     ||                  \
    ((clk & PWC_PVDFCR_PVD1NFCKS) == PWC_LVD1_DFS_DIV2)     ||                  \
    ((clk & PWC_PVDFCR_PVD1NFCKS) == PWC_LVD1_DFS_DIV4)     ||                  \
    ((clk & PWC_PVDFCR_PVD1NFCKS) == PWC_LVD1_DFS_MUL2)     ||                  \
    ((clk & PWC_PVDFCR_PVD2NFCKS) == PWC_LVD2_DFS_DIV1)     ||                  \
    ((clk & PWC_PVDFCR_PVD2NFCKS) == PWC_LVD2_DFS_DIV2)     ||                  \
    ((clk & PWC_PVDFCR_PVD2NFCKS) == PWC_LVD2_DFS_DIV4)     ||                  \
    ((clk & PWC_PVDFCR_PVD2NFCKS) == PWC_LVD2_DFS_MUL2))

/*  Parameter validity check for LVD detect voltage setting. */
#define IS_PWC_LVD_VOLTAGE(vol)                                                 \
(   ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V0)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V1)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V3)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V5)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V6)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V7)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V8)            ||                  \
    ((vol & PWC_PVDLCR_PVD1LVL) == PWC_LVD1_2V9)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V1)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V3)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V5)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V6)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V7)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V8)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_2V9)            ||                  \
    ((vol & PWC_PVDLCR_PVD2LVL) == PWC_LVD2_1V1))

/*  Parameter validity check for LVD NMI function setting. */
#define IS_PWC_LVD_NMI(func)                                                    \
(   ((func) & (~(PWC_LVD1_INT_MASK | PWC_LVD2_INT_MASK))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD trigger setting. */
#define IS_PWC_LVD_TRIG(trig)                                                   \
(   ((trig & PWC_PVDICR_PVD1EDGS) == PWC_LVD1_TRIGGER_FALLING)  ||              \
    ((trig & PWC_PVDICR_PVD1EDGS) == PWC_LVD1_TRIGGER_RISING)   ||              \
    ((trig & PWC_PVDICR_PVD1EDGS) == PWC_LVD1_TRIGGER_BOTH)     ||              \
    ((trig & PWC_PVDICR_PVD2EDGS) == PWC_LVD2_TRIGGER_FALLING)  ||              \
    ((trig & PWC_PVDICR_PVD2EDGS) == PWC_LVD2_TRIGGER_RISING)   ||              \
    ((trig & PWC_PVDICR_PVD2EDGS) == PWC_LVD2_TRIGGER_BOTH))

/*  Parameter validity check for LVD flag. */
#define IS_PWC_LVD_GET_FLAG(flag)                                               \
(   ((flag) & (~(PWC_PVDDSR_PVD1MON | PWC_PVDDSR_PVD2MON))) == ((uint8_t)0x00U))

/*  Parameter validity check for LVD flag. */
#define IS_PWC_LVD_CLR_FLAG(flag)                                               \
(   ((flag) & (~(PWC_PVDDSR_PVD1DETFLG | PWC_PVDDSR_PVD2DETFLG))) == ((uint8_t)0x00U))

/*  Parameter validity check for wakeup0 event. */
#define IS_PWC_WAKEUP0_EVENT(evt)                                               \
(   ((evt) == PWC_PDWKE0_WKE0_0)                ||                              \
    ((evt) == PWC_PDWKE0_WKE0_1)                ||                              \
    ((evt) == PWC_PDWKE0_WKE0_2)                ||                              \
    ((evt) == PWC_PDWKE0_WKE0_3)                ||                              \
    ((evt) == PWC_PDWKE0_WKE1_0)                ||                              \
    ((evt) == PWC_PDWKE0_WKE1_1)                ||                              \
    ((evt) == PWC_PDWKE0_WKE1_2)                ||                              \
    ((evt) == PWC_PDWKE0_WKE1_3))

/*  Parameter validity check for wakeup1 event. */
#define IS_PWC_WAKEUP1_EVENT(evt)                                               \
(   ((evt) == PWC_PDWKE1_WKE2_0)                ||                              \
    ((evt) == PWC_PDWKE1_WKE2_1)                ||                              \
    ((evt) == PWC_PDWKE1_WKE2_2)                ||                              \
    ((evt) == PWC_PDWKE1_WKE2_3)                ||                              \
    ((evt) == PWC_PDWKE1_WKE3_0)                ||                              \
    ((evt) == PWC_PDWKE1_WKE3_1)                ||                              \
    ((evt) == PWC_PDWKE1_WKE3_2)                ||                              \
    ((evt) == PWC_PDWKE1_WKE3_3))

/*  Parameter validity check for wakeup2 event. */
#define IS_PWC_WAKEUP2_EVENT(evt)                                               \
(   ((evt) == PWC_PDWKE2_VD1WKE)                ||                              \
    ((evt) == PWC_PDWKE2_VD2WKE)                ||                              \
    ((evt) == PWC_PDWKE2_RTCPRDWKE)             ||                              \
    ((evt) == PWC_PDWKE2_RTCALMWKE)             ||                              \
    ((evt) == PWC_PDWKE2_XTAL32ERWKE)           ||                              \
    ((evt) == PWC_PDWKE2_WKTMWKE))

/*  Parameter validity check for wakeup0 flag. */
#define IS_PWC_WAKEUP0_FLAG(flag)                                               \
(   ((flag) == PWC_PDWKF0_PTWK0F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK1F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK2F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK3F)               ||                              \
    ((flag) == PWC_PDWKF0_VD1WKF)               ||                              \
    ((flag) == PWC_PDWKF0_VD2WKF))

/*  Parameter validity check for wakeup1 flag. */
#define IS_PWC_WAKEUP1_FLAG(flag)                                               \
(       ((flag) == PWC_PDWKF1_RTCPRDWKF)        ||                              \
        ((flag) == PWC_PDWKF1_RTCALMWKF)        ||                              \
        ((flag) == PWC_PDWKF1_XTAL32ERWKF)      ||                              \
        ((flag) == PWC_PDWKF1_WKTMWKF))

/*  Parameter validity check for power down mode wakeup event. */
#define IS_PWC_WAKEUP_EVENT(event)                                              \
(   ((event) == PWC_PD_WKUP_LVD1)               ||                              \
    ((event) == PWC_PD_WKUP_LVD2)               ||                              \
    ((event) == PWC_PD_WKUP_WKP0)               ||                              \
    ((event) == PWC_PD_WKUP_WKP1)               ||                              \
    ((event) == PWC_PD_WKUP_WKP2)               ||                              \
    ((event) == PWC_PD_WKUP_WKP3))

/*  Parameter validity check for power down mode wakeup trigger edge. */
#define IS_PWC_WAKEUP_TRIG(edge)                                                \
(   ((edge) == PWC_PD_WKUP_FALLING)             ||                              \
    ((edge) == PWC_PD_WKUP_RISING))


/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP0_FLAG(flag)                                                 \
(   ((flag) == PWC_PDWKF0_PTWK0F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK1F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK2F)               ||                              \
    ((flag) == PWC_PDWKF0_PTWK3F)               ||                              \
    ((flag) == PWC_PDWKF0_VD1WKF)               ||                              \
    ((flag) == PWC_PDWKF0_VD2WKF))

/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP1_FLAG(flag)                                                 \
(   ((flag) == PWC_PDWKF1_RTCPRDWKF)            ||                              \
    ((flag) == PWC_PDWKF1_RTCALMWKF)            ||                              \
    ((flag) == PWC_PDWKF1_XTAL32ERWKF)          ||                              \
    ((flag) == PWC_PDWKF1_WKTMWKF))

/*! Parameter validity check for stop mode drive capacity. */
#define IS_PWC_STOP_DRV(drv)                                                    \
(   ((drv) == PWC_STOP_DRV_HIGH)                ||                              \
    ((drv) == PWC_STOP_DRV_LOW))

/*! Parameter validity check for clock setting after wake-up from stop mode. */
#define IS_PWC_STOP_CLK(clk)                                                    \
(   ((clk) == PWC_STOP_CLK_KEEP)                ||                              \
    ((clk) == PWC_STOP_CLK_MRC))

/*! Parameter validity check for flash wait setting after wake-up from stop mode. */
#define IS_PWC_STOP_FLASH_WAIT(wait)                                            \
(   ((wait) == PWC_STOP_FLASH_WAIT)             ||                              \
    ((wait) == PWC_STOP_FLASH_NOWAIT))

/*! Parameter validity check for ex-bus setting in stop mode. */
#define IS_PWC_STOP_EXBUS(bus)                                                  \
(   ((bus) == PWC_STOP_EXBUS_HIZ)               ||                              \
    ((bus) == PWC_STOP_EXBUS_HOLD))

/*! Parameter validity check for VBAT Reference Voltage. */
#define IS_PWC_VBAT_REF_VOL(vol)                                                \
(   ((vol) == PWC_VBAT_REF_VOL_2P0V)            ||                              \
    ((vol) == PWC_VBAT_REF_VOL_1P8V))

/*! Parameter validity check for BACKUP RAM Flag. */
#define IS_PWC_BACKUP_RAM_FLAG(flag)                                            \
(   0U != ((flag) & (PWC_BACKUP_RAM_FLAG_RAMPDF | PWC_BACKUP_RAM_FLAG_RAMVALID)))

/*! Parameter validity check for Backup Register Number. */
#define IS_PWC_BACKUP_REGISTER_NUMBER(num)      ((num) <= 127U)

/*! Parameter validity check for WKT Clock Source. */
#define IS_PWC_WKT_CLK_SRC(src)                                                 \
(   ((src) == PWC_WKT_CLK_SRC_64HZ)             ||                              \
    ((src) == PWC_WKT_CLK_SRC_XTAL32)           ||                              \
    ((src) == PWC_WKT_CLK_SRC_RTCLRC))

/*! Parameter validity check for WKT Comparision Value. */
#define IS_PWC_WKT_COMPARISION_VALUE(val)       ((val) <= 0x0FFFU)

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
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */

/**
 * @brief  Enter power down mode.
 * @param  None
 * @retval None
 */
void PWC_EnterPowerDownMode(void)
{
    PWC_REG_WRITE_ENABLE();
    bM4_PWC->STPMCR_b.STOP = 1U;
    bM4_PWC->PWRC0_b.PWDN = 1U;
    PWC_REG_WRITE_DISABLE();

    __WFI();
}

/**
 * @brief  Enter stop mode.
 * @param  None
 * @retval None
 */
void PWC_EnterStopMode(void)
{
    PWC_REG_WRITE_ENABLE();

    bM4_PWC->STPMCR_b.STOP = 1U;

    PWC_REG_WRITE_DISABLE();

     __WFI();
}

/**
 * @brief  Enter sleep mode.
 * @param  None
 * @retval None
 */
void PWC_EnterSleepMode(void)
{
    PWC_REG_WRITE_ENABLE();

    bM4_PWC->STPMCR_b.STOP = 0U;

    PWC_REG_WRITE_DISABLE();

     __WFI();
}

/**
 * @brief  Enable or disable the FCG0 peripheral clock.
 * @param [in] u32Fcg0Periph, The peripheral in FCG0.
 *   @arg PWC_FCG0_SRAMH
 *   @arg PWC_FCG0_SRAM1
 *   @arg PWC_FCG0_SRAM2
 *   @arg PWC_FCG0_SRAM3
 *   @arg PWC_FCG0_SRAM4
 *   @arg PWC_FCG0_SRAMB
 *   @arg PWC_FCG0_KEY
 *   @arg PWC_FCG0_DMA1
 *   @arg PWC_FCG0_DMA2
 *   @arg PWC_FCG0_FCM
 *   @arg PWC_FCG0_PTDIS
 *   @arg PWC_FCG0_CTC
 *   @arg PWC_FCG0_CORDIC
 *   @arg PWC_FCG0_AES
 *   @arg PWC_FCG0_HASH
 *   @arg PWC_FCG0_TRNG
 *   @arg PWC_FCG0_CRC
 *   @arg PWC_FCG0_DCU1
 *   @arg PWC_FCG0_DCU2
 *   @arg PWC_FCG0_DCU3
 *   @arg PWC_FCG0_DCU4
 *   @arg PWC_FCG0_DCU5
 *   @arg PWC_FCG0_DCU6
 *   @arg PWC_FCG0_DCU7
 *   @arg PWC_FCG0_DCU8
 * @param [in]enNewState, The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG0_PERIPH(u32Fcg0Periph));

    PWC_FCG0_WRITE_ENABLE();

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG0, u32Fcg0Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG0, u32Fcg0Periph);
    }

    PWC_FCG0_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the FCG1 peripheral clock.
 * @param [in] u32Fcg1Periph, The peripheral in FCG1.
 *   @arg PWC_FCG1_CAN1
 *   @arg PWC_FCG1_CAN2
 *   @arg PWC_FCG1_ETHER
 *   @arg PWC_FCG1_QSPI
 *   @arg PWC_FCG1_IIC1
 *   @arg PWC_FCG1_IIC2
 *   @arg PWC_FCG1_IIC3
 *   @arg PWC_FCG1_IIC4
 *   @arg PWC_FCG1_IIC5
 *   @arg PWC_FCG1_IIC6
 *   @arg PWC_FCG1_SDIOC1
 *   @arg PWC_FCG1_SDIOC2
 *   @arg PWC_FCG1_I2S1
 *   @arg PWC_FCG1_I2S2
 *   @arg PWC_FCG1_I2S3
 *   @arg PWC_FCG1_I2S4
 *   @arg PWC_FCG1_SPI1
 *   @arg PWC_FCG1_SPI2
 *   @arg PWC_FCG1_SPI3
 *   @arg PWC_FCG1_SPI4
 *   @arg PWC_FCG1_SPI5
 *   @arg PWC_FCG1_SPI6
 *   @arg PWC_FCG1_USBFS
 *   @arg PWC_FCG1_USBHS
 *   @arg PWC_FCG1_FIR1
 *   @arg PWC_FCG1_FIR2
 *   @arg PWC_FCG1_FIR3
 *   @arg PWC_FCG1_FIR4
 * @param [in]enNewState, The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG1_PERIPH(u32Fcg1Periph));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG1, u32Fcg1Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG1, u32Fcg1Periph);
    }
}

/**
 * @brief  Enable or disable the FCG2 peripheral clock.
 * @param [in] u32Fcg2Periph, The peripheral in FCG2.
 *   @arg PWC_FCG2_TMR6_1
 *   @arg PWC_FCG2_TMR6_2
 *   @arg PWC_FCG2_TMR6_3
 *   @arg PWC_FCG2_TMR6_4
 *   @arg PWC_FCG2_TMR6_5
 *   @arg PWC_FCG2_TMR6_6
 *   @arg PWC_FCG2_TMR6_7
 *   @arg PWC_FCG2_TMR6_8
 *   @arg PWC_FCG2_TMR4_1
 *   @arg PWC_FCG2_TMR4_2
 *   @arg PWC_FCG2_TMR4_3
 *   @arg PWC_FCG2_HRPWM
 *   @arg PWC_FCG2_TMR0_1
 *   @arg PWC_FCG2_TMR0_2
 *   @arg PWC_FCG2_EMB
 *   @arg PWC_FCG2_TMR2_1
 *   @arg PWC_FCG2_TMR2_2
 *   @arg PWC_FCG2_TMR2_3
 *   @arg PWC_FCG2_TMR2_4
 *   @arg PWC_FCG2_TMRA_1
 *   @arg PWC_FCG2_TMRA_2
 *   @arg PWC_FCG2_TMRA_3
 *   @arg PWC_FCG2_TMRA_4
 *   @arg PWC_FCG2_TMRA_5
 *   @arg PWC_FCG2_TMRA_6
 *   @arg PWC_FCG2_TMRA_7
 *   @arg PWC_FCG2_TMRA_8
 *   @arg PWC_FCG2_TMRA_9
 *   @arg PWC_FCG2_TMRA_10
 *   @arg PWC_FCG2_TMRA_11
 *   @arg PWC_FCG2_TMRA_12
 * @param [in]enNewState, The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG2_PERIPH(u32Fcg2Periph));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG2, u32Fcg2Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG2, u32Fcg2Periph);
    }
}

/**
 * @brief  Enable or disable the FCG3 peripheral clock.
 * @param [in] u32Fcg3Periph, The peripheral in FCG3.
 *   @arg PWC_FCG3_ADC1
 *   @arg PWC_FCG3_ADC2
 *   @arg PWC_FCG3_ADC3
 *   @arg PWC_FCG3_DAC1
 *   @arg PWC_FCG3_DAC2
 *   @arg PWC_FCG3_CMP1
 *   @arg PWC_FCG3_CMP2
 *   @arg PWC_FCG3_OTS
 *   @arg PWC_FCG3_DVP
 *   @arg PWC_FCG3_SMC
 *   @arg PWC_FCG3_DMC
 *   @arg PWC_FCG3_NFC
 *   @arg PWC_FCG3_USART1
 *   @arg PWC_FCG3_USART2
 *   @arg PWC_FCG3_USART3
 *   @arg PWC_FCG3_USART4
 *   @arg PWC_FCG3_USART5
 *   @arg PWC_FCG3_USART6
 *   @arg PWC_FCG3_USART7
 *   @arg PWC_FCG3_USART8
 *   @arg PWC_FCG3_USART9
 *   @arg PWC_FCG3_USART10
 * @param [in]enNewState, The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG3_PERIPH(u32Fcg3Periph));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG3, u32Fcg3Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG3, u32Fcg3Periph);
    }
}

/**
 * @brief RAM configuration for MCU operating mode and power down control.
 * @param [in] pstcRamConfig, Pointer to a stc_pwc_ram_config_t structure that
 *                            contains configuration information.
 * @param [in] pstcRamConfig->u32RamCtrl, Internal RAM setting for power mode.
 *   @arg PWC_RAMPC0_RAMPDC0        0x20000000 ~ 0x2000FFFF
 *   @arg PWC_RAMPC0_RAMPDC1        0x20010000 ~ 0x2001FFFF
 *   @arg PWC_RAMPC0_RAMPDC2        0x20020000 ~ 0x2002FFFF
 *   @arg PWC_RAMPC0_RAMPDC3        0x20030000 ~ 0x2003FFFF
 *   @arg PWC_RAMPC0_RAMPDC4        0x20040000 ~ 0x2004FFFF
 *   @arg PWC_RAMPC0_RAMPDC5        0x20050000 ~ 0x20057FFF
 *   @arg PWC_RAMPC0_RAMPDC6        0x20058000 ~ 0x2005FFFF
 *   @arg PWC_RAMPC0_RAMPDC7        0x1FFE0000 ~ 0x1FFE7FFF
 *   @arg PWC_RAMPC0_RAMPDC8        0x1FFE8000 ~ 0x1FFEFFFF
 *   @arg PWC_RAMPC0_RAMPDC9        0x1FFF0000 ~ 0x`FFF7FFF
 *   @arg PWC_RAMPC0_RAMPDC10       0x1FFF8000 ~ 0x1FFFFFFF
 * @param [in] pstcRamConfig->u32PRamCtrl, Peripheral RAM setting for power mode.
 *   @arg PWC_PRAMLPC_PRAMPDC0      CAN1 RAM
 *   @arg PWC_PRAMLPC_PRAMPDC1      CAN2 RAM
 *   @arg PWC_PRAMLPC_PRAMPDC2      CACHE RAM
 *   @arg PWC_PRAMLPC_PRAMPDC3      USBFS RAM
 *   @arg PWC_PRAMLPC_PRAMPDC4      USBHS RAM
 *   @arg PWC_PRAMLPC_PRAMPDC5      Ethernet Tx RAM
 *   @arg PWC_PRAMLPC_PRAMPDC6      Ethernet Rx RAM
 *   @arg PWC_PRAMLPC_PRAMPDC7      SDIO1 RAM
 *   @arg PWC_PRAMLPC_PRAMPDC8      SDIO2 RAM
 *   @arg PWC_PRAMLPC_PRAMPDC9      NFC RAM
 * @param [in] pstcRamConfig->u16RamMode, RAM setting for Operating mode.
 *   @arg PWC_RAM_HIGH              MCU operating under high frequncy (lower than 240MHz)
 *   @arg PWC_RAM_LOW               MCU operating under low frequncy (lower than 8MHz)
 * @retval Ok: RAM config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_RamConfig(const stc_pwc_ram_config_t *pstcRamConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcRamConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_RAM_CONTROL(pstcRamConfig->u32RamCtrl));
        DDL_ASSERT(IS_PWC_PRAM_CONTROL(pstcRamConfig->u32PRamCtrl));
        DDL_ASSERT(IS_PWC_RAM_MODE(pstcRamConfig->u16RamMode));

        PWC_REG_WRITE_ENABLE();

        WRITE_REG32(M4_PWC->RAMPC0, pstcRamConfig->u32RamCtrl);
        WRITE_REG32(M4_PWC->PRAMLPC, pstcRamConfig->u32PRamCtrl);
        WRITE_REG16(M4_PWC->RAMOPM, pstcRamConfig->u16RamMode);

        PWC_REG_WRITE_DISABLE();
    }
    return enRet;
}

/**
 * @brief  Initialize LVD config structure. Fill each pstcGpioInit with default value
 * @param  [in] pstcLvdConfig: Pointer to a stc_pwc_lvd_config_t structure that
 *                            contains configuration information.
 * @retval Ok: LVD structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_config_t *pstcLvdConfig)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcLvdConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset LVD init structure parameters values */
        pstcLvdConfig->u8LvdEn          = PWC_LVD1_OFF | PWC_LVD2_OFF;
        pstcLvdConfig->u8Lvd2ExtInEn    = PWC_LVD2_EXINP_OFF;
        pstcLvdConfig->u8LvdCmpOutEn    = PWC_LVD1_CMP_OFF | PWC_LVD2_CMP_OFF;
        pstcLvdConfig->u8LvdIntRstSel   = PWC_LVD1_INT | PWC_LVD2_INT;
        pstcLvdConfig->u8LvdIntRstEn    = PWC_LVD1_IR_OFF | PWC_LVD2_IR_OFF;
        pstcLvdConfig->u8FilterEn       = PWC_LVD1_DF_ON | PWC_LVD2_DF_ON;
        pstcLvdConfig->u8FilterClk      = PWC_LVD1_DFS_DIV4 | PWC_LVD2_DFS_DIV4;
        pstcLvdConfig->u8LvdVoltage     = PWC_LVD1_2V0 | PWC_LVD2_2V1;
        pstcLvdConfig->u8LvdNmiEn       = PWC_LVD1_INT_NONMASK | PWC_LVD2_INT_NONMASK;
        pstcLvdConfig->u8LvdTrigger     = PWC_LVD1_TRIGGER_FALLING | PWC_LVD2_TRIGGER_FALLING;
    }
    return enRet;
}

/**
 * @brief LVD configuration.
 * @param [in] pstcLvdConfig, Pointer to a stc_pwc_lvd_config_t structure that
 *                            contains configuration information.
 * @retval Ok: LVD initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_LVD_Init(const stc_pwc_lvd_config_t *pstcLvdConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcLvdConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_LVD2_EXINP(pstcLvdConfig->u8Lvd2ExtInEn));
        DDL_ASSERT(IS_PWC_LVD_EN(pstcLvdConfig->u8LvdEn));
        DDL_ASSERT(IS_PWC_LVD_IR_EN(pstcLvdConfig->u8LvdIntRstEn));
        DDL_ASSERT(IS_PWC_LVD_IR_SEL(pstcLvdConfig->u8LvdIntRstSel));
        DDL_ASSERT(IS_PWC_LVD_CMP_EN(pstcLvdConfig->u8LvdCmpOutEn));
        DDL_ASSERT(IS_PWC_LVD_DFS_EN(pstcLvdConfig->u8FilterEn));
        DDL_ASSERT(IS_PWC_LVD_DFS_CLK(pstcLvdConfig->u8FilterClk));
        DDL_ASSERT(IS_PWC_LVD_VOLTAGE(pstcLvdConfig->u8LvdVoltage));
        DDL_ASSERT(IS_PWC_LVD_NMI(pstcLvdConfig->u8LvdNmiEn));
        DDL_ASSERT(IS_PWC_LVD_TRIG(pstcLvdConfig->u8LvdTrigger));

        PWC_LVD_REG_WRITE_ENABLE();

        WRITE_REG8(M4_PWC->PVDCR0, (pstcLvdConfig->u8LvdEn | pstcLvdConfig->u8Lvd2ExtInEn));
        /* config PVDCMPOE in before PVDIRE*/
        WRITE_REG8(M4_PWC->PVDCR1, pstcLvdConfig->u8LvdCmpOutEn);
        SET_REG8_BIT(M4_PWC->PVDCR1, (pstcLvdConfig->u8LvdIntRstSel | pstcLvdConfig->u8LvdIntRstEn));

        WRITE_REG8(M4_PWC->PVDFCR, (pstcLvdConfig->u8FilterEn | pstcLvdConfig->u8FilterClk));
        WRITE_REG8(M4_PWC->PVDLCR, pstcLvdConfig->u8LvdVoltage);
        WRITE_REG8(M4_PWC->PVDICR, (pstcLvdConfig->u8LvdNmiEn | pstcLvdConfig->u8LvdTrigger));

        PWC_LVD_REG_WRITE_DISABLE();
    }
    return enRet;
}

/**
 * @brief  Get LVD flag.
 * @param  [in] u8Flag, LVD flag to be get
 *   @arg    PWC_PVDDSR_PVD1DETFLG, VCC across VLVD1
 *   @arg    PWC_PVDDSR_PVD2DETFLG  VCC across VLVD2
 *   @arg    PWC_PVDDSR_PVD1MON, VCC > VLVD1
 *   @arg    PWC_PVDDSR_PVD2MON, VCC > VLVD2
 * @note   PVDxDETFLG is avaliable when PVDCR0.PVDxEN and PVDCR1.PVDxCMPOE are set to '1'
 * @retval An en_flag_status_t enumeration value:
 *           - Set
 *           - Reset
 */
en_flag_status_t PWC_LVD_GetFlag(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_LVD_GET_FLAG(u8Flag));
    return READ_REG8_BIT(M4_PWC->PVDDSR, u8Flag) ? Set:Reset;
}

/**
 * @brief  Clear LVD flag.
 * @param  [in] u8Flag, LVD flag to be cleared.
 *  @arg    PWC_PVDDSR_PVD1DETFLG, LVD1 detect flag
 *  @arg    PWC_PVDDSR_PVD2DETFLG, LVD2 detect flag
 * @retval None
 */
void PWC_LVD_ClrFlag(uint8_t u8Flag)
{
    PWC_LVD_REG_WRITE_ENABLE();
    DDL_ASSERT(IS_PWC_LVD_CLR_FLAG(u8Flag));
    CLEAR_REG8_BIT(M4_PWC->PVDDSR, u8Flag);
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup0Evt, Wakeup pin group 0 and 1.
 *  @arg    PWC_PDWKE0_WKE0_0
 *  @arg    PWC_PDWKE0_WKE0_1
 *  @arg    PWC_PDWKE0_WKE0_2
 *  @arg    PWC_PDWKE0_WKE0_3
 *  @arg    PWC_PDWKE0_WKE1_0
 *  @arg    PWC_PDWKE0_WKE1_1
 *  @arg    PWC_PDWKE0_WKE1_2
 *  @arg    PWC_PDWKE0_WKE1_3
 * @param  [in] enNewState, The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup0Cmd(uint8_t u8Wkup0Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP0_EVENT(u8Wkup0Evt));

    PWC_REG_WRITE_ENABLE();

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE0, u8Wkup0Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE0, u8Wkup0Evt);
    }

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup1Evt, Wakeup pin group 0 and 1.
 *  @arg    PWC_PDWKE1_WKE2_0
 *  @arg    PWC_PDWKE1_WKE2_1
 *  @arg    PWC_PDWKE1_WKE2_2
 *  @arg    PWC_PDWKE1_WKE2_3
 *  @arg    PWC_PDWKE1_WKE3_0
 *  @arg    PWC_PDWKE1_WKE3_1
 *  @arg    PWC_PDWKE1_WKE3_2
 *  @arg    PWC_PDWKE1_WKE3_3
 * @param  [in] enNewState, The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup1Cmd(uint8_t u8Wkup1Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP1_EVENT(u8Wkup1Evt));

    PWC_REG_WRITE_ENABLE();

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE1, u8Wkup1Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE1, u8Wkup1Evt);
    }

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup2Evt, LVD, RTC, XTAL32 and wakeup timer.
 *  @arg    PWC_PDWKE2_VD1WKE
 *  @arg    PWC_PDWKE2_VD2WKE
 *  @arg    PWC_PDWKE2_RTCPRDWKE
 *  @arg    PWC_PDWKE2_RTCALMWKE
 *  @arg    PWC_PDWKE2_XTAL32ERWKE
 *  @arg    PWC_PDWKE2_WKTMWKE
 * @param  [in] enNewState, The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup2Cmd(uint8_t u8Wkup2Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP2_EVENT(u8Wkup2Evt));

    PWC_REG_WRITE_ENABLE();

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE2, u8Wkup2Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE2, u8Wkup2Evt);
    }

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Power down mode wake up event trigger config.
 * @param  [in] u8WkupEvt, LVD and wakeup pin.
 *  @arg    PWC_PD_WKUP_LVD1
 *  @arg    PWC_PD_WKUP_LVD2
 *  @arg    PWC_PD_WKUP_WKP0
 *  @arg    PWC_PD_WKUP_WKP1
 *  @arg    PWC_PD_WKUP_WKP2
 *  @arg    PWC_PD_WKUP_WKP3
 * @param  [in] u8TrigEdge, The trigger edge.
 *  @arg PWC_PD_WKUP_FALLING
 *  @arg PWC_PD_WKUP_RISING
 * @retval None
 */
void PWC_PdWakeupTrigConfig(uint8_t u8WkupEvt, uint8_t u8TrigEdge)
{
    DDL_ASSERT(IS_PWC_WAKEUP_EVENT(u8WkupEvt));
    DDL_ASSERT(IS_PWC_WAKEUP_TRIG(u8TrigEdge));

    PWC_REG_WRITE_ENABLE();

    if (PWC_PD_WKUP_RISING == u8TrigEdge)
    {
        SET_REG8_BIT(M4_PWC->PDWKES, u8WkupEvt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKES, u8WkupEvt);
    }

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Get wake up event flag.
 * @param  [in] u8Flag, Wake up event.
 *  @arg    PWC_PDWKF0_PTWK0F
 *  @arg    PWC_PDWKF0_PTWK1F
 *  @arg    PWC_PDWKF0_PTWK2F
 *  @arg    PWC_PDWKF0_PTWK3F
 *  @arg    PWC_PDWKF0_VD1WKF
 *  @arg    PWC_PDWKF0_VD2WKF
 * @retval en_flag_status_t
 */
en_flag_status_t PWC_GetWakeup0Flag(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_WKUP0_FLAG(u8Flag));

    return (READ_REG8_BIT(M4_PWC->PDWKF0, u8Flag) ? Set : Reset);
}

/**
 * @brief  Get wake up event flag.
 * @param  [in] u8Flag, Wake up event.
 *  @arg    PWC_PDWKF1_RTCPRDWKF
 *  @arg    PWC_PDWKF1_RTCALMWKF
 *  @arg    PWC_PDWKF1_XTAL32ERWK
 *  @arg    PWC_PDWKF1_WKTMWKF
 * @retval en_flag_status_t
 */
en_flag_status_t PWC_GetWakeup1Flag(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_WKUP1_FLAG(u8Flag));

    return (READ_REG8_BIT(M4_PWC->PDWKF1, u8Flag) ? Set : Reset);
}

/**
 * @brief  HRC clock power config.
 * @param  [in] enNewState, The new state of HRC power state.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_HrcPwrCmd(en_functional_state_t enNewState)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_PWC->PWRC1_b.VHRCSD, enNewState);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  PLLA clock power config.
 * @param  [in] enNewState, The new state of PLLA power state.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PllAPwrCmd(en_functional_state_t enNewState)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_PWC->PWRC1_b.VPLLASD, enNewState);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  PLLH clock power config.
 * @param  [in] enNewState, The new state of PLLH power state.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PllHPwrCmd(en_functional_state_t enNewState)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_PWC->PWRC1_b.VPLLHSD, enNewState);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Switch high speed to ultra low speed, set the drive ability.
 * @param  None
 * @retval None
 * @note   Before calling this API, please switch system clock to the required
 *         low speed frequncy in advance, and make sure NO any flash program
 *         or erase operation background.
 */
void PWC_HighSpeedToLowSpeed(void)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_EFM->FRMC_b.LVM, 0x01UL);
    WRITE_REG16(M4_PWC->RAMOPM, PWC_RAM_LOW);
    WRITE_REG8(M4_PWC->PWRC2, 0x00UL);
    WRITE_REG8(M4_PWC->PWRC3, 0x00UL);
    MODIFY_REG8(M4_PWC->PWRC2, PWC_PWRC2_DVS ,PWC_NOR_DRV_LOW);
    DDL_Delay1ms(1UL);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Switch ultra low speed to high speed, set the drive ability.
 * @param  None
 * @retval None
 * @note   After calling this API, the system clock is able to switch high frequncy.
 */
void PWC_LowSpeedToHighSpeed(void)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG8(M4_PWC->PWRC2, 0x0FUL);
    WRITE_REG8(M4_PWC->PWRC3, 0xFFUL);
    SET_REG8_BIT(M4_PWC->PWRC2, PWC_NOR_DRV_HIGH);
    DDL_Delay1ms(1UL);
    WRITE_REG32(bM4_EFM->FRMC_b.LVM, 0x00UL);
    WRITE_REG16(M4_PWC->RAMOPM, PWC_RAM_HIGH);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  ADC buffer config.
 * @param  [in] enNewState, The new state of ADC buffer.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_AdcBufCmd(en_functional_state_t enNewState)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_PWC->PWRC4_b.ADBUFE, enNewState);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  ADC internal channel sampling selection.
 * @param  [in] u8AdcInternVol, The sampling voltage for ADC internal channel.
 *  @arg PWC_AD_INTERN_REF
 *  @arg PWC_AD_VBAT_DIV2
 * @retval None
 */
void PWC_AdcInternVolSel(uint8_t u8AdcInternVol)
{
    PWC_REG_WRITE_ENABLE();

    WRITE_REG32(bM4_PWC->PWRC4_b.ADBUFS, u8AdcInternVol);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Initialize Power down mode config structure. Fill each pstcPDModeConfig with default value
 * @param  [in] pstcPDModeConfig: Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval Ok: Power down mode structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PowerDownStructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcPDModeConfig->u8IOState = PWC_PD_IO_STATE1;
        pstcPDModeConfig->u8PDMode = PWC_PD_MODE1;
        pstcPDModeConfig->u8WkUpSpeed = PWC_PD_WKUP_SLOW;
    }
    return enRet;
}

/**
 * @brief  Power down mode config structure.
 * @param  [in] pstcPDModeConfig: Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval Ok: Power down mode config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PowerDownConfig(const stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        PWC_REG_WRITE_ENABLE();

        MODIFY_REG8(M4_PWC->PWRC0, (PWC_PWRC0_IORTN | PWC_PWRC0_PDMDS),         \
                    (pstcPDModeConfig->u8IOState | pstcPDModeConfig->u8PDMode));
        WRITE_REG32(bM4_PWC->PWRC1_b.PDTS, pstcPDModeConfig->u8WkUpSpeed);

        PWC_REG_WRITE_DISABLE();
    }
    return enRet;
}

/**
 * @brief Stop mode config.
 * @param [in] pstcStopConfig, chip config before entry stop mode.
 *   @arg  u8StopDrv, MCU from which speed mode entry stop mode.
 *   @arg  u16ClkKeep, System clock setting after wake-up from stop mode.
 *   @arg  u16FlashWait, Whether wait flash stable after wake-up from stop mode.
 *   @arg  u16ExBusHold, ExBus status in stop mode.
 * @retval Ok: Stop mode config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_config *pstcStopConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_STOP_DRV(pstcStopConfig->u8StopDrv));
        DDL_ASSERT(IS_PWC_STOP_CLK(pstcStopConfig->u16ClkKeep));
        DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(pstcStopConfig->u16FlashWait));
        DDL_ASSERT(IS_PWC_STOP_EXBUS(pstcStopConfig->u16ExBusHold));

        PWC_REG_WRITE_ENABLE();

        MODIFY_REG8(M4_PWC->PWRC1, PWC_PWRC1_STPDAS, pstcStopConfig->u8StopDrv);

        MODIFY_REG16(M4_PWC->STPMCR,                                            \
                    (PWC_STPMCR_EXBUSOE | PWC_STPMCR_CKSMRC | PWC_STPMCR_FLNWT),\
                    (pstcStopConfig->u16ExBusHold | pstcStopConfig->u16ClkKeep |\
                    pstcStopConfig->u16FlashWait));

        PWC_REG_WRITE_DISABLE();
    }
    return enRet;
}

/**
 * @brief  Initialize stop mode config structure. Fill each pstcStopConfig with default value
 * @param  [in] pstcStopConfig: Pointer to a stc_pwc_stop_mode_config structure that
 *                            contains configuration information.
 * @retval Ok: Stop down mode structure initilize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_StopStructInit(stc_pwc_stop_mode_config *pstcStopConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcStopConfig->u8StopDrv = PWC_STOP_DRV_HIGH;
        pstcStopConfig->u16ExBusHold = PWC_STOP_EXBUS_HIZ;
        pstcStopConfig->u16ClkKeep = PWC_STOP_CLK_KEEP;
        pstcStopConfig->u16FlashWait = PWC_STOP_FLASH_WAIT;
    }
    return enRet;
}
/**
 * @brief Stop mode wake up clock config.
 * @param [in] u16ClkKeep, System clock setting after wake-up from stop mode.
 *   @arg PWC_STOP_CLK_KEEP
 *   @arg PWC_STOP_CLK_MRC
 * @retval None
 */
void PWC_StopClockKeepConfig(uint16_t u16ClkKeep)
{
    DDL_ASSERT(IS_PWC_STOP_CLK(u16ClkKeep));

    PWC_REG_WRITE_ENABLE();

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_CKSMRC, u16ClkKeep);

    PWC_REG_WRITE_ENABLE();
}

/**
 * @brief Stop mode wake up flash wait config.
 * @param [in] u16FlashWait, Whether wait flash stable after wake-up from stop mode.
 *   @arg PWC_STOP_FLASH_WAIT
 *   @arg PWC_STOP_FLASH_NOWAIT
 * @retval None
 */
void PWC_StopFlashWaitConfig(uint16_t u16FlashWait)
{
    DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(u16FlashWait));

    PWC_REG_WRITE_ENABLE();

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_FLNWT, u16FlashWait);

    PWC_REG_WRITE_ENABLE();
}

/**
 * @brief Stop mode ex-bus status config.
 * @param [in] u16ExBusHold, ExBus status in stop mode.
 *   @arg PWC_STOP_EXBUS_HIZ
 *   @arg PWC_STOP_EXBUS_HOLD
 * @retval None
 */
void PWC_StopExBusHoldConfig(uint16_t u16ExBusHold)
{
    DDL_ASSERT(IS_PWC_STOP_EXBUS(u16ExBusHold));

    PWC_REG_WRITE_ENABLE();

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_EXBUSOE, u16ExBusHold);

    PWC_REG_WRITE_ENABLE();
}

/**
 * @brief Stop mode driver capacity config.
 * @param [in] u8StopDrv, Drive capacity while enter stop mode.
 *   @arg  PWC_STOP_DRV_HIGH
 *   @arg  PWC_STOP_DRV_LOW
 * @retval None
 */
void PWC_StopDrvConfig(uint8_t u8StopDrv)
{
    DDL_ASSERT(IS_PWC_STOP_DRV(u8StopDrv));

    PWC_REG_WRITE_ENABLE();

    MODIFY_REG8(M4_PWC->PWRC1, PWC_PWRC1_STPDAS, u8StopDrv);

    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  VBAT monitor reference voltage selection.
 * @param  [in] u8RefVol                VBAT monitor reference voltage.
 *         This parameter can be one of the following values:
 *           @arg PWC_VBAT_REF_VOL_1P8V:  Vbat reference voltage is 1.8V
 *           @arg PWC_VBAT_REF_VOL_2P0V:  Vbat reference voltage is 2.0V
 * @retval None
 */
void PWC_VBAT_MonitorVolSel(uint8_t u8RefVol)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_VBAT_REF_VOL(u8RefVol));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->PWRC4_b.VBATREFSEL = u8RefVol;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or Disable VBAT monitor.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_MonitorCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->PWRC4_b.VBATME = enNewState;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Get VBAT voltage status.
 * @param  None
 * @retval uint8_t                      VBAT voltage status
 */
uint8_t PWC_VBAT_GetVolStatus(void)
{
    uint8_t u8VolSta = 0U;

    PWC_REG_WRITE_ENABLE();
    u8VolSta = READ_REG8(bM4_PWC->PWRC4_b.VBATMON);
    PWC_REG_WRITE_DISABLE();

    return u8VolSta;
}

/**
 * @brief  Enable or Disable VBAT voltage measure.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_VolMeasureCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->VBATCR_b.VBATDIVMONE = enNewState;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Reset the VBAT area.
 * @param  None
 * @retval None
 */
void PWC_VBAT_Reset(void)
{
    PWC_REG_WRITE_ENABLE();
    WRITE_REG8(M4_PWC->VBATRSTR, 0xA5U);
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or Disable VBAT power.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_PwrCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->VBATCR_b.CSDIS = enNewState;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or Disable Backup RAM power.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_BkRamPwrCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->VBATCR_b.VBTRSD = enNewState;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Get Backup RAM flag.
 * @param  [in] u8Flag                  Backup RAM flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg PWC_BACKUP_RAM_FLAG_RAMPDF:   Backup RAM power down flag
 *           @arg PWC_BACKUP_RAM_FLAG_RAMVALID: Backup RAM read/write flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_GetBkRamFlag(uint8_t u8Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_RAM_FLAG(u8Flag));

    PWC_REG_WRITE_ENABLE();
    if (Reset != (READ_REG8_BIT(M4_PWC->VBATCR, u8Flag)))
    {
        enFlagSta = Set;
    }
    PWC_REG_WRITE_DISABLE();

    return enFlagSta;
}

/**
 * @brief  Write Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @param  [in] u8RegVal                Value written to register
 * @retval None
 */
void PWC_WriteBackupReg(uint8_t u8RegNum, uint8_t u8RegVal)
{
    __IO uint8_t *BKR = NULL;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));

    PWC_REG_WRITE_ENABLE();
    BKR = (__IO uint8_t *)PWC_BKRx(u8RegNum);
    WRITE_REG8(*BKR, u8RegVal);
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Read Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @retval uint8_t                      Register value
 */
uint8_t PWC_ReadBackupReg(uint8_t u8RegNum)
{
    uint8_t u8RegVal = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));

    PWC_REG_WRITE_ENABLE();
    u8RegVal = READ_REG8(*((__IO uint8_t *)PWC_BKRx(u8RegNum)));
    PWC_REG_WRITE_DISABLE();

    return u8RegVal;
}

/**
 * @brief  WKT Timer Initialize.
 * @param  [in] u8ClkSrc                Clock source.
 *         This parameter can be one of the following values:
 *           @arg PWC_WKT_CLK_SRC_64HZ:     64Hz Clock
 *           @arg PWC_WKT_CLK_SRC_XTAL32:   XTAL32 Clock
 *           @arg PWC_WKT_CLK_SRC_RTCLRC:   RTCLRC Clock
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_Init(uint8_t u8ClkSrc, uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_CLK_SRC(u8ClkSrc));
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));

    PWC_REG_WRITE_ENABLE();
    MODIFY_REG8(M4_PWC->WKTC2, PWC_WKTC2_WKCKS, u8ClkSrc);
    WRITE_REG8(M4_PWC->WKTC0, (uint8_t)(u16CmpVal & 0x00FFU));
    WRITE_REG8(M4_PWC->WKTC1, (uint8_t)((u16CmpVal >> 8U) & 0x000FU));
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Set WKT Timer compare value.
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));

    PWC_REG_WRITE_ENABLE();
    WRITE_REG8(M4_PWC->WKTC0, (uint8_t)(u16CmpVal & 0x00FFU));
    WRITE_REG8(M4_PWC->WKTC1, (uint8_t)((u16CmpVal >> 8U) & 0x000FU));
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Get WKT Timer compare value.
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval uint16_t                     WKT Compara value
 */
uint16_t PWC_WKT_GetCompareValue(void)
{
    uint16_t u16CmpVal = 0U;

    PWC_REG_WRITE_ENABLE();
    u16CmpVal  = ((uint16_t)READ_REG16_BIT(M4_PWC->WKTC1, PWC_WKTC1_WKTMCMP) << 8U);
    u16CmpVal |= READ_REG8(M4_PWC->WKTC0);
    PWC_REG_WRITE_DISABLE();

    return u16CmpVal;
}

/**
 * @brief  Enable or Disable WKT Timer.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_WKT_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_REG_WRITE_ENABLE();
    bM4_PWC->WKTC2_b.WKTCE = enNewState;
    PWC_REG_WRITE_DISABLE();
}

/**
 * @brief  Get WKT Timer count match flag.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_WKT_GetFlag(void)
{
    en_flag_status_t enFlagSta = Reset;

    PWC_REG_WRITE_ENABLE();
    enFlagSta = (en_flag_status_t)(bM4_PWC->WKTC2_b.WKOVF);
    PWC_REG_WRITE_DISABLE();

    return enFlagSta;
}

/**
 * @brief  Clear WKT Timer count match flag.
 * @param  None
 * @retval None
 */
void PWC_WKT_ClearFlag(void)
{
    PWC_REG_WRITE_ENABLE();
    bM4_PWC->WKTC2_b.WKOVF = 0UL;
    PWC_REG_WRITE_DISABLE();
}

#endif  /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

