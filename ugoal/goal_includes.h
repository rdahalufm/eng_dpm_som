/** @file
 *
 * @brief platform adaption for avr atmega 2560
 *
 * This module provides platform adaption for the atmega 2560
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_INCLUDES_H
#define GOAL_INCLUDES_H

/* uGOAL Version */
#define UGOAL_VER_MAJ    2                      /**< major version */
#define UGOAL_VER_MIN    1                      /**< minor version */
#define UGOAL_VER_SUB    5                      /**< sub version */


/* standard includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/* externals */
#include <ext/uthash/utlist.h>

/* include some default values which may be used by the application config */
#include "ugoal_initial.h"

/* include application config header */
#include "goal_config.h"

/* overload symbols */
#include "ugoal_overload.h"

/* platform includes */
#include "../pic32/plat.h"

/* ugoal includes */
#include "ugoal_default.h"
#include "goal_id.h"
#include "ugoal_types.h"
#include "ugoal_plat.h"
#include "ugoal_log.h"
#include "ugoal_buffer.h"
#include "../sapi/sapi.h"
#include "ugoal.h"

#if CONFIG_UGOAL_INSTANCE == 1
#include "goal_inst.h"
#endif

#endif /* GOAL_INCLUDES_H */
