/**
 * \file   Test_StackTrace.h
 * \brief  test StackTrace
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/StackTrace.h>
//-------------------------------------------------------------------------------------------------
class Test_StackTrace :
    public UnitTest
{
public:
                   Test_StackTrace() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

