/**
 *******************************************************************************
 * @file  ov5640.c
 * @brief This file provides firmware functions for Camera OV5640.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-20       Zhangxl         First version
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
#include "ov5640.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/** @defgroup OV5640
  * @{
  */

#if (BSP_OV5640_ENABLE == BSP_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

const uint16_t OV5640_init_reg_tbl[][2]=
{
                    // system control:24MHz input clock,24MHz PCLK
    0x3008, 0x42,   // b7:software reset <> b6:software power down <> b5~b0:reserved
    0x3017, 0xff,   // b7:FREX <> b6:VSYNC <> b5:HREF <> b4:PCLK <> b3~0:D[9:6] output enable
    0x3018, 0xff,   // b7~2:D[5:0] <> b1~0:GPIO[1:0] output enable
    0x3034, 0x1a,   // b7:reserved <> b6~b4:PLL charge pump control <> b3~b0:MIPI bit mode
    0x3037, 0x13,   // b7~b5:reserved <> b4:PLL root bypass or divider/2 <> b3~b0:PLL pre-divider 1\2\3\4\6\8

    // SCCB control
    0x3103, 0x03, // b1:system clock from PAD or PLL <> b7~b2&&b0:reserved
    0x3108, 0x01, // b7~b6:reserved <> b5~b4:PCLK <> b3~b2:SCLK2x <> b1~b0:SCLK root divider 1/2/4/8

    0x3630, 0x36, //
    0x3631, 0x0e, //
    0x3632, 0xe2, //
    0x3633, 0x12, //
    0x3621, 0xe0, //
    0x3704, 0xa0, //
    0x3703, 0x5a, //
    0x3715, 0x78, //
    0x3717, 0x01, //
    0x370b, 0x60, //
    0x3705, 0x1a, //
    0x3905, 0x02, //
    0x3906, 0x10, //
    0x3901, 0x0a, //
    0x3731, 0x12, //
    0x3600, 0x08, // VCM control
    0x3601, 0x33, // VCM control
    0x302d, 0x60, // system control
    0x3620, 0x52, //
    0x371b, 0x20, //
    0x471c, 0x50, //

    // auto gain control(AGC)
    0x3a13, 0x43, // b7:reserved <> b6:pre-gain enable <> b5~b0:pre-gain value=1.047x
    0x3a18, 0x00, // b7~b2:reserved <> b1~b0:gain ceiling[9:8]
    0x3a19, 0xf8, // b7~b0:gain ceiling[7:0]=15.5x

    0x3635, 0x13, //
    0x3636, 0x03, //
    0x3634, 0x40, //
    0x3622, 0x01, //

    // 50/60Hz detection
    0x3c01, 0x34, // b7:band manual or auto <> b6:band begin reset <> b5:sum auto mode <>
    // b4:band count enbale <> b3~b0:band counter threshold
    0x3c04, 0x28, // b7~b0:threshold low sum
    0x3c05, 0x98, // b7~b0:threshold high sum
    0x3c06, 0x00, // b7~b0:light meter 1 threshold[15:8]
    0x3c07, 0x08, // b7~b0:light meter 1 threshold[7:0]
    0x3c08, 0x00, // b7~b0:light meter 2 threshold[15:8]
    0x3c09, 0x1c, // b7~b0:light meter 2 threshold[7:0]
    0x3c0a, 0x9c, // b7~b0:sample number[15:8]
    0x3c0b, 0x40, // b7~b0:sample number[7:0]

    // image windowing
    0x3810, 0x00, // b7~b4:reserved <> b3~b0:Timing Hoffset[11:8]
    0x3811, 0x10, // b7~b0:Timing Hoffset[7:0]
    0x3812, 0x00, // b7~b3:reserved <> b2~b0:Timing Voffset[10:8]
    //0x3813, 0x04, // b7~b0:Timing Voffset[7:0]
    0x3708, 0x64, // ??

    // black level calibration(BLC)
    //0x4000, 0x89, // b7~b3:reserved <> b2:apply 2 line <> b1:average frame <> b0:BLC enable
    0x4001, 0x02,   // b7~b6:reserved <> b5~b0:BLC start line
    0x4005, 0x1a,   // b7~b2:reserved <> b1:BLC update always or normal freeze <> b0:reserved

    // system control:DVP enable
    0x3000, 0x00, // b7~b0:blocks reset control reset or enable
    0x3004, 0xff, // b7~b0:blocks clock control enable or disable
    0x300e, 0x58, // b7~b3:MIPI about(MIPI power down) <> b2:MIPI/DVP select <> b1~b0:reserved
    0x302e, 0x00, // ??

    // format control
    0x4300, 0x30, // YUV422,YUYV
    0x501f, 0x00, // ?? YUV 422
    0x440e, 0x00, // ?? JPEG control

    // image sensor processor (ISP)
    0x5000, 0xa7, // b7:lenc on <> b5:raw gamma on <> b2:BPC on <> b1:WPC on <> b0:CIP on

    // auto exposure control (AEC)
    0x3a0f, 0x30, // b7~b0:stable range in high
    0x3a10, 0x28, // b7~b0:stable range in low
    0x3a1b, 0x30, // b7~b0:stable range out high
    0x3a1e, 0x26, // b7~b0:stable range out low
    0x3a11, 0x60, // b7~b0:fast zone high
    0x3a1f, 0x14, // b7~b0:fast zone low

    // lens correction (LENC)
    0x5800, 0x23, // b7~b6:reserved <> b5~b0:green matrix
    0x5801, 0x14, // b7~b6:reserved <> b5~b0:green matrix
    0x5802, 0x0f, // b7~b6:reserved <> b5~b0:green matrix
    0x5803, 0x0f, // b7~b6:reserved <> b5~b0:green matrix
    0x5804, 0x12, // b7~b6:reserved <> b5~b0:green matrix
    0x5805, 0x26, // b7~b6:reserved <> b5~b0:green matrix
    0x5806, 0x0c, // b7~b6:reserved <> b5~b0:green matrix
    0x5807, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x5808, 0x05, // b7~b6:reserved <> b5~b0:green matrix
    0x5809, 0x05, // b7~b6:reserved <> b5~b0:green matrix
    0x580a, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x580b, 0x0d, // b7~b6:reserved <> b5~b0:green matrix
    0x580c, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x580d, 0x03, // b7~b6:reserved <> b5~b0:green matrix
    0x580e, 0x00, // b7~b6:reserved <> b5~b0:green matrix
    0x580f, 0x00, // b7~b6:reserved <> b5~b0:green matrix
    0x5810, 0x03, // b7~b6:reserved <> b5~b0:green matrix
    0x5811, 0x09, // b7~b6:reserved <> b5~b0:green matrix
    0x5812, 0x07, // b7~b6:reserved <> b5~b0:green matrix
    0x5813, 0x03, // b7~b6:reserved <> b5~b0:green matrix
    0x5814, 0x00, // b7~b6:reserved <> b5~b0:green matrix
    0x5815, 0x01, // b7~b6:reserved <> b5~b0:green matrix
    0x5816, 0x03, // b7~b6:reserved <> b5~b0:green matrix
    0x5817, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x5818, 0x0d, // b7~b6:reserved <> b5~b0:green matrix
    0x5819, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x581a, 0x05, // b7~b6:reserved <> b5~b0:green matrix
    0x581b, 0x06, // b7~b6:reserved <> b5~b0:green matrix
    0x581c, 0x08, // b7~b6:reserved <> b5~b0:green matrix
    0x581d, 0x0e, // b7~b6:reserved <> b5~b0:green matrix
    0x581e, 0x29, // b7~b6:reserved <> b5~b0:green matrix
    0x581f, 0x17, // b7~b6:reserved <> b5~b0:green matrix
    0x5820, 0x11, // b7~b6:reserved <> b5~b0:green matrix
    0x5821, 0x11, // b7~b6:reserved <> b5~b0:green matrix
    0x5822, 0x15, // b7~b6:reserved <> b5~b0:green matrix
    0x5823, 0x28, // b7~b6:reserved <> b5~b0:green matrix
    0x5824, 0x46, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5825, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5826, 0x08, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5827, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5828, 0x64, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5829, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582a, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582b, 0x22, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582c, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582d, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582e, 0x06, // b7~b4:blue matrix <> b3~b0:red matrix
    0x582f, 0x22, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5830, 0x40, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5831, 0x42, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5832, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5833, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5834, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5835, 0x22, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5836, 0x22, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5837, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5838, 0x44, // b7~b4:blue matrix <> b3~b0:red matrix
    0x5839, 0x24, // b7~b4:blue matrix <> b3~b0:red matrix
    0x583a, 0x26, // b7~b4:blue matrix <> b3~b0:red matrix
    0x583b, 0x28, // b7~b4:blue matrix <> b3~b0:red matrix
    0x583c, 0x42, // b7~b4:blue matrix <> b3~b0:red matrix
    0x583d, 0xce, // b7~b4:lenc b offset <> b3~b0:lenc r offset

    // auto white balance(AWB)
    0x5180, 0xff, // b7~b0:AWB B block
    0x5181, 0xf2, // b7~b6:step local <> b5~b4:step fast <> b3:slop 8x <> b2:slop 4x <> b1:one zone <> b0:AVG all
    0x5182, 0x00, // b7~b4:max local counter <> b3~b0:max fast counter
    0x5183, 0x14, // b7:AWB simple or advanced <> b6:YUV enable <> b5:AWB preset <> b4:AWB SIMF <> b3~b2:AWB win
    0x5184, 0x25, // b7~b6:count area <> b5:G enable <> b4~b2:count limit <> b1~b0:count threshold
    0x5185, 0x24, // b7~b4:stable range unstable <> b3~b0:stable range stable
    0x5186, 0x09, // ?? about advance
    0x5187, 0x09, // ?? about advance
    0x5188, 0x09, // ?? about advance
    0x5189, 0x75, // ?? about advance
    0x518a, 0x54, // ?? about advance
    0x518b, 0xe0, // ?? about advance
    0x518c, 0xb2, // ?? about advance
    0x518d, 0x42, // ?? about advance
    0x518e, 0x3d, // ?? about advance
    0x518f, 0x56, // ?? about advance
    0x5190, 0x46, // ?? about advance
    0x5191, 0xf8, // b7~b0:AWB top limit
    0x5192, 0x04, // b7~b0:AWB bottom limit
    0x5193, 0x70, // b7~b0:red limit
    0x5194, 0xf0, // b7~b0:green limit
    0x5195, 0xf0, // b7~b0:blue limit
    0x5196, 0x03, // b7~b6:reserved <> b5:AWB freeze <> b4:reserved <>
    // b3~b2:simple select <> b1:fast enable <> b0:AWB bias stat
    0x5197, 0x01, // b7~b0:local limit
    0x5198, 0x04, // ??
    0x5199, 0x12, // ??
    0x519a, 0x04, // ??
    0x519b, 0x00, // ??
    0x519c, 0x06, // ??
    0x519d, 0x82, // ??
    0x519e, 0x38, // b7~b4:reserved <> b3:local limit select <> b2:simple stable select <> b1~b0:reserved

    // raw gamma(GMA)
    0x5480, 0x01, // b7~b2:reserved <> b1:YSLP15 manual enable <> b0:gamma bias plus on
    0x5481, 0x08, // b7~b0:Y yst
    0x5482, 0x14, // b7~b0:Y yst
    0x5483, 0x28, // b7~b0:Y yst
    0x5484, 0x51, // b7~b0:Y yst
    0x5485, 0x65, // b7~b0:Y yst
    0x5486, 0x71, // b7~b0:Y yst
    0x5487, 0x7d, // b7~b0:Y yst
    0x5488, 0x87, // b7~b0:Y yst
    0x5489, 0x91, // b7~b0:Y yst
    0x548a, 0x9a, // b7~b0:Y yst
    0x548b, 0xaa, // b7~b0:Y yst
    0x548c, 0xb8, // b7~b0:Y yst
    0x548d, 0xcd, // b7~b0:Y yst
    0x548e, 0xdd, // b7~b0:Y yst
    0x548f, 0xea, // b7~b0:Y yst
    0x5490, 0x1d, // b7~b0:Y yst

    // color matrix(CMX):é?2ê???ó
    0x5381, 0x1e, // b7~b0:CMX1 for Y
    0x5382, 0x5b, // b7~b0:CMX2 for Y
    0x5383, 0x08, // b7~b0:CMX3 for Y
    0x5384, 0x0a, // b7~b0:CMX4 for U
    0x5385, 0x7e, // b7~b0:CMX5 for U
    0x5386, 0x88, // b7~b0:CMX6 for U
    0x5387, 0x7c, // b7~b0:CMX7 for V
    0x5388, 0x6c, // b7~b0:CMX8 for V
    0x5389, 0x10, // b7~b0:CMX9 for V
    0x538a, 0x01, // b7~b1:reserved <> b0:CMX9 sign
    0x538b, 0x98, // b7~b0:CMX8~1 sign

    // special digital effects (SDE):(UV adjust)
    0x5580, 0x06, // b7:fixed Y enable <> b6:negative enable <> b5:gray enable <> b4:dixed V enable
    // b3:fixed U enable <> b2:contrast enable <> b1:saturation enable <> b0:hue enable
    0x5583, 0x40, // b7~b0:max value for UV adjust
    0x5584, 0x10, // b7~b0:min value for UV adjust
    0x5589, 0x10, // b7~b0:UV adjust threshold 1 valid
    0x558a, 0x00, // b7~b1:reserved <> b0:UV adjust threshold 2 valid
    0x558b, 0xf8, // b7~b0:UV adjust threshold 2 valid
    0x501d, 0x40, // ?? enable manual offset of contrast

    // color interpolation (CIP)
    0x5300, 0x08, // b7~b0:CIP sharpen MT threshold 1
    0x5301, 0x30, // b7~b0:CIP sharpen MT threshold 2
    0x5302, 0x10, // b7~b0:CIP sharpen MT offset 1
    0x5303, 0x00, // b7~b0:CIP sharpen MT offset 2
    0x5304, 0x08, // b7~b0:CIP DNS threshold 1
    0x5305, 0x30, // b7~b0:CIP DNS threshold 2
    0x5306, 0x08, // b7~b0:CIP DNS offset 1
    0x5307, 0x16, // b7~b0:CIP DNS offset 2
    // ??????
    //0x5308, 0x25, // b7:reserved <> b6:CIP edge MT manual enable <> b5:reserved <>
    //              // b4:CIP DNS manual enable <> b3:reserved <> b2~b0:CIP threshold for BR sharpen
    0x5309, 0x08, // b7~b0:CIP sharpen TH threshold 1
    0x530a, 0x30, // b7~b0:CIP sharpen TH threshold 2
    0x530b, 0x04, // b7~b0:CIP sharpen TH offset 1
    0x530c, 0x06, // b7~b0:CIP sharpen TH offset 2
    0x5025, 0x00, // ??

    // system control:wake up from standby
    0x3008, 0x02, // b7:software reset <> b6:software power down <> b5~b0:reserved

    // DVP control
    0x4740, 0X21, // b7~b6:reserved <> b5:PCLK polarity H/L <> b4:reserved <> b3:gate PCLK under VSYNC <>
    // b2:gate PCLK under HREF <> b1:HREF polarity H/L <> b0:VSYNC polarity H/L

    0x4740, 0X21,
};

