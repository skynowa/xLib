/**
 * \file   Test_AutoReset.h
 * \brief  test AutoReset
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_AutoReset :
    public Unit
    ///< tests for AutoReset
{
public:
                   Test_AutoReset() {}

    virtual void_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
