/**
 * \file   Test_Singleton.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Patterns/Singleton.h>
//-------------------------------------------------------------------------------------------------
class Test_Singleton :
    public UnitTest
{
public:
                   Test_Singleton() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
