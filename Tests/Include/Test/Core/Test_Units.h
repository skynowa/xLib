/**
 * \file   Test_Units.h
 * \brief  test Units
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/Units.h>
//---------------------------------------------------------------------------
class Test_Units :
    public UnitTest
    ///< tests for Units
{
public:
                   Test_Units() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
