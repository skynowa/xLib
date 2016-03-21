/**
 * \file   Test_Operators.h
 * \brief  test Operators
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Operators :
    public Unit
    ///< tests for Operators
{
public:
                   Test_Operators() {}

    virtual void_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
