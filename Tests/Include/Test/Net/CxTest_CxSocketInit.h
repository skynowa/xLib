/**
 * \file   CxTest_CxSocketInit.h
 * \brief
 */


#pragma once

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxSocketInit :
    public CxTest
{
public:
                   CxTest_CxSocketInit();
    virtual       ~CxTest_CxSocketInit();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
