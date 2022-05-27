/* 
 * File:   dpm_config.h
 * Author: Rupak
 *
 * Created on May 11, 2017, 9:55 AM
 */

#ifndef DPM_CONFIG_H
#define	DPM_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')

#define BUILD_MONTH \
    ( \
        (BUILD_MONTH_IS_JAN) ? "01" : \
        (BUILD_MONTH_IS_FEB) ? "02" : \
        (BUILD_MONTH_IS_MAR) ? "03" : \
        (BUILD_MONTH_IS_APR) ? "04" : \
        (BUILD_MONTH_IS_MAY) ? "05" : \
        (BUILD_MONTH_IS_JUN) ? "06" : \
        (BUILD_MONTH_IS_JUL) ? "07" : \
        (BUILD_MONTH_IS_AUG) ? "08" : \
        (BUILD_MONTH_IS_SEP) ? "09" : \
        (BUILD_MONTH_IS_OCT) ? "10" : \
        (BUILD_MONTH_IS_NOV) ? "11" : \
        (BUILD_MONTH_IS_DEC) ? "12" : \
        /* error default */    "00" \
    )
    
/* Define the kind of interface being used for the product */

#ifndef SOM_UGOAL    
#define SOM_UGOAL  1    
#endif
    
//#define INTERFACE_DEVICENET
//#define INTERFACE_ETHERNET_IP
//#define INTERFACE_PROFINET

#if defined INTERFACE_DEVICENET
    #define DNET_APP_DATA_BYTES 4
    #define DATA_OUT_BYTES  1
#endif
    
/* Number of flow sensors used, usually either 2 or 3 based on if the third flowmeter has been used */    
#define FLOWSENSORS_COUNT   2
/* Define this if any temperature sensor has been used, else comment it out */
#define TEMPEATURE_ENABLED   

/* Define the number of menu items the project can have */
#define MAX_MENU_COUNT  20
    
/* Units option required?*/
#define UNITS_MENU_REQUIRED

/* If units menu not required, what is the default unit wanted? */
#ifndef UNITS_MENU_REQUIRED
    #define DEFAULT_UNIT    GPM //LPM
#endif    
/* Code name and revision for the project */
#define DPM_CODE_NAME "PNET-VNT FP14    "
#define DPM_CODE_REV  "Rev1.0 "    
 
#define TESLA
// Default display and controls setup
#define DPM_DEFAULT_TASKS
//#define READ_CONFIG_FROM_USB
#if defined DPM_DEFAULT_TASKS
    // Refresh time for the LCD
    #define LCD_UPDATE_TIME             250 // LCD refresh in milliseconds
    
    // Default display for flow and temperature readings
    #define DPM_DEFAULT_FLOW_DISPLAY    0 // 1 = enable , 0 = disable    
    
    // Heartbeat to signal flow monitoring
    #define DEFAULT_HEARTBEAT           1 // 1 = enable , 0 = disable 
    
    // Default action when bypass button has been pressed 
    #define DEFAULT_BYPASS_CHECK            0 // 1 = enable, 0 = disable
    
    // Factory reset when ENTER and bypass have been simultenously pressed
    #define DEFAULT_FACTORY_RESET   1 // 1 = enable, 0 = disable
    
    // Displays the revision number when ENTER has been pressed
    #define DEFAULT_REVISION_DISP   0   // 1 = enable, 0 = disable    
    
    // Monitor Fault by default
    #define DEFAULT_FAULT_MONITOR   1 // 1 = enable, 0 = disable
    
    // Default control of the LEDs based on the faults
    #define DEFAULT_LED_CONTROL     0 // 1 = enable, 0 = disable
    
    // Default control of the valve
    #define DEFAULT_VALVE_CONTROL   0 // 1 = enable, 0 = disable
    
    // Restart on pressing RESTART button
    #define DEFAULT_RESTART         1 // 1 = enable, 0 = disable
    
    // Monitor UP button press
    #define DEFAULT_UP_MONITOR      0 // 1 = enable, 0 = disable
   
    // Monitor DOWN button press
    #define DEFAULT_DOWN_MONITOR    0 // 1 = enable, 0 = disable
