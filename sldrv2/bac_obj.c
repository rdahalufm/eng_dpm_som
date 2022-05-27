/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** bac_obj.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
**
** BACnet Host Object (0xEF) - Implementation file
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
** $Modtime: 2012-01-20 12:00:00+02:00 $
**
** Version history:
**
**    Ver 1.00     2012-01-20  MSv   First version
**
********************************************************************************
********************************************************************************
*/


#include "anybus.h"

#ifdef AB_HOST_BACNET_OBJECT_0xEF

#include "abp.h"
#include "ad_obj.h"
#include "abp_bac.h"
#include "bac_obj.h"
#include <string.h>


/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
** BACnet Host object internal variables
**------------------------------------------------------------------------------
*/

#define BAC_35EAST_WACKER_INC_VENDOR_ID   2

UINT8 BAC_abObjectName[ 50 ]              = "Climate Controller: #35 East Wacker";
const UINT8 BAC_abVendorName[]            = "35 East Wacker Inc";
const UINT8 BAC_abModelName[]             = "CLCTRL: 13A";
const UINT8 BAC_abAppSwVersion[]          = "APP: 1.00.01";
BOOL8 BAC_fAdvancedMapMode                = TRUE;


/*-------------------------------------------------------------------------------------------------------
** BACnet advanced mapping table allocation
** 
** 1. iBacObjType - BACnet class type enum, see BAC_OBJ_TYPE_XX defines
** 2. lBacInst    - BACnet instance number
** 3. iAdiInst    - Cooresponding ADI Instance
**-------------------------------------------------------------------------------------------------------
** 1. iBacObjType |  2. lBacInst |  3. iADIInst
**-------------------------------------------------------------------------------------------------------
*/

BAC_AdvMapEntryType BAC_asAdvMapTable[] =
{
   { BAC_OBJ_TYPE_ANALOG_VALUE,     0, 3 },
   { BAC_OBJ_TYPE_BINARY_VALUE,     0, 1 },
   { BAC_OBJ_TYPE_MULTISTATE_VALUE, 0, 170 }
};

#define BAC_SIZE_OF_ADV_MAP_ARRAY ( sizeof( BAC_asAdvMapTable ) / sizeof( BAC_AdvMapEntryType ) )


/*******************************************************************************
**
** Private Globals
**
********************************************************************************
*/


/*******************************************************************************
**
** Public Functions
**
********************************************************************************
*/


/*------------------------------------------------------------------------------
** BAC_Init()
**------------------------------------------------------------------------------
*/

void BAC_Init( void )
{
   /*
   ** In this context we should initilaize the APP object
   ** internal contexts.
   */

} /* end of BAC_Init */


/*------------------------------------------------------------------------------
** BAC_ProcObjectRequest()
**------------------------------------------------------------------------------
*/

