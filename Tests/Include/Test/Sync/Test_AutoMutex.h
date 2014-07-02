/**
 * \file   Test_AutoMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/AutoMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoMutex :
    public Test
{
public:
                   Test_AutoMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
