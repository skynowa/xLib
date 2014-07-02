/**
 * \file   Test_Volume.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Volume.h>
//-------------------------------------------------------------------------------------------------
class Test_Volume :
    public Test
{
public:
                   Test_Volume() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
