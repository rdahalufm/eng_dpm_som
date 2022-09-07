/* 
 * File:   main.c
 * Author: Rupak
 *
 * Created on July 26, 2017, 3:22 PM
 */

#include "dpm_bsp.h"
#include "dpm_lcd.h"
#include "dpm_menu.h"
#include "dpm_adc.h"
#include "dpm_protocol.h"
#include "dpm_flow.h"
#include "goal_appl.h"
#include "ugoal.h"
#include "ugoal_plat.h"
#include <stdio.h>

#ifndef BOOTLOADER_MODE
#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config FPLLMUL  = MUL_15        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config WDTPS = PS1024          // Watchdog Timer Postscaler (1:1024) // 1.024s
#pragma config FWDTEN = OFF              // Watchdog Timer Disabled (WDT Disabled)
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = ON            // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#endif

#define CLEAR_WATCHDOG()    ClearWDT()
#define ENABLE_WATCHDOG()   EnableWDT()
#define WATCHDOG_SET_1S()   (WDTCONbits.WDTPS = 0x0A)
#define WATCHDOG_SET_4S()   (WDTCONbits.WDTPS = 0x0C)



UINT32 SerialNumber = 0xFFFFFFFF;
#ifdef SOM_UGOAL
volatile UINT8 IPAddressLocal[4],SMaskLocal[4],MACAddress[6];
#endif

void clear_wdt() {
    CLEAR_WATCHDOG();
}

void _mon_putc(char data){
    while(!UARTTransmitterIsReady(UART2)){}
    UARTSendDataByte(UART2, data);
}


void dpm_app_factory_reset_callback() {

}

// Entry point of the code 
int main() {
    DPMSoftTimer test_timer;
    // Setup the system 
    SYSTEMConfigPerformance(GetSystemClock());
    
    // Initialize the Board Support Package 
    dpm_bsp_init();
    
    // Initialize the pnet specific application
    pnet_app_init();    
    
    printf("UGOAL APP init\r\n");
#if SOM_UGOAL == 1    
    plat_init();
    dpm_bsp_delay_ms(100);
    som_init();
    appl_init();
    
#endif    
    
    // RTC CS off
    TRISDbits.TRISD7 = 0;
    LATDbits.LATD7 = 0; // Chip select should be low for RTC, Strange!
    
    // EEPROM off
    LATEbits.LATE1 = 1;//CS high
    
    printf("UGOAL APP Init done \r\n");
    dpm_check_timeout_ms(&test_timer, 0);
    // Enable Watchdog
    WATCHDOG_SET_4S();
    ENABLE_WATCHDOG();
    
    while(1) {
        // Reset the watchdog timer periodically
        CLEAR_WATCHDOG();
        
        // This processes the board functionality
        dpm_bsp_task_run();
        
        #if SOM_UGOAL == 1 
        // Run uGoal application
        ugoal_loop();
        #endif /* SOM UGOAL */
        
        // Run the Chrysler specific application 
        pnet_app_run();
    }
    
    return (EXIT_SUCCESS);
}

