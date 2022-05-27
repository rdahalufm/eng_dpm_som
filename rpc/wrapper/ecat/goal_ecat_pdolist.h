/** @file
 *
 * @brief  CTC wrapper for ECAT RPC functions
 *
 * @details
 * This module provides a helper functions for CTC wrapper for ECAT
 *
 * @copyright
 * Copyright 2010-2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_ECAT_PDOLIST_H
#define GOAL_ECAT_PDOLIST_H
GOAL_STATUS_T goal_ecatPdoMapClear(
    GOAL_ECAT_T *pEcat                          /**< EtherCAT handle */
);

GOAL_STATUS_T goal_ecatPdoListAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint16_t dtSize,                            /**< data type size */
    uint16_t attr,                              /**< attributes (R/W/mappable,...) */
    uint8_t *pData                              /**< pointer to variable or NULL */
);

GOAL_STATUS_T goal_ecatPdoListMap(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT handle */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    GOAL_BOOL_T bTxPdo,                         /**< tx pdo (TRUE) or rx pdo (FALSE) */
    uint16_t objSize,                           /**< object size */
    uint16_t offset                             /**< object offset */
);

#endif /* GOAL_ECAT_PDOLIST_H */
