/** @file
 *
 * @brief  CTC wrapper for CCM RPC functions
 *
 * @details
 * This module provides a CTC wrapper for CCM specific functions
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_ID GOAL_ID_CCM


/****************************************************************************/
/* Includes */
/****************************************************************************/
#include <goal_includes.h>

#include "ccm_rpc_ac.h"
#include "ccm_rpc.h"

#include <goal_media/goal_mi_mctc.h>


/****************************************************************************/
/* Local type definitions */
/****************************************************************************/

/**< EtherCAT SSI header */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct ECAT_SSI_T {
    uint16_t pdiControl_le16;                   /**< PDI control */
    uint16_t pdiConfig_le16;                    /* PDI configuration */
    uint16_t syncImpulsLength_le16;             /* Sync impulse length */
    uint16_t pdiControl2_le16;                  /* PDI configuration 2 */
    uint16_t stationAlias_le16;                 /* Configured station alias */
    uint32_t reserved_4;                        /* Reserved[4] */
    uint16_t crc_le16;                          /* Checksum */
    uint32_t vendorId_le32;                     /* Vendor id */
    uint32_t productCode_le32;                  /* Product code */
    uint32_t revisionNumber_le32;               /* Revision number */
    uint32_t serialNumber_le32;                 /* Serial number */
    uint64_t reserved_8;                        /* Reserved[8] */
    uint16_t bootRecvMboxOffset_le16;           /* Bootstrap receive mailbox offset */
    uint16_t bootRecvMboxSize_le16;             /* Bootstrap receive mailbox size */
    uint16_t bootSendMboxOffset_le16;           /* Bootstrap send mailbox offset */
    uint16_t bootSendMboxSize_le16;             /* Bootstrap send mailbox size */
    uint16_t stdRecvMboxOffset_le16;            /* Standard receive mailbox offset */
    uint16_t stdRecvMboxSize_le16;              /* Standard receive mailbox size */
    uint16_t stdSendMboxOffset_le16;            /* Standard send mailbox offset */
    uint16_t stdSendMboxSize_le16;              /* Standard send mailbox size */
    uint16_t mboxProtocol_le16;                 /* Mailbox protocol */
    uint8_t reserved_66[66];                    /* Reserved[66] */
    uint16_t eepromSize_le16;                   /* EEPROM size */
    uint16_t eepromVersion_le16;                /* Version */
} GOAL_TARGET_PACKED ECAT_SSI_T;
GOAL_TARGET_PACKED_STRUCT_POST


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_MEM_DENY_HANDLE_T hdlMemDeny;       /**< memory deny delay handle */
static GOAL_STAGE_HANDLER_T stageInit;          /**< init stage handler */

static GOAL_RPC_HDL_CHN_T *pHdlRpcChn = GOAL_RPC_HDL_NONE; /**< acyclic transmission handle */

#if defined(GOAL_CONFIG_LM)
static GOAL_LM_READER_T *pReaderRpc;            /**< logging reader */
static GOAL_BOOL_T flgLogAvailable = GOAL_FALSE;/**< update flag to signal new data */
static uint8_t *pLogBuf = NULL;                 /**< message buffer */
static GOAL_BOOL_T flgEnable = GOAL_FALSE;      /**< enable flag */
#endif

static FW_UPDATE_STATUS_T fwUpdateStatus;       /**< fw update status */
static uint32_t fwUpdatePos;                    /**< fw update position */
static uint32_t fwUpdateSize;                   /**< fw update size */
static uint8_t *pFwData;                        /**< fw update data */

static APPL_CCM_FW_UPDATE_CB_T pFwUpdateCbFunc; /**< fw update callback */


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
static GOAL_STATUS_T appl_ccmRpcPastInit(
    void
);

static GOAL_STATUS_T appl_ccmRpcSetupChannels(
    void
);


#if defined(GOAL_CONFIG_LM)
static void appl_ccmRpcLoop(
    void
);
#endif

static void appl_ccmRpcFwLoop(
    void
);

