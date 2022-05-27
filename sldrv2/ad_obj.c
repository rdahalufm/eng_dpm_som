/*******************************************************************************
********************************************************************************
**
** File Name
** ---------
**
** ad_obj.c
**
********************************************************************************
********************************************************************************
**
** Description
** -----------
** Source file containing a minimalistic Anybus-CC application example.
**
** Application Data Object 0xFE (ADI) - Implementation file
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
** modified on 4/17/12
** lines 116-120 243-247 309 328 modified to match demo pdf ADIs // v.2 changed the indexes on line 309/328 to do 3x write 5x read, no errors seems to be needed to set read and write access to these locations(numbers match)
**
** Latest modification:
** --------------------
** $Modtime: 2012-01-20 12:00:00+02:00 $
**
** Version history:
**
**    Ver 1.00     2012-01-20  MSv   First version
**
**
********************************************************************************
********************************************************************************
*/


#include "anybus.h"
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
** AD_iNumOfADIs                 - Number of ADIs managed by AD (Updated automatically)
** AD_iHighestInstanceNumber     - Highest ADI instance number Updated automatically)
** AD_fHasPdReadDataLimitError   - TRUE: An limit violation (max/min) error exists for an read procedd data variable
**                                 FALSE: No limit error (max/min) exists
** AD_paiPdWriteMap              - Points to current write process data mapping list, setup in AD_Init()
**                                 if NULL: No mappings
** AD_paiPdReadMap               - Points to current read process data mapping list, setup in AD_Init()
**                                 if NULL: No mappings
**------------------------------------------------------------------------------
*/

UINT16   AD_iNumOfADIs;
UINT16   AD_iHighestInstanceNumber;
BOOL8    AD_fHasPdReadDataLimitError;
UINT16*  AD_paiPdWriteMap  = NULL;
UINT16*  AD_paiPdReadMap   = NULL;

/*------------------------------------------------------------------------------
** User declared ADI value data holders
** !!! PORTING ALART !!!!
** This is just example declarations and can be data linked to any code part
**------------------------------------------------------------------------------
*/


struct
{
//Inputs based on DeltaPoint Manifold IO Table
    UINT8  EIPStatus;
    UINT8  EIPSupplyFlow;
    UINT8  EIPReturnFlow;
    UINT8  EIPTemperature;

//Outputs
    UINT8  EIPOutput;

//Web Values
    UINT16 webUnderTemp; // under temperature
    UINT16 webMinFlow; //min flow
    UINT16 webFlowOkay;//flow ok
    UINT16 webLeakRate;//leak rate
    UINT16 webOverTemp;//overtemp
    UINT8  webResponseTime;//response time
    UINT8  webUnits;//units
    UINT16 webStatus;//web status
    UINT16 webFirmwareRev;//firmware Rev
    UINT32 webSerialNum;//serial Number
    UINT16 webRestartTime;//Restart Time
    UINT16 webSupplyFlow;//Website Supply
    UINT16 webReturnFlow;//website Return
    UINT16 webEIPStatus;//EIP Status Word
    UINT16 webEIPCommand;//EIP Command Word
    UINT8 webIPAddr[4];//IPAddressLocal
    UINT8 webSubnetMask[4];//SMaskLocal
    UINT16 webVenturiTime;//VenturiTimer
} AD_sADIValues;


/*-------------------------------------------------------------------------------------------------------
** ADI ENUM strings allocations
** Note: Optional, to be used in ADI properties allocations for ENUM if enum strings wants to be used.
**
** 1. eValue            - Enum value
** 2. abEnumStr         - Cooresponding enum string value
**-------------------------------------------------------------------------------------------------------
** 1. eValue   |  2. xMinabEnumStrValue
**-------------------------------------------------------------------------------------------------------
*/

AD_ENUMStrType ad_ENUMPropsString[] = { { 0, (UINT8 *)"Process OK" },
                                        { 1, (UINT8 *)"Process failed: Water level to high" },
                                        { 2, (UINT8 *)"Process failed: Valve 1 open problem" }
                                      };


/*-------------------------------------------------------------------------------------------------------
** ADI value properties allocation (optional)
** Note: Optional, if defined the cooresponding entry can be used for ADI instance allocations
**       in psValueProps in AD_asADIEntryList definition below.
**
** 1. xMinValue         - Minumum value allowed
** 2. xMaxValue         - Maximum value allowed
** 3. xDefaultValue     - Default value
** Note: The two fileds below only applies for AD_ENUMType type
** 4. bNumOfEnumStrings - Number of enum string entries in (5) below
** 5. psEnumStrings     - Pointer to array of AD_ENUMStrType defining enum value and coorespoinding string.
**-------------------------------------------------------------------------------------------------------
** 1. xMaxValue   |  2. xMinValue   |  3. xDefaultValue |   ( 4. bNumOfEnumStrings  |  5. psEnumStrings )
**-------------------------------------------------------------------------------------------------------
*/

AD_BOOL8Type   ad_BOOL8Props_0_1_0             = { 0, 1, 0 };
AD_SINT8Type   ad_SINT8Props_n100_100_0        = { -100, 100, 0};
AD_UINT8Type   ad_UINT8Props_0_255_0           = { 0,  255, 0 };
AD_SINT16Type  ad_SINT16Props_n32760_32760_0   = { -32760, 32760, 0 };
AD_UINT16Type  ad_UINT16Props_0_65535_0        = { 0, 65535, 0 };
AD_SINT32Type  ad_SINT32Props_n900K_900K_0     = { -900000, 900000, 0 };
AD_UINT32Type  ad_UINT32Props_0_0xFFFFFFFF_0   = { 0, 0xFFFFFFFF, 0 };
AD_FLOAT32Type ad_FLOAT32Props_n90p45_90p45_0  = { -90.45F, 90.45F, 0 };
AD_ENUMType    ad_ENUMProps_0_2_0_3STR = { 0, 2, 0, 3, ad_ENUMPropsString };

#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
AD_SINT64Type  ad_SINT64Props_n900K_900K_0            = { -900000, 900000, 0 };
AD_UINT64Type  ad_UINT64Props_0_0xFFFFFFFFFFFFFFFE_0  = { 0, 0xFFFFFFFFFFFFFFFE, 0 };
#endif


