/**
 * \file   Test_Limits.h
 * \brief  test Limits
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Limits :
    public Unit
    ///< tests for Limits
{
public:
                   Test_Limits() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
