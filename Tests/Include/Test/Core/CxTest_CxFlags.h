/**
 * \file   CxTest_CxFlags.h
 * \brief  test CxFlags
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxFlags.h>
//------------------------------------------------------------------------------
class CxTest_CxFlags :
    public CxTest
    ///< tests for CxFlags
{
public:
                   CxTest_CxFlags() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
