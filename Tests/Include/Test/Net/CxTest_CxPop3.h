/**
 * \file   CxTest_CxPop3.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxPop3.h>
//------------------------------------------------------------------------------
#if xOPENSSL_IS_USE

class CxTest_CxPop3 :
    public CxTest
{
public:
                   CxTest_CxPop3();
    virtual       ~CxTest_CxPop3();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
