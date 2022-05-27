/** @file
 *
 * @brief  CTC wrapper for CCM specific functions
 *
 * @details
 * This module provides a RPC functions
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef APPL_CCM_RPC_H_
#define APPL_CCM_RPC_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define RPC_BUFF_SIZE_CCM (GOAL_NETBUF_SIZE + 64)

#define GOAL_RPC_FUNC_CCM_LOG (1)             /**< log messages to the CC */
#define GOAL_RPC_FUNC_CCM_UPDATE_ALLOW (2)    /**< allow firmware update of CC */
#define GOAL_RPC_FUNC_CCM_UPDATE_DENY (3)     /**< deny firmware update of CC */
#define GOAL_RPC_FUNC_CCM_INFO (4)            /**< get info from CC */
#define GOAL_RPC_FUNC_CCM_FAULT_STATE_SET (5) /**< set behaviour on SPI timeout */
#define GOAL_RPC_FUNC_CCM_COMM_RESET_SET (6)  /**< set behaviour on SPI reset request */
#define GOAL_RPC_FUNC_CCM_LOG_TO_AC (7)       /**< enable logging of messages to AC */
#define GOAL_RPC_FUNC_CCM_UPDATE_INIT (8)     /**< start firmware update */
#define GOAL_RPC_FUNC_CCM_UPDATE_DATA (9)     /**< transfer firmware update data to CC module */
#define GOAL_RPC_FUNC_CCM_UPDATE_EXECUTE (10) /**< execute firmware update or commit (reboots CC module) */
#define GOAL_RPC_FUNC_CCM_UPDATE_STATUS (11)  /**< get firmware update status */
#define GOAL_RPC_FUNC_CCM_FOE_UPDATE_SETTINGS (12) /**< set FoE firmware update settings */
#define GOAL_RPC_FUNC_CCM_ECAT_SSI_UPDATE (13) /**< update eeprom ssi data */
#define GOAL_RPC_FUNC_CCM_UPDATE_EVENT_ENABLE (14) /**< enable generation of fw update events */
#define GOAL_RPC_FUNC_CCM_NETWORK_DEFAULT_UP (15) /**< start default network */
#define GOAL_RPC_FUNC_CCM_NETWORK_EOE_UP (16)  /**< start EoE network */
#define GOAL_RPC_FUNC_CCM_ETH_MAC_ADDRESS (17) /**< configure MAC address */
#define GOAL_RPC_FUNC_CCM_CFG_VAR_GET (18)     /**< read a config variable */
#define GOAL_RPC_FUNC_CCM_CFG_VAR_SET (19)     /**< write a config variable */
#define GOAL_RPC_FUNC_CCM_CFG_VAR_SAVE (20)    /**< save all config variables */


/****************************************************************************/
/* Type definitions */
/****************************************************************************/

typedef enum {
    APPL_CCM_FAULT_STATE_ENTER=0,             /**< disable fieldbus communication on fault */
    APPL_CCM_FAULT_STATE_IGNORE=1             /**< keep fieldbus communication on fault */
} APPL_CCM_FAULT_STATE_T;


#endif /* APPL_CCM_RPC_H */
