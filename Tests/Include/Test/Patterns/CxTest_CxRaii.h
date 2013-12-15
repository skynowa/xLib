/**
 * \file   CxTest_CxRaii.h
 * \brief  test CxRaii
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Patterns/CxRaii.h>
//---------------------------------------------------------------------------
class CxTest_CxRaii :
    public CxTest
    ///< tests for CxRaii
{
public:
                   CxTest_CxRaii() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
