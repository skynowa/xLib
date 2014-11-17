/**
 * \file   Test_Debugger.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/Debugger.h>
//-------------------------------------------------------------------------------------------------
class Test_Debugger :
    public Unit
{
public:
                   Test_Debugger() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

