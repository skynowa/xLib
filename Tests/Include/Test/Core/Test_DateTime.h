/**
 * \file   Test_DateTime.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
class Test_DateTime :
    public Unit
{
public:
                   Test_DateTime() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
