/**
 * \file   Test_ThreadPool.h
 * \brief  test ThreadPool
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_ThreadPool :
    public Unit
{
public:
                   Test_ThreadPool() {}

    virtual void_t unit() xOVERRIDE;
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
