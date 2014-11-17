/**
 * \file   Test_ProcessInfo.h
 * \brief  test ProcessInfo
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/ProcessInfo.h>
//-------------------------------------------------------------------------------------------------
class Test_ProcessInfo :
    public Unit
{
public:
                   Test_ProcessInfo() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
