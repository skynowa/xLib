/**
 * \file   Test_StdError.h
 * \brief  test StdError
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_StdError :
    public Unit
{
public:
                   Test_StdError() {}

    virtual void_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
