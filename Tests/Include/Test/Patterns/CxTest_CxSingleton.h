/**
 * \file   CxTest_CxSingleton.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Patterns/CxSingleton.h>
//------------------------------------------------------------------------------
class CxTest_CxSingleton :
    public CxTest
{
public:
                   CxTest_CxSingleton();
    virtual       ~CxTest_CxSingleton();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
