/**
 * \file   Test_ThreadStorage.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_ThreadStorage :
    public Unit
{
public:
                   Test_ThreadStorage() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
