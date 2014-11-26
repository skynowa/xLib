/**
 * \file   Test_SourceInfo.h
 * \brief  test SourceInfo
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/SourceInfo.h>
//-------------------------------------------------------------------------------------------------
class Test_SourceInfo :
    public Unit
    ///< tests for SourceInfo
{
public:
                   Test_SourceInfo() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
