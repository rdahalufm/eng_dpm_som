
/** @file
 *
 *  Http webserver channel list  module header
 *
 * This application runs a simple HTTP server that hosts a demo HTML page.
 * It can be accessed via web browser by browsing the IP address of this device.
 *
 * @copyright
 * Copyright 2010-2019 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
*/


#ifndef GOAL_HTTP_IDLIST_H
#define GOAL_HTTP_IDLIST_H

typedef struct GOAL_HTTP_IDLIST_T {
    struct GOAL_HTTP_IDLIST_T *pNext;           /* next channel */
    uint32_t id;                                /* channel id */
    GOAL_NET_CHAN_T *pChannel;                  /* channel handle */
    void *fnCallback;                           /* callback */
} GOAL_HTTP_IDLIST_T;

GOAL_STATUS_T goal_httpChannelId(
    GOAL_HTTP_IDLIST_T *pListChan,              /**< channel list */
    GOAL_NET_CHAN_T *pChanHandle,               /**< channel handle */
    uint32_t *pId                               /**< [out] channel id */
);

GOAL_STATUS_T goal_httpChannelEntry(
    GOAL_HTTP_IDLIST_T *pListChan,              /**< channel list */
    GOAL_NET_CHAN_T *pChanHandle,               /**< channel handle */
    GOAL_HTTP_IDLIST_T **ppEntry                /**< [out] channel list entry */
);

GOAL_STATUS_T goal_httpChannelEntryById(
    GOAL_HTTP_IDLIST_T *pListChan,              /**< channel list */
    uint32_t id,                                /**< channel id */
    GOAL_HTTP_IDLIST_T **ppEntry                /**< [out] channel list entry */
);

#endif

