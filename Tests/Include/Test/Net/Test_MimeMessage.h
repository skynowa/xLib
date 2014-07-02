/**
 * \file   Test_MimeMessage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Net/MimeMessage.h>
#include <xLib/Net/Pop3Client.h>
#include <xLib/Net/SmtpClient.h>
#include <xLib/Net/MimeHeader.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class Test_MimeMessage :
    public Test
{
public:
                   Test_MimeMessage() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
