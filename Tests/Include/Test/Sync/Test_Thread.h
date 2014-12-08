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

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;

private:
    void_t         unit1(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