#if defined(GOAL_CONFIG_LM)
GOAL_STATUS_T appl_ccmMsgFlag(
    GOAL_LM_LOG_ENTRY_T *pLmEntry               /**< log message */
);

static GOAL_STATUS_T appl_ccmReaderCb(
    struct GOAL_LM_READER_T *pHdlReader         /**< reader handle */
);

static GOAL_STATUS_T appl_irj45LogToAcServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
);
#endif

static GOAL_STATUS_T replaceString(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI dara length */
    uint8_t skipStrings,                        /**< strings to skip */
    char *strData                               /**< new string */
);

static GOAL_STATUS_T appl_ccmFwUpdateStatusServer(
     GOAL_RPC_HDL_T *pHdlRpc                    /**< rpc handle */
);


/****************************************************************************/
/** RPC initialization
 *
 * This function initialize all necessary function to use ccm via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmRpcInit(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* request memory deny delay handle */
    res = goal_memDenyDelayHandleGet(&hdlMemDeny);

    /* set  the size of the RPC stack */
    if (GOAL_RES_OK(res)) {
        res = goal_rpcSetStackMax(RPC_BUFF_SIZE_CCM);
    }

    /* register the rpc past init function */
    if (GOAL_RES_OK(res)) {
        res = goal_mainStageReg(GOAL_STAGE_MODULES, &stageInit, GOAL_STAGE_INIT, appl_ccmRpcPastInit);
    }

    return res;
}


/****************************************************************************/
/** NET via RPC past initialization
 *
 * This function is called during the init stage of the GOAL_STAGE_CTC_PRE.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T appl_ccmRpcPastInit(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* setup all necessary RPC channels */
    if (GOAL_RES_OK(res)) {
        res = appl_ccmRpcSetupChannels();
    }

    /* register the loop function */
    if (GOAL_RES_OK(res)) {
        res = goal_mainLoopReg(appl_ccmRpcFwLoop);
    }

    return res;
}


/****************************************************************************/
/** Setup channels for NET via RPC
 *
 * This function initialize the ctc channels for RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T appl_ccmRpcSetupChannels(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* setup a channel for RPC */
    res = goal_rpcSetupChannel(&pHdlRpcChn, GOAL_ID_MI_CTC_DEFAULT);

#if defined(GOAL_CONFIG_LM)
    if (GOAL_RES_OK(res)) {
        res = goal_rpcRegisterService(GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_LOG, &appl_irj45LogToAcServer);
    }
#endif

    if (GOAL_RES_OK(res)) {
        res = goal_rpcRegisterService(GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_STATUS, &appl_ccmFwUpdateStatusServer);
    }

    return res;
}


#if defined(GOAL_CONFIG_LM)
/****************************************************************************/
/** Loop function to update logging buffer on CC
 *
 * This function is called cyclic.
 */
static void appl_ccmRpcLoop(
    void
)
{
    static GOAL_BOOL_T flgInit = GOAL_FALSE;    /* flag to initialize read pos */
    GOAL_STATUS_T res;                          /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    uint16_t len = 0;                           /* message len */

    if (GOAL_FALSE == flgInit) {
        /* wait until RPC is initialized */
        res = goal_rpcStatus(GOAL_ID_MI_CTC_DEFAULT);
        if (GOAL_RES_ERR(res)) {
            return;
        }
        else {
            flgInit = GOAL_TRUE;
        }
    }

    /* do not proceed if buffer is not allocated */
    if (NULL == pLogBuf) {
        return;
    }

    if (flgLogAvailable == GOAL_TRUE) {

        res = goal_lmBufferMsgGet(pReaderRpc, pLogBuf, APPL_CCM_RPC_BUF_SIZE, &len);
        if (GOAL_RES_ERR(res)) {
            flgLogAvailable = GOAL_FALSE;
        }

        if (GOAL_RES_OK(res)) {
            appl_ccmMsgFlag((GOAL_LM_LOG_ENTRY_T *) pLogBuf);

            if (GOAL_RES_OK(res)) {
                GOAL_RPC_NEW();

                /* push the data to the stack */
                if (GOAL_RES_OK(res)) {
                    res = goal_rpcArgPush(pHdlRpc, pLogBuf, (uint16_t) len);
                }

                /* push the data length to the stack */
                GOAL_RPC_PUSH(len);

                if (GOAL_RES_OK(res)) {
                    res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_LOG);
                }

                GOAL_RPC_CLOSE();
            }
        }
    }
}
#endif


