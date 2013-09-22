/**
 * \file   CxTest_CxConsole.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxConsole.h>
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
