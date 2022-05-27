/** @file
 *
 * @brief irj45 cyclic data functions
 *
 * This module provides helper functions to evaluate and generate valid
 * cyclic data for irj45 / mctc.
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef _UGOAL_H_
#define _UGOAL_H_

#include "rpc/goal_mctc/goal_mctc.h"
#include <inttypes.h>

#define IRJ45_CRC_OFFSET    0x0007
#define IRJ45_PD_HEADER     4


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define UGOAL 1

/**< configure defines regarding mctc ac or cc configuration */
#define GOAL_CONFIG_GEN_CTC 1
#define GOAL_CONFIG_GEN_CTC_CC 0
#define GOAL_CONFIG_GEN_CTC_AC 1

#define GOAL_ID_MA_LED_DEFAULT 0

#define GOAL_TIMER_MSEC 1
#define GOAL_TIMER_SEC (GOAL_TIMER_MSEC * 1000)

#define GOAL_SNPRINTF snprintf
#define GOAL_STRCMP strcmp
#define GOAL_STRLEN strlen

#define GOAL_MEMCPY memcpy
#define GOAL_MEMCMP memcmp
#define GOAL_MEMMOVE memmove
#define GOAL_MEMSET memset

#define GOAL_le16toh(_val) letoh16(_val)
#define GOAL_le32toh(_val) letoh32(_val)
#define GOAL_le64toh(_val) letoh64(_val)
#define GOAL_htole16(_val) htole16(_val)
#define GOAL_htole32(_val) htole32(_val)
#define GOAL_htole64(_val) htole64(_val)
#define GOAL_le64toh_p(_ptr) letoh64(*_ptr)
#define GOAL_le32toh_p(_ptr) letoh32(*_ptr)
#define GOAL_le16toh_p(_ptr) letoh16(*_ptr)

#ifndef GOAL_htole64_p
# define GOAL_htole64_p(_ptr, _val) *_ptr = htole64(_val)
#endif

#ifndef GOAL_htole32_p
# define GOAL_htole32_p(_ptr, _val) *_ptr = htole32(_val)
#endif

#ifndef GOAL_htole16_p
# define GOAL_htole16_p(_ptr, _val) *_ptr = htole16(_val)
#endif

#ifndef GOAL_htobe32_p
# define GOAL_htobe32_p(_ptr, _val) *_ptr = htobe16(_val)
#endif

#ifndef GOAL_be32toh_p
# define GOAL_be32toh_p(_ptr) betoh32(*_ptr)
#endif

#define swapInt64 SWAPINT64
#define swapInt32 SWAPINT32
#define swapInt16 SWAPINT16

#define FMT_u32 PRIu32
#define FMT_x32 PRIx32
#define FMT_u64 PRIu64
#define GOAL_CASSERT(...)
#define UNUSEDARG (void )


/****************************************************************************/
/* Macros */
/****************************************************************************/
#define ARRAY_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

#if CONFIG_UGOAL_INSTANCE == 0
# define goal_instListNew(_pptr, _id) GOAL_OK ; GOAL_MEM_CALLOC(_pptr, sizeof(GOAL_INSTANCE_LIST_T))
# define goal_instNew(_pptr, _size, _modId, _id, _name) (GOAL_MEM_CALLOC(_pptr, _size), mpListInst->pInst = (GOAL_INSTANCE_T *) *_pptr, mpListInst->idInst = 0, GOAL_OK)
# define GOAL_INSTANCE_FOREACH( _list, _entry) if ((_entry = (typeof(_entry)) _list))
#endif

#define goal_logErr GOAL_LOG_ERR
#define goal_logInfo GOAL_LOG_INFO
#define goal_logDbg GOAL_LOG_DBG
#define goal_logWarn GOAL_LOG_WARN

#define goal_lmLog(_idMod, _logId, _msgId, _par1, _par2, _idLog, _msg) goal_logInfo(_msg)
#define goal_lmLogParamUINT32(...)
#define goal_lmLogFinish()

