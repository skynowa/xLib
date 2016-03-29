/**
 * \file   Test_User.h
 * \brief  test User
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_User :
    public Unit
    ///< tests for User
{
public:
                   Test_User() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
