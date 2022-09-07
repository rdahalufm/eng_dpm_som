/************************************************************************
 * @filename, goal_appl_http.c                                          *
 * @Description, Application for http webpage functionality             *
 *               Register webpages and handle data exchange             *
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <goal_includes.h>
#include <goal_dd.h>
#include <goal_http.h>
#include "ccm_rpc_ac.h"
#include "goal_appl_http.h"
#include "goal_appl.h"
#include <rpc/wrapper/net/ctc_net_ac.h>
#include <ctype.h>


#define CUSTOM_WEBPAGE

#ifndef CUSTOM_WEBPAGE
#include <goal_http_fs.h>
#else
extern const unsigned char index_html[];
extern const unsigned char style_css[];
extern const unsigned char settings_html[];
extern const char network_html[];
extern const char bitmap_output_html[];
extern const char bitmap_html[];
extern const char reset_html[];

#endif
/****************************************************************************/
/* Local Defines */
/****************************************************************************/
#define APPL_HTTP_UPLOAD_SIZE_MAX  15000        /**< byte */
#define APPL_HTTP_INDEX_POST        "/indexpost"
#define APPL_HTTP_INDEX_RESTART     "/indexrestart"
#define APPL_HTTP_SETTINGS_POST     "/settingspost"
#define APPL_HTTP_NETWORK_POST      "/netpost"
#define APPL_HTTP_URL_UPDATE_ENABLE  "/api/updateEnable"
#define APPL_HTTP_URL_UPDATE_DISABLE "/api/updateDisable"
#define APPL_HTTP_URL_MAN_ENABLE     "/api/manEnable"
#define APPL_HTTP_URL_MAN_DISABLE    "/api/manDisable"
#define APPL_HTTP_URL_DEVICE_IPGET   "/api/ipget"
#define APPL_HTTP_URL_DEVICE_IPSET   "/api/ipset"


#define MAIN_APPL_IP            GOAL_NET_IPV4(192, 168, 1, 45)
#define MAIN_APPL_NM            GOAL_NET_IPV4(255, 255, 255, 0)
#define MAIN_APPL_GW            GOAL_NET_IPV4(0, 0, 0, 0)



/****************************************************************************/
/* Local Prototypes */
/****************************************************************************/
static GOAL_STATUS_T appl_httpDataCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

static GOAL_STATUS_T appl_httpDataCbPost(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

typedef struct {
	uint32_t units;
	uint32_t minFlow;
	uint32_t flowOkay;
	uint32_t leakRate;
	uint32_t venturiTimer;
	uint32_t underTemp;
	uint32_t overTemp;
	uint32_t web_respTime;
	uint32_t restartDelay;
	uint32_t serialNumber;
} WEB_SETPOINTS;


typedef struct {
	uint32_t ip_addr;
	uint32_t subnet;
} NETWORK_SETTINGS;

typedef struct {
	uint32_t flowFromGun;
	uint32_t gunTemp;
	uint32_t flowToGun;
	uint8_t statusByte;
	union {
		uint8_t byte;
		struct {
			uint8_t reset : 1;
            uint8_t shutoff : 1;
			uint8_t bypass : 1;
			uint8_t reserved: 5;
		};
	} cmdByte;
} WEB_DATA;

typedef struct {
	WEB_SETPOINTS ws;
	NETWORK_SETTINGS ns;
	WEB_DATA wd;
} WEB_STRUCT;

static WEB_STRUCT web_values;


/* Callback function for style page GET request */
static GOAL_STATUS_T styleCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

/* Callback function index page GET request */
static GOAL_STATUS_T indexPageCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);
/* Callback function for index values GET request */
static GOAL_STATUS_T indexJsonCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

static GOAL_STATUS_T appl_httpDataCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);


/* Callback function settings page GET request */
static GOAL_STATUS_T settingsPageCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);
/* Callback function for settings json GET request */
static GOAL_STATUS_T settingsJsonCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

static GOAL_STATUS_T httpPostDataCb(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
);

extern void clear_wdt(void);

typedef enum {
	JS_UNSIGNED_INT = 0,
	JS_INT,
	JS_STRING,
	JS_FLOAT
} JSON_DATA_TYPE;

typedef struct {
	char *name;
	void * value;
	JSON_DATA_TYPE type;
} JSON_DATA;