#define goal_mainStageReg(_stage, _ptr, _phase, _fnct) ugoal_mainStageReg(_ptr, _fnct);
static inline GOAL_STATUS_T ugoal_mainStageReg(void *_ptr, GOAL_STATUS_T (*_fnct)(void)) {
    UNUSEDARG(_ptr);
    return _fnct();
}

#define goal_lockCreate(...) GOAL_OK; GOAL_LOCK_CREATE(...)
#define goal_lockGet(...) ugoal_ok()
#define goal_lockPut(...) ugoal_ok()
#define goal_rpcNew(_pptr, _hdl) goal_mctcNew((GOAL_MCTC_T **) _pptr, (GOAL_MCTC_INST_T *) _hdl)
#define goal_rpcCall(_hdl, _modId, _funcId) goal_miMctcSendReq((GOAL_MCTC_T *) _hdl, _modId, _funcId)
#define goal_timerTsGet GOAL_TIMER_TS_GET

#if CONFIG_UGOAL_MAINLOOP_REG == 0
# define goal_mainLoopReg(_f) ((void) _f, GOAL_OK)
# define goal_mainLoopParamReg(...) GOAL_OK
#else
GOAL_STATUS_T goal_mainLoopParamReg(
    GOAL_FUNC_NORET_T pFunc,                    /**< loop function */
    void *pParam                                /**< function parameter */
);
# define goal_mainLoopReg(_f) goal_mainLoopParamReg((GOAL_FUNC_NORET_T) _f, NULL)
#endif

/**< Load unaligned 16-bit integer (little-endian encoding) */
#define LOAD16LE(p) ( \
   ((uint16_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint16_t)(((uint8_t *)(p))[1]) << 8))
 
/**< Load unaligned 16-bit integer (big-endian encoding) */
#define LOAD16BE(p) ( \
   ((uint16_t)(((uint8_t *)(p))[0]) << 8) | \
   ((uint16_t)(((uint8_t *)(p))[1]) << 0))
 
/**< Load unaligned 24-bit integer (little-endian encoding) */
#define LOAD24LE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 0)| \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 16))
 
/**< Load unaligned 24-bit integer (big-endian encoding) */
#define LOAD24BE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 0))
 
/**< Load unaligned 32-bit integer (little-endian encoding) */
#define LOAD32LE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[3]) << 24))
 
/**< Load unaligned 32-bit integer (big-endian encoding) */
#define LOAD32BE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 24) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[3]) << 0))
 
/**< Load unaligned 64-bit integer (little-endian encoding) */
#define LOAD64LE(p) ( \
   ((uint64_t)(((uint8_t *)(p))[0]) << 0) | \
   ((uint64_t)(((uint8_t *)(p))[1]) << 8) | \
   ((uint64_t)(((uint8_t *)(p))[2]) << 16) | \
   ((uint64_t)(((uint8_t *)(p))[3]) << 24) | \
   ((uint64_t)(((uint8_t *)(p))[4]) << 32) | \
   ((uint64_t)(((uint8_t *)(p))[5]) << 40) | \
   ((uint64_t)(((uint8_t *)(p))[6]) << 48) | \
   ((uint64_t)(((uint8_t *)(p))[7]) << 56))
 
/**< Load unaligned 64-bit integer (big-endian encoding) */
#define LOAD64BE(p) ( \
   ((uint64_t)(((uint8_t *)(p))[0]) << 56) | \
   ((uint64_t)(((uint8_t *)(p))[1]) << 48) | \
   ((uint64_t)(((uint8_t *)(p))[2]) << 40) | \
   ((uint64_t)(((uint8_t *)(p))[3]) << 32) | \
   ((uint64_t)(((uint8_t *)(p))[4]) << 24) | \
   ((uint64_t)(((uint8_t *)(p))[5]) << 16) | \
   ((uint64_t)(((uint8_t *)(p))[6]) << 8) | \
   ((uint64_t)(((uint8_t *)(p))[7]) << 0))
 
