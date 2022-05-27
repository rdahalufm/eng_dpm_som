/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** anybus.h
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Public interfaces for an minimalistic Anybus-CC application example.
**
** ABCC Lite Driver - Serial version
**
********************************************************************************
********************************************************************************
**                                                                            **
** User Information 2012 HMS Industrial Networks AB.                          **
**                                                                            **
** This program is the property of HMS Industrial Networks AB.                **
** It has been designed to be used and modified without permission from       **
** HMS Industrial Networks AB in any application using an Anybus CompactCom   **
** module.                                                                    **
** We, HMS Industrial Networks AB, reserve the right to modify our products   **
** in line with our policy of continuous product development. The information **
** in this program is subject to updates without notice and should not be     **
** considered as a commitment by HMS Industrial Networks AB.                  **
** HMS Industrial Networks AB assumes no responsibility for any errors that   **
** may appear in this program.                                                **
**                                                                            **
********************************************************************************
********************************************************************************
**
** Company: HMS Industrial Networks AB
**          Stationsgatan 37
**          SE-302 45  Halmstad
**          SWEDEN
**          Tel:     +46 (0)35 - 17 29 00
**          Fax:     +46 (0)35 - 17 29 09
**          e-mail:  info@hms.se
**
********************************************************************************
********************************************************************************
*/

/*******************************************************************************
********************************************************************************
**
** Change Log
** ----------
**
** Latest modification:
** --------------------
** $Modtime: 2007-12-14 10:31:09+01:00 $
**
** Version history:
**
**    Ver 1.00     2007-12-14  TiB   First release
**    Ver 2.00     2012-01-29  MSv   V2 driver updates
**
********************************************************************************
********************************************************************************
*/

#ifndef ANYBUS_H
#define ANYBUS_H


/*------------------------------------------------------------------------------
** Global ABCC dirver configuration defines
**
** USE_DIPSWITCHES      - Use DIP switches msg set functions in anybus.c
** LITTLE_ENDIAN        - If defined little endian swap orders are used
** BIG_ENDIAN           - If defines gig-endian swap orders are used
** AB_MAX_PD_WRITE_SIZE - Should be setup to the maximum 
** 
**------------------------------------------------------------------------------
*/

/*#define USE_DIPSWITCHES*/
/*#define AB_ENABLE_64BIT_ADI_SUPPORT*/
#define LITTLE_ENDIAN
//#define BIG_ENDIAN
#define AB_MAX_PD_WRITE_SIZE     216


/*------------------------------------------------------------------------------
** ABCC Host object includes
** If the specific define is specififed that object will be included in the
** host object routing model.
**
** AB_HOST_APPLICATION_OBJECT_0xFF  - Application object (0xFF) (app_obj.c)
** AB_HOST_BACNET_OBJECT_0xEF       - BACnet host object (0xEF) (bac_obj.c)
** 
**------------------------------------------------------------------------------
*/

#define AB_HOST_APPLICATION_OBJECT_0xFF
//#define AB_HOST_BACNET_OBJECT_0xEF
#define AB_HOST_PNIO_OBJECT_0xF6
//#define AB_HOST_EIP_OBJECT_0xF8
#define AB_ETHERNET_HOST_OBJECT_0xF9

/*******************************************************************************
**
** Compiler dependent general purpose definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** FALSE
** TRUE
**
** These are the symbolic constants for true and false used in boolean
** data type comparisons.
**
**------------------------------------------------------------------------------
*/

#ifndef FALSE
   #define FALSE     0
#endif

#ifndef TRUE
   #define TRUE      ( !FALSE )
#endif


/*------------------------------------------------------------------------------
**
** BOOL8
**
** SINT8
** SINT16
** SINT32
**
** UINT8
** UINT16
** UINT32
**
** FLOAT32
**
** The standard boolean data type, 8-bit.
** The standard signed 8, 16, 32 and 64 bit data types (respectively).
** The standard unsigned 8, 16, 32 and 64 bit data types (respectively).
**
** PORTING ALERT!
** Make sure that the defined data types match your host system.
**
**------------------------------------------------------------------------------
*/

