/**
 * \file   Test_Array.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
class Test_Array :
    public UnitTest
{
public:
                   Test_Array() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
