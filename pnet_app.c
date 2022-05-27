#include "pnet_app.h"
#include "dpm_lcd.h"
#include "dpm_menu.h"
#include "dpm_adc.h"
#include "dpm_protocol.h"
#include "dpm_flow.h"
#include "dpm_mem.h"
#include "ad_obj.h"
#include "dpm_datalogger.h"

#define  VENTURI_TIMER_MAX          999
#define  VENTURI_TIMER_MIN          0
#define  BYPASS_TIMING_MAX          40
#define  BYPASS_TIMING_MIN          2
#define  BIT(n)                     (1 << n)



struct TestStruct {
    int a;
};


struct {
    uint16_t venturiTimeout;
    int16_t venturiTime;
    bool_t bypassRequest;
    bool_t venturiStart;
    bool_t venturiEn;
    bool_t venturiDispEnd;
    
    // EIP status bits
    union {
        uint8_t statusByte;
        struct {
            uint8_t flowOkay : 1;
            uint8_t valveClosed : 1;
            uint8_t bypass : 1;
            uint8_t minFlow : 1;
            uint8_t leak : 1;
            uint8_t lowTemp : 1;
            uint8_t highTemp : 1;
            uint8_t bypassReq : 1;
        };
    };
    
    union {
        uint8_t webCommand;
        struct {
            uint8_t webBypass : 1;
            uint8_t webShutoff : 1;
            uint8_t : 6;
        };
    };
    bool_t remoteShutoff;
    bool_t remoteReset;
    bool_t remoteBypass;
    bool_t menuUnlock;
    bool_t parametersUpdated;
}pnetParams;

enum {
    TIMER_OFF = 0,
    TIMER_VENTURI,
    TIMER_DRAWBACK
};
static DPMSoftTimer disp_timer;
extern UINT32 SerialNumber;
/**************************   CALLBACK FUNCTIONS DEMANDED BY THE FRAMEWORK   ************************/

void dpm_abcc_protocol_callback(void) {
    uint8_t cmd;

    // Send the EIP inputs
//    EIP_SetRobotInputs( pnetParams.statusByte, 
//                        dpm_get_flow(DPM_FLOW_IN)/10, 
//                        dpm_get_flow(DPM_FLOW_OUT)/10,
//                        dpm_adc_get_temp(TEMP_SENSOR1) );
//    
//    // Respond to EIP outputs
//    cmd = EIP_GetCommand();
    pnetParams.remoteReset = cmd & 0x01 ? 1 : 0;
    pnetParams.remoteShutoff = cmd & 0x02 ? 1 : 0;
    pnetParams.remoteBypass = cmd & 0x04 ? 1 : 0;   
    pnetParams.menuUnlock = cmd & 0x80 ? 1 : 0;
    dpm_flags_t.remoteReset = pnetParams.remoteReset;
}


unsigned char dpm_app_get_command(void) {
    return (pnetParams.remoteReset | pnetParams.remoteShutoff << 1 | pnetParams.remoteBypass << 2);
}

