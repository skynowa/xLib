/**
 * \file   CxTest_CxNonArrayHeap.h
 * \brief  test CxNonArrayHeap
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxNonArrayHeap.h>
//------------------------------------------------------------------------------
class CxTest_CxNonArrayHeap :
    public CxTest
{
public:
                   CxTest_CxNonArrayHeap() {}

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
