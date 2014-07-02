/**
 * \file   Test_Process.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Process.h>
//-------------------------------------------------------------------------------------------------
class Test_Process :
    public Test
{
public:
                   Test_Process() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

