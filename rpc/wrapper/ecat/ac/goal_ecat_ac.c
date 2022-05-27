/** @file
 *
 * @brief  CTC wrapper for ECAT RPC functions
 *
 * @details
 * This module provides a CTC wrapper for ECAT specific functions
 *
 * @copyright
 * Copyright 2010-2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_ID GOAL_ID_ECAT
#define GOAL_ECAT_BUFFERS 1                     /**< buffer size for wrappers */


/****************************************************************************/
/* Includes */
/****************************************************************************/
#include <goal_includes.h>

#include <goal_media/goal_mi_dm.h>

#include "goal_ecat.h"
#include "../goal_ecat_rpc.h"
#if GOAL_CONFIG_MEDIA_MI_DM == 1
#include "../goal_ecat_pdolist.h"
#endif

#include <goal_media/goal_mi_mctc.h>


/****************************************************************************/
/* Type definitions */
/****************************************************************************/
typedef struct GOAL_ECAT_CTC_INST_T {
    GOAL_ECAT_T *pHdlInst;                      /**< EtherCAT instance */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_DM_PART_T *pPartGenericDp;          /**< data stream partition */
    GOAL_MI_MCTC_DP_T genericDp;                /**< generic data provider */
    GOAL_MI_MCTC_DP_T genericDp_cmp;            /**< generic data provider for diff check */
#endif
    GOAL_BOOL_T flgCyclicComm;                  /**< cyclic communication flag */
} GOAL_ECAT_CTC_INST_T;


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_MEM_DENY_HANDLE_T hdlMemDeny;       /**< memory deny delay handle */
static GOAL_STAGE_HANDLER_T stageInit;          /**< init stage handler */
static GOAL_RPC_HDL_CHN_T *pHdlRpcChn = GOAL_RPC_HDL_NONE; /**< acyclic transmission handle */
static GOAL_INSTANCE_LIST_T *mpListInst = NULL; /**< instance list */
static GOAL_ECAT_CTC_INST_T *pEcatCtcInst;      /**< CTC wrapper instance */
static GOAL_BUFFER_T *pDataBuffer;              /**< data buffer */


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
static GOAL_STATUS_T goal_ecatRpcPastInit(
    void
);

static GOAL_STATUS_T goal_ecatRpcSetupChannels(
    void
);

static uint8_t ec_odDataTypeLenGet(
    uint16_t dataType                           /**< data type */
);

static GOAL_STATUS_T goal_ecatCbServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
);

static GOAL_STATUS_T goal_ecatPdoMapIndexSetServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
);

#if GOAL_CONFIG_MEDIA_MI_DM == 1
static GOAL_STATUS_T goal_ecatDmCbCyclicRx(
    GOAL_MI_DM_GROUP_T *pGroup,                 /**< [in] MI DM group handle */
    void *pPriv                                 /**< [in] private pointer */
);
#endif

static GOAL_STATUS_T goal_ecatRpcPushPtrElem(
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< [in] RPC handle */
    uint8_t *pData,                             /**< [in] data */
    uint8_t len,                                /**< data length */
    uint8_t cntElem                             /**< element count */
);

static GOAL_STATUS_T goal_ecatRpcPopPtrElem(
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< [in] RPC handle */
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len,                                /**< data length */
    uint8_t cntElem                             /**< element count */
);

#if GOAL_CONFIG_MEDIA_MI_DM == 1
static GOAL_STATUS_T goal_ecatGenericHToLE(
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len                                 /**< data length */
);
#endif

static GOAL_STATUS_T goal_ecatGenericLEToH(
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len                                 /**< data length */
);