/**< Store unaligned 16-bit integer (little-endian encoding) */
#define STORE16LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint16_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint16_t)(a) >> 8) & 0xFF
 
/**< Store unaligned 32-bit integer (big-endian encoding) */
#define STORE16BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint16_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint16_t)(a) >> 0) & 0xFF
 
/**< Store unaligned 24-bit integer (little-endian encoding) */
#define STORE24LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 16) & 0xFF
 
/**< Store unaligned 24-bit integer (big-endian encoding) */
#define STORE24BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 0) & 0xFF
 
/**< Store unaligned 32-bit integer (little-endian encoding) */
#define STORE32LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint32_t)(a) >> 24) & 0xFF
 
/**< Store unaligned 32-bit integer (big-endian encoding) */
#define STORE32BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint32_t)(a) >> 0) & 0xFF
 
/**< Store unaligned 64-bit integer (little-endian encoding) */
#define STORE64LE(a, p) \
   ((uint8_t *)(p))[0] = ((uint64_t)(a) >> 0) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint64_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint64_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint64_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[4] = ((uint64_t)(a) >> 32) & 0xFF, \
   ((uint8_t *)(p))[5] = ((uint64_t)(a) >> 40) & 0xFF, \
   ((uint8_t *)(p))[6] = ((uint64_t)(a) >> 48) & 0xFF, \
   ((uint8_t *)(p))[7] = ((uint64_t)(a) >> 56) & 0xFF
 
/**< Store unaligned 64-bit integer (big-endian encoding) */
#define STORE64BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
   ((uint8_t *)(p))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
   ((uint8_t *)(p))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
   ((uint8_t *)(p))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
   ((uint8_t *)(p))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
   ((uint8_t *)(p))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
   ((uint8_t *)(p))[6] = ((uint64_t)(a) >> 8) & 0xFF, \
   ((uint8_t *)(p))[7] = ((uint64_t)(a) >> 0) & 0xFF
 
/**< Swap a 16-bit integer */
#define SWAPINT16(x) ( \
   (((x) & 0x00FF) << 8) | \
   (((x) & 0xFF00) >> 8))
 
/**< Swap a 32-bit integer */
#define SWAPINT32(x) ( \
   (((x) & 0x000000FFUL) << 24) | \
   (((x) & 0x0000FF00UL) << 8) | \
   (((x) & 0x00FF0000UL) >> 8) | \
   (((x) & 0xFF000000UL) >> 24))
 
/**< Swap a 64-bit integer */
#define SWAPINT64(x) ( \
   (((x) & 0x00000000000000FFULL) << 56) | \
   (((x) & 0x000000000000FF00ULL) << 40) | \
   (((x) & 0x0000000000FF0000ULL) << 24) | \
   (((x) & 0x00000000FF000000ULL) << 8) | \
   (((x) & 0x000000FF00000000ULL) >> 8) | \
   (((x) & 0x0000FF0000000000ULL) >> 24) | \
   (((x) & 0x00FF000000000000ULL) >> 40) | \
   (((x) & 0xFF00000000000000ULL) >> 56))
 
/**< Big-endian machine? */
#ifdef _CPU_BIG_ENDIAN
 
/**< Host byte order to network byte order */
#ifndef HTONS
# define HTONS(value) (value)
#endif

#ifndef HTONL
# define HTONL(value) (value)
#endif

#ifndef htons
# define htons(value) ((uint16_t) (value))
#endif

#ifndef htonl
# define htonl(value) ((uint32_t) (value))
#endif

/**< Host byte order to little-endian byte order */
#define HTOLE16(value) SWAPINT16(value)
#define HTOLE32(value) SWAPINT32(value)
#define HTOLE64(value) SWAPINT64(value)
#define htole16(value) swapInt16((uint16_t) (value))
#define htole32(value) swapInt32((uint32_t) (value))
#define htole64(value) swapInt64((uint64_t) (value))
 
