/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** anybus.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
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
** $Modtime: 2010-06-28 14:24:58+02:00 $
**
** Version history:
**
**    Ver 1.00     2007-12-14  TiB   First release
**    Ver 2.00     2012-01-29  MSv   V2 driver updates
**
********************************************************************************
********************************************************************************
*/

#include "anybus.h"
#include "abp.h"
#include <string.h>


#include "ad_obj.h"     /* Application data object:   0xFE */
#include "app_obj.h"    /* Application object:        0xFF */
#ifdef AB_HOST_BACNET_OBJECT_0xEF
#include "bac_obj.h"    /* BACnet Host object:        0xEF */
#endif
#ifdef AB_HOST_PNIO_OBJECT_0xF6
#include "pnet_obj.h"    /* Profinet IO Host object:  0xF6 */
#endif
#ifdef AB_HOST_EIP_OBJECT_0xF8
#include "eip_obj.h"    /* EthernetIP IO Host object:  0xF8 */
#endif
#ifdef AB_ETHERNET_HOST_OBJECT_0xF9
#include "etn_obj.h"     /* Ethernet IO Host object 0xF9*/
#endif


#define min( x , y )  ( ( x ) < ( y ) ? ( x ) : ( y ) )


/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/

volatile UINT8 AnybusSetIP = 1,AnybusGetIP = 0,AnybusSetSM = 1,AnybusGetSM = 0,AnybusGetMAC = 1,AnybusSetECS1 = 0,AnybusSetECS2 = 0,AnybusSetStatic = 1;
volatile UINT8 IPAddressLocal[4], SMaskLocal[4], MACAddress[6];
/*
** bSw1 and bSw2 represent two DIP-switches (or similar) which are used to set
** the fieldbus node adress and baudrate of the Anybus-CC.
*/

#ifdef USE_DIPSWITCHES
   UINT8                      bSw1;
   UINT8                      bSw2;
#endif

/*
** Working copies of the status and control registers
*/

UINT8                         bControlReg = ABP_CTRL_R_BIT | ABP_CTRL_T_BIT;
UINT8                         bStatusReg  = 0;

/*
** State variable that keeps track of which initialization command to send next
*/

#ifdef USE_DIPSWITCHES
   CmdStateType               eCmdState   = 0;
#else
   CmdStateType               eCmdState   = 0;
#endif
   CmdStateType               eCmdRespState;

/*
** This variable keeps track of if there are any commands which we have not yet
** received a response to.
*/

UINT8 bOutstandingCmds = 0;


/*
** This variable is used to indicate the network data format.
** Little endian or big endian.
*/

NetFormatType                 eNetFormat = NET_UNKNOWN;


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

UINT16   AB_iModuleType;
UINT16   AB_iNetworkType;
UINT8    AB_bPdReadSize    = 0;
UINT8    AB_bPdWriteSize   = 0;
UINT8    AB_bNextSrcId     = 0;
BOOL8    AB_fStatSupBit    = FALSE;
BOOL8    AB_fReInitDriver  = FALSE;


/*******************************************************************************
**
** Private Globals
**
********************************************************************************
*/

/*
** Serial transmission buffer.
** The standard telegram is 19 bytes, AB_MAX_PD_WRITE_SIZE must be setup
** to the maximum process write data length.
*/

