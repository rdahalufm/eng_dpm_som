/** @file
 *
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

#ifndef PN_GOAL_H
#define PN_GOAL_H

#include <goal_includes.h>
#if (GOAL_CONFIG_GEN_CTC == 1)
#  include <goal_media/goal_mi_mctc.h>
#endif

#if GOAL_CONFIG_MEDIA_MI_DM == 1
#  include <goal_media/goal_mi_dm.h>
#endif


/****************************************************************************/
/* SNMP support */
/****************************************************************************/
#if GOAL_CONFIG_SNMP == 1
#  include <goal_snmp.h>
#else
typedef struct GOAL_INSTANCE_SNMP_T {
    GOAL_INSTANCE_HEADER(GOAL_INSTANCE_SNMP_T);
} GOAL_INSTANCE_SNMP_T;
#endif


/****************************************************************************/
/* Configuration */
/****************************************************************************/
#if GOAL_CONFIG_GEN_CTC_AC == 0
#  define GOAL_CONFIG_PNIO_LOCAL 1
#elif GOAL_CONFIG_GEN_CTC_CC == 1
#  define GOAL_CONFIG_PNIO_LOCAL 1
#else
#  define GOAL_CONFIG_PNIO_LOCAL 0
#endif

#ifndef GOAL_CONFIG_PNIO_NEW_IO_DAP
#  define GOAL_CONFIG_PNIO_NEW_IO_DAP 0
#endif


/****************************************************************************/
/* Constants */
/****************************************************************************/
/* status code areas */
#define GOAL_PNIO_RES_OFS                   (GOAL_RES_PNIO + 1) /* PN_STATUS_T */

#define GOAL_PNIO_CB_DATA_MAX               11  /**< max count of callback data */

/* flags */
#define GOAL_PNIO_FLG_AUTO_GEN GOAL_TRUE        /**< auto-generate flag */

/* IOxS states */
#define GOAL_PNIO_IOXS_GOOD                 0x80 /**< IOxS state good */
#define GOAL_PNIO_IOPS_SUBST_ACTIVE         0x01 /**< IOPS subst active */
#define GOAL_PNIO_IOXS_STATE_BY_SUBSLOT     0x00 /**< IOxS state by subslot */
#define GOAL_PNIO_IOXS_STATE_BY_SLOT        0x20 /**< IOxS state by slot */
#define GOAL_PNIO_IOXS_STATE_BY_DEVICE      0x40 /**< IOxS state by device */
#define GOAL_PNIO_IOXS_STATE_BY_CONTROLLER  0x60 /**< IOxS state by controller */
#define GOAL_PNIO_IOXS_STATE_BY_MASK        0x60 /**< IOxS state by mask */
#define GOAL_PNIO_IOXS_STATE_RESERVED_BITS  0x1E /**< IOxS states reserved bits (must be zero) */

/* Alarm priorities */
#define GOAL_PNIO_ALARM_PRIO_HIGH           0
#define GOAL_PNIO_ALARM_PRIO_LOW            1

/* Alarm types */
#define GOAL_PNIO_ALARM_TYPE_DIAG           0x0001
#define GOAL_PNIO_ALARM_TYPE_PROCESS        0x0002

/* Busy handles */
#define GOAL_PNIO_REC_BUSY_IDX_UNDEF        -1

/* Diagnosis */
#define GOAL_PNIO_DIAG_HANDLE_ERR           -1  /**< diagnosis handle invalid */
#define GOAL_PNIO_DIAG_CHAN_NUM_SUBMODULE   0x8000 /**< submodule channel */

#define GOAL_PNIO_DIAG_USI_MANUFACT_BEG     0x0000
#define GOAL_DIAG_USI_MANUFACT_END          0x7fff

/* Software revision prefix */
/*
 * V - for an officially released version
 * R - for Revision
 * P - for Prototype
 * U - for Under Test (Field Test)
 * T - for Test Device
 */
#define GOAL_PNIO_SWREV_OFFICIAL            'V'
#define GOAL_PNIO_SWREV_REVISION            'R'
#define GOAL_PNIO_SWREV_PROTOTYPE           'P'
#define GOAL_PNIO_SWREV_UNDERTEST           'U'
#define GOAL_PNIO_SWREV_TESTDEV             'T'

/**< IOxS length */
#define GOAL_PNIO_LEN_IOXS                  1

/* GOAL PROFINET Subslot Substitution Mode */
#define GOAL_PNIO_SUBSLOT_SUBST_MODE_ZERO 0     /**< outputs are set to zero */
#define GOAL_PNIO_SUBSLOT_SUBST_MODE_LAST 1     /**< last data provided by callback */
#define GOAL_PNIO_SUBSLOT_SUBST_MODE_REPLACE 2  /**< replacement data provided by callback */
#define GOAL_PNIO_SUBSLOT_SUBST_MODE_VALID 3    /**< valid data provided by callback */

/* GOAL PROFINET Subslot SubmoduleState.IdentInfo */
#define GOAL_PNIO_SUBSLOT_STATE_GOOD 0          /**< good submodule */
#define GOAL_PNIO_SUBSLOT_STATE_SUBST 1         /**< substitute submodule */

/* GOAL PROFINET Conformance Classes */
#define GOAL_PNIO_CC_A 0                        /**< PROFINET CC-A */
#define GOAL_PNIO_CC_B 1                        /**< PROFINET CC-B */

/* GOAL PROFINET APDU Status Defines */
#define GOAL_PNIO_APDU_DS_STATE_PRIMARY     (1 << 0)
#define GOAL_PNIO_APDU_DS_REDUNDANCY_BCK_NONE_PRIM (1 << 1)
#define GOAL_PNIO_APDU_DS_REDUNDANCY_PRIM_IS_BCK (1 << 1)
#define GOAL_PNIO_APDU_DS_DATAVALID_VALID   (1 << 2)
#define GOAL_PNIO_APDU_DS_PROVIDERSTATE_RUN (1 << 4)
#define GOAL_PNIO_APDU_DS_STATION_PROBLEM_INDICATOR (1 << 5)
#define GOAL_PNIO_APDU_DS_IGNORE_DATASTATUS (1 << 7)


/****************************************************************************/
/* Instance Configuration */
/****************************************************************************/
#define GOAL_PNIO_CFG_FLG_DCP_FACTORY_RESET_DISABLE    GOAL_FALSE /* flgDcpFactoryResetDisable */
#define GOAL_PNIO_CFG_FLG_DCP_ACCEPT_MIXCASE_STATION   GOAL_FALSE /* flgDcpAcceptMixcaseStation */
#define GOAL_PNIO_CFG_ID_VENDOR             0x028c /* idVendor */
#define GOAL_PNIO_CFG_ID_DEVICE             0x0001 /* idDevice */
#define GOAL_PNIO_CFG_STR_VENDOR            "port GmbH" /* strVendor */
#define GOAL_PNIO_CFG_STR_PORT              "TestPort" /* strPort */
#define GOAL_PNIO_CFG_STR_SYSTEM            "PROFINET System" /* strSystem */
#define GOAL_PNIO_CFG_STR_ID_ORDER          "00210" /* strIdOrder */
#define GOAL_PNIO_CFG_STR_NUM_SERIAL        "20074" /* strNumSerial */
#define GOAL_PNIO_CFG_ID_REV_HW             0x0001 /* idRevHw */
#define GOAL_PNIO_CFG_CHR_REV_SW_PREFIX     GOAL_PNIO_SWREV_PROTOTYPE /* chrRevSwPrefix */
#define GOAL_PNIO_CFG_ID_REV_SW_FUNC_ENH    0x50 /* idRevSwFuncEnh */
#define GOAL_PNIO_CFG_ID_REV_SW_BUGFIX      0x03 /* idRevSwBugfix */
#define GOAL_PNIO_CFG_ID_REV_SW_INT_CHG     0x18 /* idRevSwIntChg */
#define GOAL_PNIO_CFG_ID_REV_SW_REV_CNT     0x0000 /* idRevSwRevCnt */
#define GOAL_PNIO_CFG_STR_IM_1_TAG_FUNC     "                                " /* strIm1TagFunc */
#define GOAL_PNIO_CFG_STR_IM_1_TAG_LOC      "                      " /* strIm1TagLoc */
#define GOAL_PNIO_CFG_STR_IM_2_DATE         "                " /* strIm2Date */
#define GOAL_PNIO_CFG_STR_IM_3_DESC         "                                                      " /* strIm3Desc */
#define GOAL_PNIO_CFG_STR_IM_4_SIG          "                                                      " /* strIm4Sig */
#define GOAL_PNIO_CFG_FLG_DEV_DAP_SIMPLE    GOAL_TRUE /* flgDevDapSimple */
#define GOAL_PNIO_CFG_ID_DEV_DAP_API        0 /* idDevDapApi */
#define GOAL_PNIO_CFG_ID_DEV_DAP_SLOT       0 /* idDevDapSlot */
#define GOAL_PNIO_CFG_ID_DEV_DAP_SUBSLOT    1 /* idDevDapSubslot */
#define GOAL_PNIO_CFG_ID_DEV_DAP_MOD        0x01 /* idDevDapMod */
#define GOAL_PNIO_CFG_ID_DEV_DAP_SUBMOD     0x01 /* idDevDapSubmod */
#define GOAL_PNIO_CFG_FLG_NET_LINK_SAFETY   GOAL_TRUE /* flgNetLinkSafety */
#define GOAL_PNIO_CFG_FLG_CB_NEW_IO_DATA    GOAL_FALSE /* flgCbNewIoData */
#define GOAL_PNIO_CFG_FLG_LLDP_ORG_EXT      GOAL_TRUE /* flgLldpOrgExt */
#define GOAL_PNIO_CFG_FLG_LLDP_OPT_TLV      GOAL_TRUE /* flgLldpOptTlv */
#define GOAL_PNIO_CFG_FLG_LLDP_GEN_MAC      GOAL_TRUE /* flgLldpGenMac */
#define GOAL_PNIO_CFG_FLG_IM_1_4_SUPPORT    GOAL_TRUE /* flgIm14Support */
#define GOAL_PNIO_CFG_FLG_IM_1_4_CB         GOAL_FALSE /* flgIm14Cb */
#define GOAL_PNIO_CFG_FLG_IM_0_CB           GOAL_FALSE /* flgIm0Cb */
#define GOAL_PNIO_CFG_FLG_IM_0_FILTER_CB    GOAL_FALSE /* flgIm0FilterCb */
#define GOAL_PNIO_CFG_CNT_REC_DATA_BUSY_BUFSIZE 2 /* cntRecDataBusyBufsize */
#define GOAL_PNIO_CFG_SIZE_RPC_FRAG_MAX_REQ_LEN 4068 /* sizeRpcFragMaxReqLen */
#define GOAL_PNIO_CFG_FLG_RPC_FRAG_SUPPORT  GOAL_TRUE /* flgRpcFragSupport */
#define GOAL_PNIO_CFG_NUM_RPC_SESSIONS      8 /* numRpcSessions */
#define GOAL_PNIO_CFG_NUM_DIAG_BUF_MAX      20 /* numDiagBufMax */
#define GOAL_PNIO_CFG_NUM_DIAG_DATA_SIZE_MAX 28 /* numDiagDataSizeMax */
#define GOAL_PNIO_CFG_NUM_IOCR_BLOCKS_MAX   10 /* numIocrBlocksMax */
#define GOAL_PNIO_CFG_NUM_CR_MAX            10 /* numCrMax */
#define GOAL_PNIO_CFG_NUM_AR_MAX            2 /* numArMax */
#define GOAL_PNIO_CFG_NUM_API_MAX           1 /* numApiMax */
#define GOAL_PNIO_CFG_NUM_SLOT_MAX          3 /* numSlotMax */
#define GOAL_PNIO_CFG_NUM_SUBSLOT_MAX       6 /* numSubslotMax */
#define GOAL_PNIO_CFG_ID_SUBSLOT_IF         0x8000 /* idSubslotIf */
#define GOAL_PNIO_CFG_ID_SUBSLOT_PORT       0x8001 /* idSubslotPort */
#define GOAL_PNIO_CFG_NUM_PROC_AL_BUF       10 /* numProcAlBuf */
#define GOAL_PNIO_CFG_FLG_MRP               GOAL_FALSE /* flgMrpCfg */


/****************************************************************************/
/* Forward declarations */
/****************************************************************************/
struct GOAL_PNIO_T;


/****************************************************************************/
/* Data types */
/****************************************************************************/
/**< AR id */
typedef uint32_t GOAL_PNIO_AR_ID_T;


/**< DCP signal blink state */
typedef uint32_t GOAL_PNIO_DCP_BLINK_STATE_T;


/**< DCP signal light state */
typedef uint32_t GOAL_PNIO_DCP_LIGHT_STATE_T;


/**< PROFINET status */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct {
    uint8_t code;                               /**< error code */
    uint8_t decode;                             /**< error decode */
    uint8_t code1;                              /**< error code 1 */
    uint8_t code2;                              /**< error code 2 */
} GOAL_TARGET_PACKED GOAL_PNIO_STATUS_T;
GOAL_TARGET_PACKED_STRUCT_POST


/**< alarm notify data */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct {
    uint16_t typeAlarm;                         /**< AlarmType */
    uint32_t idApi;                             /**< API */
    uint16_t idSlot;                            /**< SlotNumber */
    uint16_t idSubslot;                         /**< SubslotNumber */
    uint32_t idMod;                             /**< ModuleIdentNumber */
    uint32_t idSubmod;                          /**< SubmoduleIdentNumber */
    uint16_t specAlarm;                         /**< AlarmSpecifier */
    uint16_t nrSeq;                             /**< SequenceNumber */
} GOAL_TARGET_PACKED GOAL_PNIO_ALARM_NOTIFY_T;
GOAL_TARGET_PACKED_STRUCT_POST


/**< alarm notify ack data */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct {
    uint16_t typeAlarm;                         /**< AlarmType */
    uint32_t idApi;                             /**< API */
    uint16_t idSlot;                            /**< SlotNumber */
    uint16_t idSubslot;                         /**< SubslotNumber */
    uint16_t specAlarm;                         /**< AlarmSpecifier */
    uint16_t nrSeq;                             /**< SequenceNumber */
    GOAL_PNIO_STATUS_T status;                  /**< PNIOStatus */
} GOAL_TARGET_PACKED GOAL_PNIO_ALARM_NOTIFY_ACK_T;
GOAL_TARGET_PACKED_STRUCT_POST

/**< process alarm buffer states */
typedef enum {
    GOAL_PROC_ALARM_BUF_STATE_CLOSED = 0,       /**< uninitialized */
    GOAL_PROC_ALARM_BUF_STATE_OPEN,             /**< wait for internal request */
    GOAL_PROC_ALARM_BUF_STATE_WTACK,            /**< wait for transport ACK */
} GOAL_PROC_ALARM_BUF_STATE_T;

