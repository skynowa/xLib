/**
 * \file   Test_Environment.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/Environment.h>
//-------------------------------------------------------------------------------------------------
class Test_Environment :
    public Unit
{
public:
                   Test_Environment() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
