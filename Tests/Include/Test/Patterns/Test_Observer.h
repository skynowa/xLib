/**
 * \file   Test_Observer.h
 * \brief  test Observer
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Observer :
    public Unit
    ///< tests for Observer
{
public:
                   Test_Observer() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
