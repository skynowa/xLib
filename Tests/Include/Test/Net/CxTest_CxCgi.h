/**
 * \file   CxTest_CxCgi.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxCgi.h>
//------------------------------------------------------------------------------
class CxTest_CxCgi :
    public CxTest
{
public:
                   CxTest_CxCgi();
    virtual       ~CxTest_CxCgi();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
