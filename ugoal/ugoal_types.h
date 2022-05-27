/** @file
 *
 * @brief ugoal types
 *
 * @copyright
 * Copyright 2020.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef _UGOAL_TYPES_H_
#define _UGOAL_TYPES_H_


/****************************************************************************/
/* Forward declarations */
/****************************************************************************/ 
/** GOAL_BUFFER_T prototype */
struct GOAL_BUFFER_T;


/****************************************************************************/
/* Type definitions */
/****************************************************************************/ 
typedef unsigned long PtrCast;
#ifndef GOAL_NETBUF_SIZE
# define GOAL_NETBUF_SIZE 1536
#endif

#define MAC_ADDR_LEN                6
typedef uint8_t GOAL_ETH_MAC_ADDR_T[MAC_ADDR_LEN];

#define GOAL_BOOL_T unsigned int
#define GOAL_TRUE 1
#define GOAL_FALSE 0

/**< iterate through linked list */
#define GOAL_LL_FOREACH(pList, pIt)     LL_FOREACH2(pList, pIt, pNext)

/**< put element on start of linked list */
#define GOAL_LL_PREPEND(pList, pElem)   LL_PREPEND2(pList, pElem, pNext)

/**< put element on end of linked list */
#define GOAL_LL_APPEND(pList, pElem)    LL_APPEND2(pList, pElem, pNext)

/**< remove element from linked list */
#define GOAL_LL_DELETE(pList, pElem)    LL_DELETE2(pList, pElem, pNext)

/** generic no-return and no-argument function */
typedef void (* GOAL_FUNC_NORET_T)(void *pArg);
typedef void (* GOAL_FUNC_NORET_NOARG_T)(void);


/**< main loop item */
typedef struct GOAL_MAIN_LOOP_T {
    struct GOAL_MAIN_LOOP_T *pNext;             /**< next pointer */
    GOAL_FUNC_NORET_T pFunc;                    /**< function pointer */
    void *pParam;                               /**< function parameter */
    GOAL_BOOL_T flgExec;                        /**< execution flag */
} GOAL_MAIN_LOOP_T;


/****************************************************************************/
/* Defines */
/****************************************************************************/ 
#define GOAL_OK                         0       /**< success */
#define GOAL_OK_TIMER_RUN               1       /**< timer currently running */
#define GOAL_OK_SHUTDOWN                2       /**< issue normal shutdown */
#define GOAL_OK_SUPPORTED               3       /**< supported */
#define GOAL_OK_DELAYED                 4       /**< delayed */
#define GOAL_OK_ALREADY_INITIALIZED     5       /**< already initialized */
#define GOAL_OK_EXISTS                  6       /**< exists already */
#define GOAL_OK_PARTIAL                 7       /**< partial transfer */
#define GOAL_OK_AVAILABLE               8       /**< resource available */

#define GOAL_ERROR                      (1lu << 31) /**< general error */

