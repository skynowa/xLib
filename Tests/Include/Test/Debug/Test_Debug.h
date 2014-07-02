/**
 * \file   Test_Debug.h
 * \brief  test Debug
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Debug/Debug.h>
//-------------------------------------------------------------------------------------------------
class Test_Debug :
    public UnitTest
{
public:
                   Test_Debug() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
