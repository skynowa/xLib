/**
 * \file   Test_Condition.h
 * \brief  test Condition
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Condition :
    public Unit
{
public:
                    Test_Condition() {}

    virtual void_t  unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