#define GOAL_ERR_NULL_POINTER           (GOAL_ERROR | 103) /**< null pointer error */
#define GOAL_ERR_UNSUPPORTED            (GOAL_ERROR | 104) /**< functionality unsupported */
#define GOAL_ERR_WRONG_STATE            (GOAL_ERROR | 105) /**< wrong state */
#define GOAL_ERR_ACCESS                 (GOAL_ERROR | 106) /**< access right violated */
#define GOAL_ERR_ALLOC                  (GOAL_ERROR | 107) /**< failed to allocate memory */
#define GOAL_ERR_WOULDBLOCK             (GOAL_ERROR | 108) /**< resource not available */
#define GOAL_ERR_NODATA                 (GOAL_ERROR | 109) /**< no data to process */
#define GOAL_ERR_FRAME_SEND_FAILED      (GOAL_ERROR | 110) /**< failed to send out an Ethernet frame */
#define GOAL_ERR_LOCK_GET_TIMEOUT       (GOAL_ERROR | 111) /**< timeout while acquiring lock */
#define GOAL_ERR_TARGET_INIT            (GOAL_ERROR | 112) /**< failed to initialize Low Level module */
#define GOAL_ERR_ALLOC_INIT             (GOAL_ERROR | 113) /**< failed to initialize Allocation module */
#define GOAL_ERR_TIMER_INIT             (GOAL_ERROR | 114) /**< failed to initialize Timer module */
#define GOAL_ERR_ETH_INIT               (GOAL_ERROR | 115) /**< failed to initialize Ethernet module */
#define GOAL_ERR_ETH_DUPLEX_GET         (GOAL_ERROR | 116) /**< eth: error reading duplex settings */
#define GOAL_ERR_ETH_SPEED_GET          (GOAL_ERROR | 117) /**< eth: error reading speed settings */
#define GOAL_ERR_ETH_LINK_GET           (GOAL_ERROR | 118) /**< eth: error reading link state */
#define GOAL_ERR_BUFF_GET               (GOAL_ERROR | 119) /**< failed to get a Buffer from a Queue */
#define GOAL_ERR_PARAM                  (GOAL_ERROR | 120) /**< invalid parameter */
#define GOAL_ERR_QUEUE_EMPTY            (GOAL_ERROR | 121) /**< Queue is empty */
#define GOAL_ERR_QUEUE_FULL             (GOAL_ERROR | 122) /**< Queue is full */
#define GOAL_ERR_NVS_READ               (GOAL_ERROR | 123) /**< failed to read from non-volatile memory */
#define GOAL_ERR_NVS_WRITE              (GOAL_ERROR | 124) /**< failed to write to non-volatile memory */
#define GOAL_ERR_IP_SET                 (GOAL_ERROR | 125) /**< failed to set IP address configuration */
#define GOAL_ERR_IP_GET                 (GOAL_ERROR | 126) /**< failed to get IP address configuration */
#define GOAL_ERR_OUT_OF_TIMERS          (GOAL_ERROR | 127) /**< timer module is out of resources */
#define GOAL_ERR_TIMER_NOT_USED         (GOAL_ERROR | 128) /**< timer was not initialized */
#define GOAL_ERR_TIMER_STARTED          (GOAL_ERROR | 129) /**< timer to start is already running */
#define GOAL_ERR_INVALID_FRAME          (GOAL_ERROR | 130) /**< received frame with invalid parameters */
#define GOAL_ERR_OUT_OF_RANGE           (GOAL_ERROR | 131) /**< index/value is out of range */
#define GOAL_ERR_NET_INIT               (GOAL_ERROR | 132) /**< failed to initialize Net module */
#define GOAL_ERR_NET_OPEN               (GOAL_ERROR | 133) /**< failed to open socket */
#define GOAL_ERR_NET_CLOSE              (GOAL_ERROR | 134) /**< failed to close socket */
#define GOAL_ERR_NET_REOPEN             (GOAL_ERROR | 135) /**< failed to reopen socket */
#define GOAL_ERR_NET_SEND               (GOAL_ERROR | 136) /**< failed to send on socket */
#define GOAL_ERR_NET_SEND_CHAN_DISABLED (GOAL_ERROR | 137) /**< failed to send on socket because channel is disabled */
#define GOAL_ERR_NET_OPTION             (GOAL_ERROR | 138) /**< failed to change option of socket */
#define GOAL_ERR_NET_CALLBACK           (GOAL_ERROR | 139) /**< failed to set callback for socket */
#define GOAL_ERR_NET_ACTIVATE           (GOAL_ERROR | 140) /**< failed to activate socket */
#define GOAL_ERR_NET_ADDRESS            (GOAL_ERROR | 141) /**< failed to get remote address */
#define GOAL_ERR_NET_MCAST_ADD          (GOAL_ERROR | 142) /**< failed to add multicast address */
#define GOAL_ERR_NET_MCAST_DEL          (GOAL_ERROR | 143) /**< failed to delete multicast address */
#define GOAL_ERR_OVERFLOW               (GOAL_ERROR | 144) /**< overflow error */
#define GOAL_ERR_TIMER_CREATE           (GOAL_ERROR | 145) /**< failed to create timer */
#define GOAL_ERR_TIMER_START            (GOAL_ERROR | 146) /**< failed to start timer */
#define GOAL_ERR_TIMER_STOP             (GOAL_ERROR | 147) /**< failed to stop timer */
#define GOAL_ERR_TIMER_DELETE           (GOAL_ERROR | 148) /**< failed to delete timer */
#define GOAL_ERR_THREAD_CREATE          (GOAL_ERROR | 149) /**< failed to create thread */
#define GOAL_ERR_THREAD_CLOSE           (GOAL_ERROR | 150) /**< failed to close thread */
#define GOAL_ERR_MAC_GET                (GOAL_ERROR | 151) /**< failed to get MAC address */
#define GOAL_ERR_MAC_SET                (GOAL_ERROR | 152) /**< failed to set MAC address */
#define GOAL_ERR_MAC_DEL                (GOAL_ERROR | 153) /**< failed to delete MAC address */
#define GOAL_ERR_NET_IP_SET             (GOAL_ERROR | 154) /**< failed to set IP configuration */
#define GOAL_ERR_NET_IP_GET             (GOAL_ERROR | 155) /**< failed to get IP configuration */
#define GOAL_ERR_LOCK_WRONG_STATE       (GOAL_ERROR | 156) /**< lock has wrong state */
#define GOAL_ERR_INIT                   (GOAL_ERROR | 157) /**< initialization failed */
#define GOAL_ERR_ALREADY_USED           (GOAL_ERROR | 158) /**< already in use */
#define GOAL_ERR_NOT_INITIALIZED        (GOAL_ERROR | 159) /**< not initialized */
#define GOAL_ERR_TASK_CREATE            (GOAL_ERROR | 160) /**< task: create failed */
#define GOAL_ERR_TASK_EXIT              (GOAL_ERROR | 161) /**< task: exit failed */
#define GOAL_ERR_TASK_JOIN              (GOAL_ERROR | 162) /**< task: join failed */
#define GOAL_ERR_TASK_SLEEP             (GOAL_ERROR | 163) /**< task: sleep failed */
#define GOAL_ERR_TASK_SLEEP_INT         (GOAL_ERROR | 164) /**< task: sleep interrupted  can be resumed */
#define GOAL_ERR_TASK_START             (GOAL_ERROR | 165) /**< task: start failed */
#define GOAL_ERR_TASK_SELF              (GOAL_ERROR | 166) /**< task: get self-id failed */
#define GOAL_ERR_TASK_SUSPEND           (GOAL_ERROR | 167) /**< task: suspend failed */
#define GOAL_ERR_TASK_RESUME            (GOAL_ERROR | 168) /**< task: resume failed */
#define GOAL_ERR_TASK_PRIORITY_SET      (GOAL_ERROR | 169) /**< task: priorty set failed */
#define GOAL_ERR_BUSY                   (GOAL_ERROR | 170) /**< busy */
#define GOAL_ERR_TIMEOUT                (GOAL_ERROR | 171) /**< timeout occured */
#define GOAL_ERR_NOT_FOUND              (GOAL_ERROR | 172) /**< not found */
#define GOAL_ERR_NET_DHCP_START         (GOAL_ERROR | 173) /**< DHCP: start failed */
#define GOAL_ERR_NET_DHCP_STOP          (GOAL_ERROR | 174) /**< DHCP: stop failed */
#define GOAL_ERR_NET_DHCP_RENEW         (GOAL_ERROR | 175) /**< DHCP: renew failed */
#define GOAL_ERR_NET_DHCP_RELEASE       (GOAL_ERROR | 176) /**< DHCP: release failed */
#define GOAL_ERR_NET_DHCP_INFORM        (GOAL_ERROR | 177) /**< DHCP: inform failed */
#define GOAL_ERR_NET_DHCP_ADDR          (GOAL_ERROR | 178) /**< DHCP: address retrieval failed */
#define GOAL_ERR_SPECIFIC               (GOAL_ERROR | 179) /**< specific error set in (meta-) data */
#define GOAL_ERR_EMPTY                  (GOAL_ERROR | 180) /**< selected part is empty */
#define GOAL_ERR_FULL                   (GOAL_ERROR | 181) /**< selected part is full */
#define GOAL_ERR_DELAYED                (GOAL_ERROR | 182) /**< delay error */
#define GOAL_ERR_UNDERFLOW              (GOAL_ERROR | 183) /**< underflow error */
#define GOAL_ERR_NET_DEACTIVATE         (GOAL_ERROR | 184) /**< failed to deactivate socket */
#define GOAL_ERR_NET_SET_SEND           (GOAL_ERROR | 185) /**< failed to set send function for channel */
#define GOAL_ERR_EXISTS                 (GOAL_ERROR | 186) /**< ressource already exists */
#define GOAL_ERR_NOT_EMPTY              (GOAL_ERROR | 187) /**< ressource not empty */
#define GOAL_ERR_TASK_PRIORITY_GET      (GOAL_ERROR | 188) /**< task: priorty get failed */
#define GOAL_ERR_FRAME_IN_TRANSMISSION  (GOAL_ERROR | 189) /**< eth: frame in transmission state */
#define GOAL_ERR_IO                     (GOAL_ERROR | 190) /**< generic: I/O error */
#define GOAL_ERR_UNALIGNED              (GOAL_ERROR | 191) /**< unaligned error */
#define GOAL_ERR_ETH_DUPLEX_SET         (GOAL_ERROR | 192) /**< eth: error writing duplex settings */
#define GOAL_ERR_ETH_SPEED_SET          (GOAL_ERROR | 193) /**< eth: error writing speed settings */
#define GOAL_ERR_ETH_CAPA_GET           (GOAL_ERROR | 194) /**< eth: error reading capabilities */
#define GOAL_ERR_MISMATCH               (GOAL_ERROR | 195) /**< mismatch */
#define GOAL_ERR_WRONG_DIRECTION        (GOAL_ERROR | 196) /**< wrong direction */

