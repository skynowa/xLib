/**
 * \file   Test_IpcSemaphore.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_IpcSemaphore :
    public Unit
{
public:
                   Test_IpcSemaphore() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

