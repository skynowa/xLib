/**
 * \file   Test_AutoReset.h
 * \brief  test AutoReset
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/AutoReset.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoReset :
    public UnitTest
    ///< tests for AutoReset
{
public:
                   Test_AutoReset() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
