/**
 * \file   CxTest_CxArray.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxArray.h>
//------------------------------------------------------------------------------
class CxTest_CxArray :
    public CxTest
{
public:
                   CxTest_CxArray();
    virtual       ~CxTest_CxArray();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
