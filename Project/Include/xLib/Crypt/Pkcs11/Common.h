/**
 * \file  Common.h
 * \brief all SDK headers
 */


#ifndef xLib_Pkcs11_CommonH
#define xLib_Pkcs11_CommonH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN
    #include "SDK/4.53/pkcs11.h"
    #include "SDK/4.53/eTSAPI.h"
    #include "SDK/4.53/otp-pkcs11.h"
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CommonH
