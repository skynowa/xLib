/**
 * \file   Test_Condition.h
 * \brief  test Condition
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/Condition.h>
//-------------------------------------------------------------------------------------------------
class Test_Condition :
    public Unit
{
public:
                    Test_Condition() {}

    virtual void_t  unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
