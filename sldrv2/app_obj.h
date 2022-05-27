/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** app_obj.h
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

#ifndef APP_OBJ_H
#define APP_OBJ_H

#include "./anybus.h"
#include "./abp.h"


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
** APP_fNvsConfigIsOutOfBox - Specififes if this application has an out-of-box
**                            NVS config setup or not.
**------------------------------------------------------------------------------
*/

extern BOOL8 APP_fNvsConfigIsOutOfBox;


/*******************************************************************************
**
** Public Services Definitions
**
********************************************************************************
*/

/*------------------------------------------------------------------------------
**
** APP_Init()
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

EXTFUNC void APP_Init( void );

/*------------------------------------------------------------------------------
**
** APP_IsResetRequestAllowed()
**
** Called by APP_ProcObjectRequest to check if the requested reset request is 
** acceptable by application.
**
**------------------------------------------------------------------------------
**
** Inputs:
**    bResetType        - Type of reset, see ABP_RESET_XXX defines
**
** Outputs:
**    BOOL8             - TRUE: Reset request is allowed
**                        FALSE: Reset request NOT allowed
**
** Usage:
**    APP_IsResetRequestAllowed();
**
**------------------------------------------------------------------------------
*/

EXTFUNC BOOL8 APP_IsResetRequestAllowed( UINT8 bResetType );


/*------------------------------------------------------------------------------
**
** APP_ProcResetRequest()
**
** Called by APP_ProcObjectRequest to perform an reset request
**
**------------------------------------------------------------------------------
**
** Inputs:
**    bResetType        - Type of reset, see ABP_RESET_XXX defines
**
** Outputs:
**    None
**
** Usage:
**    APP_ProcResetRequest();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void APP_ProcResetRequest( UINT8 bResetType );


/*------------------------------------------------------------------------------
**
** APP_ProcObjectRequest()
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
**    APP_ProcObjectRequest();
**
**------------------------------------------------------------------------------
*/

EXTFUNC void APP_ProcObjectRequest( ABP_MsgType * psMsgBuffer );


/*******************************************************************************
**
** Private Services Definitions
**
********************************************************************************
*/


#endif  /* inclusion lock */

/*******************************************************************************
**
** End of app_obj.h
**
********************************************************************************
*/
