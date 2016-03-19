/**
 * \file   Test_Test.h
 * \brief  test Test
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_xTest :
    public Unit
    ///< tests for Test
{
public:
                   Test_xTest() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
