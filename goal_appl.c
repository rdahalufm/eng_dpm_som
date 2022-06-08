/** @file
 *
 * @brief
 * PROFINET Simple I/O Example using process data using RPC
 *
 * @details
 * This example provides a possible test environment for a simplified
 * conformance test.
 *
 * @copyright
 * Copyright 2010-2021 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include <goal_includes.h>
#include <goal_pnio.h>
#include <ccm_rpc_ac.h>
#include "goal_appl.h"
#include "ctc_net_ac.h"
#include "ctc_net_rpc.h"
#include "goal_http.h"
#include <goal_dd.h>

/****************************************************************************/
/* Local Defines */
/****************************************************************************/
#define APPL_PNIO_ID        0                   /**< PROFINET instance id */
#define APPL_SNMP_ID        0 
#define APPL_TIMEOUT_TRIGGER_VAL 10 * GOAL_TIMER_MSEC /**< timeout trigger in ms */
#define APPL_MOD_SIZE       1                 /**< module sizes */

#define APPL_API            0                   /**< API 0 */

#define APPL_SLOT_1         1                   /**< slot 1 */
#define APPL_SLOT_1_SUB_1   1                   /**< submodule for slot 1 */
#define APPL_SLOT_2         2                   /**< slot 2 */
#define APPL_SLOT_2_SUB_1   1                   /**< submodule for slot 2 */
#define APPL_SLOT_3         3                   /**< slot 1 */
#define APPL_SLOT_3_SUB_1   1                   /**< submodule for slot 3 */
#define APPL_SLOT_4         4                   /**< slot 2 */
#define APPL_SLOT_4_SUB_1   1                   /**< submodule for slot 4 */
#define APPL_SLOT_5         5                   /**< slot 1 */
#define APPL_SLOT_5_SUB_1   1                   /**< submodule for slot 5 */




#define APPL_MOD_1          0x02                /**< module 1 */
#define APPL_MOD_1_SUB_1    0x01                /**< submodule for module 1 */
#define APPL_MOD_2          0x20                /**< module 2 */
#define APPL_MOD_2_SUB_1    0x01                /**< submodule for module 2 */


#define MAIN_APPL_IP            GOAL_NET_IPV4(192, 168, 1, 45)
#define MAIN_APPL_NM            GOAL_NET_IPV4(255, 255, 255, 0)
#define MAIN_APPL_GW            GOAL_NET_IPV4(192, 168, 1, 1)

#define APPL_SLOT_COUNT     6                  /**< maximum number of slots */
#define APPL_SUBSLOT_COUNT  6                  /**< maximum number of subslots */

/****************************************************************************/
/* Local Prototypes */
/****************************************************************************/
static GOAL_STATUS_T appl_pnioCb(
    GOAL_PNIO_T *pHdlPnio,                      /**< PROFINET instance */
    GOAL_PNIO_CB_ID_T id,                       /**< callback id */
    GOAL_PNIO_CB_DATA_T *pCb                    /**< callback parameters */
);

#if 0
static GOAL_STATUS_T appl_dmCbCyclicRx(
    GOAL_MI_DM_GROUP_T *pGroup,                 /**< [in] MI DM group handle */
    void *pPriv                                 /**< [in] private pointer */
);
#endif


/****************************************************************************/
/* Local Variables */
/****************************************************************************/
static GOAL_BOOL_T flgAppReady = GOAL_FALSE;    /**< app ready flag */
static GOAL_PNIO_AR_ID_T idAr = 0;              /**< AR ID */
static char dataRpcIn[APPL_MOD_SIZE];             /**< buffer for module data */
static char dataRpcOut[APPL_MOD_SIZE];
static GOAL_TIMESTAMP_T tsTout;                 /**< timeout timestamp */
static GOAL_PNIO_T *pPnio;                      /**< PROFINET instance */
GOAL_BOOL_T connected = GOAL_FALSE;             /* state of PNIO connection */
static GOAL_MA_LED_T *pMaLed;                   /**< led MA handle */
static GOAL_MI_MCTC_DP_T genericDp;             /**< generic data provider */


