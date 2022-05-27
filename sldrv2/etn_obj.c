/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** etn_obj.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
**
** Ethernet Host Object (0xF9) - Implementation file
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

#ifdef AB_ETHERNET_HOST_OBJECT_0xF9

#include "abp.h"
#include "ad_obj.h"
#include <string.h>

/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
** ETN_fNvsConfigIsOutOfBox - Specififes if this application has an out-of-box
**                            NVS config setup or not.
**------------------------------------------------------------------------------
*/

BOOL8 ETN_fNvsConfigIsOutOfBox = TRUE;


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
** ETN_Init()
**------------------------------------------------------------------------------
*/

void ETN_Init( void )
{
   /*
   ** In this context we should initilaize the ETN object
   ** internal contexts.
   */

} /* end of ETN_Init */

/*------------------------------------------------------------------------------
** ETN_ProcObjectRequest()
**------------------------------------------------------------------------------
*/

void ETN_ProcObjectRequest( ABP_MsgType* psMsgBuffer )
{
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
            memcpy( psMsgBuffer->abData, "Ethernet", 8 );
            psMsgBuffer->sHeader.bDataSize = 8;
            break;

         case ABP_OA_REV: /* Revision */
            psMsgBuffer->abData[ 0 ] = 2;
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
      }
      break;
   
   case 1: /* Instance 1 */
      switch( psMsgBuffer->sHeader.bCmd & ABP_MSG_HEADER_CMD_BITS )
      {
      case ABP_CMD_GET_ATTR:
         
         /* Switch on attribute */
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case 7: /* Enable Admin Mode */
            psMsgBuffer->abData[ 0 ] = TRUE;
            psMsgBuffer->sHeader.bDataSize = 1;
            break;
         default:
            /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;

      case ABP_CMD_GET_ENUM_STR:
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

} /* end of ETN_ProcObjectRequest */

#endif


/*******************************************************************************
**
** End of etn_obj.c
**
********************************************************************************
*/
