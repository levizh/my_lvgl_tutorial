

#ifndef __W25Q64_H__
#define __W25Q64_H__

/**
 * @defgroup W25Q64_Standard_SPI_Instructions W25Q64 Standard SPI Instructions
 * @{
 */
#define W25Q64_WRITE_ENABLE                             (0x06U)
#define W25Q64_VOLATILE_SR_WRITE_ENABLE                 (0x50U)
#define W25Q64_WRITE_DISABLE                            (0x04U)
#define W25Q64_RELEASE_POWER_DOWN_ID                    (0xABU)
#define W25Q64_MANUFACTURER_DEVICE_ID                   (0x90U)
#define W25Q64_JEDEC_ID                                 (0x9FU)
#define W25Q64_READ_UNIQUE_ID                           (0x4BU)
#define W25Q64_READ_DATA                                (0x03U)
#define W25Q64_FAST_READ                                (0x0BU)
#define W25Q64_PAGE_PROGRAM                             (0x02U)
#define W25Q64_SECTOR_ERASE                             (0x20U)
#define W25Q64_BLOCK_ERASE_32KB                         (0x52U)
#define W25Q64_BLOCK_ERASE_64KB                         (0xD8U)
#define W25Q64_CHIP_ERASE                               (0xC7U)
#define W25Q64_READ_STATUS_REGISTER_1                   (0x05U)
#define W25Q64_WRITE_STATUS_REGISTER_1                  (0x01U)
#define W25Q64_READ_STATUS_REGISTER_2                   (0x35U)
#define W25Q64_WRITE_STATUS_REGISTER_2                  (0x31U)
#define W25Q64_READ_STATUS_REGISTER_3                   (0x15U)
#define W25Q64_WRITE_STATUS_REGISTER_3                  (0x11U)
#define W25Q64_READ_SFDP_REGISTER                       (0x5AU)
#define W25Q64_ERASE_SECURITY_REGISTER                  (0x44U)
#define W25Q64_PROGRAM_SECURITY_REGISTER                (0x42U)
#define W25Q64_READ_SECURITY_REGISTER                   (0x48U)
#define W25Q64_GLOBAL_BLOCK_LOCK                        (0x7EU)
#define W25Q64_GLOBAL_BLOCK_UNLOCK                      (0x98U)
#define W25Q64_READ_BLOCK_LOCK                          (0x3DU)
#define W25Q64_INDIVIDUAL_BLOCK_LOCK                    (0x36U)
#define W25Q64_INDIVIDUAL_BLOCK_UNLOCK                  (0x39U)
#define W25Q64_ERASE_PROGRAM_SUSPEND                    (0x75U)
#define W25Q64_ERASE_PROGRAM_RESUME                     (0x7AU)
#define W25Q64_POWER_DOWN                               (0xB9U)
#define W25Q64_ENABLE_RESET                             (0x66U)
#define W25Q64_RESET_DEVICE                             (0x99U)
/**
 * @}
 */

/**
 * @defgroup W25Q64_Dual_Quad_SPI_Instruction W25Q64 Dual Quad SPI Instruction
 * @{
 */
#define W25Q64_FAST_READ_DUAL_OUTPUT                    (0x3BU)
#define W25Q64_FAST_READ_DUAL_IO                        (0xBBU)
#define W25Q64_MFTR_DEVICE_ID_DUAL_IO                   (0x92U)
#define W25Q64_QUAD_INPUT_PAGE_PROGRAM                  (0x32U)
#define W25Q64_FAST_READ_QUAD_OUTPUT                    (0x6BU)
#define W25Q64_MFTR_DEVICE_ID_QUAD_IO                   (0x94U)
#define W25Q64_FAST_READ_QUAD_IO                        (0xEBU)
#define W25Q64_SET_BURST_WITH_WRAP                      (0x77U)
/**
 * @}
 */

/**
 * @defgroup W25Q64_Size W25Q64 Size
 * @{
 */
#define W25Q64_PAGE_SIZE                                (256UL)
#define W25Q64_SECTOR_SIZE                              (4UL * 1024UL)
#define W25Q64_BLOCK_SIZE                               (64UL * 1024UL)
/**
 * @}
 */

/**
 * @defgroup W25Q64_Status_Flag W25Q64 Status Flag
 * @{
 */
#define W25Q64_FLAG_BUSY                                (0x01U)
#define W25Q64_FLAG_SUSPEND                             (0x80U)
/**
 * @}
 */

/**
 * @defgroup W25Q64_Miscellaneous_Macros W25Q64 Miscellaneous Macros
 * @{
 */
#define W25Q64_UNIQUE_ID_SIZE                           (8U)
#define W25Q64_DUMMY_BYTE_VALUE                         (0xffU)
/**
 * @}
 */


#endif
