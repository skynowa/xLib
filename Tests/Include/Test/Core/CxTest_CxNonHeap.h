/**
 * \file   CxTest_CxNonHeap.h
 * \brief  test CxNonHeap
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxNonHeap.h>
//------------------------------------------------------------------------------
class CxTest_CxNonHeap :
    public CxTest
{
public:
                   CxTest_CxNonHeap() {}

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
