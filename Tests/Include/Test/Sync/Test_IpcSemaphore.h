/**
 * \file   Test_IpcSemaphore.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/IpcSemaphore.h>
//-------------------------------------------------------------------------------------------------
class Test_IpcSemaphore :
    public UnitTest
{
public:
                   Test_IpcSemaphore() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

