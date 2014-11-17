/**
 * \file   Test_Test.h
 * \brief  test Test
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_Test :
    public Unit
    ///< tests for Test
{
public:
                   Test_Test() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
