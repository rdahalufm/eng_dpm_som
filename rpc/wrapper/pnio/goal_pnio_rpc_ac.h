/** @file
 *
 * @brief
 * GOAL PROFINET AC Adapter
 *
 * @details
 * Provides the GOAL PROFINET API over CTC RPC.
 *
 * @copyright
 * Copyright 2010-2018 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_PNIO_RPC_AC_H
#define GOAL_PNIO_RPC_AC_H

#include <goal_pnio_rpc.h>
#include <goal_media/goal_mi_dm.h>


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_pnioInitAc(
    void
);

GOAL_STATUS_T goal_pnioNewAc(
    struct GOAL_PNIO_T **ppPnio,                /**< PROFINET handle ref */
    const uint32_t id,                          /**< instance id */
    GOAL_PNIO_FUNC_CB_T pFunc                   /**< PROFINET callback function */
);

GOAL_STATUS_T goal_pnioSlotNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioSubslotNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioModNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod                              /**< module id */
);

GOAL_STATUS_T goal_pnioSubmodNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod,                          /**< submodule id */
    GOAL_PNIO_MOD_TYPE_T type,                  /**< submodule type */
    uint16_t sizeInput,                         /**< input size */
    uint16_t sizeOutput,                        /**< output size */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioModPlugAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint32_t idMod                              /**< module id */
);

GOAL_STATUS_T goal_pnioSubmodPlugAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
);

GOAL_STATUS_T goal_pnioModPullAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot                             /**< slot */
);

GOAL_STATUS_T goal_pnioSubmodPullAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
);

GOAL_STATUS_T goal_pnioDataOutputGetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    char *pBuf,                                 /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T *pStateIops                /**< producer state */
);

GOAL_STATUS_T goal_pnioDataInputSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    char *pBuf,                                 /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T stateIops                  /**< producer state */
);

GOAL_STATUS_T goal_pnioApduStatusGetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    GOAL_PNIO_APDU_STATUS_T *pStatusApdu        /**< APDU status */
);

GOAL_STATUS_T goal_pnioAlarmNotifySendAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t *pNrAlarmSeq,                      /**< sequence nr ref */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
);

GOAL_STATUS_T goal_pnioAlarmNotifySendAckAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    GOAL_PNIO_STATUS_T *pStatus,                /**< PROFINET status */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
);

GOAL_STATUS_T goal_pnioAlarmProcessSendAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
);

GOAL_STATUS_T goal_pnioRecReadFinishAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PROFINET status */
    const uint8_t *pData,                       /**< record data */
    uint16_t len,                               /**< record data length */
    uint32_t numSeq                             /**< sequence number */
);

GOAL_STATUS_T goal_pnioRecWriteFinishAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PROFINET status */
    uint32_t numSeq                             /**< sequence number */
);

GOAL_STATUS_T goal_pnioDiagExtChanDiagAddAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T *pHdl,              /**< handle ptr */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t chan,                              /**< channel number */
    uint16_t numErr,                            /**< error number */
    uint16_t typeExtChanErr,                    /**< extended channel error type */
    uint32_t valExtChanAdd,                     /**< extended channel error value */
    GOAL_BOOL_T flgMaintReq,                    /**< maintainance required flag */
    GOAL_BOOL_T flgMaintDem,                    /**< maintainance demanded flag */
    GOAL_BOOL_T flgSubmitAlarm,                 /**< submit alarm flag */
    uint16_t typeAlarm                          /**< alarm type */
);

GOAL_STATUS_T goal_pnioDiagChanDiagRemoveAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T hdl,                /**< diagnosis handle */
    GOAL_BOOL_T flgSubmitAlarm                  /**< submit alarm flag */
);

GOAL_STATUS_T goal_pnioCyclicCtrlAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_BOOL_T flgCyclic                       /**< cyclic data enable flag */
);

GOAL_STATUS_T goal_pnioVendorIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< vendor id */
);

GOAL_STATUS_T goal_pnioDeviceIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< device id */
);

