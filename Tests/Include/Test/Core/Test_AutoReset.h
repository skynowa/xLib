/**
 * \file   Test_AutoReset.h
 * \brief  test AutoReset
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/AutoReset.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoReset :
    public Test
    ///< tests for AutoReset
{
public:
                   Test_AutoReset() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
