/**
 * \file   Test_HandleT.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_HandleT :
    public Unit
{
public:
                   Test_HandleT() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

