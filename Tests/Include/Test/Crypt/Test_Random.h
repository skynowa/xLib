/**
 * \file   Test_Random.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Crypt/Random.h>
//-------------------------------------------------------------------------------------------------
class Test_Random :
    public UnitTest
{
public:
                   Test_Random() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
