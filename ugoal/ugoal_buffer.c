/** @file
 *
 * @brief leightweight dynamic buffer handling
 *
 * This module provides one dynamically allocable buffer
 *
 * @copyright
 * Copyright 2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include "goal_includes.h"

/****************************************************************************/
/* Defines */
/****************************************************************************/
#ifndef UGOAL_BUFFER_SIZE
# define UGOAL_BUFFER_SIZE GOAL_NETBUF_SIZE
#endif

#ifndef UGOAL_BUFFER_CNT
# define UGOAL_BUFFER_CNT 1
#endif


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_BUFFER_T mBuf[UGOAL_BUFFER_CNT];


/****************************************************************************/
/** Initialize buffers
 *
 */
GOAL_STATUS_T goal_queueBufferInit(
    void
)
{
    int idx;                                    /* index */
    GOAL_STATUS_T res;                          /* result */

    for (idx = 0; idx < UGOAL_BUFFER_CNT; idx++) {
        mBuf[idx].bufSize = UGOAL_BUFFER_SIZE;
        mBuf[idx].dataLen = 0;
        mBuf[idx].flags = 0;
        res = goal_memCalloc(&mBuf[idx].ptrData, UGOAL_BUFFER_SIZE);
    }

    return res;
}


/****************************************************************************/
/** Request buffers for allocation at startup
 *
 * This function provides no functionality in uGOAL context.
 *
 */
GOAL_STATUS_T goal_queuePoolBufsReq(
    GOAL_ID_T usageId,                          /**< goal id of user */
    uint16_t bufSize,                           /**< requested buffer size */
    uint16_t numBufFixed,                       /**< required number of buffers */
    uint16_t numBufTemp                         /**< at times required amount of buffers */
) {
    UNUSEDARG(usageId);
    UNUSEDARG(bufSize);
    UNUSEDARG(numBufFixed);
    UNUSEDARG(numBufTemp);

    return GOAL_OK;
}


/****************************************************************************/
/** Get buffer from memory pool queue
 *
 * This functions provides a buffer from memory pool queues. It returns the
 * smalles existing buffer in the pool queues which size is at least the
 * given minimal size.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_queuePoolGetBuf(
    GOAL_BUFFER_T **ppBuf,                      /**< buffer ref ptr */
    uint16_t sizeMin,                           /**< minimal size of requested buffer */
    GOAL_ID_T usage                             /**< buffer usage */
)
{
    GOAL_STATUS_T res = GOAL_ERR_OVERFLOW;      /* result */
    int idx;                                    /* index */

    UNUSEDARG(usage);

    for (idx = 0; idx < UGOAL_BUFFER_CNT; idx++) {
        if (mBuf[idx].flags != 0) {
            continue;
        }
        else if (sizeMin > mBuf[idx].bufSize) {
            continue;
        }
        else {
            *ppBuf = &mBuf[idx];
            mBuf[idx].flags = 1;
            res = GOAL_OK;
            break;
        }
    }

    if (GOAL_RES_ERR(res)) {
        *ppBuf = NULL;
        goal_logErr("no buffer available");
        res = GOAL_ERR_OVERFLOW;
    }

    return res;
}


/****************************************************************************/
/** Release a previously allocated buffer
 *
 * After the buffer is released, the buffer pointer is set to NULL.
 *
 * @returns GOAL_STATUS_T result
 */
GOAL_STATUS_T goal_queueReleaseBuf(
    GOAL_BUFFER_T **ppBuf                       /**< buffer to release */
)
{
    GOAL_STATUS_T res;                          /* result */

    if ((*ppBuf)->flags == 0) {
        goal_logErr("buffer is already freed");
        res = GOAL_ERR_OVERFLOW;
    }
    else {
        (*ppBuf)->flags = 0;
        res = GOAL_OK;
    }

    *ppBuf = NULL;

    return res;
}