/****************************************************************************/
/** Loop function to update logging buffer on CC
 *
 * This function is called cyclic.
 */
static void appl_ccmRpcFwLoop(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    uint32_t pushSize;                          /* amount of data to push */

    if (fwUpdateStatus == FW_UPDATE_TRANSFER) {

        GOAL_RPC_NEW();

        pushSize = 1024;

        /* handle last fragment */
        if (fwUpdatePos + pushSize > fwUpdateSize) {
            /* limit popSize to actual remaining data */
            pushSize = fwUpdateSize - fwUpdatePos;
        }

        if (GOAL_RES_OK(res)) {
            res = goal_rpcArgPush(pHdlRpc, &pFwData[fwUpdatePos], pushSize);
        }

        if (GOAL_RES_OK(res)) {
            res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_DATA);
        }

        /* increment position in data stream */
        if (GOAL_RES_OK(res)) {

            /* check if all data has been transfered */
            if (fwUpdatePos >= fwUpdateSize) {
                fwUpdateStatus = FW_UPDATE_TRANSFER_DONE;
            }

            fwUpdatePos += pushSize;
        }
        else {
            fwUpdateStatus = FW_UPDATE_ABORT;
        }

        GOAL_RPC_CLOSE();
    }
}


#if defined(GOAL_CONFIG_LM)
/****************************************************************************/
/** set flag in logging message to identify AC log messages
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmMsgFlag(
    GOAL_LM_LOG_ENTRY_T *pLmEntry               /**< log message */
)
{
    pLmEntry->flags |= GOAL_LM_FLAG_EXT;
    return GOAL_OK;
}


/****************************************************************************/
/** LM reader callback function
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T appl_ccmReaderCb(
    struct GOAL_LM_READER_T *pHdlReader         /**< reader handle */
)
{
    UNUSEDARG(pHdlReader);

    flgLogAvailable = GOAL_TRUE;

    return GOAL_OK;
}
#endif


/****************************************************************************/
/** enable potential firmware update
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmUpdateAllow(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_ALLOW);
    }

    GOAL_RPC_CLOSE();

    if (GOAL_RES_OK(res)) {
        goal_logInfo("allowing firmware update on CC succeeded");
    } else {
        goal_logInfo("allowing firmware update on CC failed");
    }

    return res;
}


/****************************************************************************/
/** forbid potential firmware update
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmUpdateDeny(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_DENY);
    }

    GOAL_RPC_CLOSE();

    if (GOAL_RES_OK(res)) {
        goal_logInfo("denying firmware update on CC succeeded");
    } else {
        goal_logInfo("denying firmware update on CC failed");
    }

    return res;
}


/****************************************************************************/
/** get information of ccm
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmInfo(
    char *strVersion,                           /**< target string for version */
    uint8_t lenStrVersion,                      /**< length of str buffer */
    GOAL_ETH_MAC_ADDR_T *macAddress,            /**< mac address buffer */
    uint16_t *pDevType                          /**< CCM device type */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint8_t lenStr = 0;                         /* string length */
    uint16_t deviceType = 0;                    /* device type */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_INFO);
    }

    /* pop device type */
    GOAL_RPC_POP(deviceType, uint16_t);
    *pDevType = deviceType;

    /* pop mac address */
    GOAL_RPC_POP_PTR(macAddress, MAC_ADDR_LEN);

    /* pop version string */
    GOAL_RPC_POP(lenStr, uint8_t);
    if (lenStr > lenStrVersion) {
        lenStr = lenStrVersion;
    }
    GOAL_RPC_POP_PTR(strVersion, lenStr);

    /* finish string */
    strVersion[lenStr] = '\0';

    GOAL_RPC_CLOSE();

    return res;
}


