/**
 * \file   Test_AtomicLongInt.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/AtomicLongInt.h>
//-------------------------------------------------------------------------------------------------
class Test_AtomicLongInt :
    public Test
{
public:
                   Test_AtomicLongInt() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
