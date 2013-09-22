/**
 * \file   CxTest_CxSystemInfo.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxSystemInfo.h>
//------------------------------------------------------------------------------
class CxTest_CxSystemInfo :
    public CxTest
{
public:
                   CxTest_CxSystemInfo();
    virtual       ~CxTest_CxSystemInfo();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
