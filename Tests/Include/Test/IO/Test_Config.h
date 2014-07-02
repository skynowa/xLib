/**
 * \file   Test_Config.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Config.h>
//-------------------------------------------------------------------------------------------------
class Test_Config :
    public UnitTest
{
public:
                    Test_Config() {}

    virtual  void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
