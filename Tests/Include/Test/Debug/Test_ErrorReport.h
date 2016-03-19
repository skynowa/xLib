/**
 * \file   Test_ErrorReport.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_ErrorReport :
    public Unit
{
public:
                   Test_ErrorReport() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