void dpm_abcc_web_callback(void) {
//    __WebValues__ webValues;
//    uint8_t i;
//    bool_t unitsChangeFlag = False;
//    
//    Web_GetWebValues(&webValues);
//    
//    // Bit 0 means change in IP
//    if (webValues.webStatus & BIT(0)) {
//        for (i = 0; i < 4; i++) {
//            IPAddressLocal[i] = webValues.IPAddress[i];
//            EEWrite(AdIP1 + i, IPAddressLocal[i]);
//        }
//        AnybusSetIP = 1;
//        AnybusSetStatic = 1;
//        AB_fReInitDriver = TRUE;
//        webValues.webStatus &= ~BIT(0);
//    }
//    
//    // Bit 1 means change in SMask
//    if (webValues.webStatus & BIT(1)) {
//        for(i = 0; i < 4; i++) {
//            SMaskLocal[i] = webValues.SMask[i];
//            EEWrite(AdSM1 + i, SMaskLocal[i]);
//        }
//        AnybusSetIP = 1;
//        AnybusSetStatic = 1;
//        AB_fReInitDriver = TRUE;
//        webValues.webStatus &= ~BIT(1);
//    }
//    
//    if(webValues.webStatus & BIT(2)) {
//        if (dpm_msg_t.unit != webValues.unit) {
//            dpm_msg_t.unit = webValues.unit;
//            dpm_convert_units();
//            webValues.webStatus &= ~(BIT(3) | BIT(4) | BIT(5) | BIT(6) | BIT(7) | BIT(8));
//            unitsChangeFlag = True;
//            dpm_flags_t.parametersUpdated = 1;
//        }
//        webValues.webStatus &= ~BIT(2);
//    }
//    
//    if (unitsChangeFlag == False) {        
//        // Min Flow Changed
//        if (webValues.webStatus & BIT(3)) {
//            dpm_msg_t.minFlow = webValues.minFlow;
//            if (dpm_msg_t.minFlow < dpm_msg_t.minFlowMin) {
//                dpm_msg_t.minFlow = dpm_msg_t.minFlowMin;
//            } else if (dpm_msg_t.minFlow > dpm_msg_t.minFlowMax) {
//                dpm_msg_t.minFlow = dpm_msg_t.minFlowMax;
//            }
//            EEWrite(AdMinFlowLo,dpm_msg_t.minFlow);
//            EEWrite(AdMinFlowHi,dpm_msg_t.minFlow >> 8);
//            webValues.webStatus &= ~BIT(3);
//            pnetParams.parametersUpdated = 1;
//        }
//        
//        // Flow Okay Changed
//        if (webValues.webStatus & BIT(4)) {
//            dpm_msg_t.flowOk = webValues.flowOkay;
//            
//            if (dpm_msg_t.flowOk < dpm_msg_t.flowOkMin) {
//                dpm_msg_t.flowOk = dpm_msg_t.flowOkMin;
//            } else if (dpm_msg_t.flowOk > dpm_msg_t.flowOkMax) {
//                dpm_msg_t.flowOk = dpm_msg_t.flowOkMax;
//            }
//            EEWrite(AdFlowOKLo,dpm_msg_t.flowOk);
//            EEWrite(AdFlowOKHi,dpm_msg_t.flowOk >> 8);
//            webValues.webStatus &= ~BIT(4);
//            pnetParams.parametersUpdated = 1;
//        }
//        
//        // Leak Rate Changed
//        if (webValues.webStatus & BIT(5)) {
//            dpm_msg_t.leakRate = webValues.leakRate;
//            
//            if (dpm_msg_t.leakRate < dpm_msg_t.leakRateMin) {
//                dpm_msg_t.leakRate = dpm_msg_t.leakRateMin;
//            } else if (dpm_msg_t.leakRate > dpm_msg_t.leakRateMax) {
//                dpm_msg_t.leakRate = dpm_msg_t.leakRateMax;
//            }
//            webValues.webStatus &= ~BIT(5);
//            pnetParams.parametersUpdated = 1;
//            EEWrite(AdLeakRateLo,dpm_msg_t.leakRate);
//            EEWrite(AdLeakRateHi,dpm_msg_t.leakRate >> 8);
//        }
//        
//        // Over Temperature Changed
//        if (webValues.webStatus & BIT(6)) {
//            dpm_msg_t.overTemp = webValues.overTemp;
//            
//            if (dpm_msg_t.overTemp < dpm_msg_t.overTempMin) {
//                dpm_msg_t.overTemp = dpm_msg_t.overTempMin;
//            } else if (dpm_msg_t.overTemp > dpm_msg_t.overTempMax) {
//                dpm_msg_t.overTemp = dpm_msg_t.overTempMax;
//            }
//            webValues.webStatus &= ~BIT(6);
//            pnetParams.parametersUpdated = 1;
//            EEWrite(AdOTempLo,dpm_msg_t.overTemp);
//            EEWrite(AdOTempHi,dpm_msg_t.overTemp >> 8);
//        }
//        
//        // Under Temperature Changed
//        if (webValues.webStatus & BIT(14)) {
//            dpm_msg_t.underTemp = webValues.underTemp;
//            
//            if (dpm_msg_t.underTemp < dpm_msg_t.underTempMin) {
//                dpm_msg_t.underTemp = dpm_msg_t.underTempMin;
//            } else if (dpm_msg_t.underTemp > dpm_msg_t.underTempMax) {
//                dpm_msg_t.underTemp = dpm_msg_t.underTempMax;
//            }
//            pnetParams.parametersUpdated = 1;
//            webValues.webStatus &= ~BIT(14);
//            EEWrite(AdUTempLo,dpm_msg_t.underTemp);
//            EEWrite(AdUTempHi,dpm_msg_t.underTemp >> 8);
//        }
//        
//        // Response Time Changed       
//        if (webValues.webStatus & BIT(7)) {
//            dpm_msg_t.responseTime = webValues.responseTime;
//            
//            if (dpm_msg_t.responseTime < dpm_msg_t.responseTimeMin) {
//                dpm_msg_t.responseTime = dpm_msg_t.responseTimeMin;
//            } else if (dpm_msg_t.responseTime > dpm_msg_t.responseTimeMax) {
//                dpm_msg_t.responseTime = dpm_msg_t.responseTimeMax;
//            }
//            
//            webValues.webStatus &= ~BIT(7);
//            pnetParams.parametersUpdated = 1;
//            EEWrite(AdResponseT,dpm_msg_t.responseTime);
//        }
//        
//        // Restart Time Changed
//        if (webValues.webStatus & BIT(8)) {
//            dpm_msg_t.restartTime = webValues.restartTime;
//            
//            if (dpm_msg_t.restartTime < dpm_msg_t.restartTimeMin) {
//                dpm_msg_t.restartTime = dpm_msg_t.restartTimeMin;
//            } else if (dpm_msg_t.restartTime > dpm_msg_t.restartTimeMax) {
//                dpm_msg_t.restartTime = dpm_msg_t.restartTimeMax;
//            }
//            webValues.webStatus &= ~BIT(8);
//            pnetParams.parametersUpdated = 1;
//            EEWrite(AdOTempLo,dpm_msg_t.restartTime);
//            EEWrite(AdOTempHi,dpm_msg_t.restartTime >> 8);
//        }
//        
//        // Venturi Time Changed
//        if (webValues.webStatus & BIT(15)) {
//            pnetParams.venturiTimeout = webValues.venturiTime;
//            if (pnetParams.venturiTimeout < VENTURI_TIMER_MIN) {
//                pnetParams.venturiTimeout = VENTURI_TIMER_MIN;
//            } else if (pnetParams.venturiTimeout > VENTURI_TIMER_MAX) {
//                pnetParams.venturiTimeout = VENTURI_TIMER_MAX;
//            }
//            EEWrite(AdVenturiTimerLo,pnetParams.venturiTimeout);
//            EEWrite(AdVenturiTimerHi,pnetParams.venturiTimeout >> 8);
//            webValues.webStatus &= ~BIT(15);
//            pnetParams.parametersUpdated = 1;
//        }
//    }
//    
//    if (webValues.webStatus & BIT(9)) {
//        // Bypass pressed
//        pnetParams.webBypass ^= 1;
//        webValues.webStatus &= ~BIT(9);
//    }
//    
//    if (webValues.webStatus & BIT(10)) {
//        pnetParams.webShutoff ^= 1;
//        // Valve Pressed
//        webValues.webStatus &= ~BIT(10);
//    }
//    
//    if (webValues.webStatus & BIT(11)) {
//        // Reset
//        dpm_flags_t.appReset = 1;
//        webValues.webStatus &= ~BIT(11);
//    }
//    
//    if (dpm_get_protocol_status()) {
//        webValues.webStatus |= BIT(12);
//    } else {
//        webValues.webStatus &= ~BIT(12);
//    }
//    
//    if (VENTURI_VALVE == 1) {
//        webValues.webStatus |= BIT(13);
//    } else {
//        webValues.webStatus &= ~BIT(13);
//    }
//   
//    // Update the website parameters once internally updated 
//    if (pnetParams.parametersUpdated == True || dpm_flags_t.parametersUpdated == 1) {
//        pnetParams.parametersUpdated = False;
//        dpm_flags_t.parametersUpdated = 0;
//        webValues.unit = dpm_msg_t.unit;
//        webValues.minFlow = dpm_msg_t.minFlow;
//        webValues.flowOkay = dpm_msg_t.flowOk;
//        webValues.leakRate = dpm_msg_t.leakRate;
//        webValues.overTemp = dpm_msg_t.overTemp;
//        webValues.underTemp = dpm_msg_t.underTemp;
//        webValues.responseTime = dpm_msg_t.responseTime;
//        webValues.restartTime = dpm_msg_t.restartTime;
//        webValues.venturiTime = pnetParams.venturiTimeout;
//        webValues.serialNumber = SerialNumber;
//        webValues.firmwareRev = 200;
//        webValues.webSupply = dpm_get_flow(DPM_FLOW_IN);
//        webValues.webReturn = dpm_get_flow(DPM_FLOW_OUT);
//        for (i = 0; i < 4; i++) {
//            webValues.IPAddress[i] = IPAddressLocal[i];
//            webValues.SMask[i] = SMaskLocal[i];
//        }
//        Web_SetWebValues(&webValues);
//    }   
//    Web_SetActiveData(webValues.webStatus, dpm_get_flow(DPM_FLOW_IN), dpm_get_flow(DPM_FLOW_OUT));
}

