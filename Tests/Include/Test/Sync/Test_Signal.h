/**
 * \file   Test_Signal.h
 * \brief  test Signal
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Signal :
    public Unit
    ///< tests for Signal
{
public:
                   Test_Signal() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
