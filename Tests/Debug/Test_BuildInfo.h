/**
 * \file   Test_BuildInfo.h
 * \brief  test BuildInfo
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_BuildInfo :
    public Unit
    ///< tests for BuildInfo
{
public:
                   Test_BuildInfo() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
