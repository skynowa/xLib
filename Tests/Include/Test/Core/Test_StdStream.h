/**
 * \file   Test_StdStream.h
 * \brief  test StdStream
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/StdStream.h>
//-------------------------------------------------------------------------------------------------
class Test_StdStream :
    public UnitTest
    ///< tests for StdStream
{
public:
                   Test_StdStream() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