/**< process alarm structure */
GOAL_TARGET_PACKED_STRUCT_PRE
typedef GOAL_TARGET_PACKED_PRE struct GOAL_PROC_ALARM_TYPE_T {
    struct GOAL_PNIO_T *pPnio;                  /**< PROFINET handle */
    uint32_t api;                               /**< API number */
    uint16_t slot;                              /**< slot number */
    uint16_t subslot;                           /**< subslot number */
    uint16_t usi;                               /**< user structure id */
    uint16_t lenData;                           /**< data length */
    uint8_t *pData;                             /**< data */
} GOAL_TARGET_PACKED GOAL_PROC_ALARM_TYPE_T;
GOAL_TARGET_PACKED_STRUCT_POST

/**< process alarm buffer structure */
typedef struct GOAL_PROC_ALARM_BUF_TYPE_T {
    GOAL_PROC_ALARM_TYPE_T *procAlarm;          /**< process alarm handle */
    uint8_t procAlarmBufRead;                   /**< process alarm buffer read position */
    uint8_t procAlarmBufWrite;                  /**< process alarm buffer write position */
    GOAL_LOCK_T *lockProcAl;                    /**< Process alarm buffer mutex */
    GOAL_PROC_ALARM_BUF_STATE_T state;          /**< buffer state */
}  GOAL_PROC_ALARM_BUF_TYPE_T;

/**< Expected Module/Submodule Indicator */
typedef enum {
    GOAL_PNIO_IND_MOD,                          /**< indicator was called for module */
    GOAL_PNIO_IND_SUBMOD                        /**< indicator was called for submodule */
} GOAL_PNIO_IND_EXPMOD_T;

/**< Callback Data Content Structure */
typedef union GOAL_PNIO_CB_DATA_ELEM_T {
    int32_t i32;                                /**< 32-bit signed integer */

    uint8_t *pU8;                               /**< 8-bit unsigned pointer */
    uint16_t *pU16;                             /**< 16-bit unsigned pointer */
    uint32_t *pU32;                             /**< 32-bit unsigned pointer */

    const uint8_t *pCu8;                        /**< const 8-bit unsigned pointer */
    const uint16_t *pCu16;                      /**< const 16-bit unsigned pointer */
    const uint32_t *pCu32;                      /**< const 32-bit unsigned pointer */
    const uint64_t *pCu64;                      /**< const 64-bit unsigned pointer */

    uint16_t u16;                               /**< 16-bit unsigned integer */
    uint32_t u32;                               /**< 32-bit unsigned integer */

    GOAL_BOOL_T valBool;                        /**< true or false */

    GOAL_PNIO_AR_ID_T idAr;                     /**< AR id */

    GOAL_PNIO_DCP_BLINK_STATE_T stateDcpBlink;  /**< DCP blink state */
    GOAL_PNIO_DCP_LIGHT_STATE_T stateDcpLight;  /**< DCP light state */

    GOAL_PNIO_STATUS_T *pStatus;                /**< PROFINET status pointer */
    GOAL_PNIO_STATUS_T statusPnio;              /**< PROFINET status */

    GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify;     /**< alarm notification ptr */
    GOAL_PNIO_ALARM_NOTIFY_ACK_T *pAlarmNotifyAck; /**< alarm notification ack ptr */

    GOAL_PNIO_IND_EXPMOD_T expMode;             /**< Expected Module/Submodule Indicator */
} GOAL_PNIO_CB_DATA_ELEM_T;


/**< PROFINET callback id */
typedef uint32_t GOAL_PNIO_CB_ID_T;


/**< Callback Data Structure */
typedef struct {
    GOAL_PNIO_CB_DATA_ELEM_T data[GOAL_PNIO_CB_DATA_MAX]; /**< callback data elements */
} GOAL_PNIO_CB_DATA_T;


/**< PROFINET callback function */
typedef GOAL_STATUS_T (* GOAL_PNIO_FUNC_CB_T)(
    struct GOAL_PNIO_T *,                       /**< PROFINET handle */
    GOAL_PNIO_CB_ID_T,                          /**< callback id */
    GOAL_PNIO_CB_DATA_T *                       /**< callback parameters */
);


/**< GOAL PROFINET combined instance */
typedef struct GOAL_PNIO_T {
    GOAL_INSTANCE_HEADER(GOAL_PNIO_T);          /**< instance header */

    GOAL_BOOL_T flgCtcAc;                       /**< CTC AC flag */

    struct PN_INSTANCE_T *pInstLocal;           /**< local instance */
    struct GOAL_PNIO_INSTANCE_CTC_AC_T *pInstAc; /**< CTC AC instance */
    struct GOAL_PNIO_INSTANCE_CTC_CC_T *pInstCc; /**< CTC CC instance */

    GOAL_PROC_ALARM_BUF_TYPE_T *pProcAlarmBuffer; /**< process alarm queue */
    GOAL_BOOL_T mProcBufFlgInit;                /**< process alarm initialization flag */

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_MCTC_DP_T mctcDp;                   /**< MCTC data provider status */
    GOAL_MI_DM_GROUP_T *pDmGroupInput;          /**< MI DM Input group handle */
    GOAL_MI_DM_GROUP_T *pDmGroupOutput;         /**< MI DM Output group handle */
    GOAL_MI_DM_PART_T dmTxDp;                   /**< TX data provider status */
    GOAL_MI_DM_PART_T dmTxApdu;                 /**< TX APDU */
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */
} GOAL_PNIO_T;


/**< AR data */
typedef void GOAL_PNIO_AR_DATA_T;


/**< DCP signal blink states */
#define GOAL_PNIO_DCP_BLINK_START   0           /**< start signal */
#define GOAL_PNIO_DCP_BLINK_TOGGLE  1           /**< toggle signal */
#define GOAL_PNIO_DCP_BLINK_FINISH  2           /**< stop signal */


/**< DCP signal light states */
#define GOAL_PNIO_DCP_LIGHT_OFF     0           /**< light off */
#define GOAL_PNIO_DCP_LIGHT_ON      1           /**< light on */


/**< PROFINET module type */
typedef enum {
    GOAL_PNIO_MOD_TYPE_NONE = 0,                /**< no type selected */
    GOAL_PNIO_MOD_TYPE_INPUT,                   /**< input module */
    GOAL_PNIO_MOD_TYPE_OUTPUT,                  /**< output module */
    GOAL_PNIO_MOD_TYPE_IO,                      /**< input/output module */
} GOAL_PNIO_MOD_TYPE_T;


/**< IOxS state type */
typedef uint8_t GOAL_PNIO_IOXS_T;               /**< IOxS state */


/**< DCP blink state */
typedef uint32_t GOAL_PNIO_STATE_BLINK_T;


/**< IOCR endpoint id */
typedef uint32_t GOAL_PNIO_IOCR_EP_ID_T;


/**< APDU status */
typedef struct {
    uint16_t cntCycle;                          /**< CycleCounter */
    uint8_t statusData;                         /**< DataStatus */
    uint8_t statusTransfer;                     /**< TransferStatus */
} GOAL_PNIO_APDU_STATUS_T;


/**< diagnosis handle */
typedef int16_t GOAL_PNIO_DIAG_HANDLE_T;


/**< PROFINET Conformance Class id */
typedef unsigned int GOAL_PNIO_CC_T;


/****************************************************************************/
/* Core to core support */
/****************************************************************************/
#if (GOAL_CONFIG_GEN_CTC_AC == 1)
#  include <goal_pnio_rpc_ac.h>
#endif

#if (GOAL_CONFIG_GEN_CTC_CC == 1)
#  include <goal_pnio_rpc_cc.h>
#endif


#if (GOAL_CONFIG_GEN_CTC_AC == 1)
/**< PROFINET Meta Subslot */
typedef struct GOAL_PNIO_META_SUBSLOT_T {
    struct GOAL_PNIO_META_SUBSLOT_T *pNext;     /**< next subslot */

    uint16_t id;                                /**< subslot id */

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_MI_DM_PART_T dmOut;                    /**< output dm handle */
    GOAL_MI_DM_PART_T dmIn;                     /**< input dm handle */
    GOAL_MI_DM_PART_T dmIocsOut;                /**< output IOCS handle */
    GOAL_MI_DM_PART_T dmIopsOut;                /**< output IOPS handle */
    GOAL_MI_DM_PART_T dmIocsIn;                 /**< input IOCS handle */
    GOAL_MI_DM_PART_T dmIopsIn;                 /**< input IOPS handle */
#endif

} GOAL_PNIO_META_SUBSLOT_T;


/**< PROFINET Meta Slot */
typedef struct GOAL_PNIO_META_SLOT_T {
    struct GOAL_PNIO_META_SLOT_T *pNext;        /**< next slot */

    uint16_t id;                                /**< slot id */
    struct GOAL_PNIO_META_SUBSLOT_T *pListSubslot; /**< subslot list */
} GOAL_PNIO_META_SLOT_T;

/**< PROFINET Meta Submodule */
typedef struct GOAL_PNIO_META_SUBMODULE_T {
    struct GOAL_PNIO_META_SUBMODULE_T *pNext;   /**< next submodule */

    uint32_t id;                                /**< submodule id */

    GOAL_PNIO_MOD_TYPE_T type;                  /**< submodule type */
    uint16_t sizeInput;                         /**< input size */
    uint16_t sizeOutput;                        /**< output size */

} GOAL_PNIO_META_SUBMODULE_T;


/**< PROFINET Meta Module */
typedef struct GOAL_PNIO_META_MODULE_T {
    struct GOAL_PNIO_META_MODULE_T *pNext;      /**< next module */

    uint32_t id;                                /**< module id */
    struct GOAL_PNIO_META_SUBMODULE_T *pListSubmodule; /**< submodule list */
} GOAL_PNIO_META_MODULE_T;

/**< PROFINET Meta API */
typedef struct GOAL_PNIO_META_API_T {
    struct GOAL_PNIO_META_API_T *pNext;         /**< next API */

    uint32_t id;                                /**< API id */
    struct GOAL_PNIO_META_SLOT_T *pListSlot;    /**< slot list */
} GOAL_PNIO_META_API_T;


/**< PROFINET CTC AC instance */
typedef struct GOAL_PNIO_INSTANCE_CTC_AC_T {
    uint32_t idInst;                            /**< instance id */

    GOAL_PNIO_FUNC_CB_T pnioCb;                 /**< PROFINET callback function */
    GOAL_PNIO_FUNC_CB_T pFunc;                  /**< PROFINET callback function */

    GOAL_PNIO_META_API_T *pListApi;             /**< PROFINET Meta API list */

#if GOAL_CONFIG_MEDIA_MI_DM == 1
    GOAL_BOOL_T varFlgCyclic;                   /**< transfer raw cyclic data */
    GOAL_PNIO_META_MODULE_T *pListModule;       /**< module list */

    GOAL_MI_DM_PART_T dmDp;                     /**< data provider dm handle */
    GOAL_MI_DM_PART_T dmApduOut;                /**< output APDU dm handle */

    GOAL_MI_DM_PART_T *pDmFirst;                /**< first DM partition of output data (GOAL_PNIO_CB_ID_NEW_IO_DATA) */
    uint32_t len;                               /**< length of partitions (GOAL_PNIO_CB_ID_NEW_IO_DATA) */
    uint16_t dmCycle;                           /**< latest DM CycleCounter */
#endif

    GOAL_MI_MCTC_INST_T *pHdlPnioMctc;          /**< PROFINET MCTC handle (cyclic data) */
    GOAL_RPC_HDL_CHN_T *pHdlRpcChnPnio;         /**< PROFINET RPC channel handle (acyclic data) */

    GOAL_PNIO_DCP_LIGHT_STATE_T stateDcpLight;  /**< latest DCP light state */

} GOAL_PNIO_INSTANCE_CTC_AC_T;
#endif /* (GOAL_CONFIG_GEN_CTC_AC == 1) */


#if (GOAL_CONFIG_GEN_CTC_CC == 1)
/**< PROFINET CTC CC instance */
typedef struct GOAL_PNIO_INSTANCE_CTC_CC_T {
    uint32_t idInst;                            /**< instance id */

    GOAL_STAGE_HANDLER_T stageMod;              /**< module stage handler */
    GOAL_BOOL_T flgCbNewIoData;                 /**< output data available */
    GOAL_BOOL_T flgCbReleaseAr;                 /**< AR released */
    GOAL_BOOL_T flgCbIoDataTimeout;             /**< IO data timeout */
    const IO_EP_T *pHdlCbNewIoData;             /**< IO endpoint handle for output data */
    GOAL_PNIO_AR_ID_T idCbReleaseAr;            /**< AR id to release */
    GOAL_BOOL_T varFlgCyclic;                   /**< transfer raw cyclic data */

    struct GOAL_PNIO_T *pPnio;                  /**< local PROFINET instance */
    GOAL_MI_MCTC_INST_T *pHdlPnioMctc;          /**< PROFINET MCTC handle (cyclic data) */
    GOAL_RPC_HDL_CHN_T *pHdlRpcChnPnio;         /**< PROFINET RPC channel handle (acyclic data) */
} GOAL_PNIO_INSTANCE_CTC_CC_T;
#endif /* (GOAL_CONFIG_GEN_CTC_CC == 1) */


/****************************************************************************/
/* Function and Parameter Mapping */
/****************************************************************************/
#if (GOAL_CONFIG_GEN_CTC_AC == 0)