UINT8 abTxBuffer[ 19 + AB_MAX_PD_WRITE_SIZE ] = { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*
** Message buffer.
*/

ABP_MsgType sMsgBuffer;
UINT16      iMsgBufferOffset     = 0;
UINT16      iTxMsgBufferOffset   = 0;


/*
** Tables for generating CRC16 checksum
*/

const UINT8 abCrc16Hi[] =
{
   0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
   0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
   0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
   0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
   0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01,
   0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80,
   0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
   0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
   0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
   0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
   0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
   0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
   0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
   0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
   0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
   0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
   0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
   0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
   0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};


const UINT8 abCrc16Lo[] =
{
   0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05,
   0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA,
   0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA,
   0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15,
   0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0,
   0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35,
   0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B,
   0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,
   0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27,
   0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
   0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64,
   0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
   0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE,
   0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7,
   0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
   0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
   0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99,
   0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E,
   0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46,
   0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};


/*******************************************************************************
**
** Public Functions
**
********************************************************************************
*/


/*------------------------------------------------------------------------------
** Crc16()
**------------------------------------------------------------------------------
*/

UINT16 Crc16( UINT8* pbBufferStart, UINT16 iLength )
{
   UINT8   bIndex;
   UINT8   bCrcLo;
   UINT8   bCrcHi;


   /*
   ** Init crc to 0xFFFF
   */

   bCrcLo = 0xFF;
   bCrcHi = 0xFF;

   /*
   ** Do the crc calculation
   */

   while( iLength > 0 )
   {
      bIndex = bCrcLo ^ *pbBufferStart++;
      bCrcLo = bCrcHi ^ abCrc16Hi[ bIndex ];
      bCrcHi = abCrc16Lo[ bIndex ];
      iLength--;
   }

   return( bCrcHi << 8 | bCrcLo );

} /* End of Crc16() */


/*------------------------------------------------------------------------------
** AnybusMain()
**------------------------------------------------------------------------------
*/

UINT8* AnybusMain( UINT8* pbRxData, UINT16* piTxSize, UINT16* piRxSize )
{
   UINT16 iCrc;
#ifdef USE_DIPSWITCHES
   static UINT8 bLastSw1, bLastSw2;
#endif

   if( ( pbRxData == NULL ) ||
       ( AB_fReInitDriver ) )
   {
      /*
      ** This is either the initial call to this function,
      ** a re-initialization request or the retransmission timer has timed out.
      ** Perform a (re)transmission.
      */

      if( AB_fReInitDriver )
      {
         UINT8 b;

         AB_fReInitDriver  = FALSE;
         *piTxSize         = 19;
         *piRxSize         = 19;
         bControlReg       = ABP_CTRL_R_BIT | ABP_CTRL_T_BIT;
         eCmdState         = 0;
         bStatusReg        = 0;
         bOutstandingCmds  = 0;
         iMsgBufferOffset  = 0;
         iTxMsgBufferOffset= 0;
         abTxBuffer[ 0 ]   = 0x80;

         for( b = 1; b < 19; b++ )
         {
            abTxBuffer[ b ] = 0;
         }

         ResetAnybus();
      }

      if( ( bStatusReg & ABP_STAT_S_BITS ) > ABP_ANB_STATE_SETUP )
      {
         /*
         ** Update the "write process data" in the telegram before (re)transmission.
         ** The data format of the process data is network specific.
         ** Convert our data accordingly.
         */

         AD_UpdatePdWriteData( &abTxBuffer[ 17 ] );
      }

      iCrc = Crc16( (UINT8*)abTxBuffer, (UINT16)(*piTxSize - 2) );

      abTxBuffer[ *piTxSize - 2 ] = (UINT8)( ( iCrc >> 8 ) & 0x00FF );
      abTxBuffer[ *piTxSize - 1 ] = (UINT8)( iCrc & 0x00FF );

      return( abTxBuffer );
   }


   iCrc  = (UINT16)pbRxData[ *piRxSize - 2 ] << 8;
   iCrc |= pbRxData[ *piRxSize - 1 ];

   if( iCrc != Crc16( pbRxData, (UINT16)( *piRxSize - 2 ) ) )
   {
      /*
      ** CRC error.
      ** This data must be ignored.
      */

      return( NULL );
   }

   /*
   ** Check if the toggle bit in the status register has toggled.
   */

   if( ( pbRxData[ 0 ] & ABP_STAT_T_BIT ) !=
       ( bControlReg & ABP_CTRL_T_BIT ) )
   {
      /*
      ** Toggle bit has not toggled.
      ** This data must be ignored.
      */

      return( NULL );
   }

   bStatusReg = pbRxData[ 0 ];
   AB_fStatSupBit = ( bStatusReg & ABP_STAT_SUP_BIT ) ? TRUE : FALSE;

   bControlReg ^= ABP_CTRL_T_BIT;

   if( bStatusReg & ABP_STAT_M_BIT )
   {
      /*
      ** There is a message fragment available.
      */

      /*
      ** Clear the Ready bit so that we don't have to handle more than one command at a time.
      */

      bControlReg &= ~ABP_CTRL_R_BIT;

      if( iMsgBufferOffset >= sizeof(ABP_MsgType) )
      {
         /*
         ** Defragmentation error!
         ** This should never occur. There is probably a software bug somewhere.
         ** PORTING ALERT!
         ** Add error handling here.
         */

         while( 1 );
      }
      else
      {
         memcpy( &(((UINT8*)&sMsgBuffer)[ iMsgBufferOffset ] ), &pbRxData[ 1 ], min( 16, sizeof(ABP_MsgType) - iMsgBufferOffset ) );

         iMsgBufferOffset += 16;
      }
   }
   else if( iMsgBufferOffset != 0 )
   {
      /*
      ** A new defragmented message is available.
      */

      iMsgBufferOffset = 0;
      if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_C_BIT )
      {
         /*
         ** The message is a command
         ** Prepare the response.
         */

         sMsgBuffer.sHeader.bCmd &= ~ABP_MSG_HEADER_C_BIT;
         ProcAppObjectRequest();
      }
      else
      {
         /*
         ** The message is a response to a command we have sent.
         */

         bOutstandingCmds--;

         if( bOutstandingCmds == 0 )
         {
            /*
            ** We are not waiting for any repsonses any more.
            ** Set the Ready to allow the ABCC to send a command to us.
            */

            bControlReg |= ABP_CTRL_R_BIT;
         }

         unsigned char temp = ( AB_bNextSrcId - 1u );
           if( sMsgBuffer.sHeader.bSourceId ==temp )
           {

            switch( eCmdRespState )
            {
#ifdef USE_DIPSWITCHES
            case MSG_NODE_ADR:
            case MSG_BAUDRATE:
               /*
               ** It is a response to a command to set one of the DIP-switch values.
               ** This response shall normally be ignored, even if the error bit is set.
               ** (Not all Anybus-CC modules support the use of DIP-switches)
               */

               break;
#endif
            case MSG_GET_MODULE_ID:
               if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT ) { while(1); }
               AB_iModuleType = iLeTOi( *(UINT16*)&sMsgBuffer.abData[ 0 ] );
               break;

            case MSG_GET_NETWORK_ID:
               if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT ) { while(1); }
               AB_iNetworkType = iLeTOi( *(UINT16*)&sMsgBuffer.abData[ 0 ] );

               /*
               ** Call AD_Init() to initilaize AD object based on
               ** know AB_iModuleType and AB_iNetworkType
               */

               AD_Init();
               break;

            case MSG_AD_USER_INIT:
               AD_ProcUserInitResp( &sMsgBuffer );
               break;

            case MSG_MAP_IO_WRITE:
            case MSG_MAP_IO_READ:
               /*
               ** It is a response to a mapping command.
               ** Check if everything went well.
               */

               if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT )
               {
                  /*
                  ** The Anybus-CC has responded with the error bit set. This means
                  ** something is wrong.
                  ** PORTING ALERT!
                  ** Application specific error handling can optionally be inserted
                  ** here. For example: Indicate to user that something is wrong
                  ** with the Anybus-CC.
                  ** sMsgBuffer contains information about exactly which command
                  ** caused the error and what the error is.
                  */

                  while( 1 );
               }
               break;

            case MSG_SETUP_COMPLETE:

               /*
               ** It is a response to the setup complete command.
               ** Check if everything went well.
               */

               if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT )
               {
                  int fTrip;

                  /*
                  ** The Anybus-CC has responded with the error bit set. This means
                  ** something is wrong.
                  ** PORTING ALERT!
                  ** Application specific error handling can optionally be inserted
                  ** here. For example: Indicate to user that something is wrong
                  ** with the Anybus-CC.
                  */

                  fTrip = TRUE;
               }
               else
               {
                  /*
                  ** The process data will be transmitted in every serial telegram from now on.
                  ** Increase the Rx and Tx sizes accordingly.
                  ** The standard telegram is 19 bytes.
                  */

                  if( AB_bPdWriteSize > AB_MAX_PD_WRITE_SIZE )
                  {
                     while( 1 ); /* Trap: More data configured for write process data than setup by AB_MAX_PD_WRITE_SIZE */
                  }

                  *piRxSize = ( 19 + AB_bPdReadSize );
                  *piTxSize = ( 19 + AB_bPdWriteSize );
               }
               break;

            case MSG_DATA_FORMAT:
               /*
               ** It is a response to the 'get data format' command
               */

               if( sMsgBuffer.abData[ 0 ] > 1 )
               {
                  /*
                  ** The Anybus-CC responded with a unknown data format type.
                  ** This is a unexpected error. Application specific error
                  ** handling can optionally be inserted here.
                  ** PORTING ALERT!
                  ** For example: Indicate to user that something is wrong.
                  */

                  eNetFormat = NET_UNKNOWN;
               }
               else
               {
                  /*
                  ** The Anybus-CC responded with a correct data format type.
                  ** Store it for later use.
                  */

                  eNetFormat = sMsgBuffer.abData[ 0 ];
               }
               break;

            case MSG_DONE:
               break;

            case MSG_SET_IPADD:
            case MSG_SET_SMASK:
            case MSG_SET_ECS1:
            case MSG_SET_ECS2:
            case MSG_SET_STATIC:
//                ResetAnybus();               
//                AB_fReInitDriver = TRUE;
                break;
            case MSG_GET_IPADD:
                if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT ) { while(1); }
                IPAddressLocal[0] = sMsgBuffer.abData[0];
                IPAddressLocal[1] = sMsgBuffer.abData[1];
                IPAddressLocal[2] = sMsgBuffer.abData[2];
                IPAddressLocal[3] = sMsgBuffer.abData[3];
                AnybusGetIP = FALSE;
                break;
            case MSG_GET_SMASK:
                if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT ) { while(1); }
                SMaskLocal[0] = sMsgBuffer.abData[0];
                SMaskLocal[1] = sMsgBuffer.abData[1];
                SMaskLocal[2] = sMsgBuffer.abData[2];
                SMaskLocal[3] = sMsgBuffer.abData[3];
                AnybusGetSM = FALSE;
                break;
            case MSG_GET_MACADD:
                // Only get MAC address once 
                // For some reason, in Profinet units when multiple access is made here
                // it hangs up !!
                if (AnybusGetMAC == 1) {                
                    if( sMsgBuffer.sHeader.bCmd & ABP_MSG_HEADER_E_BIT ) { while(1); }
                        MACAddress[0] = sMsgBuffer.abData[0];
                        MACAddress[1] = sMsgBuffer.abData[1];
                        MACAddress[2] = sMsgBuffer.abData[2];
                        MACAddress[3] = sMsgBuffer.abData[3];
                        MACAddress[4] = sMsgBuffer.abData[4];
                        MACAddress[5] = sMsgBuffer.abData[5];
                        AnybusGetMAC = 0;
                    }
                break;
            default:
               /*
               ** Unknown msg state
               ** PORTING ALERT!
               ** Example: Trap execution
               */

               while( 1 );
               break;

             } /* end switch( Source ID ) */
		   }
         else
         {
            /*
		      ** The Anybus-CC has responded with a source ID which is unknown
		      ** to us. This means something is wrong.
		      ** PORTING ALERT!
		      ** Application specific error handling can optionally be inserted
		      ** here.
		      ** For example: Indicate to user that something is wrong.
		      */

            while( 1 ); /* Trap */
         }

      } /* end if( message is a command ) */

   } /* end if( message available ) */

   if( ( bStatusReg & ABP_STAT_R_BIT ) &&
      !( bControlReg & ABP_CTRL_M_BIT ) &&
      ( bOutstandingCmds == 0 ) )
   {
      /*
      ** The Anybus-CC is ready to accept commands, and the WriteMsg buffer is free
      */

      switch( eCmdState )
      {
          
          case MSG_SET_IPADD:
          case MSG_GET_IPADD:
          case MSG_SET_SMASK:
          case MSG_GET_SMASK:
          case MSG_GET_MACADD:
          case MSG_SET_ECS1:
          case MSG_SET_ECS2:
          case MSG_SET_STATIC:
              break;
#ifdef USE_DIPSWITCHES
      case MSG_NODE_ADR:
         sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
         sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SW1 );
         sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
         sMsgBuffer.sHeader.bDataSize          = 1;
         sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
         sMsgBuffer.sHeader.bCmdExt1           = 0;
         sMsgBuffer.abData[ 0 ]                = bLastSw1 = bSw1;
         bControlReg                           |= ABP_CTRL_M_BIT;
		   eCmdRespState = eCmdState;
         eCmdState++;
         break;

      case MSG_BAUDRATE:
         sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
         sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SW2 );
         sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
         sMsgBuffer.sHeader.bDataSize          = 1;
         sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
         sMsgBuffer.sHeader.bCmdExt1           = 0;
         sMsgBuffer.abData[ 0 ]                = bLastSw2 = bSw2;
         bControlReg                           |= ABP_CTRL_M_BIT;
		   eCmdRespState = eCmdState;
         eCmdState++;
         break;
