/**
 * \file   CxTest_CxFunctorT.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxFunctorT.h>
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
