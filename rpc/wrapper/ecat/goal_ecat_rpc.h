/** @file
 *
 * @brief  CTC wrapper for ECAT specific functions
 *
 * @details
 * This module provides a RPC functions
 *
 * @copyright
 * Copyright 2010-2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_ECAT_RPC_H_
#define GOAL_ECAT_RPC_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define RPC_BUFF_SIZE_ECAT (GOAL_NETBUF_SIZE + 64)

#define GOAL_RPC_FUNC_ECAT_NEW (1)              /**< create new instance  */
#define GOAL_RPC_FUNC_ECAT_CFG_EMERGENCY_ON (2) /**< enable or disable feature */
#define GOAL_RPC_FUNC_ECAT_CFG_EMERGENCY_QUEUE_SIZE (3) /**< set emergency queue size */
#define GOAL_RPC_FUNC_ECAT_CFG_FOE_ENABLE (4)   /**< enable FoE */
#define GOAL_RPC_FUNC_ECAT_CFG_EXPLICIT_DEVICE_ID (5) /**< enable explicit device id */
#define GOAL_RPC_FUNC_ECAT_CFG_BOOTSTRAP (6)    /**< enable Bootstrap */
#define GOAL_RPC_FUNC_ECAT_CFG_DC (7)           /**< enable DC */
#define GOAL_RPC_FUNC_ECAT_PDO_STREAM_SIZE (8)  /**< set PDO stream size */
#define GOAL_RPC_FUNC_ECAT_VERSION_GET (9)      /**< get version */
#define GOAL_RPC_FUNC_ECAT_OBJ_VAL_GET (10)     /**< get object value */
#define GOAL_RPC_FUNC_ECAT_OBJ_VAL_SET (11)     /**< set object value */
#define GOAL_RPC_FUNC_ECAT_OBJ_ADD (12)         /**< add dynamic object */
#define GOAL_RPC_FUNC_ECAT_OBJ_SUB_ADD (13)     /**< add dynamic subindex */
#define GOAL_RPC_FUNC_ECAT_OBJ_NAME_SET (14)    /**< set dynamic object name */
#define GOAL_RPC_FUNC_ECAT_OBJ_SUB_NAME_SET (15) /**< set dynamic subindex name */
#define GOAL_RPC_FUNC_ECAT_DYN_OBJ_FINISH (16)  /**< finish adding of dynamic objects */
#define GOAL_RPC_FUNC_ECAT_ESM_STATE_GET (17)   /**< get esm state */
#define GOAL_RPC_FUNC_ECAT_EMERGENCY_WRITE (18) /**< write emergency message */
#define GOAL_RPC_FUNC_ECAT_DM_DP_ADD       (19) /**< add generic dp to cyclic data */
#define GOAL_RPC_FUNC_ECAT_CB              (20) /**< application callback */
#define GOAL_RPC_FUNC_ECAT_CFG_LED_STATUS_INDICATOR (21) /**< configure led emulation */
#define GOAL_RPC_FUNC_ECAT_PDO_MAP_INDEX_SET (22) /**< set DM index of mapped object */
#define GOAL_RPC_FUNC_ECAT_OBJ_SUB_ADD_RPC (23) /**< add an RPC mapped PDO object */

#define GOAL_ECAT_RPC_PUSH_INST(pInst) \
    if (GOAL_RES_OK(res)) { \
        GOAL_RPC_PUSH(pInst->idInst); \
    }

#define GOAL_ECAT_RPC_POP_INST(_tmp) \
    if (GOAL_RES_OK(res)) { \
        uint32_t idInst = 0; \
        GOAL_RPC_POP(idInst, uint32_t); \
        UNUSEDARG(idInst); \
        if (GOAL_RES_OK(res)) { \
            if ((NULL == pEcatCtcInst) || (NULL == pEcatCtcInst->pHdlInst)) { \
                res = GOAL_ERR_NOT_FOUND; \
            } \
            else { \
                _tmp = pEcatCtcInst->pHdlInst; \
            } \
        } \
    }

#endif /* GOAL_ECAT_RPC_H */
