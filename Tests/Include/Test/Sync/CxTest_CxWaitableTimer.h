/**
 * \file   CxTest_CxWaitableTimer.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxWaitableTimer.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxWaitableTimer :
    public CxTest
{
public:
                   CxTest_CxWaitableTimer() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
