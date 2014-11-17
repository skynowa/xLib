/**
 * \file   Test_ThreadStorage.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/ThreadStorage.h>
//-------------------------------------------------------------------------------------------------
class Test_ThreadStorage :
    public Unit
{
public:
                   Test_ThreadStorage() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