/*---------------------------------------------------------------------------------------------------------------------------------
** ADI instance allocation
**
** 1. iInstance               - ADI instance number (1-65535); 0 is reserved for Class
** 2. pabName                 - Name of ADI as an character string (ADI instance attribute #1)
**                              if NULL, an 0 length name will be returned
** 3. bDataType               - ADI data type format, can be one of the folowing:
**                               ABP_BOOL:    Boolean
**                               ABP_SINT8:   8-bit signed integer
**                               ABP_SINT16:  16-bit signed integer
**                               ABP_SINT32:  32-bit signed integer
**                               ABP_UINT8:   8-bit unsigned integer
**                               ABP_UINT16:  16-bit unsigned integer
**                               ABP_UINT32:  32-bit unsigned integer
**                               ABP_CHAR:    character
**                               ABP_ENUM:    Enumeration
**                               ABP_SINT64:  64-bit signed integer
**                               ABP_UINT64:  64-bit unsigned integer
**                               ABP_FLOAT:   floating point value (32-bits)
** 4. bNumOfElements          - Number of elements of the specified data type in (3)
** 5. bDesc                   - Entry descriptor; bits filed with the folllowing configurations:
**                               ABP_APPD_DESCR_GET_ACCESS:  Get service is allowed on value attribute
**                               ABP_APPD_DESCR_SET_ACCESS:  Set service is allowed on value attribute
** 6. pxValuePtr              - Pointer to local value variable
** 6. psValueProps            - Pointer to local value properties struct, if NULL no properties are applied (max/min/default)
**---------------------------------------------------------------------------------------------------------------------------------
** 1. iInstance   |  2. pabName   |  3. bDataType  |  4. bNumOfElements  |  5. bDesc   |  6. { { pxValuePtr, pxValuePropPtr } }
**---------------------------------------------------------------------------------------------------------------------------------
*/

    
AD_AdiEntryType AD_asADIEntryList[] =
{
/* Singe ADI types */
//INPUTS
    /* Idx:0 ADI1: UINT8/RO/INPUT*/       { 1, (UINT8 *)"Input Byte",               ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS,                             { { &AD_sADIValues.EIPStatus, NULL } } },
    /* Idx:1 ADI2: UINT8/RO/SUPPLY_FLOW*/ { 2, (UINT8 *)"Supply Flow",              ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS,                             { { &AD_sADIValues.EIPSupplyFlow, NULL } } },
    /* Idx:2 ADI3: UINT8/RO/RETURN_FLOW*/ { 3, (UINT8 *)"Return Flow",              ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS,                             { { &AD_sADIValues.EIPReturnFlow, NULL } } },
    /* Idx:3 ADI4: UINT8/RO/TEMPERATURE*/ { 4, (UINT8 *)"Water Temperature",        ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS,                             { { &AD_sADIValues.EIPTemperature, NULL } } },
//OUTPUTS
    /* Idx:4 ADI5: UINT8/RW/OUTPUT*/     { 5, (UINT8 *)"Output Byte",              ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.EIPOutput, &ad_UINT8Props_0_255_0 } } },
//Website use only
    /* Idx:5 ADI6: UINT8/RW/DISPLAY*/     { 6, (UINT8 *)"Under Temp",            ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webUnderTemp, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:6 ADI7: UINT16/RW/MinFlow*/     { 7, (UINT8 *)"Min Flow",                ABP_UINT16 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webMinFlow, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:7 ADI8: UINT16/RW/FlowOK*/      { 8, (UINT8 *)"Flow OK",                 ABP_UINT16 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webFlowOkay, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:8 ADI9: UINT16/RW/LeakRate*/    { 9, (UINT8 *)"Leak Rate",               ABP_UINT16 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webLeakRate, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:9 ADI10: UINT16/RW/OverTemp*/   { 10, (UINT8 *)"Over Temp",              ABP_UINT16 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webOverTemp, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:10 ADI11: UINT8/RW/ResponseTime*/{ 11, (UINT8 *)"Response Time",         ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webResponseTime, &ad_UINT8Props_0_255_0 } } },
    /* Idx:11 ADI12: UINT8/RW/Units*/     { 12, (UINT8 *)"Units",                   ABP_UINT8 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webUnits, &ad_UINT8Props_0_255_0 } } },
    /* Idx:12 ADI13: UINT16/RW/WebStatusByte*/{ 13, (UINT8 *)"Web Status",          ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webStatus, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:13 ADI14: UINT16/RW/FirmwareRev*/{ 14, (UINT8 *)"Firmware Revision",     ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webFirmwareRev, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:14 ADI15: UINT32/RW/SerialNum*/{ 15, (UINT8 *)"Serial Number",           ABP_UINT32, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webSerialNum, &ad_UINT32Props_0_0xFFFFFFFF_0 } } },
    /* Idx:15 ADI16: UINT16/RW/RestartTime*/{ 16, (UINT8 *)"Restart Time",          ABP_UINT16,  1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webRestartTime, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:16 ADI17: UINT16/RW/WebSupply*/{ 17, (UINT8 *)"Website Supply",          ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webSupplyFlow, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:17 ADI18: UINT16/RW/WebReturn*/{ 18, (UINT8 *)"Website Return",          ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webReturnFlow, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:18 ADI19: UINT16/RW/EIPStatusWord*/{ 19, (UINT8 *)"EIP Status Word",     ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webEIPStatus, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:19 ADI20: UINT16/RW/EIPCommandWord*/{ 20, (UINT8 *)"EIP Command Word",   ABP_UINT16, 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webEIPCommand, &ad_UINT16Props_0_65535_0 } } },
    /* Idx:20 ADI21: UINT8[4]/RW/IPAddressLocal*/{ 21, (UINT8 *)"Local IP Address", ABP_UINT8,  4, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webIPAddr, &ad_UINT8Props_0_255_0 } } },
    /* Idx:21 ADI22: UINT8[4]/RW/SMaskLocal*/{ 22, (UINT8 *)"Local Subnet Mask",    ABP_UINT8,  4, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webSubnetMask, &ad_UINT8Props_0_255_0 } } },
    /* Idx:22 ADI23: UINT16/RW/UnderTemp*/   { 23, (UINT8 *)"Venturi Time",           ABP_UINT16 , 1, ABP_APPD_DESCR_GET_ACCESS | ABP_APPD_DESCR_SET_ACCESS, { { &AD_sADIValues.webVenturiTime, &ad_UINT16Props_0_65535_0 } } },
};


/*-------------------------------------------------------------------------------------------------------
** ADI write process data mappings ( Application -> Anybus )
**
**-------------------------------------------------------------------------------------------------------
** Array of indexes entries in AD_asADIEntryList (Idx:xx) in native mapping order
** Note: Mapping sequence is terminated by index value 0xFFFF and MUST be present at end of LIST
**-------------------------------------------------------------------------------------------------------
*/

