/**
 * \file   CxTest_CxCompletionPort.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/Win/CxCompletionPort.h>
//------------------------------------------------------------------------------
class CxTest_CxCompletionPort :
    public CxTest
{
public:
                   CxTest_CxCompletionPort();
    virtual       ~CxTest_CxCompletionPort();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
