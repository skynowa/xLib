/**
 * \file   Test_Console.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/Console.h>
//-------------------------------------------------------------------------------------------------
class Test_Console :
    public Unit
{
public:
                   Test_Console() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