#define GOAL_RES_OK(x) (!(x & GOAL_ERROR))      /**< positive result verification */
#define GOAL_RES_ERR(x) (x & GOAL_ERROR)        /**< negative result verification */
#define GOAL_RES_ERR_RET(x, str) \
    if (GOAL_RES_ERR(x)) { \
        goal_logErr("'%s' failed with error 0x%"FMT_x32, str, x); \
        return x; \
    }

#define GOAL_RES_GOAL                   0x00000000 /**< GOAL */
#define GOAL_RES_APPL                   0x00200000 /**< Application */
#define GOAL_RES_PNIO                   0x00300000 /**< PROFINET */
#define GOAL_RES_EIP                    0x00400000 /**< EtherNet/IP */
#define GOAL_RES_EPL                    0x00500000 /**< POWERLINK */
#define GOAL_RES_CO                     0x00600000 /**< CANopen */
#define GOAL_RES_RPC                    0x00700000 /**< Remote Procedure Call */
#define GOAL_RES_ECAT                   0x00800000 /**< EtherCAT */

/* set and clear bit macros
 * explanation: the C standard converts unsigned char operands to integers.
 * Therefore the casting is necessary - otherwise for example IAR will give you
 * the warning:
 *     Remark[Pa091]: operator operates on value promoted to int (with possibly
 *     unexpected result)
 */