GOAL_STATUS_T goal_pnioDeviceNameSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    char *strName,                              /**< device name */
    uint32_t lenName,                           /**< device name length */
    GOAL_BOOL_T flgPerm,                        /**< permanent flag */
    GOAL_BOOL_T flgCb                           /**< run-callback flag */
);

GOAL_STATUS_T goal_pnioHwRevSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t revHw                              /**< hardware revision */
);

GOAL_STATUS_T goal_pnioSwRevSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint8_t chrPrefix,                          /**< prefix */
    uint8_t idFuncEnh,                          /**< functional enhancement */
    uint8_t idBugfix,                           /**< bugfix */
    uint8_t idIntChange,                        /**< internal change */
    uint16_t cntRev                             /**< revision counter */
);

GOAL_STATUS_T goal_pnioProfileIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id,                                /**< profile id */
    uint16_t type                               /**< profile specific type */
);

GOAL_STATUS_T goal_pnioOrderIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strOrder,                       /**< order id */
    uint32_t lenOrder                           /**< order id length */
);

GOAL_STATUS_T goal_pnioSerialNumSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSerial,                      /**< serial number */
    uint32_t lenSerial                          /**< serial number length */
);

GOAL_STATUS_T goal_pnioVendorNameSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strVendor,                      /**< vendor name */
    uint32_t lenVendor                          /**< vendor name length */
);

GOAL_STATUS_T goal_pnioPortDescSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strPort,                        /**< port description */
    uint32_t lenPort                            /**< port description length */
);

GOAL_STATUS_T goal_pnioSystemDescSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSys,                         /**< system description */
    uint32_t lenSys                             /**< system description length */
);

GOAL_STATUS_T goal_pnioCfgDcpFactoryResetDisableSetAc(
    GOAL_BOOL_T flgDcpFactoryResetDisable       /**< DCP Factory Reset Disable */
);

GOAL_STATUS_T goal_pnioCfgDcpAcceptMixcaseStationSetAc(
    GOAL_BOOL_T flgDcpAcceptMixcaseStation      /**< DCP Accept Mixcase Stationname */
);

GOAL_STATUS_T goal_pnioCfgVendorIdSetAc(
    uint16_t idVendor                           /**< Vendor Id */
);

GOAL_STATUS_T goal_pnioCfgDeviceIdSetAc(
    uint16_t idDevice                           /**< Device Id */
);

GOAL_STATUS_T goal_pnioCfgVendorNameSetAc(
    const char *strVendor                       /**< Vendor Name */
);

GOAL_STATUS_T goal_pnioCfgPortNameSetAc(
    const char *strPort                         /**< Port Name */
);

GOAL_STATUS_T goal_pnioCfgSystemDescSetAc(
    const char *strSystem                       /**< System Description */
);

GOAL_STATUS_T goal_pnioCfgOrderIdSetAc(
    const char *strIdOrder                      /**< Order Id */
);

GOAL_STATUS_T goal_pnioCfgSerialNumSetAc(
    const char *strNumSerial                    /**< Serial Number */
);

GOAL_STATUS_T goal_pnioCfgHwRevSetAc(
    uint16_t idRevHw                            /**< Hardware Revision */
);

GOAL_STATUS_T goal_pnioCfgSwRevPrefixSetAc(
    const char chrRevSwPrefix                   /**< Software Revision Prefix */
);

GOAL_STATUS_T goal_pnioCfgSwRevFuncEnhSetAc(
    uint8_t idRevSwFuncEnh                      /**< Software Revision Functional Enhancement */
);

GOAL_STATUS_T goal_pnioCfgSwRevBugfixSetAc(
    uint8_t idRevSwBugfix                       /**< Software Revision Bugfix */
);

GOAL_STATUS_T goal_pnioCfgSwRevIntChgSetAc(
    uint8_t idRevSwIntChg                       /**< Software Revision Internal Change */
);