#if defined(GOAL_CONFIG_LM)
/****************************************************************************/
/** enable transmission of log message from local logging buffer to CC
 *
 * by enabling, log messages from the AC are visible in the logging buffer
 * of the CC module ( -> management tool)
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmLogEnable(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* don't run twice */
    if (GOAL_TRUE == flgEnable) {
        return GOAL_OK;
    }

    res = goal_lmReaderReg(&pReaderRpc, appl_ccmReaderCb);

#if GOAL_CONFIG_LM == 1
    /* register the loop function */
    if (GOAL_RES_OK(res)) {
        res = goal_mainLoopReg(appl_ccmRpcLoop);
    }
#endif

    /* get memory buffers */
    if (GOAL_RES_OK(res)) {
        pLogBuf = NULL;
        res = goal_memCalloc(&pLogBuf, APPL_CCM_RPC_BUF_SIZE);
    }

    flgEnable = GOAL_TRUE;

    return res;
}


#if defined(GOAL_CONFIG_LM)
/****************************************************************************/
/**  enable logging of messages from CC to AC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmLogToAcEnable(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_LOG_TO_AC);
    }

    GOAL_RPC_CLOSE();

    return res;
}
#endif


/****************************************************************************/
/** Log message - server
 *
 * Pop the data from the RPC stack, call the selected function and send a
 * response to the client.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T appl_irj45LogToAcServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint16_t len = 0;                           /* message len */
    GOAL_BUFFER_T *pGoalBuf = NULL;                 /* GOAL buffer */

    /* pop log message from stack */
    GOAL_RPC_POP(len, uint16_t);

    if (GOAL_RES_OK(res)) {
       res = goal_queuePoolGetBuf(&pGoalBuf, len, GOAL_ID_CCM);
    }

    /* pop actual message */
    if (GOAL_RES_OK(res)) {
        res = goal_rpcArgPop(pHdlRpc, (void *) pGoalBuf->ptrData, len);
        pGoalBuf->dataLen = len;
    }

    /* pass log message to goal lm */
    if (GOAL_RES_OK(res)) {
        goal_lmBufferMsgPut(pGoalBuf->ptrData, len, len, GOAL_FALSE);
    }

    goal_queueReleaseBuf(&pGoalBuf);

    return res;
}
#endif


/****************************************************************************/
/**  set fault state on communication error between CC and AC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFaultStateSet(
    APPL_CCM_FAULT_STATE_T faultState         /**< fault state to enter */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(faultState);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_FAULT_STATE_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/**  set behaviour of CCM (CC) on sync reset request
 *
 *    value = 0  :  do nothing
 *    value = 1  :  perform reset of CC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCommResetSet(
    uint8_t value                               /**< option value */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(value);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_COMM_RESET_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** send firmware update data to CC
 *
 * required information for firmware update:
 *   - fw_updateInfo->ihex2bin_info.byte_count  --  length of binary
 *   - fw_updateInfo->signature                 --  signature
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFwUpdateStart(
    uint8_t *pBuf,                              /**< firmware data */
    uint32_t fwSize                             /**< size of firmware data */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */

    /* check if busy */
    if (fwUpdateStatus == FW_UPDATE_TRANSFER) {
        return GOAL_ERR_BUSY;
    }

    fwUpdatePos = 0;
    pFwData = pBuf;
    fwUpdateSize = fwSize;

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_INIT);
    }

    GOAL_RPC_CLOSE();

    if (GOAL_RES_OK(res)) {
        fwUpdateStatus = FW_UPDATE_TRANSFER;
        goal_logInfo("starting firmware transfer");
    }

    return res;
}


