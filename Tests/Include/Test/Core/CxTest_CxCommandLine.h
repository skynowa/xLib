/**
 * \file   CxTest_CxCommandLine.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxCommandLine.h>
//------------------------------------------------------------------------------
class CxTest_CxCommandLine :
    public CxTest
{
public:
                   CxTest_CxCommandLine();
    virtual       ~CxTest_CxCommandLine();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
