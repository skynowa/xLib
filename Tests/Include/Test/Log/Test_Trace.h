/**
 * \file   Test_Trace.h
 * \brief  test Trace
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Log/Trace.h>
//-------------------------------------------------------------------------------------------------
class Test_Trace :
    public Unit
{
public:
                   Test_Trace() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