GOAL_MA_NET_T *pMaNet;
uint32_t ip = 0;                                /* IP address */
uint32_t nm = 0;                                /* netmask */
uint32_t gw = 0;     

/****************************************************************************/
/** Application Init
 *
 * Build up the device structure and initialize the Profinet stack.
 */
GOAL_STATUS_T appl_init(
    void
)
{
    GOAL_STATUS_T res;                          /* result */

    /* initialize DD */
    res = goal_ddInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Initialization of DD failed");
    }
    
    res = goal_snmpInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Initialization of SNMP failed");
    }
    
    /* initialize PROFINET */
    res = goal_pnioInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Initialization of PROFINET failed");
    } else {
        goal_logInfo("PNET Initialized");
    }
    
    /* initialize ccm RPC interface */
    res = appl_ccmRpcInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Initialization of ccm RPC failed");
    }
    return res;
}


#if CONFIG_UGOAL_DATAMAPPER == 0
/****************************************************************************/
/** Callback function called if new data arrived
 *
 */
void som_dataCb(
    uint8_t *pReceiveData,
    uint8_t *pSendData
)
{
    GOAL_BOOL_T winkState = GOAL_FALSE;

    UNUSEDARG(pSendData);

    /* Connection State */
    if (pReceiveData[APPL_DPO_POS] & 0x01) {
        if (!connected) {
            connected = GOAL_TRUE;
            goal_logInfo("Connection established");
        }
    } else {
        if (connected) {
            connected = GOAL_FALSE;
            goal_logInfo("Connection closed");
        }
    }

    /* Wink */
    winkState = ((pReceiveData[APPL_DPO_POS + 1] & 0x01) ^ (pReceiveData[APPL_DPO_POS] & 0x01)) ? GOAL_TRUE : GOAL_FALSE;
    UNUSEDARG(winkState);

    GOAL_MEMCPY(&genericDp, &pReceiveData[APPL_DPO_POS], sizeof(genericDp));

    if (genericDp.leds & GOAL_MCTC_DP_LED_RED_1) {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED1_RED, GOAL_MA_LED_STATE_ON);
    }
    else {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED1_RED, GOAL_MA_LED_STATE_OFF);
    }

    if (genericDp.leds & GOAL_MCTC_DP_LED_RED_2) {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED2_RED, GOAL_MA_LED_STATE_ON);
    }
    else {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED2_RED, GOAL_MA_LED_STATE_OFF);
    }

    if (genericDp.leds & GOAL_MCTC_DP_LED_GREEN_1) {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED1_GREEN, GOAL_MA_LED_STATE_ON);
    }
    else {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED1_GREEN, GOAL_MA_LED_STATE_OFF);
    }

    if (genericDp.leds & GOAL_MCTC_DP_LED_GREEN_2) {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED2_GREEN, GOAL_MA_LED_STATE_ON);
    }
    else {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED2_GREEN, GOAL_MA_LED_STATE_OFF);
    }
}
#endif

/****************************************************************************/
/** Plug module from ExpectedSubmoduleEntry
 */
static void main_modulePlug(
    GOAL_PNIO_CB_DATA_T *pCb                    /**< callback parameters */
)
{
    GOAL_STATUS_T res;
    /* plug module & submodule (RPC) */
    res = goal_pnioRpcSubmodPlug(pPnio, pCb->data[1].u32, pCb->data[2].u16, pCb->data[3].u16, pCb->data[4].u32, pCb->data[5].u32);

    if (GOAL_RES_ERR(res)) {
        goal_logErr("error while plugging module (0x%08" FMT_x32 ", 0x%08" FMT_x32 ") into slot (%" FMT_u32 ", %u, %u)",
                    pCb->data[4].u32, pCb->data[5].u32, pCb->data[1].u32, pCb->data[2].u16, pCb->data[3].u16);
        return;
    }

    goal_logInfo("plugged module (0x%08" FMT_x32 ", 0x%08" FMT_x32 ") into slot (%" FMT_u32 ", %u, %u)",
                 pCb->data[4].u32, pCb->data[5].u32, pCb->data[1].u32, pCb->data[2].u16, pCb->data[3].u16);
}

