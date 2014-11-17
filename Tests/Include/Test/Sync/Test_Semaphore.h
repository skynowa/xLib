/**
 * \file   Test_Semaphore.h
 * \brief  test Semaphore
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/Semaphore.h>
//-------------------------------------------------------------------------------------------------
class Test_Semaphore :
    public Unit
{
public:
                   Test_Semaphore() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
