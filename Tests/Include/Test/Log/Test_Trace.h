/**
 * \file   Test_Trace.h
 * \brief  test Trace
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Log/Trace.h>
//-------------------------------------------------------------------------------------------------
class Test_Trace :
    public Test
{
public:
                   Test_Trace() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
