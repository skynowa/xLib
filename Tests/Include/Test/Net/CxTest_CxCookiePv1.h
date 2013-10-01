/**
 * \file   CxTest_CxCookiePv1.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxCookiePv1.h>
//------------------------------------------------------------------------------
class CxTest_CxCookiePv1 :
    public CxTest
{
public:
                   CxTest_CxCookiePv1();
    virtual       ~CxTest_CxCookiePv1();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
