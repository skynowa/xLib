/**
 * \file   Test_WaitableTimer.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/WaitableTimer.h>
//-------------------------------------------------------------------------------------------------
class Test_WaitableTimer :
    public Test
{
public:
                   Test_WaitableTimer() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
