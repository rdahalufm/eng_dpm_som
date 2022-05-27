/** @file
 *
 * @brief Internal Buffer and Queue Management
 *
 * This module implements buffer handling mechanisms. All buffers are allocated
 * at start.
 *
 * @copyright
 * Copyright 2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */


#ifndef UGOAL_BUFFER_T
#define UGOAL_BUFFER_T


/****************************************************************************/
/* Data types */
/****************************************************************************/
typedef struct GOAL_BUFFER {
    uint16_t bufSize;                           /**< buffer max size */
    uint16_t dataLen;                           /**< real data length */
    uint8_t flags;                              /**< buffer flags */
    uint8_t *ptrData;                           /**< data pointer */
}
GOAL_BUFFER_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_queueBufferInit(
    void
);

GOAL_STATUS_T goal_queuePoolBufsReq(
    GOAL_ID_T usageId,                          /**< goal id of user */
    uint16_t bufSize,                           /**< requested buffer size */
    uint16_t numBufFixed,                       /**< required number of buffers */
    uint16_t numBufTemp                         /**< at times required amount of buffers */
);

GOAL_STATUS_T goal_queuePoolGetBuf(
    GOAL_BUFFER_T **ppBuf,                      /**< buffer ref ptr */
    uint16_t sizeMin,                           /**< minimal size of requested buffer */
    GOAL_ID_T usage                             /**< buffer usage */
);

GOAL_STATUS_T goal_queueReleaseBuf(
    GOAL_BUFFER_T **ppBuf                       /**< buffer to release */
);

#endif /* UGOAL_BUFFER_T */
