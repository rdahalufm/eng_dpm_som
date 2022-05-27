/** @file
 *
 * @brief simple api goal overload defines
 *
 * This file lists all configuration options with it's default value.
 * They can be overwritten by the application.
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef UGOAL_OVERLOAD_H_
#define UGOAL_OVERLOAD_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/ 

static inline void goal_targetSetLeds(uint32_t val) {
    (void) val;
}

#define goal_targetGetButtons(...) 0

#define GOAL_NET_IPV4(a, b, c, d) \
   (((uint32_t) a << 24) | \
    ((uint32_t) b << 16) | \
    ((uint32_t) c << 8) | \
    ((uint32_t) d))

#define goal_maLedGetById(...) GOAL_OK
#define goal_memFree(_ptr) UNUSEDARG(_ptr)

/* misc */
#define goal_targetHalt() { \
    goal_logErr("target halted"); \
    while (1) ; \
}

#define goal_targetReset(...)

#define appl_ccmLogEnable(...) GOAL_OK
#define appl_ccmLogToAcEnable(...) GOAL_OK

#define GOAL_CONFIG_BUF_NUM 1

#endif /* UGOAL_OVERLOAD_H_ */

