/**
 * \file  Common.h
 * \brief all SDK headers
 */


#ifndef xLib_Pkcs11_CommonH
#define xLib_Pkcs11_CommonH
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
    #include "SDK/SDK 4.53/pkcs11.h"
    #include "SDK/SDK 4.53/eTSAPI.h"
    #include "SDK/SDK 4.53/otp-pkcs11.h"
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CommonH
