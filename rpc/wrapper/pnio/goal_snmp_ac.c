/** @file
 *
 * @brief
 * SNMP Wrapper for CTC RPC on the application core
 *
 * @details
 * simple network protocol stack implementation.
 *
 * @copyright
 * Copyright 2017 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include <goal_includes.h>
#include <goal_snmp.h>
#include <goal_snmp_rpc.h>


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_STAGE_HANDLER_T stageMod;           /**< module stage handler */
static GOAL_RPC_HDL_CHN_T *pHdlSnmpRpc;         /**< PROFINET RPC handle (acyclic data) */


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
static GOAL_STATUS_T goal_snmpInitRpc(
    void
);


/****************************************************************************/
/** SNMP target register config manager variables
 *
 * This function registers config manager variables
 *
 *
 * @retval GOAL_OK successful
 * @retval other fail
 */
GOAL_STATUS_T goal_snmpInit(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* add callback to network stage */
    if (GOAL_RES_OK(res)) {
        res = goal_mainStageReg(GOAL_STAGE_MODULES, &stageMod, GOAL_STAGE_INIT, goal_snmpInitRpc);
    }

    return res;
}


/****************************************************************************/
/** Create SNMP instance
 *
 * @retval GOAL_OK successful
 * @retval other fail
 */
GOAL_STATUS_T goal_snmpNew(
    GOAL_INSTANCE_SNMP_T **ppSnmp,              /**< SNMP instance reference */
    uint32_t id                                 /**< SNMP instance id */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    UNUSEDARG(ppSnmp);

    GOAL_SNMP_RPC_NEW();
    GOAL_RPC_PUSH(id);
    GOAL_SNMP_RPC_CALL(GOAL_SNMP_FUNC_NEW);
    GOAL_SNMP_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Setup SNMP RPC Application Core Functionality
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
static GOAL_STATUS_T goal_snmpInitRpc(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* setup RPC channel for acyclic data exchange */
    res = goal_rpcSetupChannel(&pHdlSnmpRpc, GOAL_ID_MI_CTC_DEFAULT);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to setup RPC channel");
        return res;
    }

    goal_logInfo("SNMP Application Core successfully started");

    return GOAL_OK;
}


/****************************************************************************/
/** Register SNMP community strings
 *
 * Store the given cumminity strings.
 *
 * @returns GOAL_STATUS_T value
 */
GOAL_STATUS_T goal_snmpCommSet(
    GOAL_INSTANCE_SNMP_T *pSnmp,                /**< SNMP instance handle */
    char *strReadCommunity,                     /**< read community string */
    char *strWriteCommunity                     /**< write community string */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */
    uint16_t lenReadCommunity;                  /* read community string length */
    uint16_t lenWriteCommunity;                 /* read community string length */

    UNUSEDARG(pSnmp);

    lenWriteCommunity = (uint16_t) GOAL_STRLEN(strWriteCommunity);
    lenReadCommunity = (uint16_t) GOAL_STRLEN(strReadCommunity);

    GOAL_SNMP_RPC_NEW();
    GOAL_RPC_PUSH_PTR(strWriteCommunity, lenWriteCommunity);
    GOAL_RPC_PUSH(lenWriteCommunity);
    GOAL_RPC_PUSH_PTR(strReadCommunity, lenReadCommunity);
    GOAL_RPC_PUSH(lenReadCommunity);
    GOAL_SNMP_RPC_CALL(GOAL_SNMP_FUNC_COMM_SET);
    GOAL_SNMP_RPC_CLOSE();

    return res;
}


/****************************************************************************/
/** Initializes SNMP traps
 *
 * @returns GOAL_STATUS_T value
 */
GOAL_STATUS_T goal_snmpTrapsInit(
    GOAL_INSTANCE_SNMP_T *pSnmp,                /**< SNMP instance handle */
    uint32_t trapSink                           /**< trap sink IP address */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_RPC_HDL_T *pHdlRpc = GOAL_RPC_HDL_NONE; /* call handle */

    UNUSEDARG(pSnmp);

    GOAL_SNMP_RPC_NEW();
    GOAL_RPC_PUSH(trapSink);
    GOAL_SNMP_RPC_CALL(GOAL_SNMP_FUNC_TRAPS_INIT);
    GOAL_SNMP_RPC_CLOSE();

    return res;
}
