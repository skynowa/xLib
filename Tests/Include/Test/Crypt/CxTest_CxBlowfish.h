/**
 * \file   CxTest_CxBlowfish.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class CxTest_CxBlowfish :
    public CxTest
{
public:
                   CxTest_CxBlowfish() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
