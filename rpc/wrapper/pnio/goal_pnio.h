/** @file
 * @brief
 * GOAL Generic PROFINET Wrapper
 *
 * @details
 * Provides the standard GOAL PROFINET API for applications.
 *
 * @copyright
 * Copyright 2010-2018 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_PNIO_H
#define GOAL_PNIO_H

#if (GOAL_CONFIG_GEN_CTC_CC == 1) || (GOAL_CONFIG_GEN_CTC_CC == 0 && GOAL_CONFIG_GEN_CTC_AC == 0)

/* function is required for CC and non CTC target */

#include <pn_includes.h>

GOAL_STATUS_T goal_pnioResToGoal(
    PN_STATUS_T status                          /**< PROFINET status */
);

PN_STATUS_T goal_pnioResToPnio(
    GOAL_STATUS_T status                        /**< GOAL status */
);
#endif


#include <pn_goal.h>

#endif /* GOAL_PNIO_H */
