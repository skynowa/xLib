/**
 * \file   Test_ApplicationInfo.h
 * \brief  test ApplicationInfo
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_ApplicationInfo :
    public Unit
    ///< tests for ApplicationInfo
{
public:
                   Test_ApplicationInfo() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
