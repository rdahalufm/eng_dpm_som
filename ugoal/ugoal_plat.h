/** @file
 *
 * @brief simple api platform interface
 *
 * This file lists all functions needed by a platform implementation
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef UGOAL_PLAT_T
#define UGOAL_PLAT_T


/****************************************************************************/
/* Define */
/****************************************************************************/ 
#ifndef GOAL_TARGET_FALLTHROUGH
#  if __has_attribute (fallthrough)
#    define GOAL_TARGET_FALLTHROUGH __attribute__((fallthrough))
#  else
#    define GOAL_TARGET_FALLTHROUGH /* fall through */
#  endif
#endif


/****************************************************************************/
/* Function Prototypes */
/****************************************************************************/

void plat_msSleep(
    GOAL_TIMESTAMP_T ms                         /**< milliseconds to sleep */
);


void plat_init(
    void
);

int plat_spiTransfer(
   const char *txBuf,                          /**< [in] transmission buffer */
    char *rxBuf,                                /**< [out] receive buffer */
    int size                                    /**< size of valid buffer sizes */
);

GOAL_TIMESTAMP_T plat_getMsTimer(
    void
);

int plat_ledSet(
    uint32_t state                              /**< led state field */
);

void plat_heapAllocDone(
    void
);

int plat_eventRegister(
    GOAL_BOOL_T flgAutoStart,                   /**< flag enable interrupts */
    GOAL_MA_EVENT_NOTIFY fNotify                /**< notify callback */
);

int plat_eventEnable(
    void
);

int plat_eventDisable(
    void
);

GOAL_STATUS_T plat_idInit(
    void
);

GOAL_STATUS_T plat_idGet(
    uint32_t *pId                               /* [out] id value */
);

#endif /* UGOAL_PLAT_H */