void pnet_app_handle_disconnect() {
    // Reset the command received earlier , if there is no EIP communication
    pnetParams.remoteBypass = 0;
    pnetParams.remoteShutoff = 0;
    pnetParams.remoteReset = 0;
    dpm_flags_t.remoteReset = 0;
}


// DPM application callback from the framework 
void dpm_app_flow_display(void) { 

    static uint16_t states = 0;

    // Display Message in Line 1 of the LCD 
    lcd_line1();
    // This space is occupied by venturi message if it is on 
    if (pnetParams.venturiStart == False || pnetParams.venturiDispEnd == True) {   
        dpm_bsp_display_flow(dpm_get_flow(DPM_FLOW_IN));
        if(dpm_msg_t.unit == GPM) {
            lcd_write_msg(" GPM ");
        } else {
            lcd_write_msg(" LPM ");
        }        
        // Fault Messages on the upper line of the LCD 
        if (pnetParams.leak || dpm_flags_t.noFlowFault) {
            lcd_write_msg(" Fault     ");
        } else if (pnetParams.minFlow == False) {
            lcd_write_msg(" Min       ");        
        } else if (!pnetParams.flowOkay) {
            lcd_write_msg(" Low        ");
        } else {
            lcd_write_msg(" OK         ");
        }
    } else {
        if (pnetParams.venturiEn == TIMER_VENTURI) {
            lcd_write_msg("VENTURI:   ");        
        } else {
            lcd_write_msg("D/B TIMER: ");
        }
        if(pnetParams.venturiTime) {
            dpm_put_digit(pnetParams.venturiTime);
        } else {
            if (pnetParams.venturiEn == TIMER_VENTURI) {
                lcd_write_msg("OFF");        
            } else {
                lcd_write_msg("ON");
            }                           
        }
        lcd_write_msg("       ");            
    }
    // Display Message in Line 2 of the LCD 
    lcd_line2();
  
    // Messages sent remotely take higher priority    
    if ((pnetParams.remoteShutoff && pnetParams.remoteBypass)) {
        lcd_write_msg("    BP/SO       ");
    } else if (pnetParams.remoteShutoff) {
        lcd_write_msg("    Shutoff      ");
    } else if (pnetParams.remoteBypass) {
        lcd_write_msg("    Bypass        ");
    } else if (pnetParams.webBypass || pnetParams.webShutoff){
        if (pnetParams.webBypass && pnetParams.webShutoff) {
            lcd_write_msg("    WBP/WSO        ");
        } else if (pnetParams.webBypass) {
            lcd_write_msg("     WBP            ");
        } else {
            lcd_write_msg("     WSO            ");
        }
    } else {    
        // If no command has been sent from the Profinet, display regular messages
        if (dpm_flags_t.returnGSupply) {
            lcd_write_msg("Return > Supply    ");
        } 
    }
    // Fill up remaining spaces
    lcd_write_msg("               ");
    
    if(pnetParams.bypassRequest) {
        lcd_write_cmd(0xC0 + 15); // go to the end of LCD's second line 
        lcd_write_char('R');
    }   
    
}


