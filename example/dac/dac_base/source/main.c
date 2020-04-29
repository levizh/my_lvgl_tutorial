/**
 *******************************************************************************
 * @file  template/source/main.c
 * @brief Main program template for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-28       Hexiao          First version
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
#include "hc32_ddl.h"
#include "hc32f4a0_dac.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup Templates
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
typedef enum
{
    E_KEY_NOT_PRESSED,
    E_KEY1_PRESSED,
    E_KEY2_PRESSED,
    E_KEY3_PRESSED,
    E_KEY4_PRESSED,
}en_key_event;

typedef enum 
{
    DAC_Unit1,
    DAC_Unit2,
    DAC_Unit_Max,
}en_dac_unit;

typedef enum 
{
    E_Dac_Single,
    E_Dac_Dual,
}en_dac_cvt_t;

typedef void (*pfSingleWaveSetData)(M4_DAC_TypeDef* pstcDACx, uint16_t data);
typedef struct
{
    M4_DAC_TypeDef* pUnit;
    en_dac_cvt_t enCvtType;
    en_dac_ch_t enCh;
}st_dac_handle_t;
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define DAC_UNIT1_PORT                               (GPIO_PORT_A)
#define DAC_UNIT2_PORT                               (GPIO_PORT_C)
#define DAC_UNIT1_CHN1_PIN                           (GPIO_PIN_04)
#define DAC_UNIT1_CHN2_PIN                           (GPIO_PIN_05)
#define DAC_UNIT2_CHN1_PIN                           (GPIO_PIN_04)
#define DAC_UNIT2_CHN2_PIN                           (GPIO_PIN_05)
#define VREFH                                        (3.3F)
#define DAC_CHN1                                     (0U)
#define DAC_CHN2                                     (1U)
#define DAC_DATA_ALIGN_12b_R                         (0U)
#define DAC_DATA_ALIGN_12b_L                         (1U)

#define SUPPORT_AMP
//#define SUPPORT_ADP
#define SINGLE_WAVE_DAC_CHN                          (DAC_CHN1)
#define DAC_DATA_ALIGN                               (DAC_DATA_ALIGN_12b_R)

#define SINE_DOT_NUMBER                              (4096U)
#define SINE_NEGATIVE_TO_POSITVE                     (1.0F)

#if (SINGLE_WAVE_DAC_CHN == DAC_CHN1)
#define pfSingleWaveSetData                          (DAC_SetChannel1Data)
#define pfSingleWaveConvState                        (DAC_GetChannel1ConvState)
#else
#define pfSingleWaveSetData                          (DAC_SetChannel2Data)
#define pfSingleWaveConvState                        (DAC_GetChannel2ConvState)
#endif
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
static st_dac_handle_t gstDACHandle[DAC_Unit_Max] = {0};
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
 * @brief  Configure system clock
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_pllh_init_t stcPLLHInit;
    
    /* HCLK  Max 240MHz */
    CLK_ClkDiv(CLK_CATE_ALL,                                                    \
               (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 |              \
                CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 |              \
                CLK_HCLK_DIV1));

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAMH, SRAM_WAIT_CYCLE_1, SRAM_WAIT_CYCLE_1);

    EFM_Unlock();
    EFM_SetLatency(EFM_WAIT_CYCLE_6);
    EFM_Unlock();
    
    /* PLLH config */
    CLK_PLLHStrucInit(&stcPLLHInit);
    /*
    16MHz/M*N/P = 16/1*60/4 =240MHz
    */
    stcPLLHInit.u8PLLState = CLK_PLLH_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = (1UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLN = (60UL - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLP = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLR = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLQ = (4UL  - 1UL);
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLLSRC_HRC;
    CLK_PLLHInit(&stcPLLHInit);
    CLK_PLLHCmd(Enable);
    CLK_SetSysClkSrc(CLK_SYSCLKSOURCE_PLLH);

    /* Confiure clock output system clock */
    CLK_MCO1Config(CLK_MCOSOURCCE_SYSCLK, CLK_MCODIV_128);
    /* Confiure clock output pin */
    GPIO_SetFunc(GPIO_PORT_A, GPIO_PIN_08, GPIO_FUNC_1_MCO, Disable);
    /* MCO1 output enable */
    CLK_MCO1Cmd(Enable);
}

/**
 * @brief    Get key pressed event
 * @param    None
 * @retval   An en_key_event enumeration value
 */
static en_key_event Key_Event(void)
{
    en_key_event enEvent = E_KEY_NOT_PRESSED;

    if(Set == BSP_KEY_GetStatus(BSP_KEY_1))
    {
        enEvent = E_KEY1_PRESSED;
    }
    else if(Set == BSP_KEY_GetStatus(BSP_KEY_2))
    {
        enEvent = E_KEY2_PRESSED;
    }
    else if(Set == BSP_KEY_GetStatus(BSP_KEY_3))
    {
        enEvent = E_KEY3_PRESSED;
    }
    else if(Set == BSP_KEY_GetStatus(BSP_KEY_4))
    {
        enEvent = E_KEY4_PRESSED;
    }
    else
    {
        enEvent = E_KEY_NOT_PRESSED;
    }
    return enEvent;
}

/**
 * @brief   MAU Initialization
 * @param   None
 * @retval  None
 */
static void MAU_Init(void)
{
    /* Enable MAU peripheral clock. */
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_CORDIC, Enable);
}

