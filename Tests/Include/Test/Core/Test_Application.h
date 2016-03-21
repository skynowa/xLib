/**
 * \file   Test_Application.h
 * \brief  test Application
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Application :
    public Unit
    ///< tests for Application
{
public:
                   Test_Application() {}

    virtual void_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
