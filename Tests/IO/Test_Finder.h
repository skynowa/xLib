/**
 * \file   Test_Finder.h
 * \brief  test Finder
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Finder :
    public Unit
    ///< tests for Finder
{
public:
                   Test_Finder() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

