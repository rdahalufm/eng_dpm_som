/** @file
 *
 * @brief uGOAL MCTC - Common Media Interface
 *
 * @copyright
 * Copyright 2020-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include "goal_includes.h"
#include "goal_mi_mctc.h"
#include "goal_mctc/goal_mctc_rb.h"


/****************************************************************************/
/* Defines */
/****************************************************************************/


/****************************************************************************/
/* Local prototypes */
/****************************************************************************/
static GOAL_STATUS_T goal_miMctcRpcSend(
    MCTC_INST_T *pMiMctc,                       /**< MI MCTC handle */
    uint8_t *pBuf,                              /**< buffer pointer */
    unsigned int len                            /**< buffer length */
);

static GOAL_BOOL_T goal_miMctcRpcSendAllow(
    MCTC_INST_T *pMiMctc                        /**< MI MCTC handle */
);

static GOAL_STATUS_T som_rpcSetupDoneServer(
    struct GOAL_MCTC_T *pCtc                    /**< MCTC handle */
);

static GOAL_STATUS_T ugoal_MctcRpc(
    GOAL_MCTC_T *pMctc                          /**< MCTC handle */
);

static GOAL_STATUS_T goal_miMctcCbSetupStateGet(
    GOAL_MCTC_T *pHdlMctcRx                     /**< MCTC handle */
);


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static unsigned int mSizeXfer = GOAL_MI_MCTC_XFER_SIZE; /**< xfer size */
static MCTC_INST_T mctcInst;                    /**< mctc instance */
extern uint8_t sendData[];                      /**< spi send buffer */
extern uint8_t receiveData[];                   /**< spi receive buffer */
static GOAL_MI_MCTC_CB_RESET_T fnReset;         /**< reset callback */
static GOAL_MI_MCTC_CB_RESET_T fnRemoteReset;   /**< reset callback */
static GOAL_MI_MCTC_CB_ONLINE_T fnOnline;       /**< online callback */
static GOAL_MI_MCTC_CB_TIMEOUT_RX_T fnTimeout;  /**< timeout callback */


/****************************************************************************/
/** MCTC MI - Open
 *
 * Open a registered MI MCTC instance.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcOpen(
    GOAL_MCTC_INST_T **ppInst,                       /**< MCTC instance */
    unsigned int id                             /**< instance id */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_MCTC_TGT_T *pHdlTgtRx = NULL;          /* receive buffer */
    GOAL_MCTC_TGT_T *pHdlTgtTx = NULL;          /* send buffer */
    unsigned int cnt;                           /* counter */

    UNUSEDARG(id);

    if (mctcInst.flgInit == GOAL_TRUE) {
        *ppInst = mctcInst.pInstMctc;
        return GOAL_OK;
    }

    mctcInst.flgInit = GOAL_TRUE;

    /* Manually set rpc size because rpc init handlers are executed afterwars.
     * Because of missing stage system this is not easily fixable
     */
    mSizeXfer = CONFIG_UGOAL_RPC_RB_SIZE;

    res = goal_mctcRpcReg(0, 0, ugoal_MctcRpc);

    if (GOAL_RES_OK(res)) {
        res = goal_mctcRbNew(
            &pHdlTgtRx,
            mSizeXfer * CONFIG_UGOAL_RPC_RB_ENTRIES,
            mSizeXfer,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_mctcRbNew(
            &pHdlTgtTx,
            mSizeXfer * CONFIG_UGOAL_RPC_RB_ENTRIES,
            mSizeXfer,
            NULL);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_mctcInstNew(&mctcInst.pInstMctc, pHdlTgtRx, pHdlTgtTx, CONFIG_UGOAL_RPC_HANDLES, mSizeXfer);
    }

    /* initialize private handle */
    mctcInst.pInstMctc->pPriv = &mctcInst;

    if (GOAL_RES_OK(res)) {
        res = goal_mctcRpcReg(RPC_ID_MCTC, RPC_MCTC_SETUP_DONE, som_rpcSetupDoneServer);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_mctcRpcReg(RPC_ID_MCTC, RPC_MCTC_SETUP_STATE_GET, goal_miMctcCbSetupStateGet);
    }

    if (GOAL_RES_ERR(res)) {
        goal_logErr("initialization failed");
    }

    /* retrieve write partition size */
    mctcInst.sizeRpc = 50;

    /* allocate RPC TX buffers */
    for (cnt = 0; cnt < GOAL_MI_MCTC_RPC_CNT_RESEND; cnt++) {
        res = GOAL_MEM_CALLOC(&mctcInst.pBufRpcTx[cnt], mctcInst.sizeRpc);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to allocate RX/TX resend buffer");
            return res;
        }
    }

    /* subtract RPC header from available payload size */
    mctcInst.sizeRpc -= sizeof(GOAL_MI_MCTC_RPC_TX_T);

    *ppInst = mctcInst.pInstMctc;

    return res;
}