/****************************************************************************/
/** Pull all modules
 *
 * Remove all modules from their slots.
 */
static void main_modulePull(
    void
)
{
    GOAL_STATUS_T res;                          /* result */
    uint16_t cnt;                               /* counter */

    /* slot 0 contains DAP and interfaces, don't pull these */
    for (cnt = APPL_SLOT_1; cnt <= APPL_SLOT_5; cnt++) {
        res = goal_pnioModPull(pPnio, APPL_API, cnt);
        if (GOAL_RES_ERR(res)) {
            goal_logErr("error while pulling module: %u", cnt);
        }
    }
}

/****************************************************************************/
/** Profinet Callback Handler
 *
 * This function collects all callbacks from the stack and decides if the
 * callback must be handled.
 */
static GOAL_STATUS_T appl_pnioCb(
    GOAL_PNIO_T *pHdlPnio,                      /**< PROFINET instance */
    GOAL_PNIO_CB_ID_T id,                       /**< callback id */
    GOAL_PNIO_CB_DATA_T *pCb                    /**< callback parameters */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* return value */

    UNUSEDARG(pHdlPnio);

    /* handle callback IDs */
    switch (id) {

        case GOAL_PNIO_CB_ID_APPL_READY:
            /* application ready was confirmed, start data handling if not
             * already running */
            if (GOAL_TRUE != flgAppReady) {
                flgAppReady = GOAL_TRUE;
                idAr = pCb->data[0].idAr;
            }
            break;

        case GOAL_PNIO_CB_ID_RELEASE_AR:
            /* AR was released, stop data handling if it was the first AR */
            if (idAr == pCb->data[0].idAr) {
                flgAppReady = GOAL_FALSE;
                idAr = 0;
            }
            break;

        case GOAL_PNIO_CB_ID_BLINK:
            /*
             * NOTE:
             *  The function goal_targetSetLeds does nothing on this platform, can be omitted here.
             *  Although the callback id GOAL_PNIO_CB_ID_BLINK is called by the stack, for CTC applications
             *  LEDs should be evaluated from the generic data provider states.
             */
            break;
            /* Putting this causes issues with the input bytes in profinet cyclic */
//        case GOAL_PNIO_CB_ID_CONNECT_REQUEST_EXP_START:
//            /* start of ExpectedSubmoduleBlock received, remove all modules */
//            main_modulePull();
//            break;    
        case GOAL_PNIO_CB_ID_EXP_SUBMOD:
            /* module config request received */
            main_modulePlug(pCb);
            break;
        default:
            break;
    }

    return res;
}


/****************************************************************************/
/** Application Setup
 *
 * Setup the application.
 */
GOAL_STATUS_T appl_setup(
    void
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_INSTANCE_SNMP_T *pInstanceSnmp = NULL; /* GOAL_SNMP handle */
    int i = 0;

    /* initialize timeout timestamp */
    tsTout = goal_timerTsGet() + APPL_TIMEOUT_TRIGGER_VAL;

        /* initialize ugoal net */
    res = goal_netRpcInit(GOAL_NET_ID_DEFAULT);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set vendor id");   
    }
    
    res = goal_maNetOpen(GOAL_NET_ID_DEFAULT, &pMaNet);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("error opening network MA");
    }

    /* set IP address */
    ip = GOAL_NET_IPV4(IPAddressLocal[0], IPAddressLocal[1], IPAddressLocal[2], IPAddressLocal[3]);
    nm = GOAL_NET_IPV4(SMaskLocal[0], SMaskLocal[1], SMaskLocal[2], SMaskLocal[3]);
