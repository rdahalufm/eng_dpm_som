/** @file
 *
 * @brief GOAL MCTC - Common Media Interface
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_MI_MCTC_H
#define GOAL_MI_MCTC_H

#include <goal_includes.h>

#if CONFIG_UGOAL_DATAMAPPER == 1
#include "goal_media/goal_mi_dm.h"
#endif

#define goal_rpcHdlChnDefaultGet(x) (UNUSEDARG(x), GOAL_OK)
#define goal_rpcClose goal_miMctcRelease

/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_MI_MCTC_INST_T MCTC_INST_T

#define GOAL_ID_MI_CTC_DEFAULT 0
#define GOAL_CTC_PRIO_DEFAULT 0
#define GOAL_RPC_TIMEOUT_DEFAULT (5 * GOAL_TIMER_SEC)

#define RPC_ID_MCTC 94

#define RPC_MCTC_SETUP_DONE 1
#define GOAL_MCTC_RPC_FUNC_SETUP_DONE 1
#define RPC_MCTC_SETUP_STATE_GET 2
#define GOAL_MCTC_RPC_FUNC_SETUP_STATE_GET 2
#define GOAL_MCTC_RPC_FUNC_SETUP_CFG_TOUT 3

/* RPC configuration */
#define GOAL_MI_MCTC_RPC_MAX_SEQ 10             /**< maximum sequence */
#define GOAL_MI_MCTC_RPC_CNT_RESEND 1           /**< resend buffer count */
#define GOAL_MI_MCTC_RPC_RECV_TOUT (10 * GOAL_TIMER_MSEC) /**< receive timeout */
#define GOAL_MI_MCTC_RPC_FLG_SYNC_REQ (1 << 0)  /**< sync request flag */
#define GOAL_MI_MCTC_RPC_FLG_SYNC_ACK (1 << 1)  /**< sync acknowledge flag */
#define GOAL_MI_MCTC_RPC_FLG_RESEND (1 << 2)    /**< resend flag */
#define GOAL_MI_MCTC_RPC_FLG_REQ_ACK (1 << 3)   /**< request acknowledge */

#define GOAL_MI_MCTC_RPC_STATE_SYNC_INIT 0      /**< initialize sync */
#define GOAL_MI_MCTC_RPC_STATE_SYNC_REQ 1       /**< request sync */
#define GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_LOCAL 2 /**< local sync acknowledged */
#define GOAL_MI_MCTC_RPC_STATE_SYNC_ACK_REMOTE 3 /**< remote sync acknowledged */
#define GOAL_MI_MCTC_RPC_STATE_RUN 4            /**< run */
#define GOAL_MI_MCTC_RPC_STATE_RUN_ONCE 5       /**< run once */
#define GOAL_MI_MCTC_RPC_STATE_STOP 6           /**< stop */


/****************************************************************************/
/* Datatypes */
/****************************************************************************/
typedef enum {
    RPC_OK = 0,
    RPC_ERR_UNKNOWN
} RPC_STATUS_T;

