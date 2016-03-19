/**
 * \file   Test_AtomicLongInt.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_AtomicLongInt :
    public Unit
{
public:
                   Test_AtomicLongInt() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