//    gw = GOAL_NET_IPV4(IPAddressLocal[0], IPAddressLocal[1], IPAddressLocal[2], 1);
    
    res = goal_maNetIpSet(pMaNet, ip, nm, gw, GOAL_FALSE);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Set IP failed");
        return res;
    }

    /* configure stack to feature the GOAL_PNIO_CB_ID_NEW_IO_DATA callback */
    goal_pnioCfgNewIoDataCbSet(GOAL_TRUE);

    res = goal_snmpNew(&pInstanceSnmp, APPL_SNMP_ID);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create SNMP instance");
        return res;
    }

    /* set SNMP instance id for new PNIO instance */
    res = goal_pnioCfgSnmpIdSet(APPL_SNMP_ID);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set SNMP instance id");
        return res;
    }

    /* Slot Maximum Count */
    res = goal_pnioCfgSlotMaxCntSet(APPL_SLOT_COUNT);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    /* Subslot Maximum Count */
    res = goal_pnioCfgSubslotMaxCntSet(APPL_SUBSLOT_COUNT);
    if (GOAL_RES_ERR(res)) {
        return res;
    }
    
    
    /* set identification of the slave (vendor id) */
    res = goal_pnioCfgVendorIdSet(APPL_PNIO_VENDOR_ID);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set vendor id");
        return res;
    }

    /* set identification of the slave (device id) */
    res = goal_pnioCfgDeviceIdSet(APPL_PNIO_DEVICE_ID);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set device id");
        return res;
    }

    /* set identification of the slave (vendor name) */
    res = goal_pnioCfgVendorNameSet(APPL_PNIO_VENDOR_NAME);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to set vendor name");
        return res;
    }

    res = goal_pnioCfgNumProcAlBufSetAc(10);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to configure AlBuf");
        return res;
    }
    
    /* create new PROFINET instance */
    res = goal_pnioNew(&pPnio, APPL_PNIO_ID, appl_pnioCb);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create a new PROFINET instance");
        return res;
    }

    goal_logInfo("Initializing device structure");

    /* create subslots */
    res = goal_pnioSubslotNew(pPnio, APPL_API, APPL_SLOT_1, APPL_SLOT_1_SUB_1, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add subslot");
        return res;
    }

    res = goal_pnioSubslotNew(pPnio, APPL_API, APPL_SLOT_2, APPL_SLOT_2_SUB_1, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add subslot");
        return res;
    }
    
    res = goal_pnioSubslotNew(pPnio, APPL_API, APPL_SLOT_3, APPL_SLOT_3_SUB_1, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add subslot");
        return res;
    }

    res = goal_pnioSubslotNew(pPnio, APPL_API, APPL_SLOT_4, APPL_SLOT_4_SUB_1, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add subslot");
        return res;
    }
    
    
    res = goal_pnioSubslotNew(pPnio, APPL_API, APPL_SLOT_5, APPL_SLOT_5_SUB_1, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add subslot");
        return res;
    }
    
    
    
    /* create submodules */
    res = goal_pnioSubmodNew(pPnio, APPL_MOD_1, APPL_MOD_1_SUB_1, GOAL_PNIO_MOD_TYPE_INPUT, APPL_MOD_SIZE, 0, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add submodule");
        return res;
    }

    res = goal_pnioSubmodNew(pPnio, APPL_MOD_2, APPL_MOD_2_SUB_1, GOAL_PNIO_MOD_TYPE_OUTPUT, 0, APPL_MOD_SIZE, GOAL_PNIO_FLG_AUTO_GEN);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to add submodule");
        return res;
    }
    
    

    //--------------------------------------------------------------------------------------------

    /* PROFINET: add generic dp to cyclic RX data
     *
     * NOTE: Mapping of led and status data to the cyclic channel is required.
     *       Calling this function before any other cyclic channel relevant functions
     *       (goal_pnioDmSubmodPlug e.g.) ensures, that the data provider is mapped
     *       to offset 0.
     */
    if (GOAL_RES_OK(res)) {
        res = goal_pnioDmDpAdd(
              pPnio,
              GOAL_MI_MCTC_DIR_PEER_FROM,      /* MI DM 'from peer' handle */
              NULL
           );
    }

    /* plug modules into slots */
    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_1, APPL_SLOT_1_SUB_1, APPL_MOD_1, APPL_MOD_1_SUB_1);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to plug submodule");
        return res;
    }

    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_2, APPL_SLOT_2_SUB_1, APPL_MOD_1, APPL_MOD_1_SUB_1);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to plug submodule");
        return res;
    }

    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_3, APPL_SLOT_3_SUB_1, APPL_MOD_1, APPL_MOD_1_SUB_1);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to plug submodule");
        return res;
    }
    
    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_4, APPL_SLOT_4_SUB_1, APPL_MOD_1, APPL_MOD_1_SUB_1);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to plug submodule");
        return res;
    }
    
    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_5, APPL_SLOT_5_SUB_1, APPL_MOD_2, APPL_MOD_2_SUB_1);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to plug submodule");
        return res;
    }

    /* PROFINET configuration succesful */
    goal_logInfo("PROFINET ready");

    res = goal_maLedGetById(&pMaLed, GOAL_ID_MA_LED_DEFAULT);
    if (GOAL_RES_OK(res)) {
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED1_GREEN, GOAL_MA_LED_STATE_OFF);
        goal_maLedSet(pMaLed, GOAL_MA_LED_LED2_RED, GOAL_MA_LED_STATE_OFF);

        goal_maLedSet(pMaLed, GOAL_MA_LED_CANOPEN, GOAL_MA_LED_STATE_OFF);
        goal_maLedSet(pMaLed, GOAL_MA_LED_ETHERCAT, GOAL_MA_LED_STATE_OFF);
        goal_maLedSet(pMaLed, GOAL_MA_LED_PROFINET, GOAL_MA_LED_STATE_ON);
        goal_maLedSet(pMaLed, GOAL_MA_LED_ETHERNETIP, GOAL_MA_LED_STATE_OFF);
        goal_maLedSet(pMaLed, GOAL_MA_LED_MODBUS, GOAL_MA_LED_STATE_OFF);
    }

    
    return GOAL_OK;
}


