/**
 * \file   Test_Exception.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Debug/Exception.h>
//-------------------------------------------------------------------------------------------------
class Test_Exception :
    public UnitTest
{
public:
                   Test_Exception() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

