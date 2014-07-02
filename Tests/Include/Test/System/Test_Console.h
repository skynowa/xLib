/**
 * \file   Test_Console.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/System/Console.h>
//-------------------------------------------------------------------------------------------------
class Test_Console :
    public Test
{
public:
                   Test_Console() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
