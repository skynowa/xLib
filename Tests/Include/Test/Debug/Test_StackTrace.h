/**
 * \file   Test_StackTrace.h
 * \brief  test StackTrace
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_StackTrace :
    public Unit
{
public:
                   Test_StackTrace() {}

    virtual void_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

