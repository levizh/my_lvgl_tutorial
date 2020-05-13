/**
 *******************************************************************************
 * @file  lcd/source/main.c
 * @brief Main program template for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-02       zhangxl          First version
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
#include "lvgl.h"
//#include "RGB565_480x272.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup LCD
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define TEST_PORT   GPIO_PORT_E
#define TEST_PIN    GPIO_PIN_02

#define TEST_PORT2  GPIO_PORT_E
#define TEST_PIN2   GPIO_PIN_03

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#define DVP_BUF_SIZE    960U
uint8_t u8Tmp[10];
uint16_t x,y,gt_reg;
uint16_t test_buf[10];
uint8_t reg_val;
uint16_t DVP_Buf1[DVP_BUF_SIZE], DVP_Buf2[DVP_BUF_SIZE];
uint16_t draw_cnt = 0;
uint32_t dvp_frame_cnt=0;
uint32_t dvp_line_cnt=0;

/*
    0: cam idle
    1: cam busy
*/
uint8_t cam_state = 0;;

/*
    0: gui idle
    1: gui busy
*/
uint8_t gui_state = 0;;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void DVP_CaptureOn(void);



void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4];                                 /* max 3 bytes  for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(slider));
        lv_label_set_text(0, buf);               /*Refresh the text*/
    }
}

void key_serve(void)
{
        if (Set == BSP_KEY_GetStatus(BSP_KEY_1))
        {
//            lv_port_disp_init();
            lv_tutorial_hello_world();
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_2))
        {
//            lv_port_disp_init();
            lv_tutorial_objects();
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_3))
        {
//            lv_port_disp_init();
            lv_tutorial_styles();
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_4))
        {
            lv_test_group_1();
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_5))
        {
            lv_tutorial_keyboard();
        }

        if (Set == BSP_KEY_GetStatus(BSP_KEY_6))
        {

        }
        if (Set == BSP_KEY_GetStatus(BSP_KEY_7))
        {
//            BSP_LED_Toggle(LED_RED);
            DVP_CaptureOn();
        }
        if (Set == BSP_KEY_GetStatus(BSP_KEY_8))
        {
            BSP_LED_Toggle(LED_BLUE);
        }
        if (Set == BSP_KEY_GetStatus(BSP_KEY_9))
        {
            BSP_LED_Toggle(LED_RED | LED_BLUE);
        }
}


/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
void SysTick_IrqHandler(void)
{
//    GPIO_TogglePins(TEST_PORT, TEST_PIN);
    lv_tick_inc(1);
    draw_cnt++;
}

void draw_bmp(void)
{
    stc_dma_init_t stcDmaInit;
    static uint8_t i = 0;

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_DMA1 | PWC_FCG0_PTDIS, Enable);

    DMA_StructInit(&stcDmaInit);
    if(i%2)
    {
////        stcDmaInit.u32SrcAddr   = (uint32_t)&RGB565_480x272[0];
    }
    else
    {
////        stcDmaInit.u32SrcAddr   = (uint32_t)&_acnew_york_480x272[0];
    }
    i++;
    stcDmaInit.u32DestAddr  = 0x60002000;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_16BIT;
    stcDmaInit.u32DestInc   = DMA_DEST_ADDR_FIX;
    stcDmaInit.u32SrcInc    = DMA_SRC_ADDR_INC;
    stcDmaInit.u32IntEn     = DMA_INT_DISABLE;//DMA_INT_ENABLE;
    stcDmaInit.u32TransCnt  = 480*272/4;
    stcDmaInit.u32BlockSize = 4;
    DMA_Init(M4_DMA1, DMA_CH2, &stcDmaInit);
    DMA_SetTrigSrc(M4_DMA1, DMA_CH2, EVT_AOS_STRG);
    DMA_Cmd(M4_DMA1, Enable);

#if 0
    //for RGB565_480x272
    /* Set cursor */
    NT35510_SetCursor(0, 320);

    /* Prepare to write to LCD RAM */
    LCD_WriteReg(NT35510_WRITE_RAM);

