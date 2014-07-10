/**
 * \file   Test_StdError.h
 * \brief  test StdError
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Debug/StdError.h>
//-------------------------------------------------------------------------------------------------
class Test_StdError :
    public UnitTest
{
public:
                   Test_StdError() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