/****************************************************************************/
/* Local Variables */
/****************************************************************************/
static GOAL_HTTP_HDL_T hdlIdxHtml;              /**< handle of index html page */
static GOAL_HTTP_HDL_T hdlDevHtml;              /**< handle of device html page */
static GOAL_HTTP_HDL_T hdlIndexUpdate;          /**< handle of device api  */
static GOAL_HTTP_HDL_T hdlIndexRestart;
static GOAL_HTTP_HDL_T hdlNetUpdate;
static GOAL_HTTP_HDL_T hdlStyle;
static GOAL_HTTP_HDL_T hdlSettingsPost;

/**< handle of device api  */
static GOAL_HTTP_HDL_T hdlIdxPostHtml;

static GOAL_HTTP_HDL_T hdlNetworkHtml;
static GOAL_HTTP_HDL_T hdlSettingsHtml;
static GOAL_HTTP_HDL_T hdlBitmapHtml;
static GOAL_HTTP_HDL_T hdlBitmapOutputHtml;
static GOAL_HTTP_HDL_T hdlResetHtml;

static GOAL_HTTP_HDL_T hdlNetworkJson;
static GOAL_HTTP_HDL_T hdlSettingsJson;
static GOAL_HTTP_HDL_T hdlJsonIndexSend;                /**< handle of index json style file */

static GOAL_MA_NET_T *pMaNet;                   /**< net ma handle */
static  uint32_t ipAddr;                        /**< ip address */
static  uint32_t netmask;                       /**< netmask */
static  uint32_t gateway;                       /**< gateway */
static  GOAL_BOOL_T dhcpEnable;                 /**< dhcp enable flag */

static char web_resp[512];

uint32_t appl_buildJsonData(JSON_DATA *jd, uint32_t count, char *json_buff) {
	uint32_t len = 0;
	uint32_t i = 0;

	len += sprintf(json_buff, "[{");
	while(count--) {
		len += sprintf(&json_buff[len], "\"%s\" : ", jd[i].name);
		switch (jd[i].type) {
		case JS_INT:
			len += sprintf(&json_buff[len], "\"%d\",", *((int *)jd[i].value));
			break;

		case JS_UNSIGNED_INT:
			len += sprintf(&json_buff[len], "\"%u\",", *((unsigned int *)jd[i].value));
			break;

		case JS_STRING:
			len += sprintf(&json_buff[len], "\"%s\",", (char *) jd[i].value);
			break;

		case JS_FLOAT:
			len += sprintf(&json_buff[len], "\"%.2f\",", *((float *) jd[i].value));
			break;

		default:
			len += sprintf(&json_buff[len], "\"%d\",", *((int *) jd[i].value));
			break;
		}
		i++;
	}
	len = len - 1; // last comma is omitted
	len += sprintf(&json_buff[len], "}]");

	return len;
}

/****************************************************************************/
/**
 * This function converts an IP string to integer value
 *
 */
static uint32_t stringToIpValue(
    char *strIp                                 /**< ip string */
)
{
    char chrValue;                              /* single character */
    unsigned int resValue;                      /* calculated result */
    int val;                                    /* intermediate value */
    int cntChar;                                /* iterator for character */
    int cntValue;                               /* interator for values */

    chrValue = *strIp;
    resValue = 0;

    for (cntValue = 0; cntValue < 4; cntValue++) {

        if (!isdigit(chrValue)) {
            return 0;
        }

        val = 0;
        for (cntChar = 0; cntChar < 3; cntChar++) {
            if (isdigit(chrValue)) {
                val = (val * 10) + (chrValue - '0');
                strIp = strIp + 1;
                chrValue = *strIp;
            } else {
                break;
            }
        }

        if (val < 0 || val > 255) {
            return 0;
        }

        if (chrValue == '.') {
            resValue = (resValue << 8) | val;
            strIp = strIp + 1;
            chrValue = *strIp;
        }
        else if (cntValue == 3 && chrValue == '\0') {
            resValue = ((resValue << 8) | val);
            break;
        }
    }

    if (chrValue != '\0') {
        return 0;
    }

    return resValue;
}

/****************************************************************************/
/** Application Setup
 *
 * Setup the application.
 */
