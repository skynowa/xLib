/**
 * \file   Test_Units.h
 * \brief  test Units
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Units :
    public Unit
    ///< tests for Units
{
public:
                   Test_Units() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
