/**
 * \file   CxTest_CxNonHeap.h
 * \brief  test CxNonHeap
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxNonHeap.h>
//------------------------------------------------------------------------------
class CxTest_CxNonHeap :
    public CxTest
{
public:
                   CxTest_CxNonHeap();
        ///< constructor
    virtual       ~CxTest_CxNonHeap();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
