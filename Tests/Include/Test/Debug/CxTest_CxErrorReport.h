/**
 * \file   CxTest_CxErrorReport.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxErrorReport.h>
//------------------------------------------------------------------------------
class CxTest_CxErrorReport :
    public CxTest
{
public:
                   CxTest_CxErrorReport() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
