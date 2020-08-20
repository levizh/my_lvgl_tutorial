/**
 * @file lv_port_disp_templ.c
 *
 */

 /*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_template.h"
#include "hc32_ddl_lcd.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
#if LV_USE_GPU
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
        const lv_area_t * fill_area, lv_color_t color);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/



void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /* LittlevGL requires a buffer where it draws the objects. The buffer's has to be greater than 1 display row
     *
     * There are three buffering configurations:
     * 1. Create ONE buffer with some rows:
     *      LittlevGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer with some rows:
     *      LittlevGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LittlevGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Create TWO screen-sized buffer:
     *      Similar to 2) but the buffer have to be screen sized. When LittlevGL is ready it will give the
     *      whole frame to display. This way you only need to change the frame buffer's address instead of
     *      copying the pixels.
     * */

    /* Example for 1) */
    static lv_disp_buf_t disp_buf_1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 10];                      /*A buffer for 10 rows*/
    lv_disp_buf_init(&disp_buf_1, buf1_1, NULL, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/

    /* Example for 2) */
//    static lv_disp_buf_t disp_buf_2;
//    static lv_color_t buf2_1[LV_HOR_RES_MAX * 10];                        /*A buffer for 10 rows*/
//    static lv_color_t buf2_2[LV_HOR_RES_MAX * 10];                        /*An other buffer for 10 rows*/
//    lv_disp_buf_init(&disp_buf_2, buf2_1, buf2_2, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/
//
//    /* Example for 3) */
//    static lv_disp_buf_t disp_buf_3;
//    static lv_color_t buf3_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*A screen sized buffer*/
//    static lv_color_t buf3_2[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*An other screen sized buffer*/
//    lv_disp_buf_init(&disp_buf_3, buf3_1, buf3_2, LV_HOR_RES_MAX * LV_VER_RES_MAX);   /*Initialize the display buffer*/


    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.buffer = &disp_buf_1;

#if LV_USE_GPU
    /*Optionally add functions to access the GPU. (Only in buffered mode, LV_VDB_SIZE != 0)*/

    /*Blend two color array using opacity*/
    disp_drv.gpu_blend_cb = gpu_blend;

    /*Fill a memory array with a color*/
    disp_drv.gpu_fill_cb = gpu_fill;
#endif

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your display and the required peripherals. */
static void disp_init(void)
{
    /*You code here*/
    BSP_LCD_Init();

    BSP_LCD_Clear(WHITE);

    /* Turn on backlight */
    BSP_LCD_BKLCmd(EIO_PIN_SET);
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
uint32_t cc=5000;
extern uint8_t cam_state;
//extern uint16_t test_buf[800];
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    static uint32_t cnt = 0;
//    cnt = 100;
#if 1
    uint32_t size;
    uint32_t line_size;
    uint32_t row_num = ((area->y2)-(area->y1)+1);
    line_size = (area->x2)-(area->x1)+1;
    size = ((area->y2)-(area->y1)+1)*((area->x2)-(area->x1)+1);
    for (uint32_t row = 0; row < row_num; row++)
    {
        cnt = cc;
        while(cam_state);
        /* Set cursor */
        NT35510_SetCursor(area->x1, area->y1+row);
//        NT35510_SetCursor(area->x1, area->y1+row);
//        NT35510_SetCursor(area->x1, area->y1+row);
//        __asm("nop");
//        __asm("nop");
//        __asm("nop");
        do {
          __asm("nop");
        } while(cnt--);
//        DDL_DelayMS(1);

        /* Prepare to write to LCD RAM */
        LCD_WriteReg(lcddev.wramcmd);
#if 1//use CPU
        for (uint32_t i = 0; i < line_size; i++)
        {
            //LCD_WriteData(color_p->full);
            *(uint16_t *)(0x60002000UL) = color_p->full;
            color_p++;
//            cnt++;
        }
#else//use DMA
        DMA_SetSrcAddr(M4_DMA1, DMA_CH0, (uint32_t)color_p);
//        DMA_SetDestAddr(M4_DMA1, DMA_CH0, (uint32_t)0x1FFEA864);
//        DMA_SetBlockSize(M4_DMA1, DMA_CH0, line_size/2);
        DMA_SetTransCnt(M4_DMA1, DMA_CH0, line_size);
        DMA_ChannelCmd(M4_DMA1, DMA_CH0, Enable);
        AOS_SW_Trigger();
        while(Reset == DMA_GetTransIntStatus(M4_DMA1, DMA_TC_INT0))
        {
            AOS_SW_Trigger();
            //DDL_DelayMS(1);
        }
        DMA_ClearTransIntStatus(M4_DMA1, DMA_TC_INT0);
//        if(memcmp(color_p, test_buf, line_size))
//        {
//          while(1);
//        }
#endif
    }


#else
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

    int32_t x;
    int32_t y;
//    GPIO_TogglePins(TEST_PORT, TEST_PIN);
////    NT35510_SetCursor(area->x1, area->y1);
////    LCD_WriteReg(NT35510_WRITE_RAM);
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            /* Put a pixel to the display. For example: */
            /* put_px(x, y, *color_p)*/
//          GPIO_TogglePins(TEST_PORT, TEST_PIN);
            NT35510_WritePixel(x, y, color_p->full);
////          LCD_WriteData(color_p->full);
//            GPIO_TogglePins(TEST_PORT, TEST_PIN);
            color_p++;
            cnt++;

        }
    }
//    GPIO_TogglePins(TEST_PORT, TEST_PIN);
#endif
    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
//    cnt++;
    lv_disp_flush_ready(disp_drv);
}


/*OPTIONAL: GPU INTERFACE*/
#if LV_USE_GPU

/* If your MCU has hardware accelerator (GPU) then you can use it to blend to memories using opacity
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
    /*It's an example code which should be done by your GPU*/
    uint32_t i;
    for(i = 0; i < length; i++) {
        dest[i] = lv_color_mix(dest[i], src[i], opa);
    }
}

/* If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
                    const lv_area_t * fill_area, lv_color_t color)
{
    /*It's an example code which should be done by your GPU*/
    int32_t x, y;
    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/

    for(y = fill_area->y1; y <= fill_area->y2; y++) {
        for(x = fill_area->x1; x <= fill_area->x2; x++) {
            dest_buf[x] = color;
        }
        dest_buf+=dest_width;    /*Go to the next line*/
    }
}

#endif  /*LV_USE_GPU*/

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