typedef unsigned char   BOOL8;
typedef signed char     SINT8;
typedef signed short    SINT16;
typedef signed long     SINT32;

typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;
typedef float           FLOAT32;

//typedef unsigned __int64 UINT64;
//typedef signed __int64   SINT64;


/*------------------------------------------------------------------------------
**
** NULL
**
** Default value for invalid pointers.
**
**------------------------------------------------------------------------------
*/

#ifndef NULL
   #define NULL 0
#endif


/*------------------------------------------------------------------------------
**
** Define for struct
** Compiler independent symbols to pack structures for compilers that
** need an in-line directive.
**
** PORTING ALERT!
**
**------------------------------------------------------------------------------
*/

#define  start_packet_struct     struct
#define  end_packet_struct


/*------------------------------------------------------------------------------
**
** CPLUSPLUS
** EXTFUNC
**
** C/C++ Compatibility Macros (for C++ compatibility)
**
**------------------------------------------------------------------------------
*/

#ifdef __cplusplus
   #define CPLUSPLUS
#endif


#ifdef CPLUSPLUS
   #define EXTFUNC extern "C"
#else
   #define EXTFUNC extern
#endif


/*******************************************************************************
**
** Type Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
** State variable that keeps track of which initialization command to send next
** It is also used as a "source ID" to simplify the identification of responses
** from the Anybus-CC.
**------------------------------------------------------------------------------
*/

typedef enum CmdStateType
{
#ifdef USE_DIPSWITCHES
   MSG_NODE_ADR,
   MSG_BAUDRATE,
#endif

   MSG_DATA_FORMAT,
   MSG_GET_MODULE_ID,
   MSG_GET_NETWORK_ID,
   MSG_AD_USER_INIT,
   MSG_MAP_IO_WRITE,
   MSG_MAP_IO_READ,
   MSG_SETUP_COMPLETE,
   MSG_DONE,
//start custom commands
   MSG_SET_IPADD,
   MSG_GET_IPADD,
   MSG_SET_SMASK,
   MSG_GET_SMASK,
   MSG_GET_MACADD,
   MSG_SET_ECS1,
   MSG_SET_ECS2,
   MSG_SET_STATIC
//end custom commands
}CmdStateType;


/*------------------------------------------------------------------------------
** Used for storing the data format of the fieldbus
** NET_UNKNOWN means that the Anybus-CC has not yet responded to our command to
** read the fieldbus data format.
**------------------------------------------------------------------------------
*/

typedef enum NetFormatType
{
   NET_LITTLEENDIAN,
   NET_BIGENDIAN,
   NET_UNKNOWN
}NetFormatType;


/*------------------------------------------------------------------------------
** AB_UserMsgReqType
** User request context to be used with AB_ScheduleUserMsgRequest.
** 
** psNext    - Pointer used for internal request queue
** bMsgState - AB_MSG_STATE_GET_REQUEST      - Request should me added to psMsgBuffer
**             AB_MSG_STATE_SUCCESS_RESPONSE - Success response is availible in psMsgBuffer
**             AB_MSG_STATE_ERROR_RESPONSE   - Error response is availible in psMsgBuffer
**             AB_MSG_STATE_ABORT            - Internal abort of request
**------------------------------------------------------------------------------
*/

struct AB_UserMsgReqType;
struct ABP_MsgType;
typedef BOOL8 (* AB_pnMsgReqCallback)( struct AB_UserMsgReqType* psMsgReq, UINT8 bMsgState, struct ABP_MsgType* psMsgBuffer );

typedef struct AB_UserMsgReqType
{
   struct AB_UserMsgReqType*  psNext;
   UINT8                      bUserHandle;
   AB_pnMsgReqCallback        pnMsgReqCallback;
} AB_UserMsgReqType;


