/** @file
 *
 * @brief  CTC wrapper for DD specific functions
 *
 * @details
 * This module provides a RPC functions
 *
 * @copyright
 * Copyright 2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_DD_RPC_H_
#define GOAL_DD_RPC_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define RPC_BUFF_SIZE_DD (64)

#define GOAL_RPC_FUNC_DD_NEW (1)
#define GOAL_RPC_FUNC_DD_CFG_CUSTOMER_ID (2)
#define GOAL_RPC_FUNC_DD_CFG_MODULE_NAME (3)
#define GOAL_RPC_FUNC_DD_FEATURES_SET (4)
#define GOAL_RPC_FUNC_DD_SESSION_FEATURES_ACTIVATE (5)
#define GOAL_RPC_FUNC_DD_CB (6)
#define GOAL_RPC_FUNC_DD_FILTER_ADD (7)

#endif /* GOAL_DD_RPC_H */
