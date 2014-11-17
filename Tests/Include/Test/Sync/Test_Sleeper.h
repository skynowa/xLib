/**
 * \file   Test_Sleeper.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/Sleeper.h>
//-------------------------------------------------------------------------------------------------
class Test_Sleeper :
    public Unit
{
public:
                   Test_Sleeper() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
