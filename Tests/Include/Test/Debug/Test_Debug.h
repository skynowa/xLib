/**
 * \file   Test_Debug.h
 * \brief  test Debug
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/Debug.h>
//-------------------------------------------------------------------------------------------------
class Test_Debug :
    public Unit
{
public:
                   Test_Debug() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
