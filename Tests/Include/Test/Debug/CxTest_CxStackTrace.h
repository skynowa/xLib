/**
 * \file   CxTest_CxStackTrace.h
 * \brief  test CxStackTrace
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxStackTrace.h>
//------------------------------------------------------------------------------
class CxTest_CxStackTrace :
    public CxTest
{
public:
                   CxTest_CxStackTrace();
        ///< constructor
    virtual       ~CxTest_CxStackTrace();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------

