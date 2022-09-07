/** @file
 *
 * PROFINET Simple I/O Example / HTTP Integration
 *
 * This file controls various components and settings of the Generic Open
 * Abstraction Layer (GOAL).
 *
 * For details see chapter "Build Configuration" in the documentation.
 *
 * @copyright
 * Copyright 2010-2018 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_APPL_HTTP_H
#define GOAL_APPL_HTTP_H
#include "ugoal_types.h"

#define APPL_HTTP_STATE_OFF     0               /**< http webpage: shown state OFF */
#define APPL_HTTP_STATE_OK      1               /**< http webpage: shown state OK */
#define APPL_HTTP_STATE_ERR     2               /**< http webpage: shown state ERR */

GOAL_STATUS_T appl_httpSetup(
    void
);

void appl_httpStateSet(
    uint32_t state                              /**< http state */
);


void goal_setWebData(unsigned char *data, unsigned char len);
unsigned char goal_setWebCmd(void);


#endif /* GOAL_APPL_HTTP_H */