#define GOAL_BIT_SET(x, y)      (x |= 1lu << (y))
#define GOAL_BIT_CLR(x, y)      (x &= ~(1lu << (y)))
#define GOAL_BIT_IS_SET(x, y)   (x & (1lu << (y))) ? GOAL_TRUE : GOAL_FALSE
#define GOAL_MASK_SET(x, y)     (x |= (y))
#define GOAL_MASK_CLR(x, y)     (x &= ~(y))
#define GOAL_MASK_IS_SET(x, y)  ((x & (y)) == (y)) ? GOAL_TRUE : GOAL_FALSE

#define GOAL_RES_ID(_id, _res) _res

#define GOAL_STATUS_T uint32_t
#define GOAL_TIMESTAMP_T uint32_t

#define GOAL_LOCK_T void

typedef uint16_t GOAL_ID_T;

#define GOAL_CMP_EQUAL              0


/** network connection type */
typedef enum {
    GOAL_NET_UDP_SERVER,                        /**< UDP server connection */
    GOAL_NET_UDP_CLIENT,                        /**< UDP client connection */
    GOAL_NET_TCP_LISTENER,                      /**< TCP server connection (waiting state) */
    GOAL_NET_TCP,                               /**< active TCP client or server connection */
    GOAL_NET_TCP_CLIENT,                        /**< unconnected TCP client connection */
    GOAL_NET_INTERNAL,                          /**< internal connection between GOAL channels */
} GOAL_NET_TYPE_T;

