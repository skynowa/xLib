/**
 * \file   CxTest_CxBuildInfo.h
 * \brief  test CxBuildInfo
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxBuildInfo.h>
//---------------------------------------------------------------------------
class CxTest_CxBuildInfo :
    public CxTest
    ///< tests for CxBuildInfo
{
public:
                   CxTest_CxBuildInfo() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//---------------------------------------------------------------------------
