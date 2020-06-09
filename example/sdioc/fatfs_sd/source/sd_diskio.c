/**
 *******************************************************************************
 * @file  sdioc/fatfs_sd/source/sd_diskio.c
 * @brief SD Disk I/O driver.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "sd.h"
#include "gen_drv.h"
#include "sd_diskio.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup FatFS_SD_Card
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define SDIOC_SD_UINT                           (M4_SDIOC1)
#define SDIOC_SD_CLK                            (PWC_FCG1_SDIOC1)

/* CK = PC12 */
#define SDIOC_CK_PORT                           (GPIO_PORT_C)
#define SDIOC_CK_PIN                            (GPIO_PIN_12)
/* CMD = PD02 */
#define SDIOC_CMD_PORT                          (GPIO_PORT_D)
#define SDIOC_CMD_PIN                           (GPIO_PIN_02)
/* D0 = PB07 */
#define SDIOC_D0_PORT                           (GPIO_PORT_B)
#define SDIOC_D0_PIN                            (GPIO_PIN_07)
/* D1 = PA08 */
#define SDIOC_D1_PORT                           (GPIO_PORT_A)
#define SDIOC_D1_PIN                            (GPIO_PIN_08)
/* D2 = PC10 */
#define SDIOC_D2_PORT                           (GPIO_PORT_C)
#define SDIOC_D2_PIN                            (GPIO_PIN_10)
/* D3 = PB05 */
#define SDIOC_D3_PORT                           (GPIO_PORT_B)
#define SDIOC_D3_PIN                            (GPIO_PIN_05)

/* Block size is 512 bytes */
#define SD_DEFAULT_BLOCK_SIZE                   (512U)
/* SD read/write timeout time */
#define SD_RW_TIMEOUT_TIME                      (30000UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
stc_sd_handle_t SdHandle;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static DSTATUS SD_CheckStatus(BYTE lun);

DSTATUS SD_Initialize (BYTE);
DSTATUS SD_Status (BYTE);
DRESULT SD_Read (BYTE, BYTE*, DWORD, UINT);
DRESULT SD_Write (BYTE, const BYTE*, DWORD, UINT);
DRESULT SD_Ioctl (BYTE, BYTE, void*);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static volatile DSTATUS SdStat = (DSTATUS)STA_NOINIT;

