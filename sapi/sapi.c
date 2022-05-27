/** @file
 *
 * @brief CCM basic communication layer
 *
 * This module contains basic communication functions for the CCM.
 *
 * @copyright
 * Copyright 2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include "goal_includes.h"
#include "goal_media/goal_mi_mctc.h"
#include "sapi.h"


/****************************************************************************/
/* Local prototypes */
/****************************************************************************/
static GOAL_BOOL_T sapi_pdCheckHeader(
    uint8_t *pData,                             /**< data buffer */
    int count                                   /**< data length */
);

static void sapi_pdUpdateHeader(
    uint8_t *pData,                             /**< data buffer */
    int count                                   /**< data length */
);


/****************************************************************************/
/* Local types */
/****************************************************************************/
typedef enum {
    STATE_UNKNOWN,
    STATE_OFFLINE,
    STATE_ONLINE
} SAPI_STATE_T;


/****************************************************************************/
/* Local variables */
/****************************************************************************/
uint8_t sendData[BUF_LENGTH];                   /**< send data buffer */
uint8_t receiveData[BUF_LENGTH];                /**< receive data buffer */
static uint8_t cntSeqCyclic;                    /**< counter */
static GOAL_TIMESTAMP_T tsTout;                 /**< timestamp timout */
static SAPI_STATE_T sapiState;                  /**< sapi state */
static uint8_t receivingBuffer[BUF_LENGTH];     /**< temporary buffer to keep receiveData consistent */


/****************************************************************************/
/** Fletcher checksum calculation
 *
 */
