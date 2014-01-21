/**
 * \file   CxTest_CxStackTrace.h
 * \brief  test CxStackTrace
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxStackTrace.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxStackTrace :
    public CxTest
{
public:
                   CxTest_CxStackTrace() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

