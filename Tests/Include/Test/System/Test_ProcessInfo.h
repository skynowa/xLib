/**
 * \file   Test_ProcessInfo.h
 * \brief  test ProcessInfo
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_ProcessInfo :
    public Unit
{
public:
                   Test_ProcessInfo() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
