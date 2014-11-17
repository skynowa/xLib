/**
 * \file   Test_Signal.h
 * \brief  test Signal
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/Signal.h>
//-------------------------------------------------------------------------------------------------
class Test_Signal :
    public Unit
    ///< tests for Signal
{
public:
                   Test_Signal() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
