/**
 * \file   Test_Com.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/Win/Com.h>
//-------------------------------------------------------------------------------------------------
class Test_Com :
    public UnitTest
{
public:
                   Test_Com() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
