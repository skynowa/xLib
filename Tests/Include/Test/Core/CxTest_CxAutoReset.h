/**
 * \file   CxTest_CxAutoReset.h
 * \brief  test CxAutoReset
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxAutoReset.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoReset :
    public CxTest
    ///< tests for CxAutoReset
{
public:
                   CxTest_CxAutoReset() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
