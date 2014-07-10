/**
 * \file   Test_Char.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Core/Char.h>
//-------------------------------------------------------------------------------------------------
class Test_Char :
    public UnitTest
{
public:
                   Test_Char() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
