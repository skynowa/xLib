/**
 * \file   Test_HandleT.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
class Test_HandleT :
    public Unit
{
public:
                   Test_HandleT() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

