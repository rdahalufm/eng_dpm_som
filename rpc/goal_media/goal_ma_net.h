/** @file
 *
 * @brief Generic MA for NET
 *
 * @details
 * This module provides a MA for NET
 *
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */
#ifndef GOAL_MA_NET_H
#define GOAL_MA_NET_H


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_NET_IPV4(a, b, c, d) \
   (((uint32_t) a << 24) | \
    ((uint32_t) b << 16) | \
    ((uint32_t) c << 8) | \
    ((uint32_t) d))

/****************************************************************************/
/* Forward declaration */
/****************************************************************************/
struct GOAL_MA_NET_T;                           /**< MA NET handle */


/****************************************************************************/
/* Typedefs */
/****************************************************************************/

/** network receive callback */
typedef void (*GOAL_MA_NET_CB_T)(
    struct GOAL_MA_NET_T *pMaNet,               /**< net ma handle */
    GOAL_NET_CB_TYPE_T cbType,                  /**< callback type */
    struct GOAL_NET_CHAN_T *pChan,              /**< channel descriptor */
    struct GOAL_BUFFER_T *pBuf                  /**< GOAL buffer */
);

/**< open function prototype */
typedef GOAL_STATUS_T (*GOAL_MA_NET_OPEN) (
    struct GOAL_MA_NET_T *pHdlMaNet             /**< MA handle for NET  */
);

/**< close function prototype */
typedef GOAL_STATUS_T (*GOAL_MA_NET_CLOSE) (
    struct GOAL_MA_NET_T *pHdlMaNet             /**< MA handle for NET  */
);

/**< net ip set function prototype */
typedef GOAL_STATUS_T (*GOAL_MA_NET_IP_SET) (
    struct GOAL_MA_NET_T *pHdlMaNet,            /**< MA handle for NET  */
    uint32_t addrIp,                            /**< IP address */
    uint32_t addrMask,                          /**< subnet mask */
    uint32_t addrGw,                            /**< gateway */
    GOAL_BOOL_T flgTemp                         /**< temporary IP config flag */
);

/**< NET handle instance struct */
typedef struct GOAL_MA_NET_T {
    struct GOAL_MA_NET_T *pNext;                /**< next entry */
    uint32_t id;                                /**< MA ID */
    GOAL_BOOL_T flgUsed;                        /**< used flag */
    GOAL_MA_NET_OPEN fctOpen;                   /**< open NET function */
    GOAL_MA_NET_IP_SET fctSetIp;                /**< ip set function */
    GOAL_MA_NET_CLOSE fctClose;                 /**< close NET function */
    void *pFctNotifyArg;                        /**< notification function argument */
    void *pDrvData;                             /**< driver specific data */
} GOAL_MA_NET_T;


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_maNetDrvReg(
    uint32_t id,                                /**< ID */
    GOAL_MA_NET_T **ppHdlMaNet,                 /**< NET handle ref ptr */
    GOAL_MA_NET_OPEN fOpen,                     /**< open function */
    GOAL_MA_NET_IP_SET fSetIp,                  /**< ip set function */
    GOAL_MA_NET_CLOSE fClose,                   /**< close function */
    void *pDrvData                              /**< driver specific data */
);

GOAL_STATUS_T goal_maNetOpen(
    uint32_t id,                                /**< id of NET handler to use */
    GOAL_MA_NET_T **ppNetHdl                    /**< pointer to store NET handler */
);

GOAL_STATUS_T goal_maNetClose(
    GOAL_MA_NET_T *pNetHdl                      /**< pointer to store NET handler */
);

GOAL_STATUS_T goal_maNetGetById(
    GOAL_MA_NET_T **ppHdlMaNet,                 /**< NET handle ref ptr */
    uint32_t id                                 /**< MA id */
);

GOAL_STATUS_T goal_maNetIpSet(
    GOAL_MA_NET_T *pNetHdl,                     /**< pointer to store NET handler */
    uint32_t addrIp,                            /**< IP address */
    uint32_t addrMask,                          /**< subnet mask */
    uint32_t addrGw,                            /**< gateway */
    GOAL_BOOL_T flgTemp                         /**< temporary IP config flag */
);

#endif /* GOAL_MA_NET_H */
