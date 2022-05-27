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
#ifndef PLAT_DRV_CTC_NET_RPC_H_
#define PLAT_DRV_CTC_NET_RPC_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define RPC_BUFF_SIZE_NET (GOAL_NETBUF_SIZE + 64)
#define GOAL_NET_ID_DEFAULT (0)

#define GOAL_RPC_FUNC_NET_CHAN_CB (1)
#define GOAL_RPC_FUNC_NET_CHAN_ACTIVATE (2)
#define GOAL_RPC_FUNC_NET_IP_SET (3)
#define GOAL_RPC_FUNC_NET_CHAN_NEW (4)
#define GOAL_RPC_FUNC_NET_CHAN_CLOSE (5)
#define GOAL_RPC_FUNC_NET_CHAN_SEND (6)
#define GOAL_RPC_FUNC_NET_SET_OPTION (7)
#define GOAL_RPC_FUNC_NET_CHAN_GET_REMOTE_ADDR (8)
#define GOAL_RPC_FUNC_NET_CHAN_REOPEN (9)

#define CHAN_UDP (1)
#define CHAN_TCP (2)

#endif /* PLAT_DRV_CTC_NET_RPC_H_ */
