/**
 * \file   Test_Dll.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Dll :
    public Unit
{
public:
                   Test_Dll() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
