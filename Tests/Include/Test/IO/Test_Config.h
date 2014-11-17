/**
 * \file   Test_Config.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/IO/Config.h>
//-------------------------------------------------------------------------------------------------
class Test_Config :
    public Unit
{
public:
                    Test_Config() {}

    virtual  void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