/**< Little-endian byte order to host byte order */
#define LETOH16(value) SWAPINT16(value)
#define LETOH32(value) SWAPINT32(value)
#define LETOH64(value) SWAPINT64(value)
#define letoh16(value) swapInt16((uint16_t) (value))
#define letoh32(value) swapInt32((uint32_t) (value))
#define letoh64(value) swapInt64((uint64_t) (value))
 
/**< Host byte order to big-endian byte order */
#define HTOBE16(value) (value)
#define HTOBE32(value) (value)
#define HTOBE64(value) (value)

#ifndef htobe16
# define htobe16(value) ((uint16_t) (value))
#endif

#ifndef htobe32
# define htobe32(value) ((uint32_t) (value))
#endif

#ifndef htobe64
# define htobe64(value) ((uint64_t) (value))
#endif
 
/**< Big-endian byte order to host byte order */
#define BETOH16(value) (value)
#define BETOH32(value) (value)
#define BETOH64(value) (value)

#ifndef betoh16
# define betoh16(value) ((uint16_t) (value))
#endif

#ifndef betoh32
# define betoh32(value) ((uint32_t) (value))
#endif

#ifndef betoh64
# define betoh64(value) ((uint64_t) (value))
#endif

#else /* _CPU_BIG_ENDIAN */

/**< Host byte order to network byte order */
#ifndef HTONS
# define HTONS(value) SWAPINT16(value)
#endif

#ifndef HTONL
# define HTONL(value) SWAPINT32(value)
#endif

#ifndef htons
# define htons(value) swapInt16((uint16_t) (value))
#endif

#ifndef htonl
# define htonl(value) swapInt32((uint32_t) (value))
#endif

/**< Host byte order to little-endian byte order */
#define HTOLE16(value) (value)
#define HTOLE32(value) (value)
#define HTOLE64(value) (value)

#ifndef htole16
# define htole16(value) ((uint16_t) (value))
#endif

#ifndef htole32
# define htole32(value) ((uint32_t) (value))
#endif

#ifndef htole64
# define htole64(value) ((uint64_t) (value))
#endif
 
/**< Little-endian byte order to host byte order */
#define LETOH16(value) (value)
#define LETOH32(value) (value)
#define LETOH64(value) (value)

#ifndef letoh16
# define letoh16(value) ((uint16_t) (value))
#endif

#ifndef letoh32
# define letoh32(value) ((uint32_t) (value))
#endif

#ifndef letoh64
# define letoh64(value) ((uint64_t) (value))
#endif
 
/**< Host byte order to big-endian byte order */
#define HTOBE16(value) SWAPINT16(value)
#define HTOBE32(value) SWAPINT32(value)
#define HTOBE64(value) SWAPINT64(value)

#ifndef htobe16
# define htobe16(value) swapInt16((uint16_t) (value))
#endif

#ifndef htobe32
# define htobe32(value) swapInt32((uint32_t) (value))
#endif

#ifndef htobe64
# define htobe64(value) swapInt64((uint64_t) (value))
#endif

/**< Big-endian byte order to host byte order */
#define BETOH16(value) SWAPINT16(value)
#define BETOH32(value) SWAPINT32(value)
#define BETOH64(value) SWAPINT64(value)
#define betoh16(value) swapInt16((uint16_t) (value))
#define betoh32(value) swapInt32((uint32_t) (value))
#define betoh64(value) swapInt64((uint64_t) (value))

#endif /* _CPU_BIG_ENDIAN */

unsigned long millis(
    void
);

#define GOAL_STAGE_HANDLER_T uint8_t
#define GOAL_RPC_HDL_CHN_T GOAL_MCTC_T
#define GOAL_RPC_HDL_NONE NULL

#define GOAL_RPC_FUNC_ID uint32_t
/**< still necessary GOAL_RPC_HDL_T MCTC_INST_T ? */
#define GOAL_RPC_HDL_T GOAL_MCTC_T

#if CONFIG_UGOAL_INSTANCE == 0
typedef struct GOAL_INSTANCE_T {
    struct GOAL_INSTANCE_T *pNext;
    unsigned int idInst;
} GOAL_INSTANCE_T;

