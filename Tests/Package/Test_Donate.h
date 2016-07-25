/**
 * \file   Test_Donate.h
 * \brief  test Donate
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Donate :
    public Unit
    ///< tests for Donate
{
public:
                   Test_Donate() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
