/**
 * \file   Test_StdError.h
 * \brief  test StdError
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/StdError.h>
//-------------------------------------------------------------------------------------------------
class Test_StdError :
    public Test
{
public:
                   Test_StdError() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
