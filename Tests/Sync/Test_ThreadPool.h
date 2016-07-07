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

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
