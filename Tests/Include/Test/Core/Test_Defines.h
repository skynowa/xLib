/**
 * \file   Test_Defines.h
 * \brief  test Defines
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Defines :
    public Unit
{
public:
                   Test_Defines() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
