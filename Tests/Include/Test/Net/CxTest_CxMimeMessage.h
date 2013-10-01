/**
 * \file   CxTest_CxMimeMessage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Net/CxPop3.h>
#include <xLib/Net/CxSmtp.h>
#include <xLib/Net/CxMimeHeader.h>
//------------------------------------------------------------------------------
#if xOPENSSL_IS_USE

class CxTest_CxMimeMessage :
    public CxTest
{
public:
                   CxTest_CxMimeMessage();
    virtual       ~CxTest_CxMimeMessage();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
