/** @file
 *
 * @brief  CTC wrapper for EtherCAT (AC)
 *
 * @details
 * This module provides RPC functionality for the EtherCAT stack
 *
 * @copyright
 * Copyright 2010-2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_ECAT_RPC_AC_H_
#define GOAL_ECAT_RPC_AC_H_

#include <goal_media/goal_mi_dm.h>
#include "../goal_ecat_rpc.h"
#include <goal_media/goal_mi_mctc.h>


/****************************************************************************/
/* Configuration */
/****************************************************************************/
#define GOAL_ECAT_RPC_BUF_SIZE 1000
#define GOAL_ECAT_CB_DATA_MAX 6
#define GOAL_ECAT_INSTANCE_DEFAULT 0


/****************************************************************************/
/* Types */
/****************************************************************************/

/**< ECAT callback id */
typedef uint32_t GOAL_ECAT_CB_ID_T;

/**< Callback Data Content Structure */
typedef union {
    uint16_t index;                             /**< object index */
    uint8_t subIndex;                           /**< object sub-index */
    uint8_t *pData;                             /**< object data */
    uint32_t size;                              /**< object size */
    GOAL_BOOL_T completeAccess;                 /**< complete object is accessed */
    uint16_t dlState;                           /**< new Data Link layer state */
    uint32_t dcCycleTime;                       /**< current DC cycle time */
    uint32_t dcCycleTimeMin;                    /**< minimum supported DC cycle time */
    uint16_t explDevId;                         /**< Explicit device ID */
    uint16_t esmState;                          /**< new ESM state */
    GOAL_BOOL_T esmError;                       /**< device is in error state */
    uint16_t statusCode;                        /**< status code explaining error */
    uint16_t appStatusCode;                     /**< application specific error */
    uint32_t foePassword;                       /**< password for file access */
    char *pFileName;                            /**< file to be accessed via FoE */
    uint16_t foeError;                          /**< FOE error code */
    uint32_t foeOffset;                         /**< read/write offset in file */
    uint16_t foeMaxSize;                        /**< maximum size of a FOE chunk */
    uint16_t foeActSize;                        /**< actual size of a FOE chunk */
    GOAL_BOOL_T foeFinished;                    /**< write access finished */
    GOAL_BOOL_T bLedEnable;                     /**< led state */
} GOAL_ECAT_CB_DATA_ELEM_T;

/**< Callback Data Structure */
typedef struct {
    GOAL_ECAT_CB_DATA_ELEM_T data[GOAL_ECAT_CB_DATA_MAX]; /**< callback data elements */
} GOAL_ECAT_CB_DATA_T;

typedef struct GOAL_ECAT_PDO_MAPPING_T {
    struct GOAL_ECAT_PDO_MAPPING_T *pNext;      /**< next entry */
    uint16_t index;                             /**< object index */
    uint8_t subIndex;                           /**< object subindex */
    uint32_t attr;                              /**< object attributes */
    GOAL_BOOL_T bMapped;                        /**< mapped flag */
    uint16_t size;                              /**< size of object */
    uint16_t offset;                            /**< data stream offset */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_DM_PART_T dmDataInput;              /**< partition for data mapper */
    GOAL_MI_DM_PART_T dmDataOutput;             /**< partition for data mapper */
#endif
    uint8_t *pData;                             /**< buffer to data */
} GOAL_ECAT_PDO_MAPPING_T;

typedef struct GOAL_ECAT_OBJECT_STR_T{
    struct GOAL_ECAT_OBJECT_STR_T *pNext; /**< next entry */
    uint16_t index;                             /**< object index */
    uint8_t subIndex;                           /**< object subindex */
    uint16_t size;                              /**< size of object */
} GOAL_ECAT_OBJECT_STR_T;

typedef struct {
    GOAL_INSTANCE_HEADER(GOAL_ECAT_T);          /**< instance header */
    uint32_t id;                                /**< instance id */
    void *pFunc;                                /**< EtherCAT callback function */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_MCTC_DP_T mctcDp;                   /**< MCTC data provider status */
    GOAL_MI_DM_PART_T dmTxDp;                   /**< TX data provider status */
    GOAL_MI_DM_PART_T dmDataOutput;             /**< process data, output direction */
    GOAL_MI_DM_PART_T dmDataInput;              /**< process data, input direction */
    GOAL_MI_DM_GROUP_T *pDmGroupInput;          /**< MI DM Input group handle */
    GOAL_MI_DM_GROUP_T *pDmGroupOutput;         /**< MI DM Output group handle */
#endif
    GOAL_ECAT_PDO_MAPPING_T *pListRxPdo;        /**< list of rx pdo mappings */
    GOAL_ECAT_PDO_MAPPING_T *pListTxPdo;        /**< list of tx pdo mappings */
    GOAL_ECAT_OBJECT_STR_T *pListObjectStr;     /**< list of string objects */
} GOAL_ECAT_T;

