/**
 * \file   CxTest_CxStdError.h
 * \brief  test CxStdError
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxStdError.h>
//------------------------------------------------------------------------------
class CxTest_CxStdError :
    public CxTest
{
public:
                   CxTest_CxStdError();
        ///< constructor
    virtual       ~CxTest_CxStdError();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
