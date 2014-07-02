/**
 * \file   Test_Observer.h
 * \brief  test Observer
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Patterns/Observer.h>
//-------------------------------------------------------------------------------------------------
class Test_Observer :
    public Test
    ///< tests for Observer
{
public:
                   Test_Observer() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
