/**
 * \file   Test_Profiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Profiler.h>
//-------------------------------------------------------------------------------------------------
class Test_Profiler :
    public Test
{
public:
                   Test_Profiler() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

