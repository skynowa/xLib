/**
 * \file   Test_CoreApplication.h
 * \brief  test CoreApplication
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_CoreApplication :
    public Unit
    ///< tests for CoreApplication
{
public:
                   Test_CoreApplication() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
