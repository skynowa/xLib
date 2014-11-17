/**
 * \file   Test_Shell.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/Shell.h>
//-------------------------------------------------------------------------------------------------
class Test_Shell :
    public Unit
{
public:
                   Test_Shell() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
