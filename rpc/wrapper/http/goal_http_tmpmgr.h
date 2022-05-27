/** @file
 *
 * @brief Goal http template manager
 *
 * This is the goal webserver webpage template manager.
 *
 * @copyright
 * Copyright 2010-2017 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
*/


#ifndef GOAL_HTTP_TMPMGR_H
#define GOAL_HTTP_TMPMGR_H

#include <goal_includes.h>


/****************************************************************************/
/* Defines */
/****************************************************************************/

#define GOAL_HTTP_TMPMGR_TOKEN_OPEN    ((char) '[')
#define GOAL_HTTP_TMPMGR_TOKEN_CLOSE   ((char) ']')

#define GOAL_HTTP_TMPMGR_ERR_STRING    "#ERR#"

#define GOAL_HTTP_TMPMGR_MAX_CNT_LIST      10
#define GOAL_HTTP_TMPMGR_MAX_LEN_PATH      4


/****************************************************************************/
/* Data types */
/****************************************************************************/

/** list structure for template manager */
typedef struct GOAL_HTTP_TMPMGR_LL_T {
    struct GOAL_HTTP_TMPMGR_LL_T *pNext;        /**< pointer to next entry */
    uint32_t listId;                            /**< identifier of list */
    uint32_t cntMemb;                           /**< member count */
    char listName[32];                          /**< list name */
} GOAL_HTTP_TMPMGR_LL_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/

GOAL_STATUS_T goal_httpTmpMgrParse(
    GOAL_HTTP_T *pInst,                         /**< instance pointer */
    GOAL_NET_CHAN_T *pChan,                     /**< channel pointer */
    GOAL_BUFFER_T *pBuf,                        /**< goal buffer */
    GOAL_HTTP_HDL_T hdlRes,                     /**< resource handle */
    const uint8_t *pData,                       /**< data pointer */
    uint32_t lenData,                           /**< data length */
    uint32_t bufOffset                          /**< buffer offset */
);

#endif /* GOAL_HTTP_TMPMGR_H */