/****************************************************************************/
/** perform firmware update step
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFwUpdateExecute(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_EXECUTE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/**  firmware update step
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFoeUpdateSettings(
    char *strName,                              /**< foe firmware filename */
    uint8_t matchLength,                        /**< string match length */
    uint32_t password,                          /**< foe password */
    GOAL_BOOL_T flgBootstrapReq                 /**< bootstrap required */
)
{
    uint8_t len;                                /* string length */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    len = (uint8_t) GOAL_STRLEN(strName);
    GOAL_RPC_PUSH_PTR(strName, len);
    GOAL_RPC_PUSH(len);
    GOAL_RPC_PUSH(matchLength);
    GOAL_RPC_PUSH(password);

    /* push bootstrap option */
    len = (flgBootstrapReq == GOAL_TRUE) ? 1 : 0;
    GOAL_RPC_PUSH(len);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_FOE_UPDATE_SETTINGS);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/**  EtherCAT ssi data update
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmEcatSsiUpdate(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    GOAL_BOOL_T flgEmptyCheck                   /**< empty check before writing */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pData, dataLen);
    GOAL_RPC_PUSH(dataLen);
    GOAL_RPC_PUSH(flgEmptyCheck);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_ECAT_SSI_UPDATE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/**  EtherCAT ssi data configure vendor id
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiVendorId(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t vendorId                           /**< vendor id */
)
{
    ECAT_SSI_T *pDataSsi;                       /* ssi data */

    pDataSsi = (ECAT_SSI_T *) pData;
    if (NULL == pDataSsi || dataLen < sizeof(ECAT_SSI_T)) {
        return GOAL_ERR_PARAM;
    }

    GOAL_htole32_p(&pDataSsi->vendorId_le32, vendorId);

    return GOAL_OK;
}


/****************************************************************************/
/**  EtherCAT ssi data configure product code
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiProductCode(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t productCode                        /**< product code */
)
{
    ECAT_SSI_T *pDataSsi;                       /* ssi data */

    pDataSsi = (ECAT_SSI_T *) pData;
    if (NULL == pDataSsi || dataLen < sizeof(ECAT_SSI_T)) {
        return GOAL_ERR_PARAM;
    }

    GOAL_htole32_p(&pDataSsi->productCode_le32, productCode);

    return GOAL_OK;
}


/****************************************************************************/
/**  EtherCAT ssi data configure revision number
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiRevisionNumber(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t revisionNumber                     /**< revision number */
)
{
    ECAT_SSI_T *pDataSsi;                       /* ssi data */

    pDataSsi = (ECAT_SSI_T *) pData;
    if (NULL == pDataSsi || dataLen < sizeof(ECAT_SSI_T)) {
        return GOAL_ERR_PARAM;
    }

    GOAL_htole32_p(&pDataSsi->revisionNumber_le32, revisionNumber);

    return GOAL_OK;
}


/****************************************************************************/
/**  EtherCAT ssi data configure serial number
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T  appl_ccmCfgSsiSerialNumber(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    uint32_t serialNumber                       /**< serial number */
)
{
    ECAT_SSI_T *pDataSsi;                       /* ssi data */

    pDataSsi = (ECAT_SSI_T *) pData;
    if (NULL == pDataSsi || dataLen < sizeof(ECAT_SSI_T)) {
        return GOAL_ERR_PARAM;
    }

    GOAL_htole32_p(&pDataSsi->serialNumber_le32, serialNumber);

    return GOAL_OK;
}


/****************************************************************************/
/**  EtherCAT ssi data configure vendor name
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiProductType(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strProductType                        /**< vendor name */
)
{
    return replaceString(pData, dataLen, 3, strProductType);
}


/****************************************************************************/
/**  EtherCAT ssi data configure product name
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiProductName(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strProductName                        /**< vendor name */
)
{
    return replaceString(pData, dataLen, 0, strProductName);

}


/****************************************************************************/
/**  EtherCAT ssi data configure order id
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSsiOrderId(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI data length */
    char *strOrderId                            /**< order id */
)
{
    return replaceString(pData, dataLen, 2, strOrderId);

}