/****************************************************************************/
/** RPC initialization
 *
 * This function initialize all necessary function to use ccm via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatInit(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* request memory deny delay handle */
    res = goal_memDenyDelayHandleGet(&hdlMemDeny);

    /* set  the size of the RPC stack */
    if (GOAL_RES_OK(res)) {
        res = goal_rpcSetStackMax(RPC_BUFF_SIZE_ECAT);
    }

    /* register the rpc past init function */
    if (GOAL_RES_OK(res)) {
        res = goal_mainStageReg(GOAL_STAGE_MODULES, &stageInit, GOAL_STAGE_INIT, goal_ecatRpcPastInit);
    }

    /* create the ECAT instance list */
    if (GOAL_RES_OK(res)) {
        res = goal_instListNew(&mpListInst, GOAL_ID_ECAT_CTC);
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
static GOAL_STATUS_T goal_ecatRpcPastInit(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* setup server function */
    if (GOAL_RES_OK(res)) {
        res = goal_rpcRegisterService(GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CB, &goal_ecatCbServer);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_rpcRegisterService(GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_PDO_MAP_INDEX_SET, &goal_ecatPdoMapIndexSetServer);
    }

    /* setup all necessary RPC channels */
    if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcSetupChannels();
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
static GOAL_STATUS_T goal_ecatRpcSetupChannels(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* setup a channel for RPC */
    res = goal_rpcSetupChannel(&pHdlRpcChn, GOAL_ID_MI_CTC_DEFAULT);

    return res;
}


/****************************************************************************/
/** Create a new Ethercat instance via RPC
 *
 * This function initiates the creation of a new EtherCAT instance on the CC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatNew(
    GOAL_ECAT_T **ppEcat,                       /**< [out] EtherCAT instance ref */
    const uint32_t id,                          /**< instance id */
    GOAL_ECAT_FUNC_CB_T pFunc                   /**< EtherCAT callback function */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(id);

    /* check if EtherNet/IP init is done */
    if (NULL == mpListInst) {
        goal_logErr("EtherCAT not initialized");
        return GOAL_RES_ID(GOAL_ID_ECAT, GOAL_ERR_NOT_INITIALIZED);
    }

    /* create generic GOAL instance */
    res = goal_instNew((GOAL_INSTANCE_T **) &pEcatCtcInst, sizeof(GOAL_ECAT_CTC_INST_T), GOAL_ID_ECAT_CTC, id, "EtherCAT AC");
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create generic instance");
        return res;
    }
    /* create wrapper instance */
    if (GOAL_RES_OK(res)) {
        res = goal_memCalloc(&pEcatCtcInst->pHdlInst, sizeof(GOAL_ECAT_T));
    }

    if (GOAL_RES_OK(res)) {
        res = goal_queuePoolBufsReq(GOAL_ID, GOAL_NETBUF_SIZE, GOAL_ECAT_BUFFERS, 0);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_NEW);
    }

    if (GOAL_RES_OK(res)) {
        pEcatCtcInst->pHdlInst->id = id;
        pEcatCtcInst->pHdlInst->pFunc = (void *) pFunc;
    }

    GOAL_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    /* map generic data provider */
    if (GOAL_RES_OK(res)) {
        res = goal_ecatDmDpAdd(pEcatCtcInst->pHdlInst, GOAL_MI_MCTC_DIR_PEER_FROM, &pEcatCtcInst->pPartGenericDp);
    }

    /* register read callback for cyclic data, use rx mapping to get group id */
    if (GOAL_RES_OK(res)) {
        res = goal_miDmCbReg(NULL, pEcatCtcInst->pPartGenericDp->pGroup, GOAL_MI_DM_CB_READ, goal_ecatDmCbCyclicRx, pEcatCtcInst->pHdlInst);
    }
#else
    /* map generic data provider */
    if (GOAL_RES_OK(res)) {
        res = goal_ecatDmDpAdd(pEcatCtcInst->pHdlInst, GOAL_MI_MCTC_DIR_PEER_FROM, NULL);
    }
#endif

    *ppEcat = pEcatCtcInst->pHdlInst;

    return res;
}


