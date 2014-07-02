/**
 * \file   Test_Type.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/Type.h>
//-------------------------------------------------------------------------------------------------
class Test_Type :
    public Test
{
public:
                   Test_Type() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
