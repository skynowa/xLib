/**
 * \file   Test_Utils.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/Utils.h>
//-------------------------------------------------------------------------------------------------
class Test_Utils :
    public UnitTest
{
public:
                   Test_Utils() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