//    for(uint32_t bmp_cnt = 0; bmp_cnt < 480x272; bmp_cnt++)
//    {
//         = RGB565_480x272[bmp_cnt];
//    }
//    LCD_WriteMultipleData((uint16_t*)&RGB565_480x272[0], 480*272);
    DMA_ChannelCmd(M4_DMA1, DMA_CH2, Enable);
    AOS_SW_Trigger();
    while(Reset == DMA_GetTransIntStatus(M4_DMA1, DMA_TC_INT2))
    {
        AOS_SW_Trigger();
    }
    DMA_ClearTransIntStatus(M4_DMA1, DMA_TC_INT2);
#endif
}

void Draw_bmp(void)
{
    static uint8_t i = 0;
//    uint32_t k=0;
//    for (uint32_t j = 0; j < 240*100; j++)
//    {
//        u32buf[j] = RGB565_480x272[k] | (((uint32_t)RGB565_480x272[k+1]) << 16);
//        k+=2;
//    }
    if(i%2)
    {
////        DMA_SetSrcAddr(M4_DMA1, DMA_CH2, (uint32_t)&RGB565_480x272[0]);
//        DMA_SetSrcAddr(M4_DMA1, DMA_CH2, (uint32_t)&u32buf[0]);
    }
    else
    {
////        DMA_SetSrcAddr(M4_DMA1, DMA_CH2, (uint32_t)&_acnew_york_480x272[0]);
    }
    i++;
    DMA_SetTransCnt(M4_DMA1, DMA_CH2, 480*272/4);
    NT35510_SetCursor(0, 320);

    /* Prepare to write to LCD RAM */
    LCD_WriteReg(NT35510_WRITE_RAM);
    DMA_ChannelCmd(M4_DMA1, DMA_CH2, Enable);
    AOS_SW_Trigger();
    while(Reset == DMA_GetTransIntStatus(M4_DMA1, DMA_TC_INT2))
    {
        AOS_SW_Trigger();
    }
    DMA_ClearTransIntStatus(M4_DMA1, DMA_TC_INT2);
}

void DVP_Init(void)
{
    M4_DVP->CTR = 0x00004000UL;
    M4_DVP->DTR = 0UL;
    M4_DVP->STR = 0UL;
//    M4_DVP->IER = 0x00000028UL;
    M4_DVP->SSYNDR = 0UL;
    M4_DVP->SSYNMR = 0UL;
    M4_DVP->CPSFTR = 0UL;
    M4_DVP->CPSZER = 0UL;
    M4_DVP->CTR = 0x00004020UL | (2 << 8 );
}

void DVP_TMRA_Init(void)
{
    stc_tmra_init_t stcTmrAInit;

    TMRA_StructInit(&stcTmrAInit);

    stcTmrAInit.u32ClkSrc   = TMRA_CLK_HW_UP_EVENT;
    stcTmrAInit.u32PCLKDiv  = TMRA_PCLK_DIV_1;
    stcTmrAInit.u32CntDir   = TMRA_DIR_UP;
    stcTmrAInit.u32CntMode  = TMRA_MODE_SAWTOOTH;
    stcTmrAInit.u32PeriodVal= 8UL - 1UL;

    TMRA_Init(M4_TMRA_1, &stcTmrAInit);

    TMRA_SetCntEvent(M4_TMRA_1, EVT_DVP_DMAREQ);

    TMRA_Start(M4_TMRA_1);

}

void DVP_CaptureOn(void)
{
    bM4_DVP->CTR_b.DVPEN = 1UL;
    DDL_Delay1ms(1UL);
    /* Clear all int flag */
    M4_DVP->STR = 0UL;
    M4_DVP->IER = 0x00000028UL | (1<<0);
    bM4_DVP->CTR_b.CAPEN = 1UL;
}

