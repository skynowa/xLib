/**
 * \file   Test_AutoMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/AutoMutex.h>
//-------------------------------------------------------------------------------------------------
class Test_AutoMutex :
    public UnitTest
{
public:
                   Test_AutoMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
