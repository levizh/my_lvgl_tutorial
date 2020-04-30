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
#include "RGB565_480x272.h"

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

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint8_t u8Tmp[10];
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
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
            BSP_LED_Toggle(LED_RED);
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
//    GPIO_TogglePins(GPIO_PORT_E, GPIO_PIN_02);
    lv_tick_inc(1);
}

void draw_bmp(void)
{
    //for RGB565_480x272
          /* Set cursor */
    NT35510_SetCursor(0, 320);

    /* Prepare to write to LCD RAM */
    LCD_WriteReg(NT35510_WRITE_RAM);

//    for(uint32_t bmp_cnt = 0; bmp_cnt < 480x272; bmp_cnt++)
//    {
//         = RGB565_480x272[bmp_cnt];
//    }
    LCD_WriteMultipleData((uint16_t*)&RGB565_480x272[0], 480*272);
}

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of template project
 * @param  None
 * @retval int32_t return value, if needed67
 */
uint16_t x,y,gt_reg;
uint16_t test_buf[800];
uint8_t reg_val;
int32_t main(void)
{
//    while(1);
    stc_dma_init_t stcDmaInit;
    BSP_CLK_Init();

    /* EXBUS CLK 60MHz */
//    CLK_ClkDiv(CLK_CATE_EXCLK, CLK_EXCLK_DIV4);
    /* EXBUS CLK 120MHz */
    CLK_ClkDiv(CLK_CATE_EXCLK, CLK_EXCLK_DIV2);

    GPIO_OE(GPIO_PORT_E, GPIO_PIN_02,Enable);
    BSP_IO_Init();
    BSP_LED_Init();
    BSP_CAM_Init();
    BSP_LCD_IO_Init();
    BSP_KEY_Init();
    BSP_TS_Init();

    DDL_PrintfInit();

    //BSP_TS_ReadReg(0x4081, &u8Tmp[0], 4);
    SysTick_Init(2000);

    /* HW Reset LCD */
    BSP_LCD_ResetCmd(EIO_PIN_RESET);
//    BSP_CT_ResetCmd(EIO_PIN_RESET);
    DDL_Delay1ms(1000UL);
    BSP_LCD_ResetCmd(EIO_PIN_SET);
//    BSP_CT_ResetCmd(EIO_PIN_SET);

    /* Turn on backlight */
    BSP_LCD_BKLCmd(EIO_PIN_SET);
    BSP_LCD_Clear(WHITE);

    DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32DestAddr = 0x60002000;// LCD RAM
//    stcDmaInit.u32DestAddr = (uint32_t)&test_buf[0];// LCD RAM
    stcDmaInit.u32DataWidth=DMA_DATAWIDTH_16BIT;
    stcDmaInit.u32DestInc=DMA_DEST_ADDR_FIX;
//    stcDmaInit.u32DestInc=DMA_DEST_ADDR_INC;
    stcDmaInit.u32SrcInc=DMA_SRC_ADDR_INC;
    stcDmaInit.u32IntEn=DMA_INT_DISABLE;//DMA_INT_ENABLE;
//    stcDmaInit.u32TransCnt=1;
    stcDmaInit.u32BlockSize=1;
    PWC_Fcg0PeriphClockCmd(PWC_FCG0_DMA1 | PWC_FCG0_PTDIS, Enable);
    DMA_Init(M4_DMA1, DMA_CH0, &stcDmaInit);
    DMA_SetTrigSrc(M4_DMA1, DMA_CH0, EVT_AOS_STRG);
    DMA_Cmd(M4_DMA1, Enable);
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
        //LCD_WriteData(color++);
//        BSP_LCD_Clear(WHITE);
//        BSP_LCD_Clear(BLUE);
//        BSP_LCD_Clear(GRED);
//        BSP_LCD_Clear(CYAN);
//        NT35510_DrawLine(100,10,10,300,0x55);
//        BSP_LCD_DrawCircle(200,300,90,0x786);
//        BSP_LCD_FillTriangle(30,60,100,30,200,50,0x555);
        lv_task_handler();
        key_serve();
        draw_bmp();
//        if(gt_reg<=0x8100)
        if(gt_reg!=0x00)
        {
            x = (gt_reg & 0xFF)<<8;
            y = (gt_reg & 0xFF00)>>8;
            x = x | y;
            BSP_TS_ReadReg(x, &reg_val, 1);
            printf("%XH : %2XH\n",gt_reg, reg_val);
            //gt_reg++;
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
