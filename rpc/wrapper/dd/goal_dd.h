/** @file
 *
 * @brief Header for device detection
 *
 * @copyright
 * Copyright 2013-2017 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_DD_H
#define GOAL_DD_H


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_DD_MODULE_NAME_LENGTH (20)         /* maximum length of name */

/* mask with all features disabled */
#define GOAL_DD_FEAT_NO ( \
    (1 << GOAL_DD_FEAT_HELLO) | \
    (1 << GOAL_DD_FEAT_WINK) | \
    (1 << GOAL_DD_FEAT_GETLIST) | \
    (1 << GOAL_DD_FEAT_GETCONFIG) | \
    (1 << GOAL_DD_FEAT_SETCONFIG) | \
    (1 << GOAL_DD_FEAT_SETIP))

/* mask with all features enabled */
#define GOAL_DD_FEAT_ALL (0)
#define GOAL_DD_VAR_ALL 0xFFFFFFFF


/****************************************************************************/
/* Data Types */
/****************************************************************************/

typedef uint32_t GOAL_DD_CB_DATA_T;

typedef enum {
    GOAL_DD_CB_ID_WINK                          /**< Callback ID WINK */
} GOAL_DD_CB_ID_T;

typedef enum {
    GOAL_DD_FEAT_HELLO = 0,                     /**< Feature ID HELLO Request */
    GOAL_DD_FEAT_WINK = 1,                      /**< Feature ID WINK Request */
    GOAL_DD_FEAT_GETLIST = 2,                   /**< Feature ID GET LIST Request */
    GOAL_DD_FEAT_GETCONFIG = 3,                 /**< Feature ID GET CONFIG Request */
    GOAL_DD_FEAT_SETCONFIG = 4,                 /**< Feature ID SET CONFIG Request */
    GOAL_DD_FEAT_SETIP = 5                      /**< Feature ID SET IP Request */
} GOAL_DD_FEATURE_ID;

typedef enum {
    GOAL_DD_ACCESS_READ = 0,                    /**< Access read possible */
    GOAL_DD_ACCESS_WRITE = 1,                   /**< Access write possible */
} GOAL_DD_ACCESS_T;

/**< type definition for access filter */
typedef struct GOAL_DD_VAR_T {
    struct GOAL_DD_VAR_T *pNext;                /**< next entry */
    uint32_t modId;                             /**< module id */
    uint32_t varId;                             /**< variable id */
    uint32_t access;                            /**< variable access */
} GOAL_DD_VAR_T;

typedef enum {
    GOAL_DD_ACCESS_FILTER_SET_ALL = 0,          /**< complete access */
    GOAL_DD_ACCESS_FILTER_SET_BASIC = 1,        /**< basic functionality */
    GOAL_DD_ACCESS_FILTER_SET_HIDDEN = 2,       /**< set to disable read of special vars */
} GOAL_DD_ACCESS_FILTER_SET_T;

typedef struct GOAL_DD_FILTER_DESCRIPTION_T {
    struct GOAL_DD_FILTER_DESCRIPTION_T *pNext; /**< next entry */
    GOAL_DD_ACCESS_FILTER_SET_T filterSet;      /**< filter set */
    GOAL_DD_VAR_T *pListVars;                   /**< variable list */
} GOAL_DD_FILTER_DESCRIPTION_T;

struct GOAL_DD_T;

typedef GOAL_STATUS_T (* GOAL_DD_FUNC_CB_T)(
    struct GOAL_DD_T *pHdlDd,                   /**< dd handle */
    GOAL_DD_CB_ID_T cbId,                       /**< callback id */
    GOAL_DD_CB_DATA_T *pCbData                  /**< callback data */
);

typedef struct {
    GOAL_BUFFER_T *pMessageBuf;                /**< message buffer */
    GOAL_DD_FUNC_CB_T dd_callback;             /**< callback function */
    GOAL_NET_CHAN_T *pNetChan;                 /**< network channel */
    uint32_t ddSessionFeatures;                /**< bitmask with enabled features for this session */
    GOAL_DD_FILTER_DESCRIPTION_T *pListAccess; /**< access list */
} GOAL_DD_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_ddInitImpl(
    void
);

GOAL_STATUS_T goal_ddNewImpl(
    GOAL_DD_T **ppHdlDd,                        /**< DD handle */
    uint32_t bitmaskFeatures                    /**< initial features */
);

GOAL_STATUS_T goal_ddCustomerIdSet(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    uint32_t cid                                /**< customer ID */
);

GOAL_STATUS_T goal_ddModuleNameSet(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    uint8_t *str                                /**< module name */
);

GOAL_STATUS_T goal_ddFeaturesSet(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    uint32_t bitmaskFeatures                    /**< bitmask with feature disable bits set */
);

GOAL_STATUS_T goal_ddCallbackReg(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    GOAL_DD_FUNC_CB_T pFunc                     /**< callback function */
);

GOAL_STATUS_T goal_ddSessionFeatureActivate(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    uint32_t bitmaskFeatures                    /**< bitmask with feature enable bits set */
);

GOAL_STATUS_T goal_ddFilterAdd(
    GOAL_DD_T *pHdlDd,                          /**< dd handle */
    GOAL_DD_ACCESS_FILTER_SET_T setId           /**< set id */
);

#if GOAL_CONFIG_GEN_CTC_AC == 1
# include <protos/dd/rpc/goal_dd_rpc_ac.h>
#endif

#if GOAL_CONFIG_GEN_CTC_CC == 1
# include <protos/dd/rpc/goal_dd_rpc_cc.h>
#endif

#ifndef goal_ddInit
# define goal_ddInit goal_ddInitImpl
#endif

#ifndef goal_ddNew
# define goal_ddNew goal_ddNewImpl
#endif

#endif /* GOAL_DD_H */
