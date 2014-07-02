/**
 * \file   Test_Profiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Debug/Profiler.h>
//-------------------------------------------------------------------------------------------------
class Test_Profiler :
    public UnitTest
{
public:
                   Test_Profiler() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

