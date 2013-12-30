/**
 * \file   CxTest_xUnits.h
 * \brief  test xUnits
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/xUnits.h>
//---------------------------------------------------------------------------
class CxTest_xUnits :
    public CxTest
    ///< tests for xUnits
{
public:
                   CxTest_xUnits() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
