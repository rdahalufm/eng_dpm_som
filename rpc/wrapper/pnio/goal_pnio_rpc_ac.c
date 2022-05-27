/** @file
 *
 * @brief
 * GOAL Generic PROFINET Wrapper for CTC RPC on the application core
 *
 * @details
 * Provides the standard GOAL PROFINET API for CTC RPC applications.
 *
 * @copyright
 * Copyright 2010-2018 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include <goal_includes.h>
#include <goal_pnio.h>

#if GOAL_CONFIG_MCTC_AC == 1
#  include <goal_media/goal_mi_mctc.h>
#endif

#include "goal_pnio_rpc_ac.h"


/****************************************************************************/
/* Defines */
/****************************************************************************/
/**< adding Data Provider to DM automatically */
#ifndef GOAL_CONFIG_PNIO_MCTC_DP_AUTO
# define GOAL_CONFIG_PNIO_MCTC_DP_AUTO 0
#endif

/**< adding APDU status to DM automatically */
#ifndef GOAL_CONFIG_PNIO_MCTC_APDU_AUTO
# define GOAL_CONFIG_PNIO_MCTC_APDU_AUTO 0
#endif

/**< fixed GOAL buffers for CTC AC */
#define GOAL_PNIO_CTC_AC_BUF_FIX 0

/**< temporary GOAL buffers for CTC AC */
#define GOAL_PNIO_CTC_AC_BUF_TMP 2


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_STAGE_HANDLER_T mStageMod;          /**< module stage handler */
static GOAL_INSTANCE_LIST_T *mpListInst = NULL; /**< instance list */
static GOAL_RPC_HDL_CHN_T *pHdlRpcDfl = GOAL_RPC_HDL_NONE; /**< default RPC channel handle */


/****************************************************************************/
/* Local prototypes */
/****************************************************************************/
static GOAL_STATUS_T goal_pnioRpcInit(
    void
);

static GOAL_STATUS_T goal_pnioCb(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< RPC handle */
);

#if GOAL_CONFIG_MEDIA_MI_DM == 1
static GOAL_STATUS_T goal_pnioDmCb(
    GOAL_MI_DM_GROUP_T *pGroup,                 /**< [in] MI DM group handle */
    void *pPriv                                 /**< [in] private pointer */
);

static GOAL_STATUS_T goal_pnioMetaApiGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_API_T **ppApi,               /**< [out] API handle */
    uint32_t idApi                              /**< API */
);

static GOAL_STATUS_T goal_pnioMetaSlotGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SLOT_T **ppSlot,             /**< [out] slot handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot                             /**< slot */
);

static GOAL_STATUS_T goal_pnioMetaSubslotGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SUBSLOT_T **ppSubslot,       /**< [out] subslot handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
);

static GOAL_STATUS_T goal_pnioMetaModuleGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_MODULE_T **ppModule,         /**< [out] module handle */
    uint32_t idModule                           /**< module */
);

static GOAL_STATUS_T goal_pnioMetaSubmoduleGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SUBMODULE_T **ppSubmodule,   /**< [out] submodule handle */
    uint32_t idModule,                          /**< module */
    uint32_t idSubmodule                        /**< submodule */
);
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */

static GOAL_STATUS_T goal_pnioCbDfl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_CB_ID_T idCb,                     /**< callback id */
    GOAL_PNIO_CB_DATA_T *pDataCb                /**< callback parameters */
);

/* callback prototypes */
#undef GOAL_PNIO_FUNC_CB_ENTRY
#define GOAL_PNIO_FUNC_CB_ENTRY(id, name, func) \
    static GOAL_STATUS_T func( \
        GOAL_PNIO_T *pPnio,                     /**< PROFINET instance */ \
        GOAL_RPC_HDL_T *pHdlRpc,                /**< RPC handle */ \
        GOAL_PNIO_CB_ID_T idCb                  /**< callback ID */ \
    );

GOAL_PNIO_FUNC_CB_LIST


/****************************************************************************/
/* Callback id to function map */
/****************************************************************************/
/**< callback function */
typedef GOAL_STATUS_T (* GOAL_PNIO_RPC_FUNC_CB_T)(\
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */ \
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */ \
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */ \
);

/**< callback entry */
typedef struct {
    unsigned int id;                            /**< callback id */
    GOAL_PNIO_RPC_FUNC_CB_T pFunc;              /**< callback function */
} GOAL_PNIO_FUNC_CB_ID_ENTRY_T;


/* create callback function id enum */
#undef GOAL_PNIO_FUNC_CB_ENTRY
#define GOAL_PNIO_FUNC_CB_ENTRY(id, name, func) {id, func},
static GOAL_PNIO_FUNC_CB_ID_ENTRY_T goal_pnioTblCb[] = {
    GOAL_PNIO_FUNC_CB_LIST
};


/****************************************************************************/
/** Initialize PROFINET
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_pnioInitAc(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* set size of RPC stack */
    res = goal_rpcSetStackMax(GOAL_PNIO_RPC_STACK_SIZE);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set RPC stack size");
        return res;
    }

    /* create the PROFINET CTC instance list */
    res = goal_instListNew(&mpListInst, GOAL_ID_PNIO_CTC_AC);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create PROFINET CTC instance list");
    }

    /* add stage handler to register PROFINET RPC functions */
    res = goal_mainStageReg(GOAL_STAGE_MODULES, &mStageMod, GOAL_STAGE_INIT, goal_pnioRpcInit);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to register PROFINET RPC init in modules stage");
    }

    return res;
}


/****************************************************************************/
/** Initialize PROFINET RPC
 *
 * @retval GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_pnioRpcInit(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* register RPC callback function */
    res = goal_rpcRegisterService(GOAL_ID_PNIO, GOAL_PNIO_FUNC_CALLBACK, goal_pnioCb);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to register PROFINET RPC callback function");
        return res;
    }

    /* store RPC default handle */
    res = goal_rpcHdlChnDefaultGet(&pHdlRpcDfl);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to retrieve default CTC handle");
        return res;
    }

    /* allocate required goal buffers */
    res = goal_queuePoolBufsReq(GOAL_ID_PNIO_CTC_AC, GOAL_NETBUF_SIZE, GOAL_PNIO_CTC_AC_BUF_FIX, GOAL_PNIO_CTC_AC_BUF_TMP);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to allocate required buffers");
        return res;
    }

    return GOAL_OK;
}


/****************************************************************************/
/** Create new PROFINET instance
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioNewAc(
    GOAL_PNIO_T **ppPnio,                       /**< PROFINET handle ref */
    const uint32_t id,                          /**< instance id */
    GOAL_PNIO_FUNC_CB_T pFunc                   /**< PROFINET callback function */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_DM_GROUP_T *pGroup = NULL;          /* group handle */
#endif
#if (1 == GOAL_CONFIG_PNIO_MCTC_DP_AUTO) || (1 == GOAL_CONFIG_PNIO_MCTC_APDU_AUTO)
    GOAL_MI_DM_PART_T *pPartTmp = NULL;         /* temp partition for referenece */
#endif

    /* check if PROFINET init is done */
    if (NULL == mpListInst) {
        goal_logErr("PROFINET not initialized");
        return GOAL_RES_ID(GOAL_ID_PNIO_CTC_AC, GOAL_ERR_NOT_INITIALIZED);
    }

    /* create PROFINET instance */
    res = goal_instNew((struct GOAL_INSTANCE_T **) ppPnio, sizeof(GOAL_PNIO_T), GOAL_ID_PNIO_CTC_AC, id, "PROFINET Device Stack for AC");
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create generic PROFINET instance");
        return res;
    }

    /* set CTC AC flag */
    (*ppPnio)->flgCtcAc = GOAL_TRUE;

    /* allocate CTC AC instance */
    res = goal_memCalloc(&(*ppPnio)->pInstAc, sizeof(GOAL_PNIO_INSTANCE_CTC_AC_T));
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create PROFINET CTC AC instance");
        return res;
    }

    /* set instance id */
    (*ppPnio)->pInstAc->idInst = id;

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    goal_logInfo("auto data mapper for DP is %s", (GOAL_TRUE == (GOAL_BOOL_T) GOAL_CONFIG_PNIO_MCTC_DP_AUTO) ? ("enabled") : ("disabled"));
    goal_logInfo("auto data mapper for APDU is %s", (GOAL_TRUE == (GOAL_BOOL_T) GOAL_CONFIG_PNIO_MCTC_APDU_AUTO) ? ("enabled") : ("disabled"));

    /* create group for PEER_FROM direction
     * This is required for initial plugging submodules during runtime. */
    res = goal_miDmGroupNew(&pGroup, GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to create group");
        return res;
    }

    /* registration of DM callback to the PEER_FROM group */
    res = goal_miDmCbReg(NULL, pGroup, GOAL_MI_DM_CB_READ, goal_pnioDmCb, (*ppPnio));
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to register DM callback");
        return res;
    }

    /* create group for PEER_TO direction
     * This is required for initial plugging submodules during runtime. */
    res = goal_miDmGroupNew(&pGroup, GOAL_MI_MCTC_DIR_PEER_TO, GOAL_ID_PNIO);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to create group");
        return res;
    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    /* CTC channel: cyclic data */
    res = goal_miMctcOpen((GOAL_MCTC_INST_T **) &(*ppPnio)->pInstAc->pHdlPnioMctc, GOAL_ID_DEFAULT);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to open MCTC");
        return res;
    }

    /* setup RPC channel for acyclic data exchange */
    res = goal_rpcSetupChannel(&(*ppPnio)->pInstAc->pHdlRpcChnPnio, GOAL_ID_MI_CTC_DEFAULT);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to setup RPC channel");
        return res;
    }

    /* set callback if requested */
    if (NULL != pFunc) {
        (*ppPnio)->pInstAc->pFunc = pFunc;
    } else {
        (*ppPnio)->pInstAc->pFunc = goal_pnioCbDfl;
    }

    /* call PROFINET new on CC */
    GOAL_PNIO_RPC_NEW((*ppPnio)->pInstAc);
    GOAL_PNIO_RPC_CALL((*ppPnio)->pInstAc, GOAL_PNIO_FUNC_NEW);
    GOAL_PNIO_RPC_CLOSE();

#if 1 == GOAL_CONFIG_PNIO_MCTC_DP_AUTO
    /* add Data Provider */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioDmDpAdd(
                (*ppPnio),                      /* PROFINET instance */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                &pPartTmp);                     /* temp partition for referenece */
    }
#endif

#if 1 == GOAL_CONFIG_PNIO_MCTC_APDU_AUTO
    /* add APDU */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioDmApduAddAc(
                (*ppPnio),                      /* PROFINET instance */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                &pPartTmp);                     /* temp partition for referenece */
    }
