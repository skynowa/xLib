/**
 * \file  All.h
 * \brief all Pkcs11 classes
 */


#pragma once

#include <xLib/Core/xCore.h>

#if xOS_ENV_WIN
    #include <xLib/Crypt/Pkcs11/Core.h>

    #include <xLib/Crypt/Pkcs11/CxPkcs11.h>
    #include <xLib/Crypt/Pkcs11/CxFunction.h>
    #include <xLib/Crypt/Pkcs11/CxSlot.h>
    #include <xLib/Crypt/Pkcs11/CxSession.h>
    #include <xLib/Crypt/Pkcs11/CxLogin.h>
    #include <xLib/Crypt/Pkcs11/CxInfo.h>

    // TODO: CxeTokenInfo.h
    #if xTODO
        #include <xLib/Crypt/Pkcs11/CxeTokenInfo.h>
    #endif

    #include <xLib/Crypt/Pkcs11/CxPin.h>
    #include <xLib/Crypt/Pkcs11/CxMechanism.h>
    #include <xLib/Crypt/Pkcs11/CxObject.h>
    #include <xLib/Crypt/Pkcs11/CxKey.h>
    #include <xLib/Crypt/Pkcs11/CxEncrypt.h>
    #include <xLib/Crypt/Pkcs11/CxDecrypt.h>
    #include <xLib/Crypt/Pkcs11/CxDigest.h>
    #include <xLib/Crypt/Pkcs11/CxSign.h>
    #include <xLib/Crypt/Pkcs11/CxVerify.h>
#endif