/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** bSw1, bSw2
**
** bSw1 and bSW2 represent two DIP-switches (or similar) which are used to set
** the fieldbus node adress and baudrate of the Anybus-CC.
**
**------------------------------------------------------------------------------
*/

extern UINT8   bSw1;
extern UINT8   bSw2;


/*------------------------------------------------------------------------------
**
** bControlReg, bStatusReg
**
** Working copies of the status and control registers
**
**------------------------------------------------------------------------------
*/

extern UINT8   bControlReg;
extern UINT8   bStatusReg;


/*------------------------------------------------------------------------------
**
** eCmdState
**
** State variable that keeps track of which initialization command to send next
**
**------------------------------------------------------------------------------
*/

extern CmdStateType   eCmdState;


/*------------------------------------------------------------------------------
**
** bOutstandingCmds
**
** This variable keeps track of if there are any commands which we have not yet 
** received a response to.
**
**------------------------------------------------------------------------------
*/

extern UINT8 bOutstandingCmds;


/*------------------------------------------------------------------------------
**
** eNetFormat
**
** This variable is used to indicate the network data format.
** Little endian or big endian.
**
**------------------------------------------------------------------------------
*/

extern NetFormatType eNetFormat;


/*------------------------------------------------------------------------------
** AB_iModuleType    - ABCC module type (read out during SETUP state)
** AB_iNetworkType   - ABCC network type (read out during SETUP state)
** AB_bPdReadSize    - Read process data size, setup by ab_obj.c during setup based on selected read mappings, see ad.obj.c
** AB_bPdWriteSize   - Write process data size, setup by ab_obj.c during setup based on selected write mappings, see ad_obj.c
** AB_bNextSrcId     - Next source ID of ABCC messages sent from (Application -> Anybus)
** AB_fStatSupBit    - TRUE: Supervised bit in ABCC status word is set
** AB_fReInitDriver  - If set to TRUE during AnybusMain() loop execution the kernel will re-initilize to SETUP state
**------------------------------------------------------------------------------
*/

extern UINT16   AB_iModuleType;
extern UINT16   AB_iNetworkType;
extern UINT8    AB_bPdReadSize;
extern UINT8    AB_bPdWriteSize;
extern UINT8    AB_bNextSrcId;
extern BOOL8    AB_fStatSupBit;
extern BOOL8    AB_fReInitDriver;


/*******************************************************************************
**
** Public Services Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** AnybusMain()
**
** Handles communicaton with the Anybus-CC
** This function should be called cyclically
**
**------------------------------------------------------------------------------
**
** Inputs:
**          pbRxData    - Pointer to received data, NULL if a timeout has occured.
**
** Outputs:
**          Returns     - Pointer to data to send.
**          piTxSize    - Number of bytes to send.
**          piRxSize    - Number of bytes to receive
**
** Usage:
**          pTxData = AnybusMain( abRxData, &iTxSize, &iRxSize );
**
**------------------------------------------------------------------------------
*/

EXTFUNC UINT8* AnybusMain( UINT8* pbRxData, UINT16* piTxSize, UINT16* piRxSize );


/*******************************************************************************
**
** Private Services Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** ProcAppObjectRequest()
**
** A request has been received to an object mamaged by the application.
** In this function call the user should switch on the supported application
** object and route the ABCC request to the appropriate object msg handler.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    None
**
** Outputs:
**    None
**
** Usage:
**    ProcAppObjectRequest();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void ProcAppObjectRequest( void );


/*------------------------------------------------------------------------------
**
** ResetAnybus()
**
** Should perform an hardware reset of the Anybus ABCC card
**
** PORTING ALERT!!!
** Make macro perform an reset of the Anybus card.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    None        - Works on the global driver buffers
**
** Outputs:
**    None        - Works on the global driver buffers
**
** Usage:
**    ResetAnybus();
**
**------------------------------------------------------------------------------
*/

#define ResetAnybus() {extern void dpm_reset_abcc(void);dpm_reset_abcc();}