/**************************   CALLBACK FUNCTIONS END   ***************************************************/


/************************ APPLICATION FUNCTIONS ***********************************************************/

static void pnet_show_status_bits() {
    lcd_line2();
    // Display remote commands
    lcd_write_char(dpm_flags_t.remoteBypass + 0x30);
    lcd_write_char(dpm_flags_t.remoteShutoff + 0x30);
    lcd_write_char(dpm_flags_t.remoteReset + 0x30);
    lcd_write_char(' ');
    lcd_write_char(' ');
    // Display status bits
    dpm_display_bits(pnetParams.statusByte,8);
    lcd_write_msg("                 ");
}

static void pnet_show_return_flow() {
    lcd_line2();
    // Display the return flow on the lower line of the LCD
    dpm_bsp_display_flow(dpm_get_flow(DPM_FLOW_OUT));
    if(dpm_msg_t.unit == GPM) {
        lcd_write_msg(" GPM ");
    } else {
        lcd_write_msg(" LPM ");
    }   
    lcd_write_msg("Outlet ");
}

static DPMMenuReturn pnet_units_menu(DPMMenuParams *menuParams) {
    DPMMenuReturn ret = MENU_IN_PROGRESS;
    static uint16_t temp = 0;  
    
    // For the new call from the menu process,
    // record the most recent setpoint value    
    if(menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = dpm_msg_t.unit;
        lcd_line1();
        lcd_write_msg("Units:          ");
    }    
        // Display the menu value on the second row
    lcd_line2();
    if(temp == GPM) {
        lcd_write_msg("GPM             ");
    } else {
        lcd_write_msg("LPM             ");
    }
    
    if(menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_DONE;
    } 
    else if(menuParams->buttonStatus & BUTTON_ENTER) {
        lcd_line1();
        lcd_write_msg("                ");
        lcd_line2();
        lcd_write_msg("    SET         ");
        dpm_msg_t.unit = temp;
        dpm_convert_units();
        ret = MENU_SAVED;
    } 
    else if(menuParams->buttonStatus & BUTTON_UP) {
        if(temp == GPM) {
            temp = LPM;
        } else {
            temp = GPM;
        }
    }    
    else if(menuParams->buttonStatus & BUTTON_DOWN) {
        if(temp == GPM) {
            temp = LPM;
        } else {
            temp = GPM;
        }
    } else if(menuParams->buttonStatus & BUTTON_BYPASS) {
         ret = MENU_MOVE_TO_NEXT;
    }
    return ret;
}

static DPMMenuReturn pnet_bypass_menu(DPMMenuParams *menuParams) {
    DPMMenuReturn ret = MENU_IN_PROGRESS;
    static uint16_t temp = 0;  
    
    // For the new call from the menu process,
    // record the most recent setpoint value    
    if(menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = dpm_msg_t.bypassReqTime;
        lcd_line1();
        lcd_write_msg("BP Request Time:     ");
    }
        // Display the menu value on the second row
    lcd_line2();
    if(dpm_get_nth_digit(temp,2)) lcd_write_char(dpm_get_nth_digit(temp,2)+0x30);
    if(dpm_get_nth_digit(temp,1)) lcd_write_char(dpm_get_nth_digit(temp,1)+0x30);
    lcd_write_char('.');
    lcd_write_char(dpm_get_nth_digit(temp,0)+0x30);
    
    lcd_write_char(' ');
    lcd_write_msg("Secs        ");
    
    if(menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_DONE;
    }
    else if(menuParams->buttonStatus & BUTTON_ENTER) {
        lcd_line1();
        lcd_write_msg("                ");
        lcd_line2();
        lcd_write_msg("    SET         ");
        dpm_msg_t.bypassReqTime = temp;
        EEWrite(AdRequestT,dpm_msg_t.bypassReqTime);
        ret = MENU_SAVED;
    }
    else if(menuParams->buttonStatus & BUTTON_UP) {
        temp += 1;
    }    
    else if(menuParams->buttonStatus & BUTTON_DOWN) {
        temp -= 1;
    } 
    
    if(temp >= BYPASS_TIMING_MAX) {
        temp = BYPASS_TIMING_MAX;
    } else if(temp <= BYPASS_TIMING_MIN) {
        temp = BYPASS_TIMING_MIN;
    }
    return ret;
}

