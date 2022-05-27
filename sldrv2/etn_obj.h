/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** etn_obj.h
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
**
** A minimalistic Anybus-CC application example.
**
** Application Object (0xFF) - Public interfaces
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

#ifndef ETN_OBJ_H
#define ETN_OBJ_H

#include "anybus.h"
#include "abp.h"


/*------------------------------------------------------------------------------
** ADI entry internal status bits (AD_AdiEntryType::bStatBits)
**
**------------------------------------------------------------------------------
*/


/*******************************************************************************
**
** Type Definitions
**
********************************************************************************
*/



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

extern BOOL8 ETN_fNvsConfigIsOutOfBox;


/*******************************************************************************
**
** Public Services Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** ETN_Init()
**
** Performe ETN Init routines
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

EXTFUNC void ETN_Init( void );

/*------------------------------------------------------------------------------
**
** ETN_ProcObjectRequest()
**
** Called by Anybus driver to process an object request against the
** Aplication Object (0xFF).
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
**    ETN_ProcObjectRequest();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void ETN_ProcObjectRequest( ABP_MsgType * psMsgBuffer );


/*******************************************************************************
**
** Private Services Definitions
**
********************************************************************************
*/


#endif  /* inclusion lock */

/*******************************************************************************
**
** End of etn_obj.h
**
********************************************************************************
*/
