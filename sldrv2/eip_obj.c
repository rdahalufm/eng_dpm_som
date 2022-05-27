/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** eip_obj.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
**
** EtherNet/IP Host Object (0xF8) - Implementation file
**
********************************************************************************

******************************************************************************
********************************************************************************
**
** Change Log
** ----------
**
** Latest modification:
** --------------------
** $Modtime: 2013-12-06 10:00:00+01:00 $
**
** Version history:
**
**    Ver 1.00     2007-12-06  MSv   First version
**
**
********************************************************************************
********************************************************************************
*/


#include "anybus.h"

#ifdef AB_HOST_EIP_OBJECT_0xF8

#include "abp.h"
#include "ad_obj.h"
#include <string.h>

/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/
extern UINT32 SerialNumber;
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
** EIP_Init()
**------------------------------------------------------------------------------
*/

void EIP_Init( void )
{
   /*
   ** In this context we should initilaize the APP object
   ** internal contexts.
   */

} /* end of EIP_Init */


/*------------------------------------------------------------------------------
** EIP_ProcObjectRequest()
**------------------------------------------------------------------------------
*/

void EIP_ProcObjectRequest( ABP_MsgType* psMsgBuffer )
{
    unsigned char tempArray[20];
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
            memcpy( psMsgBuffer->abData, "EtherNet/IP", 11 );
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
             case 1://Vendor ID UINT16 -- Default 0x005A -- UFM VID 774
                *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 774 );
                psMsgBuffer->sHeader.bDataSize = 2;
                 break;
             case 2://Device Type UINT16 -- Default 0x0000 - Set = 0x2B Generic Device
                *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 0x2B );
                psMsgBuffer->sHeader.bDataSize = 2;
                 break;
             case 3://Product Code UINT16 -- Default 0x002E - Deltapoint EIP base - (0) EIP + FE(11) Model code
                *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 11 );
                psMsgBuffer->sHeader.bDataSize = 2;
                 break;
             case 4://Revision UINT8 Major UINT8 Minor -- //Rev 2.01
                psMsgBuffer->abData[ 0 ] = 2;//Major - 2
                psMsgBuffer->abData[ 1 ] = 1;//Minor - .01
                psMsgBuffer->sHeader.bDataSize = 2;
                 break;
             case 5://Serial Number UINT32 -- Default ??
                *(UINT32*)&psMsgBuffer->abData[ 0 ] = iTOiLe( SerialNumber );
                psMsgBuffer->sHeader.bDataSize = 4;
                 break;
             case 6://Product Name Array of CHAR
                 tempArray[0]='R';tempArray[1]='O';tempArray[2]='C';tempArray[3]='O';tempArray[4]='N';tempArray[5]=' ';tempArray[6]='D';tempArray[7]='e';tempArray[8]='l';tempArray[9]='t';tempArray[10]='a';tempArray[11]='P';tempArray[12]='o';tempArray[13]='i';tempArray[14]='n';tempArray[15]='t';
                 memcpy(psMsgBuffer->abData,tempArray,16);
                 psMsgBuffer->sHeader.bDataSize = 16;
                 break;
          case 7: /* Producing Instance No. */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 101 );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;
         case 8: /* Consuming Instance No. */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 102 );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;
         case 15: /* Configuration Instance No. */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( 128 );
            psMsgBuffer->sHeader.bDataSize = 2;
            break;
         case 16://Disable Strict IO Match
             psMsgBuffer->abData[ 0 ] = 1;
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
** End of eip_obj.c
**
********************************************************************************
*/
