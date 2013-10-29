/**
 * \file   CxTest_CxAutoProfiler.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxAutoProfiler.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoProfiler :
    public CxTest
{
public:
                   CxTest_CxAutoProfiler() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
