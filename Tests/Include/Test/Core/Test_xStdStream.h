/**
 * \file   Test_xStdStream.h
 * \brief  test xStdStream
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/xStdStream.h>
//-------------------------------------------------------------------------------------------------
class Test_xStdStream :
    public Test
    ///< tests for xStdStream
{
public:
                   Test_xStdStream() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
