/**
 * \file   Test_AutoProfiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/AutoProfiler.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoProfiler :
    public UnitTest
{
public:
                   Test_AutoProfiler() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