#endif
      case MSG_GET_MODULE_ID:
         sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_ANB;
         sMsgBuffer.sHeader.iInstance          = iTOiLe( 1 );
         sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
         sMsgBuffer.sHeader.bDataSize          = 0;
         sMsgBuffer.sHeader.bCmdExt0           = ABP_ANB_IA_MODULE_TYPE;
         sMsgBuffer.sHeader.bCmdExt1           = 0;
         bControlReg                           |= ABP_CTRL_M_BIT;
		   eCmdRespState = eCmdState++;
         break;

      case MSG_GET_NETWORK_ID:
         sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NW;
         sMsgBuffer.sHeader.iInstance          = iTOiLe( 1 );
         sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
         sMsgBuffer.sHeader.bDataSize          = 0;
         sMsgBuffer.sHeader.bCmdExt0           = ABP_NW_IA_NW_TYPE;
         sMsgBuffer.sHeader.bCmdExt1           = 0;
         bControlReg                           |= ABP_CTRL_M_BIT;
		   eCmdRespState = eCmdState++;
         break;

      case MSG_AD_USER_INIT:
         if( AD_ProcNextUserInitCmd( &sMsgBuffer ) )
         {
            eCmdRespState = eCmdState;
         }
		   else
		   {
            eCmdState++;
		   }
         break;

      case MSG_MAP_IO_WRITE:
         if( AD_MapNextAdiWriteArea( &sMsgBuffer, FALSE ) )
         {
            eCmdRespState = eCmdState;
         }
         else
         {
            eCmdState++;
         }
         break;

      case MSG_MAP_IO_READ:
         if( AD_MapNextAdiReadArea( &sMsgBuffer, FALSE ) )
         {
            eCmdRespState = eCmdState;
         }
         else
         {
            eCmdState++;
         }
         break;

      case MSG_DATA_FORMAT:
         sMsgBuffer.sHeader.bSourceId          = MSG_DATA_FORMAT;
         sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NW;
         sMsgBuffer.sHeader.iInstance          = iTOiLe( 1 );
         sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
         sMsgBuffer.sHeader.bDataSize          = 0;
         sMsgBuffer.sHeader.bCmdExt0           = ABP_NW_IA_DATA_FORMAT;
         sMsgBuffer.sHeader.bCmdExt1           = 0;
         bControlReg                           |= ABP_CTRL_M_BIT;
         eCmdRespState = eCmdState++;
         break;

      case MSG_SETUP_COMPLETE:

         /*
         ** End the setup phase by sending the SETUP_COMPLETE command after
         ** we have received the responses to all commands which we have sent.
         */

         if( bOutstandingCmds == 0 )
         {
            /*
            ** All the configuration commands have been processed by the Anybus-CC.
            ** Go ahead and end the setup phase by sending SETUP_COMPLETE.
            */

            sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_ANB;
            sMsgBuffer.sHeader.iInstance          = iTOiLe( 1 );
            sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
            sMsgBuffer.sHeader.bDataSize          = ABP_BOOL_SIZEOF;
            sMsgBuffer.sHeader.bCmdExt0           = ABP_ANB_IA_SETUP_COMPLETE;
            sMsgBuffer.sHeader.bCmdExt1           = 0;
            sMsgBuffer.abData[ 0 ]                = TRUE;
            bControlReg                           |= ABP_CTRL_M_BIT;
            eCmdRespState = eCmdState++;
         }
         break;

      case MSG_DONE:

         /*
         ** All the initialization commands have already been sent.
         ** Check the node adress or baudrate DIP-switches if available, send
         ** a update to the Anybus-CC if they have changed.
         */
