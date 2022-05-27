/** @file
 *
 * @brief simple api initial configuration
 *
 * This file lists all default values for some configuration options
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef UGOAL_INITIAL_H_
#define UGOAL_INITIAL_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/ 

/**< efault value for the maximum size of a RPC request
 *
 * for simple fieldbus applications a value of 274
 * is sufficient, however it depends on the module sizes
 * to be handled.
 *
 * 274 bytes are required for a large DCP SetName request with a maximum
 * name length of 240 bytes, thus to get PROFINET conformance.
 */
#define DEFAULT_UGOAL_RPC_RB_SIZE 274
#define DEFAULT_UGOAL_RPC_RB_OVERHEAD 100

#endif /* UGOAL_INITIAL_H_ */
