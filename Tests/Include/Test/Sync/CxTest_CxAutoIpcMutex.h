/**
 * \file   CxTest_CxAutoIpcMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAutoIpcMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoIpcMutex :
    public CxTest
{
public:
                   CxTest_CxAutoIpcMutex() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