void DVP_CaptureOff(void)
{
    bM4_DVP->CTR_b.CAPEN = 0UL;
    while(1UL == bM4_DVP->CTR_b.CAPEN);
    bM4_DVP->CTR_b.DVPEN = 0UL;
    DDL_Delay1ms(1UL);
}

void DVP_FrameStart_IrqCallback(void)
{
    dvp_frame_cnt++;
    if (dvp_frame_cnt>=4)
    {
//        __asm("nop");
        NT35510_SetCursor(0U, 320U);
        /* Prepare to write to LCD RAM */
        LCD_WriteReg(NT35510_WRITE_RAM);
//        dvp_frame_cnt=0;
        cam_state=1;
    }
}

void DVP_FrameEnd_IrqCallback(void)
{
//    bM4_DVP->STR_b.FEF = 0;
////    DMA_ChannelCmd(M4_DMA1, DMA_CH0, Enable);
//    dvp_frame_cnt++;
    if (dvp_frame_cnt>=4)
    {
////        __asm("nop");
//        NT35510_SetCursor(0U, 320U);
//        /* Prepare to write to LCD RAM */
//        LCD_WriteReg(NT35510_WRITE_RAM);
        dvp_frame_cnt=0;
        cam_state=0;
    }
//    GPIO_TogglePins(TEST_PORT, TEST_PIN);
}

void DVP_DMA1_CH0_IrqCallback(void)
{
    dvp_line_cnt++;
//    cam_state = 1;
    /* Set DMA1_1 for next line */
    DMA_SetTransCnt(M4_DMA1, DMA_CH1, (DVP_BUF_SIZE/8)/2);
    /* repeat mode, needn't set dest again */

//    DMA_SetDestAddr(M4_DMA1, DMA_CH1, (uint32_t)&DVP_Buf2[0]);
    DMA_ChannelCmd(M4_DMA1, DMA_CH1, Enable);

    /* Set DMA2_1 for LCD */
    DMA_SetBlockSize(M4_DMA2, DMA_CH1, DVP_BUF_SIZE);
//    while(gui_state);
    DMA_ChannelCmd(M4_DMA2, DMA_CH1, Enable);
    GPIO_TogglePins(TEST_PORT, TEST_PIN);
}

void DVP_DMA1_CH0_BTC_IrqCallback(void)
{
    cam_state = 1;
//    if(0==dvp_line_cnt)
//    {
//        NT35510_SetCursor(0U, 320U);
//        /* Prepare to write to LCD RAM */
//        LCD_WriteReg(NT35510_WRITE_RAM);
//    }
}

void DVP_DMA1_CH1_IrqCallback(void)
{
//    dvp_line_cnt++;
//    if(dvp_line_cnt>=240)
//    {
//      cam_state=0;
//      __asm("nop");
//    }
    DMA_SetTransCnt(M4_DMA1, DMA_CH0, (DVP_BUF_SIZE/8)/2);
    /* repeat mode, needn't set dest again */

//    DMA_SetDestAddr(M4_DMA1, DMA_CH0, (uint32_t)&DVP_Buf1[0]);
    DMA_ChannelCmd(M4_DMA1, DMA_CH0, Enable);

    /* Set DMA2_0 for LCD */
    DMA_SetBlockSize(M4_DMA2, DMA_CH0, DVP_BUF_SIZE);
//    while(gui_state);
    DMA_ChannelCmd(M4_DMA2, DMA_CH0, Enable);
    GPIO_TogglePins(TEST_PORT, TEST_PIN);
}

void DVP_DMA2_CH1_BTC_IrqCallback(void)
{
//    dvp_line_cnt++;
//    if(dvp_line_cnt>=240)
//    {
//      cam_state=0;
//      dvp_line_cnt=0;
////      GPIO_TogglePins(TEST_PORT2, TEST_PIN2);
//    }
}

void DVP_FIFO_ERR_IrqCallback(void)
{
    while(1);
}

void DVP_LINE_START_IrqCallback(void)
{
//    GPIO_TogglePins(TEST_PORT, TEST_PIN);
}