/*------------------------------------------------------------------------------
**
** ScheduleUserMsgRequest()
**
** Schedule an msg request to the anybus driver
** When the driver is ready to get the request is executes the provided
** callback function with the appropriate AB_MSG_STATE_XXX enum.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    psUserMsgReq   - User provided context of AB_UserMsgReqType
**    pnUserCallback - Callback function to be used by driver calls.
**
** Outputs:
**    BOOL8          - TRUE: Msg request was scheduled.
**                     FALSE: Msg request NOT scheduled. 
**
** Usage:
**    ScheduleUserMsgRequest( &sUserMsg, UserMsgCallbackFunc );
**
**------------------------------------------------------------------------------
*/

EXTFUNC BOOL8 ScheduleUserMsgRequest( AB_UserMsgReqType* psUserMsgReq, AB_pnMsgReqCallback pnUserCallback );


/*------------------------------------------------------------------------------
**
** iBeTOi()
** iTOiBe()
** iLeTOi()
** iTOiLe()
**
** Transforms a big/little endian integer into a native format integer and
** a native format integer to big/little endian integer.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    xBeFoo                  - a big endian integer to be transformed
**    xLeFoo                  - a little endian integer to be transformed
**    xFoo                    - a native format integer to be transformed
**
** Outputs:
**    xFoo                    - a native format integer
**    xBeFoo                  - a big endian integer
**    xLeFoo                  - a little endian integer
**
**
** Usage:
**    xFoo   = xBeTOx( xBeFoo );
**    xBeFoo = xTOxBe( xFoo );
**    xFoo   = xLeTOx( xLeFoo );
**    xLeFoo = xTOxLe( xFoo );
**
**------------------------------------------------------------------------------
*/

#ifdef BIG_ENDIAN
   #define iBeTOi( iBeFoo )    (UINT16)(iBeFoo)
   #define iTOiBe( iFoo )      (UINT16)(iFoo)
   #define iLeTOi( iLeFoo )    (UINT16)( ( (UINT16)(iLeFoo) >> 8 ) | ( (iLeFoo) << 8 ) )
   #define iTOiLe( iFoo )      (UINT16)( ( (UINT16)(iFoo) >> 8 ) | ( (iFoo) << 8 ) )

   #define lBeTOl( lBeFoo )    (UINT32)(lBeFoo)
   #define lTOlBe( lFoo )      (UINT32)(lFoo)
   #define lLeTOl( lLeFoo )    (UINT32)( ( ( ( (UINT32)(lLeFoo & 0x0000FFFFL) >> 8 ) | ( (lLeFoo & 0x0000FFFFL ) << 8 ) ) << 16L ) | ( ( ( (UINT32)(lLeFoo & 0xFFFF0000L) >> 8 ) | ( (lLeFoo & 0xFFFF0000L ) << 8 ) ) >> 16 ) )
   #define lTOlLe( lFoo )      (UINT32)( ( ( ( (UINT32)(lFoo & 0x0000FFFFL) >> 8 ) | ( (lFoo & 0x0000FFFFL ) << 8 ) ) << 16L ) | ( ( ( (UINT32)(lFoo & 0xFFFF0000L) >> 8 ) | ( (lFoo & 0xFFFF0000L ) << 8 ) ) >> 16 ) )

   #define lBeTOl64( lBeFoo )  (UINT64)(lBeFoo)
   #define lTOlBe64( lFoo )    (UINT64)(lFoo)
   #define lLeTOl64( lLeFoo )  (UINT64)( ( (UINT64)lLeTOl( (UINT32)( lLeFoo & 0x00000000FFFFFFFFL ) ) << 32 ) | (UINT64)lLeTOl( (UINT32)( ( lLeFoo & 0xFFFFFFFF00000000L ) >> 32 )  ) )
   #define lTOlLe64( lFoo )    (UINT64)( ( (UINT64)lTOlLe( (UINT32)( lFoo & 0x00000000FFFFFFFFL ) ) << 32 ) | (UINT64)lTOlLe( (UINT32)( ( lFoo & 0xFFFFFFFF00000000L ) >> 32 )  ) )
