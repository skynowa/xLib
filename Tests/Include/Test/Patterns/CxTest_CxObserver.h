/**
 * \file   CxTest_CxObserver.h
 * \brief  test CxObserver
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Patterns/CxObserver.h>
//---------------------------------------------------------------------------
class CxTest_CxObserver :
    public CxTest
    ///< tests for CxObserver
{
public:
                   CxTest_CxObserver() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