typedef GOAL_STATUS_T (* GOAL_ECAT_FUNC_CB_T) (
    GOAL_ECAT_T *,                               /**< ECAT handle */
    GOAL_ECAT_CB_ID_T,                           /**< callback id */
    GOAL_ECAT_CB_DATA_T *                        /**< callback parameters */
);

/** data types of the object dictionary */
#define EC_DEFTYPE_UNKNOWN        0x0000        /**< data type: UNKNOWN */
#define EC_DEFTYPE_BOOL           0x0001        /**< data type: BOOL */
#define EC_DEFTYPE_INTEGER8       0x0002        /**< data type: INTEGER8 */
#define EC_DEFTYPE_INTEGER16      0x0003        /**< data type: INTEGER16 */
#define EC_DEFTYPE_INTEGER32      0x0004        /**< data type: INTEGER32 */
#define EC_DEFTYPE_UNSIGNED8      0x0005        /**< data type: UNSIGNED8 */
#define EC_DEFTYPE_UNSIGNED16     0x0006        /**< data type: UNSIGNED16 */
#define EC_DEFTYPE_UNSIGNED32     0x0007        /**< data type: UNSIGNED32 */
#define EC_DEFTYPE_REAL32         0x0008        /**< data type: REAL32 */
#define EC_DEFTYPE_VISSTRING      0x0009        /**< data type: VISSTRING */
#define EC_DEFTYPE_OCTETSTRING    0x000A        /**< data type: OCTETSTRING */
#define EC_DEFTYPE_UNICODESTRING  0x000B        /**< data type: UNICODESTRING */
#define EC_DEFTYPE_TIMEOFDAY      0x000C        /**< data type: TIMEOFDAY */
#define EC_DEFTYPE_REAL64         0x0011        /**< data type: REAL64 */
#define EC_DEFTYPE_INTEGER64      0x0015        /**< data type: INTEGER64 */
#define EC_DEFTYPE_UNSIGNED64     0x001B        /**< data type: UNSIGNED64 */
#define EC_DEFTYPE_BYTE           0x001E        /**< data type: BYTE */
#define EC_DEFTYPE_PDO_MAP        0x0021        /**< data type: PDO_MAP */
#define EC_DEFTYPE_IDENTITY       0x0023        /**< data type: IDENTITY */
#define EC_DEFTYPE_SYNC_PAR       0x0029        /**< data type: SYNC_PAR */

/**
 * return values for service requests
 * @attention values are subject of change, use the enum definition.
 */