/****************************************************************************/
/** Enable CoE Emergency Service via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgEmergencyOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_EMERGENCY_ON);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Configure the number of CoE Emergency queue slots via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgEmergencyQueueNum(
    int16_t num                                 /**< number of queue slots */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(num)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_EMERGENCY_QUEUE_SIZE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Enable FoE Service via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgFoeOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_FOE_ENABLE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Enable Explicit Device Identification via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgExplDevIdOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_EXPLICIT_DEVICE_ID);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Enable ESM state BOOTSTRAP via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgBootstrapOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_BOOTSTRAP);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Make DC synchronization mandatory via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgDcRequiredOn(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_DC);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set size of PDO bytestream buffer via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgSizePdoStreamBufSet(
    uint16_t size                               /**< size of PDO stream buffer */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(size)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_PDO_STREAM_SIZE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set LED emulation to combined RUN/ERROR led via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatCfgLedStatusIndicator(
    GOAL_BOOL_T enable                          /**< enable or disable feature */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(enable)

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_CFG_LED_STATUS_INDICATOR);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Get the EtherCAT object value via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatObjValGet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint8_t *pData,                             /**< [out] object data buffer */
    uint32_t *pSize                             /**< [in,out] object size reference */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_ECAT_OBJECT_STR_T *pEntry = NULL;      /* entry */
    uint32_t size;                              /* buffer size */

    if (NULL == pSize) {
        return GOAL_ERR_NULL_POINTER;
    }

    size = *pSize;

    GOAL_RPC_NEW();

    /* CC function checks if buffer size is sufficient */
    GOAL_RPC_PUSH(size);
    GOAL_RPC_PUSH(subIndex);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_VAL_GET);
    }

    GOAL_RPC_POP(size, uint32_t);

    if (GOAL_RES_OK(res)) {
        GOAL_LL_FOREACH(pEcat->pListObjectStr, pEntry) {
            if ((index == pEntry->index) &&
                (subIndex == pEntry->subIndex)) {
                /* pop string as byte array */
                GOAL_RPC_POP_PTR(pData, size);
                break;
            }
        }
        if (NULL == pEntry) {
            /* object not in string list, must be numerical */
            res = goal_ecatRpcPopPtrElem(pHdlRpc, pData, size, 1);
        }
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set the EtherCAT object value via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatObjValSet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint8_t *pData,                             /**< [in] new object value */
    uint32_t size                               /**< size of new data */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_ECAT_OBJECT_STR_T *pEntry = NULL;      /* entry */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        GOAL_LL_FOREACH(pEcat->pListObjectStr, pEntry) {
            if (index == pEntry->index &&
                subIndex == pEntry->subIndex) {
                /* push string as byte array */
                GOAL_RPC_PUSH_PTR(pData, size);
                break;
            }
        }
        if (NULL == pEntry) {
            /* object not in string list, must be numerical */
            res = goal_ecatRpcPushPtrElem(pHdlRpc, pData, size, 1);
        }
    }

    GOAL_RPC_PUSH(size);
    GOAL_RPC_PUSH(subIndex);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_VAL_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Add object via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatdynOdObjAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint16_t objType,                           /**< object type (VAR, ARRAY, RECORD) */
    uint16_t dataType                           /**< data type of object */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH(dataType);
    GOAL_RPC_PUSH(objType);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_ADD);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Add subindex to object via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
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
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_BOOL_T flgNumerical = GOAL_TRUE;       /* object is no string */
    GOAL_ECAT_OBJECT_STR_T *pObj = NULL;        /* string entry */
    uint16_t dtSize;                            /* data type size */
    uint16_t byteSize;                          /* data type byte size */

    dtSize = ec_odDataTypeLenGet(dataType);
    byteSize = dtSize >> 3;

    if (0 == dtSize) {
        /* non numerical type */
        flgNumerical = GOAL_FALSE;
        dtSize = size;
        byteSize = size;
    }

    if (NULL != pData) {
        if (0 == (attr & (EC_OBJATTR_RXPDOMAPPING | EC_OBJATTR_TXPDOMAPPING))) {
            goal_logErr("storage variables only allowed for mappable objects");
            return GOAL_ERR_UNSUPPORTED;
        }
    }

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res) && NULL == pMaxVal) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, byteSize, (uint8_t) flgNumerical);
    }
    else if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pMaxVal, byteSize, (uint8_t) flgNumerical);
    }

    if (GOAL_RES_OK(res) && NULL == pMinVal) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, byteSize, (uint8_t) flgNumerical);
    }
    else if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pMinVal, byteSize, (uint8_t) flgNumerical);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, byteSize, (uint8_t) flgNumerical);
    }

    GOAL_RPC_PUSH(byteSize);
    GOAL_RPC_PUSH(attr);
    GOAL_RPC_PUSH(dataType);
    GOAL_RPC_PUSH(subIndex);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_SUB_ADD);
    }

    GOAL_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (attr & (EC_OBJATTR_RXPDOMAPPING | EC_OBJATTR_TXPDOMAPPING)) {
        /* allocate memory for application variable */
        if (NULL == pData) {
            res = goal_memCalloc(&pData, dtSize);
        }

        res = goal_ecatPdoListAdd(pEcat, index, subIndex, dtSize, attr, pData);
    }
#endif

    /* note string objects */
    if (GOAL_RES_OK(res) && (0 == (attr & EC_OBJATTR_NUMERIC))) {
        res = goal_memCalloc(&pObj, sizeof(GOAL_ECAT_OBJECT_STR_T));
        if (GOAL_RES_OK(res)) {
            pObj->index = index;
            pObj->subIndex = subIndex;
            pObj->size = dtSize;

            GOAL_LL_APPEND(pEcat->pListObjectStr, pObj);
        }
    }

    return res;
}


/****************************************************************************/
/** Add subindex to object via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
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
)
{
    return goal_ecatdynOdSubIndexAdd(pEcat, index, subIndex, dataType, attr, pDefVal, pMinVal, pMaxVal, size, pData);
}


/****************************************************************************/
/** Add subindex to object via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
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
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_BOOL_T flgNumerical = GOAL_TRUE;       /* object is no string */
    GOAL_ECAT_OBJECT_STR_T *pObj = NULL;        /* string entry */
    uint16_t dtSize;                            /* data type size */

    dtSize = ec_odDataTypeLenGet(dataType);
    if (0 == dtSize) {
        if (!GOAL_MASK_IS_SET(0x0000FFFF, size)) {
            goal_logErr("invalid size of non-numerical object");
            return GOAL_ERR_PARAM;
        }
        /* non numerical type */
        flgNumerical = GOAL_FALSE;
        dtSize = (uint16_t) size;
    }

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res) && NULL == pMaxVal) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, dtSize, (uint8_t) flgNumerical);
    }
    else if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pMaxVal, dtSize, (uint8_t) flgNumerical);
    }

    if (GOAL_RES_OK(res) && NULL == pMinVal) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, dtSize, (uint8_t) flgNumerical);
    }
    else if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pMinVal, dtSize, (uint8_t) flgNumerical);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_ecatRpcPushPtrElem(pHdlRpc, pDefVal, dtSize, (uint8_t) flgNumerical);
    }

    GOAL_RPC_PUSH(dtSize);
    GOAL_RPC_PUSH(attr);
    GOAL_RPC_PUSH(dataType);
    GOAL_RPC_PUSH(subIndex);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_SUB_ADD_RPC);
    }

    GOAL_RPC_CLOSE();

    /* note string objects */
    if (GOAL_RES_OK(res) && (0 == (attr & EC_OBJATTR_NUMERIC))) {
        res = goal_memCalloc(&pObj, sizeof(GOAL_ECAT_OBJECT_STR_T));
        if (GOAL_RES_OK(res)) {
            pObj->index = index;
            pObj->subIndex = subIndex;
            pObj->size = dtSize;

            GOAL_LL_APPEND(pEcat->pListObjectStr, pObj);
        }
    }

    return res;
}