typedef struct GOAL_INSTANCE_LIST_T {
    GOAL_INSTANCE_T *pInst;
    unsigned int idInst;
} GOAL_INSTANCE_LIST_T;

# define GOAL_INSTANCE_HEADER(_type) uint32_t idInst
#endif /* CONFIG_UGOAL_INSTANCE */

/**< MCTC configuration */
#define GOAL_MI_MCTC_XFER_SIZE 32
#define GOAL_CONFIG_CTC_MESSAGE_SIZE_MAX GOAL_MI_MCTC_XFER_SIZE

/**< Ethernet/IP configuration */
#define GOAL_CONFIG_GEN_RPC 1

/**< mapped 4 bytes process data with protocol configurator */
#define APPL_PDO_LEN         4
#define APPL_PDO_POS         IRJ45_PD_HEADER + APPL_PDO_LEN

/**< mapped generic data provider status */
#define APPL_DPO_LEN         4
#define APPL_DPO_POS         IRJ45_PD_HEADER

/**< change to IRJ45_PD_HEADER + APPL_PDO_LEN + APPL_DPO_LEN? */
#define BUF_LENGTH 128

#define APPL_PDI_LEN         4
#define APPL_PDI_POS         IRJ45_PD_HEADER

/**< LEDs definition for Arduino adapter board */
#define GOAL_MA_LED_LED1_RED     (0)
#define GOAL_MA_LED_LED1_GREEN   (2)
#define GOAL_MA_LED_LED2_RED     (4)
#define GOAL_MA_LED_LED2_GREEN   (6)
#define GOAL_MA_LED_ETHERCAT     (8)
#define GOAL_MA_LED_PROFINET     (10)
#define GOAL_MA_LED_MODBUS       (12)
#define GOAL_MA_LED_ETHERNETIP   (14)
#define GOAL_MA_LED_CANOPEN      (16)


/****************************************************************************/
/* Type definitions */
/****************************************************************************/ 
typedef uint32_t GOAL_MA_LED_T;

typedef enum GOAL_MA_LED_STATE_T {
    GOAL_MA_LED_STATE_OFF = 0,                  /**< LED off */
    GOAL_MA_LED_STATE_ON = 1                    /**< LED on */
} GOAL_MA_LED_STATE_T;

typedef int GOAL_MEM_DENY_HANDLE_T;

static inline GOAL_STATUS_T goal_memDenyDelayHandleGet(GOAL_MEM_DENY_HANDLE_T *_hdl) {
    UNUSEDARG(_hdl);
    return GOAL_OK;
}

/**< RPC TX data header */
typedef struct {
    uint16_t crc_le16;                          /**< checksum */
    uint8_t seqLocal;                           /**< local sequence number */
    uint8_t seqRemoteAck;                       /**< remote sequence number */
    uint8_t lenData;                            /**< data length */
    uint8_t flags;                              /**< flags */
}  __attribute__((packed)) GOAL_MI_MCTC_RPC_TX_T;

/**< RPC RX data header */
typedef GOAL_TARGET_PACKED_PRE struct {
    uint16_t crc_le16;                          /**< checksum */
    uint8_t seqRemote;                          /**< local sequence number */
    uint8_t seqLocalAck;                        /**< remote sequence number */
    uint8_t lenData;                            /**< data length */
    uint8_t flags;                              /**< flags */
}  __attribute__((packed)) GOAL_MI_MCTC_RPC_RX_T;

typedef struct {
    uint8_t checksum[2];                        /**< checksum */
    uint8_t seqLocal;                           /**< local sequence number */
    uint8_t seqRemote;                          /**< remote sequence number */
    uint8_t lenData;                            /**< data length */
    uint8_t flags;                              /**< flags */
    uint8_t data[44];                           /**< rpc data */
} __attribute__((packed)) RPC_T;

typedef struct {
    uint8_t identifier[2];                      /**< rpc identifier */
    uint8_t length[4];                          /**< rpc length */
} __attribute__((packed)) RPC_CALL_HEADER_T;