//UINT16 AD_aiPdWriteIndexDataMap1[] =
//{
//   0, 0xFFFF
//};

UINT16 AD_aiPdWriteIndexDataMap2[] =//EIP Status Word(2) - Input Byte(1) - Supply Flow(1) - Return Flow(1) - Water Temperature(1) = (6)
{
   0,1,2,3,0xFFFF                                                   // 6, 8, 10, 12, 14, 16, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 32, 34, 35, 0xFFFF	//modified for ADI list 3 R/W
};


/*-------------------------------------------------------------------------------------------------------
** ADI read process data mappings ( Anybus -> Application )
**
**-------------------------------------------------------------------------------------------------------
** Array of indexes entries in AD_asADIEntryList (Idx:xx) in native mapping order
** Note: Mapping sequence is terminated by index value 0xFFFF and MUST be present at end of LIST
**-------------------------------------------------------------------------------------------------------
*/

//UINT16 AD_aiPdReadIndexDataMap1[] =
//{
//   1,0xFFFF
//};
UINT16 AD_aiPdReadIndexDataMap2[] =//EIP Command Word(2) - Output Byte(2) = (4)
{
   4,0xFFFF                                                                      // 1, 2,3,4,0xFFFF// 4,0xFFFF//, 6, 8, 10, 12, 14, 16, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 32, 34, 35, 0xFFFF	//modified for ADI list 3 R/W
};


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
** AD_Init()
**------------------------------------------------------------------------------
*/

void AD_Init( void )
{
   UINT16 i;

   /*
   ** In this context we should initilaize the AD object
   ** to be prepared for startup.
   **
   ** The driver globals: AB_iModuleType and AB_iNetworkType
   ** are initlaized and can be used for AD object branding
   ** depening on connected module type
   */

   AD_iNumOfADIs = sizeof( AD_asADIEntryList ) / sizeof( AD_AdiEntryType );
   AD_iHighestInstanceNumber = 0;

   for( i = 0; i < AD_iNumOfADIs; i++ )
   {
      if( AD_asADIEntryList[ i ].iInstance > AD_iHighestInstanceNumber )
      {
         AD_iHighestInstanceNumber = AD_asADIEntryList[ i ].iInstance;
      }

      AD_asADIEntryList[ i ].bStatBits = 0;
   }

   /*
   ** Setup process data mapping pointers
   */

   switch( AB_iNetworkType )
   {
   case 0x009A: /* BACnet/IP */
      /*
      ** For BACnet we cannot have any read process data
      */
      //AD_paiPdReadMap   = NULL;
      //AD_paiPdWriteMap  = AD_aiPdWriteIndexDataMap1;
      break;
   case 0x009C: /* EtherNet/IP 2-Port */
      AD_paiPdReadMap   = AD_aiPdReadIndexDataMap2;
      AD_paiPdWriteMap  = AD_aiPdWriteIndexDataMap2;
      break;
   case 0x0093: /* Modbus/TCP 2-Port */
   default:
      AD_paiPdReadMap   = AD_aiPdReadIndexDataMap2;
      AD_paiPdWriteMap  = AD_aiPdWriteIndexDataMap2;
      break;
   }

   /*
   ** Reset ADI mapping processors
   */

   AD_MapNextAdiReadArea( NULL, TRUE );
   AD_MapNextAdiWriteArea( NULL, TRUE );

} /* end of AD_Init */

/*------------------------------------------------------------------------------
** AD_GetAdiInstEntry()
**------------------------------------------------------------------------------
*/

AD_AdiEntryType* AD_GetAdiInstEntry( UINT16 iInstance )
{
   UINT16 i;
   AD_AdiEntryType* psEntry = NULL;

   for( i = 0; i < sizeof( AD_asADIEntryList ) / sizeof( AD_AdiEntryType ); i++ )
   {
      if( AD_asADIEntryList[ i ].iInstance == iInstance )
      {
         psEntry = &AD_asADIEntryList[ i ];
         break;
      }
   }

   return( psEntry );
} /* end of AD_GetAdiInstEntry */


/*------------------------------------------------------------------------------
** AD_MapNextAdiReadArea()
**------------------------------------------------------------------------------
*/

BOOL8 AD_MapNextAdiReadArea( ABP_MsgType* psMsgBuffer, BOOL8 fReset )
{
   static UINT8 bNextMapIndex = 0;

   if( fReset )
   {
      bNextMapIndex = 0;
      AB_bPdReadSize = 0;
      return( FALSE );
   }

   if( ( AD_paiPdReadMap != NULL ) &&
       ( AD_paiPdReadMap[ bNextMapIndex ] != 0xFFFF ) )
   {
      psMsgBuffer->sHeader.bDestObj             = ABP_OBJ_NUM_NW;
      psMsgBuffer->sHeader.iInstance            = iTOiLe( 1 );
      psMsgBuffer->sHeader.bCmd                 = ABP_MSG_HEADER_C_BIT | ABP_NW_CMD_MAP_ADI_READ_AREA;
      psMsgBuffer->sHeader.bDataSize            = 4;
      *(UINT16*)&psMsgBuffer->sHeader.bCmdExt0  = iTOiLe( AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ].iInstance );  /* ADI Instance number */
      psMsgBuffer->abData[ 0 ]                  = AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ].bDataType;            /* ADI data type */
      psMsgBuffer->abData[ 1 ]                  = AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ].bNumOfElements;       /* Number of elemets in ADI */
      *(UINT16*)&psMsgBuffer->abData[ 2 ]       = iTOiLe( ( &AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ] - &AD_asADIEntryList[ 0 ] ) + 1 ); /* ADI order number */
      bControlReg                              |= ABP_CTRL_M_BIT;

      AB_bPdReadSize += ( AD_GetDataTypeSize( AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ].bDataType ) * AD_asADIEntryList[ AD_paiPdReadMap[ bNextMapIndex ] ].bNumOfElements );

      bNextMapIndex++;
      return( TRUE );
   }

   return( FALSE );

} /* end of AD_MapNextAdiReadArea */


/*------------------------------------------------------------------------------
** AD_MapNextAdiWriteArea()
**------------------------------------------------------------------------------
*/