#endif

    /* info */
    if (GOAL_RES_OK(res)) {
        goal_logInfo("PROFINET Application Core successfully started");
    }

    return res;
}


/****************************************************************************/
/** PROFINET RPC Application Core Callback
 *
 * RPC call parameters:
 *   1. PROFINET instance id
 *   2. callback id
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T goal_pnioCb(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< RPC handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_STATUS_T resCb = GOAL_OK;              /* callback result */
    GOAL_PNIO_CB_ID_T idCb = 0;                 /* callback id */
    unsigned int cntFunc;                       /* function counter */
    GOAL_PNIO_T *pPnio = NULL;                  /* PROFINET instance */

    /* pop PROFINET instance */
    GOAL_PNIO_RPC_POP_INST(pPnio);

    /* pop callback id from RPC stack */
    GOAL_RPC_POP(idCb, GOAL_PNIO_CB_ID_T);

    /* handle callback id */
    if (GOAL_RES_OK(res)) {
        for (cntFunc = 0; ARRAY_ELEMENTS(goal_pnioTblCb) > cntFunc; cntFunc++) {

            if (goal_pnioTblCb[cntFunc].id == idCb) {
                resCb = goal_pnioTblCb[cntFunc].pFunc(pPnio, pHdlRpc, idCb);
                break;
            }
        }

        if (ARRAY_ELEMENTS(goal_pnioTblCb) <= cntFunc) {
            resCb = GOAL_ERR_NOT_FOUND;
        }
    } else {
        resCb = res;
    }

    /* return the result */
    return resCb;
}


/****************************************************************************/
/** PROFINET Alarm Ack Timeout Callback
 *
 * This callback informs the application that waiting for an alarm acknowledge
 * timed out.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. alarm send sequence count
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbAlarmAckTimeout(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    GOAL_RPC_POP(dataCb.data[1].u16, uint16_t);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Alarm Notification Ack Callback
 *
 * This callback informs the application that an acknowledge for an alarm
 * notification was received.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. alarm priority
 *   3. alarm notification acknowledge
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbAlarmNotifyAck(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_PNIO_ALARM_NOTIFY_ACK_T almNotifyAck;  /* GOAL PROFINET alarm notification ack */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    GOAL_RPC_POP(dataCb.data[1].u16, uint16_t);
    GOAL_RPC_POP_PTR(&almNotifyAck, sizeof(GOAL_PNIO_ALARM_NOTIFY_ACK_T));
    dataCb.data[2].pAlarmNotifyAck = &almNotifyAck;

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Alarm Notification Callback
 *
 * This callback informs the application that an alarm notification was
 * received.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. alarm priority
 *   3. alarm notification
 *   4. user data length
 *   5. user data
 *
 * RPC result:
 *   0. GOAL_OK - notification is auto-acknowledged by PROFINET stack
 *   1. other - notification is acknowledged by application
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbAlarmNotify(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_BUFFER_T *pBuf = NULL;                 /* buffer */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_PNIO_ALARM_NOTIFY_T almNotify;         /* GOAL PROFINET alarm notification */

    /* request buffer for data */
    res = goal_queuePoolGetBuf(&pBuf, GOAL_NETBUF_SIZE, GOAL_ID_PNIO_CTC_AC);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to get buffer for user data");
        return res;
    }

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    GOAL_RPC_POP(dataCb.data[1].u16, uint16_t);
    GOAL_RPC_POP_PTR(&almNotify, sizeof(GOAL_PNIO_ALARM_NOTIFY_T));
    dataCb.data[2].pAlarmNotify = &almNotify;
    GOAL_RPC_POP(dataCb.data[3].u16, uint16_t);

    /* check buffer size */
    if (pBuf->bufSize < dataCb.data[3].u16) {
        goal_logErr("user data buffer too small");
        res = GOAL_ERR_OVERFLOW;
    }

    if (GOAL_RES_OK(res)) {
        dataCb.data[4].pCu8 = pBuf->ptrData;
        GOAL_RPC_POP_PTR(pBuf->ptrData, dataCb.data[3].u16);
    }

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    /* release buffer */
    goal_queueReleaseBuf(&pBuf);

    return res;
}


/****************************************************************************/
/** PROFINET Application Ready Callback
 *
 * This callback informs the application that the application ready response
 * was received.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * RPC result:
 *   0. GOAL_OK - application ready response ok
 *   1. other - unknown application ready response received
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbApplReady(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Blink Callback
 *
 * This callback informs the application that the DCP signal (blink) request
 * was received.
 *
 * RPC call parameters:
 *   1. blink state (start, toggle, finish)
 *   2. light state (on, off)
 *
 * RPC result:
 *   0. GOAL_OK - PROFINET toggles LED by OAL_setLeds
 *   1. other - application handles LED
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbBlink(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].stateDcpBlink, GOAL_PNIO_DCP_BLINK_STATE_T);
    GOAL_RPC_POP(dataCb.data[1].stateDcpLight, GOAL_PNIO_DCP_LIGHT_STATE_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Connect Finish Callback
 *
 * This callback informs the application that the connect request was
 * successful processed.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. PROFINET status
 *
 * RPC response parameters:
 *   1. PROFINET status
 *
 * RPC result:
 *   0. GOAL_OK - no PROFINET status set
 *   1. other - PROFINET status set
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbConnectFinish(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_PNIO_STATUS_T status;                  /* PROFINET status */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    dataCb.data[1].pStatus = &status;
    GOAL_RPC_POP_PTR(dataCb.data[1].pStatus, sizeof(GOAL_PNIO_STATUS_T));

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    GOAL_RPC_PUSH_PTR(dataCb.data[1].pStatus, sizeof(GOAL_PNIO_STATUS_T));

    return res;
}


/****************************************************************************/
/** PROFINET Connect Request Callback
 *
 * This callback informs the application that a new connect request was
 * received.
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbConnectRequest(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    UNUSEDARG(pHdlRpc);

    /* call PROFINET callback function */
    return pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
}


/****************************************************************************/
/** PROFINET Connect Request ExpectedSubmoduleBlock Start Callback
 *
 * This callback informs the application that the PROFINET stack starts to
 * process the ExpectedSubmoduleBlock in the received connect request.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbConnectRequestExpStart(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET End of Parameter Callback
 *
 * This callback informs the application that the transfer of parameters is
 * finished.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbEndOfParam(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET End of Parameter for Module Plug Callback
 *
 * This callback informs the application that the transfer of parameters for a
 * newly plugged module is finished.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. plug handle
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbEndOfParamPlug(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    GOAL_RPC_POP(dataCb.data[1].u16, uint16_t);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Connect Request ExpectedSubmoduleBlock Callback
 *
 * This callback is called for each entry of the ExpectedSubmoduleBlock.
 *
 * RPC call parameters:
 *   1. AR id
 *   2. API
 *   3. slot
 *   4. subslot
 *   5. module ident number
 *   6. submodule ident number
 *   7. type (module or submodule)
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbExpSubmod(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);
    GOAL_RPC_POP(dataCb.data[1].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[2].u16, uint16_t);
    GOAL_RPC_POP(dataCb.data[3].u16, uint16_t);
    GOAL_RPC_POP(dataCb.data[4].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[5].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[6].expMode, GOAL_PNIO_IND_EXPMOD_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Factory Reset Callback
 *
 * This callback signals a factory reset to the application. This is not the
 * same as reset to factory.
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbFactoryReset(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    UNUSEDARG(pHdlRpc);

    /* call PROFINET callback function */
    return pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
}


/****************************************************************************/
/** PROFINET IO Data Timeout Callback
 *
 * This callback signals a timeout in the cyclic IO data transfer.
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbIoDataTimeout(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    UNUSEDARG(pHdlRpc);

    /* call PROFINET callback function */
    return pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
}


/****************************************************************************/
/** PROFINET Net IP Set Callback
 *
 * This callback signals a PROFINET IP configuration change.
 *
 * RPC call parameters:
 *   1. IP address
 *   2. netmask
 *   3. gateway
 *   4. temporary flag
 *   5. internal update flag
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbNetIpSet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[1].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[2].u32, uint32_t);
    GOAL_RPC_POP(dataCb.data[3].valBool, GOAL_BOOL_T);
    GOAL_RPC_POP(dataCb.data[4].valBool, GOAL_BOOL_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET New Application Relation Callback
 *
 * This callback signals a new PROFINET application relation.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * RPC result:
 *   0. GOAL_OK - accept connection
 *   1. other - deny connection
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbNewAr(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET New IO Data Callback
 *
 * This callback signals new IO data to the application.
 * RPC call parameters:
 *   1. Frame ID
 *   2. data length
 *   3. data
 *
 * RPC result:
 *   0. GOAL_OK - everything ok
 *   1. other - respond with an error to the received response
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbNewIoData(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* GOAL result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* GOAL PROFINET callback data */
    GOAL_BUFFER_T *pBuf = NULL;                 /* data buffer */

    GOAL_RPC_POP(dataCb.data[0].u16, uint16_t); /* frame ID */
    GOAL_RPC_POP(dataCb.data[1].u16, uint16_t); /* length */

    if (GOAL_RES_OK(res)) {
        /* request buffer for data */
        res = goal_queuePoolGetBuf(&pBuf, dataCb.data[1].u16, GOAL_ID_PNIO_CTC_AC);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to get buffer for station name");
            return res;
        }

        /* check buffer size */
        if (pBuf->bufSize < dataCb.data[1].u16) {
            goal_logErr("buffer for new IO data is too small");
            res = GOAL_ERR_OVERFLOW;
        }
    }

    if (GOAL_RES_OK(res)) {
        dataCb.data[2].pU8 = pBuf->ptrData;
        GOAL_RPC_POP_PTR(pBuf->ptrData, dataCb.data[1].u16);
    }

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    /* release buffer */
    goal_queueReleaseBuf(&pBuf);

    return res;
}


