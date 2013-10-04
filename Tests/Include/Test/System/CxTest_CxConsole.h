/**
 * \file   CxTest_CxConsole.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/System/CxConsole.h>
//------------------------------------------------------------------------------
class CxTest_CxConsole :
    public CxTest
{
public:
                   CxTest_CxConsole();
    virtual       ~CxTest_CxConsole();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