BOOL8 AD_MapNextAdiWriteArea( ABP_MsgType* psMsgBuffer, BOOL8 fReset )
{
   static UINT8 bNextMapIndex = 0;

   if( fReset )
   {
      bNextMapIndex = 0;
      AB_bPdWriteSize = 0;
      return( FALSE );
   }

   if( ( AD_paiPdWriteMap != NULL ) &&
       ( AD_paiPdWriteMap[ bNextMapIndex ] != 0xFFFF ) )
   {
      psMsgBuffer->sHeader.bDestObj             = ABP_OBJ_NUM_NW;
      psMsgBuffer->sHeader.iInstance            = iTOiLe( 1 );
      psMsgBuffer->sHeader.bCmd                 = ABP_MSG_HEADER_C_BIT | ABP_NW_CMD_MAP_ADI_WRITE_AREA;
      psMsgBuffer->sHeader.bDataSize            = 4;
      *(UINT16*)&psMsgBuffer->sHeader.bCmdExt0  = iTOiLe( AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ].iInstance );  /* ADI Instance number */
      psMsgBuffer->abData[ 0 ]                  = AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ].bDataType;            /* ADI data type */
      psMsgBuffer->abData[ 1 ]                  = AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ].bNumOfElements;       /* Number of elemets in ADI */
      *(UINT16*)&psMsgBuffer->abData[ 2 ]       = iTOiLe( ( &AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ] - &AD_asADIEntryList[ 0 ] ) + 1 ); /* ADI order number */
      bControlReg                              |= ABP_CTRL_M_BIT;

      AB_bPdWriteSize += ( AD_GetDataTypeSize( AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ].bDataType ) * AD_asADIEntryList[ AD_paiPdWriteMap[ bNextMapIndex ] ].bNumOfElements );

      bNextMapIndex++;
      return( TRUE );
   }

   return( FALSE );

} /* end of AD_MapNextAdiWriteArea */


/*------------------------------------------------------------------------------
** AD_ProcNextUserInitCmd()
**------------------------------------------------------------------------------
*/

BOOL8 AD_ProcNextUserInitCmd( ABP_MsgType* psMsgBuffer )
{
   return( FALSE );
} /* en of AD_ProcNextUserInitCmd */

void AD_ProcUserInitResp( ABP_MsgType* psMsgBuffer )
{

} /* end of AD_ProcUserInitResp */


/*------------------------------------------------------------------------------
** AD_ProcObjectRequest()
**------------------------------------------------------------------------------
*/

