/**
 * \file   Test_Sleeper.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Sleeper.h>
//-------------------------------------------------------------------------------------------------
class Test_Sleeper :
    public Test
{
public:
                   Test_Sleeper() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
