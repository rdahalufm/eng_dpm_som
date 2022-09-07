/** @file
 *
 * @brief GOAL Configuration File
 *
 * This file controls various components and settings of the Generic OS
 * Abstraction Layer (GOAL).
 *
 * @copyright
 * Copyright 2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_CONFIG_H
#define GOAL_CONFIG_H

#include <stdio.h>

#define CONFIG_UGOAL_LOGGING_DBG    0
#define CONFIG_UGOAL_LOGGING 1
/* this example does not use the cyclic channel of mctc */
//#define CONFIG_UGOAL_DATAMAPPER 1
#define CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT  4
///* record data maximum length
// *
// * the maximum length supported by the profinet stack is 1116
// */
//#define RECORD_DATA_LENGTH  256
/* increase RPC buffer to transport EIP IO data */
#define CONFIG_UGOAL_RPC_RB_SIZE                1024
#define CONFIG_UGOAL_RPC_RB_ENTRIES             2


///* size of ring buffer entries (default 274)
// *
// * To allow transportation of RECORD_DATA_LENGTH bytes record data this
// * size needs to be increased
// */
//#if RECORD_DATA_LENGTH + DEFAULT_UGOAL_RPC_RB_OVERHEAD > DEFAULT_UGOAL_RPC_RB_SIZE
//# define CONFIG_UGOAL_RPC_RB_SIZE (RECORD_DATA_LENGTH + DEFAULT_UGOAL_RPC_RB_OVERHEAD)
//#endif

/* number of RPC handles (default 2)
 *
 * To allow record reading and writing an additional handle is required
 */
#define CONFIG_UGOAL_RPC_HANDLES 3

#endif /* GOAL_CONFIG_H */
