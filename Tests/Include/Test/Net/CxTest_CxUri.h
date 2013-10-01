/**
 * \file   CxTest_CxUri.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxUri.h>
//------------------------------------------------------------------------------
class CxTest_CxUri :
    public CxTest
{
public:
                   CxTest_CxUri();
    virtual       ~CxTest_CxUri();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
