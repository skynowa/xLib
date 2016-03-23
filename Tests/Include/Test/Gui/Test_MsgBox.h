/**
 * \file   Test_MsgBoxT.h
 * \brief  test MsgBoxT
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_MsgBox :
    public Unit
{
public:
                   Test_MsgBox() {}

    virtual bool_t unit() xOVERRIDE;
        ///< test unit
};
//-------------------------------------------------------------------------------------------------
