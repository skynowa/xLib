/**
 * \file  All.h
 * \brief all Pkcs11 classes
 */


#ifndef xLib_Pkcs11_AllH
#define xLib_Pkcs11_AllH
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
    #include <xLib/Crypt/Pkcs11/Win/Common.h>

    #include <xLib/Crypt/Pkcs11/Win/CxUtils.h>
    #include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
    #include <xLib/Crypt/Pkcs11/Win/CxFunction.h>
    #include <xLib/Crypt/Pkcs11/Win/CxSlot.h>
    #include <xLib/Crypt/Pkcs11/Win/CxSession.h>
    #include <xLib/Crypt/Pkcs11/Win/CxLogin.h>
    #include <xLib/Crypt/Pkcs11/Win/CxInfo.h>
    #if xTODO
        #include <xLib/Crypt/Pkcs11/Win/CxeTokenInfo.h>
    #endif
    #include <xLib/Crypt/Pkcs11/Win/CxPin.h>
    #include <xLib/Crypt/Pkcs11/Win/CxMechanism.h>
    #include <xLib/Crypt/Pkcs11/Win/CxObject.h>
    #include <xLib/Crypt/Pkcs11/Win/CxKey.h>
    #include <xLib/Crypt/Pkcs11/Win/CxEncrypt.h>
    #include <xLib/Crypt/Pkcs11/Win/CxDecrypt.h>
    #include <xLib/Crypt/Pkcs11/Win/CxDigest.h>
    #include <xLib/Crypt/Pkcs11/Win/CxSign.h>
    #include <xLib/Crypt/Pkcs11/Win/CxVerify.h>
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_AllH
