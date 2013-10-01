/**
 * \file   CxTest_CxCurrentProcess.h
 * \brief  test CxCurrentProcess
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxCurrentProcess.h>
//------------------------------------------------------------------------------
class CxTest_CxCurrentProcess :
    public CxTest
{
public:
                   CxTest_CxCurrentProcess();
        ///< constructor
    virtual       ~CxTest_CxCurrentProcess();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