/* SD card disk driver */
const stc_diskio_drv_t gSDDriver =
{
    &SD_Initialize,
    &SD_Status,
    &SD_Read,
    &SD_Write,
    &SD_Ioctl,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SD_DISKIO_Global_Functions SD DISKIO Global Functions
 * @{
 */

/**
 * @brief  Initializes the SD GPIO.
 * @param  None
 * @retval None
 */
static void SDCard_GpioInit(void)
{
    /* SDIO1_CD */
    BSP_IO_ConfigPortPin(EIO_PORT0, EIO_SDIC1_CD, EIO_DIR_IN);

    /* SDIOC pins configuration */
    GPIO_SetFunc(SDIOC_CK_PORT,  SDIOC_CK_PIN,  GPIO_FUNC_9_SDIO1_CK,   PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_CMD_PORT, SDIOC_CMD_PIN, GPIO_FUNC_9_SDIO1_CMD,  PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D0_PORT,  SDIOC_D0_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D1_PORT,  SDIOC_D1_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D2_PORT,  SDIOC_D2_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SDIOC_D3_PORT,  SDIOC_D3_PIN,  GPIO_FUNC_9_SDIO1_DATA, PIN_SUBFUNC_DISABLE);
}

/**
 * @brief  Get SD card insert status.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: SD card inserted
 *           - Reset: No SD card insert
 */
static en_flag_status_t SDCard_GetInsertStatus(void)
{
    en_flag_status_t enFlagSta = Set;

    /* Check SD card detect pin */
    if (0U != BSP_IO_ReadPortPin(EIO_PORT0, EIO_SDIC1_CD))
    {
        enFlagSta = Reset;
    }

    return enFlagSta;
}

/**
 * @brief  SD card configuration.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Configuration success
 *           - Error: Configuration failed
 */
static en_result_t SDCard_Config(void)
{
    en_result_t enRet = Error;

    /* Init SD GPIO */
    SDCard_GpioInit();
    /* Enable SDIOC clock */
    PWC_Fcg1PeriphClockCmd(SDIOC_SD_CLK, Enable);

    /* Configure structure initialization */
    SdHandle.SDIOCx                          = SDIOC_SD_UINT;
    SdHandle.stcSdiocInit.u32Mode            = SDIOC_MODE_SD;
    SdHandle.stcSdiocInit.u8CardDetectSelect = SDIOC_CARD_DETECT_CD_PIN_LEVEL;
    SdHandle.stcSdiocInit.u8SpeedMode        = SDIOC_SPEED_MODE_HIGH;
    SdHandle.stcSdiocInit.u8BusWidth         = SDIOC_BUS_WIDTH_4BIT;
    SdHandle.stcSdiocInit.u16ClockDiv        = SDIOC_CLOCK_DIV_2;
    SdHandle.DMAx    = NULL;

    /* Reset SDIOC */
    if (Ok != SDIOC_SoftwareReset(SdHandle.SDIOCx, SDIOC_SW_RESET_ALL))
    {
        printf("Reset SDIOC failed!\r\n");
    }
    else
    {
        if (Set != SDCard_GetInsertStatus())
        {
            printf("No SD card insertion!\r\n");
        }
        else
        {
            if (Ok != SD_Init(&SdHandle))
            {
                printf("SD card initialize failed!\r\n");
            }
            else
            {
                enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Get SD card state.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Data transfer is acting
 *           - Error: No data transfer is acting
 */
static en_result_t SDCard_GetCardTransState(void)
{
    en_result_t enRet = Error;
    en_sd_card_state_t enCardState;

    enRet = SD_GetCardState(&SdHandle, &enCardState);
    if (Ok == enRet)
    {
        if (SDCardStateTransfer == enCardState)
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Check the SD card status.
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
static DSTATUS SD_CheckStatus(BYTE lun)
{
    SdStat = (DSTATUS)STA_NOINIT;
    en_result_t enRet = Ok;

    enRet = SDCard_GetCardTransState();
    if (Ok == enRet)
    {
        SdStat &= (DSTATUS)(~(DSTATUS)STA_NOINIT);
    }

    return SdStat;
}

/**
 * @brief  Initializes a Drive
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
DSTATUS SD_Initialize(BYTE lun)
{
    SdStat = (DSTATUS)STA_NOINIT;

    if (Ok == SDCard_Config())
    {
        SdStat = SD_CheckStatus(lun);
    }

    return SdStat;
}

/**
 * @brief  Gets Disk Status
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
DSTATUS SD_Status(BYTE lun)
{
    return SD_CheckStatus(lun);
}

/**
 * @brief  Reads Sector(s)
 * @param  lun: Not used
 * @param  buff: Pointer to data buffer used to store read data
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to read (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT SD_Read(BYTE lun, BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_ERROR;

    if (Ok == SD_ReadBlocks(&SdHandle, (uint32_t)sector, (uint16_t)count, (uint8_t *)buff, SD_RW_TIMEOUT_TIME))
    {
        /* Wait until the read operation is finished */
        while (Ok != SDCard_GetCardTransState())
        {
        }
        res = RES_OK;
    }

    return res;
}

/**
 * @brief  Writes Sector(s)
 * @param  lun: Not used
 * @param  buff: Pointer to data to be written
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to write (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT SD_Write(BYTE lun, const BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_ERROR;

    if (Ok == SD_WriteBlocks(&SdHandle, (uint32_t)sector, (uint16_t)count, (uint8_t *)buff, SD_RW_TIMEOUT_TIME))
    {
        /* Wait until the Write operation is finished */
        while (Ok != SDCard_GetCardTransState())
        {
        }
        res = RES_OK;
    }

    return res;
}

/**
 * @brief  I/O control operation
 * @param  lun: Not used
 * @param  cmd: Control code
 * @param  buff: Pointer to buffer used to send/receive data
 * @retval DRESULT: Operation result
 */
DRESULT SD_Ioctl(BYTE lun, BYTE cmd, void *buff)
{
    DRESULT res = RES_ERROR;
    stc_sd_card_info_t stcCardInfo;

    if (0U != (SdStat & (DSTATUS)STA_NOINIT))
    {
        res = RES_NOTRDY;
    }
    else
    {
        switch (cmd)
        {
            /* Make sure that no pending write process */
            case CTRL_SYNC :
                res = RES_OK;
                break;
            /* Get number of sectors on the disk (DWORD) */
            case GET_SECTOR_COUNT :
                SD_GetCardInfo(&SdHandle, &stcCardInfo);
                *(DWORD*)buff = stcCardInfo.u32LogBlockNbr;
                res = RES_OK;
                break;
            /* Get R/W sector size (WORD) */
            case GET_SECTOR_SIZE :
                SD_GetCardInfo(&SdHandle, &stcCardInfo);
                *(WORD*)buff = (uint16_t)stcCardInfo.u32LogBlockSize;
                res = RES_OK;
                break;
            /* Get erase block size in unit of sector (DWORD) */
            case GET_BLOCK_SIZE :
                SD_GetCardInfo(&SdHandle, &stcCardInfo);
                *(DWORD*)buff = stcCardInfo.u32LogBlockSize / SD_DEFAULT_BLOCK_SIZE;
                res = RES_OK;
                break;
            default:
                res = RES_PARERR;
                break;
        }
    }

    return res;
}

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
