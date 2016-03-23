/**
 * \file   Test_Service.h
 * \brief  test Service
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Service :
    public Unit
    ///< tests for Service
{
public:
                   Test_Service() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