/****************************************************************************/
/** PROFINET Module Plug Response Callback
 *
 * This callback tells the application that a module plug response was
 * received.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * RPC result:
 *   0. GOAL_OK - everything ok
 *   1. other - respond with an error to the received response
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbPlugReady(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Read Record Callback
 *
 * This callback reads record data from the application.
 *
 * RPC call parameters:
 *   0. unused
 *   1. AR id
 *   2. API
 *   3. slot
 *   4. subslot
 *   5. index
 *   6. unused
 *   7. maximum response data length
 *   8. busy index
 *   9. sequence number
 *
 * RPC result:
 *   0. GOAL_OK - PNIO status: index not found
 *   1. GOAL_OK_SUPPORTED - record handled by application
 *   2. other - PNIO status: application read error
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbReadRecord(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    /* data[0] was now obsolete PNIO status */
    GOAL_RPC_POP(dataCb.data[1].idAr, GOAL_PNIO_AR_ID_T); /* AR id */
    GOAL_RPC_POP(dataCb.data[2].u32, uint32_t); /* API */
    GOAL_RPC_POP(dataCb.data[3].u16, uint16_t); /* slot */
    GOAL_RPC_POP(dataCb.data[4].u16, uint16_t); /* subslot */
    GOAL_RPC_POP(dataCb.data[5].u16, uint16_t); /* index */
    GOAL_RPC_POP(dataCb.data[7].u32, uint32_t); /* maximum data length */
    GOAL_RPC_POP(dataCb.data[8].i32, int32_t); /* busy handle */
    GOAL_RPC_POP(dataCb.data[9].u32, uint32_t); /* sequence number */

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Release AR Callback
 *
 * This callback informs the application that an AR was released.
 *
 * RPC call parameters:
 *   1. AR id
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbReleaseAr(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Reset To Factory Callback
 *
 * This callback signals a reset to factory request to the application. This is
 * not the same as factory reset.
 *
 * RPC call parameters:
 *   1. reset to factory action
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbResetToFactory(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].u16, uint16_t);

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET Station Name Callback
 *
 * This callback informs the application about an updated name of station.
 *
 * RPC call parameters:
 *   1. permanent flag
 *   2. name of station length
 *   3. name of station
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbStationName(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_BUFFER_T *pBuf = NULL;                 /* station name buffer */

    /* request buffer for station name */
    res = goal_queuePoolGetBuf(&pBuf, GOAL_NETBUF_SIZE, GOAL_ID_PNIO_CTC_AC);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to get buffer for station name");
        return res;
    }

    GOAL_RPC_POP(dataCb.data[2].valBool, GOAL_BOOL_T);
    GOAL_RPC_POP(dataCb.data[1].u32, uint32_t);

    /* check buffer size */
    if (pBuf->bufSize < dataCb.data[1].u32) {
        goal_logErr("station name buffer too small");
        res = GOAL_ERR_OVERFLOW;
    }

    if (GOAL_RES_OK(res)) {
        dataCb.data[0].pU8 = pBuf->ptrData;
        GOAL_RPC_POP_PTR(pBuf->ptrData, (uint16_t) dataCb.data[1].u32);
    }

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    /* release buffer */
    goal_queueReleaseBuf(&pBuf);

    return res;
}


/****************************************************************************/
/** PROFINET Write Record Callback
 *
 * This callback writes record data to the application.
 *
 * RPC call parameters:
 *   0. unused
 *   1. AR id
 *   2. API
 *   3. slot
 *   4. subslot
 *   5. index
 *   6. received data length
 *   7. received data
 *   8. busy index
 *   9. locked flag
 *  10. sequence number
 *
 * RPC result:
 *   0. GOAL_OK - PNIO status: index not found
 *   1. GOAL_OK_SUPPORTED - record handled by application
 *   2. other - PNIO status: application write error
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbWriteRecord(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_BUFFER_T *pBuf = NULL;                 /* data buffer */

    /* request buffer for data */
    res = goal_queuePoolGetBuf(&pBuf, GOAL_NETBUF_SIZE, GOAL_ID_PNIO_CTC_AC);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to get buffer for data");
        return res;
    }

    GOAL_RPC_POP(dataCb.data[1].idAr, GOAL_PNIO_AR_ID_T); /* AR id */
    GOAL_RPC_POP(dataCb.data[2].u32, uint32_t); /* API */
    GOAL_RPC_POP(dataCb.data[3].u16, uint16_t); /* slot */
    GOAL_RPC_POP(dataCb.data[4].u16, uint16_t); /* subslot */
    GOAL_RPC_POP(dataCb.data[5].u16, uint16_t); /* index */
    GOAL_RPC_POP(dataCb.data[7].u32, uint32_t); /* write data length */

    /* check buffer size */
    if (GOAL_RES_OK(res) && (pBuf->bufSize < dataCb.data[7].u32)) {
        goal_logErr("user data buffer too small");
        res = GOAL_ERR_OVERFLOW;
    }

    if (GOAL_RES_OK(res)) {
        dataCb.data[6].pU8 = pBuf->ptrData;     /* pointer to data */
        GOAL_RPC_POP_PTR(pBuf->ptrData, (uint16_t) dataCb.data[7].u32);
    }

    GOAL_RPC_POP(dataCb.data[8].i32, int32_t);  /* busy handle */
    GOAL_RPC_POP(dataCb.data[9].valBool, GOAL_BOOL_T); /* locked flag */
    GOAL_RPC_POP(dataCb.data[10].u32, uint32_t); /* sequence number */

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    /* release buffer */
    goal_queueReleaseBuf(&pBuf);

    return res;
}


/****************************************************************************/
/** Create a new slot
 *
 * If the auto-generate flag is set the requested API and slot will be
 * automatically created.
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. auto generate flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSlotNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgAutogen);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SLOT_NEW);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Create a new subslot
 *
 * If the auto-generate flag is set the requested API and slot will be
 * automatically created.
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. subslot
 *   4. auto generate flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSubslotNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* subslot handle */
#endif

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgAutogen);
    GOAL_RPC_PUSH(idSubslot);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SUBSLOT_NEW);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    /* create subslot meta entry */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */

    return res;
}


/****************************************************************************/
/** Create a new module
 *
 * RPC call parameters:
 *   1. module id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioModNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod                              /**< module id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idMod);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_MOD_NEW);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Create a new submodule
 *
 * If the auto-generate flag is set the requested module will be automatically
 * created.
 *
 * RPC call parameters:
 *   1. module id
 *   2. submodule id
 *   3. submodule type
 *   4. input size
 *   5. output size
 *   6. auto generate flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSubmodNewAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod,                          /**< submodule id */
    GOAL_PNIO_MOD_TYPE_T type,                  /**< submodule type */
    uint16_t sizeInput,                         /**< input size */
    uint16_t sizeOutput,                        /**< output size */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_PNIO_META_SUBMODULE_T *pSubmodule = NULL; /* submodule handle */
#endif

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgAutogen);
    GOAL_RPC_PUSH(sizeOutput);
    GOAL_RPC_PUSH(sizeInput);
    GOAL_RPC_PUSH(type);
    GOAL_RPC_PUSH(idSubmod);
    GOAL_RPC_PUSH(idMod);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SUBMOD_NEW);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {
        res = goal_pnioMetaSubmoduleGet(pPnio, &pSubmodule, idMod, idSubmod);
    }

    if (GOAL_RES_OK(res)) {
        pSubmodule->type = type;
        pSubmodule->sizeInput = sizeInput;
        pSubmodule->sizeOutput = sizeOutput;
    }
#endif
    return res;
}


/****************************************************************************/
/** Plug a module into a slot
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. module id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioModPlugAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint32_t idMod                              /**< module id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idMod);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_MOD_PLUG);
    GOAL_PNIO_RPC_CLOSE();

    return GOAL_OK;
}


/****************************************************************************/
/** Plug a submodule into a subslot
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. subslot
 *   4. module id
 *   5. submodule id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSubmodPlugAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio || NULL == pPnio->pInstAc) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idSubmod);
    GOAL_RPC_PUSH(idMod);
    GOAL_RPC_PUSH(idSubslot);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SUBMOD_PLUG);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Pull a module from a slot
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioModPullAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot                             /**< slot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SLOT_T *pSlot = NULL;        /* meta slot */
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
#endif

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_MOD_PULL);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {
        res = goal_pnioMetaSlotGet(pPnio, &pSlot, idApi, idSlot);
    }
    if (GOAL_RES_OK(res)) {
        /* check if one of the subslots has been mapped to DM */
        GOAL_LL_FOREACH(pSlot->pListSubslot, pSubslot) {
            if (GOAL_FALSE == goal_miDmPartStatusGet(&pSubslot->dmOut) && GOAL_FALSE == goal_miDmPartStatusGet(&pSubslot->dmOut)) {
                continue;
            }

            /* reset DM only if subslot use the DM */
            res = goal_pnioDmReset(pPnio);
            if (GOAL_RES_OK(res)) {
                break;
            }
        }
    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


/****************************************************************************/
/** Pull a submodule from a subslot
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. subslot
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSubmodPullAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
#endif

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idSubslot);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SUBMOD_PULL);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {
        res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
    }
    if (GOAL_RES_OK(res) &&
        (GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmOut) || GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmOut))) {
        /* reset DM only if subslot used the DM */
        res = goal_pnioDmReset(pPnio);
    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


/****************************************************************************/
/** Read output data
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_pnioDataOutputGetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    char *pBuf,                                 /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T *pStateIops                /**< producer state */
)
{

    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_PNIO_IOXS_T stateIops = GOAL_PNIO_IOXS_GOOD; /* IOPS state */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
#endif

    if (NULL == pPnio || NULL == pPnio->pInstAc) {
        return GOAL_ERR_NULL_POINTER;
    }

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    /* get meta info of subslot */
    res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
    if (GOAL_RES_OK(res) &&
        GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmIopsOut) &&
        GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmOut)) {

        /* start group reading */
        res = goal_miDmGroupReadStart(pSubslot->dmIopsOut.pGroup);

        if (GOAL_RES_OK(res)) {
            /* read IOPS out */
            res = goal_miDmGroupPartRead(&pSubslot->dmIopsOut, (uint8_t *) pStateIops);
        }

        if (GOAL_RES_OK(res)) {
            if (GOAL_PNIO_IOXS_GOOD == *pStateIops) {
                /* read data */
                if (len < pSubslot->dmOut.len) {
                    goal_logWarn("invalid buffer size");
                } else {
                    res = goal_miDmGroupPartRead(&pSubslot->dmOut, (uint8_t *) pBuf);
                }
            }

            /* unlock partition group */
            goal_miDmGroupReadEnd(pSubslot->dmIopsOut.pGroup);
        }
    } else {
#endif
        GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
        GOAL_RPC_PUSH(idApi);
        GOAL_RPC_PUSH(idSlot);
        GOAL_RPC_PUSH(idSubslot);
        GOAL_RPC_PUSH(len);
        GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DATA_OUTPUT_GET);

        GOAL_RPC_POP(stateIops, GOAL_PNIO_IOXS_T);
        *pStateIops = stateIops;
        GOAL_RPC_POP_PTR(pBuf, len);

        GOAL_PNIO_RPC_CLOSE();
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM */
    return res;
}


