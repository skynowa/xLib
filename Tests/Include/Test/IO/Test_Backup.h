/**
 * \file   Test_Backup.h
 * \brief  test Backup
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Backup :
    public Unit
{
public:
                   Test_Backup() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