void BAC_ProcObjectRequest( ABP_MsgType* psMsgBuffer )
{
   UINT16 i;
   AD_AdiEntryType* psADIEntry;

   switch( iLeTOi( psMsgBuffer->sHeader.iInstance ) )
   {
   case ABP_INST_OBJ:
      /* An request to the object instance */
      switch( psMsgBuffer->sHeader.bCmd & ABP_MSG_HEADER_CMD_BITS )
      {
      case ABP_CMD_GET_ATTR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_OA_NAME: /* Name */
            memcpy( psMsgBuffer->abData, "BACnet", 6 );
            psMsgBuffer->sHeader.bDataSize = 6;
            break;

         case ABP_OA_REV: /* Revision */
            psMsgBuffer->abData[ 0 ] = 1;
            psMsgBuffer->sHeader.bDataSize = 1;
            break;

         case ABP_OA_NUM_INST: /* Number of instances */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 1 );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;

         case ABP_OA_HIGHEST_INST: /* Highest instance no. */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 1 );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;

         default: /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;

      case ABP_BAC_CMD_GET_ADI_BY_BACNET_OBJ_INST:
         for( i = 0; i < BAC_SIZE_OF_ADV_MAP_ARRAY; i++ )
         {
             if( ( BAC_asAdvMapTable[ i ].iBacObjType == iLeTOi( *(UINT16*)&psMsgBuffer->abData[ 0 ] ) ) &&
                 ( BAC_asAdvMapTable[ i ].lBacInst == lLeTOl( *(UINT32*)&psMsgBuffer->abData[ 2 ] ) ) )
            {
               *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( BAC_asAdvMapTable[ i ].iAdiInst );
               psMsgBuffer->sHeader.bDataSize = 2;
               break;
            }
         }

         if( i == BAC_SIZE_OF_ADV_MAP_ARRAY )
         {
            SetMsgError( psMsgBuffer, 1, ABP_BAC_EXCPT_INFO_COULD_NOT_READ_OBJ_INST_BY_ADI );
         }
         break;
         
      case ABP_BAC_CMD_GET_ADI_BY_BACNET_OBJ_INST_NAME:
         for( i = 0; i < BAC_SIZE_OF_ADV_MAP_ARRAY; i++ )
         {
            if( ( psADIEntry = AD_GetAdiInstEntry( BAC_asAdvMapTable[ i ].iAdiInst ) ) != NULL )
            {
               UINT8 bNameLen = strlen( psADIEntry->pabName );

               if( ( bNameLen == psMsgBuffer->sHeader.bDataSize ) &&
                   ( memcmp( psADIEntry->pabName, psMsgBuffer->abData, bNameLen ) == 0 ) )
               {
                  *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( BAC_asAdvMapTable[ i ].iAdiInst );
                  *(UINT16*)&psMsgBuffer->abData[ 2 ] = iTOiLe( BAC_asAdvMapTable[ i ].iBacObjType );
                  *(UINT32*)&psMsgBuffer->abData[ 4 ] = lTOlLe( BAC_asAdvMapTable[ i ].lBacInst );
                  psMsgBuffer->sHeader.bDataSize = 8;
                  break;
               }
            }
         }

         if( i == BAC_SIZE_OF_ADV_MAP_ARRAY )
         {
            SetMsgError( psMsgBuffer, 1, ABP_BAC_EXCPT_INFO_COULD_NOT_READ_OBJ_INST_BY_ADI );
         }
         break;
      case ABP_BAC_CMD_GET_ALL_BACNET_OBJ_INSTANCES:
         {
            UINT16 iBacObjType = iLeTOi( *(UINT16*)&psMsgBuffer->abData[ 0 ] );

            memset( psMsgBuffer->abData, 0, sizeof( psMsgBuffer->abData ) );         
            for( i = 0; i < BAC_SIZE_OF_ADV_MAP_ARRAY; i++ )
            {
               if( BAC_asAdvMapTable[ i ].iBacObjType == iBacObjType )
               {
                  psMsgBuffer->abData[ ( ( BAC_asAdvMapTable[ i ].lBacInst ) / 8 ) ] |= ( 0x01 << ( ( BAC_asAdvMapTable[ i ].lBacInst ) % 8 ) );
               }
            }
            psMsgBuffer->sHeader.bDataSize = 255;
         }
         break;
      case ABP_BAC_CMD_GET_BACNET_OBJ_INST_BY_ADI:
         for( i = 0; i < BAC_SIZE_OF_ADV_MAP_ARRAY; i++ )
         {
            if( BAC_asAdvMapTable[ i ].iAdiInst == *(UINT16*)&psMsgBuffer->abData[ 0 ] )
            {
               *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( BAC_asAdvMapTable[ i ].iBacObjType );
               *(UINT32*)&psMsgBuffer->abData[ 2 ] = lTOlLe( BAC_asAdvMapTable[ i ].lBacInst );
               psMsgBuffer->sHeader.bDataSize = 6;
               break;
            }
         }

         if( i == BAC_SIZE_OF_ADV_MAP_ARRAY )
         {
            SetMsgError( psMsgBuffer, 1, ABP_BAC_EXCPT_INFO_COULD_NOT_READ_OBJ_INST_BY_ADI );
         }
         break;

      default: /* Unsupported command */
         SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
         break;
      }
      break;
   
   case 1: /* Instance 1 */
      switch( psMsgBuffer->sHeader.bCmd & ABP_MSG_HEADER_CMD_BITS )
      {
      case ABP_CMD_GET_ATTR:
         
         /* Switch on attribute */
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_BAC_IA_OBJECT_NAME:
            psMsgBuffer->sHeader.bDataSize = strlen( BAC_abObjectName );
            memcpy( &psMsgBuffer->abData[ 0 ], BAC_abObjectName, psMsgBuffer->sHeader.bDataSize );
            break;
         case ABP_BAC_IA_VENDOR_NAME:
            psMsgBuffer->sHeader.bDataSize = strlen( BAC_abVendorName );
            memcpy( &psMsgBuffer->abData[ 0 ], BAC_abVendorName, psMsgBuffer->sHeader.bDataSize );
            break;
         case ABP_BAC_IA_VENDOR_IDENTIFIER:
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( BAC_35EAST_WACKER_INC_VENDOR_ID );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;
         case ABP_BAC_IA_MODEL_NAME:
            psMsgBuffer->sHeader.bDataSize = strlen( BAC_abModelName );
            memcpy( &psMsgBuffer->abData[ 0 ], BAC_abModelName, psMsgBuffer->sHeader.bDataSize );
            break;
         case ABP_BAC_IA_APP_SOFTWARE_VERSION:
            psMsgBuffer->sHeader.bDataSize = strlen( BAC_abAppSwVersion );
            memcpy( &psMsgBuffer->abData[ 0 ], BAC_abAppSwVersion, psMsgBuffer->sHeader.bDataSize );
            break;
         case ABP_BAC_IA_SUPPORT_ADV_MAPPING:
            psMsgBuffer->abData[ 0 ] = BAC_fAdvancedMapMode;
            psMsgBuffer->sHeader.bDataSize = 1;
            break;
         default:
            /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;
      case ABP_CMD_SET_ATTR:
         /* Switch on attribute */
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_BAC_IA_OBJECT_NAME:
            if( psMsgBuffer->sHeader.bDataSize <= ( sizeof( BAC_abObjectName ) - 1 ) )
            {
               memcpy( BAC_abObjectName, &psMsgBuffer->abData[ 0 ], psMsgBuffer->sHeader.bDataSize );
               BAC_abObjectName[ psMsgBuffer->sHeader.bDataSize ] = 0;
            }
            else
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_TOO_MUCH_DATA ); 
            }
            break;
         default:
            /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;

      default:
         /* Unsupported command */
         SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
         break;
      }
      break;
   default:
      /* Instance not found */
      SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_INST );
      break;
   }

} /* end of APP_ProcObjectRequest */

#endif


/*******************************************************************************
**
** End of bac_obj.c
**
********************************************************************************
*/
