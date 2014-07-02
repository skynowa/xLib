/**
 * \file   Test_ProcessInfo.h
 * \brief  test ProcessInfo
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/System/ProcessInfo.h>
//-------------------------------------------------------------------------------------------------
class Test_ProcessInfo :
    public UnitTest
{
public:
                   Test_ProcessInfo() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