#  define goal_pnioSubslotNew(...) goal_pnioSubslotNewImpl(__VA_ARGS__)
#  define goal_pnioSlotNew(...) goal_pnioSlotNewImpl(__VA_ARGS__)
#  define goal_pnioModNew(...) goal_pnioModNewImpl(__VA_ARGS__)
#  define goal_pnioSubmodNew(...) goal_pnioSubmodNewImpl(__VA_ARGS__)
#  define goal_pnioModPlug(...) goal_pnioModPlugImpl(__VA_ARGS__)
#  define goal_pnioSubmodPlug(...) goal_pnioSubmodPlugImpl(__VA_ARGS__)
#  define goal_pnioModPull(...) goal_pnioModPullImpl(__VA_ARGS__)
#  define goal_pnioSubmodPull(...) goal_pnioSubmodPullImpl(__VA_ARGS__)
#  define goal_pnioDataOutputGet(...) goal_pnioDataOutputGetImpl(__VA_ARGS__)
#  define goal_pnioDataInputSet(...) goal_pnioDataInputSetImpl(__VA_ARGS__)
#  define goal_pnioApduStatusGet(...) goal_pnioApduStatusGetImpl(__VA_ARGS__)
#  define goal_pnioAlarmNotifySend(...) goal_pnioAlarmNotifySendImpl(__VA_ARGS__)
#  define goal_pnioAlarmNotifySendAck(...) goal_pnioAlarmNotifySendAckImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessSend(...) goal_pnioAlarmProcessSendImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueInit(...) goal_pnioAlarmProcessQueueInitImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueAdd(...) goal_pnioAlarmProcessQueueAddImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueSend(...) goal_pnioAlarmProcessQueueSendImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueReset(...) goal_pnioAlarmProcessQueueResetImpl(__VA_ARGS__)
#  define goal_pnioRecReadFinish(...) goal_pnioRecReadFinishImpl(__VA_ARGS__)
#  define goal_pnioRecWriteFinish(...) goal_pnioRecWriteFinishImpl(__VA_ARGS__)
#  define goal_pnioVendorIdSet(...) goal_pnioVendorIdSetImpl(__VA_ARGS__)
#  define goal_pnioDeviceIdSet(...) goal_pnioDeviceIdSetImpl(__VA_ARGS__)
#  define goal_pnioDeviceNameSet(...) goal_pnioDeviceNameSetImpl(__VA_ARGS__)
#  define goal_pnioHwRevSet(...) goal_pnioHwRevSetImpl(__VA_ARGS__)
#  define goal_pnioSwRevSet(...) goal_pnioSwRevSetImpl(__VA_ARGS__)
#  define goal_pnioProfileIdSet(...) goal_pnioProfileIdSetImpl(__VA_ARGS__)
#  define goal_pnioOrderIdSet(...) goal_pnioOrderIdSetImpl(__VA_ARGS__)
#  define goal_pnioSerialNumSet(...) goal_pnioSerialNumSetImpl(__VA_ARGS__)
#  define goal_pnioVendorNameSet(...) goal_pnioVendorNameSetImpl(__VA_ARGS__)
#  define goal_pnioPortDescSet(...) goal_pnioPortDescSetImpl(__VA_ARGS__)
#  define goal_pnioSystemDescSet(...) goal_pnioSystemDescSetImpl(__VA_ARGS__)
#  define goal_pnioDiagExtChanDiagAdd(...) goal_pnioDiagExtChanDiagAddImpl(__VA_ARGS__)
#  define goal_pnioDiagChanDiagRemove(...) goal_pnioDiagChanDiagRemoveImpl(__VA_ARGS__)
#  define goal_pnioCyclicCtrl(...) goal_pnioCyclicCtrlImpl(__VA_ARGS__)
#  define goal_pnioCfgDcpFactoryResetDisableSet(...) goal_pnioCfgDcpFactoryResetDisableSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDcpAcceptMixcaseStationSet(...) goal_pnioCfgDcpAcceptMixcaseStationSetImpl(__VA_ARGS__)
#  define goal_pnioCfgVendorIdSet(...) goal_pnioCfgVendorIdSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDeviceIdSet(...) goal_pnioCfgDeviceIdSetImpl(__VA_ARGS__)
#  define goal_pnioCfgVendorNameSet(...) goal_pnioCfgVendorNameSetImpl(__VA_ARGS__)
#  define goal_pnioCfgPortNameSet(...) goal_pnioCfgPortNameSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSystemDescSet(...) goal_pnioCfgSystemDescSetImpl(__VA_ARGS__)
#  define goal_pnioCfgOrderIdSet(...) goal_pnioCfgOrderIdSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSerialNumSet(...) goal_pnioCfgSerialNumSetImpl(__VA_ARGS__)
#  define goal_pnioCfgHwRevSet(...) goal_pnioCfgHwRevSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSwRevPrefixSet(...) goal_pnioCfgSwRevPrefixSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSwRevFuncEnhSet(...) goal_pnioCfgSwRevFuncEnhSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSwRevBugfixSet(...) goal_pnioCfgSwRevBugfixSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSwRevIntChgSet(...) goal_pnioCfgSwRevIntChgSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSwRevCntSet(...) goal_pnioCfgSwRevCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm1TagFuncSet(...) goal_pnioCfgIm1TagFuncSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm1TagLocSet(...) goal_pnioCfgIm1TagLocSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm2DateSet(...) goal_pnioCfgIm2DateSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm3DescSet(...) goal_pnioCfgIm3DescSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm4SigSet(...) goal_pnioCfgIm4SigSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapSimpleSet(...) goal_pnioCfgDevDapSimpleSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapApiSet(...) goal_pnioCfgDevDapApiSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapSlotSet(...) goal_pnioCfgDevDapSlotSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubslotSet(...) goal_pnioCfgDevDapSubslotSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapModuleSet(...) goal_pnioCfgDevDapModuleSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubmoduleSet(...) goal_pnioCfgDevDapSubmoduleSetImpl(__VA_ARGS__)
#  define goal_pnioCfgNetLinkSafetySet(...) goal_pnioCfgNetLinkSafetySetImpl(__VA_ARGS__)
#  define goal_pnioCfgNewIoDataCbSet(...) goal_pnioCfgNewIoDataCbSetImpl(__VA_ARGS__)
#  define goal_pnioCfgLldpOrgExtSet(...) goal_pnioCfgLldpOrgExtSetImpl(__VA_ARGS__)
#  define goal_pnioCfgLldpOptTlvSet(...) goal_pnioCfgLldpOptTlvSetImpl(__VA_ARGS__)
#  define goal_pnioCfgLldpGenMacSet(...) goal_pnioCfgLldpGenMacSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm14SupportSet(...) goal_pnioCfgIm14SupportSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm14CbSet(...) goal_pnioCfgIm14CbSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm0CbSet(...) goal_pnioCfgIm0CbSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIm0FilterDataCbSet(...) goal_pnioCfgIm0FilterDataCbSetImpl(__VA_ARGS__)
#  define goal_pnioCfgRecDataBusyBufsizeSet(...) goal_pnioCfgRecDataBusyBufsizeSetImpl(__VA_ARGS__)
#  define goal_pnioCfgRpcFragReqLenMaxSet(...) goal_pnioCfgRpcFragReqLenMaxSetImpl(__VA_ARGS__)
#  define goal_pnioCfgRpcFragMaxCntSet(...) goal_pnioCfgRpcFragMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgRpcFragEnableSet(...) goal_pnioCfgRpcFragEnableSetImpl(__VA_ARGS__)
#  define goal_pnioCfgRpcSessionMaxCntSet(...) goal_pnioCfgRpcSessionMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxCntSet(...) goal_pnioCfgDiagBufMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxDataSizeSet(...) goal_pnioCfgDiagBufMaxDataSizeSetImpl(__VA_ARGS__)
#  define goal_pnioCfgIocrBlocksMaxSet(...) goal_pnioCfgIocrBlocksMaxSetImpl(__VA_ARGS__)
#  define goal_pnioCfgCrMaxCntSet(...) goal_pnioCfgCrMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgArMaxCntSet(...) goal_pnioCfgArMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgApiMaxCntSet(...) goal_pnioCfgApiMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSlotMaxCntSet(...) goal_pnioCfgSlotMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSubslotMaxCntSet(...) goal_pnioCfgSubslotMaxCntSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSubslotIfSet(...) goal_pnioCfgSubslotIfSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSubslotPortSet(...) goal_pnioCfgSubslotPortSetImpl(__VA_ARGS__)
#  define goal_pnioCfgSnmpIdSet(...) goal_pnioCfgSnmpIdSetImpl(__VA_ARGS__)
#  define goal_pnioCfgNumProcAlBufSet(...) goal_pnioCfgNumProcAlBufSetImpl(__VA_ARGS__)
#  define goal_pnioRpcSubmodPlug(...) goal_pnioSubmodPlugImpl(__VA_ARGS__)
#  define goal_pnioDmSubmodPlug(...) goal_pnioSubmodPlugImpl(__VA_ARGS__)
#  define goal_pnioDmSubslotAdd(...) goal_pnioDmSubslotAddImpl(__VA_ARGS__)
#  define goal_pnioDmSubslotIoxsAdd(...) goal_pnioDmSubslotIoxsAddImpl(__VA_ARGS__)
#  define goal_pnioDmApduAdd(...) goal_pnioDmApduAddImpl(__VA_ARGS__)
#  define goal_pnioDmDpAdd(...) goal_pnioDmDpAddImpl(__VA_ARGS__)
#  define goal_pnioDmReset(...) goal_pnioDmResetImpl(__VA_ARGS__)
#  define goal_pnioSubslotStateSet(...) goal_pnioSubslotStateSetImpl(__VA_ARGS__)
#  define goal_pnioConfClassGet(...) goal_pnioConfClassGetImpl(__VA_ARGS__)
#  define goal_pnioConfClassSet(...) goal_pnioConfClassSetImpl(__VA_ARGS__)
#  define goal_pnioConfTestGet(...) goal_pnioConfTestGetImpl(__VA_ARGS__)
#  define goal_pnioCfgFlgMrpCfgSet(...) goal_pnioCfgFlgMrpCfgSetImpl(__VA_ARGS__)
#  define goal_pnioConnReqProcess(...) goal_pnioConnReqProcessImpl(__VA_ARGS__)


#elif GOAL_CONFIG_PNIO_LOCAL == 0

#  define goal_pnioSubslotNew(...) goal_pnioSubslotNewAc(__VA_ARGS__)
#  define goal_pnioSlotNew(...) goal_pnioSlotNewAc(__VA_ARGS__)
#  define goal_pnioModNew(...) goal_pnioModNewAc(__VA_ARGS__)
#  define goal_pnioSubmodNew(...) goal_pnioSubmodNewAc(__VA_ARGS__)
#  define goal_pnioModPlug(...) goal_pnioModPlugAc(__VA_ARGS__)
#  define goal_pnioSubmodPlug(...) goal_pnioDmSubmodPlug(__VA_ARGS__)
#  define goal_pnioModPull(...) goal_pnioModPullAc(__VA_ARGS__)
#  define goal_pnioSubmodPull(...) goal_pnioSubmodPullAc(__VA_ARGS__)
#  define goal_pnioDataOutputGet(...) goal_pnioDataOutputGetAc(__VA_ARGS__)
#  define goal_pnioDataInputSet(...) goal_pnioDataInputSetAc(__VA_ARGS__)
#  define goal_pnioApduStatusGet(...) goal_pnioApduStatusGetAc(__VA_ARGS__)
#  define goal_pnioAlarmNotifySend(...) goal_pnioAlarmNotifySendAc(__VA_ARGS__)
#  define goal_pnioAlarmNotifySendAck(...) goal_pnioAlarmNotifySendAckAc(__VA_ARGS__)
#  define goal_pnioAlarmProcessSend(...) goal_pnioAlarmProcessSendAc(__VA_ARGS__)
#  define goal_pnioRecReadFinish(...) goal_pnioRecReadFinishAc(__VA_ARGS__)
#  define goal_pnioRecWriteFinish(...) goal_pnioRecWriteFinishAc(__VA_ARGS__)
#  define goal_pnioVendorIdSet(...) goal_pnioVendorIdSetAc(__VA_ARGS__)
#  define goal_pnioDeviceIdSet(...) goal_pnioDeviceIdSetAc(__VA_ARGS__)
#  define goal_pnioDeviceNameSet(...) goal_pnioDeviceNameSetAc(__VA_ARGS__)
#  define goal_pnioHwRevSet(...) goal_pnioHwRevSetAc(__VA_ARGS__)
#  define goal_pnioSwRevSet(...) goal_pnioSwRevSetAc(__VA_ARGS__)
#  define goal_pnioProfileIdSet(...) goal_pnioProfileIdSetAc(__VA_ARGS__)
#  define goal_pnioOrderIdSet(...) goal_pnioOrderIdSetAc(__VA_ARGS__)
#  define goal_pnioSerialNumSet(...) goal_pnioSerialNumSetAc(__VA_ARGS__)
#  define goal_pnioVendorNameSet(...) goal_pnioVendorNameSetAc(__VA_ARGS__)
#  define goal_pnioPortDescSet(...) goal_pnioPortDescSetAc(__VA_ARGS__)
#  define goal_pnioSystemDescSet(...) goal_pnioSystemDescSetAc(__VA_ARGS__)
#  define goal_pnioDiagExtChanDiagAdd(...) goal_pnioDiagExtChanDiagAddAc(__VA_ARGS__)
#  define goal_pnioDiagChanDiagRemove(...) goal_pnioDiagChanDiagRemoveAc(__VA_ARGS__)
#  define goal_pnioCyclicCtrl(...) goal_pnioCyclicCtrlAc(__VA_ARGS__)
#  define goal_pnioCfgDcpFactoryResetDisableSet(...) goal_pnioCfgDcpFactoryResetDisableSetAc(__VA_ARGS__)
#  define goal_pnioCfgDcpAcceptMixcaseStationSet(...) goal_pnioCfgDcpAcceptMixcaseStationSetAc(__VA_ARGS__)
#  define goal_pnioCfgVendorIdSet(...) goal_pnioCfgVendorIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgDeviceIdSet(...) goal_pnioCfgDeviceIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgVendorNameSet(...) goal_pnioCfgVendorNameSetAc(__VA_ARGS__)
#  define goal_pnioCfgPortNameSet(...) goal_pnioCfgPortNameSetAc(__VA_ARGS__)
#  define goal_pnioCfgSystemDescSet(...) goal_pnioCfgSystemDescSetAc(__VA_ARGS__)
#  define goal_pnioCfgOrderIdSet(...) goal_pnioCfgOrderIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgSerialNumSet(...) goal_pnioCfgSerialNumSetAc(__VA_ARGS__)
#  define goal_pnioCfgHwRevSet(...) goal_pnioCfgHwRevSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevPrefixSet(...) goal_pnioCfgSwRevPrefixSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevFuncEnhSet(...) goal_pnioCfgSwRevFuncEnhSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevBugfixSet(...) goal_pnioCfgSwRevBugfixSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevIntChgSet(...) goal_pnioCfgSwRevIntChgSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevCntSet(...) goal_pnioCfgSwRevCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm1TagFuncSet(...) goal_pnioCfgIm1TagFuncSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm1TagLocSet(...) goal_pnioCfgIm1TagLocSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm2DateSet(...) goal_pnioCfgIm2DateSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm3DescSet(...) goal_pnioCfgIm3DescSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm4SigSet(...) goal_pnioCfgIm4SigSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSimpleSet(...) goal_pnioCfgDevDapSimpleSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapApiSet(...) goal_pnioCfgDevDapApiSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSlotSet(...) goal_pnioCfgDevDapSlotSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubslotSet(...) goal_pnioCfgDevDapSubslotSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapModuleSet(...) goal_pnioCfgDevDapModuleSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubmoduleSet(...) goal_pnioCfgDevDapSubmoduleSetAc(__VA_ARGS__)
#  define goal_pnioCfgNetLinkSafetySet(...) goal_pnioCfgNetLinkSafetySetAc(__VA_ARGS__)
#  define goal_pnioCfgNewIoDataCbSet(...) goal_pnioCfgNewIoDataCbSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpOrgExtSet(...) goal_pnioCfgLldpOrgExtSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpOptTlvSet(...) goal_pnioCfgLldpOptTlvSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpGenMacSet(...) goal_pnioCfgLldpGenMacSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm14SupportSet(...) goal_pnioCfgIm14SupportSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm14CbSet(...) goal_pnioCfgIm14CbSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm0CbSet(...) goal_pnioCfgIm0CbSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm0FilterDataCbSet(...) goal_pnioCfgIm0FilterDataCbSetAc(__VA_ARGS__)
#  define goal_pnioCfgRecDataBusyBufsizeSet(...) goal_pnioCfgRecDataBusyBufsizeSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragReqLenMaxSet(...) goal_pnioCfgRpcFragReqLenMaxSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragMaxCntSet(...) goal_pnioCfgRpcFragMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragEnableSet(...) goal_pnioCfgRpcFragEnableSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcSessionMaxCntSet(...) goal_pnioCfgRpcSessionMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxCntSet(...) goal_pnioCfgDiagBufMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxDataSizeSet(...) goal_pnioCfgDiagBufMaxDataSizeSetAc(__VA_ARGS__)
#  define goal_pnioCfgIocrBlocksMaxSet(...) goal_pnioCfgIocrBlocksMaxSetAc(__VA_ARGS__)
#  define goal_pnioCfgCrMaxCntSet(...) goal_pnioCfgCrMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgArMaxCntSet(...) goal_pnioCfgArMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgApiMaxCntSet(...) goal_pnioCfgApiMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgSlotMaxCntSet(...) goal_pnioCfgSlotMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgFlgMrpCfgSet(...) goal_pnioCfgFlgMrpCfgSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotMaxCntSet(...) goal_pnioCfgSubslotMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotIfSet(...) goal_pnioCfgSubslotIfSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotPortSet(...) goal_pnioCfgSubslotPortSetAc(__VA_ARGS__)
#  define goal_pnioCfgSnmpIdSet(...) goal_pnioCfgSnmpIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgNumProcAlBufSet(...) goal_pnioCfgNumProcAlBufSetAc(__VA_ARGS__)
#  define goal_pnioRpcSubmodPlug(...) goal_pnioSubmodPlugAc(__VA_ARGS__)
#  define goal_pnioDmSubmodPlug(...) goal_pnioDmSubmodPlugAc(__VA_ARGS__)
#  define goal_pnioDmSubslotAdd(...) goal_pnioDmSubslotAddAc(__VA_ARGS__)
#  define goal_pnioDmSubslotIoxsAdd(...) goal_pnioDmSubslotIoxsAddAc(__VA_ARGS__)
#  define goal_pnioDmApduAdd(...) goal_pnioDmApduAddAc(__VA_ARGS__)
#  define goal_pnioDmDpAdd(...) goal_pnioDmDpAddAc(__VA_ARGS__)
#  define goal_pnioDmReset(...) goal_pnioDmResetAc(__VA_ARGS__)
#  define goal_pnioSubslotStateSet(...) goal_pnioSubslotStateSetAc(__VA_ARGS__)
#  define goal_pnioConnReqProcess(...) goal_pnioConnReqProcessAc(__VA_ARGS__)