/****************************************************************************/
/** Assign name to object via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatdynOdObjNameAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    char *pName                                 /**< name of object */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pName, GOAL_STRLEN(pName));
    GOAL_RPC_PUSH((uint32_t) GOAL_STRLEN(pName));
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_NAME_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Assign name to subindex via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatdynOdSubIndexNameAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    char *pName                                 /**< name of sub-index */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pName, GOAL_STRLEN(pName));
    GOAL_RPC_PUSH((uint32_t) GOAL_STRLEN(pName));
    GOAL_RPC_PUSH(subIndex);
    GOAL_RPC_PUSH(index);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_OBJ_SUB_NAME_SET);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Finish object creation via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatdynOdFinish(
    GOAL_ECAT_T *pEcat                          /**< EtherCAT instance data */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_DYN_OBJ_FINISH);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Get current ESM state via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatEsmStateGet(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint8_t *pState                             /**< [out] EtherCAT state */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint8_t esmState = 0;                       /* state */

    GOAL_RPC_NEW();

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_ESM_STATE_GET);
    }

    GOAL_RPC_POP(esmState, uint8_t);
    *pState = esmState;

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Generate an Emergency Message for transmission via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatEmcyReqWrite(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t errorCode,                         /**< standard error code */
    uint8_t *pManuErr                           /**< manufacturer error code */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    GOAL_RPC_NEW();

    GOAL_RPC_PUSH_PTR(pManuErr, 5);
    GOAL_RPC_PUSH(errorCode);

    GOAL_ECAT_RPC_PUSH_INST(((GOAL_ECAT_T *) pEcat));
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_EMERGENCY_WRITE);
    }

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Get the version of the EtherCAT stack via RPC
 *
 * This is the GOAL AC wrapper function for interacting with the stack on the
 * peer core by calling the named function via RPC.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_ecatGetVersion(
    char *strVersion,                           /**< [out] version string */
    int size                                    /**< buffer size */
)
{
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint32_t strSize = 0;                       /* size of version string */

    GOAL_RPC_NEW();

    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_VERSION_GET);
    }

    GOAL_RPC_POP(strSize, uint32_t);
    if (strSize >= (uint32_t) size) {
        res = GOAL_ERR_OVERFLOW;
    }

    GOAL_RPC_POP_PTR(strVersion, strSize);
    strVersion[strSize] = '\0';

    GOAL_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Get bit length of standard data types
 *
 * @internal
 *
 * This function returns the bit length of standard data types. If a data type
 * is unknown or has a variable length 0 is returned.
 *
 * @return length of standard data types in bits
 */
static uint8_t ec_odDataTypeLenGet(
    uint16_t dataType                           /**< data type */
)
{
    uint8_t len;                                /* bit length */

    switch (dataType) {
        case EC_DEFTYPE_BOOL:
        case EC_DEFTYPE_INTEGER8:
        case EC_DEFTYPE_UNSIGNED8:
        case EC_DEFTYPE_BYTE:
            len = 8;
            break;

        case EC_DEFTYPE_INTEGER16:
        case EC_DEFTYPE_UNSIGNED16:
            len = 16;
            break;

        case EC_DEFTYPE_INTEGER32:
        case EC_DEFTYPE_UNSIGNED32:
        case EC_DEFTYPE_REAL32:
            len = 32;
            break;

        case EC_DEFTYPE_INTEGER64:
        case EC_DEFTYPE_UNSIGNED64:
            len = 64;
            break;

        default:
            len = 0;
            break;
    }

    return len;
}


/****************************************************************************/
/** EtherCAT CTC Add Data Provider To Cyclic Data
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_ecatDmDpAdd(
    GOAL_ECAT_T *pEcat,                         /**< GOAL EtherCAT handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDp                /**< [out] partition for data provider status */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint32_t posDp = 0;                         /* cyclic index for data provider status */

    UNUSEDARG(idMiDmPeerTo);

    /* get a new rpc handle */
    res = goal_rpcNew(&pHdlRpc, pHdlRpcChn);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    /* push the EtherCAT handle */
    GOAL_ECAT_RPC_PUSH_INST(pEcat);

    /* push arguments */
    GOAL_RPC_PUSH(GOAL_MI_MCTC_DIR_PEER_TO);

    /* call the procedure at the server */
    if (GOAL_RES_OK(res)) {
        res = goal_rpcCall(pHdlRpc, GOAL_ID_ECAT, GOAL_RPC_FUNC_ECAT_DM_DP_ADD);
    }

    GOAL_RPC_POP(posDp, uint32_t);
    GOAL_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {

        /* partition for data provider status */
        if (NULL != ppPartDp) {

            /* CC: Provider Status -> DM, add partition with fixed index */
            res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_ECAT, &pEcat->dmTxDp, sizeof(GOAL_MI_MCTC_DP_T), posDp);
            if (GOAL_RES_OK(res)) {
                *ppPartDp = &pEcat->dmTxDp;

                /* store MI DM Output group handle */
                goal_miDmGroupGetByIdx(&pEcat->pDmGroupOutput, GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_ECAT);
            }
        }
    }
