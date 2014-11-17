/**
 * \file   Test_MimeMessage.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Net/MimeMessage.h>
#include <xLib/Net/Pop3Client.h>
#include <xLib/Net/SmtpClient.h>
#include <xLib/Net/MimeHeader.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class Test_MimeMessage :
    public Unit
{
public:
                   Test_MimeMessage() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
