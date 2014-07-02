/**
 * \file   Test_Utils.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/Utils.h>
//-------------------------------------------------------------------------------------------------
class Test_Utils :
    public Test
{
public:
                   Test_Utils() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
