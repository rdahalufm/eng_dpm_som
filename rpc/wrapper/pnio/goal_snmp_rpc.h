/** @file
 *
 * @brief
 * GOAL Generic SNMP Wrapper Common RPC Header
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

#ifndef GOAL_SNMP_RPC_H
#define GOAL_SNMP_RPC_H

#include <goal_media/goal_mi_mctc.h>


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_SNMP_RPC_STACK_SIZE 1024           /**< RPC stack size */

#define GOAL_SNMP_RPC_NEW() if (GOAL_RES_OK(res)) { res = goal_rpcNew(&pHdlRpc, pHdlSnmpRpc); if (GOAL_RES_ERR(res)) { goal_logErr("RPC new failed: %"FMT_x32, res); } }
#define GOAL_SNMP_RPC_CALL(func) if (GOAL_RES_OK(res)) { res = goal_rpcCall(pHdlRpc, GOAL_ID_SNMP, func); if (GOAL_RES_ERR(res)) { goal_logErr("RPC call failed: %"FMT_x32, res); } }
#define GOAL_SNMP_RPC_CLOSE() goal_rpcClose(pHdlRpc)

#endif /* GOAL_SNMP_RPC_H */