/****************************************************************************/
/** Write input data
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_pnioDataInputSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    char *pBuf,                                 /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T stateIops                  /**< producer state */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
#endif
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio || NULL == pPnio->pInstAc) {
        return GOAL_ERR_NULL_POINTER;
    }

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    /* get meta info of subslot */
    res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
    if (GOAL_RES_OK(res) &&
        GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmIopsIn) &&
        GOAL_TRUE == goal_miDmPartStatusGet(&pSubslot->dmIn)) {

        /* start group writing */
        res = goal_miDmGroupWriteStart(pSubslot->dmIopsIn.pGroup);

        if (GOAL_RES_OK(res)) {
            /* write IOCS input */
            res = goal_miDmGroupPartWrite(&pSubslot->dmIopsIn, (uint8_t *) &stateIops, (unsigned int) sizeof(GOAL_PNIO_IOXS_T));
        }

        if (GOAL_RES_OK(res)) {
            /* write data */
            if (len < pSubslot->dmIn.len) {
                goal_logWarn("invalid buffer size");
            } else {
                res = goal_miDmGroupPartWrite(&pSubslot->dmIn, (uint8_t *) pBuf, len);
            }

            /* unlock partition group */
            goal_miDmGroupWriteEnd(pSubslot->dmIopsIn.pGroup);
        }
    } else {
#endif /* GOAL_CONFIG_MEDIA_MI_DM */
        GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
        GOAL_RPC_PUSH(idApi);
        GOAL_RPC_PUSH(idSlot);
        GOAL_RPC_PUSH(idSubslot);
        GOAL_RPC_PUSH_PTR(pBuf, len);
        GOAL_RPC_PUSH(len);
        GOAL_RPC_PUSH(stateIops);
        GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DATA_INPUT_SET);
        GOAL_PNIO_RPC_CLOSE();
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    }
#endif

    return res;
}


/****************************************************************************/
/** Get the APDU_Status for a given AR
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_pnioApduStatusGetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    GOAL_PNIO_APDU_STATUS_T *pStatusApdu        /**< APDU status */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idAr);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_APDU_STATUS_GET);
    GOAL_RPC_POP_PTR(pStatusApdu, sizeof(GOAL_PNIO_APDU_STATUS_T));
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Submit Alarm Notification
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmNotifySendAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t *pNrAlarmSeq,                      /**< sequence nr ref */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(idAr);
    GOAL_RPC_PUSH(prio);
    GOAL_RPC_PUSH_PTR(pAlarmNotify, sizeof(GOAL_PNIO_ALARM_NOTIFY_T));
    GOAL_RPC_PUSH_PTR(pDataUser, lenDataUser);
    GOAL_RPC_PUSH(lenDataUser);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_NOTIFY_SEND);
    GOAL_RPC_POP_PTR(pNrAlarmSeq, sizeof(uint16_t));
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Submit Alarm Notification Acknowledge
 *
 * RPC call parameters:
 *   1. AR id
 *   2. priority
 *   3. alarm notification data
 *   4. PROFINET status
 *   5. user data length
 *   6. user data
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmNotifySendAckAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    GOAL_PNIO_STATUS_T *pStatus,                /**< PROFINET status */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(pDataUser, lenDataUser);
    GOAL_RPC_PUSH(lenDataUser);
    GOAL_RPC_PUSH_PTR(pStatus, sizeof(GOAL_PNIO_STATUS_T));
    GOAL_RPC_PUSH_PTR(pAlarmNotify, sizeof(GOAL_PNIO_ALARM_NOTIFY_T));
    GOAL_RPC_PUSH(prio);
    GOAL_RPC_PUSH(idAr);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_NOTIFY_SEND_ACK);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Submit Alarm Notification
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmProcessSendAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(pData, lenData);
    GOAL_RPC_PUSH(lenData);
    GOAL_RPC_PUSH(usi);
    GOAL_RPC_PUSH(subslot);
    GOAL_RPC_PUSH(slot);
    GOAL_RPC_PUSH(api);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_PROCESS_SEND);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Finish a delayed Read Record
 *
 * RPC call parameters:
 *   1. busy handle
 *   2. PROFINET status
 *   3. user data length
 *   4. user data
 *   5. sequence number
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioRecReadFinishAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PROFINET status */
    const uint8_t *pData,                       /**< record data */
    uint16_t len,                               /**< record data length */
    uint32_t numSeq                             /**< sequence number */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_PNIO_STATUS_T localPnioStatus = { 0, 0, 0, 0 }; /* error status */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(pData, len);
    GOAL_RPC_PUSH(numSeq);
    GOAL_RPC_PUSH(len);

    /* prevent pushing of invalid data */
    if (NULL == pStatusPnio) {
        pStatusPnio = &localPnioStatus;
    }

    GOAL_RPC_PUSH_PTR(pStatusPnio, sizeof(GOAL_PNIO_STATUS_T));
    GOAL_RPC_PUSH(hdl);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_REC_READ_FINISH);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Finish a delayed Write Record
 *
 * RPC call parameters:
 *   1. busy handle
 *   2. PROFINET status
 *   3. sequence number
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioRecWriteFinishAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PROFINET status */
    uint32_t numSeq                             /**< sequence number */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    GOAL_PNIO_STATUS_T localPnioStatus = { 0, 0, 0, 0 }; /* error status */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(numSeq);

    /* prevent pushing of invalid data */
    if (NULL == pStatusPnio) {
        pStatusPnio = &localPnioStatus;
    }

    GOAL_RPC_PUSH_PTR(pStatusPnio, sizeof(GOAL_PNIO_STATUS_T));
    GOAL_RPC_PUSH(hdl);

    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_REC_WRITE_FINISH);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Add Extended Channel Diagnosis Entry
 *
 * RPC call parameters:
 *   1. API
 *   2. slot
 *   3. subslot
 *   4. channel
 *   5. error number
 *   6. extended channel error type
 *   7. extended channel error value
 *   8. maintainance required flag
 *   9. maintainance demanded flag
 *   10. submit alarm flag
 *   11. alarm type
 *
 * RPC response parameters:
 *   1. diagnosis handle
 *
 * @returns GOAL_STATUS_T result
 */
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
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(typeAlarm);
    GOAL_RPC_PUSH(flgSubmitAlarm);
    GOAL_RPC_PUSH(flgMaintDem);
    GOAL_RPC_PUSH(flgMaintReq);
    GOAL_RPC_PUSH(valExtChanAdd);
    GOAL_RPC_PUSH(typeExtChanErr);
    GOAL_RPC_PUSH(numErr);
    GOAL_RPC_PUSH(chan);
    GOAL_RPC_PUSH(subslot);
    GOAL_RPC_PUSH(slot);
    GOAL_RPC_PUSH(api);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DIAG_EXT_CHAN_DIAG_ADD);
    GOAL_RPC_POP_PTR(pHdl, sizeof(GOAL_PNIO_DIAG_HANDLE_T));
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Remove Channel Diagnosis
 *
 * RPC call parameters:
 *   1. diagnosis handle
 *   2. submit alarm flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDiagChanDiagRemoveAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T hdl,                /**< diagnosis handle */
    GOAL_BOOL_T flgSubmitAlarm                  /**< submit alarm flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgSubmitAlarm);
    GOAL_RPC_PUSH(hdl);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DIAG_CHAN_DIAG_REMOVE);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Control Cyclic Data Reception
 *
 * RPC call parameters:
 *   1. cyclic data enable flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCyclicCtrlAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_BOOL_T flgCyclic                       /**< cyclic data enable flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgCyclic);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_CYCLIC_CTRL);
    GOAL_PNIO_RPC_CLOSE();
#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {
        /* Set local handling of cyclic data CB. The state may be differ between
         * AC and CC. */
        pPnio->pInstAc->varFlgCyclic = flgCyclic;
    }
#endif
    return res;
}