GOAL_STATUS_T appl_httpSetup(
    void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */
    GOAL_HTTP_T *pHttpHdl = NULL;               /* http handle */
    uint32_t ip;                                /* IP address */
    uint32_t nm;                                /* netmask */
    uint32_t gw;  
    
    goal_logInfo("setup web server");

    /* setup new http instance */
    res = goal_httpNew(&pHttpHdl, 80, 8);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to setup HTTP instance");
    }

    // Register callback function for index.html
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/index.html",
                              GOAL_HTTP_METHOD_ALLW_GET | GOAL_HTTP_METHOD_ALLW_POST,
                              appl_httpDataCb, NULL, &hdlIdxHtml);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) APPL_HTTP_INDEX_POST,
                              GOAL_HTTP_METHOD_ALLW_POST,
                              appl_httpDataCbPost, NULL, &hdlIndexUpdate);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) APPL_HTTP_SETTINGS_POST,
                              GOAL_HTTP_METHOD_ALLW_POST,
                              appl_httpDataCbPost, NULL, &hdlSettingsPost);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) APPL_HTTP_INDEX_RESTART,
                              GOAL_HTTP_METHOD_ALLW_POST,
                              appl_httpDataCbPost, NULL, &hdlIndexRestart);
    }   
    
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) APPL_HTTP_NETWORK_POST,
                              GOAL_HTTP_METHOD_ALLW_POST,
                              appl_httpDataCbPost, NULL, &hdlNetUpdate);
    }   
    
    clear_wdt();
    // Register callback function for style.css
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/style.css",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlStyle);
    }
    clear_wdt();
    // Register callback function for values.json
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/values.json",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlJsonIndexSend);
    }
    clear_wdt();
    // Register callback function for settings.html
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/settings.html",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlSettingsHtml);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/settings.json",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlSettingsJson);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/network.html",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlNetworkHtml);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/network.json",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlNetworkJson);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/bitmap.html",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlBitmapHtml);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/bitmap_output.html",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlBitmapOutputHtml);
    }
    clear_wdt();
    if (GOAL_RES_OK(res)) {
        res = goal_httpResReg(pHttpHdl, (uint8_t *) "/reset.html",
                              GOAL_HTTP_METHOD_ALLW_GET,
                              appl_httpDataCb, NULL, &hdlResetHtml);
    }
    
    /* prepare net ma for IP configuration */
    res = goal_maNetOpen(GOAL_NET_ID_DEFAULT, &pMaNet);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("error opening network MA");
    }

    /* set IP address */
    ip = MAIN_APPL_IP;
    nm = MAIN_APPL_NM;
    gw = MAIN_APPL_GW;
    res = goal_maNetIpSet(pMaNet, ip, nm, gw, GOAL_FALSE);

    if (GOAL_RES_OK(res)) {
        goal_logInfo("web server setup done");
    }
    else {
        goal_logInfo("web server setup failed");
    }

    return res;
}

static void appl_handleIndexJson(GOAL_HTTP_APPLCB_DATA_T *pCbInfo) {
    JSON_DATA jdat[4];
    static uint32_t flow = 12, temp = 71, status = 0, flowg = 12;
    
    status = (((uint8_t)web_values.wd.cmdByte.bypass << 2) |
             ((uint8_t)web_values.wd.cmdByte.shutoff << 1));
    
    /* Test supply flow and return flow data */
    flow++;
    flowg++;
    
    if (flow > 100) {
        flow = 5;
    } 
    
    if (flowg > 100) {
        flowg = 5;
    }
            
    jdat[0].name = "flowFromGun";
    jdat[0].value = &flow;
    jdat[0].type = JS_UNSIGNED_INT;

    jdat[1].name  = "gunTemp";
    jdat[1].value = &temp;
    jdat[1].type = JS_UNSIGNED_INT;

    jdat[2].name = "statusByte";
    jdat[2].value = &status;
    jdat[2].type = JS_UNSIGNED_INT;

    jdat[3].name = "flowToGun";
    jdat[3].value = &flowg;
    jdat[3].type = JS_UNSIGNED_INT;

    appl_buildJsonData(jdat, 4, &web_resp[0]);
    GOAL_HTTP_GET_RETURN_JSON(pCbInfo, web_resp, strlen(web_resp));   
}

static void appl_handleSettingsJson(GOAL_HTTP_APPLCB_DATA_T *pCbInfo) {
    int i = 0;
    JSON_DATA jdat[10];

    
    jdat[0].name = "minFlow"; jdat[0].value = &web_values.ws.minFlow;
    jdat[1].name = "flowOk";  jdat[1].value = &web_values.ws.flowOkay;
    jdat[2].name = "leakRate"; jdat[2].value = &web_values.ws.leakRate;
    jdat[3].name = "venturiTimer"; jdat[3].value = &web_values.ws.venturiTimer;
    jdat[4].name = "overTemp"; jdat[4].value = &web_values.ws.overTemp;
    jdat[5].name = "underTemp"; jdat[5].value = &web_values.ws.underTemp;
    jdat[6].name = "responseTime"; jdat[6].value = &web_values.ws.web_respTime;
    jdat[7].name = "restartDelay"; jdat[7].value = &web_values.ws.restartDelay;
    jdat[8].name = "units"; jdat[8].value = &web_values.ws.units;
    jdat[9].name = "serialNumber"; jdat[9].value = &web_values.ws.serialNumber;

    for (i = 0; i < 10; i++) jdat[i].type = JS_UNSIGNED_INT;

    appl_buildJsonData(jdat, 10, &web_resp[0]);

    GOAL_HTTP_GET_RETURN_JSON(pCbInfo, web_resp, strlen(web_resp));    
}