/**
 * @brief    Sin table Initialization
 * @param    [in] pSinTable  sin table
 * @param    [in] u32count   number of pSinTable items
 * @retval   None
 */
static void SinTable_Init(uint32_t pSinTable[],uint32_t u32count)
{
    uint32_t i = 0U;
    uint32_t u32AngAvg = (uint32_t)(float32_t)((float32_t)((float32_t)MAU_SIN_ANG_TOTAL / (float32_t)u32count) + 0.5);
    float32_t fSin = 0.0F;
    for(i = 0U; i < u32count; i++)
    {
        fSin = (((float32_t)MAU_Sin(M4_MAU, (uint16_t)(u32AngAvg * i)) 
                 / (float32_t)MAU_SIN_Q15_SCALAR + SINE_NEGATIVE_TO_POSITVE) / VREFH) *
            (float32_t)DAC_PARAM_MAX + 0.5F;
        
        #if (DAC_DATA_ALIGN == DAC_DATA_ALIGN_12b_L)
        {
            pSinTable[i] = (uint32_t)fSin << 4;
        }
        #else
        {
            pSinTable[i] = (uint32_t)fSin;
        }
        #endif
    }
}

/**
 * @brief    Enable DAC peripheral clock
 * @param    [in] en_dac_unit  The selected DAC unit
 * @retval   None
 */
static void DAC_PClkEnable(en_dac_unit eUnit)
{
    uint32_t u32PClk = 0U;
    switch(eUnit)
    {
    case DAC_Unit1:
        u32PClk = PWC_FCG3_DAC1;
        break;
    case DAC_Unit2:
        u32PClk = PWC_FCG3_DAC2;
        break;
    default:
        u32PClk = PWC_FCG3_DAC1 | PWC_FCG3_DAC2;
        break;
    }
    /* Enable DAC peripheral clock. */
    PWC_Fcg3PeriphClockCmd(u32PClk, Enable);
}

/**
 * @brief    Init DAC single channel
 * @param    [in] en_dac_unit  The selected DAC unit
 * @retval   A pointer of DAC handler
 */
