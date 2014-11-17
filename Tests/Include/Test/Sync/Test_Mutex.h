/**
 * \file   Test_Mutex.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Sync/Mutex.h>
//-------------------------------------------------------------------------------------------------
class Test_Mutex :
    public Unit
{
public:
                   Test_Mutex() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

