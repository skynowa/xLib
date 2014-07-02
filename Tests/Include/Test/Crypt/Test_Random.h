/**
 * \file   Test_Random.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Crypt/Random.h>
//-------------------------------------------------------------------------------------------------
class Test_Random :
    public Test
{
public:
                   Test_Random() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
