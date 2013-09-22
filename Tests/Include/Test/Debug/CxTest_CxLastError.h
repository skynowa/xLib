/**
 * \file   CxTest_CxLastError.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxLastError.h>
//------------------------------------------------------------------------------
class CxTest_CxLastError :
    public CxTest
{
public:
                   CxTest_CxLastError();
    virtual       ~CxTest_CxLastError();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

