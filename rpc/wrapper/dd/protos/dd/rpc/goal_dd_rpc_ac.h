/** @file
 *
 * @brief  CTC wrapper for DD
 *
 * @details
 * This module provides a RPC functionality for DD
 *
 * @copyright
 * Copyright 2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_DD_RPC_AC_H_
#define GOAL_DD_RPC_AC_H_


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_ddRpcInit(
    void
);

GOAL_STATUS_T goal_ddRpcNew(
    GOAL_DD_T **ppHdlDd,                        /**< DD handle */
    uint32_t bitmaskFeatures                    /**< initial features */
);

#define goal_ddInit goal_ddRpcInit
#define goal_ddNew goal_ddRpcNew

#endif /* GOAL_DD_RPC_AC_H_ */