st_dac_handle_t* DAC_SingleChnInit(en_dac_unit enUnit)
{
    uint8_t u8Port;
    uint16_t u16Pin;
    st_dac_handle_t* pDac = NULL;
    
    if(enUnit == DAC_Unit1)
    {
        pDac = &gstDACHandle[DAC_Unit1];
        pDac->pUnit = M4_DAC1;
    }
    else
    {
        pDac = &gstDACHandle[DAC_Unit2];
        pDac->pUnit = M4_DAC2;
    }
    DAC_PClkEnable(enUnit);

    pDac->enCvtType = E_Dac_Single;
    #if (SINGLE_WAVE_DAC_CHN == DAC_CHN1)
    pDac->enCh = DAC_Channel_1;
    #else
    pDac->enCh = DAC_Channel_2;
    #endif

    /* Set data pattern and data source */
    #if (DAC_DATA_ALIGN == DAC_DATA_ALIGN_12b_L)
    DAC_DataPatternConfig(pDac->pUnit,DAC_Align_12b_L);
    #else
    DAC_DataPatternConfig(pDac->pUnit,DAC_Align_12b_R);
    #endif
    DAC_SetDataSource(pDac->pUnit, pDac->enCh, DAC_Data_From_DataReg);
    /* Set DAC pin attribute to analog */
    if(enUnit == DAC_Unit1)
    {
        u8Port = DAC_UNIT1_PORT;
        #if (SINGLE_WAVE_DAC_CHN == DAC_CHN1)
        u16Pin = DAC_UNIT1_CHN1_PIN;
        #else
        u16Pin = DAC_UNIT1_CHN2_PIN;
        #endif
    }
    else
    {
        u8Port = DAC_UNIT2_PORT;
        #if (SINGLE_WAVE_DAC_CHN == DAC_CHN1)
        u16Pin = DAC_UNIT2_CHN1_PIN;
        #else
        u16Pin = DAC_UNIT2_CHN2_PIN;
        #endif
    } 
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    GPIO_Init(u8Port, u16Pin, &stcGpioInit);

    #ifdef SUPPORT_ADP
    /* Set ADC first */
    /* Enable DAC peripheral clock. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_ADC1|PWC_FCG3_ADC2|PWC_FCG3_ADC3, Enable);
    if(M4_ADC1->STR == 0U)
    {
        if(M4_ADC2->STR == 0U)
        {
            if(M4_ADC3->STR == 0U)
            {
                DAC_ADCPrioConfig(pDac->pUnit, DAC_ADPCR_CONFIG_ALL);
                DAC_ADCPrioCmd(pDac->pUnit, Enable);
            }
        }
    }
    #endif
    return pDac;
}

/**
 * @brief    Init DAC Dual channel
 * @param    [in] en_dac_unit  The selected DAC unit
 * @retval   A pointer of DAC handler
 */
st_dac_handle_t* DAC_DualChnInit(en_dac_unit enUnit)
{
    uint8_t u8Port;
    st_dac_handle_t* pDac = NULL;

    if(enUnit == DAC_Unit1)
    {
        pDac = &gstDACHandle[DAC_Unit1];
        pDac->pUnit = M4_DAC1;
    }
    else
    {
        pDac = &gstDACHandle[DAC_Unit2];
        pDac->pUnit = M4_DAC2;
    }
    DAC_PClkEnable(enUnit);
    pDac->enCvtType = E_Dac_Dual;
    /* Set data pattern and data source */
    #if (DAC_DATA_ALIGN == DAC_DATA_ALIGN_12b_L)
    DAC_DataPatternConfig(pDac->pUnit,DAC_Align_12b_L);
    #else
    DAC_DataPatternConfig(pDac->pUnit,DAC_Align_12b_R);
    #endif
    DAC_SetDataSource(pDac->pUnit, DAC_Channel_1, DAC_Data_From_DataReg);
    DAC_SetDataSource(pDac->pUnit, DAC_Channel_2, DAC_Data_From_DataReg);
    /* Set DAC pin attribute to analog */
    stc_gpio_init_t stcGpioInit;
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    if(enUnit == DAC_Unit1)
    {
        u8Port = DAC_UNIT1_PORT;
        GPIO_Init(u8Port,DAC_UNIT1_CHN1_PIN, &stcGpioInit);
        GPIO_Init(u8Port,DAC_UNIT1_CHN2_PIN, &stcGpioInit);
    }
    else
    {
        u8Port = DAC_UNIT2_PORT;
        GPIO_Init(u8Port,DAC_UNIT2_CHN1_PIN, &stcGpioInit);
        GPIO_Init(u8Port,DAC_UNIT2_CHN2_PIN, &stcGpioInit);
    }

    #ifdef SUPPORT_ADP
    /* Set ADC first */
    /* Enable DAC peripheral clock. */
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_ADC1|PWC_FCG3_ADC2|PWC_FCG3_ADC3, Enable);
    if(M4_ADC1->STR == 0U)
    {
        if(M4_ADC2->STR == 0U)
        {
            if(M4_ADC3->STR == 0U)
            {
                DAC_ADCPrioConfig(pDac->pUnit, DAC_ADPCR_CONFIG_ALL);
                DAC_ADCPrioCmd(pDac->pUnit, Enable);
            }
        }
    }
    #endif
    return pDac;
}