/****************************************************************************/
/** Set Vendor Id
 *
 * RPC call parameters:
 *   1. vendor id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioVendorIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< vendor id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(id);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_VENDOR_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Device Id
 *
 * RPC call parameters:
 *   1. device id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDeviceIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< device id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(id);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DEVICE_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Device Name
 *
 * RPC call parameters:
 *   1. device name length
 *   2. device name
 *   3. permanent flag
 *   4. run-callback flag
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDeviceNameSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    char *strName,                              /**< device name */
    uint32_t lenName,                           /**< device name length */
    GOAL_BOOL_T flgPerm,                        /**< permanent flag */
    GOAL_BOOL_T flgCb                           /**< run-callback flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(flgCb);
    GOAL_RPC_PUSH(flgPerm);
    GOAL_RPC_PUSH_PTR(strName, (uint16_t) lenName);
    GOAL_RPC_PUSH(lenName);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DEVICE_NAME_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Hardware Revision
 *
 * RPC call parameters:
 *   1. hardware revision
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioHwRevSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t revHw                              /**< hardware revision */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(revHw);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_HWREV_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Software Revision
 *
 * RPC call parameters:
 *   1. software revision prefix
 *   2. functional enhancement
 *   3. bugfix
 *   4. internal change
 *   5. revision counter
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSwRevSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint8_t chrPrefix,                          /**< prefix */
    uint8_t idFuncEnh,                          /**< functional enhancement */
    uint8_t idBugfix,                           /**< bugfix */
    uint8_t idIntChange,                        /**< internal change */
    uint16_t cntRev                             /**< revision counter */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(cntRev);
    GOAL_RPC_PUSH(idIntChange);
    GOAL_RPC_PUSH(idBugfix);
    GOAL_RPC_PUSH(idFuncEnh);
    GOAL_RPC_PUSH(chrPrefix);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SWREV_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Profile Id
 *
 * RPC call parameters:
 *   1. profile id
 *   2. profile specific type
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioProfileIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id,                                /**< profile id */
    uint16_t type                               /**< profile specific type */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(type);
    GOAL_RPC_PUSH(id);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_PROFILE_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Order Id
 *
 * RPC call parameters:
 *   1. order id length
 *   2. order id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioOrderIdSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strOrder,                       /**< order id */
    uint32_t lenOrder                           /**< order id length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(strOrder, (uint16_t) lenOrder);
    GOAL_RPC_PUSH(lenOrder);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ORDER_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Serial Number
 *
 * RPC call parameters:
 *   1. serial number length
 *   2. serial number
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSerialNumSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSerial,                      /**< serial number */
    uint32_t lenSerial                          /**< serial number length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(strSerial, (uint16_t) lenSerial);
    GOAL_RPC_PUSH(lenSerial);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SERIAL_NUM_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Vendor Name
 *
 * RPC call parameters:
 *   1. vendor name length
 *   2. vendor name
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioVendorNameSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strVendor,                      /**< vendor name */
    uint32_t lenVendor                          /**< vendor name length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(strVendor, (uint16_t) lenVendor);
    GOAL_RPC_PUSH(lenVendor);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_VENDOR_NAME_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set Port Description
 *
 * RPC call parameters:
 *   1. port description length
 *   2. port description
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioPortDescSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strPort,                        /**< port description */
    uint32_t lenPort                            /**< port description length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(strPort, (uint16_t) lenPort);
    GOAL_RPC_PUSH(lenPort);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_PORT_DESC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Set System Description
 *
 * RPC call parameters:
 *   1. system descriptio length
 *   2. system description
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioSystemDescSetAc(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSys,                         /**< system description */
    uint32_t lenSys                             /**< system description length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    if (NULL == pPnio) {
        return GOAL_ERR_NULL_POINTER;
    }

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(strSys, (uint16_t) lenSys);
    GOAL_RPC_PUSH(lenSys);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_SYS_DESC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set DCP Factory Reset Disable
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDcpFactoryResetDisableSetAc(
    GOAL_BOOL_T flgDcpFactoryResetDisable       /**< DCP Factory Reset Disable */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgDcpFactoryResetDisable);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DCP_FACTORY_RESET_DISABLE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set DCP Accept Mixcase Stationname
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDcpAcceptMixcaseStationSetAc(
    GOAL_BOOL_T flgDcpAcceptMixcaseStation      /**< DCP Accept Mixcase Stationname */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgDcpAcceptMixcaseStation);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DCP_ACCEPT_MIXCASE_STATION_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Vendor Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgVendorIdSetAc(
    uint16_t idVendor                           /**< Vendor Id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idVendor);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_VENDOR_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDeviceIdSetAc(
    uint16_t idDevice                           /**< Device Id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevice);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEVICE_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Vendor Name
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgVendorNameSetAc(
    const char *strVendor                       /**< Vendor Name */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strVendor, (uint16_t) GOAL_STRLEN(strVendor));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strVendor));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_VENDOR_NAME_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Port Name
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgPortNameSetAc(
    const char *strPort                         /**< Port Name */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strPort, (uint16_t) GOAL_STRLEN(strPort));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strPort));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_PORT_NAME_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set System Description
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSystemDescSetAc(
    const char *strSystem                       /**< System Description */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strSystem, (uint16_t) GOAL_STRLEN(strSystem));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strSystem));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SYSTEM_DESC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Order Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgOrderIdSetAc(
    const char *strIdOrder                      /**< Order Id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIdOrder, (uint16_t) GOAL_STRLEN(strIdOrder));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIdOrder));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_ORDER_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Serial Number
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSerialNumSetAc(
    const char *strNumSerial                    /**< Serial Number */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strNumSerial, (uint16_t) GOAL_STRLEN(strNumSerial));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strNumSerial));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SERIAL_NUM_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Hardware Revision
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgHwRevSetAc(
    uint16_t idRevHw                            /**< Hardware Revision */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idRevHw);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_HW_REV_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Software Revision Prefix
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSwRevPrefixSetAc(
    const char chrRevSwPrefix                   /**< Software Revision Prefix */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(chrRevSwPrefix);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SW_REV_PREFIX_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Software Revision Functional Enhancement
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSwRevFuncEnhSetAc(
    uint8_t idRevSwFuncEnh                      /**< Software Revision Functional Enhancement */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idRevSwFuncEnh);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SW_REV_FUNC_ENH_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Software Revision Bugfix
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSwRevBugfixSetAc(
    uint8_t idRevSwBugfix                       /**< Software Revision Bugfix */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idRevSwBugfix);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SW_REV_BUGFIX_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Software Revision Internal Change
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSwRevIntChgSetAc(
    uint8_t idRevSwIntChg                       /**< Software Revision Internal Change */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idRevSwIntChg);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SW_REV_INT_CHG_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Software Revision Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSwRevCntSetAc(
    uint8_t idRevSwRevCnt                       /**< Software Revision Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idRevSwRevCnt);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SW_REV_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M1 Tag Function
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm1TagFuncSetAc(
    const char *strIm1TagFunc                   /**< I&M1 Tag Function */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIm1TagFunc, (uint16_t) GOAL_STRLEN(strIm1TagFunc));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIm1TagFunc));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_1_TAG_FUNC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M1 Tag Location
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm1TagLocSetAc(
    const char *strIm1TagLoc                    /**< I&M1 Tag Location */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIm1TagLoc, (uint16_t) GOAL_STRLEN(strIm1TagLoc));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIm1TagLoc));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_1_TAG_LOC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M2 Date
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm2DateSetAc(
    const char *strIm2Date                      /**< I&M2 Date */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIm2Date, (uint16_t) GOAL_STRLEN(strIm2Date));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIm2Date));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_2_DATE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M3 Descriptor
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm3DescSetAc(
    const char *strIm3Desc                      /**< I&M3 Descriptor */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIm3Desc, (uint16_t) GOAL_STRLEN(strIm3Desc));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIm3Desc));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_3_DESC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M4 Signature
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm4SigSetAc(
    const char *strIm4Sig                       /**< I&M4 Signature */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strIm4Sig, (uint16_t) GOAL_STRLEN(strIm4Sig));
    GOAL_RPC_PUSH((uint16_t) GOAL_STRLEN(strIm4Sig));
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_4_SIG_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapSimpleSetAc(
    GOAL_BOOL_T flgDevDapSimple                 /**< Device DAP Simple Mode */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgDevDapSimple);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_SIMPLE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP API
 *
 * Requires: Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapApiSetAc(
    uint32_t idDevDapApi                        /**< Device DAP API */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevDapApi);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_API_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP Slot
 *
 * Requires: Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapSlotSetAc(
    uint16_t idDevDapSlot                       /**< Device DAP Slot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevDapSlot);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_SLOT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP Subslot
 *
 * Requires: Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapSubslotSetAc(
    uint16_t idDevDapSubslot                    /**< Device DAP Subslot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevDapSubslot);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_SUBSLOT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP Module
 *
 * Requires: Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapModuleSetAc(
    uint32_t idDevDapMod                        /**< Device DAP Module */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevDapMod);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_MOD_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Device DAP Submodule
 *
 * Requires: Device DAP Simple Mode
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDevDapSubmoduleSetAc(
    uint32_t idDevDapSubmod                     /**< Device DAP Submodule */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idDevDapSubmod);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DEV_DAP_SUBMOD_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Net Link Safety
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgNetLinkSafetySetAc(
    GOAL_BOOL_T flgNetLinkSafety                /**< Net Link Safety */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgNetLinkSafety);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_NET_LINK_SAFETY_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set New IO Data Callback Enable
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgNewIoDataCbSetAc(
    GOAL_BOOL_T flgCbNewIoData                  /**< New IO Data Callback Enable */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgCbNewIoData);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_NEW_IO_DATA_CB_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set LLDP Org Ext
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgLldpOrgExtSetAc(
    GOAL_BOOL_T flgLldpOrgExt                   /**< LLDP Org Ext */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgLldpOrgExt);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_LLDP_ORG_EXT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set LLDP Optional TLVs
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgLldpOptTlvSetAc(
    GOAL_BOOL_T flgLldpOptTlv                   /**< LLDP Optional TLVs */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgLldpOptTlv);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_LLDP_OPT_TLV_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set LLDP Generate Port MAC Addresses
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgLldpGenMacSetAc(
    GOAL_BOOL_T flgLldpGenMac                   /**< LLDP Generate Port MAC Addresses */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgLldpGenMac);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_LLDP_GEN_MAC_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M 1-4 Support
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm14SupportSetAc(
    GOAL_BOOL_T flgIm14Support                  /**< I&M 1-4 Support */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgIm14Support);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_1_4_SUPPORT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M 1-4 Callback
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm14CbSetAc(
    GOAL_BOOL_T flgIm14Cb                       /**< I&M 1-4 Callback */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgIm14Cb);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_1_4_CB_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M 0 Callback
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm0CbSetAc(
    GOAL_BOOL_T flgIm0Cb                        /**< I&M 0 Callback */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgIm0Cb);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_0_CB_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set I&M 0 FilterData Callback
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIm0FilterDataCbSetAc(
    GOAL_BOOL_T flgIm0FilterCb                  /**< I&M 0 FilterData Callback */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgIm0FilterCb);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IM_0_FILTER_CB_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Record Data Storage Size
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgRecDataBusyBufsizeSetAc(
    unsigned int cntRecDataBusyBufsize          /**< Record Data Storage Size */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(cntRecDataBusyBufsize);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_REC_DATA_BUSY_BUFSIZE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set RPC Fragmentation Maximum Request Length
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgRpcFragReqLenMaxSetAc(
    unsigned int sizeRpcFragMaxReqLen           /**< RPC Fragmentation Maximum Request Length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(sizeRpcFragMaxReqLen);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_RPC_FRAG_REQ_LEN_MAX_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set RPC Maximum Fragment Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgRpcFragMaxCntSetAc(
    unsigned int numRpcFragMax                  /**< RPC Maximum Fragment Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numRpcFragMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_RPC_FRAG_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set RPC Fragmentation Support Enable
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgRpcFragEnableSetAc(
    GOAL_BOOL_T flgRpcFragSupport               /**< RPC Fragmentation Support Enable */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgRpcFragSupport);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_RPC_FRAG_ENABLE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set RPC Session Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgRpcSessionMaxCntSetAc(
    unsigned int numRpcSessions                 /**< RPC Session Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numRpcSessions);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_RPC_SESSION_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Diagnosis Maximum Buffer Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDiagBufMaxCntSetAc(
    unsigned int numDiagBufMax                  /**< Diagnosis Maximum Buffer Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numDiagBufMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DIAG_BUF_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Diagnosis Maximum Data Size
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgDiagBufMaxDataSizeSetAc(
    unsigned int numDiagDataSizeMax             /**< Diagnosis Maximum Data Size */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numDiagDataSizeMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_DIAG_BUF_MAX_DATA_SIZE_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set IOCR Maximum Blocks
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgIocrBlocksMaxSetAc(
    unsigned int numIocrBlocksMax               /**< IOCR Maximum Blocks */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numIocrBlocksMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_IOCR_BLOCKS_MAX_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Communication Relation Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgCrMaxCntSetAc(
    unsigned int numCrMax                       /**< Communication Relation Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numCrMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_CR_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Application Relation Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgArMaxCntSetAc(
    unsigned int numArMax                       /**< Application Relation Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numArMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_AR_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set API Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgApiMaxCntSetAc(
    unsigned int numApiMax                      /**< API Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numApiMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_API_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Slot Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSlotMaxCntSetAc(
    unsigned int numSlotMax                     /**< Slot Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numSlotMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SLOT_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Subslot Maximum Count
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSubslotMaxCntSetAc(
    unsigned int numSubslotMax                  /**< Subslot Maximum Count */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numSubslotMax);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SUBSLOT_MAX_CNT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Interface Subslot Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSubslotIfSetAc(
    uint16_t idSubslotIf                        /**< interface subslot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idSubslotIf);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SUBSLOT_IF_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Port Subslot Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSubslotPortSetAc(
    uint16_t idSubslotPort                      /**< port subslot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idSubslotPort);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SUBSLOT_PORT_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Snmp Instance Id
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgSnmpIdSetAc(
    uint32_t idSnmp                             /**< SNMP id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(idSnmp);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_SNMP_ID_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration Set Number of slots in Process alarm queue
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgNumProcAlBufSetAc(
    uint8_t numProcAlBuf                        /**< Number of slots in Process alarm queue */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(numProcAlBuf);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_NUM_PROC_AL_BUF_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** PROFINET Configuration MRP enable
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioCfgFlgMrpCfgSetAc(
    GOAL_BOOL_T flgMrpCfg                       /**< MRP config flag */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_DFL_RPC_NEW();
    GOAL_RPC_PUSH(flgMrpCfg);
    GOAL_DFL_RPC_CALL(GOAL_PNIO_FUNC_CFG_FLG_MRP_SET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


#if GOAL_CONFIG_MEDIA_MI_DM == 1
/****************************************************************************/
/** PROFINET Plug Submod into Data Mapper Subslot
 *
 * The Subslot data is added to the cyclic MCTC stream.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmSubmodPlug(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
)
{
    GOAL_MI_DM_PART_T *pPartTmp = NULL;         /* temp partition for referenece */
    GOAL_MI_DM_PART_T **ppPartTmp1;             /* temp partition reference 1 */
    GOAL_MI_DM_PART_T **ppPartTmp2;             /* temp partition reference 2 */
    GOAL_PNIO_META_SUBMODULE_T *pSubmodule = NULL; /* meta submodule */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    if (NULL == pPnio || NULL == pPnio->pInstAc) {
        return GOAL_ERR_NULL_POINTER;
    }

#if 1 == GOAL_CONFIG_PNIO_MCTC_DP_AUTO
    /* add Data Provider if not already available */
    if (GOAL_FALSE == goal_miDmPartStatusGet(&pPnio->pInstAc->dmDp)) {
        res = goal_pnioDmDpAdd(
                pPnio,                          /* PROFINET instance */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                &pPartTmp);                     /* temp partition for referenece */
    }
#endif
#if 1 == GOAL_CONFIG_PNIO_MCTC_APDU_AUTO
    /* add APDU if not already available */
    if (GOAL_RES_OK(res) && (GOAL_FALSE == goal_miDmPartStatusGet(&pPnio->pInstAc->dmApduOut))) {
        res = goal_pnioDmApduAddAc(
                pPnio,                          /* PROFINET instance */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                &pPartTmp);                     /* temp partition for referenece */
    }
#endif

    /* get Submod configuration for direction and length information */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioMetaSubmoduleGet(pPnio, &pSubmodule, idMod, idSubmod);
    }

    /* add input data of Slot x Subslot y to cyclic data */
    if (GOAL_RES_OK(res) && (GOAL_PNIO_MOD_TYPE_INPUT == pSubmodule->type)) {
        ppPartTmp1 = NULL;
        ppPartTmp2 = &pPartTmp;
    } else if (GOAL_RES_OK(res) && (GOAL_PNIO_MOD_TYPE_OUTPUT == pSubmodule->type)) {
        ppPartTmp1 = &pPartTmp;
        ppPartTmp2 = NULL;
    } else if (GOAL_RES_OK(res) && (GOAL_PNIO_MOD_TYPE_IO == pSubmodule->type)) {
        ppPartTmp1 = &pPartTmp;
        ppPartTmp2 = &pPartTmp;
    } else {
        ppPartTmp1 = NULL;
        ppPartTmp2 = NULL;
    }

    if (GOAL_RES_OK(res)) {
        res = goal_pnioDmSubslotAdd(
                pPnio,                          /* PROFINET handle */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                GOAL_MI_MCTC_DIR_PEER_TO,       /* MI DM 'to peer' handle */
                ppPartTmp1,                     /* cyclic position for RX data */
                ppPartTmp2,                     /* cyclic position for TX data */
                idApi,                          /* API */
                idSlot,                         /* slot */
                idSubslot,                      /* subslot */
                pSubmodule->sizeOutput,         /* output data length */
                pSubmodule->sizeInput           /* input data length */
        );
    }

    if (GOAL_RES_OK(res)) {
        res = goal_pnioDmSubslotIoxsAdd(
                pPnio,                          /* PROFINET instance */
                GOAL_MI_MCTC_DIR_PEER_FROM,     /* MI DM 'from peer' handle */
                GOAL_MI_MCTC_DIR_PEER_TO,       /* MI DM 'to peer' handle */
                ppPartTmp1,                     /* [out] partition for output IOCS */
                ppPartTmp1,                     /* [out] partition for output IOPS */
                ppPartTmp2,                     /* [out] partition for input IOCS */
                ppPartTmp2,                     /* [out] partition for input IOPS */
                idApi,                          /* API */
                idSlot,                         /* slot */
                idSubslot                       /* subslot */
        );
    }

    /* The DM was configured by the functions above. Now plug the submodule into the subslot. */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioRpcSubmodPlug(pPnio, idApi, idSlot, idSubslot, idMod, idSubmod);
    }
    return res;
}
#endif /* GOAL_CONFIG_MEDIA_MI_DM */


/****************************************************************************/
/** PROFINET Add Subslot Data To Cyclic Channel - deprecated
 *
 * Configures the position of the subslot data in the cyclic CTC stream. This
 * API is deprecated, please plug module into DM by goal_pnioDmSubmodPlug
 * directly.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmSubslotAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerFrom,                    /**< MI DM 'from peer' handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDataOut,          /**< [out] partition for output data */
    GOAL_MI_DM_PART_T **ppPartDataIn,           /**< [out] partition for input data */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t lenDataOut,                        /**< output data length */
    uint32_t lenDataIn                          /**< input data length */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint32_t idxDataOut = 0;                    /* index for output data */
    uint32_t idxDataIn = 0;                     /* index for input data */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
#endif

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(lenDataIn);
    GOAL_RPC_PUSH(lenDataOut);
    GOAL_RPC_PUSH(idSubslot);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_RPC_PUSH(idMiDmPeerTo);
    GOAL_RPC_PUSH(idMiDmPeerFrom);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DM_SUBSLOT_ADD);
    GOAL_RPC_POP(idxDataOut, uint32_t);
    GOAL_RPC_POP(idxDataIn, uint32_t);
    GOAL_PNIO_RPC_CLOSE();

#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    if (GOAL_RES_OK(res)) {

        /* register output data partition */
        if (NULL != ppPartDataOut) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerFrom, GOAL_ID_PNIO, &pSubslot->dmOut, lenDataOut, idxDataOut);
                if (GOAL_RES_OK(res)) {
                    *ppPartDataOut = &pSubslot->dmOut;

                    /* store the first DM handle for GOAL_PNIO_CB_ID_NEW_IO_DATA */
                    if ((GOAL_TRUE == pPnio->pInstAc->varFlgCyclic) && (NULL == pPnio->pInstAc->pDmFirst)) {
                        pPnio->pInstAc->pDmFirst = &pSubslot->dmOut;
                    }
                    pPnio->pInstAc->len += lenDataOut;

                    /* store MI DM Output group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupOutput, idMiDmPeerFrom, GOAL_ID_PNIO);
                }
            }
        }

        /* register input data partition */
        if (NULL != ppPartDataIn) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerTo, GOAL_ID_PNIO, &pSubslot->dmIn, lenDataIn, idxDataIn);
                if (GOAL_RES_OK(res)) {
                    *ppPartDataIn = &pSubslot->dmIn;

                    /* store MI DM Input group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupInput, idMiDmPeerTo, GOAL_ID_PNIO);
                }
            }
        }
    }
#else
    UNUSEDARG(idxDataIn);
    UNUSEDARG(idxDataOut);
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


/****************************************************************************/
/** PROFINET CTC Add Subslot IOXS To Cyclic Data
 *
 * Configures the position of the subslot IOXS data in the cyclic CTC stream.
 *
 * Data status order: Output IOCS | Output IOPS | Input IOCS | Input IOPS.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmSubslotIoxsAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerFrom,                    /**< MI DM 'from peer' handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartIocsOut,          /**< [out] partition for output IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsOut,          /**< [out] partition for output IOPS */
    GOAL_MI_DM_PART_T **ppPartIocsIn,           /**< [out] partition for input IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsIn,           /**< [out] partition for input IOPS */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint32_t posDataIocsOut = 0;                /* index for output IOCS */
    uint32_t posDataIopsOut = 0;                /* index for output IOPS */
    uint32_t posDataIocsIn = 0;                 /* index for input IOCS */
    uint32_t posDataIopsIn = 0;                 /* index for input IOPS */
#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    GOAL_PNIO_META_SUBSLOT_T *pSubslot = NULL;  /* meta subslot */
    GOAL_PNIO_IOXS_T stateIocs;                 /* IOCS of output data */
#endif

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH((NULL != ppPartIopsIn) ? GOAL_TRUE : GOAL_FALSE);
    GOAL_RPC_PUSH((NULL != ppPartIocsIn) ? GOAL_TRUE : GOAL_FALSE);
    GOAL_RPC_PUSH((NULL != ppPartIopsOut) ? GOAL_TRUE : GOAL_FALSE);
    GOAL_RPC_PUSH((NULL != ppPartIocsOut) ? GOAL_TRUE : GOAL_FALSE);
    GOAL_RPC_PUSH(idSubslot);
    GOAL_RPC_PUSH(idSlot);
    GOAL_RPC_PUSH(idApi);
    GOAL_RPC_PUSH(idMiDmPeerTo);
    GOAL_RPC_PUSH(idMiDmPeerFrom);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DM_SUBSLOT_IOXS_ADD);
    GOAL_RPC_POP(posDataIopsIn, uint32_t);
    GOAL_RPC_POP(posDataIocsIn, uint32_t);
    GOAL_RPC_POP(posDataIopsOut, uint32_t);
    GOAL_RPC_POP(posDataIocsOut, uint32_t);
    GOAL_PNIO_RPC_CLOSE();

#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    if (GOAL_RES_OK(res)) {

        /* partition for output IOCS */
        if (NULL != ppPartIocsOut) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* DM: output IOCS -> CC, add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerTo, GOAL_ID_PNIO, &pSubslot->dmIocsOut, GOAL_PNIO_LEN_IOXS, posDataIocsOut);
                if (GOAL_RES_OK(res)) {
                    *ppPartIocsOut = &pSubslot->dmIocsOut;

                    /* store MI DM Output group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupInput, idMiDmPeerTo, GOAL_ID_PNIO);
                }

                /* set consumer state initial to GOOD */
                if (GOAL_RES_OK(res)) {
                    stateIocs = GOAL_PNIO_IOXS_GOOD;
                    res = goal_miDmSingleWrite(&pSubslot->dmIocsOut, (uint8_t *) &stateIocs, sizeof(GOAL_PNIO_IOXS_T));
                    if (GOAL_RES_ERR(res)) {
                        goal_logErr("failed to write IOCS");
                    }
                }
            }
        }

        /* partition for output IOPS */
        if (NULL != ppPartIopsOut) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* CC: output IOPS -> DM, add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerFrom, GOAL_ID_PNIO, &pSubslot->dmIopsOut, GOAL_PNIO_LEN_IOXS, posDataIopsOut);
                if (GOAL_RES_OK(res)) {
                    /* store the first DM handle for GOAL_PNIO_CB_ID_NEW_IO_DATA */
                    if ((GOAL_TRUE == pPnio->pInstAc->varFlgCyclic) && (NULL == pPnio->pInstAc->pDmFirst)) {
                        pPnio->pInstAc->pDmFirst = &pSubslot->dmIopsOut;
                    }
                    pPnio->pInstAc->len += GOAL_PNIO_LEN_IOXS;

                    *ppPartIopsOut = &pSubslot->dmIopsOut;

                    /* store MI DM Output group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupOutput, idMiDmPeerFrom, GOAL_ID_PNIO);
                }
            }
        }

        /* partition for input IOCS */
        if (NULL != ppPartIocsIn) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* CC: input IOCS -> DM, add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerFrom, GOAL_ID_PNIO, &pSubslot->dmIocsIn, GOAL_PNIO_LEN_IOXS, posDataIocsIn);
                if (GOAL_RES_OK(res)) {
                    /* store the first DM handle for GOAL_PNIO_CB_ID_NEW_IO_DATA */
                    if ((GOAL_TRUE == pPnio->pInstAc->varFlgCyclic) && (NULL == pPnio->pInstAc->pDmFirst)) {
                        pPnio->pInstAc->pDmFirst = &pSubslot->dmIocsIn;
                    }
                    pPnio->pInstAc->len += GOAL_PNIO_LEN_IOXS;

                    *ppPartIocsIn = &pSubslot->dmIocsIn;

                    /* store MI DM Input group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupOutput, idMiDmPeerFrom, GOAL_ID_PNIO);
                }
            }
        }

        /* partition for input IOPS */
        if (NULL != ppPartIopsIn) {

            /* retrieve subslot */
            res = goal_pnioMetaSubslotGet(pPnio, &pSubslot, idApi, idSlot, idSubslot);
            if (GOAL_RES_OK(res)) {

                /* DM: input IOPS -> CC, add partition with fixed index */
                res = goal_miDmPartIdxReg(idMiDmPeerTo, GOAL_ID_PNIO, &pSubslot->dmIopsIn, GOAL_PNIO_LEN_IOXS, posDataIopsIn);
                if (GOAL_RES_OK(res)) {
                    *ppPartIopsIn = &pSubslot->dmIopsIn;

                    /* store MI DM Input group handle */
                    goal_miDmGroupGetByIdx(&pPnio->pDmGroupInput, idMiDmPeerTo, GOAL_ID_PNIO);
                }
            }
        }
    }
