/**
 * \file   CxTest_CxMutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxMutex :
    public CxTest
{
public:
                   CxTest_CxMutex() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

