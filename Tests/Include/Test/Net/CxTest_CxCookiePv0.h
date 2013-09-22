/**
 * \file   CxTest_CxCookiePv0.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxCookiePv0.h>
//------------------------------------------------------------------------------
class CxTest_CxCookiePv0 :
    public CxTest
{
public:
                   CxTest_CxCookiePv0();
    virtual       ~CxTest_CxCookiePv0();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