uint16_t sapi_utilCrcFletcher16(
    uint8_t const *pData,                       /**< data pointer */
    int count                                   /**< size in 8-bit bytes */
)
{
    uint16_t sum1 = 0;                          /* first sum */
    uint16_t sum2 = 0;                          /* second sum */
    int index;                                  /* iteration variable */

    for (index = 0; index < count; index++) {
        sum1 = (sum1 + pData[index]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }

    return (uint16_t) ((sum2 << 8) | sum1) + IRJ45_CRC_OFFSET;
}


/****************************************************************************/
/** Cyclic header check
 *
 * This function checks for a valid cyclic data header.
 *
 * @retval true successful
 * @retval other failed
 */
static GOAL_BOOL_T sapi_pdCheckHeader(
    uint8_t *pData,                             /**< data buffer */
    int count                                   /**< data length */
)
{
    uint16_t crc;                               /* crc */
    GOAL_BOOL_T res = false;                    /* result */
    uint16_t crcHeader;

    crcHeader = U16_LETOH(pData);

    crc = sapi_utilCrcFletcher16(&pData[IRJ45_PD_HEADER], count);
    if (crcHeader == crc) {
        res = true;
    } else {
        res = false;
    }
    return res;
}


/****************************************************************************/
/** Cyclic header update
 *
 * This function generates a valid cyclic data header.
 *
 */
static void sapi_pdUpdateHeader(
    uint8_t *pData,                             /**< data buffer */
    int count                                   /**< data length */
)
{
    uint16_t crc;                               /* crc */

    /* update crc */
    crc = sapi_utilCrcFletcher16(&pData[IRJ45_PD_HEADER], count);

    /* update frame header */
    U16_HTOLE_P(&pData[0], crc);

    /* update sequence number */
    pData[2] = cntSeqCyclic;

    cntSeqCyclic++;

    /* update length */
    pData[3] = count;
}


/****************************************************************************/
/** Calculates the LED states to be send via i2c
 *
 *
 */
void irj45_setLedState(
    uint32_t *pLedStates,                       /**< pointer where lead states are stored */
    uint32_t led,                               /**< the LED to set */
    GOAL_BOOL_T state                           /**< the new state of the LED */
)
{
    *(pLedStates) &= ~(3UL << led);
    if (state) {
        *(pLedStates) |= (1UL << led);
    }
}


/****************************************************************************/
/** Returns the current state of an LED
 *
 *
 */
GOAL_BOOL_T irj45_getLedState(
    uint32_t *pLedStates,                       /**< pointer to LED states */
    uint32_t led                                /**< LED to retrieve state for */
)
{
    return ! (*(pLedStates) & (3UL << led));
}


/****************************************************************************/
/** Default sapi data handler callback, which does nothing.
 *
 * This function can be overloaded by the application to get access to the cyclic data channel.
 *
 * TODO:
 *  - remove transmitData from signature
 *  - provide access to cyclic channel only, thus skipping cyclic header
 *
 */
void GOAL_TARGET_WEAK som_dataCb(
    uint8_t *dataReceive,
    uint8_t *dataTransmit
)
{
#if CONFIG_UGOAL_DATAMAPPER == 0
    uint32_t ledStates;
    GOAL_MI_MCTC_DP_T dp;

    /* update led states */
    memcpy(&dp, &receiveData[APPL_DPO_POS], sizeof(dp));
    irj45_setLedState(&ledStates, GOAL_MA_LED_ETHERCAT, true);
    irj45_setLedState(&ledStates, GOAL_MA_LED_PROFINET, false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_MODBUS , false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_ETHERNETIP , false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_CANOPEN, false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_LED1_GREEN, (dp.leds & GOAL_MCTC_DP_LED_GREEN_1) ? true : false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_LED1_RED, (dp.leds & GOAL_MCTC_DP_LED_RED_1) ? true : false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_LED2_GREEN, (dp.leds & GOAL_MCTC_DP_LED_GREEN_2) ? true : false);
    irj45_setLedState(&ledStates, GOAL_MA_LED_LED2_RED, (dp.leds & GOAL_MCTC_DP_LED_RED_2) ? true : false);
    /* update target LEDs */

    plat_ledSet(ledStates);
#endif
    UNUSEDARG(dataReceive);
    UNUSEDARG(dataTransmit);
}


/****************************************************************************/
/** Basic cyclic communication function
 *
 * This function initiates SPI transfer and dispatches received data to
 * the upper layers data callback and RPC handling.
 *
 */
void sapi_loop(
        void
)
{
    GOAL_TIMESTAMP_T tsNow;                     /* timestamp */

    tsNow = goal_timerTsGet();

    /* update frame header */
    sapi_pdUpdateHeader(sendData, GOAL_MI_MCTC_LEN - sizeof(GOAL_MI_MCTC_SPI_CYCLIC_T));

    /* transfer data via SPI */
    plat_spiTransfer((const char *) &sendData[0], (char *) receivingBuffer, BUF_LENGTH);

    /* control LED if Connection valid or Wink active */
    if (true == sapi_pdCheckHeader(receivingBuffer, GOAL_MI_MCTC_LEN - sizeof(GOAL_MI_MCTC_SPI_CYCLIC_T))) {

        /* if received buffer is ok, swap data */
        memcpy(receiveData, receivingBuffer, BUF_LENGTH);

        /* inform application */
        som_dataCb(&receiveData[0], &sendData[0]);

        /* trigger RPC */
        goal_miMctcDmCbRead();

        /* rearm watchdog - if timeout is disabled, trigger watchdog
         * after a millisecond but without executing registered
         * callbacks.
         */
        tsTout = CONFIG_UGOAL_TIMEOUT_MEDIA ? tsNow + CONFIG_UGOAL_TIMEOUT_MEDIA : tsNow + GOAL_TIMER_SEC;
    }

    /* evaluate watchdog */
    if ((tsTout <= tsNow) && (STATE_ONLINE == sapiState)) {
        /* data channel offline */
        sapiState = STATE_OFFLINE;
        goal_logInfo("data channel offline");

        if (CONFIG_UGOAL_TIMEOUT_MEDIA != 0) {
            goal_miMctcTimeoutCb();
        }
    }

    if ((tsTout > tsNow) && (STATE_OFFLINE == sapiState)) {
        /* data channel online */
        sapiState = STATE_ONLINE;
        goal_logInfo("data channel online");

        if (CONFIG_UGOAL_TIMEOUT_MEDIA != 0) {
            goal_miMctcOnlineCb();
        }
    }

    if ((tsTout > tsNow) && (STATE_UNKNOWN == sapiState)) {
        /* data channel online */
        sapiState = STATE_ONLINE;
        tsTout = tsNow + CONFIG_UGOAL_TIMEOUT_MEDIA;
    }
}