typedef enum
{
    RET_OK = 0,                                 /**< request successful */
    RET_BUSY,                                   /**< request not finished yet */
    RET_ERROR,                                  /**< request error */
    RET_ERR_SDO_CMD_SPEC_INVALID = 0x0100,      /**< sdo command specifier invalid */
    RET_ERR_NONEXIST_OBJECT,                    /**< object doesn't exist */
    RET_ERR_NONEXIST_SUBINDEX,                  /**< subindex doesn't exist */
    RET_ERR_WRONG_SIZE,                         /**< object has wrong size */
    RET_ERR_NO_READ_PERM,                       /**< no read permissions */
    RET_ERR_NO_WRITE_PERM,                      /**< no write permissions */
    RET_ERR_PARA_INCOMP,                        /**< unsupported access to object */
    RET_ERR_INTERNAL_INCOMPATIBLE,              /**< internal incompatible */
    RET_ERR_TRANS_TYPE,                         /**< wrong trans type */
    RET_ERR_MAP,                                /**< wrong/inconsistent mapping parameter */
    RET_ERR_SI0_NOT_ZERO,                       /**< subindex 0 not 0 */
    RET_ERR_SDO_GENERAL_ERROR,                  /**< unspecified sdo error */
    RET_ERR_SDO_TOGGLE,                         /**< toggle bit doesn't work correctly */
    RET_ERR_VALUE_TO_LOW,                       /**< value to low */
    RET_ERR_VALUE_TO_HIGH,                      /**< value to high */
    RET_ERR_PDO_LEN_EXCEED,                     /**< number and length of PDO exceed */
    RET_ERR_HARDWARE_ERROR,                     /**< hardware error */
    RET_ERR_PARAM_LENGTH_ERROR,                 /**< parameter length exceed */
    RET_ERR_VALUE_RANGE_EXCEEDED,               /**< value range exceeded */
    RET_ERR_ABORT_STORE_APPL,                   /**< data cannot store to the appl */
    RET_ERR_ABORT_LOCAL_CONTROL_STORE,          /**< data cannot store because local control */
    RET_ERR_ABORT_LOCAL_DEVICE_STATE,           /**< data cannot store because present device state */
    RET_ERR_SDO_PROTOCOL_TIMEOUT,               /**< sdo time out */
    RET_EC_MBX_HANDLE_DISABLED = 0x0200,        /**< Mailbox handling disabled */
    RET_EC_MBX_BUSY,                            /**< Mailbox already in use */
    RET_EC_MBX_BAD_LEN,                         /**< wrong Mailbox length */
    RET_EC_MBX_RETRY_BUSY,                      /**< Mailbox retry busy */
    RET_EC_MBX_UNSUPPORTED_PROTOCOL,            /**< unsupported Mailbox protocol */
    RET_EC_MBX_INVALID_HEADER,                  /**< invalid Mailbox header */
    RET_EC_OD_ACCESS_FAILED,                    /**< access to OD failed */
    RET_EC_PDO_MAP_ERROR,                       /**< PDO mapping error */
    RET_EC_SM_ERROR,                            /**< sync manager error */
    RET_EC_EMQ_FULL,                            /**< emergency queue full */
    RET_EC_EMQ_EMPTY,                           /**< emergency queue empty */
    RET_EC_MBOX_SIZE,                           /**< wrong Mailbox size */
    RET_EC_MBOX_CONFIG,                         /**< wrong Mailbox configuration */
    RET_EC_MBOX_ADDR,                           /**< invalid Mailbox memory address */
    RET_EC_DC_INT,                              /**< DC interrupt not active */
    RET_EC_UNKNOWN_NMT_STATE,                   /**< unknown NMT state */
    RET_EC_DYNOD_NO_RESSOURCE,                  /**< no resource for dynamic OD available */
    RET_EC_SIIPROM_BUSY,                        /**< SII/EEPROM busy */
    RET_EC_SIIPROM_RD_ERROR,                    /**< SII/EEPROM read error */
    RET_EC_SIIPROM_WR_ERROR,                    /**< SII/EEPROM write error */
    RET_EC_SIIPROM_INIT_ERROR,                  /**< initialization of EEPROM Emulation failed */
    EC_RET_OD_GAP,                              /**< OD entry is a gap */
    RET_ERR_MII_ACCESS,                         /**< access to MII management registers denied */
    RET_ERR_MII_PARAM,                          /**< invalid parameter */
    RET_ERR_STATE,                              /**< bad device state */

    RET_ERR_END                                 /**< end marker */
} EC_RET_T;


/** application specific SDO accesses errors */
#define GOAL_ERR_SDO_HARDWARE            (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_HARDWARE_ERROR) /**< hardware error */
#define GOAL_ERR_SDO_TOO_LOW               (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_VALUE_TO_LOW) /**< value to low */
#define GOAL_ERR_SDO_TOO_HIGH             (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_VALUE_TO_HIGH) /**< value to high */
#define GOAL_ERR_SDO_APPL              (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_ABORT_STORE_APPL) /**< application specific reason */
#define GOAL_ERR_SDO_DEV_STATE (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_ABORT_LOCAL_DEVICE_STATE) /**< current device state insufficient */
#define GOAL_ERR_SDO_GENERAL          (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_SDO_GENERAL_ERROR) /**< unspecified SDO error */

/** object dictionary access errors */
#define GOAL_ERR_OBJ_NOT_FOUND        (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_NONEXIST_OBJECT) /**< object not found */
#define GOAL_ERR_SIDX_NOT_FOUND     (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_NONEXIST_SUBINDEX) /**< sub-index not found */
#define GOAL_ERR_OBJ_VAL_TO_HIGH      (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_VALUE_TO_HIGH) /**< new value exceeds object's upper limit */
#define GOAL_ERR_OBJ_VAL_TO_LOW       (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_VALUE_TO_LOW) /**< new value exceeds object's lower limit */
#define GOAL_ERR_OBJ_SIZE          (GOAL_ERROR | GOAL_RES_ECAT | RET_ERR_WRONG_SIZE) /**< invalid data size for object */

