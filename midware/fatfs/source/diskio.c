/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various existing      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "gen_drv.h"
#include "diskio.h"		/* Declarations of disk functions */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @brief Compiler Macro Definitions
 */
#if defined ( __GNUC__ ) && !defined (__CC_ARM) /*!< GNU Compiler */
  #ifndef __WEAKDEF
    #define __WEAKDEF                   __attribute__((weak))
  #endif /* __WEAKDEF */
#elif defined (__ICCARM__)                /*!< IAR Compiler */
  #ifndef __WEAKDEF
    #define __WEAKDEF                   __weak
  #endif /* __WEAKDEF */
#elif defined (__CC_ARM)                /*!< ARM Compiler */
  #ifndef __WEAKDEF
    #define __WEAKDEF                   __attribute__((weak))
  #endif /* __WEAKDEF */
#else
    #error  "unsupported compiler!!"
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern stc_disk_drv_t gDiskDrv;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Gets Disk Status
 * @param  pdrv:    Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive number to identify the drive */
)
{
	DSTATUS stat;

	stat = gDiskDrv.drv[pdrv]->status(gDiskDrv.lun[pdrv]);

	return stat;
}

/**
 * @brief  Initializes a Drive
 * @param  pdrv:    Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;

	if(gDiskDrv.state[pdrv] == 0)
	{
		gDiskDrv.state[pdrv] = 1;
		stat = gDiskDrv.drv[pdrv]->initialize(gDiskDrv.lun[pdrv]);
	}

	return stat;
}

/**
 * @brief  Reads Sector(s)
 * @param  pdrv:    Physical drive number (0..)
 * @param  buff:    Pointer to data buffer used to store read data
 * @param  sector:  Sector address (LBA)
 * @param  count:   Number of sectors to read (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	res = gDiskDrv.drv[pdrv]->read(gDiskDrv.lun[pdrv], buff, sector, count);

	return res;
}

#if FF_FS_READONLY == 0
/**
 * @brief  Writes Sector(s)
 * @param  pdrv:    Physical drive number (0..)
 * @param  buff:    Pointer to data to be written
 * @param  sector:  Sector address (LBA)
 * @param  count:   Number of sectors to write (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	res = gDiskDrv.drv[pdrv]->write(gDiskDrv.lun[pdrv], buff, sector, count);

	return res;
}
#endif

/**
 * @brief  I/O control operation
 * @param  pdrv:    Physical drive number (0..)
 * @param  cmd:     Control code
 * @param  buff:    Pointer to buffer used to send/receive data
 * @retval DRESULT: Operation result
 */
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	res = gDiskDrv.drv[pdrv]->ioctl(gDiskDrv.lun[pdrv], cmd, buff);

	return res;
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
__WEAKDEF DWORD get_fattime (void)
{
	return 0;
}
