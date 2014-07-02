/**
 * \file   Test_Raii.h
 * \brief  test Raii
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Patterns/Raii.h>
//-------------------------------------------------------------------------------------------------
class Test_Raii :
    public Test
    ///< tests for Raii
{
public:
                   Test_Raii() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
