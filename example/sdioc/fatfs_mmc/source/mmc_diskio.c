/**
 *******************************************************************************
 * @file  sdioc/fatfs_mmc/source/mmc_diskio.c
 * @brief MMC Disk I/O driver.
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
#include "mmc.h"
#include "gen_drv.h"
#include "mmc_diskio.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define SDIOC_MMC_UINT                          (M4_SDIOC1)
#define SDIOC_MMC_CLK                           (PWC_FCG1_SDIOC1)

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
#define MMC_DEFAULT_BLOCK_SIZE                  (512U)
/* MMC read/write timeout time */
#define MMC_RW_TIMEOUT_TIME                     (30000UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
stc_mmc_handle_t MmcHandle;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static DSTATUS MMC_CheckStatus(BYTE lun);

DSTATUS MMC_Initialize (BYTE);
DSTATUS MMC_Status (BYTE);
DRESULT MMC_Read (BYTE, BYTE*, DWORD, UINT);
DRESULT MMC_Write (BYTE, const BYTE*, DWORD, UINT);
DRESULT MMC_Ioctl (BYTE, BYTE, void*);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static volatile DSTATUS MmcStat = (DSTATUS)STA_NOINIT;

/* MMC card disk driver */
const stc_diskio_drv_t gMMCDriver =
{
    &MMC_Initialize,
    &MMC_Status,
    &MMC_Read,
    &MMC_Write,
    &MMC_Ioctl,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Initializes the MMC GPIO.
 * @param  None
 * @retval None
 */
static void MMCCard_GpioInit(void)
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
 * @brief  Get MMC card insert status.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: MMC card inserted
 *           - Reset: No MMC card insert
 */
static en_flag_status_t MMCCard_GetInsertStatus(void)
{
    en_flag_status_t enFlagSta = Set;

    /* Check MMC card detect pin */
    if (0U != BSP_IO_ReadPortPin(EIO_PORT0, EIO_SDIC1_CD))
    {
        enFlagSta = Reset;
    }

    return enFlagSta;
}

/**
 * @brief  MMC card configuration.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Configuration success
 *           - Error: Configuration failed
 */
static en_result_t MMCCard_Config(void)
{
    en_result_t enRet = Error;

    /* Init MMC GPIO */
    MMCCard_GpioInit();
    /* Enable SDIOC clock */
    PWC_Fcg1PeriphClockCmd(SDIOC_MMC_CLK, Enable);

    /* Configure structure initialization */
    MmcHandle.SDIOCx                          = SDIOC_MMC_UINT;
    MmcHandle.stcSdiocInit.u32Mode            = SDIOC_MODE_MMC;
    MmcHandle.stcSdiocInit.u8CardDetectSelect = SDIOC_CARD_DETECT_CD_PIN_LEVEL;
    MmcHandle.stcSdiocInit.u8SpeedMode        = SDIOC_SPEED_MODE_HIGH;
    MmcHandle.stcSdiocInit.u8BusWidth         = SDIOC_BUS_WIDTH_4BIT;
    MmcHandle.stcSdiocInit.u16ClockDiv        = SDIOC_CLOCK_DIV_2;
    MmcHandle.DMAx    = NULL;

    /* Reset SDIOC */
    if (Ok != SDIOC_SoftwareReset(MmcHandle.SDIOCx, SDIOC_SW_RESET_ALL))
    {
        printf("Reset SDIOC failed!\r\n");
    }
    else
    {
        if (Set != MMCCard_GetInsertStatus())
        {
            printf("No MMC card insertion!\r\n");
        }
        else
        {
            if (Ok != MMC_Init(&MmcHandle))
            {
                printf("MMC card initialize failed!\r\n");
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
 * @brief  Get MMC card state.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Data transfer is acting
 *           - Error: No data transfer is acting
 */
static en_result_t MMCCard_GetCardTransState(void)
{
    en_result_t enRet = Error;
    en_mmc_card_state_t enCardState;

    enRet = MMC_GetCardState(&MmcHandle, &enCardState);
    if (Ok == enRet)
    {
        if (MMCCardStateTransfer == enCardState)
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Check the MMC card status.
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
static DSTATUS MMC_CheckStatus(BYTE lun)
{
    MmcStat = (DSTATUS)STA_NOINIT;
    en_result_t enRet = Ok;

    enRet = MMCCard_GetCardTransState();
    if (Ok == enRet)
    {
        MmcStat &= (DSTATUS)(~(DSTATUS)STA_NOINIT);
    }

    return MmcStat;
}

/**
 * @brief  Initializes a Drive
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
DSTATUS MMC_Initialize(BYTE lun)
{
    MmcStat = (DSTATUS)STA_NOINIT;

    if (Ok == MMCCard_Config())
    {
        MmcStat = MMC_CheckStatus(lun);
    }

    return MmcStat;
}

/**
 * @brief  Gets Disk Status
 * @param  lun: Not used
 * @retval DSTATUS: Operation status
 */
DSTATUS MMC_Status(BYTE lun)
{
    return MMC_CheckStatus(lun);
}

/**
 * @brief  Reads Sector(s)
 * @param  lun: Not used
 * @param  buff: Pointer to data buffer used to store read data
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to read (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT MMC_Read(BYTE lun, BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_ERROR;

    if (Ok == MMC_ReadBlocks(&MmcHandle, (uint32_t)sector, (uint16_t)count, (uint8_t *)buff, MMC_RW_TIMEOUT_TIME))
    {
        /* Wait until the read operation is finished */
        while (Ok != MMCCard_GetCardTransState())
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
DRESULT MMC_Write(BYTE lun, const BYTE *buff, DWORD sector, UINT count)
{
    DRESULT res = RES_ERROR;

    if (Ok == MMC_WriteBlocks(&MmcHandle, (uint32_t)sector, (uint16_t)count, (uint8_t *)buff, MMC_RW_TIMEOUT_TIME))
    {
        /* Wait until the Write operation is finished */
        while (Ok != MMCCard_GetCardTransState())
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
DRESULT MMC_Ioctl(BYTE lun, BYTE cmd, void *buff)
{
    DRESULT res = RES_ERROR;
    stc_mmc_card_info_t stcCardInfo;

    if (0U != (MmcStat & (DSTATUS)STA_NOINIT))
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
                MMC_GetCardInfo(&MmcHandle, &stcCardInfo);
                *(DWORD*)buff = stcCardInfo.u32LogBlockNbr;
                res = RES_OK;
                break;
            /* Get R/W sector size (WORD) */
            case GET_SECTOR_SIZE :
                MMC_GetCardInfo(&MmcHandle, &stcCardInfo);
                *(WORD*)buff = (uint16_t)stcCardInfo.u32LogBlockSize;
                res = RES_OK;
                break;
            /* Get erase block size in unit of sector (DWORD) */
            case GET_BLOCK_SIZE :
                MMC_GetCardInfo(&MmcHandle, &stcCardInfo);
                *(DWORD*)buff = stcCardInfo.u32LogBlockSize / MMC_DEFAULT_BLOCK_SIZE;
                res = RES_OK;
                break;
            default:
                res = RES_PARERR;
                break;
        }
    }

    return res;
}

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
