/**
 * \file   Test_Condition.h
 * \brief  test Condition
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Condition.h>
//-------------------------------------------------------------------------------------------------
class Test_Condition :
    public Test
{
public:
                    Test_Condition() {}

    virtual void_t  unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