void AD_ProcObjectRequest( ABP_MsgType* psMsgBuffer )
{
   AD_AdiEntryType* psAdiEntry;
   UINT16 iItemSize;

   if( iLeTOi( psMsgBuffer->sHeader.iInstance ) == ABP_INST_OBJ )
   {
      /* An request to the object instance */

      switch( psMsgBuffer->sHeader.bCmd & ABP_MSG_HEADER_CMD_BITS )
      {
      case ABP_CMD_GET_ATTR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_OA_NAME: /* Name */
            memcpy( psMsgBuffer->abData, "Application data", 16 );
            psMsgBuffer->sHeader.bDataSize = 16;
            break;

         case ABP_OA_REV: /* Revision */
            psMsgBuffer->abData[ 0 ] = 1;
            psMsgBuffer->sHeader.bDataSize = ABP_OA_REV_DS;
            break;

         case ABP_OA_NUM_INST: /* Number of instances */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( AD_iNumOfADIs );
            psMsgBuffer->sHeader.bDataSize = ABP_OA_NUM_INST_DS;
            break;

         case ABP_OA_HIGHEST_INST: /* Highest instance no. */
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( AD_iHighestInstanceNumber );
            psMsgBuffer->sHeader.bDataSize = ABP_OA_HIGHEST_INST_DS;
            break;

         default: /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;
      case ABP_APPD_CMD_GET_INST_BY_ORDER:
         if( ( iLeTOi( *(UINT16*)&psMsgBuffer->sHeader.bCmdExt0 ) == 0 ) ||
             ( iLeTOi( *(UINT16*)&psMsgBuffer->sHeader.bCmdExt0 ) > AD_iNumOfADIs ) )
         {
            /*
            ** Requested order number does not exist.
            */

            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
         }
         else
         {
            *(UINT16*)&psMsgBuffer->abData[ 0 ] = iTOiLe( AD_asADIEntryList[ iLeTOi( *(UINT16*)&psMsgBuffer->sHeader.bCmdExt0 ) - 1 ].iInstance );
            psMsgBuffer->sHeader.bDataSize = ABP_UINT16_SIZEOF;
         }
         break;
      default: /* Unsupported command */
         SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
         break;
      }
   }
   else if( ( psAdiEntry = AD_GetAdiInstEntry( iLeTOi( psMsgBuffer->sHeader.iInstance ) ) ) != NULL )
   {
      /* ADI instance found, now switch on command */

      switch( psMsgBuffer->sHeader.bCmd & ABP_MSG_HEADER_CMD_BITS )
      {
      case ABP_CMD_GET_ATTR:

         /* Switch on attribute */
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_APPD_IA_NAME: /* Instance name */
            if( psAdiEntry->pabName )
            {
               psMsgBuffer->sHeader.bDataSize = strlen( (const char *)psAdiEntry->pabName );
               memcpy( psMsgBuffer->abData, psAdiEntry->pabName, psMsgBuffer->sHeader.bDataSize );
            }
            else
            {
               psMsgBuffer->sHeader.bDataSize = 0;
            }
            break;

         case ABP_APPD_IA_DATA_TYPE: /* Data type */
            psMsgBuffer->abData[ 0 ] = psAdiEntry->bDataType;
            psMsgBuffer->sHeader.bDataSize = ABP_APPD_IA_DATA_TYPE_DS;
            break;

         case ABP_APPD_IA_NUM_ELEM: /* Number of elements */
            psMsgBuffer->abData[ 0 ] = psAdiEntry->bNumOfElements;
            psMsgBuffer->sHeader.bDataSize = ABP_APPD_IA_NUM_ELEM_DS;
            break;

         case ABP_APPD_IA_DESCRIPTOR: /* Descriptor */
            psMsgBuffer->abData[ 0 ] = psAdiEntry->bDesc;
            psMsgBuffer->sHeader.bDataSize = ABP_APPD_IA_DESCRIPTOR_DS;
            break;

         case ABP_APPD_IA_VALUE: /* Value */
            if( !( psAdiEntry->bDesc & ABP_APPD_DESCR_GET_ACCESS ) )
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_ATTR_NOT_GETABLE );
               break;
            }

            psMsgBuffer->sHeader.bDataSize = (UINT8)AD_GetAdiValue( psAdiEntry, &psMsgBuffer->abData[ 0 ] );
            break;

         case ABP_APPD_IA_MAX_VALUE:
         case ABP_APPD_IA_MIN_VALUE:
         case ABP_APPD_IA_DFLT_VALUE:
            if( psAdiEntry->uData.sUINT8.psValueProps )
            {
               switch( psAdiEntry->bDataType )
               {
               case ABP_BOOL:
               case ABP_CHAR:
               case ABP_UINT8:
               case ABP_SINT8:
               case ABP_ENUM:
                  switch( psMsgBuffer->sHeader.bCmdExt0 )
                  {
                  case ABP_APPD_IA_MAX_VALUE:
                     psMsgBuffer->abData[ 0 ] = psAdiEntry->uData.sUINT8.psValueProps->bMaxValue;
                     break;
                  case ABP_APPD_IA_MIN_VALUE:
                     psMsgBuffer->abData[ 0 ] = psAdiEntry->uData.sUINT8.psValueProps->bMinValue;
                     break;
                  default:
                     psMsgBuffer->abData[ 0 ] = psAdiEntry->uData.sUINT8.psValueProps->bDefaultValue;
                     break;
                  }

                  psMsgBuffer->sHeader.bDataSize = 1;
                  break;
               case ABP_UINT16:
               case ABP_SINT16:
                  switch( psMsgBuffer->sHeader.bCmdExt0 )
                  {
                  case ABP_APPD_IA_MAX_VALUE:
                     *(UINT16*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? iTOiBe( psAdiEntry->uData.sUINT16.psValueProps->iMaxValue ) : iTOiLe( psAdiEntry->uData.sUINT16.psValueProps->iMaxValue );
                     break;
                  case ABP_APPD_IA_MIN_VALUE:
                     *(UINT16*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? iTOiBe( psAdiEntry->uData.sUINT16.psValueProps->iMinValue ) : iTOiLe( psAdiEntry->uData.sUINT16.psValueProps->iMinValue );
                     break;
                  default:
                     *(UINT16*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? iTOiBe( psAdiEntry->uData.sUINT16.psValueProps->iDefaultValue ) : iTOiLe( psAdiEntry->uData.sUINT16.psValueProps->iDefaultValue );
                     break;
                  }

                  psMsgBuffer->sHeader.bDataSize = 2;
                  break;
               case ABP_UINT32:
               case ABP_SINT32:
               case ABP_FLOAT:
                  switch( psMsgBuffer->sHeader.bCmdExt0 )
                  {
                  case ABP_APPD_IA_MAX_VALUE:
                     *(UINT32*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe( psAdiEntry->uData.sUINT32.psValueProps->lMaxValue ) : lTOlLe( psAdiEntry->uData.sUINT32.psValueProps->lMaxValue );
                     break;
                  case ABP_APPD_IA_MIN_VALUE:
                     *(UINT32*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe( psAdiEntry->uData.sUINT32.psValueProps->lMinValue ) : lTOlLe( psAdiEntry->uData.sUINT32.psValueProps->lMinValue );
                     break;
                  default:
                     *(UINT32*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe( psAdiEntry->uData.sUINT32.psValueProps->lDefaultValue ) : lTOlLe( psAdiEntry->uData.sUINT32.psValueProps->lDefaultValue );
                     break;
                  }

                  psMsgBuffer->sHeader.bDataSize = 4;
                  break;
#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
               case ABP_UINT64:
               case ABP_SINT64:
                  switch( psMsgBuffer->sHeader.bCmdExt0 )
                  {
                  case ABP_APPD_IA_MAX_VALUE:
                     *(UINT64*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe64( psAdiEntry->uData.sUINT64.psValueProps->lMaxValue ) : lTOlLe64( psAdiEntry->uData.sUINT64.psValueProps->lMaxValue );
                     break;
                  case ABP_APPD_IA_MIN_VALUE:
                     *(UINT64*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe64( psAdiEntry->uData.sUINT64.psValueProps->lMinValue ) : lTOlLe64( psAdiEntry->uData.sUINT64.psValueProps->lMinValue );
                     break;
                  default:
                     *(UINT64*)&psMsgBuffer->abData[ 0 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe64( psAdiEntry->uData.sUINT64.psValueProps->lDefaultValue ) : lTOlLe64( psAdiEntry->uData.sUINT64.psValueProps->lDefaultValue );
                     break;
                  }

                  psMsgBuffer->sHeader.bDataSize = 8;
                  break;
#endif
               default:
                  while( 1 ); /* Trap: ADI type not supported */
                  break;
               }
            }
            else
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            }
            break;

         default: /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;
      case ABP_CMD_SET_ATTR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_APPD_IA_NAME:
         case ABP_APPD_IA_DATA_TYPE:
         case ABP_APPD_IA_NUM_ELEM:
         case ABP_APPD_IA_DESCRIPTOR: /* Attribues not settable */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_ATTR_NOT_SETABLE );
            break;
         case ABP_APPD_IA_VALUE:
            if( !( psAdiEntry->bDesc & ABP_APPD_DESCR_SET_ACCESS ) )
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_ATTR_NOT_SETABLE );
               break;
            }


            /* 1. Check array lengths */
            iItemSize = AD_GetDataTypeSize( psAdiEntry->bDataType );
            if( psMsgBuffer->sHeader.bDataSize > ( iItemSize * psAdiEntry->bNumOfElements ) )
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_TOO_MUCH_DATA );
               break;
            }
            else if( psMsgBuffer->sHeader.bDataSize < ( iItemSize * psAdiEntry->bNumOfElements ) )
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_NOT_ENOUGH_DATA );
               break;
            }

            if( AD_SetAdiValue( psAdiEntry, &psMsgBuffer->abData[ 0 ], FALSE ) == -1 )
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_OUT_OF_RANGE );
            }
            break;

         default: /* Unsupported attribute */
            SetMsgError( psMsgBuffer, 1, ABP_ERR_INV_CMD_EXT_0 );
            break;
         }
         break;
      case ABP_CMD_GET_ENUM_STR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         case ABP_APPD_IA_VALUE:
            if( psAdiEntry->bDataType == ABP_ENUM )
            {
               if( ( psAdiEntry->uData.sENUM.psValueProps == NULL ) ||
                   ( psAdiEntry->uData.sENUM.psValueProps->pasEnumStrings == NULL ) )
               {
                  SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
               }
               else
               {
                  UINT8 b = 0;

                  for( b = 0; b < psAdiEntry->uData.sENUM.psValueProps->bNumOfEnumStrings; b++ )
                  {
                     if( psAdiEntry->uData.sENUM.psValueProps->pasEnumStrings[ b ].eValue == psMsgBuffer->sHeader.bCmdExt1 )
                     {
                        break;
                     }
                  }

                  if( b < psAdiEntry->uData.sENUM.psValueProps->bNumOfEnumStrings )
                  {
                     psMsgBuffer->sHeader.bDataSize = strlen( (const char *)psAdiEntry->uData.sENUM.psValueProps->pasEnumStrings[ b ].abEnumStr );
                     memcpy( &psMsgBuffer->abData[ 0 ], psAdiEntry->uData.sENUM.psValueProps->pasEnumStrings[ b ].abEnumStr, psMsgBuffer->sHeader.bDataSize );
                  }
                  else
                  {
                     /*
                     ** Enum value not found in string lookup
                     */

                     SetMsgError( psMsgBuffer, 1, ABP_ERR_OUT_OF_RANGE );
                  }
               }
            }
            else
            {
               SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
            }
            break;
         default:
            SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
            break;
         }
         break;
      case ABP_CMD_GET_INDEXED_ATTR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         //case ABP_APPD_IA_VALUE:
         //   break;

         default:
            SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
            break;
         }
         break;
      case ABP_CMD_SET_INDEXED_ATTR:
         switch( psMsgBuffer->sHeader.bCmdExt0 )
         {
         //case ABP_APPD_IA_VALUE:
         //   break;

         default:
            SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
            break;
         }
         break;

      default: /* Unsupported command */
         SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_CMD );
         break;
      }
   }
   else
   {
      /* Instance not found */
      SetMsgError( psMsgBuffer, 1, ABP_ERR_UNSUP_INST );
   }

} /* end of AD_ProcObjectRequest */


