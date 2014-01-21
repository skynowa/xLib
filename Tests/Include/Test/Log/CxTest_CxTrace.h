/**
 * \file   CxTest_CxTrace.h
 * \brief  test CxTrace
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxTrace.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxTrace :
    public CxTest
{
public:
                   CxTest_CxTrace() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
