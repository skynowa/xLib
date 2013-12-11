/**
 * \file   CxTest_xTest.h
 * \brief  test xTest
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Test/xTest.h>
//---------------------------------------------------------------------------
class CxTest_xTest :
    public CxTest
    ///< tests for xTest
{
public:
                   CxTest_xTest() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
