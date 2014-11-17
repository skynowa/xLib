/**
 * \file   Test_SystemInfo.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/SystemInfo.h>
//-------------------------------------------------------------------------------------------------
class Test_SystemInfo :
    public Unit
{
public:
                   Test_SystemInfo() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
