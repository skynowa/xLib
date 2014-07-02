/**
 * \file   Test_Com.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/Win/Com.h>
//-------------------------------------------------------------------------------------------------
class Test_Com :
    public Test
{
public:
                   Test_Com() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