#else

#  define goal_pnioSubslotNew(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSubslotNewAc(__VA_ARGS__) : goal_pnioSubslotNewImpl(__VA_ARGS__)
#  define goal_pnioSlotNew(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSlotNewAc(__VA_ARGS__) : goal_pnioSlotNewImpl(__VA_ARGS__)
#  define goal_pnioModNew(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioModNewAc(__VA_ARGS__) : goal_pnioModNewImpl(__VA_ARGS__)
#  define goal_pnioSubmodNew(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSubmodNewAc(__VA_ARGS__) : goal_pnioSubmodNewImpl(__VA_ARGS__)
#  define goal_pnioModPlug(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioModPlugAc(__VA_ARGS__) : goal_pnioModPlugImpl(__VA_ARGS__)
#  define goal_pnioSubmodPlug(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDmSubmodPlug(__VA_ARGS__) : goal_pnioSubmodPlugImpl(__VA_ARGS__)
#  define goal_pnioModPull(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioModPullAc(__VA_ARGS__) : goal_pnioModPullImpl(__VA_ARGS__)
#  define goal_pnioSubmodPull(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSubmodPullAc(__VA_ARGS__) : goal_pnioSubmodPullImpl(__VA_ARGS__)
#  define goal_pnioDataOutputGet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDataOutputGetAc(__VA_ARGS__) : goal_pnioDataOutputGetImpl(__VA_ARGS__)
#  define goal_pnioDataInputSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDataInputSetAc(__VA_ARGS__) : goal_pnioDataInputSetImpl(__VA_ARGS__)
#  define goal_pnioApduStatusGet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioApduStatusGetAc(__VA_ARGS__) : goal_pnioApduStatusGetImpl(__VA_ARGS__)
#  define goal_pnioAlarmNotifySend(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmNotifySendAc(__VA_ARGS__) : goal_pnioAlarmNotifySendImpl(__VA_ARGS__)
#  define goal_pnioAlarmNotifySendAck(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmNotifySendAckAc(__VA_ARGS__) : goal_pnioAlarmNotifySendAckImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessSend(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmProcessSendAc(__VA_ARGS__) : goal_pnioAlarmProcessSendImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueInit(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmProcessQueueInitAc(__VA_ARGS__) : goal_pnioAlarmProcessQueueInitImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueAdd(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmProcessQueueAddAc(__VA_ARGS__) : goal_pnioAlarmProcessQueueAddImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueSend(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmProcessQueueSendAc(__VA_ARGS__) : goal_pnioAlarmProcessQueueSendImpl(__VA_ARGS__)
#  define goal_pnioAlarmProcessQueueReset(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioAlarmProcessQueueResetAc(__VA_ARGS__) : goal_pnioAlarmProcessQueueResetImpl(__VA_ARGS__)
#  define goal_pnioRecReadFinish(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioRecReadFinishAc(__VA_ARGS__) : goal_pnioRecReadFinishImpl(__VA_ARGS__)
#  define goal_pnioRecWriteFinish(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioRecWriteFinishAc(__VA_ARGS__) : goal_pnioRecWriteFinishImpl(__VA_ARGS__)
#  define goal_pnioVendorIdSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioVendorIdSetAc(__VA_ARGS__) : goal_pnioVendorIdSetImpl(__VA_ARGS__)
#  define goal_pnioDeviceIdSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDeviceIdSetAc(__VA_ARGS__) : goal_pnioDeviceIdSetImpl(__VA_ARGS__)
#  define goal_pnioDeviceNameSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDeviceNameSetAc(__VA_ARGS__) : goal_pnioDeviceNameSetImpl(__VA_ARGS__)
#  define goal_pnioHwRevSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioHwRevSetAc(__VA_ARGS__) : goal_pnioHwRevSetImpl(__VA_ARGS__)
#  define goal_pnioSwRevSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSwRevSetAc(__VA_ARGS__) : goal_pnioSwRevSetImpl(__VA_ARGS__)
#  define goal_pnioProfileIdSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioProfileIdSetAc(__VA_ARGS__) : goal_pnioProfileIdSetImpl(__VA_ARGS__)
#  define goal_pnioOrderIdSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioOrderIdSetAc(__VA_ARGS__) : goal_pnioOrderIdSetImpl(__VA_ARGS__)
#  define goal_pnioSerialNumSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSerialNumSetAc(__VA_ARGS__) : goal_pnioSerialNumSetImpl(__VA_ARGS__)
#  define goal_pnioVendorNameSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioVendorNameSetAc(__VA_ARGS__) : goal_pnioVendorNameSetImpl(__VA_ARGS__)
#  define goal_pnioPortDescSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioPortDescSetAc(__VA_ARGS__) : goal_pnioPortDescSetImpl(__VA_ARGS__)
#  define goal_pnioSystemDescSet(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioSystemDescSetAc(__VA_ARGS__) : goal_pnioSystemDescSetImpl(__VA_ARGS__)
#  define goal_pnioDiagExtChanDiagAdd(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDiagExtChanDiagAddAc(__VA_ARGS__) : goal_pnioDiagExtChanDiagAddImpl(__VA_ARGS__)
#  define goal_pnioDiagChanDiagRemove(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioDiagChanDiagRemoveAc(__VA_ARGS__) : goal_pnioDiagChanDiagRemoveImpl(__VA_ARGS__)
#  define goal_pnioCyclicCtrl(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioCyclicCtrlAc(__VA_ARGS__) : goal_pnioCyclicCtrlImpl(__VA_ARGS__)
#  define goal_pnioConnReqProcess(...) (GOAL_TRUE == pPnio->flgCtcAc) ? goal_pnioConnReqProcessAc(__VA_ARGS__) : goal_pnioConnReqProcessImpl(__VA_ARGS__)
#  define goal_pnioCfgDcpFactoryResetDisableSet(...) goal_pnioCfgDcpFactoryResetDisableSetAc(__VA_ARGS__)
#  define goal_pnioCfgDcpAcceptMixcaseStationSet(...) goal_pnioCfgDcpAcceptMixcaseStationSetAc(__VA_ARGS__)
#  define goal_pnioCfgVendorIdSet(...) goal_pnioCfgVendorIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgDeviceIdSet(...) goal_pnioCfgDeviceIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgVendorNameSet(...) goal_pnioCfgVendorNameSetAc(__VA_ARGS__)
#  define goal_pnioCfgPortNameSet(...) goal_pnioCfgPortNameSetAc(__VA_ARGS__)
#  define goal_pnioCfgSystemDescSet(...) goal_pnioCfgSystemDescSetAc(__VA_ARGS__)
#  define goal_pnioCfgOrderIdSet(...) goal_pnioCfgOrderIdSetAc(__VA_ARGS__)
#  define goal_pnioCfgSerialNumSet(...) goal_pnioCfgSerialNumSetAc(__VA_ARGS__)
#  define goal_pnioCfgHwRevSet(...) goal_pnioCfgHwRevSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevPrefixSet(...) goal_pnioCfgSwRevPrefixSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevFuncEnhSet(...) goal_pnioCfgSwRevFuncEnhSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevBugfixSet(...) goal_pnioCfgSwRevBugfixSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevIntChgSet(...) goal_pnioCfgSwRevIntChgSetAc(__VA_ARGS__)
#  define goal_pnioCfgSwRevCntSet(...) goal_pnioCfgSwRevCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm1TagFuncSet(...) goal_pnioCfgIm1TagFuncSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm1TagLocSet(...) goal_pnioCfgIm1TagLocSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm2DateSet(...) goal_pnioCfgIm2DateSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm3DescSet(...) goal_pnioCfgIm3DescSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm4SigSet(...) goal_pnioCfgIm4SigSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSimpleSet(...) goal_pnioCfgDevDapSimpleSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapApiSet(...) goal_pnioCfgDevDapApiSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSlotSet(...) goal_pnioCfgDevDapSlotSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubslotSet(...) goal_pnioCfgDevDapSubslotSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapModuleSet(...) goal_pnioCfgDevDapModuleSetAc(__VA_ARGS__)
#  define goal_pnioCfgDevDapSubmoduleSet(...) goal_pnioCfgDevDapSubmoduleSetAc(__VA_ARGS__)
#  define goal_pnioCfgNetLinkSafetySet(...) goal_pnioCfgNetLinkSafetySetAc(__VA_ARGS__)
#  define goal_pnioCfgNewIoDataCbSet(...) goal_pnioCfgNewIoDataCbSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpOrgExtSet(...) goal_pnioCfgLldpOrgExtSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpOptTlvSet(...) goal_pnioCfgLldpOptTlvSetAc(__VA_ARGS__)
#  define goal_pnioCfgLldpGenMacSet(...) goal_pnioCfgLldpGenMacSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm14SupportSet(...) goal_pnioCfgIm14SupportSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm14CbSet(...) goal_pnioCfgIm14CbSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm0CbSet(...) goal_pnioCfgIm0CbSetAc(__VA_ARGS__)
#  define goal_pnioCfgIm0FilterDataCbSet(...) goal_pnioCfgIm0FilterDataCbSetAc(__VA_ARGS__)
#  define goal_pnioCfgRecDataBusyBufsizeSet(...) goal_pnioCfgRecDataBusyBufsizeSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragReqLenMaxSet(...) goal_pnioCfgRpcFragReqLenMaxSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragMaxCntSet(...) goal_pnioCfgRpcFragMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcFragEnableSet(...) goal_pnioCfgRpcFragEnableSetAc(__VA_ARGS__)
#  define goal_pnioCfgRpcSessionMaxCntSet(...) goal_pnioCfgRpcSessionMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxCntSet(...) goal_pnioCfgDiagBufMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgDiagBufMaxDataSizeSet(...) goal_pnioCfgDiagBufMaxDataSizeSetAc(__VA_ARGS__)
#  define goal_pnioCfgIocrBlocksMaxSet(...) goal_pnioCfgIocrBlocksMaxSetAc(__VA_ARGS__)
#  define goal_pnioCfgCrMaxCntSet(...) goal_pnioCfgCrMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgArMaxCntSet(...) goal_pnioCfgArMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgApiMaxCntSet(...) goal_pnioCfgApiMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgSlotMaxCntSet(...) goal_pnioCfgSlotMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgFlgMrpCfgSet(...) goal_pnioCfgFlgMrpCfgSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotMaxCntSet(...) goal_pnioCfgSubslotMaxCntSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotIfSet(...) goal_pnioCfgSubslotIfSetAc(__VA_ARGS__)
#  define goal_pnioCfgSubslotPortSet(...) goal_pnioCfgSubslotPortSetAc(__VA_ARGS__)
#  define goal_pnioCfgNumProcAlBufSet(...) goal_pnioCfgNumProcAlBufSetAc(__VA_ARGS__)
#  define goal_pnioRpcSubmodPlug(...) goal_pnioSubmodPlugAc(__VA_ARGS__)
#  define goal_pnioDmSubmodPlug(...) goal_pnioDmSubmodPlugAc(__VA_ARGS__)
#  define goal_pnioDmSubslotAdd(...) goal_pnioDmSubslotAddAc(__VA_ARGS__)
#  define goal_pnioDmSubslotIoxsAdd(...) goal_pnioDmSubslotIoxsAddAc(__VA_ARGS__)
#  define goal_pnioDmApduAdd(...) goal_pnioDmApduAddAc(__VA_ARGS__)
#  define goal_pnioDmReset(...) goal_pnioDmReset(__VA_ARGS__)
#  define goal_pnioDmDpAdd(...) goal_pnioDmDpAddAc(__VA_ARGS__)

#endif


