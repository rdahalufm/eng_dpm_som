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


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_ID GOAL_ID_ECAT


/****************************************************************************/
/* Includes */
/****************************************************************************/
#include <goal_includes.h>
#include "goal_ecat.h"
#include <goal_media/goal_mi_mctc.h>
#include "goal_ecat_pdolist.h"


/****************************************************************************/
/** clear pdo mapping list
 *
 * @returns GOAL_STATUS_T result
 */
/****************************************************************************/
GOAL_STATUS_T goal_ecatPdoMapClear(
    GOAL_ECAT_T *pEcat                          /**< EtherCAT handle */
)
{
    GOAL_ECAT_PDO_MAPPING_T *pList[] = {pEcat->pListTxPdo, pEcat->pListRxPdo}; /* PDO mapping lists */
    uint8_t idxList;                            /* list iterator */
    GOAL_ECAT_PDO_MAPPING_T *pEntry;            /* list entry */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    for (idxList = 0; idxList < 2; idxList++) {

        GOAL_LL_FOREACH(pList[idxList], pEntry) {
            pEntry->bMapped = GOAL_FALSE;
            pEntry->offset = 0;
        }
    }

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    res = goal_miDmGroupPartsRemove(GOAL_MI_MCTC_DIR_PEER_TO, GOAL_ID_ECAT);
    if (GOAL_RES_OK(res)) {
        res = goal_miDmGroupPartsRemove(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_ECAT);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_ECAT, &pEcat->dmTxDp, sizeof(GOAL_MI_MCTC_DP_T), 0);
    }
#endif

    return res;
}


/****************************************************************************/
/** add an entry to the pdo mapping list
 *
 * @returns GOAL_STATUS_T result
 */
/****************************************************************************/
GOAL_STATUS_T goal_ecatPdoListAdd(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT instance data */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    uint16_t dtSize,                            /**< data type size */
    uint16_t attr,                              /**< attributes (R/W/mappable,...) */
    uint8_t *pData                              /**< pointer to variable or NULL */
)
{
    GOAL_ECAT_PDO_MAPPING_T *pMapping = NULL;   /* pdo mapping entry */
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    /* populate local pdo mapping list */
    if (attr & EC_OBJATTR_RXPDOMAPPING) {
        res = goal_memCalloc(&pMapping, sizeof(GOAL_ECAT_PDO_MAPPING_T));
        if (GOAL_RES_OK(res)) {
            pMapping->index = index;
            pMapping->subIndex = subIndex;
            pMapping->offset = 0;               /* will be set later by the CC */
            pMapping->size = dtSize;
            pMapping->attr = attr;
            pMapping->pData = pData;

            /* append new entry to list */
            GOAL_LL_APPEND(pEcat->pListRxPdo, pMapping);
        }
    }

    if (attr & EC_OBJATTR_TXPDOMAPPING) {
        res = goal_memCalloc(&pMapping, sizeof(GOAL_ECAT_PDO_MAPPING_T));
        if (GOAL_RES_OK(res)) {
            pMapping->index = index;
            pMapping->subIndex = subIndex;
            pMapping->offset = 0;               /* will be set later by the CC */
            pMapping->size = dtSize;
            pMapping->attr = attr;
            pMapping->pData = pData;

            /* append new entry to list */
            GOAL_LL_APPEND(pEcat->pListTxPdo, pMapping);
        }
    }

    return res;
}


/****************************************************************************/
/** map objects from the pdo mapping list to the data mapper
 *
 * @returns GOAL_STATUS_T result
 */
/****************************************************************************/
GOAL_STATUS_T goal_ecatPdoListMap(
    GOAL_ECAT_T *pEcat,                         /**< EtherCAT handle */
    uint16_t index,                             /**< object index */
    uint8_t subIndex,                           /**< object sub-index */
    GOAL_BOOL_T bTxPdo,                         /**< tx pdo (TRUE) or rx pdo (FALSE) */
    uint16_t objSize,                           /**< object size */
    uint16_t offset                             /**< object offset */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_ECAT_PDO_MAPPING_T *pList = NULL;      /* mapping list */
    GOAL_ECAT_PDO_MAPPING_T *pEntry = NULL;     /* mapping entry */

    if (GOAL_TRUE == bTxPdo) {
        pList = pEcat->pListTxPdo;
    }
    else {
        pList = pEcat->pListRxPdo;
    }

    res = GOAL_ERR_NOT_FOUND;
    GOAL_LL_FOREACH(pList, pEntry) {
        if ((pEntry->index == index) && (pEntry->subIndex == subIndex)) {
            pEntry->bMapped = GOAL_TRUE;
            pEntry->offset = offset;
            pEntry->size = objSize;

#if GOAL_CONFIG_MEDIA_MI_DM == 1
            /* map object to data mapper */
            /* TODO: remove magic number for dp offset */
            if ((GOAL_FALSE == bTxPdo) && (pEntry->attr & EC_OBJATTR_RXPDOMAPPING)) {
                res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_ID_ECAT, &pEntry->dmDataOutput, pEntry->size, pEntry->offset + 4);
                goal_logInfo("mapping object 0x%04x:0x%02x to PEER_FROM, index %"FMT_u32" with offset %d, length %d", pEntry->index, pEntry->subIndex, goal_miDmPartIdxGet(&pEntry->dmDataOutput), pEntry->offset, pEntry->size);
            }

            if ((GOAL_TRUE == bTxPdo)  && (pEntry->attr & EC_OBJATTR_TXPDOMAPPING)) {
                res = goal_miDmPartIdxReg(GOAL_MI_MCTC_DIR_PEER_TO, GOAL_ID_ECAT, &pEntry->dmDataInput, pEntry->size, pEntry->offset);
                goal_logInfo("mapping object 0x%04x:0x%02x to PEER_TO, index %"FMT_u32" with offset %d, length %d", pEntry->index, pEntry->subIndex, goal_miDmPartIdxGet(&pEntry->dmDataInput), pEntry->offset, pEntry->size);
            }
#endif
        }
    }

    return res;
}