#else
    UNUSEDARG(posDp);
#endif

    return res;
}


/****************************************************************************/
/** EtherCAT CTC Add Data Provider To Cyclic Data - server functionality
 *
 * This function pops the data from the RPC stack, calls the selected function
 * and pushes the returned values to RPC stack for response.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatCbServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_ECAT_T *pEcat = NULL;                  /* EtherCAT handle */
    GOAL_ECAT_CB_ID_T id = (GOAL_ECAT_CB_ID_T) 0; /* callback id */
    GOAL_ECAT_CB_DATA_T cbData;                 /* callback data */
    GOAL_ECAT_FUNC_CB_T cbFunc;                 /* callback function */
    GOAL_BOOL_T flgValid;                       /* valid cb id flag */
    uint32_t lenData = 0;                       /* length of data */
    GOAL_STATUS_T resLocal = GOAL_OK;           /* local return value */
    GOAL_ECAT_OBJECT_STR_T *pEntry = NULL;      /* entry of string object */

    flgValid = GOAL_FALSE;

    /* get a buffer */
    res = goal_queuePoolGetBuf(&pDataBuffer, GOAL_NETBUF_SIZE, GOAL_ID);

    /* fill data pointer of cb data structure */
    cbData.data[2].pData = pDataBuffer->ptrData;

    GOAL_ECAT_RPC_POP_INST(pEcat);

    GOAL_RPC_POP(id, GOAL_ECAT_CB_ID_T);

    switch (id) {
        case GOAL_ECAT_CB_ID_SDO_UPLOAD:   /* read */
            cbData.data[3].size = 0;
            cbData.data[2].pData = NULL;
            GOAL_RPC_POP(cbData.data[1].subIndex, uint8_t);
            GOAL_RPC_POP(cbData.data[0].index, uint16_t);
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_SDO_DOWNLOAD: /* write */
            GOAL_RPC_POP(cbData.data[3].size, uint32_t);
            GOAL_RPC_POP_PTR(cbData.data[2].pData, cbData.data[3].size);
            GOAL_RPC_POP(cbData.data[1].subIndex, uint8_t);
            GOAL_RPC_POP(cbData.data[0].index, uint16_t);
            if (GOAL_RES_OK(res)) {
                GOAL_LL_FOREACH(pEcat->pListObjectStr, pEntry) {
                    if (cbData.data[0].index == pEntry->index &&
                        cbData.data[1].subIndex == pEntry->subIndex) {
                        /* object in string list */
                        break;
                    }
                }
                if (NULL == pEntry) {
                    /* not found in string list, convert numerical to host order */
                    res = goal_ecatGenericLEToH(cbData.data[2].pData, cbData.data[3].size);
                }
            }
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_NEW_DL_STATE:
            GOAL_RPC_POP(cbData.data[0].dlState, uint16_t);
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_RxPDO_RECEIVED:
            break;
        case GOAL_ECAT_CB_ID_TxPDO_PREPARE:
            break;
        case GOAL_ECAT_CB_ID_SYNC_FAIL:
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_NEW_DC_CONFIG:
            GOAL_RPC_POP(cbData.data[0].dcCycleTime, uint32_t);
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_DC_FAIL:
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_SM_WATCHDOG_EXPIRED:
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_EXPLICIT_DEV_ID:
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_NEW_ESM_STATE_ENTERED:
            GOAL_RPC_POP(cbData.data[0].esmState, uint16_t);
            GOAL_RPC_POP(cbData.data[1].esmError, GOAL_BOOL_T);
            GOAL_RPC_POP(cbData.data[2].statusCode, uint16_t);
            flgValid = GOAL_TRUE;

#if GOAL_CONFIG_MEDIA_MI_DM == 1
            /* intercept if state entered was preop, thus clearing
             * the pdo mapping list */
            if (cbData.data[0].esmState == GOAL_ECAT_ESM_STATE_PREOP) {
                goal_ecatPdoMapClear(pEcat);
            }
#endif

            if (cbData.data[0].esmState == GOAL_ECAT_ESM_STATE_OP) {
                pEcatCtcInst->flgCyclicComm = GOAL_TRUE;
            }
            else {
                pEcatCtcInst->flgCyclicComm = GOAL_FALSE;
            }

            break;
        case GOAL_ECAT_CB_ID_NEW_ESM_STATE_REQUESTED:
            GOAL_RPC_POP(cbData.data[0].esmState, uint16_t);
            GOAL_RPC_POP(cbData.data[1].statusCode, uint16_t);
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_FOE_READ_REQ:
            GOAL_RPC_POP(lenData, uint32_t);
            cbData.data[0].pFileName = (char *) pDataBuffer->ptrData;
            GOAL_RPC_POP_PTR(cbData.data[0].pFileName, lenData);
            cbData.data[0].pFileName[lenData] = 0;
            GOAL_RPC_POP(cbData.data[1].foePassword, uint32_t);
            cbData.data[2].foeError = 0;
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_FOE_READ_DATA:
            cbData.data[0].pData = pDataBuffer->ptrData;
            GOAL_RPC_POP(cbData.data[1].foeOffset, uint32_t);
            GOAL_RPC_POP(cbData.data[2].foeMaxSize, uint32_t);
            cbData.data[4].foeError = 0;
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_FOE_WRITE_REQ:
            GOAL_RPC_POP(lenData, uint32_t);
            cbData.data[0].pFileName = (char *) pDataBuffer->ptrData;
            GOAL_RPC_POP_PTR(cbData.data[0].pFileName, lenData);
            cbData.data[0].pFileName[lenData] = 0;
            GOAL_RPC_POP(cbData.data[1].foePassword, uint32_t);
            cbData.data[2].foeError = 0;
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_FOE_WRITE_DATA:
            GOAL_RPC_POP(cbData.data[2].foeActSize, uint32_t);
            cbData.data[0].pData = pDataBuffer->ptrData;
            GOAL_RPC_POP_PTR(cbData.data[0].pData, cbData.data[2].foeActSize);
            GOAL_RPC_POP(cbData.data[1].foeOffset, uint32_t);
            GOAL_RPC_POP(cbData.data[3].foeFinished, GOAL_BOOL_T);
            cbData.data[4].foeError = 0;
            flgValid = GOAL_TRUE;
            break;
        case GOAL_ECAT_CB_ID_FOE_ERROR:
            GOAL_RPC_POP(cbData.data[0].foeError, uint32_t);
            flgValid = GOAL_TRUE;
            break;
        default:
            break;
    }

    if ((GOAL_TRUE == flgValid) && GOAL_RES_OK(res)) {
        if (NULL != pEcat->pFunc) {
            cbFunc = (GOAL_ECAT_FUNC_CB_T) pEcat->pFunc;
            resLocal = cbFunc(pEcat, id, &cbData);
        }
    }

    switch (id) {
        case GOAL_ECAT_CB_ID_NEW_ESM_STATE_REQUESTED:
            GOAL_RPC_PUSH(cbData.data[2].appStatusCode);
            break;
        case GOAL_ECAT_CB_ID_NEW_DC_CONFIG:
            GOAL_RPC_PUSH(cbData.data[1].dcCycleTimeMin);
            break;
        case GOAL_ECAT_CB_ID_EXPLICIT_DEV_ID:
            GOAL_RPC_PUSH(cbData.data[0].explDevId);
            break;
        case GOAL_ECAT_CB_ID_SDO_UPLOAD:
            if ((NULL != cbData.data[2].pData) && (cbData.data[3].size > 0)) {
                GOAL_LL_FOREACH(pEcat->pListObjectStr, pEntry) {
                    if (cbData.data[0].index == pEntry->index &&
                        cbData.data[1].subIndex == pEntry->subIndex) {
                        /* push string as byte array */
                        GOAL_RPC_PUSH_PTR(cbData.data[2].pData, cbData.data[3].size);
                        break;
                    }
                }
                if (NULL == pEntry) {
                    /* object not in string list, must be numerical */
                    res = goal_ecatRpcPushPtrElem(pHdlRpc, cbData.data[2].pData, cbData.data[3].size, 1);
                }
            }
            GOAL_RPC_PUSH(cbData.data[3].size);
            break;
        case GOAL_ECAT_CB_ID_FOE_READ_REQ:
            GOAL_RPC_PUSH(cbData.data[2].foeError);
            break;
        case GOAL_ECAT_CB_ID_FOE_READ_DATA:
            GOAL_RPC_PUSH(cbData.data[4].foeError);
            GOAL_RPC_PUSH_PTR(cbData.data[0].pData, cbData.data[3].foeActSize);
            GOAL_RPC_PUSH(cbData.data[3].foeActSize);
            break;
        case GOAL_ECAT_CB_ID_FOE_WRITE_REQ:
            GOAL_RPC_PUSH(cbData.data[2].foeError);
            break;
        case GOAL_ECAT_CB_ID_FOE_WRITE_DATA:
            GOAL_RPC_PUSH(cbData.data[4].foeError);
            break;
        default:
            break;
    }

    goal_queueReleaseBuf(&pDataBuffer);

    return resLocal;
}


