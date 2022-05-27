/** @file
 *
 * @brief GOAL Micro Core To Core - UGOAL platform
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_MCTC_PLAT_UGOAL_H
#define GOAL_MCTC_PLAT_UGOAL_H

#include "../../ugoal/goal_includes.h"


/****************************************************************************/
/* Externals */
/****************************************************************************/
void ugoal_loop(
    void
);

void goal_miMctcRpcProcessLoop(
    void *pParam                                /**< loop parameter */
);


/****************************************************************************/
/* Platform support */
/****************************************************************************/

#define GOAL_MEM_CALLOC goal_memCalloc
#define GOAL_UNUSED(_x) ((void)(_x))

#define GOAL_FLETCHER16(_data, _len) goal_mctcFletcher16(_data, _len)
#define GOAL_LOCK_CREATE(...)
#define GOAL_LOCK_GET(...)
#define GOAL_LOCK_GET_NO_RES(...)
#define GOAL_LOCK_PUT(...)
#define GOAL_TIMER_TS_GET plat_getMsTimer
#define GOAL_LOOP() ugoal_loop(); goal_miMctcRpcProcessLoop(pCtc->pInst->pPriv)

#define GOAL_LOG(...)

#endif /* GOAL_MCTC_PLAT_UGOAL_H */
