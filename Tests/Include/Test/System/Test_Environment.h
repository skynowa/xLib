/**
 * \file   Test_Environment.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/System/Environment.h>
//-------------------------------------------------------------------------------------------------
class Test_Environment :
    public UnitTest
{
public:
                   Test_Environment() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