GOAL_STATUS_T goal_pnioCfgSwRevCntSetAc(
    uint8_t idRevSwRevCnt                       /**< Software Revision Count */
);

GOAL_STATUS_T goal_pnioCfgIm1TagFuncSetAc(
    const char *strIm1TagFunc                   /**< I&M1 Tag Function */
);

GOAL_STATUS_T goal_pnioCfgIm1TagLocSetAc(
    const char *strIm1TagLoc                    /**< I&M1 Tag Location */
);

GOAL_STATUS_T goal_pnioCfgIm2DateSetAc(
    const char *strIm2Date                      /**< I&M2 Date */
);

GOAL_STATUS_T goal_pnioCfgIm3DescSetAc(
    const char *strIm3Desc                      /**< I&M3 Descriptor */
);

GOAL_STATUS_T goal_pnioCfgIm4SigSetAc(
    const char *strIm4Sig                       /**< I&M4 Signature */
);

GOAL_STATUS_T goal_pnioCfgDevDapSimpleSetAc(
    GOAL_BOOL_T flgDevDapSimple                 /**< Device DAP Simple Mode */
);

GOAL_STATUS_T goal_pnioCfgDevDapApiSetAc(
    uint32_t idDevDapApi                        /**< Device DAP API */
);

GOAL_STATUS_T goal_pnioCfgDevDapSlotSetAc(
    uint16_t idDevDapSlot                       /**< Device DAP Slot */
);

GOAL_STATUS_T goal_pnioCfgDevDapSubslotSetAc(
    uint16_t idDevDapSubslot                    /**< Device DAP Subslot */
);

GOAL_STATUS_T goal_pnioCfgDevDapModuleSetAc(
    uint32_t idDevDapMod                        /**< Device DAP Module */
);

GOAL_STATUS_T goal_pnioCfgDevDapSubmoduleSetAc(
    uint32_t idDevDapSubmod                     /**< Device DAP Submodule */
);

GOAL_STATUS_T goal_pnioCfgNetLinkSafetySetAc(
    GOAL_BOOL_T flgNetLinkSafety                /**< Net Link Safety */
);

GOAL_STATUS_T goal_pnioCfgNewIoDataCbSetAc(
    GOAL_BOOL_T flgCbNewIoData                  /**< New IO Data Callback Enable */
);

GOAL_STATUS_T goal_pnioCfgLldpOrgExtSetAc(
    GOAL_BOOL_T flgLldpOrgExt                   /**< LLDP Org Ext */
);

GOAL_STATUS_T goal_pnioCfgLldpOptTlvSetAc(
    GOAL_BOOL_T flgLldpOptTlv                   /**< LLDP Optional TLVs */
);

GOAL_STATUS_T goal_pnioCfgLldpGenMacSetAc(
    GOAL_BOOL_T flgLldpGenMac                   /**< LLDP Generate Port MAC Addresses */
);

GOAL_STATUS_T goal_pnioCfgIm14SupportSetAc(
    GOAL_BOOL_T flgIm14Support                  /**< I&M 1-4 Support */
);

GOAL_STATUS_T goal_pnioCfgIm14CbSetAc(
    GOAL_BOOL_T flgIm14Cb                       /**< I&M 1-4 Callback */
);

GOAL_STATUS_T goal_pnioCfgIm0CbSetAc(
    GOAL_BOOL_T flgIm0Cb                        /**< I&M 0 Callback */
);

GOAL_STATUS_T goal_pnioCfgIm0FilterDataCbSetAc(
    GOAL_BOOL_T flgIm0FilterCb                  /**< I&M 0 FilterData Callback */
);

GOAL_STATUS_T goal_pnioCfgRecDataBusyBufsizeSetAc(
    unsigned int cntRecDataBusyBufsize          /**< Record Data Storage Size */
);

GOAL_STATUS_T goal_pnioCfgRpcFragReqLenMaxSetAc(
    unsigned int sizeRpcFragMaxReqLen           /**< RPC Fragmentation Maximum Request Length */
);

