/**
 * \file   CxTest_CxSemaphore.h
 * \brief  test CxSemaphore
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//------------------------------------------------------------------------------
class CxTest_CxSemaphore :
    public CxTest
{
public:
                   CxTest_CxSemaphore() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
