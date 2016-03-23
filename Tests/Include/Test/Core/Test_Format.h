/**
 * \file   Test_Format.h
 * \brief  test Format
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Format :
    public Unit
    ///< tests for Format
{
public:
                   Test_Format() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
