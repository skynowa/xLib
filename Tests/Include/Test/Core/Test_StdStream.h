/**
 * \file   Test_StdStream.h
 * \brief  test StdStream
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/StdStream.h>
//-------------------------------------------------------------------------------------------------
class Test_StdStream :
    public Unit
    ///< tests for StdStream
{
public:
                   Test_StdStream() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
