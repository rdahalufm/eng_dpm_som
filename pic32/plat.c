/** @file
 *
 * 
 *
 * 
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include "ugoal/goal_includes.h"
#include <stdbool.h>
#include "rpc/goal_media/goal_mi_mctc.h"
#include <plib.h>
#include "plat.h"
#include "dpm_bsp.h"
/****************************************************************************/
/* Local Variables */
/****************************************************************************/
static volatile GOAL_TIMESTAMP_T milliseconds = 0;  /**< milli second counter */


/****************************************************************************/
/* Local Prototypes */
/****************************************************************************/
static void timer_init(
    void
);

static void spi_init(
    void
);

static uint8_t spi_txrx_char(
    char cData                                  /**< character to transmit */
);

static void uart_init(
    void
);

static int uart_tx_char(
    char character,                             /**< character to transmit */
    FILE *stream                                /**< stream for transmission */
);

static void i2c_init(
    void
);

static int freeRam (
    void
);

static GOAL_STATUS_T plat_reset(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
);

static GOAL_STATUS_T plat_resetPeer(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
);


/****************************************************************************/
/** platform reset function
 *
 * this function performs a reset
 *
 */
static GOAL_STATUS_T plat_reset(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
)
{
                        /* timeout */

    UNUSEDARG(pMiMctc);
    while(1);

    return GOAL_OK;
}


/****************************************************************************/
/** platform peer reset function
 *
 * this function performs a reset of the peer
 *
 */
static GOAL_STATUS_T plat_resetPeer(
    struct GOAL_MI_MCTC_INST_T *pMiMctc         /**< MI MCTC instance */
)
{
    GOAL_TIMESTAMP_T tsTout;                    /* timeout */

    UNUSEDARG(pMiMctc);

    /* reset irj45 */
    LATFbits.LATF3 = 0;
    tsTout = plat_getMsTimer() + 100;
    while (plat_getMsTimer() < tsTout) ;
    LATFbits.LATF3 = 1;
    return GOAL_OK;
}


/****************************************************************************/
/** TIMER initialization
 *
 * This function sets up the hardware for TIMER functions
 */
static void timer_init(
    void
)
{

}


/****************************************************************************/
/** ISR for timer
 *
 * This ISR is required for the milli second counter
 *
 */



/****************************************************************************/
/** SPI initialization
 *
 * This function sets up the hardware for SPI transmissions
 */
static void spi_init(
    void
) {
    
    SPI2CONbits.ON = 0;  //disable SPI to reset
    SPI2CONbits.MODE16 = 0; 
    SPI2CONbits.MODE32=0;//8bit mode
    // Serial output when going from idle to active
    SPI2CONbits.CKP = 0; 
    // IDLE state low
    SPI2CONbits.CKE = 0; 
    SPI2CONbits.MSTEN = 1;//set SPI Master
    IEC1bits.SPI2EIE =0; IEC1bits.SPI2RXIE =0; IEC1bits.SPI2TXIE = 0;//disable SPI interrupts
    SPI2BRG = 30; //set Baud rate to 0.5MHz 
    SPI2BUF = 0;//clear SPI buffer
    SPI2CONbits.ON = 1; //enable SPI
}


/****************************************************************************/
/** SPI initialization
 *
 * This function transmits a single character over SPI
 *
 * @retval character received
 */
static uint8_t spi_txrx_char(
    char cData                                  /**< character to transmit */
) {
    if (SPI2STATbits.SPIROV)  SPI2STATbits.SPIROV = 0;
    while(!SPI2STATbits.SPITBE);
    SPI2BUF = cData;                        // write to buffer for TX
    while(!SPI2STATbits.SPIRBF);       // wait transfer complete
    return SPI2BUF; 
}


/****************************************************************************/
/** UART initialization
 *
 * This function sets up the hardware for UART transmissions
 */
static void uart_init(
    void
) {

}


/****************************************************************************/
/** UART transmission function
 *
 * This function transmits a single character over UART
 *
 * @retval character received
 */
static int uart_tx_char(
    char character,                             /**< character to transmit */
    FILE *stream                                /**< stream for transmission */
)
{
    
    
    return 0;
}