/*------------------------------------------------------------------------------
** AD_GetDataTypeSize()
**------------------------------------------------------------------------------
*/

UINT8 AD_GetDataTypeSize( UINT8 bDataType )
{
   UINT8 bSize;

   switch( bDataType )
   {
   case ABP_BOOL:
   case ABP_CHAR:
   case ABP_UINT8:
   case ABP_ENUM:
   case ABP_SINT8:
      bSize = 1;
      break;
   case ABP_UINT16:
   case ABP_SINT16:
      bSize = 2;
      break;
   case ABP_UINT32:
   case ABP_SINT32:
   case ABP_FLOAT:
      bSize = 4;
      break;
#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
   case ABP_UINT64:
   case ABP_SINT64:
      bSize = 8;
      break;
#endif
   default:
      while(1); /* Trap */
      break;
   }

   return( bSize );

} /* end of AD_GetDataTypeSize */


/*------------------------------------------------------------------------------
** AD_GetAdiValue()
**------------------------------------------------------------------------------
*/

UINT16 AD_GetAdiValue( AD_AdiEntryType* psAdiEntry, UINT8* pabDataPtr )
{
   UINT16 i;
   UINT16 iSize = 0;

   switch( psAdiEntry->bDataType )
   {
   case ABP_BOOL:
   case ABP_CHAR:
   case ABP_UINT8:
   case ABP_SINT8:
   case ABP_ENUM:
      memcpy( pabDataPtr, psAdiEntry->uData.sUINT8.pbValuePtr, psAdiEntry->bNumOfElements );
      iSize = psAdiEntry->bNumOfElements;
      break;
   case ABP_SINT16:
   case ABP_UINT16:
      for( i = 0; i < psAdiEntry->bNumOfElements; i++ )
      {
         iSize += 2;
//         temp = (UINT8*)pabDataPtr; //temp2 = (UINT8)psAdiEntry->uData.sUINT16.piValuePtr[ i ];
         *pabDataPtr = (UINT8)psAdiEntry->uData.sUINT16.piValuePtr[ i ];
         pabDataPtr++;
         *pabDataPtr = (UINT8)(psAdiEntry->uData.sUINT16.piValuePtr[ i ]>>8);
//         memcpy(&temp, &temp2, 2);
//         *temp = *temp2;
//         temp++; temp2++;
//         memcpy(&temp, &temp2, 1);
//         *&pabDataPtr[ i*2 ] = ( eNetFormat == NET_BIGENDIAN ) ? iTOiBe( psAdiEntry->uData.sUINT16.piValuePtr[ i ] ) : iTOiLe( psAdiEntry->uData.sUINT16.piValuePtr[ i ] );
      }
      break;
   case ABP_UINT32:
   case ABP_SINT32:
   case ABP_FLOAT:
      for( i = 0; i < psAdiEntry->bNumOfElements; i++ )
      {
         iSize += 4;
//         *&pabDataPtr[ i*4 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe( psAdiEntry->uData.sUINT32.plValuePtr[ i ] ) : lTOlLe( psAdiEntry->uData.sUINT32.plValuePtr[ i ] );
         *pabDataPtr = (UINT8)psAdiEntry->uData.sUINT32.plValuePtr[ i ];
         pabDataPtr++;
         *pabDataPtr = (UINT8)(psAdiEntry->uData.sUINT32.plValuePtr[ i ]>>8);
         pabDataPtr++;
         *pabDataPtr = (UINT8)(psAdiEntry->uData.sUINT32.plValuePtr[ i ]>>16);
         pabDataPtr++;
         *pabDataPtr = (UINT8)(psAdiEntry->uData.sUINT32.plValuePtr[ i ]>>24);
      }
      break;
#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
   case ABP_UINT64:
   case ABP_SINT64:
      for( i = 0; i < psAdiEntry->bNumOfElements; i++ )
      {
         iSize += 8;
         *(UINT64*)&pabDataPtr[ i*8 ] = ( eNetFormat == NET_BIGENDIAN ) ? lTOlBe64( psAdiEntry->uData.sUINT64.plValuePtr[ i ] ) : lTOlLe64( psAdiEntry->uData.sUINT64.plValuePtr[ i ] );
      }
      break;
#endif
   default:
      while( 1 ); /* Trap: Unknown data type */
      break;
   }

   return( iSize );

} /* end of AD_GetAdiValue */


/*------------------------------------------------------------------------------
** AD_SetAdiValue()
**------------------------------------------------------------------------------
*/

