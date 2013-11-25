/**
 * \file   CxTest_CxThreadPool.h
 * \brief  test CxThreadPool
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxThreadPool.h>
//------------------------------------------------------------------------------
class CxTest_CxThreadPool :
    public CxTest
{
public:
                   CxTest_CxThreadPool() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
class CPoolThread :
    public CxThread
{
public:
    size_t         index;

                   CPoolThread(cbool_t &cbAutoDelete);
    virtual       ~CPoolThread();

protected:
    virtual uint_t uiOnRun(void_t *pData);
};
//------------------------------------------------------------------------------
