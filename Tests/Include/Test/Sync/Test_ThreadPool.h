/**
 * \file   Test_ThreadPool.h
 * \brief  test ThreadPool
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/ThreadPool.h>
//-------------------------------------------------------------------------------------------------
class Test_ThreadPool :
    public Test
{
public:
                   Test_ThreadPool() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
class CPoolThread :
    public Thread
{
public:
    size_t         index;

                   CPoolThread(cbool_t &cbAutoDelete);
    virtual       ~CPoolThread();

protected:
    virtual uint_t uiOnRun(void_t *pData);
};
//-------------------------------------------------------------------------------------------------