/****************************************************************************/
/** set offset of mapped object - server functionality
 *
 * This function pops the data from the RPC stack, calls the selected function
 * and pushes the returned values to RPC stack for response.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatPdoMapIndexSetServer(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< rpc handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint16_t index = 0;                         /* object index */
    uint8_t subIndex = 0;                       /* object sub-index */
    GOAL_BOOL_T bTxPdo = GOAL_FALSE;            /* tx pdo (TRUE) or rx pdo (FALSE) */
    uint16_t offset = 0;                        /* object offset */
    uint16_t objSize = 0;                       /* object size */
    GOAL_ECAT_T *pEcat = NULL;                  /* EtherCAT handle */

    GOAL_ECAT_RPC_POP_INST(pEcat);
    GOAL_RPC_POP(index, uint16_t);
    GOAL_RPC_POP(subIndex, uint8_t);
    GOAL_RPC_POP(bTxPdo, GOAL_BOOL_T);
    GOAL_RPC_POP(objSize, uint16_t);
    GOAL_RPC_POP(offset, uint16_t);

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {
        res = goal_ecatPdoListMap(pEcat, index, subIndex, bTxPdo, objSize, offset);
    }
#else
    UNUSEDARG(index);
    UNUSEDARG(subIndex);
    UNUSEDARG(bTxPdo);
    UNUSEDARG(objSize);
    UNUSEDARG(offset);
    UNUSEDARG(pEcat);
