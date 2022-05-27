/** @file
 *
 * @brief CCM simple communication layer
 *
 * This module contains functions of the simple API for ccm modules.
 *
 * @copyright
 * Copyright 2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */


#ifndef SAPI_H
#define SAPI_H


#include "ugoal/goal_includes.h"


/****************************************************************************/
/* Data types */
/****************************************************************************/
/**< data provider meta container */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct {
    uint8_t status;                             /**< status */
    uint8_t leds;                               /**< LED state */
    uint16_t cntUpdate;                         /**< update counter */
} GOAL_TARGET_PACKED GOAL_MI_MCTC_DP_T;
GOAL_TARGET_PACKED_STRUCT_POST

/**< SPI cyclic data header */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct {
    uint16_t crc_le16;                          /**< checksum */
    uint8_t seq;                                /**< sequence number */
    uint8_t lenData;                            /**< data length */
} GOAL_TARGET_PACKED GOAL_MI_MCTC_SPI_CYCLIC_T;
GOAL_TARGET_PACKED_STRUCT_POST


/****************************************************************************/
/* Defines */
/****************************************************************************/
/* data provider status */
#define GOAL_MCTC_DP_STATUS_FLG_CONN    (1 << 0) /**< connection signal */
#define GOAL_MCTC_DP_STATUS_FLG_ERR     (1 << 1) /**< error signal */
#define GOAL_MCTC_DP_STATUS_FLG_VALID   (1 << 2) /**< data valid */
#define GOAL_MCTC_DP_STATUS_FLG_SYNC_1  (1 << 3) /**< sync signal 1 */
#define GOAL_MCTC_DP_STATUS_FLG_SYNC_2  (1 << 4) /**< sync signal 2 */

/* data provider LED state */
#define GOAL_MCTC_DP_LED_WINK           (1 << 0) /**< wink LED */
#define GOAL_MCTC_DP_LED_RED_1          (1 << 1) /**< red LED 1 */
#define GOAL_MCTC_DP_LED_RED_2          (1 << 2) /**< red LED 2 */
#define GOAL_MCTC_DP_LED_GREEN_1        (1 << 3) /**< green LED 1 */
#define GOAL_MCTC_DP_LED_GREEN_2        (1 << 4) /**< green LED 2 */

#define GOAL_MI_MCTC_LEN                128      /**< SPI transfer length */


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
uint16_t sapi_utilCrcFletcher16(
    uint8_t const *pData,                       /**< data pointer */
    int count                                   /**< size in 8-bit bytes */
);

void irj45_setLedState(
    uint32_t *pLedStates,                       /**< pointer where lead states are stored */
    uint32_t led,                               /**< the LED to set */
    GOAL_BOOL_T state                           /**< the new state of the LED */
);

GOAL_BOOL_T irj45_getLedState(
    uint32_t *pLedStates,                       /**< pointer to LED states */
    uint32_t led                                /**< LED to retrieve state for */
);

void sapi_loop(
        void
);

#endif /* SIMPLE_API_H */
