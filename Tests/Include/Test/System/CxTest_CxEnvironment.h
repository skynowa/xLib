/**
 * \file   CxTest_CxEnvironment.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/System/CxEnvironment.h>
//------------------------------------------------------------------------------
class CxTest_CxEnvironment :
    public CxTest
{
public:
                   CxTest_CxEnvironment() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
