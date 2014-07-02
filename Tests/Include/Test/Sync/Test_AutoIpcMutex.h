/**
 * \file   Test_AutoIpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/AutoIpcMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoIpcMutex :
    public Test
{
public:
                   Test_AutoIpcMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
