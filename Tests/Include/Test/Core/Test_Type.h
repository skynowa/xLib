/**
 * \file   Test_Type.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/Type.h>
//-------------------------------------------------------------------------------------------------
class Test_Type :
    public Unit
{
public:
                   Test_Type() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
