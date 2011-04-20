/**********************************************************************
*	 ласс CYug_SmartCard (CYug_SmartCard.h)
*
***********************************************************************/


#ifndef CYug_SmartCardH
#define CYug_SmartCardH       
//---------------------------------------------------------------------------
#include "Include SDK 4.53\pkcs11.h"
#include "Include SDK 4.53\eTSAPI.h"
#include "Include SDK 4.53\otp-pkcs11.h"

#include <stdio.h>
#include <stdlib.h>
#include <winscard.h>   //vEnumReaderList
#include <wincrypt.h>   //vEnumReaderList
#include <iostream>     //STL vEnumReaderList
#include <iomanip>      //STL vEnumReaderList
#include <vector>       //STL vEnumReaderList

//--#include <system.hpp>   //AnsiString
//--#include <Classes.hpp>  //TStringList
//---------------------------------------------------------------------------
#define DEBUG_(MSG)       MessageBox(0, AnsiString(MSG).c_str(), "Debug", MB_OK)
#define MSG_WARNING(MSG)  MessageBox(0, AnsiString(MSG).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP        + MB_TOPMOST)
#define MSG_INFO(MSG)     MessageBox(0, AnsiString(MSG).c_str(), Application->Title.c_str(), MB_OK + MB_ICONINFORMATION + MB_TOPMOST)

#define APPLICATION_TITLE "eToken"
#define LOG_FILE          "___Log.txt"
#define EMPTY_MSG         "=отсутствует\n"
#define ETPKCS11_PATH     "DLL\\eTPKCS11.dll"	//путь к eTPKCS11.dll
#define ETSAPI_PATH       "DLL\\eTSAPI.dll"     //путь к eTSAPI.dll
#define TRUE_MSG          "да"
#define FALSE_MSG         "нет"
#define TOKEN_NON_PRESENT  - 1
//---------------------------------------------------------------------------
class CYug_SmartCard : public CXNonCopyable {
	public:
	    /*+*/CYug_SmartCard();
		/*+*/~CYug_SmartCard();
		
        TStringList   *vEnumReaderList();
		AnsiString     asSmartCardErrorString(DWORD dwRV);
        
    private:
 
};
//---------------------------------------------------------------------------
#endif