static DPMMenuReturn pnet_venturi_menu(DPMMenuParams *menuParams) {
    DPMMenuReturn ret = MENU_IN_PROGRESS;
    static int16_t temp = 0;  
    
    // For the new call from the menu process,
    // record the most recent setpoint value    
    if(menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = pnetParams.venturiTimeout;
        lcd_line1();
        if (pnetParams.venturiEn == TIMER_VENTURI) {
            lcd_write_msg("Venturi Duration: ");
        } else {
            lcd_write_msg("Drawback Time:    ");
        }
        
    }    
        // Display the menu value on the second row
    lcd_line2();
    lcd_write_char(dpm_get_nth_digit(temp,2)+0x30);
    lcd_write_char(dpm_get_nth_digit(temp,1)+0x30);
    lcd_write_char(dpm_get_nth_digit(temp,0)+0x30);
    lcd_write_char(' ');
    lcd_write_msg("Sec.        ");
    
    if(menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_MOVE_TO_NEXT;
    }
    else if(menuParams->buttonStatus & BUTTON_ENTER) {
        lcd_line1();
        lcd_write_msg("                ");
        lcd_line2();
        lcd_write_msg("    SET         ");
        pnetParams.venturiTimeout = temp;
        EEWrite(AdVenturiTimerLo,pnetParams.venturiTimeout);
        EEWrite(AdVenturiTimerHi,pnetParams.venturiTimeout >> 8);
        ret = MENU_SAVED;
    }
    else if(menuParams->buttonStatus & BUTTON_UP) {
        temp += 1;
    }    
    else if(menuParams->buttonStatus & BUTTON_DOWN) {
        temp -= 1;
    }
    
    if(temp >= VENTURI_TIMER_MAX) {
        temp = VENTURI_TIMER_MAX;
    } else if(temp <= VENTURI_TIMER_MIN) {
        temp = VENTURI_TIMER_MIN;
    }
    return ret;
}


static DPMMenuReturn pnet_flowok_menu(DPMMenuParams *menuParams) {
    static uint16_t temp = 0;
    DPMMenuReturn ret = MENU_IN_PROGRESS;    
    
    // For the new call from the menu process,
    // record the most recent setpoint value   
    if(menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = dpm_msg_t.flowOk;
            // Display menu name on the first row
        lcd_line1();
        lcd_write_msg(FLOW_OK_TITLE);
    }   
    // Display the menu value on the second row
    lcd_line2();
    dpm_bsp_display_flow(temp);      
    if(dpm_msg_t.unit == GPM) {
        lcd_write_msg("  GPM        ");
    } else {
        lcd_write_msg("  LPM        ");
    }       
    
    if(menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_MOVE_TO_NEXT;
    } else {
        if (pnetParams.menuUnlock) {
                if(menuParams->buttonStatus & BUTTON_ENTER) {
                    lcd_line1();
                    lcd_write_msg("               ");
                    lcd_line2();
                    lcd_write_msg("    SET        ");
                    dpm_msg_t.flowOk = temp;        
                    EEWrite(AdFlowOKLo,dpm_msg_t.flowOk);
                    EEWrite(AdFlowOKHi,dpm_msg_t.flowOk>>8);
                    ret = MENU_SAVED;
                }
                else if(menuParams->buttonStatus & BUTTON_UP) {
                    temp += 10;
                }    
                else if(menuParams->buttonStatus & BUTTON_DOWN) {
                    temp -= 10;
                } 
        }
    }

   
    // Flow okay settings should not 
    if (temp < (dpm_msg_t.minFlow + 20)) {
        temp = dpm_msg_t.minFlow + 20;
    } else if (temp < dpm_msg_t.flowOkMin) {
        temp = dpm_msg_t.flowOkMin;
    } else if(temp > dpm_msg_t.flowOkMax) {
        temp = dpm_msg_t.flowOkMax;
    } 
    
    return ret;
}


static DPMMenuReturn pnet_minflow_menu(DPMMenuParams *menuParams) {   
    static uint16_t temp = 0;
    DPMMenuReturn ret = MENU_IN_PROGRESS;    
    
    // For the new call from the menu process,
    // record the most recent setpoint value    
    if (menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = dpm_msg_t.minFlow;
            // Display menu name on the first row
        lcd_line1();
        lcd_write_msg(MIN_FLOW_TITLE);
    }
    
    // Display the menu value on the second row
    lcd_line2();
    dpm_bsp_display_flow(temp);
    if (dpm_msg_t.unit == GPM) {
        lcd_write_msg("  GPM        ");
    } else {
        lcd_write_msg("  LPM        ");
    }   
    if (menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_MOVE_TO_NEXT;
    } else {
        if (pnetParams.menuUnlock) {
                if (menuParams->buttonStatus & BUTTON_ENTER) {
                    lcd_line1();
                    lcd_write_msg("               ");
                    lcd_line2();
                    lcd_write_msg("    SET        ");
                    dpm_msg_t.minFlow = temp;
                    EEWrite(AdMinFlowLo,dpm_msg_t.minFlow);
                    EEWrite(AdMinFlowHi,dpm_msg_t.minFlow>>8);
                    ret = MENU_SAVED;
                }
                else if (menuParams->buttonStatus & BUTTON_UP) {
                    temp += 10;
                }    
                else if (menuParams->buttonStatus & BUTTON_DOWN) {
                    temp -= 10;
                } 
        }
    }

    
    if (temp > dpm_msg_t.minFlowMax) {
        temp = dpm_msg_t.minFlowMax;
    } else if (temp < dpm_msg_t.minFlowMin) {
        temp = dpm_msg_t.minFlowMin;
    }
    return ret;
}


