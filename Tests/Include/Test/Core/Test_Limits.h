/**
 * \file   Test_Limits.h
 * \brief  test Limits
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/Limits.h>
//-------------------------------------------------------------------------------------------------
class Test_Limits :
    public Unit
    ///< tests for Limits
{
public:
                   Test_Limits() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
