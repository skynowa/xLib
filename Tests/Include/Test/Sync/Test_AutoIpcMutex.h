/**
 * \file   Test_AutoIpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_AutoIpcMutex :
    public Unit
{
public:
                   Test_AutoIpcMutex() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