SINT16 AD_SetAdiValue( AD_AdiEntryType* psAdiEntry, UINT8* pabDataPtr, BOOL8 fPdRead )
{
   BOOL8 fCheckFailed = FALSE;
   SINT16 iSetSize = -1;
   UINT16 i;

//   union
//   {
//      UINT16 iValue;
//      SINT16 iSignedValue;
//      UINT32 lValue;
//      SINT32 lSignedValue;
//      float  rValue;
//#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
//      UINT64 l64Value;
//      SINT64 l64SignedValue;
//#endif
//   } sValue;

   if( psAdiEntry->uData.sUINT8.psValueProps )
   {
      /* 2. Check array max/min limits */
      for( i = 0; i < psAdiEntry->bNumOfElements; i++ )
      {
//         switch( psAdiEntry->bDataType )
//         {
//         case ABP_BOOL:
//         case ABP_CHAR:
//         case ABP_UINT8:
//         case ABP_ENUM:
//            if( ( *(UINT8*)&pabDataPtr[ i ] > psAdiEntry->uData.sUINT8.psValueProps->bMaxValue ) ||
//                ( *(UINT8*)&pabDataPtr[ i ] < psAdiEntry->uData.sUINT8.psValueProps->bMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_SINT8:
//            if( ( *(SINT8*)&pabDataPtr[ i ] > psAdiEntry->uData.sSINT8.psValueProps->bMaxValue ) ||
//                ( *(SINT8*)&pabDataPtr[ i ] < psAdiEntry->uData.sSINT8.psValueProps->bMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//
//         case ABP_UINT16:
//            sValue.iValue = ( eNetFormat == NET_BIGENDIAN ) ? iBeTOi( *(UINT16*)&pabDataPtr[ i*2 ] ) : iLeTOi( *(UINT16*)&pabDataPtr[ i*2 ] );
//
//            if( ( sValue.iValue > psAdiEntry->uData.sUINT16.psValueProps->iMaxValue ) ||
//                ( sValue.iValue < psAdiEntry->uData.sUINT16.psValueProps->iMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_SINT16:
//            sValue.iValue = ( eNetFormat == NET_BIGENDIAN ) ? iBeTOi( *(UINT16*)&pabDataPtr[ i*2 ] ) : iLeTOi( *(UINT16*)&pabDataPtr[ i*2 ] );
//
//            if( ( sValue.iSignedValue > psAdiEntry->uData.sSINT16.psValueProps->iMaxValue ) ||
//                ( sValue.iSignedValue < psAdiEntry->uData.sSINT16.psValueProps->iMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_UINT32:
//            sValue.lValue = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl( *(UINT32*)&pabDataPtr[ i*4 ] ) : lLeTOl( *(UINT32*)&pabDataPtr[ i*4 ] );
//
//            if( ( sValue.lValue > psAdiEntry->uData.sUINT32.psValueProps->lMaxValue ) ||
//                ( sValue.lValue < psAdiEntry->uData.sUINT32.psValueProps->lMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_SINT32:
//            sValue.lValue = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl( *(UINT32*)&pabDataPtr[ i*4 ] ) : lLeTOl( *(UINT32*)&pabDataPtr[ i*4 ] );
//
//            if( ( sValue.lSignedValue > psAdiEntry->uData.sSINT32.psValueProps->lMaxValue ) ||
//                ( sValue.lSignedValue < psAdiEntry->uData.sSINT32.psValueProps->lMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_FLOAT:
//            sValue.lValue = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl( *(UINT32*)&pabDataPtr[ i*4 ] ) : lLeTOl( *(UINT32*)&pabDataPtr[ i*4 ] );
//
//            if( ( sValue.rValue > psAdiEntry->uData.sFLOAT.psValueProps->rMaxValue ) ||
//                ( sValue.rValue < psAdiEntry->uData.sFLOAT.psValueProps->rMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
//         case ABP_UINT64:
//            sValue.l64Value = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] ) : lLeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] );
//
//            if( ( sValue.l64Value > psAdiEntry->uData.sUINT64.psValueProps->lMaxValue ) ||
//                ( sValue.l64Value < psAdiEntry->uData.sUINT64.psValueProps->lMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//         case ABP_SINT64:
//            sValue.l64Value = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] ) : lLeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] );
//
//            if( ( sValue.l64SignedValue > psAdiEntry->uData.sSINT64.psValueProps->lMaxValue ) ||
//                ( sValue.l64SignedValue < psAdiEntry->uData.sSINT64.psValueProps->lMinValue ) )
//            {
//               fCheckFailed = TRUE;
//            }
//            break;
//#endif
//         }

         if( fCheckFailed )
         {
            break;
         }
      }
   }

   /*
   ** Update set size
   */

   iSetSize = ( AD_GetDataTypeSize( psAdiEntry->bDataType ) * psAdiEntry->bNumOfElements );

   if( !fCheckFailed )
   {
      /* 3. Copy data to local memory */
       UINT8* temp;
      for( i = 0; i < psAdiEntry->bNumOfElements; i++ )
      {
         switch( psAdiEntry->bDataType )
         {
         case ABP_BOOL:
         case ABP_CHAR:
         case ABP_UINT8:
         case ABP_SINT8:
         case ABP_ENUM:
            psAdiEntry->uData.sUINT8.pbValuePtr[ i ] = pabDataPtr[ i ];
            break;
         case ABP_UINT16:
         case ABP_SINT16:
             temp = (UINT8*)&psAdiEntry->uData.sUINT16.piValuePtr[ i ];
//            psAdiEntry->uData.sUINT16.piValuePtr[ i ] = ( eNetFormat == NET_BIGENDIAN ) ?
//                iBeTOi( *&pabDataPtr[ i*2 ] ) :
//                iLeTOi( *&pabDataPtr[ i*2 ] );
             *temp = *&pabDataPtr[ i*2 ];
             temp++;
             *temp = *&pabDataPtr[ ((i*2)+1) ];
            break;
         case ABP_UINT32:
         case ABP_SINT32:
         case ABP_FLOAT:
//            psAdiEntry->uData.sUINT32.plValuePtr[ i ] = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl( *&pabDataPtr[ i*4 ] ) : lLeTOl( *&pabDataPtr[ i*4 ] );
             *temp = *&pabDataPtr[ i*2 ];
             temp++;
             *temp = *&pabDataPtr[ ((i*2)+1) ];
             temp++;
             *temp = *&pabDataPtr[ ((i*2)+2) ];
             temp++;
             *temp = *&pabDataPtr[ ((i*2)+3) ];
            break;
#ifdef AB_ENABLE_64BIT_ADI_SUPPORT
         case ABP_UINT64:
         case ABP_SINT64:
            psAdiEntry->uData.sUINT64.plValuePtr[ i ] = ( eNetFormat == NET_BIGENDIAN ) ? lBeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] ) : lLeTOl64( *(UINT64*)&pabDataPtr[ i*8 ] );
            break;
#endif
         default:
            while( 1 ); /* Trap: Unknown data type */
            break;

         }
      }

      if( fPdRead )
      {
         psAdiEntry->bStatBits &= ~AD_STATBIT_PD_READ_LIMIT_ERROR;
      }
   }
   else if( fPdRead )
   {
      psAdiEntry->bStatBits |= AD_STATBIT_PD_READ_LIMIT_ERROR;
   }
   else
   {
      iSetSize = -1; /* Indicate error */
   }

   return( iSetSize );

} /* end of AD_SetAdiValue */


