/**
 * \file   CxTest_CxFileLog.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxFileLog.h>
//------------------------------------------------------------------------------
class CxTest_CxFileLog :
    public CxTest
{
public:
                   CxTest_CxFileLog();
    virtual       ~CxTest_CxFileLog();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