/**< payload is located between header and footer */
typedef struct { 
    uint8_t idFnct[4];                          /**< function id */
    uint8_t idRpc[4];                           /**< rpc id */
    uint8_t idCtc;                              /**< ctc id */
    uint8_t flags;                              /**< flags */
    uint8_t crc[2];                             /**< crc */
} __attribute__((packed)) RPC_CALL_FOOTER_T;

typedef struct { 
    uint8_t idCtc;                              /**< ctc id */
    uint8_t flags;                              /**< flags */
    uint8_t crc[2];                             /**< crc */
} __attribute__((packed)) RPC_RESP_FOOTER_T;

typedef enum {
    RPC_SYNC_INIT,
    RPC_SYNC_REQUEST,
    RPC_SYNC_ACK,
    RPC_SYNC_SEQ,
    RPC_SYNC_SEQ_ACK,
    RPC_RUN_ONCE,
    RPC_RUN
} RPC_STATE_T;

#define RPC_STACK_SIZE     1024

#define RPC_FLAG_SYNC_REQ (1 << 0)
#define RPC_FLAG_SYNC_ACK (1 << 1)
#define RPC_FLAG_REQ_ACK  (1 << 3)

/**< crcReq = req->checksum[0] | req->checksum[1] << 8; */
#define U16_LETOH(_ar) (_ar[0] | _ar[1] << 8)

/**< rpcLength = rpcHeader->length[0] + (rpcHeader->length[1]<<8) + (rpcHeader->length[2]<<16) + (rpcHeader->length[3]<<24);
 */
#define U32_LETOH(_ar) (_ar[0] + (_ar[1]<<8) + (_ar[2]<<16) + (_ar[3]<<24))
/**<     pData[0] = crc&0xff;
    pData[1] = (crc >> 8)&0xff; */
    
#define U16_HTOLE_P(_dst, _val) { \
    uint8_t *_ptr = (uint8_t *) _dst; \
    _ptr[0] = _val & 0xff; \
    _ptr[1] = (_val >> 8) & 0xff; \
}

#define U32_HTOLE_P(_dst, _val) { \
    uint8_t *_ptr = (uint8_t *) _dst; \
    _ptr[0] = _val & 0xff; \
    _ptr[1] = (_val >> 8) & 0xff; \
    _ptr[2] = (_val >> 16) & 0xff; \
    _ptr[3] = (_val >> 24) & 0xff; \
}


/**< create a new RPC handle */
#define GOAL_RPC_NEW() { \
    if (GOAL_RES_OK(res)) { \
        res = goal_mctcNew(&pHdlRpc, (GOAL_MCTC_INST_T *) pHdlRpcChn); \
        if (GOAL_RES_ERR(res)) { \
            goal_logDbg("failed to create MCTC handle"); \
        } \
    } \
}

/**< allocate a MCTC handle */
#define GOAL_MCTC_NEW(_pInst) \
    if (GOAL_RES_OK(res)) { \
        res = goal_mctcNew(&pHdlMctcTx, _pInst->pInstMctc); \
        if (GOAL_RES_ERR(res)) { \
            pHdlMctcTx = NULL; \
        } \
    }

/**< free a MCTC handle */
#define GOAL_MCTC_RELEASE() \
    if (NULL != pHdlMctcTx) { \
        if (GOAL_RES_OK(res)) { \
            res = goal_miMctcRelease(pHdlMctcTx); \
        } else { \
            goal_miMctcRelease(pHdlMctcTx); \
        } \
    }

/**< close a RPC handle */
#define GOAL_RPC_CLOSE() \
    if (NULL != pHdlRpc) { \
        goal_miMctcRelease((GOAL_MCTC_T *) pHdlRpc); \
    }

/**< push to request handle */
#define GOAL_MCTC_PUSH_REQ(_val) GOAL_MCTC_PUSH(Tx, _val)

