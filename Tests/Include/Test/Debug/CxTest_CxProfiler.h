/**
 * \file   CxTest_CxProfiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxProfiler.h>
//------------------------------------------------------------------------------
class CxTest_CxProfiler :
    public CxTest
{
public:
                   CxTest_CxProfiler();
    virtual       ~CxTest_CxProfiler();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

