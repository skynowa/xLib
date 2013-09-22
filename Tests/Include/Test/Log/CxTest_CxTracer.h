/**
 * \file   CxTest_CxTracer.h
 * \brief  test CxTracer
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxTracer.h>
//------------------------------------------------------------------------------
class CxTest_CxTracer :
    public CxTest
{
public:
                   CxTest_CxTracer();
        ///< constructor
    virtual       ~CxTest_CxTracer();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
