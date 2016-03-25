/**
 * \file   Test_File.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_File :
    public Unit
{
public:
                   Test_File() {}

    virtual bool_t unit();

private:
    bool_t         unit1();
    bool_t         unitPrivate();
};
//-------------------------------------------------------------------------------------------------
