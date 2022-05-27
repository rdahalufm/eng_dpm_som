/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** PNIO_obj.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
**
** PNIOnet Host Object (0xEF) - Implementation file
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

#ifdef AB_HOST_PNIO_OBJECT_0xF6

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
**------------------------------------------------------------------------------
*/


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
** PNIO_Init()
**------------------------------------------------------------------------------
*/

//void PNIO_Init( void )
//{
//   /*
//   ** In this context we should initilaize the APP object
//   ** internal contexts.
//   */
//
//} /* end of PNIO_Init */


/*------------------------------------------------------------------------------
** PNIO_ProcObjectRequest()
**------------------------------------------------------------------------------
*/

void PNIO_ProcObjectRequest( ABP_MsgType* psMsgBuffer )
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
            memcpy( psMsgBuffer->abData, "PROFINET IO", 11 );
            psMsgBuffer->sHeader.bDataSize = 11;
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
      case 0x17:    //this is command End_Of_Prm_Ind - code is locking in error state on this response
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
//          psMsgBuffer->sHeader.bCmdExt0 =0;
//          psMsgBuffer->sHeader.bCmdExt1 =0;
//          psMsgBuffer->abData[ 0 ] = 0;
//          psMsgBuffer->sHeader.bDataSize = 1;
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
** End of PNIO_obj.c
**
********************************************************************************
*/