/****************************************************************************/
/* PROFINET functions */
/****************************************************************************/
/**< PROFINET function list */
#define GOAL_PNIO_FUNC_LIST \
    /*                   id, name,                                  function */                         \
    GOAL_PNIO_FUNC_ENTRY( 1, GOAL_PNIO_FUNC_SUBSLOT_NEW,            goal_pnioSubslotNew)                \
    GOAL_PNIO_FUNC_ENTRY( 2, GOAL_PNIO_FUNC_SUBMOD_NEW,             goal_pnioSubmodNew)                 \
    GOAL_PNIO_FUNC_ENTRY( 3, GOAL_PNIO_FUNC_SUBMOD_PLUG,            goal_pnioSubmodPlug)                \
    GOAL_PNIO_FUNC_ENTRY( 4, GOAL_PNIO_FUNC_DATA_OUTPUT_GET,        goal_pnioDataOutputGet)             \
    GOAL_PNIO_FUNC_ENTRY( 5, GOAL_PNIO_FUNC_DATA_INPUT_SET,         goal_pnioDataInputSet)              \
    GOAL_PNIO_FUNC_ENTRY( 6, GOAL_PNIO_FUNC_APDU_STATUS_GET,        goal_pnioApduStatusGet)             \
    GOAL_PNIO_FUNC_ENTRY( 7, GOAL_PNIO_FUNC_ALARM_NOTIFY_SEND,      goal_pnioAlarmNotifySend)           \
    GOAL_PNIO_FUNC_ENTRY( 8, GOAL_PNIO_FUNC_ALARM_NOTIFY_SEND_ACK,  goal_pnioAlarmNotifySendAck)        \
    GOAL_PNIO_FUNC_ENTRY( 9, GOAL_PNIO_FUNC_MOD_PULL,               goal_pnioModPull)                   \
    GOAL_PNIO_FUNC_ENTRY(10, GOAL_PNIO_FUNC_REC_READ_FINISH,        goal_pnioRecReadFinish)             \
    GOAL_PNIO_FUNC_ENTRY(11, GOAL_PNIO_FUNC_REC_WRITE_FINISH,       goal_pnioRecWriteFinish)            \
    GOAL_PNIO_FUNC_ENTRY(12, GOAL_PNIO_FUNC_DIAG_EXT_CHAN_DIAG_ADD, goal_pnioDiagExtChanDiagAdd)        \
    GOAL_PNIO_FUNC_ENTRY(13, GOAL_PNIO_FUNC_DIAG_CHAN_DIAG_REMOVE,  goal_pnioDiagChanDiagRemove)        \
    GOAL_PNIO_FUNC_ENTRY(14, GOAL_PNIO_FUNC_CYCLIC_CTRL,            goal_pnioCyclicCtrl)                \
    GOAL_PNIO_FUNC_ENTRY(15, GOAL_PNIO_FUNC_SLOT_NEW,               goal_pnioSlotNew)                   \
    GOAL_PNIO_FUNC_ENTRY(16, GOAL_PNIO_FUNC_MOD_NEW,                goal_pnioModNew)                    \
    GOAL_PNIO_FUNC_ENTRY(17, GOAL_PNIO_FUNC_SUBMOD_PULL,            goal_pnioSubmodPull)                \
    GOAL_PNIO_FUNC_ENTRY(18, GOAL_PNIO_FUNC_MOD_PLUG,               goal_pnioModPlug)                   \
    GOAL_PNIO_FUNC_ENTRY(19, GOAL_PNIO_FUNC_VENDOR_ID_SET,          goal_pnioVendorIdSet)               \
    GOAL_PNIO_FUNC_ENTRY(20, GOAL_PNIO_FUNC_DEVICE_ID_SET,          goal_pnioDeviceIdSet)               \
    GOAL_PNIO_FUNC_ENTRY(21, GOAL_PNIO_FUNC_HWREV_SET,              goal_pnioHwRevSet)                  \
    GOAL_PNIO_FUNC_ENTRY(22, GOAL_PNIO_FUNC_SWREV_SET,              goal_pnioSwRevSet)                  \
    GOAL_PNIO_FUNC_ENTRY(23, GOAL_PNIO_FUNC_PROFILE_ID_SET,         goal_pnioProfileIdSet)              \
    GOAL_PNIO_FUNC_ENTRY(24, GOAL_PNIO_FUNC_ORDER_ID_SET,           goal_pnioOrderIdSet)                \
    GOAL_PNIO_FUNC_ENTRY(25, GOAL_PNIO_FUNC_SERIAL_NUM_SET,         goal_pnioSerialNumSet)              \
    GOAL_PNIO_FUNC_ENTRY(26, GOAL_PNIO_FUNC_VENDOR_NAME_SET,        goal_pnioVendorNameSet)             \
    GOAL_PNIO_FUNC_ENTRY(27, GOAL_PNIO_FUNC_PORT_DESC_SET,          goal_pnioPortDescSet)               \
    GOAL_PNIO_FUNC_ENTRY(28, GOAL_PNIO_FUNC_SYS_DESC_SET,           goal_pnioSystemDescSet)             \
    GOAL_PNIO_FUNC_ENTRY(29, GOAL_PNIO_FUNC_NEW,                    goal_pnioNew)                       \
    GOAL_PNIO_FUNC_ENTRY(30, GOAL_PNIO_FUNC_CFG_DCP_FACTORY_RESET_DISABLE_SET, goal_pnioCfgDcpFactoryResetDisableSet)    \
    GOAL_PNIO_FUNC_ENTRY(31, GOAL_PNIO_FUNC_CFG_DCP_ACCEPT_MIXCASE_STATION_SET, goal_pnioCfgDcpAcceptMixcaseStationSet)    \
    GOAL_PNIO_FUNC_ENTRY(32, GOAL_PNIO_FUNC_CFG_VENDOR_ID_SET,      goal_pnioCfgVendorIdSet)            \
    GOAL_PNIO_FUNC_ENTRY(33, GOAL_PNIO_FUNC_CFG_DEVICE_ID_SET,      goal_pnioCfgDeviceIdSet)            \
    GOAL_PNIO_FUNC_ENTRY(34, GOAL_PNIO_FUNC_CFG_VENDOR_NAME_SET,    goal_pnioCfgVendorNameSet)          \
    GOAL_PNIO_FUNC_ENTRY(35, GOAL_PNIO_FUNC_CFG_PORT_NAME_SET,      goal_pnioCfgPortNameSet)            \
    GOAL_PNIO_FUNC_ENTRY(36, GOAL_PNIO_FUNC_CFG_SYSTEM_DESC_SET,    goal_pnioCfgSystemDescSet)          \
    GOAL_PNIO_FUNC_ENTRY(37, GOAL_PNIO_FUNC_CFG_ORDER_ID_SET,       goal_pnioCfgOrderIdSet)             \
    GOAL_PNIO_FUNC_ENTRY(38, GOAL_PNIO_FUNC_CFG_SERIAL_NUM_SET,     goal_pnioCfgSerialNumSet)           \
    GOAL_PNIO_FUNC_ENTRY(39, GOAL_PNIO_FUNC_CFG_HW_REV_SET,         goal_pnioCfgHwRevSet)               \
    GOAL_PNIO_FUNC_ENTRY(40, GOAL_PNIO_FUNC_CFG_SW_REV_PREFIX_SET,  goal_pnioCfgSwRevPrefixSet)         \
    GOAL_PNIO_FUNC_ENTRY(41, GOAL_PNIO_FUNC_CFG_SW_REV_FUNC_ENH_SET, goal_pnioCfgSwRevFuncEnhSet)       \
    GOAL_PNIO_FUNC_ENTRY(42, GOAL_PNIO_FUNC_CFG_SW_REV_BUGFIX_SET,  goal_pnioCfgSwRevBugfixSet)         \
    GOAL_PNIO_FUNC_ENTRY(43, GOAL_PNIO_FUNC_CFG_SW_REV_INT_CHG_SET, goal_pnioCfgSwRevIntChgSet)         \
    GOAL_PNIO_FUNC_ENTRY(44, GOAL_PNIO_FUNC_CFG_SW_REV_CNT_SET,     goal_pnioCfgSwRevCntSet)            \
    GOAL_PNIO_FUNC_ENTRY(45, GOAL_PNIO_FUNC_CFG_IM_1_TAG_FUNC_SET,  goal_pnioCfgIm1TagFuncSet)          \
    GOAL_PNIO_FUNC_ENTRY(46, GOAL_PNIO_FUNC_CFG_IM_1_TAG_LOC_SET,   goal_pnioCfgIm1TagLocSet)           \
    GOAL_PNIO_FUNC_ENTRY(47, GOAL_PNIO_FUNC_CFG_IM_2_DATE_SET,      goal_pnioCfgIm2DateSet)             \
    GOAL_PNIO_FUNC_ENTRY(48, GOAL_PNIO_FUNC_CFG_IM_3_DESC_SET,      goal_pnioCfgIm3DescSet)             \
    GOAL_PNIO_FUNC_ENTRY(49, GOAL_PNIO_FUNC_CFG_IM_4_SIG_SET,       goal_pnioCfgIm4SigSet)              \
    GOAL_PNIO_FUNC_ENTRY(50, GOAL_PNIO_FUNC_CFG_DEV_DAP_SIMPLE_SET, goal_pnioCfgDevDapSimpleSet)        \
    GOAL_PNIO_FUNC_ENTRY(51, GOAL_PNIO_FUNC_CFG_DEV_DAP_API_SET,    goal_pnioCfgDevDapApiSet)           \
    GOAL_PNIO_FUNC_ENTRY(52, GOAL_PNIO_FUNC_CFG_DEV_DAP_SLOT_SET,   goal_pnioCfgDevDapSlotSet)          \
    GOAL_PNIO_FUNC_ENTRY(53, GOAL_PNIO_FUNC_CFG_DEV_DAP_SUBSLOT_SET, goal_pnioCfgDevDapSubslotSet)      \
    GOAL_PNIO_FUNC_ENTRY(54, GOAL_PNIO_FUNC_CFG_DEV_DAP_MOD_SET,    goal_pnioCfgDevDapModuleSet)        \
    GOAL_PNIO_FUNC_ENTRY(55, GOAL_PNIO_FUNC_CFG_DEV_DAP_SUBMOD_SET, goal_pnioCfgDevDapSubmoduleSet)     \
    GOAL_PNIO_FUNC_ENTRY(56, GOAL_PNIO_FUNC_CFG_NET_LINK_SAFETY_SET, goal_pnioCfgNetLinkSafetySet)      \
    GOAL_PNIO_FUNC_ENTRY(57, GOAL_PNIO_FUNC_CFG_NEW_IO_DATA_CB_SET, goal_pnioCfgNewIoDataCbSet)         \
    GOAL_PNIO_FUNC_ENTRY(58, GOAL_PNIO_FUNC_CFG_LLDP_ORG_EXT_SET,   goal_pnioCfgLldpOrgExtSet)          \
    GOAL_PNIO_FUNC_ENTRY(59, GOAL_PNIO_FUNC_CFG_LLDP_OPT_TLV_SET,   goal_pnioCfgLldpOptTlvSet)          \
    GOAL_PNIO_FUNC_ENTRY(60, GOAL_PNIO_FUNC_CFG_LLDP_GEN_MAC_SET,   goal_pnioCfgLldpGenMacSet)          \
    GOAL_PNIO_FUNC_ENTRY(61, GOAL_PNIO_FUNC_CFG_IM_1_4_SUPPORT_SET, goal_pnioCfgIm14SupportSet)         \
    GOAL_PNIO_FUNC_ENTRY(62, GOAL_PNIO_FUNC_CFG_IM_1_4_CB_SET,      goal_pnioCfgIm14CbSet)              \
    GOAL_PNIO_FUNC_ENTRY(63, GOAL_PNIO_FUNC_CFG_IM_0_CB_SET,        goal_pnioCfgIm0CbSet)               \
    GOAL_PNIO_FUNC_ENTRY(64, GOAL_PNIO_FUNC_CFG_IM_0_FILTER_CB_SET, goal_pnioCfgIm0FilterDataCbSet)     \
    GOAL_PNIO_FUNC_ENTRY(65, GOAL_PNIO_FUNC_CFG_REC_DATA_BUSY_BUFSIZE_SET, goal_pnioCfgRecDataBusyBufsizeSet)    \
    GOAL_PNIO_FUNC_ENTRY(66, GOAL_PNIO_FUNC_CFG_RPC_FRAG_REQ_LEN_MAX_SET, goal_pnioCfgRpcFragReqLenMaxSet)    \
    GOAL_PNIO_FUNC_ENTRY(67, GOAL_PNIO_FUNC_CFG_RPC_FRAG_MAX_CNT_SET, goal_pnioCfgRpcFragMaxCntSet)     \
    GOAL_PNIO_FUNC_ENTRY(68, GOAL_PNIO_FUNC_CFG_RPC_FRAG_ENABLE_SET, goal_pnioCfgRpcFragEnableSet)      \
    GOAL_PNIO_FUNC_ENTRY(69, GOAL_PNIO_FUNC_CFG_RPC_SESSION_MAX_CNT_SET, goal_pnioCfgRpcSessionMaxCntSet)    \
    GOAL_PNIO_FUNC_ENTRY(70, GOAL_PNIO_FUNC_CFG_DIAG_BUF_MAX_CNT_SET, goal_pnioCfgDiagBufMaxCntSet)     \
    GOAL_PNIO_FUNC_ENTRY(71, GOAL_PNIO_FUNC_CFG_DIAG_BUF_MAX_DATA_SIZE_SET, goal_pnioCfgDiagBufMaxDataSizeSet)    \
    GOAL_PNIO_FUNC_ENTRY(72, GOAL_PNIO_FUNC_CFG_IOCR_BLOCKS_MAX_SET, goal_pnioCfgIocrBlocksMaxSet)      \
    GOAL_PNIO_FUNC_ENTRY(73, GOAL_PNIO_FUNC_CFG_CR_MAX_CNT_SET,     goal_pnioCfgCrMaxCntSet)            \
    GOAL_PNIO_FUNC_ENTRY(74, GOAL_PNIO_FUNC_CFG_AR_MAX_CNT_SET,     goal_pnioCfgArMaxCntSet)            \
    GOAL_PNIO_FUNC_ENTRY(75, GOAL_PNIO_FUNC_CFG_API_MAX_CNT_SET,    goal_pnioCfgApiMaxCntSet)           \
    GOAL_PNIO_FUNC_ENTRY(76, GOAL_PNIO_FUNC_CFG_SLOT_MAX_CNT_SET,   goal_pnioCfgSlotMaxCntSet)          \
    GOAL_PNIO_FUNC_ENTRY(77, GOAL_PNIO_FUNC_CFG_SUBSLOT_MAX_CNT_SET, goal_pnioCfgSubslotMaxCntSet)      \
    GOAL_PNIO_FUNC_ENTRY(78, GOAL_PNIO_FUNC_CFG_SUBSLOT_IF_SET,     goal_pnioCfgSubslotIfSet)           \
    GOAL_PNIO_FUNC_ENTRY(79, GOAL_PNIO_FUNC_CFG_SUBSLOT_PORT_SET,   goal_pnioCfgSubslotPortSet)         \
    GOAL_PNIO_FUNC_ENTRY(80, GOAL_PNIO_FUNC_DEVICE_NAME_SET,        goal_pnioDeviceNameSet)             \
    GOAL_PNIO_FUNC_ENTRY(81, GOAL_PNIO_FUNC_ALARM_PROCESS_SEND,     goal_pnioAlarmProcessSend)          \
    GOAL_PNIO_FUNC_ENTRY(82, GOAL_PNIO_FUNC_DM_SUBSLOT_ADD,         goal_pnioDmSubslotAdd)              \
    GOAL_PNIO_FUNC_ENTRY(83, GOAL_PNIO_FUNC_DM_SUBSLOT_IOXS_ADD,    goal_pnioDmSubslotIoxsAdd)          \
    GOAL_PNIO_FUNC_ENTRY(84, GOAL_PNIO_FUNC_DM_APDU_ADD,            goal_pnioDmApduAdd)                 \
    GOAL_PNIO_FUNC_ENTRY(85, GOAL_PNIO_FUNC_DM_DP_ADD,              goal_pnioDmDpAdd)                   \
    GOAL_PNIO_FUNC_ENTRY(86, GOAL_PNIO_FUNC_CFG_SNMP_ID_SET,        goal_pnioCfgSnmpIdSet)              \
    GOAL_PNIO_FUNC_ENTRY(87, GOAL_PNIO_FUNC_CFG_FLG_MRP_SET,        goal_pnioCfgFlgMrpCfgSet)           \
    GOAL_PNIO_FUNC_ENTRY(88, GOAL_PNIO_FUNC_DM_RESET,               goal_pnioDmReset)                   \
    GOAL_PNIO_FUNC_ENTRY(89, GOAL_PNIO_FUNC_CFG_NUM_PROC_AL_BUF_SET, goal_pnioCfgNumProcAlBufSet)       \
    GOAL_PNIO_FUNC_ENTRY(90, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_INIT, goal_pnioAlarmProcessQueueInit)   \
    GOAL_PNIO_FUNC_ENTRY(91, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_RESET, goal_pnioAlarmProcessQueueReset) \
    GOAL_PNIO_FUNC_ENTRY(92, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_ADD, goal_pnioAlarmProcessQueueAdd)     \
    GOAL_PNIO_FUNC_ENTRY(93, GOAL_PNIO_FUNC_ALARM_PROCESS_QUEUE_SEND, goal_pnioAlarmProcessQueueSend)   \
    GOAL_PNIO_FUNC_ENTRY(94, GOAL_PNIO_FUNC_CONN_REQ_PROCESS,       goal_pnioConnReqProcess)            \

