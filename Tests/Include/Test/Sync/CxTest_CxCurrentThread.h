/**
 * \file   CxTest_CxCurrentThread.h
 * \brief  test CxCurrentThread
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxCurrentThread.h>
//------------------------------------------------------------------------------
class CxTest_CxCurrentThread :
    public CxTest
{
public:
                   CxTest_CxCurrentThread() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