#else
    UNUSEDARG(posDataIocsIn);
    UNUSEDARG(posDataIocsOut);
    UNUSEDARG(posDataIopsIn);
    UNUSEDARG(posDataIopsOut);
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


/****************************************************************************/
/** PROFINET Reset Data Mapper from Cyclic Channel
 *
 * Reset the Data Mapper and remove all subslot data from the cyclic MCTC
 * stream. Removing a single partition form DM is not possible. Thus, all
 * partitions of the GOAL_ID_PNIO DM (incl. DP,  APDU) will be removed at once.
 * The upper layer has to setup the DM configuration again if
 * GOAL_CONFIG_PNIO_MCTC_DP_AUTO and GOAL_CONFIG_PNIO_MCTC_APDU_AUTO is 0.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmResetAc(
    GOAL_PNIO_T *pPnio                          /**< PROFINET instance */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DM_RESET);
    GOAL_PNIO_RPC_CLOSE();

#if 1 == GOAL_CONFIG_MEDIA_MI_DM
    if (GOAL_RES_OK(res) && (NULL != pPnio->pDmGroupOutput)) {
        /* remove all group parts from DM */
        res = goal_miDmGroupPartsRemove(GOAL_MI_MCTC_DIR_PEER_TO, GOAL_ID_PNIO);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to remove all group parts from DM");
            return res;
        }

        /* remove all group parts from DM */
        res = goal_miDmGroupPartsRemove(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to remove all group parts from DM");
            return res;
        }

        /* reset information of first DM element */
        pPnio->pInstAc->pDmFirst = NULL;
        pPnio->pInstAc->len = 0;

        /* remove MI DM Output group handle */
        pPnio->pDmGroupOutput = NULL;
        pPnio->pDmGroupInput = NULL;

    }