void DVP_DMA_Init(void)
{
    stc_dma_init_t stcDmaInit;
    stc_dma_rpt_init_t stcDmaRptInit;

    /* DMA1_0 for line */
    DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32SrcAddr   = (uint32_t)&M4_DVP->DMR;
    stcDmaInit.u32DestAddr  = (uint32_t)&DVP_Buf1[0];
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_32BIT;
    stcDmaInit.u32DestInc   = DMA_DEST_ADDR_INC;
    stcDmaInit.u32SrcInc    = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32IntEn     = DMA_INT_ENABLE;
    stcDmaInit.u32TransCnt  = (DVP_BUF_SIZE/8)/2;
    stcDmaInit.u32BlockSize = 8UL;
    DMA_Init(M4_DMA1, DMA_CH0, &stcDmaInit);

    /* dest repeat */
    DMA_RepeatStructInit(&stcDmaRptInit);
    stcDmaRptInit.u32SrcRptEn       = DMA_SRC_RPT_DISABLE;
    stcDmaRptInit.u32SrcRptSize     = DVP_BUF_SIZE;
    stcDmaRptInit.u32DestRptEn      = DMA_DEST_RPT_ENABLE;
    stcDmaRptInit.u32DestRptSize    = DVP_BUF_SIZE/2;
    DMA_RepeatInit(M4_DMA1, DMA_CH0, &stcDmaRptInit);
    DMA_SetTrigSrc(M4_DMA1, DMA_CH0, EVT_TMRA_1_OVF);

    /* DMA1_1 for line */
    stcDmaInit.u32DestAddr  = (uint32_t)&DVP_Buf2[0];
    DMA_Init(M4_DMA1, DMA_CH1, &stcDmaInit);
    DMA_RepeatInit(M4_DMA1, DMA_CH1, &stcDmaRptInit);
    DMA_SetTrigSrc(M4_DMA1, DMA_CH1, EVT_TMRA_1_OVF);

    /* DMA2_0 for LCD DVP_Buf1 */
    stcDmaInit.u32SrcAddr   = (uint32_t)&DVP_Buf1[0];
    stcDmaInit.u32DestAddr  = 0x60002000UL;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_16BIT;
    stcDmaInit.u32DestInc   = DMA_DEST_ADDR_FIX;
    stcDmaInit.u32SrcInc    = DMA_SRC_ADDR_INC;
    stcDmaInit.u32IntEn     = DMA_INT_ENABLE;
    stcDmaInit.u32TransCnt  = 1UL;
    stcDmaInit.u32BlockSize = DVP_BUF_SIZE;
    DMA_Init(M4_DMA2, DMA_CH0, &stcDmaInit);
    stcDmaRptInit.u32SrcRptEn       = DMA_SRC_RPT_ENABLE;
    stcDmaRptInit.u32DestRptEn      = DMA_DEST_RPT_DISABLE;
    DMA_RepeatInit(M4_DMA2, DMA_CH0, &stcDmaRptInit);
    DMA_SetTrigSrc(M4_DMA2, DMA_CH0, EVT_DMA1_TC0);

    /* DMA2_1 for LCD DVP_Buf2 */
    stcDmaInit.u32SrcAddr   = (uint32_t)&DVP_Buf2[0];
//    stcDmaInit.u32DestAddr  = 0UL;// test
    DMA_Init(M4_DMA2, DMA_CH1, &stcDmaInit);
    DMA_RepeatInit(M4_DMA2, DMA_CH1, &stcDmaRptInit);
    DMA_SetTrigSrc(M4_DMA2, DMA_CH1, EVT_DMA1_TC1);

    DMA_Cmd(M4_DMA1, Enable);
    DMA_Cmd(M4_DMA2, Enable);
}