//---RGB565模式设定参数表:帧速15FPS,最大图像输出1280*800
const uint16_t OV5640_RGB565_reg_tbl[][2]=
{
                // format control
//0x4300, 0X61, // GRB565,{r[4:0],g[5:0],b[4:0]}
                // ??????
  0x4300, 0X6F, // GRB565,{r[4:0],g[5:0],b[4:0]}
  0X501f, 0x01, // ??

                // system control
  0x3035, 0x11, // b7~b4:system clock divider slow down all clocks
                // b3~b0:scale divider for MIPI PCLK/SERCLK can be slowed down
  0x3036, 0x90, // b7~b0:PLL multiplier
                // a0: 64M NG
                // 9c: 62M OK
                // 98: 60M OK
                // 90: 58M OK

                // 50/60 detection
                // ??????
  0x3c07, 0x07, // b7~b0:light meter 1 threshold[7:0]

                // timing control
  0x3820, 0x42, // b7~b3:reserved <> b2:ISP vflip <> b1:sensor vflip <> b0:reserved
  0x3821, 0x00, // b7~b6:reserved <> b5:JPEG enable <> b4~b3:reserved <>
                // b2:ISP mirror <> b1:sensor mirror <> b0:horizontal binning enable
  0x3814, 0x11, // b7~b4:horizontal odd subsample increment <> b3~b0:even
  0x3815, 0x11, // b7~b4:vertical odd subsample increment <> b3~b0:even
  0x3800, 0x00, // b7~b4:reserved <> b3~b0:X address start[11:8]
  0x3801, 0x00, // b7~b0:X address start[7:0]
  0x3802, 0x00, // b7~b4:reserved <> b3~b0:Y address start[11:8]
  0x3803, 0x00, // b7~b0:Y address start[7:0]
  0x3804, 0x0a, // b7~b4:reserved <> b3~b0:X address end[11:8]
  0x3805, 0x20, // b7~b0:X address end[7:0]
  0x3806, 0x07, // b7~b3:reserved <> b2~b0:Y address end[10:8]
  0x3807, 0x98, // b7~b0:Y address end[7:0]
                // ****---- ISP Size：0xa20*0x798=2592*1944; figure4-2 ----****
//	0x380c, 0x05, // b7~b4:reserved <> b3~b0:total horizontal size byte[11:8]
//	0x380d, 0xf8, // b7~b0:total horizontal size byte[7:0]
//	0x380e, 0x03, // b7~b0:total vertical size byte[15:8]
//	0x380f, 0x84, // b7~b0:total vertical size byte[7:0]
//  0x3813, 0x04, // b7~b0:Timing Voffset[7:0]
//
//	0x3618, 0x00, // ??
//	0x3612, 0x29, // ??
//	0x3709, 0x52, // ??
//	0x370c, 0x03, // ??
//
//	              // AEC control
//	0x3a02, 0x02, // b7~b0:60Hz max exposure[15:8]
//	0x3a03, 0xe0, // b7~b0:60Hz max exposure[7:0]
//	0x3a14, 0x02, // b7~b4:reserved <> b3~b0:50Hz max exposure[11:8]
//	0x3a15, 0xe0, // b7~b0:50Hz max exposure[7:0]
//
//	              // BLC control
//	0x4004, 0x02, // b7~b0:BLC line number
//
//		            // system control
//	0x3002, 0x1c, // b7~b0:blocks reset control reset or enable
//	0x3006, 0xc3, // b7~b0:blocks clock control enable or disable
//
//	              // DVP control
////0x4713, 0x03, // b7~b3:reserved <> b2~b0:JPEG mode select 3
////0x471b, 0x03,
////0x471d, 0x00,
//  0x4740, 0x20, // b5:PIXCLK Active Level <> b1:HSYNC Active Level  <> b0:VSYNC Active Level

                // JPEG control
  0x4407, 0x04, // b7:enable read QTA auto increment <> b6:reserved <> b5~b0:quantization sacle

                // VFIFO control
  0x460b, 0x37, // ??
  0x460c, 0x20, // b7~b4:JPEG dummy data pad speed <> b3:reserved <>
                // b2:footer disable <> b1:PCLK manual enable by 0x3824[4:0] or auto <> b0:reserved

                // MIPI control
  0x4837, 0x16, // b7~b0:PCLK period of pixel clock

  0x3824, 0x04, // ?? PCLK manual divider

                // ISP control
  0x5001, 0xa3, // b7:SDE on <> b5:scaling on <>b3:UV average off <> b1:CMX on <> b0:AWB on

                // AEC/AGC control
  0x3503, 0x00, // bit7~2:reserved <> b1:AGC manual or auto <> b0:AEC manual or auto
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup OV5640_Global_Functions OV5640 Global Functions
 * @{
 */
/**
 * @brief  Camera device initialize.
 * @param  none
 * @retval none
 */
void OV5640_Init(void)
{
    uint8_t reg_val = 0U;
    uint32_t i = 0;
    /* 0x5640 */
    BSP_CAM_ReadReg(OV5640_CHIPIDH, (uint8_t *)&reg_val, 1);
    BSP_CAM_ReadReg(OV5640_CHIPIDL, (uint8_t *)&reg_val, 1);

    reg_val = 0x11U;
    BSP_CAM_WriteReg(0x3103U, (uint8_t *)&reg_val, 1U);

    reg_val = 0x82U;
    BSP_CAM_WriteReg(0x3008U, (uint8_t *)&reg_val, 1U);
    DDL_Delay1ms(100);

    for (i = 0; i < (sizeof(OV5640_init_reg_tbl)/sizeof(uint16_t)); i++)
    {
        BSP_CAM_WriteReg(OV5640_init_reg_tbl[i][0], (uint8_t *)&OV5640_init_reg_tbl[i][1], 1U);
    }
    BSP_OV5640_Light_Ctrl(1U);
    DDL_Delay1ms(50UL);
    BSP_OV5640_Light_Ctrl(0U);
}


void OV5640_RGB565_Mode(void)
{
    uint32_t i=0;
    for(i = 0; i < (sizeof(OV5640_RGB565_reg_tbl)/sizeof(uint16_t)); i++)
    {
        BSP_CAM_WriteReg(OV5640_RGB565_reg_tbl[i][0], (uint8_t *)&OV5640_RGB565_reg_tbl[i][1], 1U);
    }
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval Camera Register Value.
  */
uint16_t OV5640_ReadID(void)
{
    return (0x5510U);
}

/**
  * @brief  Writes to the selected Camera register.
  * @param  Reg: address of the selected register.
  * @param  Data: Data to be written
  * @retval None
  */
void OV5640_WriteReg(uint16_t Reg, uint16_t Data)
{

}

/**
  * @brief  Writes data to the selected Camera register.
  * @param  Camera_Reg: address of the selected register.
  * @retval None
  */
void OV5640_WriteData(uint16_t RegValue)
{

}

/**
  * @brief  Reads the selected Camera Register.
  * @param  None
  * @retval Camera ram Value.
  */
uint32_t OV5640_ReadData(void)
{
    /* Read a max of 4 bytes */
    return (0UL);
}

/**
 * @}
 */

#endif /* BSP_OV5640_ENABLE */

/**
 * @}
 */

/**
 * @}
 */


/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