/** AL status codes - see register 0x123 */
#define GOAL_ECAT_STATE_CODE_OK                      0x0000 /**< No error */
#define GOAL_ECAT_STATE_CODE_UNSPEC                  0x0001 /**< Unspecified error */
#define GOAL_ECAT_STATE_CODE_NO_MEM                  0x0002 /**< No Memory */
#define GOAL_ECAT_STATE_CODE_INVALID_SETUP           0x0003 /**< Invalid Device Setup */
#define GOAL_ECAT_STATE_CODE_SII_MISMATCH            0x0006 /**< SII/EEPROM information does not match firmware */
#define GOAL_ECAT_STATE_CODE_FW_UPDATE_FAIL          0x0007 /**< Firmware update not successful, old firmware still running */
#define GOAL_ECAT_STATE_CODE_LICENSE_ERR             0x000E /**< License error */
#define GOAL_ECAT_STATE_CODE_INVALID_REQ             0x0011 /**< Invalid requested state change */
#define GOAL_ECAT_STATE_CODE_UNKNOWN_REQ             0x0012 /**< Unknown requested state */
#define GOAL_ECAT_STATE_CODE_NO_BOOTSTRAP            0x0013 /**< Bootstrap not supported */
#define GOAL_ECAT_STATE_CODE_NO_FIRMWARE             0x0014 /**< No valid firmware */
#define GOAL_ECAT_STATE_CODE_INVALID_MBX_CONF_B      0x0015 /**< Invalid mailbox configuration */
#define GOAL_ECAT_STATE_CODE_INVALID_MBX_CONF        0x0016 /**< Invalid mailbox configuration */
#define GOAL_ECAT_STATE_CODE_INVALID_SYNCM_CONFIG    0x0017 /**< Invalid sync manager configuration */
#define GOAL_ECAT_STATE_CODE_NO_INPUTS               0x0018 /**< No valid inputs available */
#define GOAL_ECAT_STATE_CODE_NO_OUTPUTS              0x0019 /**< No valid outputs */
#define GOAL_ECAT_STATE_CODE_UNSPECIFIC_SYNC_ERROR   0x001A /**< Synchronization error */
#define GOAL_ECAT_STATE_CODE_SYNCM_WATCHDOG          0x001B /**< Sync manager watchdog */
#define GOAL_ECAT_STATE_CODE_INVALID_SYNCM_TYPE      0x001C /**< Invalid Sync Manager Types */
#define GOAL_ECAT_STATE_CODE_INVALID_OUTPUT_CONFIG   0x001D /**< Invalid Output Configuration */
#define GOAL_ECAT_STATE_CODE_INVALID_INPUT_CONFIG    0x001E /**< Invalid Input Configuration */
#define GOAL_ECAT_STATE_CODE_INVALID_WD_CONFIG       0x001F /**< Invalid Watchdog Configuration */
#define GOAL_ECAT_STATE_CODE_COLD_START              0x0020 /**< Slave needs cold start */
#define GOAL_ECAT_STATE_CODE_NEED_INIT               0x0021 /**< Slave needs INIT */
#define GOAL_ECAT_STATE_CODE_NEED_PREOP              0x0022 /**< Slave needs PREOP */
#define GOAL_ECAT_STATE_CODE_NEED_SAFEOP             0x0023 /**< Slave needs SAFEOP */
#define GOAL_ECAT_STATE_CODE_INVALID_INPUT_MAPPING   0x0024 /**< Invalid Input Mapping */
#define GOAL_ECAT_STATE_CODE_INVALID_OUTPUT_MAPPING  0x0025 /**< Invalid Output Mapping */
#define GOAL_ECAT_STATE_CODE_INVALID_SETTING         0x0026 /**< Inconsistent Settings */
#define GOAL_ECAT_STATE_CODE_NO_FREERUN              0x0027 /**< FreeRun not supported */
#define GOAL_ECAT_STATE_CODE_INVALID_SYNC_MODE       0x0028 /**< SyncMode not supported */
#define GOAL_ECAT_STATE_CODE_FREERUN_3BUF            0x0029 /**< FreeRun needs 3Buffer Mode */
#define GOAL_ECAT_STATE_CODE_BACKGROUND_WD           0x002A /**< Background Watchdog */
#define GOAL_ECAT_STATE_CODE_INVALID_INPUT_OUTPUT    0x002B /**< No Valid Inputs and Outputs */
#define GOAL_ECAT_STATE_CODE_FATAL_SYNC_ERROR        0x002C /**< Fatal Sync Error */
#define GOAL_ECAT_STATE_CODE_NO_SYNC_RECEIVED        0x002D /**< No Sync Error */
#define GOAL_ECAT_STATE_CODE_SMALL_CYCLE_TIME        0x002E /**< Cycle time too small */
#define GOAL_ECAT_STATE_CODE_INVALID_DC_SYNC         0x0030 /**< Invalid DC SYNC Configuration */
#define GOAL_ECAT_STATE_CODE_INVALID_DC_LATCH        0x0031 /**< Invalid DC Latch Configuration */
#define GOAL_ECAT_STATE_CODE_PLL_ERR                 0x0032 /**< PLL Error */
#define GOAL_ECAT_STATE_CODE_UNSYNCED_IO             0x0033 /**< DC Sync IO Error */
#define GOAL_ECAT_STATE_CODE_UNSYNCED                0x0034 /**< DC Sync Timeout Error */
#define GOAL_ECAT_STATE_CODE_INVALID_SYNC_CYCLE_TIME 0x0035 /**< DC Invalid Sync Cycle Time */
#define GOAL_ECAT_STATE_CODE_DC_SYNC_0_CYCLE_TIME    0x0036 /**< DC Sync0 Cycle Time */
#define GOAL_ECAT_STATE_CODE_DC_SYNC_1_CYCLE_TIME    0x0037 /**< DC Sync1 Cycle Time */
#define GOAL_ECAT_STATE_CODE_MBX_AOE                 0x0041 /**< MBX_AOE */
#define GOAL_ECAT_STATE_CODE_MBX_EOE                 0x0042 /**< MBX_EOE */
#define GOAL_ECAT_STATE_CODE_MBX_COE                 0x0043 /**< MBX_COE */
#define GOAL_ECAT_STATE_CODE_MBX_FOE                 0x0044 /**< MBX_FOE */
#define GOAL_ECAT_STATE_CODE_MBX_SOE                 0x0045 /**< MBX_SOE */
#define GOAL_ECAT_STATE_CODE_MBX_VOE                 0x004F /**< MBX_VOE */
#define GOAL_ECAT_STATE_CODE_EEPROM_NO_ACCESS        0x0050 /**< EEPROM no access */
#define GOAL_ECAT_STATE_CODE_EEPROM_ERR              0x0051 /**< EEPROM Error */
#define GOAL_ECAT_STATE_CODE_EXT_HW_ERR              0x0052 /**< External Hardware not ready */
#define GOAL_ECAT_STATE_CODE_RESTARTED               0x0060 /**< Slave restarted locally */
#define GOAL_ECAT_STATE_CODE_DEVICE_ID_UPDATE        0x0061 /**< Device Identification value updated */
#define GOAL_ECAT_STATE_CODE_MODULE_IDENT_MISMATCH   0x0070 /**< Detected Module Ident List does not match */
#define GOAL_ECAT_STATE_CODE_APP_AVAILABLE           0x00F0 /**< Application controller available */