void DVP_Int_Init(void)
{
    stc_irq_signin_config_t stcIrqSignConfig;

    /* DVP frame end */
    stcIrqSignConfig.enIntSrc   = INT_DVP_FRAMEND;
    stcIrqSignConfig.enIRQn     = Int000_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_FrameEnd_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(Int000_IRQn);
    NVIC_SetPriority(Int000_IRQn,DDL_IRQ_PRIORITY_02);
    NVIC_EnableIRQ(Int000_IRQn);

    /* DVP frame start */
    stcIrqSignConfig.enIntSrc   = INT_DVP_FRAMSTA;
    stcIrqSignConfig.enIRQn     = Int007_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_FrameStart_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(Int007_IRQn);
    NVIC_SetPriority(Int007_IRQn,DDL_IRQ_PRIORITY_02);
    NVIC_EnableIRQ(Int007_IRQn);



    /* DMA1 Ch.0 BTC */
    stcIrqSignConfig.enIntSrc   = INT_DMA1_BTC0;
    stcIrqSignConfig.enIRQn     = Int005_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_DMA1_CH0_BTC_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
//    NVIC_ClearPendingIRQ(Int005_IRQn);
//    NVIC_SetPriority(Int005_IRQn,DDL_IRQ_PRIORITY_01);
//    NVIC_EnableIRQ(Int005_IRQn);

    /* DMA1 Ch.0 BTC */
    stcIrqSignConfig.enIntSrc   = INT_DMA2_BTC1;
    stcIrqSignConfig.enIRQn     = Int006_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_DMA2_CH1_BTC_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(Int006_IRQn);
    NVIC_SetPriority(Int006_IRQn,DDL_IRQ_PRIORITY_01);
    NVIC_EnableIRQ(Int006_IRQn);

    /* DMA1 Ch.0 TC */
    stcIrqSignConfig.enIntSrc   = INT_DMA1_TC0;
    stcIrqSignConfig.enIRQn     = Int001_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_DMA1_CH0_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(Int001_IRQn);
    NVIC_SetPriority(Int001_IRQn,DDL_IRQ_PRIORITY_01);
    NVIC_EnableIRQ(Int001_IRQn);

    /* DMA1 Ch.1 TC */
    stcIrqSignConfig.enIntSrc   = INT_DMA1_TC1;
    stcIrqSignConfig.enIRQn     = Int002_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_DMA1_CH1_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);
    /* NVIC config */
    NVIC_ClearPendingIRQ(Int002_IRQn);
    NVIC_SetPriority(Int002_IRQn,DDL_IRQ_PRIORITY_01);
    NVIC_EnableIRQ(Int002_IRQn);

    /* DVP FIFO ERR */
    stcIrqSignConfig.enIntSrc   = INT_DVP_FIFOERR;
    stcIrqSignConfig.enIRQn     = Int003_IRQn;
    stcIrqSignConfig.pfnCallback= &DVP_FIFO_ERR_IrqCallback;
    INTC_IrqSignIn(&stcIrqSignConfig);
    /* NVIC config */
//    NVIC_ClearPendingIRQ(Int003_IRQn);
//    NVIC_SetPriority(Int003_IRQn,DDL_IRQ_PRIORITY_00);
//    NVIC_EnableIRQ(Int003_IRQn);

//    /* DVP line start */
//    stcIrqSignConfig.enIntSrc   = INT_DVP_LINESTA;
//    stcIrqSignConfig.enIRQn     = Int004_IRQn;
//    stcIrqSignConfig.pfnCallback= &DVP_LINE_START_IrqCallback;
//    INTC_IrqSignIn(&stcIrqSignConfig);
//    /* NVIC config */
//    NVIC_ClearPendingIRQ(Int004_IRQn);
//    NVIC_SetPriority(Int004_IRQn,DDL_IRQ_PRIORITY_00);
//    NVIC_EnableIRQ(Int004_IRQn);
}

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of template project
 * @param  None
 * @retval int32_t return value, if needed67
 */
int32_t main(void)
{
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_DMA1 | PWC_FCG0_DMA2 | PWC_FCG0_PTDIS, Enable);
    PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMRA_1, Enable);

    BSP_CLK_Init();

    /* EXBUS CLK 60MHz */