/**< push to response handle */
#define GOAL_MCTC_PUSH_CB(_val) GOAL_MCTC_PUSH(Rx, _val)

/**< convert value to little endian and push it to an allocated MCTC handle */
#define GOAL_MCTC_PUSH(_hdl, _val) \
    if (GOAL_RES_OK(res)) { \
        uint32_t _val_le32 = GOAL_htole32((uint32_t) _val); \
        res = goal_miMctcPush(pHdlMctc ## _hdl, (const uint8_t *) &_val_le32, sizeof(uint32_t)); \
        if (GOAL_RES_ERR(res)) { \
            GOAL_LOG_ERR("failed to push value"); \
        } \
    }

/**< pop from request handle */
#define GOAL_MCTC_POP_REQ(_val, _type) GOAL_MCTC_POP(Tx, _val, _type)

/**< pop from response handle */
#define GOAL_MCTC_POP_CB(_val, _type) GOAL_MCTC_POP(Rx, _val, _type)

/**< pop little endian value from an allocated MCTC handle and convert it to given type */
#define GOAL_MCTC_POP(_hdl, _val, _type) \
    if (GOAL_RES_OK(res)) { \
        uint32_t _val_le32; \
        res = goal_miMctcPop(pHdlMctc ## _hdl, (uint8_t *) &_val_le32, sizeof(uint32_t)); \
        if (GOAL_RES_OK(res)) { \
            _val = (_type) GOAL_le32toh(_val_le32); \
        } else { \
            GOAL_LOG_ERR("failed to pop value"); \
        } \
    }
    
/**< send data without waiting for a response */
#define GOAL_MCTC_SEND_INFO(_idRpc, _idFunc) \
    if (GOAL_RES_OK(res)) { \
        res = goal_miMctcSendInfo(pHdlMctcTx, _idRpc, _idFunc); \
    }

/**< send data and wait for a response */
#define GOAL_MCTC_SEND_REQ(_idRpc, _idFunc) \
    if (GOAL_RES_OK(res)) { \
        res = goal_miMctcSendReq(pHdlMctcTx, _idRpc, _idFunc); \
    }
    
/**< convert value to 32-bit little endian and push it */
#define GOAL_RPC_PUSH(goal_rpcVal) { \
            if (GOAL_RES_OK(res)) { \
                uint32_t val32_le = GOAL_htole32((uint32_t) goal_rpcVal); \
                res = goal_miMctcPush((GOAL_MCTC_T *) pHdlRpc, (uint8_t *) &val32_le, sizeof(uint32_t)); \
                if (GOAL_RES_ERR(res)) { \
                    goal_logDbg("RPC push result: 0x%"FMT_x32, res); \
                } \
            } \
        }

/**< pop a 32-bit little endian value and convert it back */
#define GOAL_RPC_POP(goal_rpcVal, goal_rpcDdstType) { \
            if (GOAL_RES_OK(res)) { \
                uint32_t val32_le; \
                res = goal_miMctcPop((GOAL_MCTC_T *) pHdlRpc, (uint8_t *) &val32_le, sizeof(uint32_t)); \
                if (GOAL_RES_OK(res)) { \
                    goal_rpcVal = (goal_rpcDdstType) GOAL_le32toh(val32_le); \
                } else { \
                    goal_logDbg("RPC pop result: 0x%"FMT_x32, res); \
                } \
            } \
        }

