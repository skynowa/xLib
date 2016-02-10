/**
 * \file   Test_Csv.h
 * \brief  test Csv
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_Csv :
    public Unit
    ///< tests for Csv
{
public:
                   Test_Csv() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