#endif /* GOAL_CONFIG_MEDIA_MI_DM */
    return res;
}


/****************************************************************************/
/** PROFINET CTC Add Output APDU Status To Cyclic Data
 *
 * Data order: Cycle Counter (16-bit, big endian) | Data Status | Xfer Status
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmApduAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartApduOut           /**< [out] partition for output APDU data */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint32_t posDmApduOut = 0;                  /* DM index for output APDU */

    UNUSEDARG(idMiDmPeerTo);

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(GOAL_MI_MCTC_DIR_PEER_TO);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DM_APDU_ADD);
    GOAL_RPC_POP(posDmApduOut, uint32_t);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {

        /* partition for output APDU status */
        if (NULL != ppPartApduOut) {

            /* CC: APDU -> DM, add partition with fixed index */
            res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO, &pPnio->pInstAc->dmApduOut, sizeof(GOAL_PNIO_APDU_STATUS_T), posDmApduOut);
            if (GOAL_RES_OK(res)) {
                *ppPartApduOut = &pPnio->pInstAc->dmApduOut;

                /* store MI DM Output group handle */
                goal_miDmGroupGetByIdx(&pPnio->pDmGroupOutput, GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO);
            }
        }
    }
#else
    UNUSEDARG(posDmApduOut);
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


/****************************************************************************/
/** PROFINET CTC Add Data Provider Status To Cyclic Data
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioDmDpAddAc(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDp                /**< [out] partition for data provider status */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint32_t posDp = 0;                         /* cyclic index for data provider status */

    UNUSEDARG(idMiDmPeerTo);

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH(GOAL_MI_MCTC_DIR_PEER_TO);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_DM_DP_ADD);
    GOAL_RPC_POP(posDp, uint32_t);
    GOAL_PNIO_RPC_CLOSE();

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    if (GOAL_RES_OK(res)) {

        /* partition for data provider status */
        if (NULL != ppPartDp) {

            /* CC: Provider Status -> DM, add partition with fixed index */
            res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO, &pPnio->pInstAc->dmDp, sizeof(GOAL_MI_MCTC_DP_T), posDp);
            if (GOAL_RES_OK(res)) {
                *ppPartDp = &pPnio->pInstAc->dmDp;

                /* store MI DM Output group handle */
                goal_miDmGroupGetByIdx(&pPnio->pDmGroupOutput, GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_PNIO);
            }
        }
    }
#else
    /* suppress -Werror=unused-but-set-variable, if logging disabled */
    UNUSEDARG(posDp);
    goal_logInfo("generic data provider mapped to position %"FMT_u32, posDp);
#endif /* GOAL_CONFIG_MEDIA_MI_DM */

    return res;
}


#if GOAL_CONFIG_MEDIA_MI_DM == 1
/****************************************************************************/
/** PROFINET Data Mapper Callback
 *
 * This data mapper callback is executed by every group update. It forwardes
 * the content of Data Provider, IOxS and Subslotdata to application layer.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_pnioDmCb(
    GOAL_MI_DM_GROUP_T *pGroup,                 /**< [in] MI DM group handle */
    void *pPriv                                 /**< [in] private pointer */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_MI_MCTC_DP_T genericDataProvider;      /* generic data provider */
    GOAL_PNIO_INSTANCE_CTC_AC_T *pInstAc;       /* PNIO AC instance */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_PNIO_T *pPnio;                         /* PROFINET handle */
    uint32_t len;                               /* DM partition length */
    GOAL_BOOL_T flgNewIoDataCb = GOAL_FALSE;    /* flag for running new IO Data CB */

    /* get private data */
    pPnio = (GOAL_PNIO_T *) pPriv;
    pInstAc = pPnio->pInstAc;

    /* lock partition group */
    res = goal_miDmGroupReadStart(pGroup);
    if (GOAL_RES_OK(res)) {

        /* fetch status of generic data provider */
        res = goal_miDmGroupPartRead(&pInstAc->dmDp, (uint8_t *) &genericDataProvider);
        if (GOAL_RES_OK(res)) {
            /* check if wink LED changed by comparing light state to LED_WINK state */
            if (pInstAc->stateDcpLight != GOAL_MASK_IS_SET(genericDataProvider.leds, GOAL_MCTC_DP_LED_WINK)) {
                /* toggle state */
                pInstAc->stateDcpLight = GOAL_MASK_IS_SET(genericDataProvider.leds, GOAL_MCTC_DP_LED_WINK);

                /* prepare callback
                 * the correct DCP Blink State can not be restored by LED_WINK only
                 */
                dataCb.data[0].stateDcpBlink = GOAL_PNIO_DCP_BLINK_START;
                dataCb.data[1].stateDcpLight = pInstAc->stateDcpLight;

                /* call PROFINET callback function */
                res = pInstAc->pFunc(pPnio, GOAL_PNIO_CB_ID_BLINK, &dataCb);
            }

            /* NEW IO Data callback */
            if ((GOAL_TRUE == pPnio->pInstAc->varFlgCyclic) && (pInstAc->len)) {

                    /* DP available, run callback only for new cycle counter */
                    if (pInstAc->dmCycle != genericDataProvider.cntUpdate) {
                        pInstAc->dmCycle = genericDataProvider.cntUpdate;
                        flgNewIoDataCb = GOAL_TRUE;
                    }
            }
        } else if ((GOAL_ERR_WRONG_STATE == res) && (GOAL_TRUE == pPnio->pInstAc->varFlgCyclic) && (pInstAc->len)) {
            /* DP not available, run callback always */
            pInstAc->dmCycle++;
            flgNewIoDataCb = GOAL_TRUE;
        }

        /* unlock partition group */
        res = goal_miDmGroupReadEnd(pGroup);
    }

    if (GOAL_TRUE == flgNewIoDataCb) {
       /* prepare callback data */
        dataCb.data[0].u16 = pInstAc->dmCycle;
        dataCb.data[1].u32 = pInstAc->len;
        res = goal_miDmGroupReadBufGet(&dataCb.data[2].pU8, &len, pPnio->pInstAc->pDmFirst);
        if (GOAL_RES_OK(res)) {
            /* call PROFINET callback function */
            res = pInstAc->pFunc(pPnio, GOAL_PNIO_CB_ID_NEW_IO_DATA, &dataCb);
        }
    }
    return res;
}
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */


