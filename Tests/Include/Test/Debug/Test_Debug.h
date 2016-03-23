/**
 * \file   Test_Debug.h
 * \brief  test Debug
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Debug :
    public Unit
{
public:
                   Test_Debug() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
