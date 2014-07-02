/**
 * \file   Test_Mutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Mutex.h>
//-------------------------------------------------------------------------------------------------
class Test_Mutex :
    public Test
{
public:
                   Test_Mutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

