/**
 * \file   Test_StackTrace.h
 * \brief  test StackTrace
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/StackTrace.h>
//-------------------------------------------------------------------------------------------------
class Test_StackTrace :
    public Unit
{
public:
                   Test_StackTrace() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

