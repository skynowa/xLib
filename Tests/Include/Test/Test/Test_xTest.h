/**
 * \file   Test_xTest.h
 * \brief  test Test
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_xTest :
    public UnitTest
    ///< tests for Test
{
public:
                   Test_xTest() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
