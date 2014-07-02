/**
 * \file   Test_ProcessInfo.h
 * \brief  test ProcessInfo
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/System/ProcessInfo.h>
//-------------------------------------------------------------------------------------------------
class Test_ProcessInfo :
    public Test
{
public:
                   Test_ProcessInfo() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