static DPMMenuReturn pnet_responsetime_menu(DPMMenuParams *menuParams) {
    DPMMenuReturn ret = MENU_IN_PROGRESS;
    static uint16_t temp = 0;  
    
    // For the new call from the menu process,
    // record the most recent setpoint value    
    if(menuParams->firstFlag == 0) {
        menuParams->firstFlag = 1;
        temp = dpm_msg_t.responseTime;
        lcd_line1();
        lcd_write_msg(RESPONSE_TIME_TITLE);
    }
        // Display the menu value on the second row
    lcd_line2();
    if(dpm_get_nth_digit(temp,2))lcd_write_char(dpm_get_nth_digit(temp,2)+0x30);
    lcd_write_char(dpm_get_nth_digit(temp,1)+0x30);
    lcd_write_char('.');
    lcd_write_char(dpm_get_nth_digit(temp,0)+0x30);
    lcd_write_char(' ');
    lcd_write_msg("Sec.        ");
    
    if(menuParams->buttonStatus & BUTTON_PGM) {
        ret = MENU_MOVE_TO_NEXT;
    }
    else if(menuParams->buttonStatus & BUTTON_ENTER) {
        lcd_line1();
        lcd_write_msg("               ");
        lcd_line2();
        lcd_write_msg("    SET        ");
        dpm_msg_t.responseTime = temp;
        EEWrite(AdResponseT,dpm_msg_t.responseTime);
        ret = MENU_SAVED;
    }
    else if(menuParams->buttonStatus & BUTTON_UP) {
        temp += 5;
	if (temp == 25) temp = 50; // After 2 seconds, next is 5 seconds
	if (temp == 55) temp = 100; // After 5 seconds, next if 10 seconds
    }    
    else if(menuParams->buttonStatus & BUTTON_DOWN) {
        temp -= 5;
	if (temp == 45) temp = 20; // After 5 seconds, next is 2 seconds
	if (temp == 95) temp = 50; // After 10 seconds, next is 2 seconds
    } 
    
    
    if(temp > dpm_msg_t.responseTimeMax) {
        temp = dpm_msg_t.responseTimeMax;
    } else if(temp < dpm_msg_t.responseTimeMin) {
        temp = dpm_msg_t.responseTimeMin;
    }
    return ret;
}

static bool_t pnet_display_network() {
    bool_t ret = False;
    static DPMSoftTimer networkTimer;
    static uint8_t networkDispStates = 0;
    
    if (dpm_check_timeout_ms(&networkTimer, 3000)) {
        switch (networkDispStates) {
            case 0:
                dpm_display_ip();
                networkDispStates++;   
                break;

            case 1:   
                dpm_display_smask(); 
                networkDispStates++;
                break;

            case 2:
                dpm_display_mac();
                networkDispStates++;
                break;

            case 3:
                networkDispStates = 0;
                ret = True;
                break;
            default:
                ret = True;
                networkDispStates = 0;
                
                break;
        }
    }
    return ret;
}

static void pnet_buttons_monitor() {  
    static bool_t buttonPressed = False;
    static bool_t enterPressed = False;
    static char datalogger_msg[40];
    static DPMSoftTimer datalogger_timer;
    static bool_t dataLogDisp = False;
    // UP and Down Monitor while the user is not in the menu
    if (dpm_get_menu_status() == MENU_IDLE) { 
                
        // If ENTER is pressed 
        if(dpm_get_button_pressed() == BUTTON_ENTER && enterPressed == False) {
            enterPressed = True;
            dpm_flags_t.appDisplayLock = 1;	    
	    dataLogDisp = False;
        } else if (enterPressed == True) {	    
	    if (dpm_datalogger_is_active()) {		
		if (dataLogDisp == False) {
		    dataLogDisp = True;
		    lcd_line1();
		    sprintf(datalogger_msg, "DAT%d            ", dpm_datalogger_get_data_count());
		    lcd_write_msg(datalogger_msg);
		    if (dpm_datalogger_get_status() == DATALOGGING_STARTED) {
                lcd_line2();
                dpm_datalogger_stop();		    
                lcd_write_msg("Eject USB              ");
		    } else if (dpm_datalogger_get_status() == DATALOGGING_EXIT) {
                lcd_line2();
                dpm_datalogger_start();
                lcd_write_msg("Started Logging            ");
		    }
		    dpm_check_timeout_ms(&datalogger_timer, 0);
		} else {
		    if (dpm_check_timeout_ms(&datalogger_timer, 2000)) {
                enterPressed = False;
                dpm_flags_t.appDisplayLock = 0;
		    }
		}
	    } else {
            if (pnet_display_network() == True) {
                enterPressed = False;
                dpm_flags_t.appDisplayLock = 0;
            }
	    }

        } else {
            // Show status bits when pressed up
            // If UP and other button has been pressed, only bypass button would have no effect  
            if(dpm_get_button_pressed() == BUTTON_UP || dpm_get_button_pressed() == (BUTTON_UP | BUTTON_BYPASS)) {
                // Acquire the access to the LCD display
                dpm_flags_t.appDisplayLock = 1;                         
                pnet_show_status_bits();
            } else if(dpm_get_button_pressed() == BUTTON_NONE) {
                // Release the access to the LCD display
                dpm_flags_t.appDisplayLock = 0; 
            }
            // If DOWN and other button has been pressed, only bypass button would have no effect  
            if(dpm_get_button_pressed() == BUTTON_DOWN || dpm_get_button_pressed() == (BUTTON_DOWN | BUTTON_BYPASS)) {
                // Acquire the access to the LCD display
                dpm_flags_t.appDisplayLock = 1; 
                // Prevent from rewriting into LCD, causing glitter on display
                if (buttonPressed == False) {
                    pnet_show_return_flow();
                }
                buttonPressed = True; 
            } else if(dpm_get_button_pressed() == BUTTON_NONE) {
                buttonPressed = False;
                // Release the access to the LCD display
                dpm_flags_t.appDisplayLock = 0; 
            }
        }

    }
}