/**
 * @brief    Start  Dual DAC conversions
 * @param    [in] pDac       A pointer of DAC handler
 * @retval   None
 */
static void DAC_DualChnStart(const st_dac_handle_t* pDac)
{
    /* Set sin data and start convert */
    DAC_OutputCmd(pDac->pUnit,DAC_Channel_1,Enable);
    DAC_OutputCmd(pDac->pUnit,DAC_Channel_2,Enable);
    #ifdef SUPPORT_AMP
    /* Enalbe AMP */
    DAC_SetChannelAllData(pDac->pUnit,0U,0U);
    DAC_AMPCmd(pDac->pUnit,DAC_Channel_1,Enable);
    DAC_AMPCmd(pDac->pUnit,DAC_Channel_2,Enable);
    #endif
    /* Enalbe Dual Channel */
    DAC_ChannelAllCmd(pDac->pUnit,Enable);
    #ifdef SUPPORT_AMP
	/* delay 3us before setting data*/
	DDL_Delay1ms(1U);
    #endif
}

/**
 * @brief    Start single DAC conversions
 * @param    [in] pDac       A pointer of DAC handler
 * @retval   None
 */
static void DAC_SingleChnStart(const st_dac_handle_t* pDac)
{
    DAC_OutputCmd(pDac->pUnit,pDac->enCh,Enable);
    /* Enalbe AMP */
    #ifdef SUPPORT_AMP
    DAC_SetChannelAllData(pDac->pUnit,0U,0U);
    DAC_AMPCmd(pDac->pUnit,pDac->enCh,Enable);
    #endif
    DAC_ChannelCmd(pDac->pUnit,pDac->enCh,Enable);
	#ifdef SUPPORT_AMP
	/* delay 3us before setting data*/
	DDL_Delay1ms(1U);
	#endif
}

/**
 * @brief    Convert data by single DAC channel
 * @param    [in] pDac       A pointer of DAC handler
 * @param    [in] pDataTable The data table to be converted
 * @param    [in] u32count   Number of data table items
 * @retval   None
 */
__STATIC_INLINE void DAC_SingleChnConvert(const st_dac_handle_t* pDac, uint32_t const pDataTable[],uint32_t u32count)
{
    for(uint32_t i = 0U; i < u32count; i++)
    {
        #ifdef SUPPORT_ADP
        uint32_t u32TryCount = 100U;
        while(u32TryCount != 0U)
        {
            u32TryCount--;
            if(DAC_Convert_Ongoing != pfSingleWaveConvState(pDac->pUnit))
            {
                break;
            }
        }
        #endif
        pfSingleWaveSetData(pDac->pUnit,(uint16_t)pDataTable[i]);
    }
}

