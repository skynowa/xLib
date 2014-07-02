/**
 * \file   Test_SystemLog.h
 * \brief  test SystemLogs
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Log/SystemLog.h>
//-------------------------------------------------------------------------------------------------
class Test_SystemLog:
    public Test
{
public:
                   Test_SystemLog() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