/****************************************************************************/
/** MCTC MI - RPC Send
 *
 * @returns GOAL_STATUS_T
 */
static GOAL_STATUS_T goal_miMctcRpcSend(
    MCTC_INST_T *pMiMctc,                       /**< MI MCTC handle */
    uint8_t *pBuf,                              /**< buffer pointer */
    unsigned int len                            /**< buffer length */
)
{
    GOAL_MI_MCTC_RPC_TX_T *pRpc;                /* RPC header */
    uint8_t *pBufPart = NULL;                   /* partition buffer */

    /* assign destination address */
    pBufPart = (uint8_t *) &sendData[77];

    /* build header */
    pRpc = (GOAL_MI_MCTC_RPC_TX_T *) pBufPart;
    pRpc->flags = pMiMctc->flgRpc;
    pRpc->seqLocal = pMiMctc->seqRpcLocal;
    pRpc->seqRemoteAck = pMiMctc->seqRpcRemoteAck;
    pRpc->lenData = (uint8_t) len;

    goal_logDbg("seqLocal = %d", pMiMctc->seqRpcLocal);

    /* acknowledge sync if remote requests it */
    if (GOAL_MI_MCTC_RPC_FLG_SYNC_REQ & pMiMctc->flgRpcRemote) {
        pRpc->flags |= GOAL_MI_MCTC_RPC_FLG_SYNC_ACK;
    }

    /* attach data */
    if ((NULL != pBuf) && (0 != len)) {
        GOAL_MEMCPY(&pBufPart[sizeof(GOAL_MI_MCTC_RPC_TX_T)], pBuf, len);
        pMiMctc->flgRpcPrevEmpty = GOAL_FALSE;
    } else {
        pMiMctc->flgRpcPrevEmpty = GOAL_TRUE;
    }

    /* calculate CRC */
    pRpc->crc_le16 = GOAL_htole16(GOAL_FLETCHER16(&pBufPart[sizeof(GOAL_MI_MCTC_RPC_TX_T)], (int) len) + IRJ45_CRC_OFFSET);

    goal_logDbg("local %stransmit: l:%u, lack:%u, rack:%u, buf_idx: %u, flags: 0x%x",
                 (GOAL_MI_MCTC_RPC_FLG_RESEND & pRpc->flags) ? "re" : "",
                 pRpc->seqLocal,
                 pMiMctc->seqRpcLocalAck,
                 pRpc->seqRemoteAck,
                 pMiMctc->cntResend,
                 pRpc->flags);

    /* add frame to send-active counter */
    pMiMctc->cntRpcActive++;

    /* update receive timeout timestamp */
    pMiMctc->tsRpcTout = GOAL_TIMER_TS_GET() + GOAL_MI_MCTC_RPC_RECV_TOUT;

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC Send Processing
 *
 * @returns GOAL_STATUS_T
 */
GOAL_STATUS_T goal_miMctcRpcTxProcess(
    MCTC_INST_T *pMiMctc                        /**< MCTC handle */
)
{
    GOAL_STATUS_T res;                          /* result */
    unsigned int valDiff;                       /* difference value */
    unsigned int lenData;                       /* data length */

    /* check if remote got all our frames */
    valDiff = (pMiMctc->seqRpcLocal >= pMiMctc->seqRpcLocalAck) ? pMiMctc->seqRpcLocal - pMiMctc->seqRpcLocalAck : pMiMctc->seqRpcLocal + GOAL_MI_MCTC_RPC_MAX_SEQ - pMiMctc->seqRpcLocalAck;
    if (GOAL_MI_MCTC_RPC_CNT_RESEND <= valDiff) {

        /* update remote sequence */
        GOAL_MASK_SET(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_RESEND);
        GOAL_MASK_SET(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_REQ_ACK);
        goal_miMctcRpcSend(pMiMctc, pMiMctc->pBufRpcTx[pMiMctc->cntResend], pMiMctc->lenBufRpcTx[pMiMctc->cntResend]);
        return GOAL_OK;
    }

    /* get data length from TX rb */
    lenData = goal_mctcRbLenGet((GOAL_MCTC_RB_T *) pMiMctc->pInstMctc->pTgtTx->pPriv);
    if (lenData > pMiMctc->sizeRpc) {
        lenData = pMiMctc->sizeRpc;
    }

    /* skip processing if no data is available, no ACK is needed and sequence is confirmed */
    if ((0 == lenData) && (GOAL_FALSE == pMiMctc->flgRpcAck) && (pMiMctc->seqRpcLocal == pMiMctc->seqRpcLocalAck)) {
        return GOAL_OK;
    }

    /* get TX data from ringbuffer */
    if (0 != lenData) {
        res = goal_mctcRbPeek((GOAL_MCTC_RB_T *) pMiMctc->pInstMctc->pTgtTx->pPriv, pMiMctc->pBufRpcTx[pMiMctc->cntResend], 0, lenData);
        if (GOAL_RES_ERR(res)) {
            return res;
        }
    }

    /* build RPC header */
    pMiMctc->lenBufRpcTx[pMiMctc->cntResend] = lenData;

    /* if previous and this frame are empty, don't increase the sequence counter */
    if (!((GOAL_TRUE == pMiMctc->flgRpcPrevEmpty) && (0 == lenData))) {
        pMiMctc->seqRpcLocal = (pMiMctc->seqRpcLocal + 1) % GOAL_MI_MCTC_RPC_MAX_SEQ;
    } else {
        goal_logDbg("previous frame == empty, keeping seq");
    }

    GOAL_MASK_CLR(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_RESEND);
    GOAL_MASK_CLR(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_REQ_ACK);
    goal_logDbg("seqRpcLocal = %d", pMiMctc->seqRpcLocal);
    goal_miMctcRpcSend(pMiMctc, pMiMctc->pBufRpcTx[pMiMctc->cntResend], pMiMctc->lenBufRpcTx[pMiMctc->cntResend]);

    /* update resend */
    pMiMctc->cntResend = (pMiMctc->cntResend + 1) % GOAL_MI_MCTC_RPC_CNT_RESEND;

    /* remove acknowledge flag */
    pMiMctc->flgRpcAck = GOAL_FALSE;

    /* remove data from ringbuffer */
    if (0 != lenData) {
        goal_mctcRbRemove((GOAL_MCTC_RB_T *) pMiMctc->pInstMctc->pTgtTx->pPriv, lenData);
    }

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC Process Loop
 */
void goal_miMctcRpcProcessLoop(
    void *pParam                                /**< loop parameter */
)
{
    GOAL_MI_MCTC_INST_T *pMiMctc = pParam;      /* MI MCTC handle */

    /* process RX data */
    pMiMctc->pInstMctc->pTgtRx->funcRecv(pMiMctc->pInstMctc, pMiMctc->pInstMctc->pTgtRx);

    /* leave if not in run-mode */
    if (GOAL_MI_MCTC_RPC_STATE_RUN != pMiMctc->stateRpc) {
        return;
    }

    /* check if send is permitted */
    if (GOAL_TRUE != goal_miMctcRpcSendAllow(pMiMctc)) {
        return;
    }

    /* process TX data */
    goal_miMctcRpcTxProcess(pMiMctc);
}


/****************************************************************************/
/** MCTC MI - Push data to MCTC stack
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcPush(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    const uint8_t *pData,                       /**< data */
    unsigned int len                            /**< data length */
)
{
    GOAL_STATUS_T res;                          /* result */

    /* check */
    if (NULL == pHdl) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* push data */
    res = goal_mctcPush(pHdl, pData, len);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to push data to MCTC stack");
        return res;
    }

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - Pop data from MCTC stack
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcPop(
    GOAL_MCTC_T    *pHdl,                       /**< MCTC handle */
    uint8_t *pData,                             /**< [out] data */
    unsigned int len                            /**< data length */
)
{
    GOAL_STATUS_T res;                          /* result */

    /* check */
    if (NULL == pHdl) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* pop data */
    res = goal_mctcPop(pHdl, pData, len);
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to pop data to MCTC stack");
        return res;
    }

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC Sync Loop
 */
void goal_miMctcRpcSyncLoop(
    MCTC_INST_T *pMiMctc                        /**< MI MCTC handle */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_BOOL_T flgSetupLocal = GOAL_FALSE;     /* local setup done flag */
    GOAL_BOOL_T flgSetupRemote = GOAL_FALSE;    /* remote setup done flag */
    GOAL_MCTC_T *pHdlMctcTx = NULL;             /* call handle */

    /* leave if not in sync-mode */
    if ((GOAL_MI_MCTC_RPC_STATE_RUN == pMiMctc->stateRpc)
        || (GOAL_MI_MCTC_RPC_STATE_STOP == pMiMctc->stateRpc)) {
        return;
    }

    /* check if send is permitted */
    if (GOAL_TRUE != goal_miMctcRpcSendAllow(pMiMctc)) {
        return;
    }

    /* handle state machine */
    switch (pMiMctc->stateRpc) {

        case GOAL_MI_MCTC_RPC_STATE_RUN_ONCE:

            goal_logDbg("state: RUN_ONCE");

            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_RUN;

            /* check device state of partner device */
            GOAL_MCTC_NEW(pMiMctc);
            GOAL_MCTC_PUSH_REQ(pMiMctc->idInst);
            GOAL_MCTC_SEND_REQ(GOAL_ID_MI_MCTC, GOAL_MCTC_RPC_FUNC_SETUP_STATE_GET);
            GOAL_MCTC_POP_REQ(flgSetupLocal, GOAL_BOOL_T);
            GOAL_MCTC_POP_REQ(flgSetupRemote, GOAL_BOOL_T);
            GOAL_MCTC_RELEASE();

            /* reset to sync state as partner isn't ready for setup */
            if (GOAL_RES_ERR(res)) {
                pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_INIT;
                break;
            }

            /* compare current local state vs reported by partner */
            if (pMiMctc->flgSetupLocal != flgSetupLocal) {

                /* local device needs a reset */
                if (GOAL_TRUE == pMiMctc->flgSetupLocal) {

                    goal_logErr("sync needs local reset to proceed");

                    /* halt RPC */
                    pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_STOP;

                    /* inform callback listeners */
                    goal_miMctcResetCb();

                    break;
                }

                goal_logErr("sync needs remote reset to proceed");

                /* remote reset is needed, stay in sync mode */
                pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_INIT;

                /* inform callback listeners */
                goal_miMctcRemoteResetCb();
                break;
            }

            /* compare current remote state vs reported by partner */
            if (pMiMctc->flgSetupRemote != flgSetupRemote) {

                /* local device needs a reset */
                if (GOAL_TRUE == pMiMctc->flgSetupRemote) {

                    goal_logErr("sync needs local reset to proceed");

                    /* halt RPC */
                    pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_STOP;

                    /* inform callback listeners */
                    goal_miMctcResetCb();

                    break;
                }

                goal_logErr("sync needs remote reset to proceed");

                /* remote reset is needed, stay in sync mode */
                pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_INIT;

                break;
            }

            /* leave if both devices are fully initialized */
            if ((GOAL_TRUE == flgSetupLocal) && (GOAL_TRUE == flgSetupRemote)) {
                break;
            }

            /* mark local setup as done */
            goal_logInfo("RPC state synchronized, running appl_setup");
            pMiMctc->flgStateSync = GOAL_TRUE;

            goal_logInfo("configuring timeout values for peer");

            /* the application controller may configure remote timeouts */
            GOAL_MCTC_NEW(pMiMctc);
            /* push rpc timeout */
            GOAL_MCTC_PUSH_REQ(CONFIG_UGOAL_TIMEOUT_RPC);
            /* push media timeout */
            GOAL_MCTC_PUSH_REQ(CONFIG_UGOAL_TIMEOUT_MEDIA);
            GOAL_MCTC_PUSH_REQ(pMiMctc->idInst);
            GOAL_MCTC_SEND_REQ(GOAL_ID_MI_MCTC, GOAL_MCTC_RPC_FUNC_SETUP_CFG_TOUT);
            /* pop rpc timeout */
            GOAL_MCTC_RELEASE();

            goal_mctcCfgTout(CONFIG_UGOAL_TIMEOUT_RPC);
            goal_mctcToutSet(pMiMctc->pInstMctc, CONFIG_UGOAL_TIMEOUT_RPC);

            /* call application setup */
            res = appl_setup();
            if (GOAL_RES_ERR(res)) {
                break;
            }

            /* inform partner that appl_setup is finished */
            GOAL_MCTC_NEW(pMiMctc);
            GOAL_MCTC_PUSH_REQ(pMiMctc->idInst);
            GOAL_MCTC_SEND_INFO(GOAL_ID_MI_MCTC, GOAL_MCTC_RPC_FUNC_SETUP_DONE);
            GOAL_MCTC_RELEASE();

            /* lock flag access */
            GOAL_LOCK_GET(pMiMctc->pLock);

            /* mark local setup as done */
            goal_logInfo("local setup done");
            pMiMctc->flgSetupLocal = GOAL_TRUE;

            /* register loop function after rpc is synchronized */
            if (GOAL_RES_OK(res)) {
                res = goal_mainLoopReg(appl_loop);
            }
 
            /* lock memory allocation */
            goal_memInitDone();

            /* unlock flag access */
            GOAL_LOCK_PUT(pMiMctc->pLock);

            break;

        /* initialize synchronisation */
        case GOAL_MI_MCTC_RPC_STATE_SYNC_INIT:

            goal_logDbg("state: SYNC_INIT");

            /* reset sync state */
            GOAL_MASK_SET(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_SYNC_REQ);
            GOAL_MASK_CLR(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_SYNC_ACK);
            pMiMctc->seqRpcLocal = 0;
            pMiMctc->seqRpcLocalAck = 0;
            pMiMctc->seqRpcRemoteAck = 0;
            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_REQ;

            /* intended fallthrough */
            GOAL_TARGET_FALLTHROUGH;

        /* request synchronisation from partner */
        case GOAL_MI_MCTC_RPC_STATE_SYNC_REQ:

            goal_logDbg("state: SYNC_REQ");

            /* send RPC sync frame until ACK is received */
            if (!(GOAL_MI_MCTC_RPC_FLG_SYNC_ACK & pMiMctc->flgRpcRemote)) {

                /* send sync request frame */
                goal_miMctcRpcSend(pMiMctc, NULL, 0);

                break;
            }

            /* request acknowledge of first sequence */
            GOAL_MASK_CLR(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_SYNC_REQ);
            GOAL_MASK_SET(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_REQ_ACK);
            pMiMctc->seqRpcLocal = 1;
            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_LOCAL;

            /* intended fallthrough */
            GOAL_TARGET_FALLTHROUGH;

        case GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_LOCAL:

            goal_logDbg("state: SYNC_ACK_LOCAL");

            /* send empty sequence 1 until ACK is received and we confirmed remote sequence */
            if (1 != pMiMctc->seqRpcLocalAck) {

                /* send empty RPC request */
                goal_miMctcRpcSend(pMiMctc, NULL, 0);

                break;
            }

            /* wait for remote sync */
            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_REMOTE;

            break;

        case GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_REMOTE:

            goal_logDbg("state: SYNC_ACK_REMOTE");

            if (0 == pMiMctc->seqRpcRemoteAck) {

                /* send empty RPC request */
                goal_miMctcRpcSend(pMiMctc, NULL, 0);

                break;
            }

            /* enter run mode */
            GOAL_MASK_CLR(pMiMctc->flgRpc, GOAL_MI_MCTC_RPC_FLG_REQ_ACK);
            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_RUN_ONCE;

            break;
    }
}


/****************************************************************************/
/** MCTC MI - RPC Send Allow Check
 *
 * @returns GOAL_STATUS_T
 */
static GOAL_BOOL_T goal_miMctcRpcSendAllow(
    MCTC_INST_T *pMiMctc                /**< MI MCTC handle */
)
{
    /* check active send counter */
    if (GOAL_MI_MCTC_RPC_CNT_RESEND > pMiMctc->cntRpcActive) {
        return GOAL_TRUE;
    }

    /* check send timeout */
    if (pMiMctc->tsRpcTout < GOAL_TIMER_TS_GET()) {
        pMiMctc->cntRpcActive = 0;

        return GOAL_TRUE;
    }

    return GOAL_FALSE;
}

/****************************************************************************/
/** MCTC MI - Call remote function and wait for a result
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcSendReq(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    uint32_t idRpc,                             /**< RPC id */
    uint32_t idFunc                             /**< function id */
)
{
    GOAL_STATUS_T res;                          /* result */
    struct MCTC_INST_T *pMiMctc;        /* MI MCTC handle */

    /* check */
    if (NULL == pHdl) {
        return GOAL_ERR_NULL_POINTER;
    }

    /* refer the MI handle */
    pMiMctc = (struct MCTC_INST_T *) pHdl->pInst->pPriv;

    /* remote call */
    res = goal_mctcSendReq(pHdl, idRpc, idFunc);
    if (GOAL_ERR_TIMEOUT == res) {
        if ((GOAL_MI_MCTC_RPC_STATE_RUN == pMiMctc->stateRpc) && (GOAL_TRUE == pMiMctc->flgStateSync)) {

            goal_logErr("request failed");
        }
    }

    return res;
}


