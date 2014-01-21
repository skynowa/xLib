/**
 * \file   CxTest_xStdStream.h
 * \brief  test xStdStream
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/xStdStream.h>
//-------------------------------------------------------------------------------------------------
class CxTest_xStdStream :
    public CxTest
    ///< tests for xStdStream
{
public:
                   CxTest_xStdStream() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