/****************************************************************************/
/**  SSI replace string
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T replaceString(
    unsigned char *pData,                       /**< SSI data */
    uint32_t dataLen,                           /**< SSI dara length */
    uint8_t skipStrings,                        /**< strings to skip */
    char *strData                               /**< new string */
)
{
    uint32_t pos;                               /* position */
    uint32_t posCategory;                       /* category position */
    uint16_t catNr;                             /* category */
    uint16_t catLength;                         /* category length */
    uint32_t posCatLength;                      /* position category length */
    uint16_t lenString;                         /* string length */
    uint32_t posLenString;                      /* position string length */
    int16_t diffLen;                            /* length correction */
    int idxString;                              /* string index */

    pos = sizeof(ECAT_SSI_T);
    do {
        /* get category number */
        catNr = GOAL_le16toh_p(&pData[pos]);
        pos += sizeof(uint16_t);

        /* remember category length position */
        posCatLength = pos;

        /* get category length */
        catLength = GOAL_le16toh_p(&pData[pos]);

        /* if found break the loop */
        if (0x000a == catNr) {
            break;
        }

        /* skip to next category */
        pos += sizeof(uint16_t) + catLength * sizeof(uint16_t);

    } while (pos < dataLen);

    if (0x000a == catNr) {

        /* skip category length */
        pos += sizeof(uint16_t);

        /* skip number of strings */
        pos += sizeof(uint8_t);

        /* store start of data */
        posCategory = pos;

        /* skip n strings */
        for (idxString = 0; idxString < skipStrings; idxString++) {
            posLenString = pos;
            pos += sizeof(uint8_t);
            lenString = pData[posLenString];
            pos += lenString;
        }

        /* remember string length position */
        posLenString = pos;

        /* get string length */
        lenString = pData[posLenString];

        /* set position to string data */
        pos += sizeof(uint8_t);

        goal_logInfo("replace string at position %"FMT_u32, pos);

        /* correct new string length */
        diffLen = (int16_t) GOAL_STRLEN(strData) - lenString;

        if (skipStrings < 3) {
            /* diffLen > 0 -> additional space needed */
            /* diffLen < 0 -> space reduction needed */

            /* amount of data to move: [pos + lenString .. posCategory + 2 * catLength] */
            GOAL_MEMMOVE(
                &pData[(int16_t) pos + (int16_t) lenString + diffLen],
                &pData[pos + lenString],
                posCategory + catLength * sizeof(uint16_t) - (pos + lenString));
        }

        /* update string data */
        GOAL_MEMCPY(&pData[pos], strData, GOAL_STRLEN(strData));

        /* update string length */
        pData[posLenString] = (uint8_t) GOAL_STRLEN(strData);

        /* update category length */
        GOAL_htole16_p(&pData[posCatLength], (uint16_t) (catLength + diffLen/2));

        return GOAL_OK;
    }

    return GOAL_ERR_PARAM;
}


/****************************************************************************/
/** register a callback function for firmware update events
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFwUpdateCbReg(
    APPL_CCM_FW_UPDATE_CB_T pFunc               /**< fw update callback */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    FW_UPDATE_STATUS_T status = FW_UPDATE_IDLE; /* update status */

    /* store pointer */
    pFwUpdateCbFunc = pFunc;

    /* tell CC to generate fw update events */
    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_UPDATE_EVENT_ENABLE);
    }

    GOAL_RPC_CLOSE();

    if (GOAL_RES_OK(res)) {
        res = appl_ccmFwUpdateStateGet(&status);
    }

    /* use callback function to interprete state */
    if (NULL != pFunc) {
        pFunc(FW_UPDATE_SOURCE_HTTP, status, 0);
    }

    return res;
}


