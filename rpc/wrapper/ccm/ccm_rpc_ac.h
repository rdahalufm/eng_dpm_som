/** @file
 *
 * @brief  CTC wrapper for net
 *
 * @details
 * This module provides a MA for networking over CTC
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef APPL_CCM_RPC_AC_H_
#define APPL_CCM_RPC_AC_H_

#include "ccm_rpc.h"


/****************************************************************************/
/* Configuration */
/****************************************************************************/
#define APPL_CCM_RPC_BUF_SIZE 1000


/****************************************************************************/
/* Compatibilty to API changes */
/****************************************************************************/
#define appl_ccmFwUpdateAllow appl_ccmUpdateAllow


/****************************************************************************/
/* Type definitions*/
/****************************************************************************/
typedef enum {
    FW_UPDATE_IDLE,                             /**< no firmware update in progress */
    FW_UPDATE_TRANSFER_INIT,                    /**< transfer of firmware to CC started */
    FW_UPDATE_TRANSFER,                         /**< transfer of firmware to CC in progress */
    FW_UPDATE_TRANSFER_DONE,                    /**< transfer of firmware to CC done */
    FW_UPDATE_ABORT,                            /**< firmware update aborted */
    FW_UPDATE_COMMIT_PENDING,                   /**< firmware update commit pending */
    FW_UPDATE_COMMIT_DONE                       /**< firware update commit done */
} FW_UPDATE_STATUS_T;

typedef enum {
    FW_UPDATE_SOURCE_RPC,                       /**< firmware update from AC */
    FW_UPDATE_SOURCE_HTTP,                      /**< firmware update via web server */
    FW_UPDATE_SOURCE_FOE                        /**< firmware update via EtherCAT foe */
} FW_UPDATE_SOURCE_T;

typedef void (*APPL_CCM_FW_UPDATE_CB_T)(
    FW_UPDATE_SOURCE_T source,                  /**< remote update source */
    FW_UPDATE_STATUS_T status,                  /**< remote update status */
    uint8_t progress                            /**< remote update progress */
);


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T appl_ccmRpcInit(
    void
);

GOAL_STATUS_T appl_ccmUpdateAllow(
    void
);

GOAL_STATUS_T appl_ccmUpdateDeny(
    void
);

GOAL_STATUS_T appl_ccmInfo(
    char *strVersion,                           /**< target string for version */
    uint8_t lenStrVersion,                      /**< length of str buffer */
    GOAL_ETH_MAC_ADDR_T *macAddress,            /**< mac address buffer */
    uint16_t *pDevType                          /**< CCM device type */
);

#if defined(GOAL_CONFIG_LM)
GOAL_STATUS_T appl_ccmLogEnable(
    void
);
#endif

GOAL_STATUS_T appl_ccmFaultStateSet(
    APPL_CCM_FAULT_STATE_T faultState         /**< fault state to enter */
);

GOAL_STATUS_T appl_ccmCommResetSet(
    uint8_t value                               /**< option value */
);

#if defined(GOAL_CONFIG_LM)
GOAL_STATUS_T appl_ccmLogToAcEnable(
    void
);
#endif

GOAL_STATUS_T appl_ccmFwUpdateStart(
    uint8_t *pFwData,                           /**< firmware data */
    uint32_t fwSize                             /**< size of firmware data */
);

GOAL_STATUS_T appl_ccmFwUpdateExecute(
    void
);

GOAL_STATUS_T appl_ccmFoeUpdateSettings(
    char *strName,                              /**< foe firmware filename */
    uint8_t matchLength,                        /**< string match length */
    uint32_t password,                          /**< foe password */
    GOAL_BOOL_T flgBootstrapReq                 /**< bootstrap required */
);

GOAL_STATUS_T appl_ccmEcatSsiUpdate(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    GOAL_BOOL_T flgEmptyCheck                   /**< empty check before writing */
);

GOAL_STATUS_T appl_ccmCfgSsiVendorId(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t vendorId                           /**< vendor id */
);

GOAL_STATUS_T appl_ccmCfgSsiProductCode(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t productCode                        /**< product code */
);

GOAL_STATUS_T appl_ccmCfgSsiRevisionNumber(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t revisionNumber                     /**< revision number */
);

GOAL_STATUS_T  appl_ccmCfgSsiSerialNumber(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t serialNumber                       /**< serial number */
);

GOAL_STATUS_T appl_ccmCfgSsiProductType(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strProductType                        /**< vendor name */
);

GOAL_STATUS_T appl_ccmCfgSsiProductName(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strProductName                        /**< vendor name */
);

GOAL_STATUS_T appl_ccmCfgSsiOrderId(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strOrderId                            /**< order id */
);

GOAL_STATUS_T appl_ccmFwUpdateCbReg(
    APPL_CCM_FW_UPDATE_CB_T pFunc               /**< fw update callback */
);

GOAL_STATUS_T appl_ccmFwUpdateStateGet(
    FW_UPDATE_STATUS_T *pState                  /**< [out] status */
);

GOAL_STATUS_T appl_ccmNetworkDefaultUp(
    void
);

GOAL_STATUS_T appl_ccmNetworkEoEUp(
    void
);

GOAL_STATUS_T appl_ccmEthMacAddressSet(
    uint8_t *pMacAddr
);

GOAL_STATUS_T appl_ccmCfgVarGet(
    uint32_t modId,                             /**< module id */
    uint32_t varId,                             /**< variable id */
    void *pBuf,                                 /**< [out] output buffer */
    uint32_t bufLength,                         /**< buffer length */
    uint32_t *pVarLength,                       /**< [out] variable length */
    uint32_t *pVarType                          /**< [out] variable type */
);

GOAL_STATUS_T appl_ccmCfgVarSet(
    uint32_t modId,                             /**< module id */
    uint32_t varId,                             /**< variable id */
    void *pBuf,                                 /**< [out] output buffer */
    uint32_t bufLength                          /**< buffer length */
);

GOAL_STATUS_T appl_ccmCfgSave(
    void
);

#endif /* APPL_CCM_RPC_AC_H_ */
