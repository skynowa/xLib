/**
 * \file   CxTest_CxAutoMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAutoMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoMutex :
    public CxTest
{
public:
                   CxTest_CxAutoMutex();
    virtual       ~CxTest_CxAutoMutex();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
