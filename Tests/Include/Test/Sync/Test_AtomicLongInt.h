/**
 * \file   Test_AtomicLongInt.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/AtomicLongInt.h>
//-------------------------------------------------------------------------------------------------
class Test_AtomicLongInt :
    public Unit
{
public:
                   Test_AtomicLongInt() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
