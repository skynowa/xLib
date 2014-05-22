/**
 * \file   CxTest_CxMimeMessage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Net/CxPop3Client.h>
#include <xLib/Net/CxSmtpClient.h>
#include <xLib/Net/CxMimeHeader.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class CxTest_CxMimeMessage :
    public CxTest
{
public:
                   CxTest_CxMimeMessage() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
