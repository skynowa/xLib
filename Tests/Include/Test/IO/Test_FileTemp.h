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

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

