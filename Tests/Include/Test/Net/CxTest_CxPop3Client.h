/**
 * \file   CxTest_CxPop3Client.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxPop3Client.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class CxTest_CxPop3Client :
    public CxTest
{
public:
                   CxTest_CxPop3Client() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
