/**
 * \file   Test_Environment.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/System/Environment.h>
//-------------------------------------------------------------------------------------------------
class Test_Environment :
    public Test
{
public:
                   Test_Environment() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