/**< MI MCTC instance type */
typedef struct MCTC_INST_T {

    GOAL_BOOL_T flgInit;                        /**< initialization flag */

    GOAL_LOCK_T *pLock;                         /**< instance lock */
    GOAL_BOOL_T flgStateSync;                   /**< state sync flag */
    GOAL_BOOL_T flgSetupLocal;                  /**< local setup done flag */
    GOAL_BOOL_T flgSetupRemote;                 /**< remote setup done flag */
    GOAL_BOOL_T flgInfoToutRx;                  /**< remote timeout info tracker */

    uint32_t sizeXferRemote;                    /**< maximum remote transfer size */

    /* RPC sequence counters and trackers */
    GOAL_MCTC_INST_T *pInstMctc;                /**< MCTC instance */
    uint8_t flgRpc;                             /**< RPC flags */
    uint8_t flgRpcRemote;                       /**< RPC remote flags */
    uint8_t seqRpcLocal;                        /**< local seq nr */
    uint8_t seqRpcLocalAck;                     /**< remotely acked local seq nr */
    uint8_t seqRpcRemoteAck;                    /**< acked remote seq nr */
    unsigned int cntResend;                     /**< resend index */
    unsigned int sizeRpc;                       /**< maximum RPC data size */
    uint8_t *pBufRpcTx[GOAL_MI_MCTC_RPC_CNT_RESEND]; /**< RPC buffer cache */
    unsigned int lenBufRpcTx[GOAL_MI_MCTC_RPC_CNT_RESEND]; /**< RPC buffer length */
    unsigned int stateRpc;                      /**< RPC state */
    GOAL_BOOL_T flgRpcPrevEmpty;                /**< previously frame was empty */
    GOAL_BOOL_T flgRpcAck;                      /**< RPC send acknowledge */
    GOAL_TIMESTAMP_T tsRpcTout;                 /**< RPC receive timeout */
    unsigned int cntRpcActive;                  /**< active RPC send items */
    unsigned int idInst;                        /**< instance id */
} MCTC_INST_T;

/**< RPC function type */
typedef GOAL_STATUS_T (* GOAL_RPC_FUNC_T)(
    GOAL_RPC_HDL_T *pHdlRpc                     /**< RPC handle */
);

typedef GOAL_STATUS_T (* GOAL_MI_MCTC_CB_RESET_T)(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
);

typedef GOAL_STATUS_T (* GOAL_MI_MCTC_CB_TIMEOUT_RX_T)(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
);

typedef GOAL_STATUS_T (* GOAL_MI_MCTC_CB_ONLINE_T)(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
);


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_miMctcPop(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    uint8_t *pData,                             /**< [out] data */
    unsigned int len                            /**< data length */
);

GOAL_STATUS_T goal_miMctcPush(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    const uint8_t *pData,                       /**< data */
    unsigned int len                            /**< data length */
);

GOAL_STATUS_T goal_miMctcSendInfo(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    uint32_t idRpc,                             /**< RPC id */
    uint32_t idFunc                             /**< function id */
);

GOAL_STATUS_T goal_miMctcSendReq(
    GOAL_MCTC_T *pHdl,                          /**< MCTC handle */
    uint32_t idRpc,                             /**< RPC id */
    uint32_t idFunc                             /**< function id */
);

GOAL_STATUS_T goal_miMctcRelease(
    GOAL_MCTC_T *pHdlMctc                      /**< MCTC handle */
);

GOAL_STATUS_T goal_rpcSetStackMax(
    unsigned int size
);

GOAL_STATUS_T goal_miMctcOpen(
    GOAL_MCTC_INST_T **ppInst,                  /**< MCTC instance */
    unsigned int id                             /**< instance id */
);

GOAL_STATUS_T goal_miMctcDmCbRead(
        void
);

void goal_miMctcRpcSyncLoop(
    MCTC_INST_T *pMiMctc                        /**< MI MCTC handle */
);

GOAL_STATUS_T goal_miMctcRpcTxProcess(
    MCTC_INST_T *pMiMctc                        /**< MCTC handle */
);

void goal_miMctcRpcProcessLoop(
    void *pParam                                /**< loop parameter */
);

GOAL_STATUS_T goal_miMctcCbRegReset(
    GOAL_MI_MCTC_CB_RESET_T func                /**< callback function */
);

GOAL_STATUS_T goal_miMctcCbRegToutRx(
    GOAL_MI_MCTC_CB_TIMEOUT_RX_T func           /**< callback function */
);

GOAL_STATUS_T goal_miMctcCbRegOnline(
    GOAL_MI_MCTC_CB_ONLINE_T func               /**< callback function */
);

void goal_miMctcOnlineCb(
    void
);

void goal_miMctcTimeoutCb(
    void
);

void goal_miMctcResetCb(
    void
);

GOAL_STATUS_T goal_miMctcCbRegRemoteReset(
    GOAL_MI_MCTC_CB_RESET_T func                /**< callback function */
);

void goal_miMctcRemoteResetCb(
    void
);

#endif
