/**
 * \file   Test_AutoIpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/AutoIpcMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoIpcMutex :
    public UnitTest
{
public:
                   Test_AutoIpcMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
