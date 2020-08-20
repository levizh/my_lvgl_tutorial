/**
 *******************************************************************************
 * @file  gen_drv.c
 * @brief FatFs generic driver.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#include "gen_drv.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
stc_disk_drv_t gDiskDrv = {{0}, {0}, {0}, 0};

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
 * @brief  Links a compatible diskio driver and increments the number of active
 *         linked drivers.
 * @note   The number of linked drivers (volumes) is up to 10 due to FatFs limits
 * @param  drv:  Pointer to the disk IO Driver structure
 * @param  path: Pointer to the logical drive path
 * @retval An uint8_t value:
 *           - 0: Links success
 *           - 1: Links failed
 */
uint8_t FatFS_LinkDriver(const stc_diskio_drv_t *drv, char path[])
{
    return FatFS_LinkDriverEx(drv, path, 0U);
}

/**
  * @brief  Unlinks a diskio driver and decrements the number of active linked
  *         drivers.
  * @param  path: Pointer to the logical drive path
 * @retval An uint8_t value:
 *           - 0: Unlinks success
 *           - 1: Unlinks failed
  */
uint8_t FatFS_UnLinkDriver(char path[])
{
    return FatFS_UnLinkDriverEx(path, 0U);
}

/**
 * @brief  Links a compatible diskio driver/lun id and increments the number of active
 *         linked drivers.
 * @note   The number of linked drivers (volumes) is up to 10 due to FatFs limits.
 * @param  drv:  Pointer to the disk IO Driver structure
 * @param  path: Pointer to the logical drive path
 * @param  lun : Only used for USB Key Disk to add multi-lun management
                 else the parameter must be equal to 0
 * @retval An uint8_t value:
 *           - 0: Links success
 *           - 1: Links failed
 */
uint8_t FatFS_LinkDriverEx(const stc_diskio_drv_t *drv, char path[], uint8_t lun)
{
    uint8_t u8Ret = 1U;
    uint8_t u8DiskNum = 0U;

    if (gDiskDrv.nbr < (uint8_t)FF_VOLUMES)
    {
        gDiskDrv.state[gDiskDrv.nbr] = 0U;
        gDiskDrv.drv[gDiskDrv.nbr]   = drv;
        gDiskDrv.lun[gDiskDrv.nbr]   = lun;
        u8DiskNum = gDiskDrv.nbr++;
        path[0]   = u8DiskNum + '0';
        path[1]   = ':';
        path[2]   = '/';
        path[3]   = 0;
        u8Ret     = 0U;
    }

    return u8Ret;
}

/**
  * @brief  Unlinks a diskio driver and decrements the number of active linked
  *         drivers.
  * @param  path: Pointer to the logical drive path
  * @param  lun : Not used
 * @retval An uint8_t value:
 *           - 0: Unlinks success
 *           - 1: Unlinks failed
  */
uint8_t FatFS_UnLinkDriverEx(const char path[], uint8_t lun)
{
    uint8_t u8DiskNum = 0U;
    uint8_t u8Ret = 1U;

    if (gDiskDrv.nbr >= 1U)
    {
        u8DiskNum = path[0] - (int8_t)'0';
        if (0 != gDiskDrv.drv[u8DiskNum])
        {
            gDiskDrv.drv[u8DiskNum] = 0;
            gDiskDrv.lun[u8DiskNum] = 0U;
            gDiskDrv.nbr--;
            u8Ret = 0U;
        }
    }

    return u8Ret;
}

/**
 * @brief  Gets number of linked drivers to the FatFs module.
 * @param  None
 * @retval Number of attached drivers.
 */
uint8_t FatFS_GetLinkDriverNbr(void)
{
    return gDiskDrv.nbr;
}

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
