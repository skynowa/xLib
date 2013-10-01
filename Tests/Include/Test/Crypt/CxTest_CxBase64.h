/**
 * \file   CxTest_CxBase64.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxBase64.h>
//------------------------------------------------------------------------------
class CxTest_CxBase64 :
    public CxTest
{
public:
                   CxTest_CxBase64();
    virtual       ~CxTest_CxBase64();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