/****************************************************************************/
/** Application Loop
 *
 * This function must implement the application logic and must not block. It is
 * called in a loop (the GOAL loop) and if state tracking is necessary it
 * should use static or global variables.
 */
void appl_loop(
    void
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_TIMESTAMP_T tsCur;                     /* current timestamp */
    GOAL_PNIO_IOXS_T iops;                      /* io state */

    /* get current timestamp */
    tsCur = goal_timerTsGet();

    /* Write the value in the module */
    if ((GOAL_TRUE == flgAppReady) && (tsTout <= tsCur)) {

//        /* read data from output module */
//        res = goal_pnioDataOutputGet(pPnio, APPL_API, APPL_SLOT_5, APPL_SLOT_5_SUB_1, dataRpcOut, APPL_MOD_SIZE, &iops);
//        if (GOAL_RES_ERR(res)) {
//            return;
//        }
//
//        /* copy data to input module */
//        res = goal_pnioDataInputSet(pPnio, APPL_API, APPL_SLOT_1, APPL_SLOT_1_SUB_1, dataRpcOut, APPL_MOD_SIZE, GOAL_PNIO_IOXS_GOOD);
//        if (GOAL_RES_ERR(res)) {
//            return;
//        }

        /* update timeout value */
        tsTout = tsCur + APPL_TIMEOUT_TRIGGER_VAL;
    }
}


void goal_app_reset_ip() {
        /* set IP address */
    ip = GOAL_NET_IPV4(IPAddressLocal[0], IPAddressLocal[1], IPAddressLocal[2], IPAddressLocal[3]);
    nm = GOAL_NET_IPV4(SMaskLocal[0], SMaskLocal[1], SMaskLocal[2], SMaskLocal[3]);
    goal_maNetIpSet(pMaNet, ip, nm, gw, GOAL_FALSE);
}

void goal_app_set_inputs(unsigned char *data, unsigned char len) {
    uint8_t i = 0; 
    uint8_t write_len = len > APPL_MOD_SIZE ? APPL_MOD_SIZE : len;
    
    for (i = 0; i < write_len; i++) {
        dataRpcIn[i] = data[i];
    }
}

void goal_app_get_outputs(unsigned char *data, unsigned char len) {
    uint8_t i = 0; 
    uint8_t write_len = len > APPL_MOD_SIZE ? APPL_MOD_SIZE : len;
    
    for (i = 0; i < write_len; i++) {
        data[i] = dataRpcOut[i];
    }
}