/****************************************************************************/
/** get firmware update status from CC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T appl_ccmFwUpdateStatusServer(
     GOAL_RPC_HDL_T *pHdlRpc                    /**< rpc handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    FW_UPDATE_STATUS_T remoteStatus;            /* remote fw update status */
    FW_UPDATE_SOURCE_T remoteSource;            /* remote fw update source */
    uint8_t remoteProgress = 0;                 /* remote fw update progress */

    remoteStatus = FW_UPDATE_IDLE;
    remoteSource = FW_UPDATE_SOURCE_RPC;

    GOAL_RPC_POP(remoteProgress, uint8_t);
    GOAL_RPC_POP(remoteStatus, FW_UPDATE_STATUS_T);
    GOAL_RPC_POP(remoteSource, FW_UPDATE_SOURCE_T);

    if (NULL != pFwUpdateCbFunc) {
        pFwUpdateCbFunc(remoteSource, remoteStatus, remoteProgress);
    }

    return res;
}


/****************************************************************************/
/** start default network on CC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmNetworkDefaultUp(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* tell CC to generate fw update events */
    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_NETWORK_DEFAULT_UP);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** start EoE network on CC
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmNetworkEoEUp(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* tell CC to generate fw update events */
    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_NETWORK_EOE_UP);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** configure device MAC address
 *
 * Note: This function must be called before any other network related calls
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmEthMacAddressSet(
    uint8_t *pMacAddress
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pMacAddress, MAC_ADDR_LEN);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_ETH_MAC_ADDRESS);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** get config variable
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgVarGet(
    uint32_t modId,                             /**< module id */
    uint32_t varId,                             /**< variable id */
    void *pBuf,                                 /**< [out] output buffer */
    uint32_t bufLength,                         /**< buffer length */
    uint32_t *pVarLength,                       /**< [out] variable length */
    uint32_t *pVarType                          /**< [out] variable type */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint32_t type = 0;                          /* variable type */
    uint32_t flags = 0;                         /* variable flags */
    uint32_t length = 0;                        /* variable length */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(varId);
    GOAL_RPC_PUSH(modId);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_CFG_VAR_GET);
    }

    GOAL_RPC_POP(type, uint32_t);
    GOAL_RPC_POP(flags, uint32_t);
    GOAL_RPC_POP(length, uint32_t);

    if (length > bufLength) {
        res = GOAL_ERR_OVERFLOW;
    }

    if (GOAL_RES_OK(res)) {
        GOAL_RPC_POP_PTR(pBuf, length);
    }

    if (pVarLength) {
        *pVarLength = length;
    }

    if (pVarType) {
        *pVarType = type;
    }

    UNUSEDARG(flags);

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** set config variable
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgVarSet(
    uint32_t modId,                             /**< module id */
    uint32_t varId,                             /**< variable id */
    void *pBuf,                                 /**< [out] output buffer */
    uint32_t bufLength                          /**< buffer length */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pBuf, bufLength);
    GOAL_RPC_PUSH(bufLength);
    GOAL_RPC_PUSH(varId);
    GOAL_RPC_PUSH(modId);

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_CFG_VAR_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** set config variable
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmCfgSave(
    void
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE;/* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_CCM, GOAL_RPC_FUNC_CCM_CFG_VAR_SAVE);
    }

    GOAL_RPC_CLOSE();

    return res;
}

/****************************************************************************/
/** get update status
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T appl_ccmFwUpdateStateGet(
    FW_UPDATE_STATUS_T *pState                  /**< [out] status */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint8_t updateStatus = 0;                   /* status */

    /* get bootloader active image slot */
    if (GOAL_RES_OK(res)) {
        res = appl_ccmCfgVarGet(
            37, /* module id */
            1000,  /* variable id */
            &updateStatus,
            sizeof(updateStatus),
            NULL, NULL
            );
    }

    if (NULL != pState) {
        switch (updateStatus) {
            case 0:
                *pState = FW_UPDATE_IDLE;
                break;
            case 1:
                *pState = FW_UPDATE_TRANSFER;
                break;
            case 2:
                *pState = FW_UPDATE_ABORT;
                break;
            case 3:
                *pState = FW_UPDATE_COMMIT_DONE;
                break;
            case 4:
                *pState = FW_UPDATE_IDLE;
                break;
            case 5:
                *pState = FW_UPDATE_ABORT;
                break;
            case 6:
                *pState = FW_UPDATE_ABORT;
                break;
            default:
                break;
        }
    }

    return res;
}
