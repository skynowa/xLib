/**
 * \file   Test_IpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/IpcMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_IpcMutex :
    public UnitTest
{
public:
                   Test_IpcMutex() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