/* create function id enum */
#undef GOAL_PNIO_FUNC_ENTRY
#define GOAL_PNIO_FUNC_ENTRY(id, name, ...) name = id,
typedef enum {
    GOAL_PNIO_FUNC_LIST
} GOAL_PNIO_FUNC_ID_T;


#define GOAL_PNIO_FUNC_CALLBACK 0               /**< callback function id */


/* callback function list */
#define GOAL_PNIO_FUNC_CB_LIST \
    /*                      id, name,                                       function */                         \
    GOAL_PNIO_FUNC_CB_ENTRY( 0, GOAL_PNIO_CB_ID_ALARM_ACK_TIMEOUT,          goal_pnioCbAlarmAckTimeout)         \
    GOAL_PNIO_FUNC_CB_ENTRY( 1, GOAL_PNIO_CB_ID_ALARM_NOTIFY_ACK,           goal_pnioCbAlarmNotifyAck)          \
    GOAL_PNIO_FUNC_CB_ENTRY( 2, GOAL_PNIO_CB_ID_ALARM_NOTIFY,               goal_pnioCbAlarmNotify)             \
    GOAL_PNIO_FUNC_CB_ENTRY( 3, GOAL_PNIO_CB_ID_APPL_READY,                 goal_pnioCbApplReady)               \
    GOAL_PNIO_FUNC_CB_ENTRY( 4, GOAL_PNIO_CB_ID_BLINK,                      goal_pnioCbBlink)                   \
    GOAL_PNIO_FUNC_CB_ENTRY( 5, GOAL_PNIO_CB_ID_CONNECT_FINISH,             goal_pnioCbConnectFinish)           \
    GOAL_PNIO_FUNC_CB_ENTRY( 6, GOAL_PNIO_CB_ID_CONNECT_REQUEST,            goal_pnioCbConnectRequest)          \
    GOAL_PNIO_FUNC_CB_ENTRY( 7, GOAL_PNIO_CB_ID_CONNECT_REQUEST_EXP_START,  goal_pnioCbConnectRequestExpStart)  \
    GOAL_PNIO_FUNC_CB_ENTRY( 8, GOAL_PNIO_CB_ID_END_OF_PARAM,               goal_pnioCbEndOfParam)              \
    GOAL_PNIO_FUNC_CB_ENTRY( 9, GOAL_PNIO_CB_ID_END_OF_PARAM_PLUG,          goal_pnioCbEndOfParamPlug)          \
    GOAL_PNIO_FUNC_CB_ENTRY(10, GOAL_PNIO_CB_ID_EXP_SUBMOD,                 goal_pnioCbExpSubmod)               \
    GOAL_PNIO_FUNC_CB_ENTRY(11, GOAL_PNIO_CB_ID_FACTORY_RESET,              goal_pnioCbFactoryReset)            \
    GOAL_PNIO_FUNC_CB_ENTRY(13, GOAL_PNIO_CB_ID_IO_DATA_TIMEOUT,            goal_pnioCbIoDataTimeout)           \
    GOAL_PNIO_FUNC_CB_ENTRY(14, GOAL_PNIO_CB_ID_NET_IP_SET,                 goal_pnioCbNetIpSet)                \
    GOAL_PNIO_FUNC_CB_ENTRY(15, GOAL_PNIO_CB_ID_NEW_AR,                     goal_pnioCbNewAr)                   \
    GOAL_PNIO_FUNC_CB_ENTRY(17, GOAL_PNIO_CB_ID_NEW_IO_DATA,                goal_pnioCbNewIoData)               \
    GOAL_PNIO_FUNC_CB_ENTRY(19, GOAL_PNIO_CB_ID_PLUG_READY,                 goal_pnioCbPlugReady)               \
    GOAL_PNIO_FUNC_CB_ENTRY(20, GOAL_PNIO_CB_ID_READ_RECORD,                goal_pnioCbReadRecord)              \
    GOAL_PNIO_FUNC_CB_ENTRY(21, GOAL_PNIO_CB_ID_RELEASE_AR,                 goal_pnioCbReleaseAr)               \
    GOAL_PNIO_FUNC_CB_ENTRY(22, GOAL_PNIO_CB_ID_RESET_TO_FACTORY,           goal_pnioCbResetToFactory)          \
    GOAL_PNIO_FUNC_CB_ENTRY(23, GOAL_PNIO_CB_ID_STATION_NAME,               goal_pnioCbStationName)             \
    GOAL_PNIO_FUNC_CB_ENTRY(24, GOAL_PNIO_CB_ID_WRITE_RECORD,               goal_pnioCbWriteRecord)             \
    GOAL_PNIO_FUNC_CB_ENTRY(25, GOAL_PNIO_CB_ID_INIT,                       goal_pnioCbInit)                    \
    GOAL_PNIO_FUNC_CB_ENTRY(26, GOAL_PNIO_CB_ID_LLDP_UPDATE,                goal_pnioCbLldpUpdate)              \
    GOAL_PNIO_FUNC_CB_ENTRY(27, GOAL_PNIO_CB_ID_CONN_REQ_EXP_FINISH,        goal_pnioCbConnReqExpFinish)        \
    GOAL_PNIO_FUNC_CB_ENTRY(28, GOAL_PNIO_CB_ID_STATION_NAME_VERIFY,        goal_pnioCbStationNameVerify)       \
    GOAL_PNIO_FUNC_CB_ENTRY(29, GOAL_PNIO_CB_ID_NET_IP_SET_VERIFY,          goal_pnioCbNetIpSetVerify)


/* create callback function id enum */
#undef GOAL_PNIO_FUNC_CB_ENTRY
#define GOAL_PNIO_FUNC_CB_ENTRY(id, name, ...) name = id,
typedef enum {
    GOAL_PNIO_FUNC_CB_LIST
} GOAL_PNIO_FUNC_CB_ID_T;


/****************************************************************************/
/* PROFINET Status and Error Codes */
/****************************************************************************/

/* 5.2.6.2 Coding of the field ErrorCode */
#define GOAL_PNIO_ERR_CODE_MANU_SPEC                        0x20    /* manufacturer specific */

/* 5.2.6.3 Coding of the field ErrorDecode */
#define GOAL_PNIO_ERR_DECODE_RESERVED                       0x00
#define GOAL_PNIO_ERR_DECODE_PNIORW                         0x80    /* context with user error codes */
#define GOAL_PNIO_ERR_DECODE_PNIO                           0x81    /* context with other services */
#define GOAL_PNIO_ERR_DECODE_MANU_SPEC                      0x82    /* manufacturer specific */

#define GOAL_PNIO_ERR_CODE1_PNIORW_ACCESS_INVAL_IDX         (0xB0 | 0x00)
#define GOAL_PNIO_ERR_CODE1_PNIORW_ACCESS_INVAL_RANGE       (0xB0 | 0x07)


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
GOAL_STATUS_T goal_pnioInitImpl(
    void
);

GOAL_STATUS_T goal_pnioNewImpl(
    struct GOAL_PNIO_T **ppPnio,                /**< PROFINET handle ref */
    const uint32_t id,                          /**< instance id */
    GOAL_PNIO_FUNC_CB_T pFunc                   /**< PROFINET callback function */
);

GOAL_STATUS_T goal_pnioSlotNewImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioSubslotNewImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioModNewImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod                              /**< module id */
);

GOAL_STATUS_T goal_pnioSubmodNewImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod,                          /**< submodule id */
    GOAL_PNIO_MOD_TYPE_T type,                  /**< submodule type */
    uint16_t sizeInput,                         /**< input size */
    uint16_t sizeOutput,                        /**< output size */
    GOAL_BOOL_T flgAutogen                      /**< auto-generate flag */
);

GOAL_STATUS_T goal_pnioModPlugImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint32_t idMod                              /**< module id */
);

GOAL_STATUS_T goal_pnioSubmodPlugImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
);

GOAL_STATUS_T goal_pnioModPullImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot                             /**< slot */
);

GOAL_STATUS_T goal_pnioSubmodPullImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
);

GOAL_STATUS_T goal_pnioDataOutputGetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    char *pBuf,                                 /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T *pStateIops                /**< producer state */
);

GOAL_STATUS_T goal_pnioDataInputSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    const char *pBuf,                           /**< data buffer */
    uint16_t len,                               /**< data buffer length */
    GOAL_PNIO_IOXS_T stateIops                  /**< producer state */
);

GOAL_STATUS_T goal_pnioApduStatusGetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    GOAL_PNIO_APDU_STATUS_T *pStatusApdu        /**< APDU status */
);

GOAL_STATUS_T goal_pnioAlarmNotifySendImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t *pNrAlarmSeq,                      /**< sequence nr ref */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
);

GOAL_STATUS_T goal_pnioAlarmNotifySendAckImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_AR_ID_T idAr,                     /**< AR id */
    uint32_t prio,                              /**< priority */
    const GOAL_PNIO_ALARM_NOTIFY_T *pAlarmNotify, /**< notify structure */
    GOAL_PNIO_STATUS_T *pStatus,                /**< PROFINET status */
    uint16_t lenDataUser,                       /**< user data length */
    void *pDataUser                             /**< user data ptr */
);

GOAL_STATUS_T goal_pnioAlarmProcessSendImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
);

GOAL_STATUS_T goal_pnioRecReadFinishImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PNIO Status */
    const uint8_t *pData,                       /**< record data */
    uint16_t len,                               /**< record data length */
    uint32_t numSeq                             /**< sequence number */
);

GOAL_STATUS_T goal_pnioRecWriteFinishImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    int32_t hdl,                                /**< record data busy index */
    GOAL_PNIO_STATUS_T *pStatusPnio,            /**< PNIO Status */
    uint32_t numSeq                             /**< sequence number */
);

GOAL_STATUS_T goal_pnioDiagChanDiagAddImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T *pHdl,              /**< handle ptr */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t chan,                              /**< channel number */
    uint16_t numErr,                            /**< error number */
    GOAL_BOOL_T flgMaintReq,                    /**< maintainance required flag */
    GOAL_BOOL_T flgMaintDem,                    /**< maintainance demanded flag */
    GOAL_BOOL_T flgSubmitAlarm                  /**< submit alarm flag */
);

GOAL_STATUS_T goal_pnioDiagExtChanDiagAddImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T *pHdl,              /**< handle ptr */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t chan,                              /**< channel number */
    uint16_t numErr,                            /**< error number */
    uint16_t typeExtChanErr,                    /**< extended channel error type */
    uint32_t valExtChanAdd,                     /**< extended channel error value */
    GOAL_BOOL_T flgMaintReq,                    /**< maintainance required flag */
    GOAL_BOOL_T flgMaintDem,                    /**< maintainance demanded flag */
    GOAL_BOOL_T flgSubmitAlarm,                 /**< submit alarm flag */
    uint16_t typeAlarm                          /**< alarm type */
);

GOAL_STATUS_T goal_pnioDiagChanDiagRemoveImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_PNIO_DIAG_HANDLE_T hdl,                /**< diagnosis handle */
    GOAL_BOOL_T flgSubmitAlarm                  /**< submit alarm flag */
);

GOAL_STATUS_T goal_pnioCyclicCtrlImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    GOAL_BOOL_T flgCyclic                       /**< cyclic data enable flag */
);

GOAL_STATUS_T goal_pnioVendorIdSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< vendor id */
);

GOAL_STATUS_T goal_pnioDeviceIdSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id                                 /**< device id */
);

GOAL_STATUS_T goal_pnioDeviceNameSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    char *strName,                              /**< device name */
    uint32_t lenName,                           /**< device name length */
    GOAL_BOOL_T flgPerm,                        /**< permanent flag */
    GOAL_BOOL_T flgCb                           /**< run-callback flag */
);

GOAL_STATUS_T goal_pnioHwRevSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t revHw                              /**< hardware revision */
);

GOAL_STATUS_T goal_pnioSwRevSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint8_t chrPrefix,                          /**< prefix */
    uint8_t idFuncEnh,                          /**< functional enhancement */
    uint8_t idBugfix,                           /**< bugfix */
    uint8_t idIntChange,                        /**< internal change */
    uint16_t cntRev                             /**< revision counter */
);

GOAL_STATUS_T goal_pnioProfileIdSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint16_t id,                                /**< profile id */
    uint16_t type                               /**< profile specific type */
);

GOAL_STATUS_T goal_pnioOrderIdSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strOrder,                       /**< order id */
    uint32_t lenOrder                           /**< order id length */
);

GOAL_STATUS_T goal_pnioSerialNumSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSerial,                      /**< serial number */
    uint32_t lenSerial                          /**< serial number length */
);

GOAL_STATUS_T goal_pnioVendorNameSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strVendor,                      /**< vendor name */
    uint32_t lenVendor                          /**< vendor name length */
);

