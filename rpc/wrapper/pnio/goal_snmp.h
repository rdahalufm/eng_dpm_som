/** @file
 *
 * @brief
 * GOAL snmp implementation
 *
 * @details
 * This implementation defines macros und functions used by all possible
 * SNMP stacks.
 *
 * @copyright
 * Copyright 2017 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_SNMP_H
#define GOAL_SNMP_H


/****************************************************************************/
/* configuration */
/****************************************************************************/
#ifndef GOAL_SNMP_MIB_RFC1213_SYS_ONLY
#  define GOAL_SNMP_MIB_RFC1213_SYS_ONLY 0
#endif

#ifndef GOAL_SNMP_MIB_RFC1213_DISABLE
#  define GOAL_SNMP_MIB_RFC1213_DISABLE 0
#endif

#ifndef GOAL_SNMP_MIB_PORT_DISABLE
#  define GOAL_SNMP_MIB_PORT_DISABLE 0
#endif


/****************************************************************************/
/* defines */
/****************************************************************************/
#define GOAL_SNMP_TRUE                  1
#define GOAL_SNMP_FALSE                 2


/****************************************************************************/
/* structures */
/****************************************************************************/
typedef struct GOAL_INSTANCE_SNMP_T {
    GOAL_INSTANCE_HEADER(GOAL_INSTANCE_SNMP_T);
} GOAL_INSTANCE_SNMP_T;


/****************************************************************************/
/* prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_snmpInitImpl(
    void
);

GOAL_STATUS_T goal_snmpNewImpl(
    GOAL_INSTANCE_SNMP_T **ppSnmp,              /**< SNMP instance reference */
    uint32_t id                                 /**< SNMP instance id */
);

#if GOAL_CONFIG_GEN_CTC_CC == 1
# define goal_snmpInit goal_snmpInitCc

GOAL_STATUS_T goal_snmpInitCc(
    void
);
#endif

GOAL_STATUS_T goal_snmpCommSet(
    GOAL_INSTANCE_SNMP_T *pSnmp,                /**< SNMP instance handle */
    char *strReadCommunity,                     /**< read community string */
    char *strWriteCommunity                     /**< write community string */
);

GOAL_STATUS_T goal_snmpTrapsInit(
    GOAL_INSTANCE_SNMP_T *pSnmp,                /**< SNMP instance handle */
    uint32_t trapSink                           /**< trap sink IP address */
);

#if GOAL_CONFIG_GEN_CTC_AC == 0
GOAL_STATUS_T goal_snmpResetToDefault(
    GOAL_INSTANCE_SNMP_T *pSnmp                 /**< SNMP instance handle */
);
#endif

GOAL_STATUS_T goal_snmpGetById(
    GOAL_INSTANCE_SNMP_T **ppSnmp,              /**< [out] SNMP instance reference */
    uint32_t id                                 /**< SNMP instance id */
);


/****************************************************************************/
/* RPC Function and Parameter Mapping */
/****************************************************************************/
/* function list */
#define GOAL_SNMP_FUNC_LIST \
    /*                   id, name,                                  function */                         \
    GOAL_SNMP_FUNC_ENTRY( 0, GOAL_SNMP_FUNC_COMM_SET,               goal_snmpRpcCommSet)                \
    GOAL_SNMP_FUNC_ENTRY( 1, GOAL_SNMP_FUNC_TRAPS_INIT,             goal_snmpRpcTrapsInit)              \
    GOAL_SNMP_FUNC_ENTRY( 2, GOAL_SNMP_FUNC_NEW,                    goal_snmpRpcNew)

/* create function id enum */
#undef GOAL_SNMP_FUNC_ENTRY
#define GOAL_SNMP_FUNC_ENTRY(id, name, ...) name = id,
typedef enum {
    GOAL_SNMP_FUNC_LIST
} GOAL_SNMP_FUNC_ID_T;


/****************************************************************************/
/* Mapping of functions which can be overload */
/****************************************************************************/
#ifndef goal_snmpInit
# define goal_snmpInit goal_snmpInitImpl
#endif

#ifndef goal_snmpNew
# define goal_snmpNew goal_snmpNewImpl
#endif


#endif /* GOAL_SNMP_H */
