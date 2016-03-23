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

    virtual bool_t unit() xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