#else
   #define iBeTOi( iBeFoo )    (UINT16)( ( (UINT16)(iBeFoo) >> 8 ) | ( (iBeFoo) << 8 ) )
   #define iTOiBe( iFoo )      (UINT16)( ( (UINT16)(iFoo) >> 8 ) | ( (iFoo) << 8 ) )
   #define iLeTOi( iLeFoo )    (UINT16)(iLeFoo)
   #define iTOiLe( iFoo )      (UINT16)(iFoo)

   #define lBeTOl( lBeFoo )    (UINT32)( ( ( ( (UINT32)(lBeFoo & 0x0000FFFFL) >> 8 ) | ( (lBeFoo & 0x0000FFFFL ) << 8 ) ) << 16L ) | ( ( ( (UINT32)(lBeFoo & 0xFFFF0000L) >> 8 ) | ( (lBeFoo & 0xFFFF0000L ) << 8 ) ) >> 16 ) )
   #define lTOlBe( lFoo )      (UINT32)( ( ( ( (UINT32)(lFoo & 0x0000FFFFL) >> 8 ) | ( (lFoo & 0x0000FFFFL ) << 8 ) ) << 16L ) | ( ( ( (UINT32)(lFoo & 0xFFFF0000L) >> 8 ) | ( (lFoo & 0xFFFF0000L ) << 8 ) ) >> 16 ) )
   #define lLeTOl( lLeFoo )    (UINT32)(lLeFoo)
   #define lTOlLe( lFoo )      (UINT32)(lFoo)

   #define lBeTOl64( lBeFoo )  (UINT64)( ( (UINT64)lBeTOl( (UINT32)( lBeFoo & 0x00000000FFFFFFFFL ) ) << 32 ) | (UINT64)lBeTOl( (UINT32)( ( lBeFoo & 0xFFFFFFFF00000000L ) >> 32 )  ) )
   #define lTOlBe64( lFoo )    (UINT64)( ( (UINT64)lTOlBe( (UINT32)( lFoo & 0x00000000FFFFFFFFL ) ) << 32 ) | (UINT64)lTOlBe( (UINT32)( ( lFoo & 0xFFFFFFFF00000000L ) >> 32 )  ) )
   #define lLeTOl64( lLeFoo )  (UINT64)(lLeFoo)
   #define lTOlLe64( lFoo )    (UINT64)(lFoo)
#endif


/*------------------------------------------------------------------------------
**
** SetMsgError()
**
** Sets the E-bit and enters the submitted error code.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    psMsg                - Pointer to the message command to convert.
**    bMsgDataSize         - The number of valid message data field bytes.
**    eErr                 - The requested error code (ABP_MsgErrorCodeType).
**
** Outputs:
**    None
**
** Usage:
**    SetMsgError( psMsg, bMsgDataSize, bErr );
**
**------------------------------------------------------------------------------
*/

#define SetMsgError( psMsg, bMsgDataSize, bErr )                           \
{                                                                              \
   (psMsg)->sHeader.bCmd      |=  ABP_MSG_HEADER_E_BIT;                        \
   (psMsg)->sHeader.bDataSize  =  (bMsgDataSize);                              \
   (psMsg)->abData[ 0 ]        =  (UINT8) (bErr);                              \
                                                                               \
} /* end of SetMsgError() */


/***********************************************************************
 * User Application Interface to the Anybus Application layer 
 * These global variables shall be used to access or modified needed ABCC
 * parameters
 * ---------------------------------------------------------------------
 */

extern volatile UINT8 AnybusSetIP,AnybusGetIP,AnybusSetSM,AnybusGetSM,AnybusGetMAC,AnybusSetECS1,AnybusSetECS2,AnybusSetStatic;
extern volatile UINT8 IPAddressLocal[4],SMaskLocal[4],MACAddress[6];


#endif  /* inclusion lock */





/*******************************************************************************
**
** End of anybus.h
**
********************************************************************************
*/