GOAL_STATUS_T goal_pnioPortDescSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strPort,                        /**< port description */
    uint32_t lenPort                            /**< port description length */
);

GOAL_STATUS_T goal_pnioSystemDescSetImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    const char *strSys,                         /**< system description */
    uint32_t lenSys                             /**< system description length */
);

GOAL_STATUS_T goal_pnioCfgDcpFactoryResetDisableSetImpl(
    GOAL_BOOL_T flgDcpFactoryResetDisable       /**< DCP Factory Reset Disable */
);

GOAL_STATUS_T goal_pnioCfgDcpAcceptMixcaseStationSetImpl(
    GOAL_BOOL_T flgDcpAcceptMixcaseStation      /**< DCP Accept Mixcase Stationname */
);

GOAL_STATUS_T goal_pnioCfgVendorIdSetImpl(
    uint16_t idVendor                           /**< Vendor Id */
);

GOAL_STATUS_T goal_pnioCfgDeviceIdSetImpl(
    uint16_t idDevice                           /**< Device Id */
);

GOAL_STATUS_T goal_pnioCfgVendorNameSetImpl(
    const char *strVendor                       /**< Vendor Name */
);

#define goal_pnioCfgPortNameSetImpl goal_pnioCfgPortDescSetImpl
GOAL_STATUS_T goal_pnioCfgPortDescSetImpl(
    const char *strDesc                         /**< Port Description */
);

GOAL_STATUS_T goal_pnioCfgPortNameSetImpl(
    const char *strDescPort                     /**< Port Name */
);

GOAL_STATUS_T goal_pnioCfgSystemDescSetImpl(
    const char *strSystem                       /**< System Description */
);

GOAL_STATUS_T goal_pnioCfgOrderIdSetImpl(
    const char *strOrder                        /**< Order Id */
);

GOAL_STATUS_T goal_pnioCfgSerialNumSetImpl(
    const char *strNumSerial                    /**< Serial Number */
);

GOAL_STATUS_T goal_pnioCfgHwRevSetImpl(
    uint16_t idRevHw                            /**< Hardware Revision */
);

GOAL_STATUS_T goal_pnioCfgSwRevPrefixSetImpl(
    const char chrRevSwPrefix                   /**< Software Revision Prefix */
);

GOAL_STATUS_T goal_pnioCfgSwRevFuncEnhSetImpl(
    uint8_t idRevSwFuncEnh                      /**< Software Revision Functional Enhancement */
);

GOAL_STATUS_T goal_pnioCfgSwRevBugfixSetImpl(
    uint8_t idRevSwBugfix                       /**< Software Revision Bugfix */
);

GOAL_STATUS_T goal_pnioCfgSwRevIntChgSetImpl(
    uint8_t idRevSwIntChg                       /**< Software Revision Internal Change */
);

GOAL_STATUS_T goal_pnioCfgSwRevCntSetImpl(
    uint16_t idRevSwRevCnt                      /**< Software Revision Count */
);

GOAL_STATUS_T goal_pnioCfgIm1TagFuncSetImpl(
    const char *strIm1TagFunc                   /**< I&M1 Tag Function */
);

GOAL_STATUS_T goal_pnioCfgIm1TagLocSetImpl(
    const char *strIm1TagLoc                    /**< I&M1 Tag Location */
);

GOAL_STATUS_T goal_pnioCfgIm2DateSetImpl(
    const char *strIm2Date                      /**< I&M2 Date */
);

GOAL_STATUS_T goal_pnioCfgIm3DescSetImpl(
    const char *strIm3Desc                      /**< I&M3 Descriptor */
);

GOAL_STATUS_T goal_pnioCfgIm4SigSetImpl(
    const char *strIm4Sig                       /**< I&M4 Signature */
);

GOAL_STATUS_T goal_pnioCfgDevDapSimpleSetImpl(
    GOAL_BOOL_T flgDevDapSimple                 /**< Device DAP Simple Mode */
);

GOAL_STATUS_T goal_pnioCfgDevDapApiSetImpl(
    uint32_t idDevDapApi                        /**< Device DAP API */
);

GOAL_STATUS_T goal_pnioCfgDevDapSlotSetImpl(
    uint16_t idDevDapSlot                       /**< Device DAP Slot */
);

GOAL_STATUS_T goal_pnioCfgDevDapSubslotSetImpl(
    uint16_t idDevDapSubslot                    /**< Device DAP Subslot */
);

GOAL_STATUS_T goal_pnioCfgDevDapModuleSetImpl(
    uint32_t idDevDapMod                        /**< Device DAP Module */
);

GOAL_STATUS_T goal_pnioCfgDevDapSubmoduleSetImpl(
    uint32_t idDevDapSubmod                     /**< Device DAP Submodule */
);

GOAL_STATUS_T goal_pnioCfgNetLinkSafetySetImpl(
    GOAL_BOOL_T flgNetLinkSafety                /**< Net Link Safety */
);

GOAL_STATUS_T goal_pnioCfgNewIoDataCbSetImpl(
    GOAL_BOOL_T flgCbNewIoData                  /**< New IO Data Callback Enable */
);

GOAL_STATUS_T goal_pnioCfgLldpOrgExtSetImpl(
    GOAL_BOOL_T flgLldpOrgExt                   /**< LLDP Org Ext */
);

GOAL_STATUS_T goal_pnioCfgLldpOptTlvSetImpl(
    GOAL_BOOL_T flgLldpOptTlv                   /**< LLDP Optional TLVs */
);

GOAL_STATUS_T goal_pnioCfgLldpGenMacSetImpl(
    GOAL_BOOL_T flgLldpGenMac                   /**< LLDP Generate Port MAC Addresses */
);

GOAL_STATUS_T goal_pnioCfgIm14SupportSetImpl(
    GOAL_BOOL_T flgIm14Support                  /**< I&M 1-4 Support */
);

GOAL_STATUS_T goal_pnioCfgIm14CbSetImpl(
    GOAL_BOOL_T flgIm14Cb                       /**< I&M 1-4 Callback */
);

GOAL_STATUS_T goal_pnioCfgIm0CbSetImpl(
    GOAL_BOOL_T flgIm0Cb                        /**< I&M 0 Callback */
);

GOAL_STATUS_T goal_pnioCfgIm0FilterDataCbSetImpl(
    GOAL_BOOL_T flgIm0FilterCb                  /**< I&M 0 FilterData Callback */
);

GOAL_STATUS_T goal_pnioCfgRecDataBusyBufsizeSetImpl(
    unsigned int cntRecDataBusyBufsize          /**< Record Data Storage Size */
);

GOAL_STATUS_T goal_pnioCfgRpcFragReqLenMaxSetImpl(
    unsigned int sizeRpcFragMaxReqLen           /**< RPC Fragmentation Maximum Request Length */
);

GOAL_STATUS_T goal_pnioCfgRpcFragMaxCntSetImpl(
    unsigned int numRpcFragMax                  /**< RPC Maximum Fragment Count */
);

GOAL_STATUS_T goal_pnioCfgRpcFragEnableSetImpl(
    GOAL_BOOL_T flgRpcFragSupport               /**< RPC Fragmentation Support Enable */
);

GOAL_STATUS_T goal_pnioCfgRpcSessionMaxCntSetImpl(
    unsigned int numRpcSessions                 /**< RPC Session Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgDiagBufMaxCntSetImpl(
    unsigned int numDiagBufMax                  /**< Diagnosis Maximum Buffer Count */
);

GOAL_STATUS_T goal_pnioCfgDiagBufMaxDataSizeSetImpl(
    unsigned int numDiagDataSizeMax             /**< Diagnosis Maximum Data Size */
);

GOAL_STATUS_T goal_pnioCfgIocrBlocksMaxSetImpl(
    unsigned int numIocrBlocksMax               /**< IOCR Maximum Blocks */
);

GOAL_STATUS_T goal_pnioCfgCrMaxCntSetImpl(
    unsigned int numCrMax                       /**< Communication Relation Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgArMaxCntSetImpl(
    unsigned int numArMax                       /**< Application Relation Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgApiMaxCntSetImpl(
    unsigned int numApiMax                      /**< API Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSlotMaxCntSetImpl(
    unsigned int numSlotMax                     /**< Slot Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSubslotMaxCntSetImpl(
    unsigned int numSubslotMax                  /**< Subslot Maximum Count */
);

GOAL_STATUS_T goal_pnioCfgSubslotIfSetImpl(
    uint16_t idSubslotIf                        /**< interface subslot */
);

GOAL_STATUS_T goal_pnioCfgSubslotPortSetImpl(
    uint16_t idSubslotPort                      /**< port subslot */
);

GOAL_STATUS_T goal_pnioCfgSnmpIdSetImpl(
    uint32_t idSnmp                             /**< SNMP id */
);

GOAL_STATUS_T goal_pnioCfgNumProcAlBufSetImpl(
    uint8_t numProcAlBuf                        /**< Number of slots in Process alarm queue */
);

GOAL_STATUS_T goal_pnioInstGetById(
    GOAL_PNIO_T **ppPnio,                       /**< [out] PROFINET instance */
    uint32_t id                                 /**< PROFINET instance id */
);

GOAL_STATUS_T goal_pnioCfgFlgMrpCfgSetImpl(
    GOAL_BOOL_T flgMrpCfg                       /**< MRP config flag */
);


#if GOAL_CONFIG_MEDIA_MI_DM == 1
GOAL_STATUS_T goal_pnioDmSubmodPlug(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t idMod,                             /**< module id */
    uint32_t idSubmod                           /**< submodule id */
);

GOAL_STATUS_T goal_pnioDmSubslotAddImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerFrom,                    /**< MI DM 'from peer' handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDataOut,          /**< [out] partition for output data */
    GOAL_MI_DM_PART_T **ppPartDataIn,           /**< [out] partition for input data */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot,                         /**< subslot */
    uint32_t lenDataOut,                        /**< output data length */
    uint32_t lenDataIn                          /**< input data length */
);


GOAL_STATUS_T goal_pnioDmSubslotIoxsAddImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerFrom,                    /**< MI DM 'from peer' handle */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartIocsOut,          /**< [out] partition for output IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsOut,          /**< [out] partition for output IOPS */
    GOAL_MI_DM_PART_T **ppPartIocsIn,           /**< [out] partition for input IOCS */
    GOAL_MI_DM_PART_T **ppPartIopsIn,           /**< [out] partition for input IOPS */
    uint32_t idApi,                             /**< API */
    uint16_t idSlot,                            /**< slot */
    uint16_t idSubslot                          /**< subslot */
);


GOAL_STATUS_T goal_pnioDmApduAddImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartApduOut           /**< [out] partition for output APDU data */
);


GOAL_STATUS_T goal_pnioDmDpAddImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    uint32_t idMiDmPeerTo,                      /**< MI DM 'to peer' handle */
    GOAL_MI_DM_PART_T **ppPartDp                /**< [out] partition for data provider status */
);

GOAL_STATUS_T goal_pnioDmResetImpl(
    GOAL_PNIO_T *pPnio                          /**< PROFINET instance */
);
#endif /* GOAL_CONFIG_MEDIA_MI_DM == 1 */

GOAL_STATUS_T goal_pnioSubslotStateSetImpl(
    GOAL_PNIO_T *pPnio,                         /**< GOAL PROFINET handle */
    uint32_t idApi,                             /**< API id */
    uint16_t idSlot,                            /**< slot id */
    uint16_t idSubslot,                         /**< subslot id */
    uint16_t state                              /**< state override */
);

GOAL_STATUS_T goal_pnioConfClassGetImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_CC_T *pIdConfClass                /**< [out] conformance class */
);

GOAL_STATUS_T goal_pnioConfClassSetImpl(
    GOAL_PNIO_T *pPnio,                         /**< PROFINET instance */
    GOAL_PNIO_CC_T idConfClass                  /**< conformance class */
);

