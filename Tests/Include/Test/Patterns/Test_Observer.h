/**
 * \file   Test_Observer.h
 * \brief  test Observer
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Patterns/Observer.h>
//-------------------------------------------------------------------------------------------------
class Test_Observer :
    public UnitTest
    ///< tests for Observer
{
public:
                   Test_Observer() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
