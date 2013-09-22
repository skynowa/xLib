/**
 * \file   CxTest_CxUtils.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxUtils.h>
//------------------------------------------------------------------------------
class CxTest_CxUtils :
    public CxTest
{
public:
                   CxTest_CxUtils();
    virtual       ~CxTest_CxUtils();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