/* Build json data for  network settings */
static void appl_handleNetworkJson(GOAL_HTTP_APPLCB_DATA_T *pCbInfo) {
    uint32_t json_len = 0;
    
    json_len += sprintf(&web_resp[json_len], "[{\"%s\" : \"%s\",", "ip", "192.168.1.45");
	json_len += sprintf(&web_resp[json_len], "\"%s\" : \"%s\",", "subnet", "255.255.255.0");
	json_len += sprintf(&web_resp[json_len], "\"%s\" : \"%s\"}]", "macaddr", "85:89:89:47:AA:15");
    
    GOAL_HTTP_GET_RETURN_JSON(pCbInfo, web_resp, strlen(web_resp));
}

// Parse JSON Data 
uint32_t appl_webParseJsonData(char *ptr, const char *id, char *data) {
	uint32_t len = 0;
    char *ret = 0;
    
    if (!ptr) {
        return 0;
    } 
    
	ret = strstr(ptr, id);

	if (ret) {
		char *ptr = strchr(ret, ':');

		if (ptr) {
			while(*ptr != '"') {
				ptr++;
			}
			// Quotation mark start point found
			ptr++;
			while(*ptr != '"') {
				data[len++] = *ptr;
				ptr++;
			}
			data[len] = 0;
		}

	}
	return len;
}

static GOAL_STATUS_T appl_handleNetworkPost(char *data, uint32_t len) {
    GOAL_STATUS_T ret = GOAL_ERROR;
    char web_net[15];
    
    if (len == 0) {
        return ret;
    }
    /* Extract IP address and subnet */
    if (appl_webParseJsonData(data, "ip", web_net)) {
        web_values.ns.ip_addr = stringToIpValue(web_net);
        if (web_values.ns.ip_addr != 0) {
            ret = GOAL_OK;
        }
    }
    
    if (appl_webParseJsonData(data, "subnet", web_net)) {
        web_values.ns.subnet = stringToIpValue(web_net);
        if (web_values.ns.subnet != 0) {
            ret = GOAL_OK;
        }
    }
    
    return ret;
}

static GOAL_STATUS_T appl_handleSettingsHtmlPost(char *data, uint32_t len) {
    GOAL_STATUS_T ret = GOAL_ERROR;
    char data_ptr[4];
    char *endptr;  
    
    if (len == 0) {
        return ret;
    }
    
    if (appl_webParseJsonData(data, "minFlow", data_ptr)) {
        web_values.ws.minFlow = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.minFlow += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "flowOk", data_ptr)) {
        web_values.ws.flowOkay = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.flowOkay += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "leakRate", data_ptr)) {
        web_values.ws.leakRate = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.leakRate += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "venturiTimer", data_ptr)) {
        web_values.ws.venturiTimer = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.venturiTimer += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "overTemp", data_ptr)) {
        web_values.ws.overTemp = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.overTemp += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "underTemp", data_ptr)) {
        web_values.ws.underTemp = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.underTemp += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "responseTime", data_ptr)) {
        web_values.ws.web_respTime = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.web_respTime += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "restartDelay", data_ptr)) {
        web_values.ws.restartDelay = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.restartDelay += 10;
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "units", data_ptr)) {
        web_values.ws.units = (uint8_t) strtod((const char *)data_ptr, &endptr);
        web_values.ws.units += 10;
        ret = GOAL_OK;
    }
    
    return ret;
}

static GOAL_STATUS_T appl_handleIndexHtmlPost(char *data, uint32_t len) {
    char data_ptr[4];
    char *endptr;   
    GOAL_STATUS_T ret = GOAL_ERROR;
    
    if (len == 0) {
        return ret;
    }
    
    if (appl_webParseJsonData(data, "bypass", data_ptr)) {
        web_values.wd.cmdByte.bypass = (uint8_t) strtod((const char *)data_ptr, &endptr);
        ret = GOAL_OK;
    }
    
    if (appl_webParseJsonData(data, "valve", data_ptr)) {
        web_values.wd.cmdByte.shutoff = (uint8_t) strtod((const char *)data_ptr, &endptr);
        ret = GOAL_OK;
    }
    
    return ret;
}

