/**
 * \file   CxTest_CxFlags.h
 * \brief  test CxFlags
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxFlags.h>
//------------------------------------------------------------------------------
class CxTest_CxFlags :
    public CxTest
    ///< tests for CxFlags
{
public:
                   CxTest_CxFlags();
        ///< constructor
    virtual       ~CxTest_CxFlags();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