/** network address */
typedef struct {
    uint32_t      localIp;                      /**< local IP address */
    uint16_t      localPort;                    /**< local port number */
    uint32_t      remoteIp;                     /**< remote IP address */
    uint16_t      remotePort;                   /**< remote port number */
} GOAL_NET_ADDR_T;

/** callback types */
typedef enum {
    GOAL_NET_CB_NEW_DATA,                       /**< callback: data available */
    GOAL_NET_CB_NEW_SOCKET,                     /**< callback: new socket opened */
    GOAL_NET_CB_CLOSING,                        /**< callback: socket closing */
    GOAL_NET_CB_CONNECTED,                      /**< callback: connected to server */
} GOAL_NET_CB_TYPE_T;

/* GOAL net buffer forward declaration */
struct GOAL_NET_CHAN_T;

/** network receive callback */
typedef void (*GOAL_NET_CB_T)(
    GOAL_NET_CB_TYPE_T cbType,                  /**< callback type */
    struct GOAL_NET_CHAN_T *pChan,              /**< channel descriptor */
    struct GOAL_BUFFER_T *pBuf                  /**< GOAL buffer */
);

/** network channel send function */
typedef GOAL_STATUS_T (*GOAL_NET_SEND_FUNC_T)(
    struct GOAL_NET_CHAN_T *pChan,              /**< channel descriptor */
    struct GOAL_BUFFER_T *pBuf                  /**< GOAL buffer */
);

/** network channel close function */
typedef GOAL_STATUS_T (*GOAL_NET_CLOSE_FUNC_T)(
    struct GOAL_NET_CHAN_T *pChan               /**< channel descriptor */
);

typedef struct GOAL_NET_CHAN_T {
    struct GOAL_NET_CHAN_T *pChanSendDir;       /**< next channel in sending direction */
    struct GOAL_NET_CHAN_T *pChanApplDir;       /**< next channel in application direction */
    GOAL_NET_SEND_FUNC_T send;                  /**< channel sending function */
    GOAL_NET_CLOSE_FUNC_T close;                /**< channel closing function */
    GOAL_NET_CB_T callback;                     /**< callback function */
    GOAL_NET_TYPE_T type;                       /**< channel type */
    void *pData;                                /**< generic data pointer */
    GOAL_BOOL_T used;                           /**< channel is in use flag */
    GOAL_BOOL_T active;                         /**< channel is in use flag */
    GOAL_NET_ADDR_T addr;                       /**< net address */
} GOAL_NET_CHAN_T;

/** network option */
typedef enum {
    GOAL_NET_OPTION_NONBLOCK,                   /**< set socket to non-blocking */
    GOAL_NET_OPTION_BROADCAST,                  /**< broadcast reception */
    GOAL_NET_OPTION_TTL,                        /**< set TTL value in IP header */
    GOAL_NET_OPTION_TOS,                        /**< set TOS value in IP header */
    GOAL_NET_OPTION_MCAST_IF,                   /**< choose multicast interface */
    GOAL_NET_OPTION_MCAST_ADD,                  /**< join multicast group */
    GOAL_NET_OPTION_MCAST_DROP,                 /**< leave multicast group  */
    GOAL_NET_OPTION_REUSEADDR,                  /**< make address reusable */
} GOAL_NET_OPTION_T;

/** event types */
typedef uint32_t GOAL_MA_EVENT_T;

typedef enum {
    GOAL_MA_EVENT_RISING_EDGE = 1,              /**< rising edge */
    GOAL_MA_EVENT_FALLING_EDGE = 2              /**< falling edge */
} GOAL_MA_EVENT_EVENT_T;

typedef GOAL_STATUS_T (*GOAL_MA_EVENT_NOTIFY)(
    uint32_t *pEventHdl,                        /**< handle where the event occurred */
    uint32_t id,                                /**< event id */
    GOAL_MA_EVENT_EVENT_T event                 /**< event type */
);

#endif
