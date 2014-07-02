/**
 * \file   Test_IpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/IpcMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_IpcMutex :
    public Test
{
public:
                   Test_IpcMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
