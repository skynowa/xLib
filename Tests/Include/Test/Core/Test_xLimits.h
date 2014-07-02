/**
 * \file   Test_xLimits.h
 * \brief  test xLimits
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/xLimits.h>
//-------------------------------------------------------------------------------------------------
class Test_xLimits :
    public Test
    ///< tests for xLimits
{
public:
                   Test_xLimits() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
