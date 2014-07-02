/**
 * \file   Test_BuildInfo.h
 * \brief  test BuildInfo
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Debug/BuildInfo.h>
//---------------------------------------------------------------------------
class Test_BuildInfo :
    public UnitTest
    ///< tests for BuildInfo
{
public:
                   Test_BuildInfo() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