/*------------------------------------------------------------------------------
** AD_UpdatePdReadData()
**------------------------------------------------------------------------------
*/

void AD_UpdatePdReadData( UINT8* pabPdDataBuf )
{
   UINT16 i;
   BOOL8 fPdReadLimitError = FALSE;

   if( AD_paiPdReadMap )
   {
      i = 0;
      while( AD_paiPdReadMap[ i ] != 0xFFFF )
      {
         pabPdDataBuf += AD_SetAdiValue( &AD_asADIEntryList[ AD_paiPdReadMap[ i ] ], pabPdDataBuf, TRUE );

         if( AD_asADIEntryList[ AD_paiPdReadMap[ i ] ].bStatBits & AD_STATBIT_PD_READ_LIMIT_ERROR )
         {
            fPdReadLimitError = TRUE;
         }

         i++;
      }
   }

   AD_fHasPdReadDataLimitError = fPdReadLimitError;

} /* end of AD_UpdatePdReadData */


/*------------------------------------------------------------------------------
** AD_UpdatePdWriteData()
**------------------------------------------------------------------------------
*/

void AD_UpdatePdWriteData( UINT8* pabPdDataBuf )
{
   UINT16 i;

//   pabPdDataBuf=&abTxBuffer[ 17 ];
   if( AD_paiPdWriteMap )
   {
      i = 0;
      while( AD_paiPdWriteMap[ i ] != 0xFFFF )
      {
         pabPdDataBuf += AD_GetAdiValue( &AD_asADIEntryList[ AD_paiPdWriteMap[ i ] ], pabPdDataBuf );
         i++;
      }
   }

} /* end of AD_UpdatePdWriteData */

void EIP_SetRobotInputs(UINT8 status, UINT8 supply, UINT8 returnFlow, UINT8 temp) {
    AD_sADIValues.EIPStatus = status;
    AD_sADIValues.EIPSupplyFlow = supply;
    AD_sADIValues.EIPReturnFlow = returnFlow;
    AD_sADIValues.EIPTemperature = temp;
}

unsigned short EIP_GetCommand(void) {
    return AD_sADIValues.EIPOutput;
}


void Web_SetActiveData(UINT16 WebStatus, UINT16 WebSupply,UINT16 WebReturn) {
    AD_sADIValues.webStatus = iTOiBe(WebStatus);//Web Status
    AD_sADIValues.webSupplyFlow = iTOiBe(WebSupply);//Web Supply
    AD_sADIValues.webReturnFlow = iTOiBe(WebReturn);//Web Return
}

void Web_SetWebValues(__WebValues__ *v) {
    UINT8 i;
    
    // Unlike EIP , in Profinet bytes are reversed for value with more than 1 byte size 
    AD_sADIValues.webMinFlow = iTOiBe(v->minFlow);
    AD_sADIValues.webFlowOkay = iTOiBe(v->flowOkay);
    AD_sADIValues.webLeakRate = iTOiBe(v->leakRate);
    AD_sADIValues.webOverTemp = iTOiBe(v->overTemp);
    AD_sADIValues.webResponseTime = v->responseTime;
    AD_sADIValues.webUnits = v->unit;
    AD_sADIValues.webStatus = iTOiBe(v->webStatus);
    AD_sADIValues.webFirmwareRev = iTOiBe(v->firmwareRev);
    AD_sADIValues.webSerialNum = lBeTOl(v->serialNumber);
    AD_sADIValues.webRestartTime = iTOiBe(v->restartTime);
    AD_sADIValues.webSupplyFlow = iTOiBe(v->webSupply);
    AD_sADIValues.webReturnFlow = iTOiBe(v->webReturn);
    AD_sADIValues.webEIPStatus = iTOiBe(v->EIPStatus);
    AD_sADIValues.webEIPCommand = iTOiBe(v->EIPCommand);    
    AD_sADIValues.webVenturiTime = iTOiBe(v->venturiTime);
    AD_sADIValues.webUnderTemp = iTOiBe(v->underTemp);
    
    for (i = 0; i < 4; i++) {
       AD_sADIValues.webIPAddr[i] = v->IPAddress[i];
       AD_sADIValues.webSubnetMask[i] = v->SMask[i]; 
    }
}

void Web_GetWebValues(__WebValues__ *v) { 
    UINT8 i;    

    // Unlike EIP , in Profinet bytes are reversed for value with more than 1 byte size 
    v->EIPCommand = iTOiBe(AD_sADIValues.webEIPCommand);
    v->EIPStatus = iTOiBe(AD_sADIValues.webEIPStatus);
    for (i = 0; i < 4; i++) {
        v->IPAddress[i] = AD_sADIValues.webIPAddr[i];
        v->SMask[i] = AD_sADIValues.webSubnetMask[i];
    }
    v->venturiTime = iTOiBe(AD_sADIValues.webVenturiTime);
    v->flowOkay = iTOiBe(AD_sADIValues.webFlowOkay);
    v->leakRate = iTOiBe(AD_sADIValues.webLeakRate);
    v->minFlow = iTOiBe(AD_sADIValues.webMinFlow);
    v->unit = AD_sADIValues.webUnits;
    v->webReturn = iTOiBe(AD_sADIValues.webReturnFlow);
    v->webSupply = iTOiBe(AD_sADIValues.webSupplyFlow);
    v->overTemp = iTOiBe(AD_sADIValues.webOverTemp);
    v->responseTime = AD_sADIValues.webResponseTime;
    v->restartTime = iTOiBe(AD_sADIValues.webRestartTime);
    v->webStatus = iTOiBe(AD_sADIValues.webStatus);
    v->underTemp = iTOiBe(AD_sADIValues.webUnderTemp);
}


/*******************************************************************************
**
** End of ad_obj.c
**
********************************************************************************
*/
