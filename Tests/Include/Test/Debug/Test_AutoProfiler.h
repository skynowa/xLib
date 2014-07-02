/**
 * \file   Test_AutoProfiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/AutoProfiler.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoProfiler :
    public Test
{
public:
                   Test_AutoProfiler() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