static void pnet_fault_monitor() {
    // Status bits 
    pnetParams.leak = dpm_flags_t.leakFault;
    pnetParams.bypass = pnetParams.remoteBypass | pnetParams.webBypass;
    pnetParams.flowOkay = ~dpm_flags_t.flowFault;
    
    // Disabled in FP14
//    pnetParams.highTemp = dpm_flags_t.overTempFault;
//    pnetParams.lowTemp = dpm_flags_t.underTempFault;
    
    pnetParams.highTemp = 0;
    pnetParams.lowTemp = 0;
    
    pnetParams.bypassReq = pnetParams.bypassRequest;
    pnetParams.minFlow = ~dpm_flags_t.minFlowFault;
    
    // Leak or minimum flow will cause the flow okay bit to go 0
    if (pnetParams.leak || !pnetParams.minFlow) {        
        pnetParams.flowOkay = 0;          
    }
    
    if (dpm_flags_t.reset || dpm_flags_t.appReset || dpm_flags_t.remoteReset) {
        // During a reset the minflow and flow okay both need to be off
        pnetParams.minFlow = 0;
        pnetParams.flowOkay = 0;
        pnetParams.valveClosed  = 0;
    } else {
        // Direct shutoff command from the GUI or the WEB should shut the valve off
        if(pnetParams.remoteShutoff || pnetParams.webShutoff) {
            pnetParams.valveClosed = 1;
        } else {
            if (pnetParams.leak || dpm_flags_t.noFlowFault) {
                // Bypass only opens the valve if closed
                // It doesn't change the status of any other bit
                if (pnetParams.bypass) {
                    pnetParams.valveClosed  = 0;
                } else {
                    pnetParams.valveClosed  = 1;
                }
            } else {           
                pnetParams.valveClosed  = 0;
            }
        }
    }

    // Valve control
    if (pnetParams.valveClosed) {
        VALVE = 1; 
    } else {
        VALVE = 0; 
    }
    
    // LEDs
    // Flow Okay LED
    if (pnetParams.flowOkay) {        
            FLOWOK_GLED_ON();
            FLOWOK_RLED_OFF();
    } else {
        FLOWOK_RLED_ON();
        FLOWOK_GLED_OFF();
    }
    
    // Min Flow LED
    if ((pnetParams.minFlow == 0) || (pnetParams.flowOkay == 0)) {
        MINFLOW_LED_ON();
    } else {
        MINFLOW_LED_OFF();
    }
    
    // Valve LED
    if (pnetParams.valveClosed) {       
        VALVE_RLED_ON();
        VALVE_GLED_OFF();
    } else {
        VALVE_RLED_OFF();
        VALVE_GLED_ON();
    }
    
    // Aux Power    
    if (dpm_flags_t.powerFault) {
        AUXPWR_GLED_OFF();       
    } else {
        AUXPWR_GLED_ON();
    }
    
    // Bypass LED   
    if (pnetParams.remoteBypass || pnetParams.webBypass) {
        BYPASS_LED_ON();
    } else {
        BYPASS_LED_OFF();
    }    
}

static void pnet_bypass_monitor() {
    static DPMSoftTimer bypassTimer;
    if((dpm_get_button_pressed() & BUTTON_BYPASS) == BUTTON_BYPASS) {
        // Enable the flag to monitor the release of the button
        pnetParams.bypassRequest = 1;
	dpm_flags_t.heartBeatDisable = 1;
        dpm_check_timeout_ms(&bypassTimer, 0);
    }
    // Start the countdown after the user has released the button
    if (pnetParams.bypassRequest) {
        // Bypass Request time is in x * 100 ms , 1 = 100ms   
        if (dpm_check_timeout_ms(&bypassTimer, (dpm_msg_t.bypassReqTime * 100))) {
            pnetParams.bypassRequest = 0;
            dpm_flags_t.heartBeatDisable = 0;
        }
    }    
}

