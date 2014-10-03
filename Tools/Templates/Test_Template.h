/**
 * \file   Test_[CLASS_NAME].h
 * \brief  test [CLASS_NAME]
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/xxxxxxxxx/[CLASS_NAME].h>
//-------------------------------------------------------------------------------------------------
class Test_[CLASS_NAME] :
    public UnitTest
    ///< tests for [CLASS_NAME]
{
public:
                   Test_[CLASS_NAME]() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
