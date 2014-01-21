/**
 * \file   CxTest_CxIpcSemaphore.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxIpcSemaphore.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxIpcSemaphore :
    public CxTest
{
public:
                   CxTest_CxIpcSemaphore() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

