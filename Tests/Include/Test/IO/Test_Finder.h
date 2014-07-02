/**
 * \file   Test_Finder.h
 * \brief  test Finder
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Finder.h>
//-------------------------------------------------------------------------------------------------
class Test_Finder :
    public UnitTest
    ///< tests for Finder
{
public:
                   Test_Finder() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