/**
 * @brief    Convert data by dual DAC channel
 * @param    [in] pDac       A pointer of DAC handler
 * @param    [in] pDataTable The data table to be converted
 * @param    [in] u32count   Number of data table items
 * @retval   None
 */
__STATIC_INLINE void DAC_DualChnConvert(const st_dac_handle_t* pDac, uint32_t const pDataTable[],uint32_t u32count)
{
    for(uint32_t i = 0U; i < u32count; i++)
    {
        #ifdef SUPPORT_ADP
        en_dac_conv_sate_t enSt;
        uint32_t u32TryCount = 100U;
        while(u32TryCount != 0U)
        {
            enSt = DAC_GetChannel1ConvState(pDac->pUnit);
            u32TryCount--;
            if(DAC_Convert_Ongoing != enSt)
            {
                enSt = DAC_GetChannel2ConvState(pDac->pUnit);
                if(DAC_Convert_Ongoing != enSt)
                {
                    break;
                }
            }
        }
        #endif
        DAC_SetChannelAllData(pDac->pUnit,(uint16_t)pDataTable[i],(uint16_t)pDataTable[i]);
    }
}

/**
 * @brief    stop DAC conversion
 * @param    [in] A pointer of DAC handler 
 * @retval   None
 */
static void DAC_Stop(const st_dac_handle_t* pDac)
{
    if(pDac->enCvtType != E_Dac_Dual)
    {
        DAC_ChannelCmd(pDac->pUnit,pDac->enCh,Disable);
    }
    DAC_ChannelAllCmd(pDac->pUnit,Disable);
}

/**
 * @brief  Main function of template project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    BSP_IO_Init();
    BSP_LED_Init();
    BSP_KEY_Init();

    /* Configure system clock */
    SystemClockConfig();
    /* Init MAU for generating sine data*/
    MAU_Init();
    /* Init sine data table */
    static uint32_t gu32SinTable[SINE_DOT_NUMBER];
    SinTable_Init(gu32SinTable, SINE_DOT_NUMBER);

    /* Init DAC */
    st_dac_handle_t* pSingleDac = DAC_SingleChnInit(DAC_Unit1);
    st_dac_handle_t* pDualDac = DAC_DualChnInit(DAC_Unit2);
    /**
    * Output sine waves after system restart, 
    * Press Key2 to stop the single sine wave ,and Press Key1 to restart
    * Press Key4 to stop the dual sine waves ,and Press Key3 to restart
    */
    en_key_event enEvent = E_KEY_NOT_PRESSED;
    uint8_t u8EnableSingle = 1U,u8EnableDual = 1U;
    DAC_SingleChnStart(pSingleDac);
    BSP_LED_On(LED_BLUE);
    DAC_DualChnStart(pDualDac);
    BSP_LED_On(LED_RED);
    while (1)
    {
        enEvent = Key_Event();
        switch(enEvent)
        {         
            case E_KEY1_PRESSED:
                u8EnableSingle = 1U;
                BSP_LED_On(LED_BLUE);
                DAC_SingleChnStart(pSingleDac);
                break;
            case E_KEY2_PRESSED:
                u8EnableSingle = 0U;
                DAC_Stop(pSingleDac);
                BSP_LED_Off(LED_BLUE);
                break;
            case E_KEY3_PRESSED:
                u8EnableDual = 1U;
                BSP_LED_On(LED_RED);
                DAC_DualChnStart(pDualDac);
                break;
            case E_KEY4_PRESSED:
                u8EnableDual = 0U;
                DAC_Stop(pDualDac);
                BSP_LED_Off(LED_RED);
                break;
            default:
                break;
        }
        if(u8EnableSingle)
        {
            DAC_SingleChnConvert(pSingleDac,gu32SinTable, SINE_DOT_NUMBER);
        }
        if(u8EnableDual)
        {
            DAC_DualChnConvert(pDualDac,gu32SinTable, SINE_DOT_NUMBER);
        }
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
