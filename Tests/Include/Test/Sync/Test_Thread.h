/**
 * \file   Test_Thread.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Thread :
    public Unit
{
public:
                   Test_Thread() {}

    virtual void_t unit() xOVERRIDE;

private:
    void_t         unit1();
};
//-------------------------------------------------------------------------------------------------