#ifdef USE_DIPSWITCHES
         if( bSw1 != bLastSw1 )
         {
            /*
            ** DIP switch 1 (node adress) has changed.
            ** Send a update to the Anybus-CC.
            */

            sMsgBuffer.sHeader.bSourceId          = MSG_NODE_ADR;
            sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
            sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SW1 );
            sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
            sMsgBuffer.sHeader.bDataSize          = 1;
            sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
            sMsgBuffer.sHeader.bCmdExt1           = 0;
            sMsgBuffer.abData[ 0 ]                = bLastSw1 = bSw1;
            bControlReg                           |= ABP_CTRL_M_BIT;
         }
         else if( bSw2 != bLastSw2 )
         {
            /*
            ** DIP switch 2 (baudrate) has changed.
            ** Send a update to the Anybus-CC.
            */

            sMsgBuffer.sHeader.bSourceId          = MSG_BAUDRATE;
            sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
            sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SW2 );
            sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
            sMsgBuffer.sHeader.bDataSize          = 1;
            sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
            sMsgBuffer.sHeader.bCmdExt1           = 0;
            sMsgBuffer.abData[ 0 ]                = bLastSw2 = bSw2;
            bControlReg                           |= ABP_CTRL_M_BIT;
         }
         else
#endif
         {
            /*
            ** New commands can be added here.
            */
//AnybusSetIP,AnybusGetIP,AnybusSetSM,AnybusGetSM,AnybusGetMAC;

             if(AnybusGetIP) {
                sMsgBuffer.sHeader.bSourceId          = MSG_GET_IPADD;
                sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
                sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_IPADD );
                sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
                sMsgBuffer.sHeader.bDataSize          = 0;
                sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
                sMsgBuffer.sHeader.bCmdExt1           = 0;
                bControlReg                           |= ABP_CTRL_M_BIT;
                eCmdRespState = MSG_GET_IPADD;
                
             }
             else if(AnybusSetStatic) {
                sMsgBuffer.sHeader.bSourceId          = MSG_SET_STATIC;
                sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
                sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_DHCP );
                sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
                sMsgBuffer.sHeader.bDataSize          = 1;
                sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
                sMsgBuffer.sHeader.bCmdExt1           = 0;
                sMsgBuffer.abData[ 0 ]                = 0;//1: enable DHCP, 0: disable
                bControlReg                           |= ABP_CTRL_M_BIT;
                AnybusSetStatic = FALSE;
             }
             else if(AnybusSetIP) {
                    sMsgBuffer.sHeader.bSourceId          = MSG_SET_IPADD;
                    sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
                    sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_IPADD );
                    sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
                    sMsgBuffer.sHeader.bDataSize          = 4;
                    sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
                    sMsgBuffer.sHeader.bCmdExt1           = 0;
                    sMsgBuffer.abData[ 0 ]                = IPAddressLocal[0];
                    sMsgBuffer.abData[ 1 ]                = IPAddressLocal[1];
                    sMsgBuffer.abData[ 2 ]                = IPAddressLocal[2];
                    sMsgBuffer.abData[ 3 ]                = IPAddressLocal[3];
                    bControlReg                           |= ABP_CTRL_M_BIT;
                    AnybusSetIP = FALSE;
                   
            }
            else if(AnybusSetSM) {
              sMsgBuffer.sHeader.bSourceId          = MSG_SET_SMASK;
              sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
              sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SMASK );
              sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
              sMsgBuffer.sHeader.bDataSize          = 4;
              sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
              sMsgBuffer.sHeader.bCmdExt1           = 0;
              sMsgBuffer.abData[ 0 ]                = SMaskLocal[0];
              sMsgBuffer.abData[ 1 ]                = SMaskLocal[1];
              sMsgBuffer.abData[ 2 ]                = SMaskLocal[2];
              sMsgBuffer.abData[ 3 ]                = SMaskLocal[3];
              bControlReg                           |= ABP_CTRL_M_BIT;
              AnybusSetSM = FALSE;
            }
            else if(AnybusGetSM) {
                 sMsgBuffer.sHeader.bSourceId          = MSG_GET_SMASK;
                 sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
                 sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_SMASK );
                 sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
                 sMsgBuffer.sHeader.bDataSize          = 0;
                 sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
                 sMsgBuffer.sHeader.bCmdExt1           = 0;
                 bControlReg                           |= ABP_CTRL_M_BIT;
                 eCmdRespState = MSG_GET_SMASK;
            }
            else if(AnybusGetMAC) {
                   sMsgBuffer.sHeader.bSourceId          = MSG_GET_MACADD;
                   sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NWETN;
                   sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_ETN_INST_NUM_MACADD );
                   sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_GET_ATTR;
                   sMsgBuffer.sHeader.bDataSize          = 0;
                   sMsgBuffer.sHeader.bCmdExt0           = ABP_ETN_IA_MACADD;
                   sMsgBuffer.sHeader.bCmdExt1           = 0;
                   bControlReg                           |= ABP_CTRL_M_BIT;
                   eCmdRespState = MSG_GET_MACADD;
            }
