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

    virtual bool_t  unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
