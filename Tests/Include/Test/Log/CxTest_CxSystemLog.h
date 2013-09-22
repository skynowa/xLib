/**
 * \file   CxTest_CxSystemLog.h
 * \brief  test CxSystemLogs
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxSystemLog.h>
//------------------------------------------------------------------------------
class CxTest_CxSystemLog:
    public CxTest
{
public:
                   CxTest_CxSystemLog();
        ///< constructor
    virtual       ~CxTest_CxSystemLog();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------