//            else if(AnybusSetECS1) {
//                    sMsgBuffer.sHeader.bSourceId          = MSG_SET_ECS1;
//                    sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
//                    sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_ECS1 );
//                    sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
//                    sMsgBuffer.sHeader.bDataSize          = 1;
//                    sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
//                    sMsgBuffer.sHeader.bCmdExt1           = 0;
//                    sMsgBuffer.abData[ 0 ]                = 0;//auto negotiation
//                    bControlReg                           |= ABP_CTRL_M_BIT;
//                    AnybusSetECS1 = FALSE;
//            }
//            else if(AnybusSetECS2) {
//                 sMsgBuffer.sHeader.bSourceId          = MSG_SET_ECS2;
//                 sMsgBuffer.sHeader.bDestObj           = ABP_OBJ_NUM_NC;
//                 sMsgBuffer.sHeader.iInstance          = iTOiLe( ABP_NC_INST_NUM_ECS2 );
//                 sMsgBuffer.sHeader.bCmd               = ABP_MSG_HEADER_C_BIT | ABP_CMD_SET_ATTR;
//                 sMsgBuffer.sHeader.bDataSize          = 1;
//                 sMsgBuffer.sHeader.bCmdExt0           = ABP_NC_VAR_IA_VALUE;
//                 sMsgBuffer.sHeader.bCmdExt1           = 0;
//                 sMsgBuffer.abData[ 0 ]                = 0;//auto negotiation
//                 bControlReg                           |= ABP_CTRL_M_BIT;
//                 AnybusSetECS2 = FALSE;
//            }
         }
         break;
      } /* end switch( command state ) */

      if( bControlReg & ABP_CTRL_M_BIT )
      {
         /*
         ** A new command has been posted to the Anybus-CC.
         ** Increment counter for outstanding commands.
         ** Clear the Ready bit to prevent the ABCC from sending any commands to us.
         */

         bOutstandingCmds++;
         sMsgBuffer.sHeader.bSourceId = AB_bNextSrcId++;

         bControlReg &= ~ABP_CTRL_R_BIT;
      }

   } /* end if( it's OK to send a command ) */

  //TODO: note to me. looks like it is just getting caught on that 255 value dno why. it appears that the sourceid randomly goes up as anybus gets called while anybus module isnt ready

   if( bControlReg & ABP_CTRL_M_BIT )
   {
      if( iTxMsgBufferOffset < sMsgBuffer.sHeader.bDataSize + 8 )
      {
         /*
         ** There is message data waiting for transmission to the ABCC
         */

         memcpy( &abTxBuffer[ 1 ], &(((UINT8*)&sMsgBuffer)[ iTxMsgBufferOffset ]), min( 16, sizeof(ABP_MsgType) - iTxMsgBufferOffset ) );
         iTxMsgBufferOffset += 16;
      }
      else
      {
         /*
         ** All fragments have been sent.
         ** Terminate fragmentation.
         */

         bControlReg &= ~ABP_CTRL_M_BIT;
         iTxMsgBufferOffset = 0;

         if( bOutstandingCmds == 0 )
         {
            /*
            ** We are not waiting for any repsonses, and the message buffer is free.
            ** Set the Ready bit to allow the ABCC to send a command to us.
            */

            bControlReg |= ABP_CTRL_R_BIT;
         }
      }
   }


   if( ( bStatusReg & ABP_STAT_S_BITS ) > ABP_ANB_STATE_SETUP )
   {
      /*
      ** Send new "write process data" to the Anybus-CC.
      ** The data format of the process data is network specific.
      ** Convert our data accordingly.
      */

      AD_UpdatePdWriteData( &abTxBuffer[ 17 ] );
   }

   if( ( bStatusReg & ABP_STAT_S_BITS ) == ABP_ANB_STATE_PROCESS_ACTIVE )
   {
      /*
      ** The "read process data" is only valid in the PROCESS_ACTIVE state.
      ** Retrieve the new "read process data" from the Anybus-CC.
      ** The data format of the process data is network specific.
      ** Convert it to our native format.
      */

      AD_UpdatePdReadData( &pbRxData[ 17 ] );
   }

   /*
   ** Finally, complete the telegram with the control register and CRC values
   ** and send it to the Anybus-CC.
   */

   abTxBuffer[ 0 ] = bControlReg;

   iCrc = Crc16( abTxBuffer, (UINT16)(*piTxSize - 2) );

   abTxBuffer[ *piTxSize - 2 ] = (UINT8)( ( iCrc >> 8 ) & 0x00FF );
   abTxBuffer[ *piTxSize - 1 ] = (UINT8)( iCrc & 0x00FF );

   return( abTxBuffer );

} /* end of AnybusMain() */