/* Handle webpage "GET" command */

static GOAL_STATUS_T appl_httpDataCb (
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
)
{
    if (hdlIdxHtml == pCbInfo->hdlRes) {
        if (pCbInfo->reqType == GOAL_HTTP_FW_GET) {
            GOAL_HTTP_GET_RETURN_HTML(pCbInfo, index_html, strlen(index_html)); 
        }       
    } else if (hdlStyle == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_CSS(pCbInfo, style_css, strlen(style_css));
    } else if (hdlJsonIndexSend == pCbInfo->hdlRes) {
        appl_handleIndexJson(pCbInfo);
    } else if (hdlSettingsHtml == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_HTML(pCbInfo, settings_html, strlen(settings_html));
    } else if (hdlSettingsJson == pCbInfo->hdlRes) {
        appl_handleSettingsJson(pCbInfo);
    } else if (hdlNetworkHtml == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_HTML(pCbInfo, network_html, strlen(network_html));
    } else if (hdlNetworkJson == pCbInfo->hdlRes) {
        appl_handleNetworkJson(pCbInfo);
    } else if (hdlBitmapHtml == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_HTML(pCbInfo, bitmap_html, strlen(bitmap_html));
    } else if (hdlBitmapOutputHtml == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_HTML(pCbInfo, bitmap_output_html, strlen(bitmap_output_html));
    } else if (hdlResetHtml == pCbInfo->hdlRes) {
        GOAL_HTTP_GET_RETURN_HTML(pCbInfo, reset_html, strlen(reset_html));
    } 

    return GOAL_OK;
}

/* Handle HTTP "POST" data in form of JSON string */
static GOAL_STATUS_T appl_httpDataCbPost(
    GOAL_HTTP_APPLCB_DATA_T *pCbInfo            /**< pointer to callback info struct */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* result */

    // Index page post
    if (hdlIndexUpdate == pCbInfo->hdlRes) { 
        if (pCbInfo->reqType == GOAL_HTTP_FW_POST_DATA) {
            if (appl_handleIndexHtmlPost((char *)pCbInfo->cs.pData, pCbInfo->cs.lenData) == GOAL_OK) {               
                GOAL_HTTP_RETURN_OK_204(pCbInfo);
            }
        } else {
            GOAL_HTTP_RETURN_OK_204(pCbInfo);
        }
    } 
    // Index Page Restart
    else if (hdlIndexRestart == pCbInfo->hdlRes) {
        if (pCbInfo->reqType == GOAL_HTTP_FW_POST_DATA) {
            web_values.wd.cmdByte.reset = 1;
        }
        GOAL_HTTP_RETURN_OK_204(pCbInfo);
    }
    // Settings Page Post
    else if (hdlSettingsPost == pCbInfo->hdlRes) {
        if (pCbInfo->reqType == GOAL_HTTP_FW_POST_DATA) {
            if (appl_handleSettingsHtmlPost((char *)pCbInfo->cs.pData, pCbInfo->cs.lenData) == GOAL_OK) {               
                GOAL_HTTP_RETURN_OK_204(pCbInfo);
            }
        }
        GOAL_HTTP_RETURN_OK_204(pCbInfo);
    }
    // Network Page Post
    else if (hdlNetUpdate == pCbInfo->hdlRes) {
        if (pCbInfo->reqType == GOAL_HTTP_FW_POST_DATA) {
            if (appl_handleNetworkPost((char *)pCbInfo->cs.pData, pCbInfo->cs.lenData) == GOAL_OK) {               
                GOAL_HTTP_RETURN_OK_204(pCbInfo);
            }
        }
        GOAL_HTTP_RETURN_OK_204(pCbInfo);
    }
    return res;
}

void goal_setWebData(unsigned char *data, unsigned char len) {
    web_values.wd.statusByte = data[0];
    web_values.wd.flowToGun = data[1];
    web_values.wd.flowFromGun = data[2];
    web_values.wd.gunTemp = data[3];
}

unsigned char goal_setWebCmd() {
    uint8_t ret = web_values.wd.cmdByte.byte;
    web_values.wd.cmdByte.reset = 0;
    return ret;
}