#endif

    return res;
}


#if GOAL_CONFIG_MEDIA_MI_DM == 1
/****************************************************************************/
/** Cyclic Data Update Callback
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatDmCbCyclicRx(
    GOAL_MI_DM_GROUP_T *pGroup,                 /**< [in] MI DM group handle */
    void *pPriv                                 /**< [in] private pointer */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_ECAT_T *pHdlEcat;                      /* EtherCAT handle */
    GOAL_ECAT_CB_DATA_T cbData;                 /* callback data */
    GOAL_ECAT_FUNC_CB_T cbFunc;                 /* callback function */
    GOAL_ECAT_PDO_MAPPING_T *pEntry = NULL;     /* mapping entry */
    GOAL_MI_DM_GROUP_T *pGroupWr = NULL;        /* group handle for writing */

    pHdlEcat = (GOAL_ECAT_T *) pPriv;
    cbFunc = (GOAL_ECAT_FUNC_CB_T) pHdlEcat->pFunc;

    /* lock group for reading */
    res = goal_miDmGroupReadStart(pGroup);

    if (GOAL_RES_OK(res)) {
        /* Copy DP status */
        res = goal_miDmGroupPartRead(pEcatCtcInst->pPartGenericDp, (uint8_t *) &pEcatCtcInst->genericDp);
        /* no evaluation of return value to read all partitions */

        /* Copy Output data */
        if (GOAL_TRUE == pEcatCtcInst->flgCyclicComm) {
            GOAL_LL_FOREACH(pHdlEcat->pListRxPdo, pEntry) {
                if (GOAL_TRUE == pEntry->bMapped) {
                    res = goal_miDmGroupPartRead(&pEntry->dmDataOutput, pEntry->pData);
                    /* no evaluation of return value to read all partitions */

                    if (pEntry->attr & EC_OBJATTR_NUMERIC) {
                        /* apply endianess for numeric types */
                        goal_ecatGenericLEToH(pEntry->pData, pEntry->dmDataOutput.len);
                    }
                }
            }
        }

        /* finish group reading even if reading causes an error */
        res = goal_miDmGroupReadEnd(pGroup);
    }

    if (pEcatCtcInst->genericDp.leds != pEcatCtcInst->genericDp_cmp.leds) {
        /* led states have changed */
        if ((pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_GREEN_1) != (pEcatCtcInst->genericDp_cmp.leds & GOAL_MCTC_DP_LED_GREEN_1)) {
            cbData.data[0].bLedEnable = (pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_GREEN_1) ? GOAL_TRUE : GOAL_FALSE;
            res = cbFunc(pHdlEcat, GOAL_ECAT_CB_ID_RUN_LED_STATE, &cbData);
        }

        if ((pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_RED_1) != (pEcatCtcInst->genericDp_cmp.leds & GOAL_MCTC_DP_LED_RED_1)) {
            cbData.data[0].bLedEnable = (pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_RED_1) ? GOAL_TRUE : GOAL_FALSE;
            res = cbFunc(pHdlEcat, GOAL_ECAT_CB_ID_ERROR_LED_STATE, &cbData);
        }

        if ((pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_RED_2) != (pEcatCtcInst->genericDp_cmp.leds & GOAL_MCTC_DP_LED_RED_2)) {
            cbData.data[0].bLedEnable = (pEcatCtcInst->genericDp.leds & GOAL_MCTC_DP_LED_RED_2) ? GOAL_TRUE : GOAL_FALSE;
            res = cbFunc(pHdlEcat, GOAL_ECAT_CB_ID_ERROR_LED_STATE, &cbData);
        }
    }

    /* only signalize application callback when the update counter changes */
    if ((GOAL_TRUE == pEcatCtcInst->flgCyclicComm) &&
        (pEcatCtcInst->genericDp.cntUpdate != pEcatCtcInst->genericDp_cmp.cntUpdate)) {
        /* indicate updated process data to the application */
        cbFunc(pHdlEcat, GOAL_ECAT_CB_ID_RxPDO_RECEIVED, &cbData);

        /* request to update process data from the application */
        cbFunc(pHdlEcat, GOAL_ECAT_CB_ID_TxPDO_PREPARE, &cbData);

        res = goal_miDmGroupGetByIdx(&pGroupWr, GOAL_MI_MCTC_DIR_PEER_TO, GOAL_ID_ECAT);
        if (GOAL_RES_OK(res)) {
            /* lock group partitions for writing */
            res = goal_miDmGroupWriteStart(pGroupWr);
        }

        /* write all group partitions */
        if (GOAL_RES_OK(res)) {
            GOAL_LL_FOREACH(pHdlEcat->pListTxPdo, pEntry) {
                if (GOAL_TRUE == pEntry->bMapped) {
                    goal_miDmGroupPartWrite(&pEntry->dmDataInput, pEntry->pData, pEntry->size);
                    /* no evaluation of return value to write all partitions */

                    if (pEntry->attr & EC_OBJATTR_NUMERIC) {
                        /* apply endianess for numeric types */
                        goal_ecatGenericHToLE(&(pEntry->dmDataInput.pBufWrite[pEntry->dmDataInput.idxPart]), pEntry->size);
                    }
                }
            }

            /* finish group writing */
            res = goal_miDmGroupWriteEnd(pGroupWr);
        }
    }

    GOAL_MEMCPY(&pEcatCtcInst->genericDp_cmp, &pEcatCtcInst->genericDp, sizeof(pEcatCtcInst->genericDp));

    return GOAL_OK;
}
#endif