//    CLK_ClkDiv(CLK_CATE_EXCLK, CLK_EXCLK_DIV4);
    /* EXBUS CLK 120MHz */
    CLK_ClkDiv(CLK_CATE_EXCLK, CLK_EXCLK_DIV2);

    GPIO_OE(TEST_PORT, (TEST_PIN | TEST_PIN2),Enable);
    BSP_IO_Init();
//    BSP_LCD_IO_Init();
//    BSP_LCD_IO_Init();
//    BSP_LCD_IO_Init();
//    BSP_LCD_IO_Init();
//    BSP_LED_Init();
//    BSP_LED_Init();
    BSP_LED_Init();
    BSP_CAM_IO_Init();
    BSP_LCD_IO_Init();
    BSP_KEY_Init();
    BSP_TS_Init();

    DDL_PrintfInit();

    //BSP_TS_ReadReg(0x4081, &u8Tmp[0], 4);
    SysTick_Init(1000);

    /* HW Reset LCD */
    BSP_LCD_ResetCmd(EIO_PIN_RESET);
    BSP_CAM_ResetCmd(EIO_PIN_RESET);
//    BSP_CT_ResetCmd(EIO_PIN_RESET);
    DDL_Delay1ms(100UL);
    BSP_LCD_ResetCmd(EIO_PIN_SET);
    BSP_CAM_ResetCmd(EIO_PIN_SET);
    BSP_CAM_StandbyCmd(EIO_PIN_RESET);

    DDL_Delay1ms(100UL);

    DVP_TMRA_Init();

    BSP_CAM_Init();
    OV5640_RGB565_Mode();
    BSP_CAM_SetOutSize(0, 40, 480, 480);
//    BSP_OV5640_Test_Pattern(1);

    DVP_DMA_Init();

    DVP_Int_Init();

//    cam_state = 1;

    DMA_ChannelCmd(M4_DMA1, DMA_CH0, Enable);
    DMA_ChannelCmd(M4_DMA2, DMA_CH0, Enable);

//    BSP_CT_ResetCmd(EIO_PIN_SET);

    //lcddev.id = 0X5310;
    //LCD_Init();
    //BSP_LCD_Init();
    //NT35510_SetCursor(0U,0U);
    //LCD_WriteRAM_Prepare();
    //LCD_WriteReg(NT35510_WRITE_RAM);

    lv_init();

    lv_port_disp_init();

    lv_port_indev_init();

//    LCD_WriteReg(NT35510_WRITE_RAM);
//
//    lv_obj_t * label;
//
//
//
///* Create a slider in the center of the display */
//lv_obj_t * slider = lv_slider_create(lv_scr_act(), NULL);
//lv_obj_set_width(slider, 200);                        /*Set the width*/
//lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);    /*Align to the center of the parent (screen)*/
//lv_obj_set_event_cb(slider, slider_event_cb);         /*Assign an event function*/
//
///* Create a label below the slider */
//label = lv_label_create(lv_scr_act(), NULL);
//lv_label_set_text(label, "0");
//lv_obj_set_auto_realign(slider, true);
//lv_obj_align(label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
//


    /* tutorial */
//    lv_tutorial_hello_world();
//    lv_tutorial_objects();
//    lv_tutorial_styles();
//    lv_tutorial_themes();
//    lv_tutorial_image();
//    lv_tutorial_antialiasing();
//    lv_tutorial_fonts();
//    lv_tutorial_animations();
//    lv_tutorial_responsive();
//    lv_tutorial_keyboard();

    /* apps */
//    benchmark_create();
    demo_create();
//    sysmon_create();
//    terminal_create();
//    tpcal_create();

    /* tests */
//    lv_test_group_1();
//
//    lv_test_task_1();
//    lv_test_task_2();

