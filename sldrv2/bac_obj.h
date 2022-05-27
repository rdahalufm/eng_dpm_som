/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** bac_obj.h
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
**
** A minimalistic Anybus-CC application example.
**
** BACnet Host Object (0xEF) - Public interfaces
**
********************************************************************************
********************************************************************************
**                                                                            **
** COPYRIGHT NOTIFICATION (c) 2012 HMS Industrial Networks AB                 **
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
*/

/*******************************************************************************
********************************************************************************
**
** Change Log
** ----------
**
** Latest modification:
** --------------------
** $Modtime: 2012-01-27 10:00:00+01:00 $
**
** Version history:
**
**    Ver 1.00     2007-12-14  MSv   First version
**
********************************************************************************
********************************************************************************
*/

#ifndef BAC_OBJ_H
#define BAC_OBJ_H

#include "anybus.h"
#include "abp.h"


/*------------------------------------------------------------------------------
** BACnet object class type enumerations
**------------------------------------------------------------------------------
*/

#define BAC_OBJ_TYPE_ANALOG_VALUE         2
#define BAC_OBJ_TYPE_BINARY_VALUE         5
#define BAC_OBJ_TYPE_MULTISTATE_VALUE     19


/*******************************************************************************
**
** Type Definitions
**
********************************************************************************
*/


/*------------------------------------------------------------------------------
** BAC_AdvMapEntryType - BACnet advanced mapping entry
**
** iBacObjType - BACnet class type enum, see BAC_OBJ_TYPE_XX defines
** lBacInst    - BACnet instance number
** iAdiInst    - Cooresponding ADI Instance
**------------------------------------------------------------------------------
*/

typedef struct BAC_AdvMapEntryType
{
   UINT16 iBacObjType;
   UINT32 lBacInst;
   UINT16 iAdiInst;
} BAC_AdvMapEntryType;


/*******************************************************************************
**
** Public Globals
**
********************************************************************************
*/


/*------------------------------------------------------------------------------
**
**------------------------------------------------------------------------------
*/


/*******************************************************************************
**
** Public Services Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** BAC_Init()
**
** Performe APP Init routines
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
**    AD_Init();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void BAC_Init( void );


/*------------------------------------------------------------------------------
**
** BAC_ProcObjectRequest()
**
** Called by Anybus driver to process an object request against the
** BACnet Host Object (0xEF).
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
**    BAC_ProcObjectRequest();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void BAC_ProcObjectRequest( ABP_MsgType * psMsgBuffer );


/*******************************************************************************
**
** Private Services Definitions
**
********************************************************************************
*/


#endif  /* inclusion lock */

/*******************************************************************************
**
** End of bac_obj.h
**
********************************************************************************
*/
