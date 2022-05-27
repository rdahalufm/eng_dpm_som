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

/****************************************************************************/
/* Local Defines */
/****************************************************************************/
#define APPL_PNIO_ID        0                   /**< PROFINET instance id */

#define APPL_TIMEOUT_TRIGGER_VAL 100 * GOAL_TIMER_MSEC /**< timeout trigger in ms */
#define APPL_MOD_SIZE       128                 /**< module sizes */

#define APPL_API            0                   /**< API 0 */

#define APPL_SLOT_1         1                   /**< slot 1 */
#define APPL_SLOT_1_SUB_1   1                   /**< submodule for slot 1 */
#define APPL_SLOT_2         2                   /**< slot 2 */
#define APPL_SLOT_2_SUB_1   1                   /**< submodule for slot 2 */

#define APPL_MOD_1          0x30                /**< module 1 */
#define APPL_MOD_1_SUB_1    0x01                /**< submodule for module 1 */
#define APPL_MOD_2          0x31                /**< module 2 */
#define APPL_MOD_2_SUB_1    0x01                /**< submodule for module 2 */


#define MAIN_APPL_IP            GOAL_NET_IPV4(192, 168, 1, 45)
#define MAIN_APPL_NM            GOAL_NET_IPV4(255, 255, 255, 0)
#define MAIN_APPL_GW            GOAL_NET_IPV4(192, 168, 1, 1)

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
static char dataRpc[APPL_MOD_SIZE];             /**< buffer for module data */
static GOAL_TIMESTAMP_T tsTout;                 /**< timeout timestamp */
static GOAL_PNIO_T *pPnio;                      /**< PROFINET instance */
GOAL_BOOL_T connected = GOAL_FALSE;             /* state of PNIO connection */
static GOAL_MA_LED_T *pMaLed;                   /**< led MA handle */
static GOAL_MI_MCTC_DP_T genericDp;             /**< generic data provider */

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

    /* initialize PROFINET */
    res = goal_pnioInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Initialization of PROFINET failed");
    } else {
        goal_logInfo("PNET Initialized");
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
    GOAL_MA_NET_T *pMaNet;
    uint32_t ip;                                /* IP address */
    uint32_t nm;                                /* netmask */
    uint32_t gw;     
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
    ip = MAIN_APPL_IP;
    nm = MAIN_APPL_NM;
    gw = MAIN_APPL_GW;
    res = goal_maNetIpSet(pMaNet, ip, nm, gw, GOAL_FALSE);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("Set IP failed");
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


    //-------------------- Making the slots complaint with what we had with HMS, which is 64 slots

    

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

    res = goal_pnioRpcSubmodPlug(pPnio, APPL_API, APPL_SLOT_2, APPL_SLOT_2_SUB_1, APPL_MOD_2, APPL_MOD_2_SUB_1);
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

        /* read data from output module */
        res = goal_pnioDataOutputGet(pPnio, APPL_API, APPL_SLOT_2, APPL_SLOT_2_SUB_1, dataRpc, APPL_MOD_SIZE, &iops);
        if (GOAL_RES_ERR(res)) {
            return;
        }

        /* copy data to input module */
        res = goal_pnioDataInputSet(pPnio, APPL_API, APPL_SLOT_1, APPL_SLOT_1_SUB_1, dataRpc, APPL_MOD_SIZE, GOAL_PNIO_IOXS_GOOD);
        if (GOAL_RES_ERR(res)) {
            return;
        }

        /* update timeout value */
        tsTout = tsCur + APPL_TIMEOUT_TRIGGER_VAL;
    }
}
