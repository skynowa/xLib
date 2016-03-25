/**
 * \file   Test_Guid.h
 * \brief  test Guid
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Guid :
    public Unit
    ///< tests for Guid
{
public:
                   Test_Guid() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
