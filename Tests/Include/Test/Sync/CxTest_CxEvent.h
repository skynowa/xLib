/**
 * \file   CxTest_CxEvent.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxEvent.h>
//------------------------------------------------------------------------------
class CxTest_CxEvent :
    public CxTest
{
public:
                   CxTest_CxEvent();
    virtual       ~CxTest_CxEvent();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};

