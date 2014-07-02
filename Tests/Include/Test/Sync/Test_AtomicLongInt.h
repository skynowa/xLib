/**
 * \file   Test_AtomicLongInt.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/AtomicLongInt.h>
//-------------------------------------------------------------------------------------------------
class Test_AtomicLongInt :
    public UnitTest
{
public:
                   Test_AtomicLongInt() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