/** EtherCAT State Machine states */
#define GOAL_ECAT_ESM_STATE_UNKNOWN   0         /**< unknown ESM state */
#define GOAL_ECAT_ESM_STATE_INIT      1         /**< ESM state INIT */
#define GOAL_ECAT_ESM_STATE_PREOP     2         /**< ESM state PreOP */
#define GOAL_ECAT_ESM_STATE_BOOTSTRAP 3         /**< ESM state BOOTSTRAP */
#define GOAL_ECAT_ESM_STATE_SAFEOP    4         /**< ESM state SafeOP */
#define GOAL_ECAT_ESM_STATE_OP        8         /**< ESM state OP */

/** FoE Error Codes */
#define GOAL_ECAT_FOE_ERR_NOT_DEFINED         0x8000 /**< unefined error */
#define GOAL_ECAT_FOE_ERR_NOT_FOUND           0x8001 /**< not found */
#define GOAL_ECAT_FOE_ERR_ACCESS_DENIED       0x8002 /**< access denied */
#define GOAL_ECAT_FOE_ERR_DISK_FULL           0x8003 /**< disk full */
#define GOAL_ECAT_FOE_ERR_ILLEGAL             0x8004 /**< illegal */
#define GOAL_ECAT_FOE_ERR_PACKET_NUMBER_WRONG 0x8005 /**< wrong packet number */
#define GOAL_ECAT_FOE_ERR_ALREADY_EXISTS      0x8006 /**< already exists */
#define GOAL_ECAT_FOE_ERR_NO_USER             0x8007 /**< no user */
#define GOAL_ECAT_FOE_ERR_BOOTSTRAP_ONLY      0x8008 /**< Bootstrap only */
#define GOAL_ECAT_FOE_ERR_NOT_BOOTSTRAP       0x8009 /**< not Bootstrap */
#define GOAL_ECAT_FOE_ERR_NO_RIGHTS           0x800A /**< no rights */
#define GOAL_ECAT_FOE_ERR_PROGRAM_ERROR       0x800B /**< programm error */
#define GOAL_ECAT_FOE_ERR_CSUM_WRONG          0x800C /**< checksum wrong */
#define GOAL_ECAT_FOE_ERR_FIRMWARE            0x800D /**< wrong firmware */
#define GOAL_ECAT_FOE_ERR_NO_FILE_TO_READ     0x800F /**< no file to read */
#define GOAL_ECAT_FOE_ERR_NO_HEADER           0x8010 /**< file header does not exist */
#define GOAL_ECAT_FOE_ERR_FLASH               0x8011 /**< flash error */
#define GOAL_ECAT_FOE_ERR_FILE_INCOMPATIBLE   0x800C /**< file incompatible */

