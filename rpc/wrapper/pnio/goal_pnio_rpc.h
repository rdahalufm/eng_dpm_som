/** @file
 *
 * @brief
 * GOAL Generic PROFINET Wrapper Common RPC Header
 *
 * @details
 * Common RPC header for shared functionality between RPC AC and RPC CC
 * implementation.
 *
 * @copyright
 * Copyright 2010-2018 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_PNIO_RPC_H
#define GOAL_PNIO_RPC_H

#include <goal_media/goal_mi_mctc.h>


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_PNIO_RPC_STACK_SIZE 1024           /**< RPC stack size */

#ifdef UGOAL

#define GOAL_DFL_RPC_NEW() \
    if (GOAL_RES_OK(res)) { \
        if (NULL == pHdlRpcDfl) { \
            goal_miMctcOpen((GOAL_MCTC_INST_T **) &pHdlRpcDfl, 0); \
        } \
        res = goal_rpcNew(&pHdlRpc, pHdlRpcDfl); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC new failed: %"FMT_x32, res); \
        } \
    }

#define GOAL_PNIO_RPC_NEW(pInst) \
    if (GOAL_RES_OK(res)) { \
        res = goal_rpcNew(&pHdlRpc, pInst->pHdlRpcChnPnio); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC new failed: %"FMT_x32, res); \
        } \
    }

#define GOAL_DFL_RPC_CALL(func) \
    if (GOAL_RES_OK(res)) { \
        res = goal_rpcCall(pHdlRpc, GOAL_ID_PNIO, func); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC call failed: %"FMT_x32, res); \
        } \
    }

#define GOAL_PNIO_RPC_CALL(pInst, func) \
    GOAL_RPC_PUSH(pInst->idInst); \
    if (GOAL_RES_OK(res)) { \
        res = goal_rpcCall(pHdlRpc, GOAL_ID_PNIO, func); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC call failed: %"FMT_x32, res); \
        } \
    }

#else
#define GOAL_DFL_RPC_NEW() \
    if (GOAL_RES_OK(res)) { \
        if (NULL == pHdlRpcDfl) { \
            res = goal_instGetById((GOAL_INSTANCE_T **) &pHdlRpcDfl, GOAL_ID_MI_MCTC, GOAL_ID_DEFAULT); \
        } \
        if (GOAL_RES_OK(res)) { \
            res = goal_rpcNew(&pHdlRpc, pHdlRpcDfl); \
            if (GOAL_RES_ERR(res)) { \
                goal_logErr("RPC new failed: %"FMT_x32, res); \
            } \
        } \
    }

#define GOAL_PNIO_RPC_NEW(pInst) \
    if (GOAL_RES_OK(res)) { \
        if (NULL == pInst->pHdlRpcChnPnio) { \
            pInst->pHdlRpcChnPnio = pInst->pHdlPnioMctc; \
        } \
        res = goal_rpcNew(&pHdlRpc, pInst->pHdlRpcChnPnio); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC new failed: %"FMT_x32, res); \
        } \
    }

#define GOAL_DFL_RPC_CALL(func) \
    if (GOAL_RES_OK(res)) { \
        res = goal_rpcCall(pHdlRpc, GOAL_ID_PNIO, func); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC call failed: %"FMT_x32, res); \
        } \
    }

#define GOAL_PNIO_RPC_CALL(pInst, func) \
    GOAL_RPC_PUSH(pInst->idInst); \
    if (GOAL_RES_OK(res)) { \
        res = goal_rpcCall(pHdlRpc, GOAL_ID_PNIO, func); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC call failed: %"FMT_x32, res); \
        } \
    }
#endif

#define GOAL_PNIO_RPC_CLOSE() \
    goal_rpcClose(pHdlRpc)

#define GOAL_PNIO_RPC_PUSH_INST(pInst) \
    if (GOAL_RES_OK(res)) { \
        GOAL_RPC_PUSH(pInst->id); \
    }

#define GOAL_PNIO_RPC_POP_INST(_tmp) \
    if (GOAL_RES_OK(res)) { \
        uint32_t idInst = 0; \
        GOAL_RPC_POP(idInst, uint32_t); \
        if (GOAL_RES_OK(res)) { \
            for (*((GOAL_INSTANCE_T **) &_tmp) = mpListInst->pInst; _tmp; *((GOAL_INSTANCE_T **) &_tmp) = (GOAL_INSTANCE_T *) (((GOAL_INSTANCE_T *) _tmp)->pNext)) { \
                if (idInst == _tmp->idInst) { \
                    break; \
                } \
            } \
            if (NULL == _tmp) { \
                res = GOAL_ERR_NOT_FOUND; \
            } \
        } \
    }


#endif /* GOAL_PNIO_RPC_H */
