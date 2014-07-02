/**
 * \file   Test_ThreadStorage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/ThreadStorage.h>
//-------------------------------------------------------------------------------------------------
class Test_ThreadStorage :
    public Test
{
public:
                   Test_ThreadStorage() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
