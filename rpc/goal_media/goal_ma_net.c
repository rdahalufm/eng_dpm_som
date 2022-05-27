/** @file
 *
 * @brief Generic MA for NET
 *
 * @details
 * This module provides a MA for NET
 *
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#define GOAL_ID GOAL_ID_MA_NET
#include "goal_includes.h"
#include "goal_media/goal_ma_net.h"


/****************************************************************************/
/* Local prototypes */
/****************************************************************************/


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_MA_NET_T *pListNet = NULL;          /**< NET list */


/****************************************************************************/
/** Registers a NET MA compliant driver
 *
 * This function is called during board init to register available
 * NET drivers.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maNetDrvReg(
    uint32_t id,                                /**< ID */
    GOAL_MA_NET_T **ppHdlMaNet,                 /**< NET handle ref ptr */
    GOAL_MA_NET_OPEN fOpen,                     /**< open function */
    GOAL_MA_NET_IP_SET fSetIp,                  /**< ip set function */
    GOAL_MA_NET_CLOSE fClose,                   /**< close function */
    void *pDrvData                              /**< driver specific data */
)
{
    GOAL_MA_NET_T *pElem;                       /* spi element */
    GOAL_MA_NET_T *pMaValid = NULL;             /* MA validation element */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* validate that the ID was not registered before */
    res = goal_maNetGetById(&pMaValid, id);
    if (GOAL_RES_OK(res)) {
        goal_logErr("The NET MA with ID %"FMT_u32" is already in use", id);
        return GOAL_ERR_INIT;
    }

    res = goal_memCalloc(ppHdlMaNet, sizeof(GOAL_MA_NET_T));
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Unable to allocate NET MA");
        return res;
    }

    /* initialize the structure items */
    (*ppHdlMaNet)->id = id;
    (*ppHdlMaNet)->pDrvData = pDrvData;
    (*ppHdlMaNet)->fctOpen = fOpen;
    (*ppHdlMaNet)->fctSetIp = fSetIp;
    (*ppHdlMaNet)->fctClose = fClose;

    /* iterate to list end */
    if (NULL != pListNet) {
        for (pElem = pListNet; pElem->pNext; pElem = pElem->pNext);
        /* store NET handle */
        pElem->pNext = *ppHdlMaNet;
    } else {
        /* store NET handle */
        pListNet = *ppHdlMaNet;
    }

    return res;
}


/****************************************************************************/
/** Open a NET MA channel
 *
 * After successful execution, *ppNetHdl contains a pointer to the opened
 * NET channel instance, otherwise the pointer is invalid.
 *
 * @retval GOAL_OK successful
 * @retval GOAL_ERR_NULL_POINTER notify handler was null
 * @retval other failed
 */
GOAL_STATUS_T goal_maNetOpen(
    uint32_t id,                                /**< id of NET handler to use */
    GOAL_MA_NET_T **ppNetHdl                    /**< pointer to store NET handler */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* Return value */

    /* Get NET handler for given ID */
    if (GOAL_RES_OK(res)) {
        res = goal_maNetGetById(ppNetHdl, id);
    }

    /* Check whether handle is already in use */
    if (GOAL_RES_OK(res)) {
        if ((*ppNetHdl)->flgUsed) {
            res = GOAL_ERR_ACCESS;
        }
    }

    /* Invoke open function */
    if (GOAL_RES_OK(res)) {
        res = (*ppNetHdl)->fctOpen(*ppNetHdl);
    }

    /* Mark handle as used */
    if (GOAL_RES_OK(res)) {
        (*ppNetHdl)->flgUsed = GOAL_TRUE;
    }

    return res;
}


/****************************************************************************/
/** Closes an NET channel instance
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maNetClose(
    GOAL_MA_NET_T *pNetHdl                      /**< pointer to store NET handler */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    if (NULL == pNetHdl) {
       res = GOAL_ERR_NULL_POINTER;
    }

    /* Invoke close function */
    if (GOAL_RES_OK(res)) {
        res = (pNetHdl)->fctClose(pNetHdl);
        pNetHdl->flgUsed = GOAL_FALSE;
    }

    return res;
}


/****************************************************************************/
/** Get MA NET by ID
 *
 * This function returns the ID associated MA.
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maNetGetById(
    GOAL_MA_NET_T **ppHdlMaNet,                 /**< NET handle ref ptr */
    uint32_t id                                 /**< MA id */
)
{
    GOAL_MA_NET_T *pListNetIdx = NULL;          /* NET list idx */
    GOAL_STATUS_T res;                          /* result */

    res = GOAL_ERR_NOT_FOUND;

    /* validate the arguments */
    if (NULL == ppHdlMaNet) {
        goal_logErr("MA NET reference is NULL");
        return GOAL_ERR_NULL_POINTER;
    }

    /* search the entry with the correct ID */
    for (pListNetIdx = pListNet; (pListNetIdx); pListNetIdx = pListNetIdx->pNext) {
        if (pListNetIdx->id == id) {
            *ppHdlMaNet = pListNetIdx;
            return GOAL_OK;
        }
    }

    /* no entry was found */
    return res;
}


/****************************************************************************/
/** Set IP Address
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maNetIpSet(
    GOAL_MA_NET_T *pNetHdl,                     /**< pointer to store NET handler */
    uint32_t addrIp,                            /**< IP address */
    uint32_t addrMask,                          /**< subnet mask */
    uint32_t addrGw,                            /**< gateway */
    GOAL_BOOL_T flgTemp                         /**< temporary IP config flag */
)
{
    GOAL_STATUS_T res = GOAL_ERR_NULL_POINTER;  /* result */

    if (NULL != pNetHdl->fctSetIp) {
        res = pNetHdl->fctSetIp(pNetHdl, addrIp, addrMask, addrGw, flgTemp);
    }

    return res;
}
