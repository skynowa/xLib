/**
 * \file   CxTest_CxShell.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/System/CxShell.h>
//------------------------------------------------------------------------------
class CxTest_CxShell :
    public CxTest
{
public:
                   CxTest_CxShell() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
