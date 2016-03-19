/**
 * \file   Test_SourceInfo.h
 * \brief  test SourceInfo
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_SourceInfo :
    public Unit
    ///< tests for SourceInfo
{
public:
                   Test_SourceInfo() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
