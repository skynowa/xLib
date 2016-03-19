/**
 * \file   Test_SystemLog.h
 * \brief  test SystemLogs
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_SystemLog:
    public Unit
{
public:
                   Test_SystemLog() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