/** FoE Busy status */
#define GOAL_ECAT_FOE_BUSY_STATE  0xC000        /**< Server is busy */

/** object dictionary object types */
#define GOAL_ECAT_OBJCODE_VAR    0x0007         /**< object is a variable object */
#define GOAL_ECAT_OBJCODE_ARRAY  0x0008         /**< object is an array object */
#define GOAL_ECAT_OBJCODE_RECORD 0x0009         /**< object is a record object */

/** object dictionary data types */
#define GOAL_ECAT_DATATYPE_UNKNOWN      0x0000  /**< data type: UNKNOWN */
#define GOAL_ECAT_DATATYPE_BOOL         0x0001  /**< data type: BOOL */
#define GOAL_ECAT_DATATYPE_INTEGER8     0x0002  /**< data type: INTEGER8 */
#define GOAL_ECAT_DATATYPE_INTEGER16    0x0003  /**< data type: INTEGER16 */
#define GOAL_ECAT_DATATYPE_INTEGER32    0x0004  /**< data type: INTEGER32 */
#define GOAL_ECAT_DATATYPE_UNSIGNED8    0x0005  /**< data type: UNSIGNED8 */
#define GOAL_ECAT_DATATYPE_UNSIGNED16   0x0006  /**< data type: UNSIGNED16 */
#define GOAL_ECAT_DATATYPE_UNSIGNED32   0x0007  /**< data type: UNSIGNED32 */
#define GOAL_ECAT_DATATYPE_REAL32       0x0008  /**< data type: REAL32 */
#define GOAL_ECAT_DATATYPE_VISSTRING    0x0009  /**< data type: VISSTRING */
#define GOAL_ECAT_DATATYPE_OCTETSTRING  0x000A  /**< data type: OCTETSTRING */
#define GOAL_ECAT_DATATYPE_REAL64       0x0011  /**< data type: REAL64 */
#define GOAL_ECAT_DATATYPE_INTEGER64    0x0015  /**< data type: INTEGER64 */
#define GOAL_ECAT_DATATYPE_UNSIGNED64   0x001B  /**< data type: UNSIGNED64 */
#define GOAL_ECAT_DATATYPE_BYTE         0x001E  /**< data type: BYTE */

