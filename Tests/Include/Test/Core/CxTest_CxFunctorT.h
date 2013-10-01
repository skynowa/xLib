/**
 * \file   CxTest_CxFunctorT.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxFunctorT.h>
//------------------------------------------------------------------------------
class CxTest_CxFunctorT :
    public CxTest
{
public:
                   CxTest_CxFunctorT();
    virtual       ~CxTest_CxFunctorT();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