static void pnet_venturi_monitor() {
    static DPMSoftTimer venturiTimer;     
    
    if (pnetParams.valveClosed && pnetParams.venturiStart == False) {
        pnetParams.venturiStart = True;
        dpm_check_timeout_ms(&venturiTimer, 0);
        pnetParams.venturiTime = pnetParams.venturiTimeout;        
        if (pnetParams.venturiEn == TIMER_VENTURI) {
            // Venturi Valve Open
            VENTURI_VALVE = 0;
        } else {
            // Venturi Valve still closed in case of drawback cylinder
            VENTURI_VALVE = 1;
        }
        pnetParams.venturiDispEnd = False;
    } else if (pnetParams.valveClosed == False) {
        pnetParams.venturiStart = False;
        // Valve Close 
        VENTURI_VALVE = 1;
    }
    
    // If the venturi countdown has begun
    if (pnetParams.venturiStart) {
        // Decrease the counter each second        
        if (pnetParams.venturiTime >= 1) {
            if (dpm_check_timeout_ms(&venturiTimer, 1000)) {
                pnetParams.venturiTime--;
                if(pnetParams.venturiTime <= 0) {
                    pnetParams.venturiTime = 0;
                    if (pnetParams.venturiEn == TIMER_VENTURI) {
                        // Close the venturi valve 
                        VENTURI_VALVE = 1;
                    } else {
                        // Open the drawback valve
                        VENTURI_VALVE = 0;
                    }                    
                }            
            }
        } else {
            // After the venturi countdown has ended,
            // display the venturi on message for 5 seconds before returning to normal
            if (dpm_check_timeout_ms(&venturiTimer, 5000)) {
                // Now signal the display to not show the venturi message
                pnetParams.venturiDispEnd = True;
            }            
        }
    }    
}

static void pnet_reset_monitor() {
    if (dpm_flags_t.reset || dpm_flags_t.remoteReset || dpm_flags_t.appReset) {
        // Reset the command from web if there is a reset 
        pnetParams.webCommand = 0;
    }
}


void pnet_app_run() {   
    // Monitor the state of buttons and execute accordingly
    pnet_buttons_monitor();   
    // Monitor Bypass button
    pnet_bypass_monitor();
    // Check for faults
    pnet_fault_monitor();
    // Look if the reset command has been set, in order to clear the web commands
    pnet_reset_monitor();
    // Venturi Timer set to zero disables the timer 
    if (pnetParams.venturiTimeout > 0 && pnetParams.venturiEn > TIMER_OFF) {
        pnet_venturi_monitor();
    }
}

unsigned char dpm_app_get_status(void) {
    return pnetParams.statusByte;
}

void pnet_app_init() {
    static DPMMenuStruct pnetUnitsMenu;
    static DPMMenuStruct pnetBPMenu;
    static DPMMenuStruct pnetVenturiMenu;
    static DPMMenuStruct pnetFlowOkMenu, pnetMinFlowMenu;
    static DPMMenuStruct  responseTimeMenu;
    
    dpm_check_timeout_ms(&disp_timer, 0);
    
    // Venturi Timeout Time
    pnetParams.venturiTimeout = EEDRead(AdVenturiTimerHi, AdVenturiTimerLo);    
    if (pnetParams.venturiTimeout > VENTURI_TIMER_MAX) {
        pnetParams.venturiTimeout = VENTURI_TIMER_MAX;
        EEWrite(AdVenturiTimerLo,pnetParams.venturiTimeout);        
        EEWrite(AdVenturiTimerHi,pnetParams.venturiTimeout >> 8);
    }
    // Add the venturi menu to the UI only if it has been enabled
    pnetParams.venturiEn =  EERead(AdVenturiTimerEnable);      
    
    if (pnetParams.venturiEn > TIMER_DRAWBACK) {
        pnetParams.venturiEn = TIMER_OFF;
    }
    // FP10 specific menu features 
    dpm_menu_add(&pnetFlowOkMenu, 2, pnet_minflow_menu);
    dpm_menu_add(&pnetMinFlowMenu, 3, pnet_flowok_menu);
    

    if (pnetParams.venturiEn > TIMER_DRAWBACK) {
        pnetParams.venturiEn = TIMER_OFF;
    }
    
    if (pnetParams.venturiEn > TIMER_OFF) {
        dpm_menu_add(&pnetVenturiMenu, dpm_get_menu_count(), pnet_venturi_menu);
    }
    
    dpm_menu_add(&pnetUnitsMenu, dpm_get_menu_count(), pnet_units_menu);
    // Response Time Menu
    dpm_menu_add(&responseTimeMenu,dpm_get_menu_count(), pnet_responsetime_menu);
    dpm_menu_add(&pnetBPMenu, dpm_get_menu_count(), pnet_bypass_menu);        
    
    // Venturi Valve is Closed in the beginning
    VENTURI_VALVE = 1;    
    pnetParams.venturiStart = False;
    pnetParams.venturiDispEnd = True;
    
    // Set the flag for the first update of all the EIP parameters
    pnetParams.parametersUpdated = True;            
}
