/**
 * \file   Test_ThreadPool.h
 * \brief  test ThreadPool
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/ThreadPool.h>
//-------------------------------------------------------------------------------------------------
class Test_ThreadPool :
    public UnitTest
{
public:
                   Test_ThreadPool() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
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