/**< push data from pointer to stack */
#define GOAL_RPC_PUSH_PTR(ptr, len) \
    if (GOAL_RES_OK(res)) { \
        res = goal_miMctcPush((GOAL_MCTC_T *)pHdlRpc, (const uint8_t *) ptr, len); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC push ptr failed: %"FMT_x32, res); \
        } \
    }

/**< pop data from stack to pointer */
#define GOAL_RPC_POP_PTR(ptr, len) \
    if (GOAL_RES_OK(res)) { \
        res = goal_miMctcPop((GOAL_MCTC_T *)pHdlRpc, (uint8_t *) ptr, len); \
        if (GOAL_RES_ERR(res)) { \
            goal_logErr("RPC pop ptr failed: %"FMT_x32, res); \
        } \
    } \

#define goal_rpcArgPop(_pHdl, _pData, _lenData) goal_miMctcPop(_pHdl, (uint8_t *) (_pData), _lenData)
#define goal_rpcArgPush(_pHdl, _pData, _lenData) goal_miMctcPush(_pHdl, (uint8_t *) (_pData), _lenData)
#define goal_rpcRegisterService goal_mctcRpcReg
#define goal_rpcSetupChannel(_ppHdl, _id) goal_miMctcOpen((GOAL_MCTC_INST_T **) _ppHdl, _id)
#define goal_rpcStatus(...) GOAL_OK

#define GOAL_MI_MCTC_DIR_PEER_TO 0
#define GOAL_MI_MCTC_DIR_PEER_FROM 1

GOAL_STATUS_T goal_memCalloc(
    void *ptr,                                  /**< data pointer */
    size_t size                                 /**< data length */
);

void irj45_rpc(
    const uint8_t *pReqRpc,                     /**< rpc request */
    int cntReqRpc,                              /**< rpc request length */
    uint8_t *pResRpc,                           /**< rpc response */
    int cntResRpc                               /**< rpc response length */
);

void som_loop(
    void
);

void som_dataCb(
    uint8_t *pReceiveData,
    uint8_t *pSendData
);

GOAL_STATUS_T appl_init(
    void
);

GOAL_STATUS_T appl_setup(
    void
);

void appl_loop(
    void
);

void ugoal_loop(
    void
);

GOAL_STATUS_T ugoal_ok(
    void
);

GOAL_STATUS_T som_init(
        void
);

void goal_memInitDone(
    void
);

GOAL_STATUS_T goal_maLedOpen(
    uint32_t id,                                /**< MA id */
    GOAL_MA_LED_T **ppMaLed                     /**< [out] MA handle */
);

GOAL_STATUS_T goal_maLedSet(
    GOAL_MA_LED_T *pMaLed,                      /**< MA handle */
    uint32_t led,                               /**< led id */
    GOAL_MA_LED_STATE_T state                   /**< led state */
);

GOAL_STATUS_T goal_maEventOpen(
    uint32_t id,                                /**< id of EVENT handler to use */
    GOAL_MA_EVENT_T **ppEventHdl,               /**< pointer to store EVENT handler */
    GOAL_BOOL_T flgAutoStart,                   /**< auto start of event generation */
    GOAL_MA_EVENT_NOTIFY fNotify                /**< notify callback */
);

GOAL_STATUS_T goal_maEventEnable(
    GOAL_MA_EVENT_T *pEventHdl                  /**< MA handle for EVENT */
);

GOAL_STATUS_T goal_maEventDisable(
    GOAL_MA_EVENT_T *pEventHdl                  /**< MA handle for EVENT */
);

#if GOAL_CONFIG_MEDIA_MA_ID == 1

typedef void GOAL_MA_ID_T;                      /**< dummy type for media adatper id */

GOAL_STATUS_T goal_maIdOpen(
    uint32_t id,                                /**< id of ID handler to use */
    GOAL_MA_ID_T **ppIdHdl                      /**< pointer to store ID handler */
);

GOAL_STATUS_T goal_maIdGet(
    GOAL_MA_ID_T *pIdHdl,                       /**< MA handle for ID */
    uint32_t *pId                               /**< [out] id value */
);

GOAL_STATUS_T goal_maIdClose(
    GOAL_MA_ID_T *pIdHdl                        /**< MA handle for ID */
);

/* overwrite function, since there is no handle */
#define goal_maIdGetById(_hdl, ...)  (*_hdl = NULL, GOAL_OK)
#if 0
GOAL_STATUS_T goal_maIdGetById(
    GOAL_MA_ID_T **ppHdlMaId,                   /**< ID handle ref ptr */
    uint32_t id                                 /**< MA id */
);
#endif

#endif

#endif