#endif
    
    
#if DEFAULT_LED_CONTROL == 1
    #define DEFAULT_BYPASS_LED_CONTROL  1 // 1 = enable, 0 = disable
    #define DEFAULT_FLOWOK_LED_CONTROL  1 // 1 = enable, 0 = disable
    #define DEFAULT_VALVE_LED_CONTROL   1 // 1 = enable, 0 = disable
    #define DEFAULT_MINFLOW_LED_CONTROL 1 // 1 = enable, 0 = disable
    #define DEFAULT_AUX_LED_CONTROL     1 // 1 = enable, 0 = disable
#endif    

#if DEFAULT_UP_MONITOR == 1
    #define DEFAULT_DISPLAY_ON_UP_PRESS     1 // 1 = enable, 0 = disable
#endif

#if DEFAULT_DOWN_MONITOR == 1
    #define DEFAULT_DISPLAY_ON_DOWN_PRESS     1 // 1 = enable, 0 = disable
#endif

    
#define DATALOGGER_ENABLED  0
    
// Max and Min Limits of Generic Parameters 
    
// For 3 GPM 
#define FLOWOK_3GPM_MAX     300
#define FLOWOK_3GPM_MIN     110
#define MINFLOW_3GPM_MAX    250
#define MINFLOW_3GPM_MIN    60
#define LEAKRATE_3GPM_MAX   100
#define LEAKRATE_3GPM_MIN   30
        
// For 6 GPM  (unit = GPM)
#define FLOWOK_6GPM_MAX     600
#define FLOWOK_6GPM_MIN     110
#define MINFLOW_6GPM_MAX    550
#define MINFLOW_6GPM_MIN    60
#define LEAKRATE_6GPM_MAX   100
#define LEAKRATE_6GPM_MIN   30

// For 12 GPM  (unit = GPM)  
#define FLOWOK_12GPM_MAX    1200
#define FLOWOK_12GPM_MIN    110
#define MINFLOW_12GPM_MAX   1150
#define MINFLOW_12GPM_MIN   80
#define LEAKRATE_12GPM_MAX  100
#define LEAKRATE_12GPM_MIN  50
                
// General delays
#define RESTARTDELAY_MAX    300 // Delay in seconds x 10 
#define RESTARTDELAY_MIN    10  // Delay in seconds x 10
#define RESPONSETIME_MAX    100  // Delay in mseconds x 100
#define RESPONSETIME_MIN    5  // Delay in mseconds x 100
    
// Temperature max in F    
#define OVERTEMP_MAX        210
#define OVERTEMP_MIN        45
#define UNDERTEMP_MAX       205
#define UNDERTEMP_MIN       40


#define RETURN_G_SUPPLY_THRESH_GPM  40
#define RETURN_G_SUPPLY_THRESH_LPM  152    
    
    
// Generic Menu Display
// Define if used     

//#define FLOW_OK_MENU    
//#define MIN_FLOW_MENU  
#define LEAK_RATE_MENU
#define RESTART_DELAY_MENU
//#define RESPONSE_TIME_MENU   
//#define OVER_TEMPERATURE_MENU    
//#define UNDER_TEMPERATURE_MENU
#ifdef UNITS_MENU_REQUIRED
//    #define UNITS_MENU
#endif    

#define FLOW_OK_TITLE "Set Flow OK:       "
#define MIN_FLOW_TITLE "Set Min Flow:     "
#define LEAK_RATE_TITLE "Set Leak Rate:   "
#define RESTART_DELAY_TITLE "Restart Delay:   "
#define RESPONSE_TIME_TITLE  "Response Time:  "
#define OVER_TEMP_TITLE "Set High Temp:       "    
#define UNDER_TEMP_TITLE "Set Low Temp:       "    
#define RESTART_MENU_TITLE "Restart Delay:    "
#define UNITS_MENU_TITLE "Units:          "
    
// Application functions if default functions are deactivated
// These functions should be defined in the application
    
#if DPM_DEFAULT_FLOW_DISPLAY  == 0  
    void dpm_app_flow_display(void); // function to display application specific lcd display
#endif

#if DEFAULT_DISPLAY_ON_UP_PRESS == 0
    // Parameter: timeExpired: True if time has expired since the function was last visited
    void dpm_app_up_diplay(unsigned char timeExpired);
#endif 
    
#if DEFAULT_DISPLAY_ON_DOWN_PRESS == 0
    // Parameter: timeExpired: True if time for display has expired since the function was last visited
    void dpm_app_down_diplay(unsigned char timeExpired);
#else
    unsigned char dpm_app_get_status (void); // Get the status bits from the application
#endif 
    
#ifdef	__cplusplus
}
#endif

#endif	/* DPM_CONFIG_H */

