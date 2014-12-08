/**
 * \file   Test_MimeMessage.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

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