GOAL_STATUS_T goal_pnioCfgRpcFragMaxCntSetAc(
    unsigned int numRpcFragMax                  /**< RPC Maximum Fragment Count */
);

GOAL_STATUS_T goal_pnioCfgRpcFragEnableSetAc(
    GOAL_BOOL_T flgRpcFragSupport               /**< RPC Fragmentation Support Enable */
);

GOAL_STATUS_T goal_pnioCfgRpcSessionMaxCntSetAc(
    unsigned int numRpcSessions                 /**< RPC Session Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgDiagBufMaxCntSetAc(
    unsigned int numDiagBufMax                  /**< Diagnosis Maximum Buffer Count */
);

GOAL_STATUS_T goal_pnioCfgDiagBufMaxDataSizeSetAc(
    unsigned int numDiagDataSizeMax             /**< Diagnosis Maximum Data Size */
);

GOAL_STATUS_T goal_pnioCfgIocrBlocksMaxSetAc(
    unsigned int numIocrBlocksMax               /**< IOCR Maximum Blocks */
);

GOAL_STATUS_T goal_pnioCfgCrMaxCntSetAc(
    unsigned int numCrMax                       /**< Communication Relation Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgArMaxCntSetAc(
    unsigned int numArMax                       /**< Application Relation Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgApiMaxCntSetAc(
    unsigned int numApiMax                      /**< API Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSlotMaxCntSetAc(
    unsigned int numSlotMax                     /**< Slot Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSubslotMaxCntSetAc(
    unsigned int numSubslotMax                  /**< Subslot Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSubslotIfSetAc(
    uint16_t idSubslotIf                        /**< interface subslot */
);

GOAL_STATUS_T goal_pnioCfgSubslotPortSetAc(
    uint16_t idSubslotPort                      /**< port subslot */
);

GOAL_STATUS_T goal_pnioCfgSnmpIdSetAc(
    uint32_t idSnmp                             /**< SNMP id */
);

GOAL_STATUS_T goal_pnioCfgNumProcAlBufSetAc(
    uint8_t numProcAlBuf                        /**< Number of slots in Process alarm queue */
);

GOAL_STATUS_T goal_pnioCfgFlgMrpCfgSetAc(
    GOAL_BOOL_T flgMrpCfg                       /**< MRP config flag */
);

GOAL_STATUS_T goal_pnioDmSubmodPlug(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
);

GOAL_STATUS_T goal_pnioDmSubslotAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmOut,                         /**< MI DM output handle */
    uint32_t idMiDmIn,                          /**< MI DM input handle */
    GOAL_MI_DM_PART_T **ppPartDataOut,          /**< [out] partition for output data */
    GOAL_MI_DM_PART_T **ppPartDataIn,           /**< [out] partition for input data */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t lenDataOut,                        /**< output data length */
    uint32_t lenDataIn                          /**< input data length */
);

GOAL_STATUS_T goal_pnioDmSubslotIoxsAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmOut,                         /**< MI DM output handle */
    uint32_t idMiDmIn,                          /**< MI DM input handle */
    GOAL_MI_DM_PART_T **ppPartIocsOut,          /**< [out] partition for output IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsOut,          /**< [out] partition for output IOPS */
    GOAL_MI_DM_PART_T **ppPartIocsIn,           /**< [out] partition for input IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsIn,           /**< [out] partition for input IOPS */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
);

GOAL_STATUS_T goal_pnioDmApduAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmOut,                         /**< MI DM output handle */
    GOAL_MI_DM_PART_T **ppPartApduOut           /**< [out] partition for output APDU data */
);

GOAL_STATUS_T goal_pnioDmDpAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmOut,                         /**< MI DM output handle */
    GOAL_MI_DM_PART_T **ppPartDp                /**< [out] partition for data provider status */
);

GOAL_STATUS_T goal_pnioDmResetAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET instance */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueInitAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueAddAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueSendAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueResetAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioConnReqProcessAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

#endif /* GOAL_PNIO_RPC_AC_H */
