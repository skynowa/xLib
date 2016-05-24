/**
 * \file   Test_Algos.h
 * \brief  test Algos
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Algos :
    public Unit
    ///< tests for Algos
{
public:
                   Test_Algos() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
