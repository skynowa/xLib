/**
 * \file   Test_Blowfish.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Crypt/OpenSSL/Blowfish.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class Test_Blowfish :
    public Test
{
public:
                   Test_Blowfish() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