/** access attributes of the objects */
#define EC_OBJATTR_RD_PREOP 0x0001              /**< readable in PreOP */
#define EC_OBJATTR_RD_SAFEOP 0x0002             /**< readable in SafeOP */
#define EC_OBJATTR_RD_OP 0x0004                 /**< readable in OP */
#define EC_OBJATTR_RD (EC_OBJATTR_RD_PREOP | EC_OBJATTR_RD_SAFEOP | EC_OBJATTR_RD_OP) /**< readable in all states */
#define EC_OBJATTR_WR_PREOP 0x0008              /**< writeable in PreOP */
#define EC_OBJATTR_WR_SAFEOP 0x0010             /**< writeable in SafeOP */
#define EC_OBJATTR_WR_OP 0x0020                 /**< writeable in OP */
#define EC_OBJATTR_WR (EC_OBJATTR_WR_PREOP | EC_OBJATTR_WR_SAFEOP | EC_OBJATTR_WR_OP) /**< writeable in all states */
#define EC_OBJATTR_RD_WR (EC_OBJATTR_RD | EC_OBJATTR_WR) /**< readable & writeable in all states */
#define EC_OBJATTR_NOPDOMAPPING 0x0000          /**< not mappable */
#define EC_OBJATTR_RXPDOMAPPING 0x0040          /**< mappable to RxPDOs */
#define EC_OBJATTR_TXPDOMAPPING 0x0080          /**< mappable to TxPDOs */
#define EC_OBJATTR_PDOMAPPING (EC_OBJATTR_RXPDOMAPPING | EC_OBJATTR_TXPDOMAPPING) /**< mappable to both */
#define EC_OBJATTR_BACKUP 0x0100                /**< backup flag */
#define EC_OBJATTR_SETTINGS 0x0200              /**< settings flag */
#define EC_OBJATTR_MAN 0x0400                   /**< internal: object category: mandatory */
#define EC_OBJATTR_OPT 0x0800                   /**< internal: object category: optional */
#define EC_OBJATTR_CON 0x0000                   /**< internal: object category: conditional */
#define EC_OBJATTR_NUMERIC 0x1000               /**< internal: numeric object value */
#define EC_OBJATTR_NO_DFLT 0x2000               /**< internal: object has no default value */
#define EC_OBJATTR_SHORT_ARRAY_DESC 0x4000      /**< internal: array elements all equal to subindex 1 */
#define EC_OBJATTR_NO_LIMITS 0x8000             /**< internal: object has no minimum and maximum limits */


/****************************************************************************/
/* Function and Parameter Mapping */
/****************************************************************************/
#define GOAL_ECAT_FUNC_CALLBACK 0               /**< callback function id */

