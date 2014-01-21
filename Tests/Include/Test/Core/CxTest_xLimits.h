/**
 * \file   CxTest_xLimits.h
 * \brief  test xLimits
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/xLimits.h>
//-------------------------------------------------------------------------------------------------
class CxTest_xLimits :
    public CxTest
    ///< tests for xLimits
{
public:
                   CxTest_xLimits() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
