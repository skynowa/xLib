/**
 * \file   CxTest_CxTracer.h
 * \brief  test CxTracer
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxTracer.h>
//------------------------------------------------------------------------------
class CxTest_CxTracer :
    public CxTest
{
public:
                   CxTest_CxTracer() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
