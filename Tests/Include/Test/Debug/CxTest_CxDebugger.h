/**
 * \file   CxTest_CxDebugger.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxDebugger.h>
//------------------------------------------------------------------------------
class CxTest_CxDebugger :
    public CxTest
{
public:
                   CxTest_CxDebugger();
    virtual       ~CxTest_CxDebugger();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