/* callback function list */
#define GOAL_ECAT_FUNC_CB_LIST \
    /*                      id, name,                                       function */ \
    GOAL_ECAT_FUNC_CB_ENTRY(1, GOAL_ECAT_CB_ID_SDO_DOWNLOAD,             NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(2, GOAL_ECAT_CB_ID_SDO_UPLOAD,               NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(3, GOAL_ECAT_CB_ID_RxPDO_RECEIVED,           NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(4, GOAL_ECAT_CB_ID_TxPDO_PREPARE,            NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(5, GOAL_ECAT_CB_ID_SYNC_FAIL,                NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(6, GOAL_ECAT_CB_ID_NEW_DL_STATE,             NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(7, GOAL_ECAT_CB_ID_NEW_DC_CONFIG,            NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(8, GOAL_ECAT_CB_ID_DC_FAIL,                  NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(9, GOAL_ECAT_CB_ID_SM_WATCHDOG_EXPIRED,      NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(10, GOAL_ECAT_CB_ID_EXPLICIT_DEV_ID,         NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(11, GOAL_ECAT_CB_ID_NEW_ESM_STATE_ENTERED,   NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(12, GOAL_ECAT_CB_ID_NEW_ESM_STATE_REQUESTED, NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(13, GOAL_ECAT_CB_ID_FOE_READ_REQ,            NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(14, GOAL_ECAT_CB_ID_FOE_READ_DATA,           NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(15, GOAL_ECAT_CB_ID_FOE_WRITE_REQ,           NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(16, GOAL_ECAT_CB_ID_FOE_WRITE_DATA,          NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(17, GOAL_ECAT_CB_ID_FOE_ERROR,               NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(18, GOAL_ECAT_CB_ID_RUN_LED_STATE,           NULL), \
    GOAL_ECAT_FUNC_CB_ENTRY(19, GOAL_ECAT_CB_ID_ERROR_LED_STATE,         NULL)

/* create callback function id enum */
#undef GOAL_ECAT_FUNC_CB_ENTRY
#define GOAL_ECAT_FUNC_CB_ENTRY(id, name, ...) name = id
typedef enum {
    GOAL_ECAT_FUNC_CB_LIST
} GOAL_ECAT_FUNC_CB_ID_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_ecatInit(
    void
);

GOAL_STATUS_T goal_ecatNew(
    GOAL_ECAT_T **ppEcat,                       /**< [out] EtherCAT instance ref */
    const uint32_t id,                          /**< instance id */
    GOAL_ECAT_FUNC_CB_T pFunc                   /**< EtherCAT callback function */
);

GOAL_STATUS_T goal_ecatCfgEmergencyOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatCfgEmergencyQueueNum(
    int16_t num                                 /**< number of queue slots */
);

GOAL_STATUS_T goal_ecatCfgFoeOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatCfgExplDevIdOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatCfgBootstrapOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatCfgDcRequiredOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatCfgSizePdoStreamBufSet(
    uint16_t size                               /**< size of PDO stream buffer */
);

GOAL_STATUS_T goal_ecatCfgLedStatusIndicator(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
);

GOAL_STATUS_T goal_ecatObjAddrGet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint8_t **ppData,                           /**< [out] object data pointer reference */
    uint32_t *pSize                             /**< [out] object size reference */
);

GOAL_STATUS_T goal_ecatObjValGet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint8_t *pData,                             /**< [out] object data buffer */
    uint32_t *pSize                             /**< [out] object size reference */
);

GOAL_STATUS_T goal_ecatObjValSet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint8_t *pData,                             /**< [in] new object value */
    uint32_t size                               /**< size of new data */
);

GOAL_STATUS_T goal_ecatdynOdObjAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint16_t objTpye,                           /**< object type (VAR, ARRAY, RECORD) */
    uint16_t dataType                           /**< data type of object */
);

GOAL_STATUS_T goal_ecatdynOdSubIndexAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint16_t dataType,                          /**< data type of object */
    uint16_t attr,                              /**< attributes (R/W/mappable,...) */
    uint8_t *pDefVal,                           /**< default value of entry */
    uint8_t *pMinVal,                           /**< minimum value of entry */
    uint8_t *pMaxVal,                           /**< maximum value of entry */
    uint32_t size,                              /**< size of non-numerical objects */
    uint8_t *pData                              /**< pointer to variable or NULL */
);


GOAL_STATUS_T goal_ecatdynOdSubIndexDmAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint16_t dataType,                          /**< data type of object */
    uint16_t attr,                              /**< attributes (R/W/mappable,...) */
    uint8_t *pDefVal,                           /**< default value of entry */
    uint8_t *pMinVal,                           /**< minimum value of entry */
    uint8_t *pMaxVal,                           /**< maximum value of entry */
    uint32_t size,                              /**< size of non-numerical objects */
    uint8_t *pData                              /**< pointer to variable or NULL */
);

GOAL_STATUS_T goal_ecatdynOdSubIndexRpcAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint16_t dataType,                          /**< data type of object */
    uint16_t attr,                              /**< attributes (R/W/mappable,...) */
    uint8_t *pDefVal,                           /**< default value of entry */
    uint8_t *pMinVal,                           /**< minimum value of entry */
    uint8_t *pMaxVal,                           /**< maximum value of entry */
    uint32_t size                               /**< size of non-numerical objects */
);

GOAL_STATUS_T goal_ecatdynOdObjNameAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    char *pName                                 /**< name of object */
);

GOAL_STATUS_T goal_ecatdynOdSubIndexNameAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    char *pName                                 /**< name of sub-index */
);

GOAL_STATUS_T goal_ecatdynOdFinish(
    GOAL_ECAT_T *pEcat                          /**< EtherCAT instance data */
);

GOAL_STATUS_T goal_ecatEsmStateGet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint8_t *pState                             /**< [out] EtherCAT state */
);

GOAL_STATUS_T goal_ecatEmcyReqWrite(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t errorCode,                         /**< standard error code */
    uint8_t *pManuErr                           /**< manufacturer error code */
);

GOAL_STATUS_T goal_ecatGetVersion(
    char *strVersion,                           /**< [out] stack version */
    int size                                    /**< buffer size */
);

GOAL_STATUS_T goal_ecatDmDpAdd(
    GOAL_ECAT_T *pEcat,                         /**< GOAL EtherCAT handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDp                /**< [out] partition for data provider status */
);

#endif /* GOAL_ECAT_RPC_Ac_H_ */