/****************************************************************************/
/** PROFINET CTC Init Callback
 *
 * This callback informs the application that the PROFINET stack is ready.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_pnioCbInit(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    UNUSEDARG(pHdlRpc);

    /* call PROFINET callback function */
    return pPnio->pInstAc->pFunc(pPnio, idCb, NULL);
}


/****************************************************************************/
/** PROFINET CTC LLDP Update Callback
 *
 * This callback informs the application that the LLDP data was updated.
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbLldpUpdate(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].u32, uint32_t); /* GOAL Ethernet Port */

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET CTC Connect Request Expected Submodule Block Finish Callback
 *
 * This callback informs the application that the Expected Submodule Block in
 * the Connect Request has been processed.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_pnioCbConnReqExpFinish(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].idAr, GOAL_PNIO_AR_ID_T); /* AR id */

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


/****************************************************************************/
/** PROFINET CTC Station Name Verification Callback
 *
 * This callback asks the application if the supplied station name is valid.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_pnioCbStationNameVerify(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */
    GOAL_BUFFER_T *pBuf = NULL;                 /* data buffer */

    GOAL_RPC_POP(dataCb.data[2].valBool, GOAL_BOOL_T); /* permanent flag */
    GOAL_RPC_POP(dataCb.data[1].u32, uint32_t); /* length of station name */

    /* request buffer for data */
    if (GOAL_RES_OK(res)) {
        res = goal_queuePoolGetBuf(&pBuf, (uint16_t) dataCb.data[1].u32, GOAL_ID_PNIO_CTC_AC);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to get buffer for station name");
            return res;
        }
    }

    /* copy data to buffer */
    if (GOAL_RES_OK(res)) {
        dataCb.data[0].pCu8 = pBuf->ptrData;
        GOAL_RPC_POP_PTR(pBuf->ptrData, (uint16_t) dataCb.data[1].u32);
    }

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    /* release buffer */
    goal_queueReleaseBuf(&pBuf);

    return res;
}


/****************************************************************************/
/** PROFINET CTC IP Address Verification Callback
 *
 * This callback asks the application if the supplied IP address data is valid.
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioCbNetIpSetVerify(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_RPC_HDL_T *pHdlRpc,                    /**< RPC handle */
    GOAL_PNIO_CB_ID_T idCb                      /**< callback ID */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_PNIO_CB_DATA_T dataCb;                 /* callback data */

    GOAL_RPC_POP(dataCb.data[0].u32, uint32_t); /* IP address */
    GOAL_RPC_POP(dataCb.data[1].u32, uint32_t); /* netmask */
    GOAL_RPC_POP(dataCb.data[2].u32, uint32_t); /* gateway */
    GOAL_RPC_POP(dataCb.data[3].valBool, GOAL_BOOL_T); /* temporary flag */

    /* call PROFINET callback function */
    if (GOAL_RES_OK(res)) {
        res = pPnio->pInstAc->pFunc(pPnio, idCb, &dataCb);
    }

    return res;
}


#if GOAL_CONFIG_MEDIA_MI_DM == 1
/****************************************************************************/
/** PROFINET - Create or return existing API on AC
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioMetaApiGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_API_T **ppApi,               /**< [out] API handle */
    uint32_t idApi                              /**< API */
)
{
    GOAL_STATUS_T res;                          /* result */

    GOAL_LL_FOREACH(pPnio->pInstAc->pListApi, (*ppApi)) {
        if ((*ppApi)->id == idApi) {
            /* meta API entry found */
            return GOAL_OK;
        }
    }

    /* meta API entry doesn't exists - create new one */
    res = goal_memCalloc(ppApi, sizeof(GOAL_PNIO_META_API_T));
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    /* set API ID */
    (*ppApi)->id = idApi;

    /* append new entry to list */
    GOAL_LL_APPEND(pPnio->pInstAc->pListApi, (*ppApi));

    return GOAL_OK;
}


/****************************************************************************/
/** PROFINET - Create or return existing slot on AC
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioMetaSlotGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SLOT_T **ppSlot,             /**< [out] slot handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot                             /**< slot */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_PNIO_META_API_T *pApi = NULL;          /* meta API */

    /* get meta API handle */
    res = goal_pnioMetaApiGet(pPnio, &pApi, idApi);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    GOAL_LL_FOREACH(pApi->pListSlot, (*ppSlot)) {
        if ((*ppSlot)->id == idSlot) {
            /* meta slot entry found */
            return GOAL_OK;
        }
    }

    /* meta slot entry doesn't exists - create new one */
    res = goal_memCalloc(ppSlot, sizeof(GOAL_PNIO_META_SLOT_T));
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    (*ppSlot)->id = idSlot;

    /* append new entry to list */
    GOAL_LL_APPEND(pApi->pListSlot, (*ppSlot));

    return GOAL_OK;
}


/****************************************************************************/
/** PROFINET - Create or return existing subslot on AC
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioMetaSubslotGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SUBSLOT_T **ppSubslot,       /**< [out] subslot handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_PNIO_META_SLOT_T *pSlot = NULL;        /* meta slot */

    /* get meta slot handle */
    res = goal_pnioMetaSlotGet(pPnio, &pSlot, idApi, idSlot);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    for (*ppSubslot = pSlot->pListSubslot; *ppSubslot; *ppSubslot = (*ppSubslot)->pNext) {
        if ((*ppSubslot)->id == idSubslot) {
            /* subslot entry found */
            return GOAL_OK;
        }
    }

    /* meta sub slot entry doesn't exists - create new one */
    res = goal_memCalloc(ppSubslot, sizeof(GOAL_PNIO_META_SUBSLOT_T));
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    (*ppSubslot)->id = idSubslot;

    /* append new entry to list */
    GOAL_LL_APPEND(pSlot->pListSubslot, (*ppSubslot));

    return GOAL_OK;
}


/****************************************************************************/
/** PROFINET - Create or return existing module on AC
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioMetaModuleGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_MODULE_T **ppModule,         /**< [out] module handle */
    uint32_t idModule                           /**< module */
)
{
    GOAL_STATUS_T res;                          /* result */

    GOAL_LL_FOREACH(pPnio->pInstAc->pListModule, (*ppModule)) {
        if ((*ppModule)->id == idModule) {
            /* meta module entry found */
            return GOAL_OK;
        }
    }

    /* meta module entry doesn't exists - create new one */
    res = goal_memCalloc(ppModule, sizeof(GOAL_PNIO_META_MODULE_T));
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    (*ppModule)->id = idModule;

    /* append new entry to list */
    GOAL_LL_APPEND(pPnio->pInstAc->pListModule, (*ppModule));

    return GOAL_OK;
}


/****************************************************************************/
/** PROFINET - Create or return existing submodule on AC
 *
 * @returns GOAL_STATUS_T status
 */
static GOAL_STATUS_T goal_pnioMetaSubmoduleGet(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_META_SUBMODULE_T **ppSubmodule,   /**< [out] submodule handle */
    uint32_t idModule,                          /**< module */
    uint32_t idSubmodule                        /**< submodule */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_PNIO_META_MODULE_T *pModule = NULL;    /* meta module */

    /* get meta module handle */
    res = goal_pnioMetaModuleGet(pPnio, &pModule, idModule);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    for (*ppSubmodule = pModule->pListSubmodule; *ppSubmodule; *ppSubmodule = (*ppSubmodule)->pNext) {
        if ((*ppSubmodule)->id == idSubmodule) {
            /* submodule entry found */
            return GOAL_OK;
        }
    }

    /* meta sub module entry doesn't exists - create new one */
    res = goal_memCalloc(ppSubmodule, sizeof(GOAL_PNIO_META_SUBMODULE_T));
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    (*ppSubmodule)->id = idSubmodule;

    /* append new entry to list */
    GOAL_LL_APPEND(pModule->pListSubmodule, (*ppSubmodule));

    return GOAL_OK;
}
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */


/****************************************************************************/
/** PROFINET - Default Callback if no Callback is set
 *
 * Always returns default result GOAL_OK.
 *
 * @retval GOAL_OK successful
 */
static GOAL_STATUS_T goal_pnioCbDfl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_CB_ID_T idCb,                     /**< callback id */
    GOAL_PNIO_CB_DATA_T *pDataCb                /**< callback parameters */
)
{
    UNUSEDARG(pPnio);
    UNUSEDARG(idCb);
    UNUSEDARG(pDataCb);

    return GOAL_OK;
}


/****************************************************************************/
/** Initialize Process Alarm Queue
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmProcessQueueInit(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_INIT);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Add Process Alarm to Process Alarm Queue
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmProcessQueueAdd(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_RPC_PUSH_PTR(pData, lenData);
    GOAL_RPC_PUSH(lenData);
    GOAL_RPC_PUSH(usi);
    GOAL_RPC_PUSH(subslot);
    GOAL_RPC_PUSH(slot);
    GOAL_RPC_PUSH(api);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_ADD);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Send Process Alarm from Process Alarm Queue
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_pnioAlarmProcessQueueSend(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_SEND);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Reset Process Alarm Queue
 *
 * @returns GOAL_OK
 */
GOAL_STATUS_T goal_pnioAlarmProcessQueueReset(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_RESET);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Process Connect Request Block
 *
 * @returns GOAL_OK
 */
GOAL_STATUS_T goal_pnioConnReqProcess(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    GOAL_PNIO_RPC_NEW(pPnio->pInstAc);
    GOAL_PNIO_RPC_CALL(pPnio, GOAL_PNIO_FUNC_CONN_REQ_PROCESS);
    GOAL_PNIO_RPC_CLOSE();

    return res;
}