//    lv_test_object_1();
//
//    lv_test_theme_1();
//
//    lv_test_theme_2();
//    gt_reg = 0x8047;
    gt_reg = 0x0;
    NT35510_SetCursor(0, 320);
    /* Prepare to write to LCD RAM */
    LCD_WriteReg(NT35510_WRITE_RAM);
//    draw_bmp();
    DVP_Init();
    DVP_CaptureOn();
    while (1)
    {
//        BSP_LED_On(LED_RED | LED_BLUE);
//        DDL_Delay1ms(100UL);
//        BSP_LED_Off(LED_RED | LED_BLUE);
//        DDL_Delay1ms(100UL);
//        *(uint16_t *)(0x60001000UL) = 0xFF;
//        *(uint16_t *)(0x60001000UL) = 0x00;
//        *(uint16_t *)(0x60002000UL) = 0xFF;
//        *(uint16_t *)(0x60001FFEUL) = 0xFF;
////        *(uint16_t *)(0x60004000UL) = 0xFF;
////        *(uint16_t *)(0x60004000UL) = 0x00;     //NG
////        *(uint16_t *)(0x60008000UL) = 0xFF;
////        *(uint16_t *)(0x60008000UL) = 0x00;
//        BSP_CAM_RSTCmd(EIO_PIN_SET);
//        BSP_CAM_RSTCmd(EIO_PIN_RESET);
//        BSP_CAM_STBYCmd(EIO_PIN_SET);
//        BSP_CAM_STBYCmd(EIO_PIN_RESET);
//        LCD_WriteData(color++);
//        BSP_LCD_Clear(WHITE);
//        BSP_LCD_Clear(BLUE);
//        BSP_LCD_Clear(GRED);
//        BSP_LCD_Clear(CYAN);
//        NT35510_DrawLine(100,10,10,300,0x55);
//        BSP_LCD_DrawCircle(200,300,90,0x786);
//        BSP_LCD_FillTriangle(30,60,100,30,200,50,0x555);

        if ((cam_state==0))// && (dvp_frame_cnt<3))
        {
            DMA_ChannelCmd(M4_DMA1, DMA_CH0, Disable);
            DMA_ChannelCmd(M4_DMA2, DMA_CH0, Disable);
//            gui_state = 1;
            lv_task_handler();
            key_serve();
//            gui_state = 0;
//            GPIO_TogglePins(TEST_PORT2, TEST_PIN2);
            DMA_ChannelCmd(M4_DMA1, DMA_CH0, Enable);
            DMA_ChannelCmd(M4_DMA2, DMA_CH0, Enable);
        }

//        DVP_data = M4_DVP->DTR;
        if (draw_cnt>=1000)
        {
//            draw_bmp();
//            Draw_bmp();
            draw_cnt = 0;
        }
//        if(gt_reg<=0x8100)
        if(gt_reg!=0x00)
        {
            BSP_TS_ReadReg(gt_reg, &reg_val, 1);
            printf("%XH : %2XH\n",gt_reg, reg_val);
//            gt_reg++;
//            gt_reg=0;
        }

//        BSP_TS_ReadReg(GT9147_REG_GSTID, &u8Tmp[0], 1);
//        if(u8Tmp[0] & 0x80)
//        {
//            u8Tmp[1] = 0;
//            BSP_TS_WriteReg(GT9147_REG_GSTID, &u8Tmp[1], 1);
//
//            BSP_TS_ReadReg(GT9147_REG_TP1, &u8Tmp[2], 4);
//            y = u8Tmp[2] | ((uint16_t)u8Tmp[3] << 8);
//            x = 800 - (u8Tmp[4] | ((uint16_t)u8Tmp[5] << 8));
//            NT35510_WritePixel(x,y,RED);
//            NT35510_WritePixel(x,y+1,RED);
//            NT35510_WritePixel(x+1,y,RED);
//            NT35510_WritePixel(x+1,y+1,RED);
//            NT35510_WritePixel(x+2,y,RED);
//            NT35510_WritePixel(x+2,y+2,RED);
//
//        }



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