/****************************************************************************/
/** Convert object to LE and push it to RPC stack
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatRpcPushPtrElem(
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< [in] RPC handle */
    uint8_t *pData,                             /**< [in] data */
    uint8_t len,                                /**< data length */
    uint8_t cntElem                             /**< element count */
)
{
    GOAL_STATUS_T res;                          /* result */
    uint16_t val_le16;                          /* value 16 bit LE */
    uint32_t val_le32;                          /* value 32 bit LE */
    uint64_t val_le64;                          /* value 64 bit LE */

    /* Do not convert and push the original data pointer, as the
     * variable behind might be used after pushing. Use a temp.
     * variable instead.
     */
    if ((1 == cntElem) && sizeof(uint16_t) == len) {
        GOAL_htole16_p(&val_le16, *(uint16_t *) pData);
        res = goal_miMctcPush((GOAL_MCTC_T *)pHdlRpc, (uint8_t *) &val_le16, len);
    }
    else if ((1 == cntElem) && sizeof(uint32_t) == len) {
        GOAL_htole32_p(&val_le32, *(uint32_t *) pData);
        res = goal_miMctcPush((GOAL_MCTC_T *)pHdlRpc, (uint8_t *) &val_le32, len);
    }
    else if ((1 == cntElem) && sizeof(uint64_t) == len) {
        GOAL_htole64_p(&val_le64, *(uint64_t *) pData);
        res = goal_miMctcPush((GOAL_MCTC_T *)pHdlRpc, (uint8_t *) &val_le64, len);
    }
    else {
        res = goal_miMctcPush((GOAL_MCTC_T *)pHdlRpc, (const uint8_t *) pData, len);
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("RPC push ptr failed: %"FMT_x32, res);
    }

    return res;
}


/****************************************************************************/
/** Pop object from RPC stack and convert it to LE
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatRpcPopPtrElem(
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< [in] RPC handle */
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len,                                /**< data length */
    uint8_t cntElem                             /**< element count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    res = goal_miMctcPop((GOAL_MCTC_T *)pHdlRpc, pData, len);

    if (GOAL_RES_OK(res) && (1 == cntElem)) {
        /* numerical data types must be converted to little endian */
        res = goal_ecatGenericLEToH(pData, len);
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("RPC pop ptr failed: %"FMT_x32, res);
    }

    return res;
}


#if GOAL_CONFIG_MEDIA_MI_DM == 1
/****************************************************************************/
/** Convert numerical data type from Hostorder to Little endianess
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatGenericHToLE(
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len                                 /**< data length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint16_t val_le16;                          /* value 16 bit LE */
    uint32_t val_le32;                          /* value 32 bit LE */
    uint64_t val_le64;                          /* value 64 bit LE */

    if (len == sizeof(uint16_t)) {
        val_le16 = GOAL_htole16(*(uint16_t *) pData);
        *(uint16_t *) pData = val_le16;
    }
    else if (len == sizeof(uint32_t)) {
        val_le32 = GOAL_htole32(*(uint32_t *) pData);
        *(uint32_t *) pData = val_le32;
    }
    else if (len == sizeof(uint64_t)) {
        val_le64 = GOAL_htole64(*(uint64_t *) pData);
        *(uint64_t *) pData = val_le64;
    }

    return res;
}
#endif /* GOAL_CONFIG_MEDIA_MI_DM */


/****************************************************************************/
/** Convert numerical data type from Little endian to Hostorder
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_ecatGenericLEToH(
    uint8_t *pData,                             /**< [in/out] data */
    uint8_t len                                 /**< data length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint16_t val_le16;                          /* value 16 bit LE */
    uint32_t val_le32;                          /* value 32 bit LE */
    uint64_t val_le64;                          /* value 64 bit LE */

    if (len == sizeof(uint16_t)) {
        val_le16 = GOAL_le16toh(*(uint16_t *) pData);
        *(uint16_t *) pData = val_le16;
    }
    else if (len == sizeof(uint32_t)) {
        val_le32 = GOAL_le32toh(*(uint32_t *) pData);
        *(uint32_t *) pData = val_le32;
    }
    else if (len == sizeof(uint64_t)) {
        val_le64 = GOAL_le64toh(*(uint64_t *) pData);
        *(uint64_t *) pData = val_le64;
    }

    return res;
}
