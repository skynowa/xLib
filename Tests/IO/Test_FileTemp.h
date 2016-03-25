/**
 * \file   Test_FileTemp.h
 * \brief  test FileTemp
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_FileTemp :
    public Unit
{
public:
                   Test_FileTemp() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

