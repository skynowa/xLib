/**
 * \file   Test_WaitableTimer.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/WaitableTimer.h>
//-------------------------------------------------------------------------------------------------
class Test_WaitableTimer :
    public UnitTest
{
public:
                   Test_WaitableTimer() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