/****************************************************************************/
/** MCTC MI - Call remote function without waiting for a result
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcSendInfo(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    uint32_t idRpc,                             /**< RPC id */
    uint32_t idFunc                             /**< function id */
)
{
    /* check */
    if (NULL == pHdl) {
        return GOAL_ERR_NULL_POINTER;
    }

    goal_logDbg("MCTC info");

    /* remote call */
    return goal_mctcSendInfo(pHdl, idRpc, idFunc);
}


/****************************************************************************/
/** MCTC MI - Release Handle
 *
 * Free an allocated MCTC transfer handle.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcRelease(
    GOAL_MCTC_T *pHdlMctc                      /**< MCTC handle */
)
{
    /* check */
    if (NULL == pHdlMctc) {
        return GOAL_ERR_NULL_POINTER;
    }

    return goal_mctcRelease(pHdlMctc);
}


/****************************************************************************/
/** MCTC MI - DM Partition Read Update Callback
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcDmCbRead(
    void
)
{
    GOAL_STATUS_T res;                          /* result */
    MCTC_INST_T *pMiMctc;                       /* MI MCTC instance */
    uint8_t *pBufRpc = NULL;                    /* RPC buffer */
    GOAL_MI_MCTC_RPC_RX_T *pHdr;                /* RPC header */
    unsigned int valDiff;                       /* difference value */
    uint16_t crc;                               /* crc */

    /* assign instance */
    pMiMctc = (MCTC_INST_T *) &mctcInst;

    /* get partition buffer address */
    pBufRpc = &receiveData[77];

    /* assign frame header */
    pHdr = (GOAL_MI_MCTC_RPC_RX_T *) pBufRpc;

    /* check frame CRC */
    crc = sapi_utilCrcFletcher16(((uint8_t *) pHdr) + sizeof(GOAL_MI_MCTC_RPC_RX_T), pHdr->lenData);
    if (crc != GOAL_le16toh_p(&pHdr->crc_le16)) {
        return GOAL_OK;
    }

    goal_logDbg("received frame: received local ack: %u, local seq: %u, remote seq: %u, my remote ack: %u, flags: 0x%x", pHdr->seqLocalAck, pMiMctc->seqRpcLocal, pHdr->seqRemote, pMiMctc->seqRpcRemoteAck, pHdr->flags);

    /* store remote flags */
    pMiMctc->flgRpcRemote = pHdr->flags;

    /* remove an active item on receive */
    if (0 < pMiMctc->cntRpcActive) {
        pMiMctc->cntRpcActive--;
    }

    /* skip processing if sync mode is requested */
    if (GOAL_MI_MCTC_RPC_FLG_SYNC_REQ & pHdr->flags) {
        if (GOAL_MI_MCTC_RPC_STATE_STOP != pMiMctc->stateRpc) {
            pMiMctc->stateRpc = GOAL_MI_MCTC_RPC_STATE_SYNC_INIT;
            goal_logInfo("peer requested Sync Init");
        }
        return GOAL_OK;
    }

    /* check if an acknowledge must be sent */
    if (GOAL_MI_MCTC_RPC_FLG_REQ_ACK & pHdr->flags) {
        pMiMctc->flgRpcAck = (GOAL_MI_MCTC_RPC_STATE_STOP != pMiMctc->stateRpc) ? GOAL_TRUE : GOAL_FALSE;
    }

    /* accept remote frame if sequence is ascending */
    if (pHdr->seqRemote == ((pMiMctc->seqRpcRemoteAck + 1) % GOAL_MI_MCTC_RPC_MAX_SEQ)) {

        goal_logDbg("remote seq accepted: %u", pHdr->seqRemote);

        /* update remote sequence tracker */
        pMiMctc->seqRpcRemoteAck = pHdr->seqRemote;

        /* put RX data into ringbuffer */
        goal_logDbg("added %u bytes", pHdr->lenData);
        res = goal_mctcRbPut((GOAL_MCTC_RB_T *) mctcInst.pInstMctc->pTgtRx->pPriv, ((uint8_t *) pHdr) + sizeof(GOAL_MI_MCTC_RPC_RX_T), pHdr->lenData);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("failed to put data into RX ringbuffer");
            return GOAL_OK;
        }

        /* send acknowledge */
        pMiMctc->flgRpcAck = GOAL_TRUE;
    }

    /* track local sequence acknowledge */
    valDiff = (pHdr->seqLocalAck >= pMiMctc->seqRpcLocalAck) ? pHdr->seqLocalAck - pMiMctc->seqRpcLocalAck : pHdr->seqLocalAck + GOAL_MI_MCTC_RPC_MAX_SEQ - pMiMctc->seqRpcLocalAck;
    goal_logDbg("current local ack: %u, new local ack: %u, diff: %u", pMiMctc->seqRpcLocalAck, pHdr->seqLocalAck, valDiff);
    if (GOAL_MI_MCTC_RPC_CNT_RESEND >= valDiff) {
        pMiMctc->seqRpcLocalAck = pHdr->seqLocalAck;
    }

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC handler for setup done function
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T som_rpcSetupDoneServer(
    struct GOAL_MCTC_T *pCtc                    /**< MCTC handle */
)
{
    UNUSEDARG(pCtc);

    mctcInst.flgInit = 1;
    goal_logDbg("RPC_MCTC_SETUP_DONE");

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC stack configuration function
 *
 * Configuration function for mctc stack size
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_rpcSetStackMax(
    unsigned int size
)
{
    if (mSizeXfer < size) {
        mSizeXfer = size;
        goal_logInfo("rpc transfer size set to %"FMT_u32, (uint32_t) mSizeXfer);
    }

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC callback function
 *
 * Catch-All handler for RPC calls
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T ugoal_MctcRpc(
    GOAL_MCTC_T *pMctc                          /**< MCTC handle */
)
{
    UNUSEDARG(pMctc);

    /* call rpc function handler [pMctc->idRpc:pmctc->idFunc] */

    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - RPC Setup State Get Callback
 *
 * Request the current initialization state.
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_STATUS_T goal_miMctcCbSetupStateGet(
    GOAL_MCTC_T *pHdlMctcRx                     /**< MCTC handle */
)
{
    MCTC_INST_T *pMiMctc;                       /* instance */
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    uint32_t idInst;                            /* instance id */

    /* instance id */
    GOAL_MCTC_POP_CB(idInst, uint32_t);

    /* assign instance */
    pMiMctc = &mctcInst;
    UNUSEDARG(idInst);

    /* lock flag access */
    GOAL_LOCK_GET(pMiMctc->pLock);

    /* return initialization state */
    GOAL_MCTC_PUSH_CB(pMiMctc->flgSetupLocal);
    GOAL_MCTC_PUSH_CB(pMiMctc->flgSetupRemote);

    /* unlock flag access */
    GOAL_LOCK_PUT(pMiMctc->pLock);

    return res;
}


/****************************************************************************/
/** MCTC MI - Register reset callback
 *
 * register callback for peer requests a reset
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcCbRegReset(
    GOAL_MI_MCTC_CB_RESET_T func                /**< callback function */
)
{
    fnReset = func;
    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - Register remote reset callback
 *
 * register callback for peer requires a reset
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcCbRegRemoteReset(
    GOAL_MI_MCTC_CB_RESET_T func                /**< callback function */
)
{
    fnRemoteReset = func;
    return GOAL_OK;
}

/****************************************************************************/
/** MCTC MI - Register timeout callback
 *
 * register callback for communication timeout detected
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcCbRegToutRx(
    GOAL_MI_MCTC_CB_TIMEOUT_RX_T func           /**< callback function */
)
{
    fnTimeout = func;
    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - Register online callback
 *
 * register callback for communication reastablishement detected
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_miMctcCbRegOnline(
    GOAL_MI_MCTC_CB_ONLINE_T func               /**< callback function */
)
{
    fnOnline = func;
    return GOAL_OK;
}


/****************************************************************************/
/** MCTC MI - call registered online callback
 *
 */
void goal_miMctcOnlineCb(
    void
)
{
    if (NULL != fnOnline) {
        fnOnline(&mctcInst);
    }
}


/****************************************************************************/
/** MCTC MI - call registered offline callback
 *
 */
void goal_miMctcTimeoutCb(
    void
)
{
    if (NULL != fnTimeout) {
        fnTimeout(&mctcInst);
    }
}


/****************************************************************************/
/** MCTC MI - call registered reset callback
 *
 */
void goal_miMctcResetCb(
    void
)
{
    if (NULL != fnReset) {
        fnReset(&mctcInst);
    }
}


/****************************************************************************/
/** MCTC MI - call registered remote reset callback
 *
 */
void goal_miMctcRemoteResetCb(
    void
)
{
    if (NULL != fnRemoteReset) {
        fnRemoteReset(&mctcInst);
    }
}
