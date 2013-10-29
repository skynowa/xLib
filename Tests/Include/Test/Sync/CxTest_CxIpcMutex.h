/**
 * \file   CxTest_CxIpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxIpcMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxIpcMutex :
    public CxTest
{
public:
                   CxTest_CxIpcMutex() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
