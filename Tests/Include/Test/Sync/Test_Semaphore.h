/**
 * \file   Test_Semaphore.h
 * \brief  test Semaphore
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Semaphore :
    public Unit
{
public:
                   Test_Semaphore() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
