/** @file
 *
 * @brief  CTC wrapper for net
 *
 * @details
 * This module provides a MA for networking over CTC
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef PLAT_DRV_CTC_NET_H_
#define PLAT_DRV_CTC_NET_H_

#include <goal_media/goal_ma_net.h>
#include "ctc_net_rpc.h"


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_netRpcInit(
    uint32_t id                                 /**< id for MA instance */
);

#endif /* PLAT_DRV_CTC_NET_H_ */
