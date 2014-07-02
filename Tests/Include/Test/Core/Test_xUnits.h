/**
 * \file   Test_xUnits.h
 * \brief  test xUnits
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/xUnits.h>
//---------------------------------------------------------------------------
class Test_xUnits :
    public Test
    ///< tests for xUnits
{
public:
                   Test_xUnits() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