/****************************************************************************/
/** I2C initialization
 *
 * This function sets up the hardware for I2C transmissions
 */
static void i2c_init(
    void
) {
    
}


/****************************************************************************/
/** platform sleep function
 *
 * This function sleeps the given number of milliseconds
 *
 */
void plat_msSleep(
    GOAL_TIMESTAMP_T ms                         /**< milliseconds to sleep */
)
{
    GOAL_TIMESTAMP_T tsTout;                    /* timout value */

    tsTout = plat_getMsTimer() + ms;
    while (plat_getMsTimer() < tsTout) {
        ;
    }
}


/****************************************************************************/
/** get HEAP size
 *
 * This function initilizes the hardware before usage
 *
 */
static int freeRam (
    void
)
{
    return 0;
}


/****************************************************************************/
/** platform init function
 *
 * This function initilizes the hardware before usage
 *
 */
void plat_init(
    void
)
{
    // Chip select
    TRISBbits.TRISB5 = 0; // Output
    // Reset
    TRISFbits.TRISF3 = 0; // Output
    // MOSI
    TRISGbits.TRISG8 = 0; // Output
    //MISO
    TRISGbits.TRISG7 = 1;// Input
    // Clock out
    TRISGbits.TRISG6 = 0;// Output
    
    // Reset High
    LATFbits.LATF3 = 1;
    
//    spi_init();
    goal_miMctcCbRegReset(plat_reset);
    goal_miMctcCbRegRemoteReset(plat_resetPeer);
}


/****************************************************************************/
/** platform SPI transmission function
 *
 * This function handles SPI transmission of the SPI frame
 *
 */
int plat_spiTransfer(
    const char *txBuf,                          /**< [in] transmission buffer */
    char *rxBuf,                                /**< [out] receive buffer */
    int size                                    /**< size of valid buffer sizes */
)
{
    uint8_t cntLen;                             /* length counter */
    uint8_t buff[0x80];
    
    LATBbits.LATB5 = 0;
    for (cntLen = 0; cntLen < (uint8_t) size; cntLen++) {
        rxBuf[cntLen] = spi_txrx_char(txBuf[cntLen]);
        if (cntLen < 0x80) {
            buff[cntLen] = rxBuf[cntLen];
        }
    }
    LATBbits.LATB5 = 1;
    return 0;
}


/****************************************************************************/
/** platform LED set function
 *
 * This function handles the LED data
 *
 */
int plat_ledSet(
    uint32_t state                              /**< led state field */
)
{
    uint8_t ledState[4];                        /* transfer buffer */

    /* set new value for LED states */
    ledState[0] = 0x16;                         /* register offset */
    ledState[1] = (state >> 0) & 0xFF;
    ledState[2] = (state >> 8) & 0xFF;
    ledState[3] = (state >> 16) & 0xFF;


    return 0;
}


/****************************************************************************/
/** platform millisecond counter function
 *
 * This function returns the number of milliseconds since start of system
 *
 */
GOAL_TIMESTAMP_T plat_getMsTimer(
    void
)
{
    GOAL_TIMESTAMP_T millis_return;
    
    millis_return = milliseconds;
    
    return millis_return;
}


/****************************************************************************/
/** memory allocation done function
 *
 * this overloads a weak implementation, to show available HEAP on this platform
 *
 */
void plat_heapAllocDone(
    void
) {

}



/****************************************************************************/
/** Event Callback Register
 */
int plat_eventRegister(
    GOAL_BOOL_T flgAutoStart,                   /**< flag enable interrupts */
    GOAL_MA_EVENT_NOTIFY fNotify                /**< notify callback */
)
{
    UNUSEDARG(flgAutoStart);
    UNUSEDARG(fNotify);

    return 0;
}


/****************************************************************************/
/** Enable Event Callback
 */
int plat_eventEnable(
    void
)
{
    return 0;
}


/****************************************************************************/
/** Disable Event Callback
 */
int plat_eventDisable(
    void
)
{
    return 0;
}

// Callback from 1ms timer interrupt

void dpm_app_1ms_callback(void) {
    milliseconds++;
}
