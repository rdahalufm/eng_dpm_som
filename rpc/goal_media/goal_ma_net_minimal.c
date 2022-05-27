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

#if UGOAL_WRAPPER_NET_MINIMAL == 1

#define GOAL_ID GOAL_ID_MA_NET
#include "goal_includes.h"
#include <ccm_rpc_ac.h>
#include "goal_media/goal_ma_net.h"


/****************************************************************************/
/* Local prototypes */
/****************************************************************************/


/****************************************************************************/
/* Local variables */
/****************************************************************************/


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
    UNUSEDARG(id);
    UNUSEDARG(ppNetHdl);

    return GOAL_OK;
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
    UNUSEDARG(pNetHdl);
    return GOAL_OK;
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
    GOAL_STATUS_T res;                          /* result */
    uint8_t tmpVal;                             /* setting value */

    UNUSEDARG(flgTemp);

    /* set IP address via CM variables */
    res = appl_ccmCfgVarSet(
        12, /* module id net */
        0, /* variable id IP */
        &addrIp,
        sizeof(addrIp)
        );

    /* set IP address via CM variables */
    if (GOAL_RES_OK(res)) {
        res = appl_ccmCfgVarSet(
            12, /* module id net */
            1, /* variable id netmask */
            &addrMask,
            sizeof(addrMask)
            );
    }

    /* set IP address via CM variables */
    if (GOAL_RES_OK(res)) {
        res = appl_ccmCfgVarSet(
            12, /* module id net */
            2, /* variable id netmask */
            &addrGw,
            sizeof(addrGw)
            );
    }

    /* set valid flag */
    if (GOAL_RES_OK(res)) {
        if (GOAL_TRUE == flgTemp) {
            tmpVal = 0;
        }
        else {
            tmpVal = 1;
        }
        res = appl_ccmCfgVarSet(
            12, /* module id net */
            3, /* variable id dhcp */
            &tmpVal,
            sizeof(tmpVal)
            );
    }

    /* commit IP settings  */
    if (GOAL_RES_OK(res)) {
        tmpVal = 1;
        res = appl_ccmCfgVarSet(
            12, /* module id net */
            1000, /* variable id dhcp */
            &tmpVal,
            0   /* woraround for issue with virtual cm variables */
            );
    }

    return res;
}
#endif

