/**
 * \file   CxTest_CxType.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxType.h>
//------------------------------------------------------------------------------
class CxTest_CxType :
    public CxTest
{
public:
                   CxTest_CxType();
    virtual       ~CxTest_CxType();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
