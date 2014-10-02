/**
 * \file   Test_Application.h
 * \brief  test Application
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/Application.h>
//-------------------------------------------------------------------------------------------------
class Test_Application :
    public UnitTest
    ///< tests for Application
{
public:
                   Test_Application() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
