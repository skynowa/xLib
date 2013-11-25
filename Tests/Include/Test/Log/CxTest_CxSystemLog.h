/**
 * \file   CxTest_CxSystemLog.h
 * \brief  test CxSystemLogs
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxSystemLog.h>
//------------------------------------------------------------------------------
class CxTest_CxSystemLog:
    public CxTest
{
public:
                   CxTest_CxSystemLog() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------

