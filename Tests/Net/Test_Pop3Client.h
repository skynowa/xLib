/**
 * \file   Test_Pop3Client.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Pop3Client :
    public Unit
{
public:
                   Test_Pop3Client() {}

    virtual bool_t unit() xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
