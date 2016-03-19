/**
 * \file   Test_Raii.h
 * \brief  test Raii
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Raii :
    public Unit
    ///< tests for Raii
{
public:
                   Test_Raii() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
