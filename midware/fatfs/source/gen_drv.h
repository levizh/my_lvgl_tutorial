/**
 *******************************************************************************
 * @file  gen_drv.h
 * @brief Header for gen_drv.c module.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-04-28       Yangjp          First version
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
#ifndef __GEN_DRV_H__
#define __GEN_DRV_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ff.h"
#include "diskio.h"
#include <stdint.h>

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief Disk IO Driver structure definition
 */
typedef struct
{
    DSTATUS (*initialize) (BYTE);                           /*!< Initialize Disk Drive  */
    DSTATUS (*status)     (BYTE);                           /*!< Get Disk Status        */
    DRESULT (*read)       (BYTE, BYTE*, DWORD, UINT);       /*!< Read Sector(s)         */
    DRESULT (*write)      (BYTE, const BYTE*, DWORD, UINT); /*!< Write Sector(s)        */
    DRESULT (*ioctl)      (BYTE, BYTE, void*);              /*!< I/O control operation  */
} stc_diskio_drv_t;

/**
 * @brief Global Disk Drivers structure definition
 */
typedef struct
{
    uint8_t                 state[FF_VOLUMES];
    const stc_diskio_drv_t *drv[FF_VOLUMES];
    uint8_t                 lun[FF_VOLUMES];
    volatile uint8_t        nbr;
} stc_disk_drv_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
uint8_t FatFS_LinkDriver(const stc_diskio_drv_t *drv, char path[]);
uint8_t FatFS_UnLinkDriver(char path[]);
uint8_t FatFS_LinkDriverEx(const stc_diskio_drv_t *drv, char path[], BYTE lun);
uint8_t FatFS_UnLinkDriverEx(const char path[], BYTE lun);
uint8_t FatFS_GetLinkDriverNbr(void);

#ifdef __cplusplus
}
#endif

#endif /* __GEN_DRV_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
