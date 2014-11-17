/**
 * \file   Test_Application.h
 * \brief  test Application
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/Application.h>
//-------------------------------------------------------------------------------------------------
class Test_Application :
    public Unit
    ///< tests for Application
{
public:
                   Test_Application() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
