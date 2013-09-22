/**
 * \file   CxTest_CxSemaphore.h
 * \brief  test CxSemaphore
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//------------------------------------------------------------------------------
class CxTest_CxSemaphore :
    public CxTest
{
public:
                   CxTest_CxSemaphore();
        ///< constructor
    virtual       ~CxTest_CxSemaphore();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