GOAL_STATUS_T goal_pnioConfTestGetImpl(
    const char **pStrPnioStd,                   /**< [out] PROFINET standard */
    const char **pStrTestSpec,                  /**< [out] test specification */
    const char **pStrTestcases,                 /**< [out] testcases */
    const char **pStrArt,                       /**< [out] ART tester */
    const char **pStrTedCheck,                  /**< [out] TED check */
    const char **pStrPnio,                      /**< [out] PROFINET version */
    const char **pStrGsd                        /**< [out] GSD version */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueInitImpl(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueAddImpl(
    struct GOAL_PNIO_T *pPnio,                  /**< PROFINET handle */
    uint32_t api,                               /**< API number */
    uint16_t slot,                              /**< slot number */
    uint16_t subslot,                           /**< subslot number */
    uint16_t usi,                               /**< user structure id */
    uint16_t lenData,                           /**< data length */
    uint8_t *pData                              /**< data */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueSendImpl(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioAlarmProcessQueueResetImpl(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);

GOAL_STATUS_T goal_pnioConnReqProcess(
    GOAL_PNIO_T *pPnio                          /**< PROFINET handle */
);


/****************************************************************************/
/* Inline APIs */
/****************************************************************************/


/****************************************************************************/
/** Initialize PROFINET for local, AC and CC
 *
 * @returns GOAL_STATUS_T result
 */
static GOAL_TARGET_INLINE GOAL_STATUS_T goal_pnioInitMulti(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

#if (GOAL_CONFIG_GEN_CTC_AC == 1)
    /* initialize CTC AC stack */
    res = goal_pnioInitAc();
    if (GOAL_RES_ERR(res)) {
        return res;
    }
#endif

#if (GOAL_CONFIG_GEN_CTC_CC == 1)
    /* initialize CTC CC stack */
    res = goal_pnioInitCc();
    if (GOAL_RES_ERR(res)) {
        return res;
    }

#elif GOAL_CONFIG_PNIO_LOCAL == 1

    /* initialize local stack */
    res = goal_pnioInitImpl();
    if (GOAL_RES_ERR(res)) {
        return res;
    }
#endif

    return res;
}


/****************************************************************************/
/* Mapping of functions which can be overload */
/****************************************************************************/
#ifndef goal_pnioInit
# define goal_pnioInit goal_pnioInitMulti
#endif

#if (GOAL_CONFIG_GEN_CTC_AC == 1)
#  define goal_pnioNew goal_pnioNewAc
#else
#  define goal_pnioNew goal_pnioNewImpl
#endif

#ifndef goal_pnioSlotNew
# define goal_pnioSubslotNew goal_pnioSubslotNewImpl
#endif

#ifndef goal_pnioSlotNew
# define goal_pnioSlotNew goal_pnioSlotNewImpl
#endif

#ifndef goal_pnioModNew
# define goal_pnioModNew goal_pnioModNewImpl
#endif

#ifndef goal_pnioSubmodNew
# define goal_pnioSubmodNew goal_pnioSubmodNewImpl
#endif

#ifndef goal_pnioModPlug
# define goal_pnioModPlug goal_pnioModPlugImpl
#endif

#ifndef goal_pnioSubmodPlug
# define goal_pnioSubmodPlug goal_pnioSubmodPlugImpl
#endif

#ifndef goal_pnioModPull
# define goal_pnioModPull goal_pnioModPullImpl
#endif

#ifndef goal_pnioSubmodPull
# define goal_pnioSubmodPull goal_pnioSubmodPullImpl
#endif

#ifndef goal_pnioDataOutputGet
# define goal_pnioDataOutputGet goal_pnioDataOutputGetImpl
#endif

#ifndef goal_pnioDataInputSet
# define goal_pnioDataInputSet goal_pnioDataInputSetImpl
#endif

#ifndef goal_pnioApduStatusGet
# define goal_pnioApduStatusGet goal_pnioApduStatusGetImpl
#endif

#ifndef goal_pnioAlarmNotifySend
# define goal_pnioAlarmNotifySend goal_pnioAlarmNotifySendImpl
#endif

#ifndef goal_pnioAlarmNotifySendAck
# define goal_pnioAlarmNotifySendAck goal_pnioAlarmNotifySendAckImpl
#endif

#ifndef goal_pnioAlarmProcessSend
# define goal_pnioAlarmProcessSend goal_pnioAlarmProcessSendImpl
#endif

#ifndef goal_pnioAlarmProcessQueueInit
# define goal_pnioAlarmProcessQueueInit goal_pnioAlarmProcessQueueInitImpl
#endif

#ifndef goal_pnioAlarmProcessQueueAdd
# define goal_pnioAlarmProcessQueueAdd goal_pnioAlarmProcessQueueAddImpl
#endif

#ifndef goal_pnioAlarmProcessQueueSend
# define goal_pnioAlarmProcessQueueSend goal_pnioAlarmProcessQueueSendImpl
#endif

#ifndef goal_pnioAlarmProcessQueueReset
# define goal_pnioAlarmProcessQueueReset goal_pnioAlarmProcessQueueResetImpl
#endif

#ifndef goal_pnioRecReadFinish
# define goal_pnioRecReadFinish goal_pnioRecReadFinishImpl
#endif

#ifndef goal_pnioRecWriteFinish
# define goal_pnioRecWriteFinish goal_pnioRecWriteFinishImpl
#endif

#ifndef goal_pnioDiagChanDiagAdd
# define goal_pnioDiagChanDiagAdd goal_pnioDiagChanDiagAddImpl
#endif

#ifndef goal_pnioDiagExtChanDiagAdd
# define goal_pnioDiagExtChanDiagAdd goal_pnioDiagExtChanDiagAddImpl
#endif

#ifndef goal_pnioDiagChanDiagRemove
# define goal_pnioDiagChanDiagRemove goal_pnioDiagChanDiagRemoveImpl
#endif

#ifndef goal_pnioCyclicCtrl
# define goal_pnioCyclicCtrlImpl
#endif

#ifndef goal_pnioVendorIdSet
# define goal_pnioVendorIdSet goal_pnioVendorIdSetImpl
#endif

#ifndef goal_pnioDeviceIdSet
# define goal_pnioDeviceIdSet goal_pnioDeviceIdSetImpl
#endif

#ifndef goal_pnioDeviceNameSet
# define goal_pnioDeviceNameSet goal_pnioDeviceNameSetImpl
#endif

#ifndef goal_pnioHwRevSet
# define goal_pnioHwRevSet goal_pnioHwRevSetImpl
#endif

#ifndef goal_pnioSwRevSet
# define goal_pnioSwRevSet goal_pnioSwRevSetImpl
#endif

#ifndef goal_pnioProfileIdSet
# define goal_pnioProfileIdSet goal_pnioProfileIdSetImpl
#endif

#ifndef goal_pnioOrderIdSet
# define goal_pnioOrderIdSet goal_pnioOrderIdSetImpl
#endif

#ifndef goal_pnioSerialNumSet
# define goal_pnioSerialNumSet goal_pnioSerialNumSetImpl
#endif

#ifndef goal_pnioVendorNameSet
# define goal_pnioVendorNameSet goal_pnioVendorNameSetImpl
#endif

#ifndef goal_pnioPortDescSet
# define goal_pnioPortDescSet goal_pnioPortDescSetImpl
#endif

#ifndef goal_pnioSystemDescSet
# define goal_pnioSystemDescSet goal_pnioSystemDescSetImpl
#endif

#ifndef goal_pnioCfgDcpFactoryResetDisableSet
#  define goal_pnioCfgDcpFactoryResetDisableSet goal_pnioCfgDcpFactoryResetDisableSetImpl
#endif

#ifndef goal_pnioCfgDcpAcceptMixcaseStationSet
#  define goal_pnioCfgDcpAcceptMixcaseStationSet goal_pnioCfgDcpAcceptMixcaseStationSetImpl
#endif

#ifndef goal_pnioCfgVendorIdSet
#  define goal_pnioCfgVendorIdSet goal_pnioCfgVendorIdSetImpl
#endif

#ifndef goal_pnioCfgDeviceIdSet
#  define goal_pnioCfgDeviceIdSet goal_pnioCfgDeviceIdSetImpl
#endif

#ifndef goal_pnioCfgVendorNameSet
#  define goal_pnioCfgVendorNameSet goal_pnioCfgVendorNameSetImpl
#endif

#ifndef goal_pnioCfgPortNameSet
#  define goal_pnioCfgPortNameSet goal_pnioCfgPortNameSetImpl
#endif

#ifndef goal_pnioCfgSystemDescSet
#  define goal_pnioCfgSystemDescSet goal_pnioCfgSystemDescSetImpl
#endif

#ifndef goal_pnioCfgOrderIdSet
#  define goal_pnioCfgOrderIdSet goal_pnioCfgOrderIdSetImpl
#endif

#ifndef goal_pnioCfgSerialNumSet
#  define goal_pnioCfgSerialNumSet goal_pnioCfgSerialNumSetImpl
#endif

#ifndef goal_pnioCfgHwRevSet
#  define goal_pnioCfgHwRevSet goal_pnioCfgHwRevSetImpl
#endif

#ifndef goal_pnioCfgSwRevPrefixSet
#  define goal_pnioCfgSwRevPrefixSet goal_pnioCfgSwRevPrefixSetImpl
#endif

#ifndef goal_pnioCfgSwRevFuncEnhSet
#  define goal_pnioCfgSwRevFuncEnhSet goal_pnioCfgSwRevFuncEnhSetImpl
#endif

#ifndef goal_pnioCfgSwRevBugfixSet
#  define goal_pnioCfgSwRevBugfixSet goal_pnioCfgSwRevBugfixSetImpl
#endif

#ifndef goal_pnioCfgSwRevIntChgSet
#  define goal_pnioCfgSwRevIntChgSet goal_pnioCfgSwRevIntChgSetImpl
#endif

#ifndef goal_pnioCfgSwRevCntSet
#  define goal_pnioCfgSwRevCntSet goal_pnioCfgSwRevCntSetImpl
#endif

#ifndef goal_pnioCfgIm1TagFuncSet
#  define goal_pnioCfgIm1TagFuncSet goal_pnioCfgIm1TagFuncSetImpl
#endif

#ifndef goal_pnioCfgIm1TagLocSet
#  define goal_pnioCfgIm1TagLocSet goal_pnioCfgIm1TagLocSetImpl
#endif

#ifndef goal_pnioCfgIm2DateSet
#  define goal_pnioCfgIm2DateSet goal_pnioCfgIm2DateSetImpl
#endif

#ifndef goal_pnioCfgIm3DescSet
#  define goal_pnioCfgIm3DescSet goal_pnioCfgIm3DescSetImpl
#endif

#ifndef goal_pnioCfgIm4SigSet
#  define goal_pnioCfgIm4SigSet goal_pnioCfgIm4SigSetImpl
#endif

#ifndef goal_pnioCfgDevDapSimpleSet
#  define goal_pnioCfgDevDapSimpleSet goal_pnioCfgDevDapSimpleSetImpl
#endif

#ifndef goal_pnioCfgDevDapApiSet
#  define goal_pnioCfgDevDapApiSet goal_pnioCfgDevDapApiSetImpl
#endif

#ifndef goal_pnioCfgDevDapSlotSet
#  define goal_pnioCfgDevDapSlotSet goal_pnioCfgDevDapSlotSetImpl
#endif

#ifndef goal_pnioCfgDevDapSubslotSet
#  define goal_pnioCfgDevDapSubslotSet goal_pnioCfgDevDapSubslotSetImpl
#endif

#ifndef goal_pnioCfgDevDapModuleSet
#  define goal_pnioCfgDevDapModuleSet goal_pnioCfgDevDapModuleSetImpl
#endif

#ifndef goal_pnioCfgDevDapSubmoduleSet
#  define goal_pnioCfgDevDapSubmoduleSet goal_pnioCfgDevDapSubmoduleSetImpl
#endif

#ifndef goal_pnioCfgNetLinkSafetySet
#  define goal_pnioCfgNetLinkSafetySet goal_pnioCfgNetLinkSafetySetImpl
#endif

#ifndef goal_pnioCfgNewIoDataCbSet
#  define goal_pnioCfgNewIoDataCbSet goal_pnioCfgNewIoDataCbSetImpl
#endif

#ifndef goal_pnioCfgLldpOrgExtSet
#  define goal_pnioCfgLldpOrgExtSet goal_pnioCfgLldpOrgExtSetImpl
#endif

#ifndef goal_pnioCfgLldpOptTlvSet
#  define goal_pnioCfgLldpOptTlvSet goal_pnioCfgLldpOptTlvSetImpl
#endif

#ifndef goal_pnioCfgLldpGenMacSet
#  define goal_pnioCfgLldpGenMacSet goal_pnioCfgLldpGenMacSetImpl
#endif

#ifndef goal_pnioCfgIm14SupportSet
#  define goal_pnioCfgIm14SupportSet goal_pnioCfgIm14SupportSetImpl
#endif

#ifndef goal_pnioCfgIm14CbSet
#  define goal_pnioCfgIm14CbSet goal_pnioCfgIm14CbSetImpl
#endif

#ifndef goal_pnioCfgIm0CbSet
#  define goal_pnioCfgIm0CbSet goal_pnioCfgIm0CbSetImpl
#endif

#ifndef goal_pnioCfgIm0FilterDataCbSet
#  define goal_pnioCfgIm0FilterDataCbSet goal_pnioCfgIm0FilterDataCbSetImpl
#endif

#ifndef goal_pnioCfgRecDataBusyBufsizeSet
#  define goal_pnioCfgRecDataBusyBufsizeSet goal_pnioCfgRecDataBusyBufsizeSetImpl
#endif

#ifndef goal_pnioCfgRpcFragReqLenMaxSet
#  define goal_pnioCfgRpcFragReqLenMaxSet goal_pnioCfgRpcFragReqLenMaxSetImpl
#endif

#ifndef goal_pnioCfgRpcFragMaxCntSet
#  define goal_pnioCfgRpcFragMaxCntSet goal_pnioCfgRpcFragMaxCntSetImpl
#endif

#ifndef goal_pnioCfgRpcFragEnableSet
#  define goal_pnioCfgRpcFragEnableSet goal_pnioCfgRpcFragEnableSetImpl
#endif

#ifndef goal_pnioCfgRpcSessionMaxCntSet
#  define goal_pnioCfgRpcSessionMaxCntSet goal_pnioCfgRpcSessionMaxCntSetImpl
#endif

#ifndef goal_pnioCfgDiagBufMaxCntSet
#  define goal_pnioCfgDiagBufMaxCntSet goal_pnioCfgDiagBufMaxCntSetImpl
#endif

#ifndef goal_pnioCfgDiagBufMaxDataSizeSet
#  define goal_pnioCfgDiagBufMaxDataSizeSet goal_pnioCfgDiagBufMaxDataSizeSetImpl
#endif

#ifndef goal_pnioCfgIocrBlocksMaxSet
#  define goal_pnioCfgIocrBlocksMaxSet goal_pnioCfgIocrBlocksMaxSetImpl
#endif

#ifndef goal_pnioCfgCrMaxCntSet
#  define goal_pnioCfgCrMaxCntSet goal_pnioCfgCrMaxCntSetImpl
#endif

#ifndef goal_pnioCfgArMaxCntSet
#  define goal_pnioCfgArMaxCntSet goal_pnioCfgArMaxCntSetImpl
#endif

#ifndef goal_pnioCfgApiMaxCntSet
#  define goal_pnioCfgApiMaxCntSet goal_pnioCfgApiMaxCntSetImpl
#endif

#ifndef goal_pnioCfgSlotMaxCntSet
#  define goal_pnioCfgSlotMaxCntSet goal_pnioCfgSlotMaxCntSetImpl
#endif

#ifndef goal_pnioCfgSubslotMaxCntSet
#  define goal_pnioCfgSubslotMaxCntSet goal_pnioCfgSubslotMaxCntSetImpl
#endif

#ifndef goal_pnioCfgSubslotIfSet
#  define goal_pnioCfgSubslotIfSet goal_pnioCfgSubslotIfSetImpl
#endif

#ifndef goal_pnioCfgSubslotPortSet
#  define goal_pnioCfgSubslotPortSet goal_pnioCfgSubslotPortSetImpl
#endif

#ifndef goal_pnioCfgSnmpIdSet
#  define goal_pnioCfgSnmpIdSet goal_pnioCfgSnmpIdSetImpl
#endif

#ifndef goal_pnioCfgNumProcAlBufSet
#  define goal_pnioCfgNumProcAlBufSet goal_pnioCfgNumProcAlBufSetImpl
#endif

#ifndef goal_pnioDmSubslotPlug
#  define goal_pnioDmSubslotPlug goal_pnioDmSubslotPlugImpl
#endif

#ifndef goal_pnioDmSubslotAdd
#  define goal_pnioDmSubslotAdd goal_pnioDmSubslotAddImpl
#endif

#ifndef goal_pnioDmSubslotIoxsAdd
#  define goal_pnioDmSubslotIoxsAdd goal_pnioDmSubslotIoxsAddImpl
#endif

#ifndef goal_pnioDmApduAdd
#  define goal_pnioDmApduAdd goal_pnioDmApduAddImpl
#endif

#ifndef goal_pnioDmDpAdd
#  define goal_pnioDmDpAdd goal_pnioDmDpAddImpl
#endif

#ifndef goal_pnioSubslotStateSet
#  define goal_pnioSubslotStateSet goal_pnioSubslotStateSetImpl
#endif

#ifndef goal_pnioConnReqProcess
#  define goal_pnioConnReqProcess goal_pnioConnReqProcessImpl
#endif


/****************************************************************************/
/* Instance Data */
/****************************************************************************/
typedef struct {
    GOAL_PNIO_FUNC_CB_T goal_pnioCb;            /**< PROFINET callback function */
    GOAL_BOOL_T varFlgCyclic;                   /**< cyclic data enable flag */
    GOAL_PNIO_T *pInstGoalPnio;                 /**< GOAL PNIO instance */
} PN_INSTANCE_GOAL_T;


#endif /* PN_GOAL_H */
