/**
 * \file   Test_Flags.h
 * \brief  test Flags
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/Flags.h>
//-------------------------------------------------------------------------------------------------
class Test_Flags :
    public Test
    ///< tests for Flags
{
public:
                   Test_Flags() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
