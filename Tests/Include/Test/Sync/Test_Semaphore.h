/**
 * \file   Test_Semaphore.h
 * \brief  test Semaphore
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Semaphore.h>
//-------------------------------------------------------------------------------------------------
class Test_Semaphore :
    public Test
{
public:
                   Test_Semaphore() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
