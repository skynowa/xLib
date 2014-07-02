/**
 * \file   Test_xTest.h
 * \brief  test xTest
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Test/xTest.h>
//-------------------------------------------------------------------------------------------------
class Test_xTest :
    public Test
    ///< tests for xTest
{
public:
                   Test_xTest() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
