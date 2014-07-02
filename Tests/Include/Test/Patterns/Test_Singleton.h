/**
 * \file   Test_Singleton.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Patterns/Singleton.h>
//-------------------------------------------------------------------------------------------------
class Test_Singleton :
    public Test
{
public:
                   Test_Singleton() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
