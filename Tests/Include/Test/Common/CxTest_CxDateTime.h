/**
 * \file   CxTest_CxDateTime.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxDateTime.h>
//------------------------------------------------------------------------------
class CxTest_CxDateTime :
    public CxTest
{
public:
                   CxTest_CxDateTime();
    virtual       ~CxTest_CxDateTime();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