/*------------------------------------------------------------------------------
** ProcAppObjectRequest()
**------------------------------------------------------------------------------
*/

void ProcAppObjectRequest( void )
{
   switch( sMsgBuffer.sHeader.bDestObj )
   {
   case ABP_OBJ_NUM_APPD:

      /*
      ** Command to the application data object
      */

      AD_ProcObjectRequest( &sMsgBuffer );
      break;

#ifdef AB_HOST_APPLICATION_OBJECT_0xFF
   case ABP_OBJ_NUM_APP:
      APP_ProcObjectRequest( &sMsgBuffer );
      break;
#endif
#ifdef AB_HOST_BACNET_OBJECT_0xEF
   case ABP_OBJ_NUM_BAC:
      BAC_ProcObjectRequest( &sMsgBuffer );
      break;
#endif
#ifdef AB_HOST_PNIO_OBJECT_0xF6
       case ABP_OBJ_NUM_PNIO:
        PNIO_ProcObjectRequest( &sMsgBuffer );
           break;
#endif
#ifdef AB_HOST_EIP_OBJECT_0xF8
       case ABP_OBJ_NUM_EIP:
        EIP_ProcObjectRequest( &sMsgBuffer );
           break;
#endif
#ifdef AB_ETHERNET_HOST_OBJECT_0xF9
   case ABP_OBJ_NUM_ETN:
        ETN_ProcObjectRequest( &sMsgBuffer );
       break;
#endif
   default:
      /*
      ** Command to a unsupported object.
      */

      SetMsgError( &sMsgBuffer, 1, ABP_ERR_UNSUP_OBJ );
      break;
   }

   bControlReg |= ABP_CTRL_M_BIT;

} /* end of ProcAppObjectRequest */


/*------------------------------------------------------------------------------
** ScheduleUserMsgRequest()
**------------------------------------------------------------------------------
*/

BOOL8 ScheduleUserMsgRequest( AB_UserMsgReqType* psUserMsgReq, AB_pnMsgReqCallback pnUserCallback )
{

   return( FALSE );
} /* rnd of ScheduleUserMsgRequest */


/*******************************************************************************
**
** End of anybus.c
**
********************************************************************************
*/
